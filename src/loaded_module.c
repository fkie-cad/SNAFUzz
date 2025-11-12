
// 
// Loading / Parsing / Using of "Loaded Modules", i.e: Any PE file loaded into memory.
// 
// At the start of execution, or whenever the user enters the debugger, we refresh the
// loaded module list (`globals.module_list`). This is done by
// 
//      1) Finding the NT kernel by searching backwards from the `IA32_LSTAR` register, 
//         which holds `nt!KiSystemCall64`, until we find a MZ header.
//         See `maybe_find_and_load_ntoskrnl`.
//         
//      2) Iterating `nt!PsLoadedModuleList` to find what the loaded kernel modules are
//         and where they are loaded too.
//         
//      3) Iterating '_PEB.Ldr.InMemoryOrderModuleList' to find all the loaded user modules
//         and where they are loaded too.
//         
// To aid debugging, we are interested in two set of information:
//    1) The unwind information
//    2) The symbol file (.pdb)
// Because aggressively downloading all the symbol files would take a long time
// and is not necessary, we instead load symbols and unwind information lazily.
// See `loaded_module_try_to_load_pdb` and `loaded_module_try_to_load_unwind_information`.
// 
// Because at any point, any part of the unwind information of an image could be unmapped,
// and because Microsoft .pdb's often contain unwind information, we try to load the symbols
// first, before trying to load the unwind information from guest memory.
// 
// Further, because also the debug directory inside the module could be unmapped, everything
// needs to be failable and reentrant.
// 
// To load symbol files, we first look at the Debug Directory inside the image.
// If this Debug Directory specifies a full path, we try to load it from the disk.
// Otherwise, or if we failed to load it from disk, we attempt to download it from the
// Microsoft symbol store and cache it in a 'symbols' folder.
// 
// If we fail to unwind information, we fall back to scanning the stack for addresses,
// which "look like calls" to unwind a function frame. See `unwind_one_function`.
// 

struct loaded_module{
    struct loaded_module *next;
    
    struct string short_name;
    
    u64 guest_image_base;
    u64 size_of_image;
    
    struct{
        u32 rva;
        u32 size;
        u8 *base;    
    } pdata, xdata;
    
    // Set if both .pdata and .xdata sections have been loaded.
    int have_unwind_information;
    
    // This is here to only write coverage files that have changed.
    u64 coverage; 
    
    // These are here to only download and parse the .PDB on a single thread.
    // @cleanup: Maybe there is a simpler way using a ticket lock.
    //     'load_in_progress'  is when the first thread starts loading the .PDB.
    //     'tried_to_load_pdb' is set when this thread fails or succeeds in loading the .PDB.
    // Once we have tried to download and load the .PDB once, we do not try again.
    u32 tried_to_load_pdb;
    u32 load_in_progress;
    struct pdb_context *pdb_context;
};

struct loaded_module *get_loaded_module(struct string module_name){
    for(struct loaded_module *module = globals.module_list.first; module; module = module->next){
        
        if(module_name.data){
            if(module->short_name.size != module_name.size) continue;
            if(strnicmp(module->short_name.data, module_name.data, module_name.size)) continue;
        }
        return module;
    }
    return null;
}

struct loaded_module *get_module_for_address(u64 address){
    struct loaded_module *module = globals.module_list.first;
    
    for(; module; module = module->next){
        if(module->guest_image_base <= address && address < module->guest_image_base + module->size_of_image){
            break;
        }
    }
    
    return module;
}

