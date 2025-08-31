// 
// This is the default "target-specific" code.
// If SNAFUzz is build without a `target.c`, i.e. simply using `build.bat`,
// this file is used as the target-specific code.
// 
// If you want to understand how to write target-specific code, 
// I would recommend first reading the `hevd.c` and `HeaderParser.c` target-files,
// as well as the `target_specific_code_api.h` documentation/header-file.
// 
// The only thing not covered by the `hevd.c` and `HeaderParser.c` examples,
// that is used in this file, is the `-double_fetch` stuff.
// For that stuff, see the :default_target_double_fetch_detection tag.
// 
//                                                  - Pascal Beyer 31.08.2025
// 


#define INPUT_SIZE 0x400

// 
// Input structure designed to call into 'NtDeviceIoControlFile'.
// 
struct input_metadata{
    u32 ioctl;
    u32 input_buffer_offset;
    u32 input_buffer_size;
    u32 output_buffer_offset;
    u32 output_buffer_size;
};

struct{
    u64 input_buffer;
    s64 input_size;
    
    u64 isob_buffer;
    u64 NtDeviceIoControlFile;
    u64 handle;
    
    u32 amount_of_known_ioctls;
    u32 *known_ioctls;
    
    int enable_double_fetch_detection;
} target_globals;

int is_kernel_mode = 0;

