// 
// This file sets up the initial state when booting from disk.
// This includes:
// 
//     1) Setting up 4 GB of guest physical memory.
//     2) Setting up an identity page table mapping.
//     3) Parsing the .vhdx to load the '/efi/boot/bootx64.efi' file
//        off the efi system partition and loading it at its preferred base.
//     4) Loading the bios implemented by 'uefi_bios.c'.
//     5) Setting up the initial register state.
//     6) Setting up initial GDT and IDT.
// 

struct efi_loaded_pe{
    u64 image_base;
    u64 entry_point;
    u64 image_size;
} efi_load_pe_at_its_preferred_base(struct context *context, u8 *image_file_data, smm image_file_size, char *file_name){
    
    u8 *image_file_end = image_file_data + image_file_size;
    
    u32 pe_header_offset = *(u32 *)(image_file_data + 0x3c);
    if((smm)pe_header_offset + 4 > image_file_size){
        print("Invalid %s file.\n", file_name);
        os_panic(1);
    }
    
    u32 pe_signature = *(u32 *)(image_file_data + pe_header_offset);
    if(pe_signature != 'EP'){
        print("Invalid %s file.\n", file_name);
        os_panic(1);
    }
    pe_header_offset += 4;
    
    struct coff_header{
        u16 machine;
        u16 number_of_sections;
        u32 time_data_stamp;
        u32 pointer_to_symbol_table;
        u32 number_of_symbols;
        u16 size_of_optional_header;
        u16 characteristics;
    } *coff_header = (void *)(image_file_data + pe_header_offset);
    
    struct pe_optional_header{
        u16 magic;
        u8  major_link;
        u8  minor_link;
        u32 size_of_code;
        u32 size_of_init_data;
        u32 size_of_uninit_data;
        u32 address_of_entry_point;
        u32 base_of_code;
        u64 image_base;
        u32 section_alignment;
        u32 file_alignment;
        u16 major_os;
        u16 minor_os;
        u16 major_image;
        u16 minor_image;
        u16 major_subsystem;
        u16 minor_subsystem;
        u32 win32;
        u32 size_of_image;
        u32 size_of_headers;
        u16 checksum;
        u16 dll_characteristics;
        u64 size_of_stack_reserve;
        u64 size_of_stack_commit;
        u64 size_of_heap_reserve;
        u64 size_of_heap_commit;
        u32 loader_flags;
        u32 number_of_rva_and_sizes;
    } *optional_header = (void *)(coff_header + 1);
    
    if(((u8 *)coff_header + sizeof(struct coff_header) + sizeof(struct pe_optional_header)) > image_file_end){
        print("Invalid %s file.\n", file_name);
        os_panic(1);
    }
    
    u32 address_of_entry_point = optional_header->address_of_entry_point;
    u64 image_base = optional_header->image_base;
    
    u64 image_size = optional_header->size_of_image;
    
    if(image_base > context->physical_memory_size || image_base + image_size > context->physical_memory_size){
        print("Image base of %s exceeds size of physical memory, currently unsuppored.\n", file_name);
        os_panic(1);
    }
    
    memcpy(context->physical_memory + image_base, image_file_data, image_file_size);
    
    u32 number_of_directories = optional_header->number_of_rva_and_sizes;
    u16 number_of_sections    = coff_header->number_of_sections;
    
    struct pe_directory_entry{
        u32 rva;
        u32 size;
    } *directory = (void *)(optional_header + 1);
    
    struct coff_section_header {
        u8 section_name[8];
        u32 virtual_size;
        u32 virtual_address;
        u32 size_of_raw_data;
        u32 pointer_to_raw_data;
        u32 pointer_to_relocations;
        u32 pointer_ot_linenumbers;
        u16 number_of_relocations;
        u16 number_of_line_numbers;
        u32 characteristics;
    } *section_headers = (void *)(directory + number_of_directories);
    
    if((u8 *)(section_headers + number_of_sections) > image_file_end){
        print("Invalid %s file.\n", file_name);
        os_panic(1);
    }
    
    for(u32 section_index = 0; section_index < number_of_sections; section_index++){
        u32 pointer_to_raw_data = section_headers[section_index].pointer_to_raw_data;
        u32 size_of_raw_data    = section_headers[section_index].size_of_raw_data;
        u32 virtual_address     = section_headers[section_index].virtual_address;
        u32 virtual_size        = section_headers[section_index].virtual_size;
        
        if((pointer_to_raw_data > image_file_size) || (((smm)pointer_to_raw_data + (smm)size_of_raw_data) > image_file_size) || ((u64)virtual_address + (u64)virtual_size > image_size)){
            print("Invalid %s file.\n", file_name);
            os_panic(1);
        }
        
        u8 *dest   = context->physical_memory + image_base + virtual_address;
        u8 *source = image_file_data + pointer_to_raw_data;
        smm size   = size_of_raw_data;
        
        memcpy(dest, source, size);
        if(virtual_size > size) memset(dest + size, 0, virtual_size - size);
    }
    
    struct efi_loaded_pe ret = {
        .image_base  = image_base,
        .image_size  = optional_header->size_of_image,
        .entry_point = image_base + address_of_entry_point,
    };
    return ret;
}