static void loaded_module_try_to_load_pdb(struct context *context, struct loaded_module *module){
    
    int found_rsds = 0;
    
    struct _RSDS_DEBUG_DIRECTORY{
        char RSDS[4];
        struct guid pdb_guid;
        u32 pdb_age;
        char pdb_name[0x200];
    } rsds;
    
    {
        // 
        // First extract the "GUID" and "Age" from the Debug Directory.
        // This might potentially crash, if something is mapped out.
        // If it crashes, we just want to return (we have not _tried_ to load the PDB yet,
        // only the GUID).
        // 
        
        u64 guest_image_base = module->guest_image_base;
        
        struct crash_information crash_information = enter_debugging_routine(context);
        u64 user_cr3 = patch_in_cr3_for_virtual_address(context, guest_image_base, /*print cr3*/false);
        
        u32 pe_header_offset = guest_read(u32, guest_image_base + 0x3c);
        pe_header_offset += 4;
        
        u32 optional_header_offset = pe_header_offset + 20;
        u32 directory_base = optional_header_offset + 112;
        
        u32 debug_offset = guest_read(u32, guest_image_base + directory_base + 6 * 8);
        u32 debug_size   = guest_read(u32, guest_image_base + directory_base + 6 * 8 + 4);
        u32 debug_end_offset = debug_offset + debug_size;
        
        for(; debug_offset < debug_end_offset; debug_offset += /*sizeof(_IMAGE_DEBUG_DIRECTORY)*/7 * 4){
            
            struct {
                u32 characteristics;
                u32 time_date_stamp;
                u16 major_version;
                u16 minor_version;
                u32 type;
                u32 size_of_raw_data;
                u32 address_of_raw_data;
                u32 pointer_to_raw_data;
            } image_debug_directory = {0};
            
            guest_read_size(context, &image_debug_directory, guest_image_base + debug_offset, sizeof(image_debug_directory), PERMISSION_none);
            
            //
            // Find the CODEVIEW debug entry.
            if(image_debug_directory.type != /*IMAGE_DEBUG_TYPE_CODEVIEW*/2) continue;
            
            //
            // Read the RSDS debug entry.
            if(image_debug_directory.size_of_raw_data >= sizeof(rsds)){
                print("RSDS debug directory is larger than expected. Truncating it...\n");
                image_debug_directory.size_of_raw_data = sizeof(rsds)-1;
            }
            
            guest_read_size(context, &rsds, guest_image_base + image_debug_directory.address_of_raw_data, image_debug_directory.size_of_raw_data, PERMISSION_none);
            
            // Ensure zero-termination:
            rsds.pdb_name[image_debug_directory.size_of_raw_data] = 0;
            
            found_rsds = 1;
            
            //
            // If we got here, we found the _RSDS, thus break!
            //
            break;
        }
        
        context->registers.cr3 = user_cr3;
        
        int should_return = (context->crash != CRASH_none);
        
        exit_debugging_routine(context, crash_information); 
        
        // We crashes somewhere on the way here, this means we are not yet ready to try to load the pdb.
        if(should_return) return;
    }
    
    // 
    // From this point forward, we don't have to look at memory anymore, hence we can exit the debugging block.
    // 
    
    if(!found_rsds){
        // 
        // If we did not crash (which we checked above) and there is no 'RSDS' debug section,
        // then we cannot load the .PDB for this module (as it probably does not exist).
        // 
        atomic_load(u32, module->tried_to_load_pdb) = 1;
        return;
    }
    
    {
        u32 initial_value = atomic_compare_exchange((volatile long32 *)&module->load_in_progress, 1, 0);
        if(initial_value != 0){
            //
            // We are not the thread which loads the PDB. Wait for the other thread to finish!
            //
            while(atomic_load(u32, module->tried_to_load_pdb) != 1) _mm_pause();
            return;
        }
    }
    
    struct string pdb_name = {.data = rsds.pdb_name, .size = strlen(rsds.pdb_name) };
    
    if(!module->short_name.size){
        // 
        // If we don't have a name for this module (this happens for the 'load_module' debugger command)
        // patch up the name based of the 'pdb_name'.
        // 
        
        struct string short_name = string_strip_file_path(string_strip_file_extension(pdb_name));
        
        short_name.data = memcpy(malloc(short_name.size + 1), short_name.data, short_name.size);
        short_name.data[short_name.size] = 0;
        
        if(string_match(short_name, string("ntkrnlmp"))){
            short_name = string("nt");
        }
        
        module->short_name = short_name;
    }
    
    struct file pdb = {0};
    
    if(pdb_name.size > 2 && pdb_name.data[1] == ':'){
        // 
        // Absolute path, attempt to load it from the users computer.
        // If that fails, try to load it from the symbol server, using only the file name of the 'pdb_name'.
        // 
        pdb = load_file(pdb_name.data); // Don't print anything on failiure, we will try to download it.
        pdb_name = string_strip_file_path(pdb_name);
    }
    
    if(!pdb.memory){
        
        char guid[0x100];
        snprintf(guid, sizeof(guid), "%.8X%.4X%.4X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%d", PRINT_GUID_MEMBERS(rsds.pdb_guid), rsds.pdb_age);
        
        char pdb_file_path[0x100];
        // 
        // Generate the file path.
        // 
        snprintf(pdb_file_path, sizeof(pdb_file_path), "symbols/%s/%s/%s", pdb_name.data, guid, pdb_name.data);
        
        pdb = load_file(pdb_file_path);
        if(!pdb.memory){
            {
                // 
                // Make sure the path to the 'pdb_file_name' exists.
                // 
                
                char buffer[0x100];
                snprintf(buffer, sizeof(buffer), "symbols/%s", pdb_name.data);
                mkdir(buffer); // @note: ignore errors, it might already exist
                
                snprintf(buffer, sizeof(buffer), "symbols/%s/%s", pdb_name.data, guid);
                mkdir(buffer); // @note: ignore errors, it might already exist
            }
            
            // 
            // Attempt to download the file from the microsoft public symbol server.
            // 
            char url[0x100];
            snprintf(url, sizeof(url), "https://msdl.microsoft.com/download/%s", pdb_file_path);
            
            print("Could not load '%s'. Trying to download from %s.\n", pdb_file_path, url);
            
            int download_file_success = download_file(pdb_file_path, url);
            
            if(download_file_success){
                pdb = load_file(pdb_file_path);
                if(!pdb.memory) print("Error: Somehow we downloaded the file but then we could not open them.\n");
            }
        }
    }
    
    if(pdb.memory){
        module->pdb_context = load_pdb(pdb);
        
        if(!module->pdb_context){
            print("\nWARNING: PDB for '%.*s' is present, but we failed to load it.\n", pdb_name.size, pdb_name.data);
            print("         This can happen because of a CTRL-C while downloading,\n");
            print("         or because of a bug in the PDB parser.\n");
        }
    }
    
    //
    // Mark the attempt of loading the PDB as done.
    //
    atomic_load(u32, module->tried_to_load_pdb) = 1;
    
    return;
}

struct unwind_info{
    u8 version : 3;
    u8 flags   : 5;
    u8 size_of_prolog;
    u8 count_of_unwind_codes;
    u8 frame_register: 4;
    u8 frame_register_offset : 4;
};

struct runtime_function{
    u32 start_rva;
    u32 end_rva;
    u32 unwind_info_rva;
};

struct unwind_code{
    u8 offset_in_prolog;
    u8 operation_code : 4;
    u8 operation_info : 4;
};