void target_initialize(struct context *context, int target_argc, char *target_argv[]){
    
    if(target_argc == 0){
        print("Default target usages:\n");
        print("    kernel_snapshot: <\\Device\\DeviceName> [-double_fetch] [ioctl...]\n");
        print("    user_snapshot: -buffer <input_buffer> -size <input_size> [-corpus <directory>] [-no_loop]\n");
        _exit(0);
    }
    
    // Assume its a kernel snapshot if we are at the correct rip.
    int is_kernel_snapshot = context->registers.rip == get_symbol(context, string("nt!NtSetInformationTransactionManager"));
    
    // Assume its a user snapshot, if the rip is in user space and the rip matches the dr0 (which is how the user_snapshot.exe works).
    int is_user_snapshot = ((s64)context->registers.rip > 0); // && context->registers.rip == context->registers.dr0;
    
    if(!is_kernel_snapshot && !is_user_snapshot){
        print("Error: The specified snapshot is invalid for the `default_target.c`.\n");
        print("       It can only handle snapshots created with `kernel_snapshot.c` or `user_snapshot.c`.\n");
        os_panic(1);
    }
    
    is_kernel_mode = is_kernel_snapshot;
    
    if(is_kernel_snapshot){
        
        // We expect the .DMP state to be at the start of 'nt!NtSetInformationTransactionManager'
        // With 
        //    rcx = Handle or ignored.
        //    rdx = One page of memory.
        //    r8  = One page of memory.
        //    r9  = One page of memory.
        
        target_globals.input_buffer = context->registers.rdx;
        target_globals.isob_buffer  = context->registers.r8;
        target_globals.NtDeviceIoControlFile = get_symbol(context, string("nt!NtDeviceIoControlFile"));
        
        if(target_argc == 0){
            print("Error: `default_taget.c` expected a device name.\n");
            os_panic(1);
        }
        
        char *device_string = target_argv[0];
        
        if(strcmp(device_string, "handle") == 0){
            target_globals.handle = context->registers.rcx;
            print("Handle is %p\n", target_globals.handle);
        }else{
            
            size_t device_string_length = strlen(device_string);
            if( 2 * (device_string_length + 1) > 0xffff){
                print("Error: Device string provided to default target is too long.\n");
                os_panic(1);
            }
            
            u16 *unicode_device_string = push_data(&context->permanent_arena, u16, device_string_length + 1);
#if _WIN32
            size_t unicode_device_string_length = mbstowcs(unicode_device_string, device_string, device_string_length);
#else
            size_t unicode_device_string_length = device_string_length;
            for(size_t index = 0; index < device_string_length; index++){
                unicode_device_string[index] = device_string[index];
            }
#endif
            if(unicode_device_string_length == (size_t)-1){
                print("Error: Failed to convert device string '%s' to utf16.\n", device_string);
                os_panic(1);
            }
            unicode_device_string[unicode_device_string_length] = 0;
            
            
            // 
            // Call nt!NtCreateFile to create a HANDLE for the device which we can then use during fuzzing.
            // 
            
            u64 input_buffer = target_globals.input_buffer;
            
            struct create_buffer{
                u64 handle;
                
                struct{
                    u32 length;
                    u64 root_directory;
                    u64 object_name;
                    u32 attributes;
                    u64 security_descriptor;
                    u64 security_quality_of_service;
                } object_attributes;
                
                struct{
                    u16 length;
                    u16 maximum_length;
                    u64 buffer;
                } unicode_string;
                
                struct{
                    u64 status;
                    u64 information;
                } io_status_block;
                
            } create_buffer = {
                .object_attributes = {
                    .length = sizeof(create_buffer.object_attributes),
                    .object_name = input_buffer + offset_in_type(struct create_buffer, unicode_string),
                    .attributes = 0x40,
                },
                
                .unicode_string = {
                    .length = (u16)(2 * unicode_device_string_length),
                    .maximum_length = (u16)(2 * unicode_device_string_length + 2),
                    .buffer = input_buffer + sizeof(create_buffer),
                },
            };
            
            // Write the 'create_buffer' into guest memory, where the guest can read it.
            int success = guest_write_size(context, &create_buffer, input_buffer, sizeof(create_buffer));
            success &= guest_write_size(context, unicode_device_string, input_buffer + sizeof(create_buffer), 2 * (unicode_device_string_length + 1));
            
            if(!success){
                print("Error: Default target failed to write to the input buffer during initialization.\n");
                os_panic(1);
            }
            
            // 
            // Set up the 'DEFAULT_RETURN_RIP'.
            // This is a special value we use to signal _successful execution_.
            // If the guest ever executes 'DEFAULT_RETURN_RIP' we will exit 
            // 'start_execution' with 'result.crash_type == CRASH_none'.
            // 
            guest_write(u64, context->registers.rsp, DEFAULT_RETURN_RIP); // return value
            
            //
            // Call into 'NtCreateFile'.
            // This is done by setting up the registers correctly and then calling 'start_execution'.
            //
            context->registers.rip = get_symbol(context, string("nt!NtCreateFile"));
            context->registers.rcx = target_globals.input_buffer + offset_in_type(struct create_buffer, handle);
            context->registers.rdx = /*GENERIC_READ*/0x80000000 | /*GENERIC_WRITE0x40000000 |*/ /*SYNCHRONIZE*/0x00100000 | 0x80;
            context->registers.r8  = target_globals.input_buffer + offset_in_type(struct create_buffer, object_attributes);
            context->registers.r9  = target_globals.input_buffer + offset_in_type(struct create_buffer, io_status_block);
            guest_write(u64, context->registers.rsp + 0x28, 0);    // AllocationSize = NULL
            guest_write(u64, context->registers.rsp + 0x30, 0x80); // FileAttributes = FILE_ATTRIBUTE_NORMAL
            guest_write(u64, context->registers.rsp + 0x38, 1);    // ShareAccess = 1
            guest_write(u64, context->registers.rsp + 0x40, 1);    // CreateDisposition = FILE_OPEN
            guest_write(u64, context->registers.rsp + 0x48, 0x60); // CreateOptions = FILE_SYNCHRONOUS_IO_NONALERT | FILE_NON_DIRECTORY_FILE
            guest_write(u64, context->registers.rsp + 0x50, 0);    // EaBuffer = NULL
            guest_write(u64, context->registers.rsp + 0x58, 0);    // EaLength = 0
            struct crash_information result = start_execution_jit(context);
            
            if(result.crash_type || (s32)context->registers.rax < 0){
                print_result_status(context, "NtCreateFile(%s)", device_string);
                os_panic(1);
            }
            
            // Read out the handle from the create buffer (we placed it at the start).
            target_globals.handle = guest_read(u64, input_buffer);
        }
        
        // "Remove" the handle / device name from the target arguments.
        target_argc -= 1;
        target_argv += 1;
        
        if((target_argc > 0) && strcmp(target_argv[0], "-double_fetch") == 0){
            // 
            // Enable double fetch detection. :default_target_double_fetch_detection
            // 
            target_globals.enable_double_fetch_detection = 1;
            u64 input_buffer_pte = 0;
            globals.input_buffer_physical_address = translate_page_number_to_physical(context, target_globals.input_buffer >> 12, PERMISSION_read, &input_buffer_pte);
            assert(input_buffer_pte & PAGE_TABLE_present); // The input buffer address must be present.
            
            target_argc -= 1;
            target_argv += 1;
        }
        
        // 
        // Parse the ioctl arguments.
        // 
        int amount_of_known_ioctls = target_argc;
        u32 *known_ioctls = push_data(&context->permanent_arena, u32, amount_of_known_ioctls);
        
        for(int argument_index = 0; argument_index < target_argc; argument_index++){
            known_ioctls[argument_index] = strtoul(target_argv[argument_index], null, 0);
        }
        
        target_globals.known_ioctls = known_ioctls;
        target_globals.amount_of_known_ioctls = amount_of_known_ioctls;
        
        // 
        // Provide an initial input.
        // 
        
        struct input initial_input = {
            .data = push_data(&context->permanent_arena, u8, INPUT_SIZE),
            .size = INPUT_SIZE,
        };
        
        struct input_metadata *input_metadata = (void *)initial_input.data;
        input_metadata->ioctl = amount_of_known_ioctls ? known_ioctls[0] : 0xe7c42c;
        input_metadata->input_buffer_offset  = sizeof(struct input_metadata);
        input_metadata->input_buffer_size    = 0x100;
        input_metadata->output_buffer_offset = sizeof(struct input_metadata) + 0x100;
        input_metadata->output_buffer_size   = 0x100;
        
        add_input(initial_input);
        
        // 
        // Add default hooks to track bugchecks and memory allocations.
        // 
        register_bugcheck_hooks(context);
        register_kernel_memory_allocation_hooks(context);
    }else{
        
        u64 input_buffer = 0;
        u64 input_size   = 0;
        
        for(int argument_index = 0; argument_index < target_argc; argument_index++){
            char *arg = target_argv[argument_index];
            
            if(strcmp(arg, "-buffer") == 0){
                char *buffer_cstring = target_argv[++argument_index];
                
                if(!buffer_cstring){
                    print("Error: Expected argument after '-buffer'.\n");
                    os_panic(1);
                }
                
                struct string buffer_string = {.data = buffer_cstring, .size = strlen(buffer_cstring) };
                int error = 0;
                
                input_buffer = parse_address(context, &buffer_string, &error);
                
                if(error){
                    print("Error: Unable to parse argument '%s' to '-buffer'.\n", buffer_cstring);
                    os_panic(1);
                }
                continue;
            }
            
            if(strcmp(arg, "-size") == 0){
                char *size_cstring = target_argv[++argument_index];
                
                if(!size_cstring){
                    print("Error: Expected argument after '-size'.\n");
                    os_panic(1);
                }
                
                struct string size_string = {.data = size_cstring, .size = strlen(size_cstring) };
                int error = 0;
                
                input_size = parse_address(context, &size_string, &error);
                
                if(error){
                    print("Error: Unable to parse argument '%s' to '-size'.\n", size_cstring);
                    os_panic(1);
                }
                continue;
            }
            
            
            if(strcmp(arg, "-corpus") == 0){
                
                char *corpus_directory = target_argv[++argument_index];
                
                if(!corpus_directory){
                    print("Error: Expected argument after '-corpus'.\n");
                    os_panic(1);
                }
                
                load_input_directory(corpus_directory);
                continue;
            }
            
            if(strcmp(arg, "-no_loop") == 0){
                FUZZ_CASES_BEFORE_RESET = 1;
                continue;
            }
            
            print("Error: `default_target.c` (user target) unhandled argument '%s'.\n", arg);
            os_panic(1);
        }
        
        if(!input_buffer){
            print("Error: `default_target.c` needs argument '-buffer'\n");
            os_panic(1);
        }
        
        if(!input_size){
            print("Error: `default_target.c` needs argument '-size'\n");
            os_panic(1);
        }
        
        target_globals.input_buffer = input_buffer;
        target_globals.input_size   = input_size;
        
        // 
        // Read the initial input from memory.
        // 
        struct input initial_input = {
            .data = push_data(&context->permanent_arena, u8, input_size),
            .size = input_size,
        };
        
        guest_read_size(context, initial_input.data, input_buffer, input_size, PERMISSION_read);
        
        add_input(initial_input);
        
        register_hook(context, get_symbol(context, string("ntdll!RtlUserThreadStart$filt$0")), Unhandled_user_exception_hook);
        
        register_user_memory_allocation_hooks(context);
    }
}