// 
// This routine is expected to only be called from the main thread.
// 
int efi_setup_initial_state(struct context *context){
    
    // 
    // Allocate the physical memory for main thread context.
    // 
    u64 memory_size =  4ull * 1024ull * 1024ull * 1024ull;
    u64 page_bitmap_size = (memory_size / 0x1000) / 8;
    
    if(globals.snapshot.physical_memory){
        // On reset, for now we free and reallocate...
        VirtualFree(context->physical_memory,          0, /*MEM_RELEASE*/0x8000);
        VirtualFree(context->physical_memory_copied,   0, /*MEM_RELEASE*/0x8000);
        VirtualFree(context->physical_memory_executed, 0, /*MEM_RELEASE*/0x8000);
    }
    
    context->physical_memory_size      = memory_size;
    context->physical_memory           = os_allocate_memory(memory_size);
    context->physical_memory_copied    = os_allocate_memory(page_bitmap_size);
    context->physical_memory_executed  = os_allocate_memory(page_bitmap_size);
    memset(context->physical_memory_copied, 0xff, page_bitmap_size);
    
    globals.snapshot.physical_memory_size = memory_size;
    globals.snapshot.physical_memory = context->physical_memory;
    
    // 
    // Identity mapping the physical memory as rwx:
    // 
    
    u64 page_table_pages = 0;
    {
        u64 amount_of_physical_pages = memory_size >> 12;
        u64 maximum_page_index = (amount_of_physical_pages - 1);
        
        u64 maximum_p1_index = (maximum_page_index >> 0 * 9) & 0x1ff;
        u64 maximum_p2_index = (maximum_page_index >> 1 * 9) & 0x1ff;
        u64 maximum_p3_index = (maximum_page_index >> 2 * 9) & 0x1ff;
        u64 maximum_p4_index = (maximum_page_index >> 3 * 9) & 0x1ff;
        
        context->registers.cr3 = 0x6d5000;
        
        u64 page_at = (context->registers.cr3 >> 12) + 1;
        
        u64 *root_page_table = (u64 *)(context->physical_memory + context->registers.cr3); // level 4
        
        for(u32 p4_index = 0; p4_index <= maximum_p4_index; p4_index++){
            root_page_table[p4_index] = (page_at << 12) | 3;
            
            u64 *p4_table = (u64 *)(context->physical_memory + (page_at << 12)); // level 3
            page_at += 1;
            
            for(u32 p3_index = 0; p3_index <= maximum_p3_index; p3_index++){
                p4_table[p3_index] = (page_at << 12) | 3;
                
                u64 *p3_table = (u64 *)(context->physical_memory + (page_at << 12)); // level 2
                page_at += 1;
                
                for(u32 p2_index = 0; p2_index <= maximum_p2_index; p2_index++){
                    p3_table[p2_index] = (page_at << 12) | 3;
                    
                    u64 *p2_table = (u64 *)(context->physical_memory + (page_at << 12)); // level 1
                    page_at += 1;
                    
                    for(u32 p1_index = 0; p1_index <= maximum_p1_index; p1_index++){
                        u64 physical_page_index = p1_index | (p2_index << 9) | (p3_index << 18) | (p4_index << 27);
                        
                        if(physical_page_index == 0){
                            // Don't map the zero page for now...
                        }else{
                            p2_table[p1_index] = (physical_page_index << 12) | 3;
                        }
                    }
                }
            }
        }
        
        page_table_pages = page_at - (context->registers.cr3 >> 12);
        
#if 0
        for(u64 page_index = 0; page_index <= maximum_page_index; page_index++){
            smm wanted_page = page_index << 12;
            smm given_page  = (smm)translate_address(context, page_index << 12, PERMISSION_none) - (smm)context->physical_memory;
            assert(wanted_page == given_page);
        }
#endif
    }
    
    u64 efi_system_partition_starting_lba = 0;
    u64 efi_system_partition_last_lba = 0;
    u64 disk_last_lba = 0;
    
    u32 boot_file_size = 0;
    u8 *boot_file_data = null;
    
    {
        // 
        // Parse the disk image.
        // 
        // The first sector of the disk image is the MBR or Master Boot Record.
        // In the case of UEFI this is mostly ignored, but it tells us the 'starting_lba'
        // and the 'size_in_lba'.
        // 
        
        u8 *master_boot_record = disk_read_sectors(&context->scratch_arena, 1, 0);
        
        u8  boot_indicator = master_boot_record[446];
        u8  os_indicator   = master_boot_record[450];
        u32 starting_lba   = *(u32 *)(master_boot_record + 454);
        
        if(boot_indicator != 0 || os_indicator != 0xEE){
            print("[efi] Error: Disk is not a UEFI disk, boot_indicator %x os_indicator %x.\n", boot_indicator, os_indicator);
            return 0;
        }
        
        struct guid_partition_table_header{
            u64 signature;
            u32 revision;
            u32 header_size;
            u32 header_crc32;
            u32 reserved;
            u64 lba_of_this_header;
            u64 lba_of_backup_header;
            u64 first_usable_lba;
            u64 last_usable_lba;
            struct guid disk_guid;
            
            struct{
                u64 starting_lba;
                u32 number_of_entries;
                u32 entry_size;
                u32 crc32;
            } partition_entry_array;
        } *gpt_header = (void *)disk_read_sectors(&context->scratch_arena, 1, starting_lba);
        
        if(gpt_header->signature != 0x5452415020494645ULL){
            print("[efi] Guid partition table has invalid signature %.8s, Expected 'EFI PART'.\n", (char *)&gpt_header->signature);
            return 0;
        }
        
        print("disk guid " PRINT_GUID_FORMAT "\n", PRINT_GUID_MEMBERS(gpt_header->disk_guid));
        
        u64 partition_table_size_in_sectors = (gpt_header->partition_entry_array.number_of_entries * gpt_header->partition_entry_array.entry_size)/0x200; 
        
        struct guid_partition_table_entry{
            struct guid partition_type_guid;
            struct guid unique_partition_guid;
            
            u64 starting_lba;
            u64 ending_lba;
            
            u64 attributes;
            
            u16 partition_name[36];
        } *partition_table_entry = (void *)disk_read_sectors(&context->scratch_arena, partition_table_size_in_sectors, gpt_header->partition_entry_array.starting_lba);
        
        struct guid_partition_table_entry *efi_system_partition_entry = null;
        
        for(u32 index = 0; index < gpt_header->partition_entry_array.number_of_entries; index++){
            if((memcmp(partition_table_entry[index].partition_name, L"EFI system partition", sizeof(L"EFI system partition") - 2) == 0) || memcmp(&partition_table_entry[index].partition_type_guid, &(struct guid){0xC12A7328, 0xF81F, 0x11D2, 0xBA, 0x4B, 0x00, 0xA0, 0xC9, 0x3E, 0xC9, 0x3B}, 16) == 0){
                efi_system_partition_entry = &partition_table_entry[index];
                break;
            }
        }
        
        if(!efi_system_partition_entry){
            print("[efi] Error: Could not find EFI System Partition.\n");
            return 0;
        }
        
        efi_system_partition_starting_lba = efi_system_partition_entry->starting_lba;
        efi_system_partition_last_lba     = efi_system_partition_entry->ending_lba;
        disk_last_lba = gpt_header->last_usable_lba;
        
        // 
        // The 'efi_system_partition' should be FAT32 formatted.
        // FAT32:
        //    Reserved Sectors | Fat Region | User Region
        // 
        // Reserved Sectors:
        //   0 - Boot Sector
        //   1 - FSInfo
        //   2,3,4,5 - Unused
        //   6 - Backup Boot Secotr
        //   7 - Backup FSInfo
        //   
        
        u8 *fat32_boot_sector = disk_read_sectors(&context->scratch_arena, 1, efi_system_partition_entry->starting_lba);
        u16 bytes_per_sector    = *(u16 *)(fat32_boot_sector + 11);
        u8  sectors_per_cluster = *(u8  *)(fat32_boot_sector + 13);
        u16 number_of_reserved_logical_sector = *(u16 *)(fat32_boot_sector + 14);
        u8  number_of_file_allocation_tables  = *(u8  *)(fat32_boot_sector + 16);
        u32 large_total_sectors = *(u32 *)(fat32_boot_sector + 32);
        
        // @cleanup: Somehow these are not used, but they seem important...
        (void)bytes_per_sector;
        (void)large_total_sectors; 
        
        u32 number_of_sectors_per_file_allocation_table = *(u32 *)(fat32_boot_sector + 36);
        
        u64 user_area_start_sector = efi_system_partition_entry->starting_lba + number_of_reserved_logical_sector + number_of_file_allocation_tables * number_of_sectors_per_file_allocation_table;
        
        u8 *fat32_root_directory = disk_read_sectors(&context->scratch_arena, sectors_per_cluster, user_area_start_sector);
        
        struct fat32_directory_entry{
            u8 name[11];
            u8 attributes;
            u8 nt_reserved;
            u8 creation_time_tenth;
            u16 creation_time;
            u16 creation_date;
            u16 last_access_date;
            u16 first_data_cluster_number_high;
            u16 write_time;
            u16 write_date;
            u16 first_data_cluster_number_low;
            u32 file_size;
        } *directory = (void *)fat32_root_directory;
        
        // 
        // Search for the 'EFI/BOOT/BOOTX64.EFI' file.
        // 
        static char *files[] = {
            "EFI        ",
            "BOOT       ",
            "BOOTX64 EFI",
        };
        
        int found = 1;
        
        for(u32 path_index = 0; path_index < array_count(files); path_index++){
            char *file_name = files[path_index];
            
            for(u32 index = 0; index < (sectors_per_cluster * 0x200) / sizeof(*directory); index++){
                if(memcmp(file_name, directory[index].name, 11) == 0){
                    directory = &directory[index]; 
                    break;
                }
            }
            
            if(path_index + 1 == array_count(files)){
                found = 0;
                break;
            }
            
            u32 cluster_number = (directory->first_data_cluster_number_high << 16) | directory->first_data_cluster_number_low;
            
            directory = (void *)disk_read_sectors(&context->scratch_arena, sectors_per_cluster, user_area_start_sector + (cluster_number - 2) * sectors_per_cluster);
        }
        
        if(found){
            print("[efi] Error: Could not find 'EFI/BOOT/BOOTX64.EFI'.\n");
            return 0;
        }
        
        boot_file_size = directory->file_size;
        
        u32 amount_of_sectors = (boot_file_size + 0x1ff) / 0x200;
        u32 cluster_number    = (directory->first_data_cluster_number_high << 16) | directory->first_data_cluster_number_low;
        
        boot_file_data = disk_read_sectors(&context->scratch_arena, amount_of_sectors, user_area_start_sector + (cluster_number - 2) * sectors_per_cluster);
    }
    
    struct file bios_file = load_file("build/bios.exe");
    if(!bios_file.data){
        print("[efi] Error: Could not load the 'build/bios.exe' file.\n");
        return 0;
    }
    
    struct efi_loaded_pe loaded_bios_file = efi_load_pe_at_its_preferred_base(context, bios_file.data, bios_file.size, "bios.exe");
    print("Bios:        [%p, %p]\n", loaded_bios_file.image_base, loaded_bios_file.image_base + loaded_bios_file.image_size);
    struct loaded_module *bios_module = parse_loaded_module(context, loaded_bios_file.image_base, loaded_bios_file.image_size, string("bios.exe"));
    struct file bios_pdb = load_file("build/bios.pdb");
    bios_module->pdb_context = load_pdb(bios_pdb);
    bios_module->tried_to_load_pdb = 1; // @cleanup: it feels somewhat dumb that I have to set this.
    
    struct efi_loaded_pe loaded_boot_file = efi_load_pe_at_its_preferred_base(context, boot_file_data, boot_file_size, "/EFI/BOOT/BOOTX64.EFI");
    print("BootX64.efi: [%p, %p]\n", loaded_boot_file.image_base, loaded_boot_file.image_base + loaded_boot_file.image_size);
    parse_loaded_module(context, loaded_boot_file.image_base, loaded_boot_file.image_size, string("bootx64.efi"));
    
    {
        // 
        // Initialize the 'registers' to start executing at the bios entry point:
        // 
        //     void entry(u8 *boot_file_base, u64 page_table_pages, u64 efi_system_partition_starting_lba);
        // 
        
        struct registers registers = {0};
        registers.rip = loaded_bios_file.entry_point;
        registers.rsp = 0x13370000 - 0x28;
        registers.cr3 = context->registers.cr3;
        print("Stack:       [%p, %p]\n", registers.rsp - 0x10000, registers.rsp);
        registers.rcx = loaded_boot_file.image_base;
        registers.rdx = page_table_pages;
        registers.r8  = efi_system_partition_starting_lba;
        registers.r9  = disk_last_lba;
        guest_write(u64, registers.rsp + 0x28, efi_system_partition_last_lba);
        
        registers.rflags = 0x6;
        
        registers.cs.selector = 0x28;
        registers.ds.selector = 8;
        registers.es.selector = 8;
        registers.fs.selector = 8;
        registers.gs.selector = 8;
        registers.ss.selector = 8;
        
        // dafuq, how can this be 0 but not zero
        // 
        //     [+0x000] base                     : 0x0 [Type: unsigned __int64]
        //     [+0x008] limit                    : 0xffff [Type: unsigned int]
        //     [+0x00c] selector                 : 0x0 [Type: unsigned short]
        //     [+0x00e ( 3: 0)] segment_type     : 0xb [Type: unsigned short]
        //     [+0x00e ( 4: 4)] is_non_system    : 0x0 [Type: unsigned short]
        //     [+0x00e ( 6: 5)] privilege_level  : 0x0 [Type: unsigned short]
        //     [+0x00e ( 7: 7)] present          : 0x1 [Type: unsigned short]
        //     [+0x00e (11: 8)] reserved         : 0x0 [Type: unsigned short]
        //     [+0x00e (12:12)] available        : 0x0 [Type: unsigned short]
        //     [+0x00e (13:13)] long_mode        : 0x0 [Type: unsigned short]
        //     [+0x00e (14:14)] default_big      : 0x0 [Type: unsigned short]
        //     [+0x00e (15:15)] granularity      : 0x0 [Type: unsigned short]
        // 
        registers.tr = (struct segment){
            .base = 0,
            .limit = 0xffff,
            .selector = 0,
            .segment_type = 0xb,
            .is_non_system = 0,
            .privilege_level = 0,
            .present = 1,
        };
        
        registers.ia32_bios_sign_id = 0xffffffff00000000; // @note: " If IA32_BIOS_SIGN_ID[63:32] is non-zero, then an update was already loaded from the FIT, and the early BIOS microcode update load point may be skipped."
        registers.ia32_misc_enable = 0x851809;
        registers.ia32_efer = 0x500;
        registers.ia32_pat  = 0x0007040600070406;
        registers.ia32_apic_base = 0xfee00000 | 0x900; // Address + Enabled + Boot Strap Processor
        
        registers.ia32_mtrr_def_type = 0xc00;
        registers.ia32_mtrr_cap      = 0x508;
        registers.ia32_mtrr_phys_base = 6;
        registers.ia32_mtrr_phys_mask = 0x7f00000800;
        
        
        registers.local_apic.destination_format_register = 0xffffffff; 
        registers.local_apic.spurious_interrupt_vector_register = 0xff;
        
        registers.local_apic.local_vector_table.timer_register = /*masked*/0x10000;
        registers.local_apic.local_vector_table.thermal_sensor_register = /*masked*/0x10000;
        registers.local_apic.local_vector_table.performance_monitoring_counters_register = /*masked*/0x10000;
        registers.local_apic.local_vector_table.lint0_register = /*masked*/0x10000;
        registers.local_apic.local_vector_table.lint1_register = /*masked*/0x10000;
        registers.local_apic.local_vector_table.error_register = /*masked*/0x10000;
        
        registers.local_apic.highest_interrupt_in_service = -1;
        registers.local_apic.highest_pending_interrupt    = -1;
        
        registers.cr0 = 0x80010033; // PE MP ET NE WP PG
        registers.cr4 = 0x40668;    // DE PAE MCE OSFXSR OSXMMEXCPT OSXSAVE
        registers.xcr0 = /*x87 | SSE | AVX*/7;
        
        registers.ia32_spec_ctrl = 0;
        registers.xinuse = 6;
        
        registers.fpu_control_word = 0x37f; // "Floating-point control word must be initialized to 0x037F."
        registers.mxcsr = 0x1f80;           // "Multimedia-extensions control word (if supported) must be initialized to 0x1F80."
        registers.mxcsr_mask = 0xffff;
        registers.ia32_tsc = 0x13370000;
        registers.ia32_tsc_aux = 0;
        
        registers.ia32_apic_base   = 0xfee00900;
        
        for(u32 index = 0; index < array_count(registers.io_apic.redirection_table); index++){
            registers.io_apic.redirection_table[index].low  = /*masked*/1 << 16;
            registers.io_apic.redirection_table[index].high = 0;
        }
        
        guest_write(u64, registers.rsp, DEFAULT_RETURN_RIP);
        
        static u8 gdt[] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
            0xff, 0xff, 0x00, 0x00, 0x00, 0x93, 0xcf, 0x00, 
            0xff, 0xff, 0x00, 0x00, 0x00, 0x9a, 0xcf, 0x00, 
            0xff, 0xff, 0x00, 0x00, 0x00, 0x92, 0xcf, 0x00, 
            0xff, 0xff, 0x00, 0x00, 0x00, 0x9a, 0xcf, 0x00, 
            0xff, 0xff, 0x00, 0x00, 0x00, 0x9b, 0xaf, 0x00, 
        };
        
        registers.gdt_base  = ((loaded_bios_file.image_base + loaded_bios_file.image_size) + 0xffff) & ~0xffff;
        registers.gdt_limit = sizeof(gdt) - 1;
        memcpy(context->physical_memory + registers.gdt_base, gdt, sizeof(gdt));
        print("gdt:         [%p, %p]\n", registers.gdt_base, registers.gdt_base + registers.gdt_limit);
        
        // 
        // @cleanup: This is not that useful right now.
        //           This will give us a "Bios Crashed!!" message, 
        //           but will not pop the Exception frame.
        //           Hence, it is not easy to get a stack trace. ('dps rsp' works though).
        // 
        u64 bios_crash_address = registers.gdt_base + 0x800;
        u8 *crash = context->physical_memory + bios_crash_address;
        
        // mov ecx, BIOS_crash
        // rdmsr
        crash[0] = 0xb9; *(u32 *)&crash[1] = BIOS_crash;
        crash[5] = 0x0f; crash[6] = 0x32;
        
        static struct idt_entry{
            u16 offset_low;
            u16 selector;
            
            struct{
                u16 ist_index : 3;
                u16 reserved0 : 5;
                u16 gate_type : 5;
                u16 dpl : 2;
                u16 present : 1;
            };
            u16 offset_middle;
            u32 offset_high;
            u32 reserved1;
        } idt[256];
        
        for(u32 index = 0; index < array_count(idt); index++){
            u64 value = (u64)bios_crash_address;
            
            idt[index].offset_low = (u16)value;
            idt[index].offset_middle = (u16)(value >> 16);
            idt[index].offset_high = (u32)(value >> 32);
            
            idt[index].present = 1;
            idt[index].selector = 0x28;
            idt[index].gate_type = 0xe;
        }
        
        // :IDT_GDT position
        // If you change the relative position of the gdt and idt, 
        // then you also have to changs the code in the "firmware".
        registers.idt_base  = registers.gdt_base + 0x1000;
        registers.idt_limit = sizeof(idt) - 1;
        memcpy(context->physical_memory + registers.idt_base, idt, sizeof(idt));
        print("idt:         [%p, %p]\n", registers.idt_base, registers.idt_base + registers.idt_limit);
        
        globals.snapshot.registers = context->registers = registers;
    }
    
    return 1;
}