void loaded_module_try_to_load_unwind_information(struct context *context, struct loaded_module *module){
    
    if(!module->tried_to_load_pdb) loaded_module_try_to_load_pdb(context, module);
    
    if(module->pdb_context && module->pdb_context->have_unwind_information){
        struct pdb_context *pdb_context = module->pdb_context;
        
        struct pdb_stream pdata_stream = pdb_context->streams[pdb_context->pdata_dump_stream_index];
        struct pdb_stream xdata_stream = pdb_context->streams[pdb_context->xdata_dump_stream_index];
        
        // @note: We checked while parsing the .pdb, that these headers fit in the stream.
        struct dump_stream_section_header{
            u32 version;
            u32 header_size;
            u32 data_size;
            u32 data_rva;
            u64 vaImage; // @note: I am not sure what this value is, it always seems to be '0x1C0000000'.
            u32 reserved[2];
        } *xdata_header = (void *)xdata_stream.base, *pdata_header = (void *)pdata_stream.base;
        
        module->pdata.rva  = pdata_header->data_rva;
        module->pdata.size = pdata_header->data_size;
        module->pdata.base = pdata_stream.base + pdata_header->header_size;
        
        module->xdata.rva  = xdata_header->data_rva;
        module->xdata.size = xdata_header->data_size;
        module->xdata.base = xdata_stream.base + xdata_header->header_size;
        
        module->have_unwind_information = 1;
        return;
    }
    
    // Treat this as a 'debugging_routine' so we can use 'context->crash' to detect if we were successful.
    struct crash_information crash_information = enter_debugging_routine(context);
    
    // 
    // Load the .pdata section from memory:
    //    1) If we dont know the rva / size yet, try to load it from the exception_data directory.
    //    2) If we have not copied the data yet, walk the pages to see if they are all present.
    //    
    
    u64 guest_image_base = module->guest_image_base;
    u64 image_size       = module->size_of_image;
    
    if(module->pdata.rva == 0){
        
        // "At location 0x3c, the stub has the file offset to the PE signature."
        u32 pe_header_offset = guest_read(u32, guest_image_base + 0x3c);
        
        u32 pe_signature = guest_read(u32, guest_image_base + pe_header_offset);
        if(pe_signature != 'EP'){ 
            // @note: This can happen if the header is paged out.
            exit_debugging_routine(context, crash_information);
            return; 
        }
        
        pe_header_offset += 4;
        u16 optional_header_size = guest_read(u16, guest_image_base + pe_header_offset + 16);
        if(!optional_header_size){
            // @note: This can happen if the header is paged out.
            exit_debugging_routine(context, crash_information);
            return;
        }
        
        u32 optional_header_offset = pe_header_offset + 20;
        u32 directory_base = optional_header_offset + 112;
        
        u32 exception_data_base = guest_read(u32, guest_image_base + directory_base + 3 * 8);
        u32 exception_data_size = guest_read(u32, guest_image_base + directory_base + 3 * 8 + 4);
        
        if(context->crash){
            // We crashed somewhere above. Don't set any values and just return.
            exit_debugging_routine(context, crash_information);
            return;
        }
        
        module->pdata.rva  = exception_data_base;
        module->pdata.size = exception_data_size;
    }
    
    if(!module->pdata.base){
        
        u64 pdata_base = guest_image_base + module->pdata.rva;
        u32 pdata_size = module->pdata.size;
        
        for(u64 page = pdata_base & ~0xfff; page < pdata_base + pdata_size; page += 0x1000){
            if(!translate_address(context, page, PERMISSION_none)){
                // 
                // A page of the runtime functions is not paged in.
                // 
                exit_debugging_routine(context, crash_information);
                return;
            }
        }
        
        // 
        // We know the .pdata section is completely paged in. Copy into memory.
        // 
        u8 *pdata = push_data(&context->permanent_arena, u8, pdata_size);
        int read_pdata_success = guest_read_size(context, pdata, pdata_base, pdata_size, PERMISSION_none);
        assert(read_pdata_success); // This should always succeed, we made sure of this in the loop above.
        
        module->pdata.base = pdata;
    }
    
    // 
    // Load the .xdata section from memory:
    //    1) Locate the approximate bounds of the xdata section by iterating the .pdata section
    //    2) Try to load the base by again iterating all the pages.
    // 
    
    if(!module->xdata.rva){
        u32 amount_of_runtime_functions = module->pdata.size / sizeof(struct runtime_function);
        struct runtime_function *runtime_function_base = (void *)module->pdata.base;
        
        u32 unwind_info_min = 0xffffffff;
        u32 unwind_info_max = 0;
        
        for(u32 runtime_function_index = 0; runtime_function_index < amount_of_runtime_functions; runtime_function_index++){
            struct runtime_function function = runtime_function_base[runtime_function_index];
            
            u32 min = function.unwind_info_rva;
            u32 max = function.unwind_info_rva + sizeof(struct unwind_info) + /*count of unwind codes*/0x100 * sizeof(u16);
            
            unwind_info_min = (min < unwind_info_min) ? min : unwind_info_min;
            unwind_info_max = (max > unwind_info_max) ? max : unwind_info_max;
        }
        
        if(unwind_info_max > image_size) unwind_info_max = (u32)image_size;
        if((unwind_info_min > image_size) || (unwind_info_min > unwind_info_max)){
            exit_debugging_routine(context, crash_information);
            return;
        }
        
        module->xdata.rva  = unwind_info_min;
        module->xdata.size = unwind_info_max - unwind_info_min;
    }
    
    if(!module->xdata.base){ // @note: We should always take this case other wise, why did we enter this function?
        
        u64 xdata_base = guest_image_base + module->xdata.rva;
        u32 xdata_size = module->xdata.size;
        
        for(u64 page = xdata_base & ~0xfff; page < xdata_base + xdata_size; page += 0x1000){
            if(!translate_address(context, page, PERMISSION_none)){
                // 
                // A page of the .xdata section is not paged in.
                // 
                exit_debugging_routine(context, crash_information);
                return;
            }
        }
        
        // 
        // We know the .xdata section is completely paged in. Copy into memory.
        // 
        u8 *xdata = push_data(&context->permanent_arena, u8, xdata_size);
        int read_xdata_success = guest_read_size(context, xdata, xdata_base, xdata_size, PERMISSION_none);
        assert(read_xdata_success); // This should always succeed, we made sure of this in the loop above.
        
        module->xdata.base = xdata;
    }
    
    // Everything succeeded, report that we have unwind information.
    module->have_unwind_information = 1;
    exit_debugging_routine(context, crash_information);
}

struct unwind_info *loaded_module_get_unwind_info_for_rva(struct loaded_module *module, u32 rva){
    if(module->xdata.rva <= rva && rva < module->xdata.rva + module->xdata.size){
        return (void *)(module->xdata.base + (rva - module->xdata.rva));
    }else{
        return null;
    }
}

void loaded_module_get_unwind_info(struct context *context, struct loaded_module *module, u64 address, struct unwind_info **out_unwind_info, struct runtime_function **out_runtime_function){
    
    if(!module->have_unwind_information){
        loaded_module_try_to_load_unwind_information(context, module);
        
        if(!module->have_unwind_information) return;
    }
    
    u32 relative_virtual_address = (u32)(address - module->guest_image_base);
    
    struct runtime_function *runtime_function_base = (void *)module->pdata.base;
    u32 amount_of_runtime_functions = module->pdata.size / sizeof(struct runtime_function);
    
    struct unwind_info      *unwind_info   = null;
    struct runtime_function *function_info = null;
    
    function_info = runtime_function_base;
    
    s64 min = 0;
    s64 max = amount_of_runtime_functions - 1;
    
    while(max - min >= 0){
        s64 at = (min + max) / 2;
        if(function_info[at].start_rva <= relative_virtual_address && relative_virtual_address < function_info[at].end_rva){
            
            unwind_info = loaded_module_get_unwind_info_for_rva(module, function_info[at].unwind_info_rva);
            
            function_info += at;
            break;
        }else if(function_info[at].start_rva > relative_virtual_address){
            max = at - 1;
        }else if(function_info[at].end_rva <= relative_virtual_address){
            min = at + 1;
        }
    }
    
    if(out_unwind_info)      *out_unwind_info      = unwind_info;
    if(out_runtime_function) *out_runtime_function = function_info;
}

struct loaded_module *parse_loaded_module(struct context *context, u64 guest_image_base, u64 image_size, struct string file_path){
    
    struct string import_name = string_strip_file_path(file_path);
    
    struct string short_name = {0};
    
    if(string_match(import_name, string("ntoskrnl.exe"))){
        short_name = string("nt");
    }else{
        short_name = string_strip_file_extension(import_name);
    }
    
    struct loaded_module *module = null;
    