struct input target_get_input(struct context *context, u64 *seed){
    
    struct input input = get_random_input(&context->fuzz_run_arena, seed);
    
    // 
    // Just apply simple mutations to the buffer.
    // 
    apply_simple_mutations(input, target_globals.input_buffer, seed);
    
    if(is_kernel_mode){
        // 
        // If we have known ioctls, sometimes patch one in.
        // 
        if(target_globals.amount_of_known_ioctls && (xor_shift(seed) & 3) == 0){
            struct input_metadata *metadata = (void *)input.data;
            metadata->ioctl = target_globals.known_ioctls[xor_shift(seed) % target_globals.amount_of_known_ioctls];
        }
    }
    
    return input;
}


// :default_target_double_fetch_detection
// 
// If `target_globals.enable_double_fetch_detection` is enabled, instead of writing in the input into the `target_globals.input_buffer`,
// we register the `globals.input_buffer_physical_address`, which causes the system to call into the following routine:
// 
thread_local struct input current_input;
thread_local u64 offset_in_input_buffer;

int target_read_guest_input_buffer(struct context *context, u64 virtual_address, u8 *buffer, u64 size){
    (void)virtual_address;
    if(offset_in_input_buffer + size < (u64)current_input.size){
        memcpy(buffer, current_input.data + offset_in_input_buffer, size);
        offset_in_input_buffer += size;
        return 1;
    }
    set_crash_information(context, CRASH_timeout, (u64)"Ran out of input."); // We cannot cause a page fault, as the page is still present in the page tables, causing windows to infinitely loop.
    return 0;
}