    // 
    // @note: The 'short_name' (or equivalently the 'file_path') can be zero-sized, 
    //        if we found this module with a stack-trace and don't know it yet.
    // 
    if(short_name.size){
        module = get_loaded_module(short_name);
    }
    
    if(module && (s64)module->guest_image_base < 0 && (s64)guest_image_base > 0){
        // We are a user-space module with the same name as a kernel-space module.
        // add a `u_` to the name and register it anew.
        
        u8 *new_data = push_data(&context->scratch_arena, u8, short_name.size + 2);
        new_data[0] = 'u';
        new_data[1] = '_';
        memcpy(new_data + 2, short_name.data, short_name.size);
        
        short_name.data = (char *)new_data;
        short_name.size += 2;
        
        module = get_loaded_module(short_name);
    }
    
    if(module){
        // 
        // Still get the new bounds for the imagae.
        // 
        module->guest_image_base = guest_image_base;
        module->size_of_image    = image_size;
        return module;
    }
    
    module = malloc(sizeof(*module));
    module->guest_image_base = guest_image_base;
    module->size_of_image    = image_size;
    
    // 
    // Copy the short name.
    // 
    
    char *short_name_copy = malloc(short_name.size + 1);
    memcpy(short_name_copy, short_name.data, short_name.size);
    short_name_copy[short_name.size] = 0;
    
    short_name.data = short_name_copy;
    module->short_name = short_name;
    
    if(!short_name.size){
        loaded_module_try_to_load_pdb(context, module);
        if(!module->pdb_context) return null; // If we could not load the thing and we dont have a name, skip it. @cleanup: this is all terribly hacky... :(
    }
    
    // 
    // @cleanup: This would need to be atomic.
    // 
    
    if(globals.module_list.first){
        globals.module_list.last = globals.module_list.last->next = module;
    }else{
        globals.module_list.last = globals.module_list.first = module;
    }
    
    return module;
}

//_____________________________________________________________________________________________________________________
// Printing the symbol for a given address.

void print_symbol_from_loaded_module(struct context *context, struct loaded_module *module, u64 address, FILE *file){
    
    struct crash_information crash_information = enter_debugging_routine(context);
    
    if(!(module->guest_image_base <= address && address <= module->guest_image_base + module->size_of_image)){
        print("[print_symbol_from_loaded_module] internal error: tried to print address %p, with loaded_module '%.*s' but the address is not in range of %p to %p\n",
                address, module->short_name.size, module->short_name.data, module->guest_image_base, module->guest_image_base + module->size_of_image);
    }
    
    if(!module->tried_to_load_pdb) loaded_module_try_to_load_pdb(context, module);
    
    if(module->pdb_context){
        
        u64 offset_in_function;
        u32 function_rva;
        {        
            struct unwind_info      *unwind_info   = null;
            struct runtime_function *function_info = null;
            loaded_module_get_unwind_info(context, module, address, &unwind_info, &function_info);
            
            if(unwind_info && function_info){
                //
                // If we are not in a text section or do not have an unwind info (leaf function), just try the stuff below.
                //
                
                while(unwind_info->flags & /*UNW_FLAG_CHAININFO*/4){
                    u16 *unwind_code_base = (void *)(unwind_info + 1);
                    
                    u32 unwind_code_index = unwind_info->count_of_unwind_codes;
                    unwind_code_index += unwind_code_index & 1;
                    
                    function_info = (void *)(unwind_code_base + unwind_code_index);
                    unwind_info   = loaded_module_get_unwind_info_for_rva(module, function_info->unwind_info_rva);
                }
                
                offset_in_function = address - (function_info->start_rva + module->guest_image_base);
                function_rva = function_info->start_rva;
            }else{
                offset_in_function = 0;
                function_rva = (u32)(address - module->guest_image_base);
            }
        }
                    
        u32 symbol_offset = 0;
        struct string function_name = pdb_get_symbol_name(module->pdb_context, function_rva, &symbol_offset);
        
        if(function_name.data){
            
            offset_in_function += symbol_offset;
            
            if(function_name.data[0] == '?'){
                // 
                // C++ name.
                // Basic syntax seems to be '?function@class@otherclass@@XYZ'
                // for 'otherclass::class::function'.
                // 
                
                smm end_index = function_name.size;
                
                for(smm index = 1; index < function_name.size - 1; index++){
                    if(function_name.data[index] == '@' && function_name.data[index + 1] == '@'){
                        end_index = index;
                        break;
                    }
                }
                
                fprintf(file, "%s!", module->short_name.data);
                smm last_index = end_index;
                for(smm index = end_index-1; index >= 1; index--){
                    if(function_name.data[index] == '@'){
                        fprintf(file, "%.*s::", last_index - (index + 1), function_name.data + index + 1);
                        last_index = index;
                    }
                }
                fprintf(file, "%.*s + %llx", last_index - 1, function_name.data + 1, offset_in_function);
            }else{
                fprintf(file, "%s!%.*s + %llx", module->short_name.data, function_name.size, function_name.data, offset_in_function);
            }
            
            exit_debugging_routine(context, crash_information);
            return;
        }
        
        //
        // Punt because we could not find the 'function_name'.
        //
    }
    
    fprintf(file, "%s + %x", module->short_name.data, address - module->guest_image_base);
    exit_debugging_routine(context, crash_information);
}

void print_symbol(struct context *context, u64 address){
    struct loaded_module *module = get_module_for_address(address);
    
    if(!module){
        print("Unknown %p", address);
    }else{
        print_symbol_from_loaded_module(context, module, address, stdout);
        fflush(stdout);
    }
}


//_____________________________________________________________________________________________________________________
// Getting the address for a given symbol.

u64 get_export_symbol_from_module(struct context *context, struct loaded_module *module, struct string symbol){
    
    u64 export_symbol_address = 0;
    
    // @cleanup: Should we require zero-termination here instead?
    char zero_terminated_symbol[0x100];
    if(symbol.size > sizeof(zero_terminated_symbol)-1) return 0;
    memcpy(zero_terminated_symbol, symbol.data, symbol.size);
    zero_terminated_symbol[symbol.size] = 0;
    
    struct crash_information crash_information = enter_debugging_routine(context);
    
    u64 guest_image_base = module->guest_image_base;
    
    u32 pe_header_offset = guest_read(u32, guest_image_base + 0x3c);
    pe_header_offset += 4;
    
    u32 optional_header_offset = pe_header_offset + 20;
    u32 directory_base = optional_header_offset + 112;
    
    u32 export_offset = guest_read(u32, guest_image_base + directory_base + 0 * 8);
    
    struct{
        u32 export_flags;
        u32 time_date_stamp;
        u16 major_version;
        u16 minor_version;
        u32 name_rva;
        u32 ordinal_base;
        u32 address_table_entries;
        u32 number_of_name_pointers;
        u32 export_address_table_rva;
        u32 name_pointer_rva;
        u32 ordinal_table_rva;
    } export_directory_table = {0};
    guest_read_size(context, &export_directory_table, guest_image_base + export_offset, sizeof(export_directory_table), PERMISSION_none);
    
    if(export_directory_table.number_of_name_pointers){
        s64 min = 0;
        s64 max = (s64)export_directory_table.number_of_name_pointers-1;
        
        char name[0x100];
        
        s64 found = -1;
        
        while(min <= max){
            u64 mid = (max - min)/2 + min;
            
            u32 name_rva = guest_read(u32, guest_image_base + export_directory_table.name_pointer_rva + mid * sizeof(u32));
            
            // Uff, read a zero-terminated string.
            for(u32 index = 0; index < sizeof(name); index++){
                char c = guest_read(char, guest_image_base + name_rva + index);
                name[index] = c;
                if(c == 0) break;
            }
            name[sizeof(name)-1] = 0; // ensure zero-termination.
            
            int differance = strcmp(name, zero_terminated_symbol);
            if(differance == 0){
                found = mid;
                break;
            }else if(differance < 0){
                min = mid + 1;
            }else{
                max = mid - 1;
            }
        }
        
        if(found != -1){
            // According to the PE-Documentation:
            //     i = Search_ExportNamePointerTable (name);
            //     ordinal = ExportOrdinalTable [i];
            //     rva = ExportAddressTable [ordinal];
            
            u16 ordinal = guest_read(u16, guest_image_base + export_directory_table.ordinal_table_rva + found * sizeof(u16));
            u32 rva     = guest_read(u32, guest_image_base + export_directory_table.export_address_table_rva + ordinal * sizeof(u32));
            export_symbol_address = guest_image_base + rva;
        }
    }
    
    exit_debugging_routine(context, crash_information);
    
    return export_symbol_address;
}

u64 get_symbol_from_module(struct context *context, struct loaded_module *module, struct string symbol){
    
    if(!module->tried_to_load_pdb) loaded_module_try_to_load_pdb(context, module);
    if(!module->pdb_context){
        // If we have no pdb, fall-back on trying to lookup an export.
        return get_export_symbol_from_module(context, module, symbol);
    }
    
    u32 amount_of_dividers = 0;
    for(smm index = 0; index < symbol.size-1; index++){
        if(symbol.data[index] == ':' && symbol.data[index+1] == ':'){
            index++;
            amount_of_dividers += 1;
        }
    }
    
    // @note: Save and restore the current pointer of the scratch arena,
    //        in case we have to allocate the C++ symbol below.
    u8 *saved_current = context->scratch_arena.current;
    
    if(amount_of_dividers){
        // 
        // Map otherclass::class::function to ?function@class@otherclass.
        // 
        
        char *data = push_data(&context->permanent_arena, char, symbol.size - amount_of_dividers + 1);
        data[0] = '?';
        smm data_at = 1;
        
        smm last_terminator = symbol.size;
        for(smm index = symbol.size-1; index >= -1; index--){
            if(index == -1 || symbol.data[index] == ':' && symbol.data[index-1] == ':'){
                
                struct string class = {.data = symbol.data + (index + 1), .size = last_terminator - (index + 1)};
                
                memcpy(data + data_at, class.data, class.size);
                
                data_at += class.size;
                
                if(index != -1) data[data_at++] = '@';
                
                index--;
                
                last_terminator = index;
            }
        }
        
        assert(data_at == (symbol.size - amount_of_dividers) + 1);
        
        symbol = (struct string){.data = data, .size = data_at};
    }
    
    
    u64 rva = pdb_get_rva_for_symbol(module->pdb_context, symbol);
    
    context->scratch_arena.current = saved_current;
    
    if(rva == (u64)-1) return 0; // @cleanup: How to handle something like kernel32 where there are a bunch of exports that have no debug symbols as they are also imports?
    
    return module->guest_image_base + rva;
}

u64 get_constant_from_module(struct context *context, struct loaded_module *module, struct string symbol, int *error){
    
    if(!module->tried_to_load_pdb) loaded_module_try_to_load_pdb(context, module);
    if(!module->pdb_context){
        *error = 1;
        return 0;
    }
    
    return pdb_get_constant_for_symbol(module->pdb_context, symbol, error);
}

struct string get_module_name_from_symbol_string(struct string symbol){
    struct string module_name = {0};
    
    for(u32 i = 0; i < symbol.size; i++){
        if(symbol.data[i] == '!'){
            module_name.size = i;
            module_name.data = symbol.data;
            symbol.data += i + 1;
            symbol.size -= i + 1;
            break;
        }
    }
    
    return module_name;
}

u64 get_symbol(struct context *context, struct string symbol){
    struct string module_name = get_module_name_from_symbol_string(symbol);
    
    if(!module_name.size){
        struct loaded_module *module = get_loaded_module(symbol);
        if(module) return module->guest_image_base;
        
        print("[get_symbol] Could not find 'module_name' for '%.*s', please use a fully qualified name like 'nt!NtDeviceIoControlFile' instead of just 'NtDeviceIoControlFile'\n", symbol.size, symbol.data);
        return 0;
    }
    
    if(module_name.data){
        symbol.data += module_name.size + 1;
        symbol.size -= module_name.size + 1;
    }
    
    struct loaded_module *module = get_loaded_module(module_name);
    if(!module) return 0;
    
    return get_symbol_from_module(context, module, symbol);
}

u64 get_member_offset(struct context *context, struct string symbol){
    struct string original = symbol;
    
    struct string module_name = get_module_name_from_symbol_string(symbol);
    
    if(!module_name.size){
        print("[get_member_offset] Could not find 'module_name' for '%.*s', please use a fully qualified name like 'nt!_IRP.AssociatedIrp.SystemBuffer' instead of just 'IRP.AssociatedIrp.SystemBuffer'\n", symbol.size, symbol.data);
        return 0;
    }
    
    if(module_name.data){
        symbol.data += module_name.size + 1;
        symbol.size -= module_name.size + 1;
    }
    
    struct loaded_module *module = get_loaded_module(module_name);
    if(!module){
        print("[get_member_offset] Could not find module '%.*s' for type string '%.*s'.\n", module_name.size, module_name.data, original.size, original.data);
        return 0;
    }
    
    
    if(!module->tried_to_load_pdb) loaded_module_try_to_load_pdb(context, module);
    if(!module->pdb_context){
        print("[get_member_offset] Module '%.*s' has no pdb, but symbol '%.*s' is needed.\n", module_name.size, module_name.data, original.size, original.data);
        return 0;
    }
    
    struct string type_name = symbol;
    
    struct string member_string = {0};
    for(smm index = 0; index < type_name.size; index++){
        if(type_name.data[index] == '.'){
            member_string.size = type_name.size - index;
            member_string.data = type_name.data + index;
            
            type_name.size = index;
            break;
        }
    }
    
    int error = 0; // @cleanup: propergate this?
    return pdb_get_member_offset(module->pdb_context, type_name, member_string, &error);
}