struct crash_information target_execute_input(struct context *context, struct input input){
    struct registers registers = globals.snapshot.registers;
    
    if(is_kernel_mode){
        // 
        // If we are targeting a driver, emulate the call to 'nt!NtDeviceIoControlFile'.
        // 
        struct input_metadata *input_metadata = (void *)input.data;
        
        if(target_globals.enable_double_fetch_detection){
            current_input = input;
            offset_in_input_buffer = sizeof(struct input_metadata);
        }else{
            // 
            // Write in the input.
            // 
            guest_write_size(context, input.data, target_globals.input_buffer, input.size);
        }
        
        // 
        // Supply the input parameters.
        //    NtDeviceIoControlFile(FileHandle, Event, ApcRoutine, ApcContext, IoStatusBlock, IoControlCode, InputBuffer, InputBufferLength, OutputBuffer, OutputBufferLength);
        // 
        registers.rip = target_globals.NtDeviceIoControlFile;
        registers.rcx = target_globals.handle;
        registers.rdx = 0;
        registers.r8  = 0;
        registers.r9  = 0;
        guest_write(u64, registers.rsp + 0x28, target_globals.isob_buffer);
        guest_write(u64, registers.rsp + 0x30, input_metadata->ioctl);
        guest_write(u64, registers.rsp + 0x38, target_globals.input_buffer + (input_metadata->input_buffer_offset % INPUT_SIZE));
        guest_write(u64, registers.rsp + 0x40, input_metadata->input_buffer_size);
        guest_write(u64, registers.rsp + 0x48, target_globals.input_buffer + (input_metadata->output_buffer_offset % INPUT_SIZE));
        guest_write(u64, registers.rsp + 0x50, input_metadata->output_buffer_size);
        
    }else{
        // 
        // If we are targeting a user-mode function, simply continue from the snapshot register state, 
        // after writing in the new input.
        // 
        u64 size_to_write = (input.size < target_globals.input_size) ? input.size : target_globals.input_size;
        
        guest_write_size(context, input.data, target_globals.input_buffer, size_to_write);
    }
    
    // 
    // Set up the return value of 'DEFAULT_RETURN_RIP' which will mark the success case.
    // 
    guest_write(u64, registers.rsp, DEFAULT_RETURN_RIP);
    
    context->registers = registers;
    return start_execution_jit(context);
}

// We don't have to do anything on reset.
void target_reset(struct context *context){ (void)context; }