//_____________________________________________________________________________________________________________________
// Finding and loading modules.

struct string guest_read_unicode_string(struct context *context, struct memory_arena *arena, u64 address){
    
    struct unicode_string unicode_string = {0};
    struct string ret = {0};
    
    int unicode_string_read_success = guest_read_size(context, &unicode_string, address, sizeof(unicode_string), PERMISSION_none);
    if(!unicode_string_read_success) return ret;
    if(!unicode_string.length) return ret;
    
    // @note: We leak 50% of the memory here, but whatever.
    u8 *buffer = push_data(arena, u8, unicode_string.length);
    
    int buffer_read_success = guest_read_size(context, buffer, unicode_string.buffer, unicode_string.length, PERMISSION_none);
    if(!buffer_read_success) return ret;
    
    u32 length = (unicode_string.length / 2);
    for(u32 i = 0; i < length; i++){
        buffer[i] = (u8)((u16 *)buffer)[i];
    }
    buffer[length] = 0;
    
    ret.data = (char *)buffer;
    ret.size = length;
    return ret;
}

void load_modules_from_list(struct context *context, u64 PsLoadedModuleList){
    
    struct crash_information crash_information = enter_debugging_routine(context);
    
    for(u64 entry_guest_address = guest_read(u64, PsLoadedModuleList); !context->crash && entry_guest_address && entry_guest_address != PsLoadedModuleList;){
        
        struct _KLDR_DATA_TABLE_ENTRY{
            u64 Flink;
            u64 Blink;
            u64 ExceptionTable;
            u64 ExceptionTableSize;
            u64 GpValue;
            u64 NonPagedDebugInfo;
            u64 DllBase;
            u64 EntryPoint;
            u64 SizeOfImage;
            struct unicode_string FullDllName;
            struct unicode_string BaseDllName;
            u32 Flags;
            u16 LoadCount;
            u16 _some_union;
            u64 SectionPointer;
            u32 CheckSum;
            u32 CoverageSectionSize;
            u64 CoverageSection;
            u64 LoadedImports;
            u64 Spare;
            u32 SizeOfImageNotRounded;
            u32 TimeDateStamp;
        } table_entry;
        
        int success = guest_read_size(context, &table_entry, entry_guest_address, sizeof(table_entry), PERMISSION_none);
        if(!success) continue;
        
        // @cleanup: FullDllName vs BaseDllName
        u64 base_dll_name_address = entry_guest_address + /*get_member_offset(string("nt!_LDR_DATA_TABLE_ENTRY.BaseDllName"))*/ 11 * 8;
        
        struct string BaseDllName = guest_read_unicode_string(context, &context->scratch_arena, base_dll_name_address);
        
        parse_loaded_module(context, table_entry.DllBase, table_entry.SizeOfImage, BaseDllName);
        
        entry_guest_address = table_entry.Flink;
    }
    
    exit_debugging_routine(context, crash_information);
}

struct loaded_module *maybe_find_and_load_ntoskrnl(struct context *context){
    
    struct loaded_module *nt = get_loaded_module(string("nt"));
    if(nt) return nt;
    
    struct crash_information crash_information = enter_debugging_routine(context);
    
    {
        
        u64 address = context->registers.vtl_state.current_vtl ? context->registers.vtl_state.ia32_lstar : context->registers.ia32_lstar;
        
        u64 cr3 = patch_in_cr3_for_virtual_address(context, address, /*print cr3*/false);
        
        // @note: For some reason (at least) the header of some intel driver is at offset 169000
        //        from the kernel. We could maybe check some other stuff, to eliminate these false 
        //        postives, but luckily for us, because the kernel uses large pages, it is 0x200000
        //        aligned. So we can have this bigger step.
        u64 step = 0x200000;
        
        address &= ~(step - 1);
        
        for(; !context->crash; address -= step){
            if(guest_read(u16, address) == 'ZM'){
                u32 pe_header_offset = guest_read(u32, address + 0x3c);
                u32 image_size       = guest_read(u32, address + pe_header_offset + 4 + 20 + 56);
                
                nt = parse_loaded_module(context, address, image_size, string("nt"));
                if(nt) break;
            }
        }
        
        context->registers.cr3 = cr3;
    }
    
    exit_debugging_routine(context, crash_information);
    
    return nt;
}


struct loaded_module *maybe_find_nt_and_load_module_list(struct context *context){
    
    struct crash_information crash_information = enter_debugging_routine(context);
    
    struct loaded_module *nt = maybe_find_and_load_ntoskrnl(context);
    if(nt){
        // 
        // Load the kernel module list in 'PsLoadedModuleList'.
        // 
        
        u64 PsLoadedModuleList = get_symbol_from_module(context, nt, string("PsLoadedModuleList"));
        u64 cr3 = patch_in_cr3_for_virtual_address(context, PsLoadedModuleList, /*print cr3*/false);
        
        load_modules_from_list(context, PsLoadedModuleList);
        
        // 
        // Load the user module list by checking the '_PEB'.
        // 
        
        u64 TIB = (context->registers.cs.selector & 3) ? context->registers.gs_base : context->registers.gs_swap;
        u64 PEB = guest_read(u64, TIB + get_member_offset(context, string("nt!_TEB.ProcessEnvironmentBlock")));
        u64 Ldr = guest_read(u64, PEB + get_member_offset(context, string("nt!_PEB.Ldr")));
        
        u64 InMemoryOrderModuleList = guest_read(u64, Ldr + get_member_offset(context, string("nt!_PEB_LDR_DATA.InMemoryOrderModuleList")));
        
        u64 DataTableEntryLink = InMemoryOrderModuleList;
        do{
            u64 DataTableEntry = DataTableEntryLink - get_member_offset(context, string("nt!_LDR_DATA_TABLE_ENTRY.InMemoryOrderLinks"));
            
            u64 DllBase = guest_read(u64, DataTableEntry + get_member_offset(context, string("nt!_LDR_DATA_TABLE_ENTRY.DllBase")));
            u32 DllSize = guest_read(u32, DataTableEntry + get_member_offset(context, string("nt!_LDR_DATA_TABLE_ENTRY.SizeOfImage")));
            
            if(DllBase){
                struct string BaseDllName = guest_read_unicode_string(context, &context->scratch_arena, DataTableEntry + get_member_offset(context, string("nt!_LDR_DATA_TABLE_ENTRY.FullDllName")));
                
                parse_loaded_module(context, DllBase, DllSize, BaseDllName);
            }
            
            DataTableEntryLink = guest_read(u64, DataTableEntryLink);
        }while(!context->crash && (DataTableEntryLink != InMemoryOrderModuleList) && DataTableEntryLink);
        
        context->registers.cr3 = cr3;
        context->crash = CRASH_none;
    }
    
    struct loaded_module *securekernel = get_loaded_module(string("securekernel"));
    if(!securekernel){
        
        u64 address = context->registers.vtl_state.current_vtl ? context->registers.ia32_lstar : context->registers.vtl_state.ia32_lstar;
        
        u64 cr3 = patch_in_cr3_for_virtual_address(context, address, /*print cr3*/false);
        
        address &= ~0xfff;
        
        for(; !context->crash; address -= 0x1000){
            if(guest_read(u16, address) == 'ZM'){
                u32 pe_header_offset = guest_read(u32, address + 0x3c);
                u32 image_size       = guest_read(u32, address + pe_header_offset + 4 + 20 + 56);
                
                struct string name = string("securekernel");
                
                securekernel = parse_loaded_module(context, address, image_size, name);
                break;
            }
        }
        
        if(securekernel){
            // @cleanup: This will probably nuke where Cng.sys is... but whatever?
            u64 SkLoadedModuleList = get_symbol_from_module(context, securekernel, string("SkLoadedModuleList"));
            load_modules_from_list(context, SkLoadedModuleList);
        }
        
        context->registers.cr3 = cr3;
    }
    
    exit_debugging_routine(context, crash_information);
    
    return nt;
}


//_____________________________________________________________________________________________________________________
// Unwinding the stack

void unwind_one_function(struct context *context, struct loaded_module *module, struct registers *registers, int print_machframe_info){
    
    struct unwind_info      *unwind_info   = NULL;
    struct runtime_function *function_info = NULL;
    
    if(module) loaded_module_get_unwind_info(context, module, registers->rip, &unwind_info, &function_info);
    
    if(!unwind_info || !function_info){
        // 
        // We don't have unwind information, let's do it hacker style 8^)
        // Search the stack for an address which looks like it is right after a call.
        // 
        
        s64 rsp_limit = registers->rsp + 1ull * 1024 * 1024; // Make sure we never search through more than one mib of stack.
        
        for(registers->rsp &= ~7; registers->rsp < rsp_limit; registers->rsp += 8){
            
            // If the rsp is not readable anymore, we could not find anything.
            if(!translate_address(context, registers->rsp, PERMISSION_read)) break;
            
            // This read should always succeed because of alignment.
            u64 address = guest_read(u64, registers->rsp);
            if(!translate_address(context, address, PERMISSION_execute)) continue;
            
            u8 instruction_buffer[8];
            u32 amount_of_bytes = 0;
            
            // Begin at the first byte before the potential return-address.
            address -= 1;
            while(amount_of_bytes < array_count(instruction_buffer)){
                u8 *translated = translate_address(context, address, PERMISSION_execute);
                if(!translated) break;
                
                instruction_buffer[amount_of_bytes++] = *translated;
                address -= 1;
            }
            
            // Possible call instructions:    Instruction Bytes in reverse order:
            //     call rel32               | XX XX XX XX e8 
            //     call reg                 | d0 ff
            //     call [reg]               | 10 ff
            //     call [reg + reg]         | 10 14 ff 
            //     call [reg + off8]        | XX 50 ff
            //     call [reg + reg]         | 10 14 ff
            //     call [reg + reg + off8]  | XX 10 54 ff
            //     call [reg + off32]       | XX XX XX 90 ff
            //     call [rip + off32]       | XX XX XX XX 15 ff
            //     call [reg + reg + off32] | XX XX XX XX 10 94 ff
            
            int found = 0;
            if(amount_of_bytes >= 5 && instruction_buffer[4] == 0xe8){
                found = 1;
            }else{
                
                u8 decode_buffer[0x20] = {0};
                for(u32 index = 0; index < amount_of_bytes; index++){
                    decode_buffer[index] = instruction_buffer[(amount_of_bytes - 1) - index];
                }
                
                for(u32 index = 1; index < amount_of_bytes; index++){
                    if(instruction_buffer[index] != 0xff) continue;
                    
                    u32 decode_index = (amount_of_bytes - 1) - index;
                    
                    struct instruction_information decoded_instruction = decode_instruction(decode_buffer + decode_index);
                    assert(decoded_instruction.augmented_opcode == 0xff);
                    if(decoded_instruction.reg == /*call*/2 && decoded_instruction.instruction_size == index + 1){
                        found = 1;
                        break;
                    }
                }
            }
            
            if(found){
                registers->rip = guest_read(u64, registers->rsp);
                registers->rsp += 8;
                return;
            }
        }
        
        // 
        // We have not found anything.
        // Set a 'crash' to signal the outside code to stop iterating.
        // 
        set_crash_information(context, CRASH_internal_error, (u64)"Could not unwind_one_function, because we don't have unwind information and it has more than 1MiB of stack.");
        
        return;
    }
    
    while(unwind_info){
        u32 unwind_code_index = 0;
        u16 *unwind_code_base = (void *)(unwind_info + 1);
        
        // @cleanup: Check if we are in an epilog.
        u64 offset_in_function = registers->rip - (function_info->start_rva + module->guest_image_base);
        
        for(; unwind_code_index < unwind_info->count_of_unwind_codes; unwind_code_index++){
            
            struct unwind_code{
                u8 offset_in_prolog;
                u8 operation_code : 4;
                u8 operation_info : 4;
            } *unwind_code = (void *)(unwind_code_base + unwind_code_index);
            
            // The codes are sorted in descending order.
            if((unwind_code->offset_in_prolog >= offset_in_function) && !(offset_in_function == 0 && unwind_code->operation_code == /*UWOP_PUSH_MACHFRAME*/10)){
                // @note: We still need to consume everything if its a multi-code situation.
                switch(unwind_code->operation_code + 0){
                    case 1:{
                        if(unwind_code->operation_info == 0){
                            unwind_code_index++;
                        }else{
                            crash_assert(unwind_code->operation_info == 1);
                            unwind_code_index += 2;
                        }
                    } break;
                    case 4: case 8: unwind_code_index++; break;
                }
                continue;
            }
            
            switch(unwind_code->operation_code){
                case 0:{ // UWOP_PUSH_NONVOL
                    registers->gpr[unwind_code->operation_info] = guest_read(u64, registers->rsp);
                    registers->rsp += 8;
                }break;
                case 1:{ // UWOP_ALLOC_LARGE
                    u64 allocation_size;
                    if(unwind_code->operation_info == 0){
                        unwind_code_index++;
                        allocation_size = unwind_code_base[unwind_code_index] * 8;
                    }else{
                        crash_assert(unwind_code->operation_info == 1);
                        unwind_code_index++;
                        allocation_size = *(u32 *)(unwind_code_base + unwind_code_index);
                        unwind_code_index++;
                    }
                    
                    registers->rsp += allocation_size;
                }break;
                
                case 2:{ // UWOP_ALLOC_SMALL
                    registers->rsp += unwind_code->operation_info * 8 + 8;
                }break;
                
                case 3:{ // UWOP_SET_FPREG
                    registers->rsp = registers->gpr[unwind_info->frame_register] - 0x10 * unwind_info->frame_register_offset;
                }break;
                
                case 4:{ // UWOP_SAVE_NON_VOL
                    unwind_code_index++;
                    
                    u32 reg          = unwind_code->operation_info;
                    u64 stack_offset = unwind_code_base[unwind_code_index] * 8;
                    
                    registers->gpr[reg] = guest_read(u64, registers->rsp + stack_offset);
                    if(reg == REGISTER_SP){
                        print("UWOP_SAVE_NON_VOL RSP\n");
                    }
                }break;
                
                case 6:{ // EPILOG
                }break;
                
                case 8:{ // UWOP_SAVE_XMM128
                    unwind_code_index++;
                }break;
                
                case 10:{ // UWOP_PUSH_MACHFRAME
                    
                    //
                    // Read rsp and rip and then jump skipping all the stuff below.
                    // This feels really hacky, but this is sort of a hacky/technical thing...
                    //
                    
                    // If the operation equals 1, there is a status on top of the stack, otherwise, there is not!
                    if(unwind_code->operation_info) registers->rsp += 8; // "pop" the error code!
                    
                    // fffffa8a`53300250  00000000`00000010 fffff803`5125abea status, rip
                    // fffffa8a`53300260  00000000`00000010 00000000`00050246 cs,     rflags
                    // fffffa8a`53300270  fffffa8a`53300280 00000000`00000018 rsp,    ss
                    
                    registers->rip = guest_read(u64, registers->rsp +  0x0);
                    registers->rsp = guest_read(u64, registers->rsp + 0x18);
                    
                    if(!translate_address(context, registers->rsp, PERMISSION_read)){
                        if(print_machframe_info) print("Did not understand exception frame.\n");
                    }else{
                        
                        if(!translate_address(context, registers->rip, PERMISSION_execute)){
                            //
                            // Assume this comes from a busted call.
                            //
                            registers->rip = guest_read(u64, registers->rsp);
                            registers->rsp += 8;
                            
                            if(translate_address(context, registers->rip, PERMISSION_execute)){
                                if(print_machframe_info) print("----- Invalid Call Exception Frame ----- \n");
                            }
                        }else{
                            if(print_machframe_info) print("-------- Exception Frame --------\n");
                        }
                    }
                    
                    return;
                }break;
                
                invalid_default_case();
            }
        } // for(unwind_code_index)
        
        // align it up
        unwind_code_index += unwind_code_index & 1;
        
        if(unwind_info->flags & 4){ // UNW_FLAG_CHAININFO
            function_info = (void *)(unwind_code_base + unwind_code_index);
            unwind_info   = loaded_module_get_unwind_info_for_rva(module, function_info->unwind_info_rva);
            
            // research this unwind info
            continue;
        }
        break;
    } // while(unwind_info)
    
    registers->rip = guest_read(u64, registers->rsp);
    registers->rsp += 8;
}

void print_stack_trace(struct context *context){
    
    struct crash_information crash_information = enter_debugging_routine(context);
    
    struct registers registers = context->registers;
    
    u64 cr3 = registers.cr3;
    
    for(int vtl = context->registers.vtl_state.current_vtl; vtl >= 0; vtl -= 1){ 
        
        for(u32 depth = 0; depth < 0x200 && !context->crash; depth++){
            
            struct loaded_module *module = get_module_for_address(registers.rip);
            
            print("%p %p: ", registers.rsp, registers.rip);
            
            if(module){
                print_symbol_from_loaded_module(context, module, registers.rip, stdout);
                print("\n");
            }else{
                print("???\n");
            }
            
            unwind_one_function(context, module, &registers, /*print_machframe_info*/true);
            
            if(!translate_address(context, registers.rip, PERMISSION_execute) || !registers.rip) break; // If the new Rip is not executable we are past the stack.
        }
        
        if(vtl != 0){
            context->crash = CRASH_none;
            registers.cr3 = context->registers.vtl_state.cr3;
            registers.rsp = context->registers.vtl_state.rsp;
            registers.rip = context->registers.vtl_state.rip;
            
            // Needed for memory reads, as they use registers->cr3 implicitly.
            context->registers.cr3 = registers.cr3;
            
            print("-------- VTL%d Transition --------\n", vtl);
        }
    }
    
    context->registers.cr3 = cr3;
    
    exit_debugging_routine(context, crash_information);
}

u64 calculate_stack_trace_hash(struct context *context){
    u64 hash = 0;
    
    struct crash_information crash_information = enter_debugging_routine(context);
    
    struct registers registers = context->registers;
    
    if(!translate_address(context, registers.rip, PERMISSION_execute)){
        //
        // For a call to some invalid memory address, we don't want the
        // initial rip to be contributing to the crash_hash.
        // Otherwise, it will register each new invalid memory address we
        // can pass in as a new crash.
        //
        registers.rip = guest_read(u64, registers.rsp);
        registers.rsp += 8;
    }
    
    for(u32 depth = 0; depth < 0x200 && !context->crash; depth++){
        
        struct loaded_module *module = get_module_for_address(registers.rip);
        
        xor_shift(&hash);
        hash ^= registers.rip;
        
        unwind_one_function(context, module, &registers, /*print_machframe_info*/false);
        
        if(!translate_address(context, registers.rip, PERMISSION_execute) || !registers.rip) break; // If the new Rip is not executable we are past the stack.
    }
    
    exit_debugging_routine(context, crash_information);
    
    return hash;
}

