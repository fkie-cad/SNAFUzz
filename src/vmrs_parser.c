// 
// A very ad-hoc implementation of the VMRS format used by Hyper-v
// to save the state of their Virtual Machines to disk.
// 
// The original idea was to implement this format so we can 
// load a state of a virtual machine into 'snapshot mode' and
// then take a snapshot from there.
// This would remove the need to be able to boot from a disk.
// In practice, I have had a lot of trouble getting the format
// up and running and the parser is pretty immature.
// 
// The format still possibly fills the desired role when booting 
// the virtual machine from the .vhdx fails.
// 
//                                       - Pascal Beyer 21.03.2024
// 


#if _WIN32
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))
#else
#define PACK( __Declaration__ )  __Declaration__ __attribute__((packed))
#endif

// @cleanup: maybe implement this.
__declspec(dllimport) int RtlDecompressBufferEx(u16 CompressionFormat, void *UncompressedBuffer, u32 UncompressedBufferSize, void *CompressedBuffer, u32 CompressedBufferSize, u32 *FinalUncompressedSize, void *WorkSpace);

int parse_vmrs(struct context *context, char *vmrs_file_name){
    
    struct file file = load_file(vmrs_file_name);
    if(!file.memory){
        print("Error: Could not load '%s'.\n", vmrs_file_name);
        return 0;
    }
    
    struct registers registers = {0};
    
    print("Parsing .VMRS file '%s'\n", vmrs_file_name);
    print("\nWarning: The VMRS parser is relatively unstable.\n");
    
    PACK(struct vmrs_header{
                u32 signature;
                u32 crc;
                u16 age;
                u32 version;
                u64 not_sure;
                u32 data_alignment;
                u64 log_offset;
                u64 log_size;
                u32 header_size;
            }) *header = (void *)file.memory;
    
    struct{
        u32 signature;
        u32 amount_of_entries;
        
        PACK(struct storage_object_table_entry {
                    u8 type;
                    u32 crc32;
                    u64 start_offset;
                    u32 size;
                    u8  one;
                }) entries[];
        
    } *storage_object_table_header = (void *)(file.data + 2 * header->header_size);
    
    struct key_table{
        u8 *data;
        u64 size;
    } *key_tables = 0;
    u64 amount_of_key_tables = 0;
    
    for(u32 index = 0; index < storage_object_table_header->amount_of_entries; index++){
        struct storage_object_table_entry *entry = &storage_object_table_header->entries[index];
        
        u8 *entry_data = file.data + entry->start_offset;
        u32 entry_size = entry->size;
        
        if(entry->type == /*unknown*/0){
            // 
            // These seem to be ignored.
            // 
        }else if(entry->type == /*object_table*/1){
            if(index + 1 != storage_object_table_header->amount_of_entries){
                print("The VMRS file has a corrupt object table.\n");
                return 0;
            }
            
            // Restart the loop with the new table.
            index = 0xffffffff;
            storage_object_table_header = (void *)entry_data;
            continue;
            
        }else if(entry->type == /*key_table*/2){
            struct key_table_header{
                u16 two;             // ?
                u16 table_index;
                u16 sequence_number; // ?
                u8  crc32[4];
            } *key_table_header = (void *)entry_data;
            
            if(key_table_header->table_index >= amount_of_key_tables){
                
                u64 new_amount = ((u64)key_table_header->table_index + 1) > (2 * amount_of_key_tables) ? ((u64)key_table_header->table_index + 1) : (2 * amount_of_key_tables);
                
                key_tables = realloc(key_tables, new_amount * sizeof(*key_tables));
                memset(key_tables + amount_of_key_tables, 0, sizeof(*key_tables) * (new_amount - amount_of_key_tables));
                
                amount_of_key_tables = new_amount;
            }
            
            assert(!key_tables[key_table_header->table_index].data);
            
            key_tables[key_table_header->table_index].data = entry_data;
            key_tables[key_table_header->table_index].size = entry_size;
        }else if(entry->type == /*file*/3){
        }else if(entry->type == /*free*/4){
        }else{
            print("[VMRS] Warning: Ignoring unhandled entry type %d in storage object table.\n", entry->type);
        }
    }
    
    struct ram_block{
        u8 *data;
        u64 size;
    } *ram_blocks = null;
    u64 ram_block_count = 0;
    
    struct memory_block{
        u64 pages;
        u64 previous;
        u64 base;
    } memory_blocks[0x10] = {0};
    u32 memory_block_count = 0;
    
    for(u32 key_table_index = 0; key_table_index < amount_of_key_tables; key_table_index++){
        if(!key_tables[key_table_index].data) continue;
        
        for(u32 key_offset = 10; key_offset + 32 < key_tables[key_table_index].size; ){
            PACK(struct key_table_entry{
                        u8 type;
                        u8 flags; // 1 - file_entry,  2 - ?
                        u32 size;
                        u16 parent_table_index;
                        u32 parent;
                        u32 checksum;
                        u32 child_index;
                        u8 string_length;
                        u8 string[];
                    }) *key_entry = (void *)(key_tables[key_table_index].data + key_offset);
            
            key_offset += key_entry->size;
            
            if(!key_entry->size) break;
            
            if(key_entry->type == /*free*/1) continue;
            if(key_entry->type == /*non-leaf*/9) continue;
            
#if 0
            u8 *stack[0x20] = {0};
            s32 stack_at = 0;
            
            stack[stack_at++] = (void *)key_entry;
            
            while(key_entry->parent){
                assert(stack_at < array_count(stack));
                u8 *parent = key_tables[key_entry->parent_table_index].data + key_entry->parent;
                
                stack[stack_at++] = parent;
                
                key_entry = (void *)parent;
            }
            
            while(stack_at > 0){
                key_entry = (void *)stack[--stack_at];
                
                print("/");
                print("%.*s", key_entry->string_length, key_entry->string);
            }
            print("\n");
#endif
            
            struct string entry_name = (struct string){.data = (char *)key_entry->string, .size = key_entry->string_length - 1};
            
            u8 *entry_data = key_entry->string + key_entry->string_length;
            u64 entry_size = key_entry->size - (sizeof(*key_entry) + key_entry->string_length);
            
            // HyperVStorageKeyTableEntry::GetValueSizeInBytes
            // 
            // key_entry->type == 1       -> key_entry->size - 15.
            // if(key_entry->flags & 1)   -> 0xc (probably is_file or something)
            // key_entry->type == 9       -> 8
            // key_entry->type == 6, 7    -> *(u32 *)(key_entry->string + key_entry->string_length)
            // key_entry->type == 3, 4, 5 -> 8
            // key_entry->type == 8       -> 4
            // 
            // otherwise -1.
            // 
            // GetFileObject() *(u64 *)(key_entry->string + key_entry->string_length + 4)
            // 
            
            if(key_entry->flags & 1){
                entry_size = *(u32 *)entry_data;
                u64 offset_in_file = *(u64 *)(entry_data + 4);
                
                entry_data = file.data + offset_in_file;
            }else if(key_entry->type == 6 || key_entry->type == 7){
                entry_size = *(u32 *)entry_data;
                entry_data += 4;
            }
            
            if(string_match(entry_name, string("partition_state"))){
                // 
                // /savedstate/savedVM/partition_state 
                // 
                // The value consists of a sequence of blocks.
                // The offset of the first block is at offset 8 in the data.
                // Each block specifies its size at offset 4.
                // 
                // These sizes/offsets do not include the header (0x10) bytes
                // Each block has a feature code at offset 0.
                // 
                
                for(u64 offset = *(u64 *)(entry_data + 8) + 0x10; offset + 0x10 < entry_size;){
                    u8 *partition_state_block = entry_data + offset;
                    
                    u32 kind = *(u32 *)(partition_state_block + 0);
                    u32 size = *(u32 *)(partition_state_block + 4);
                    
                    u64 *reg_data = (u64 *)(partition_state_block + 0x10);
                    
                    switch(kind){
                        // 
                        // @note: There are a lot of different things here,
                        //        but vm2dmp only cares about certain ones.
                        // 
                        
                        case 0x20000000:{
                            // CPUID leaves.
                        }break;
                        
                        case 0x20001000:{
                            // guest os info.
                        }break;
                        
                        case 0x20002000:{
                            registers.hv_x64_msr_hypercall_page = reg_data[0];
                        }break;
                        
                        case 0x20003000:{
                            // u64 sequence_number;
                            registers.hv_x64_msr_reference_tsc_page = reg_data[1];
                        }break;
                        
                        case 0x30005000:{
                            // 
                            // gprs, rip, rflags
                            // 
                            assert(size == 18 * 8);
                            
                            for(u32 index = 0; index < array_count(registers.gpr); index++){
                                registers.gpr[index] = reg_data[index];
                            }
                            registers.rip = reg_data[16];
                            registers.rflags = reg_data[17];
                        }break;
                        case 0x30006000:{
                            // 
                            // Legacy xsave area:?
                            //    xmm
                            //    st
                            //    mxcsr (2 x u64 for some reason)
                            //    fpcs  (2 x u64 for some reason)
                            assert(size == 16 * (16 + 8 + 2));
                            
                            for(u32 index = 0; index < array_count(registers.simd); index++){
#if _WIN32
                                registers.simd[index].xmmi.m128i_i64[0] = reg_data[2 * index + 0];
                                registers.simd[index].xmmi.m128i_i64[1] = reg_data[2 * index + 1];
#else
                                registers.simd[index].xmmi[0] = reg_data[2 * index + 0];
                                registers.simd[index].xmmi[1] = reg_data[2 * index + 1];
#endif
                            }
                            
                            // 
                            // @cleanup: I don't have st registers at the moment.
                            // 
                            
                            registers.fpu_control_word = (u16)reg_data[32 + 16 + 0];
                            registers.mxcsr      = (u32)(reg_data[32 + 16 + 3] >> 0);
                            registers.mxcsr_mask = (u32)(reg_data[32 + 16 + 3] >> 32);
                        }break;
                        case 0x30007000:{
                            // 
                            // This seems to be control registers
                            // 
                            // cr0, cr2, cr3, cr4, cr8, efer
                            // 
                            assert(size == 8 * 6);
                            
                            registers.cr0 = reg_data[0];
                            registers.cr2 = reg_data[1];
                            registers.cr3 = reg_data[2];
                            registers.cr4 = reg_data[3];
                            registers.cr8 = reg_data[4];
                            registers.ia32_efer = reg_data[5];
                        }break;
                        case 0x30008000:{
                            // 
                            // This seems to be the debug registers
                            // 
                            // dr0, dr1, dr2, dr3, dr6, dr7
                            // 
                            assert(size == 8 * 6);
                            
                            registers.dr0 = reg_data[0];
                            registers.dr1 = reg_data[1];
                            registers.dr2 = reg_data[2];
                            registers.dr3 = reg_data[3];
                            registers.dr6 = reg_data[4];
                            registers.dr7 = reg_data[5];
                        }break;
                        case 0x30009000:{
                            // 
                            // Segment registers
                            // 
                            assert(size == 16 * 9);
                            struct segment *segments = (void *)reg_data;
                            
                            registers.ds = segments[0];
                            registers.cs = segments[1];
                            registers.ss = segments[2];
                            registers.es = segments[3];
                            registers.fs = segments[4];
                            registers.gs = segments[5];
                            
                            registers.tr = segments[7];
                            
                            registers.gs_base = registers.gs.base;
                            registers.fs_base = registers.fs.base;
                            
                            registers.ldt = segments[8];
                        }break;
                        case 0x3000a000:{
                            // 
                            // GDT, IDT
                            // 
                            assert(size == 16 * 2);
                            
                            registers.idt_limit = (u16)(reg_data[0] >> 48);
                            registers.idt_base  = reg_data[1];
                            
                            registers.gdt_limit = (u16)(reg_data[2] >> 48);
                            registers.gdt_base  = reg_data[3];
                        }break;
                        case 0x3000b000:{
                            // 
                            // Probably msr information (there is the apic base in there).
                            // 
                            assert(size == 8 * 12);
                            
                            registers.ia32_tsc = reg_data[0]; // @cleanup: not sure
                            registers.gs_swap = reg_data[1];
                            registers.ia32_apic_base = reg_data[2];
                            registers.ia32_star = reg_data[7];
                            registers.ia32_lstar = reg_data[8];
                            registers.ia32_cstar = reg_data[9];
                            registers.ia32_fmask = reg_data[10];
                            
                        }break;
                        case 0x3000c000:{
                            // 
                            // @note: I am sort of guessing these as most of them are just 0.
                            // 
                            // pat
                            // mtr_cap
                            // mtr_def_type
                            // MTRR_FIX_64K_00000
                            // MTRR_FIX_16K_80000
                            // MTRR_FIX_16K_A0000
                            // MTRR_FIX_4K_C0000
                            // MTRR_FIX_4K_C8000
                            // MTRR_FIX_4K_D0000
                            // MTRR_FIX_4K_D8000
                            // MTRR_FIX_4K_E0000
                            // MTRR_FIX_4K_E8000
                            // MTRR_FIX_4K_F0000
                            // MTRR_FIX_4K_F8000
                            // 
                            // MTRR_PHYS_BASE_0
                            // MTRR_PHYS_MASK_0
                            // MTRR_PHYS_BASE_1
                            // MTRR_PHYS_BASE_1
                            // ...
                            registers.ia32_pat           = reg_data[0];
                            registers.ia32_mtrr_cap      = reg_data[1];
                            registers.ia32_mtrr_def_type = reg_data[2];
                            
                            registers.ia32_mtrr_phys_base = reg_data[14];
                            registers.ia32_mtrr_phys_mask = reg_data[15];
                            
                        }break;
                        case 0x3000d000:{
                            // 
                            // This contains the xcr0 (presumably, its just 7).
                            // 
                            registers.xcr0 = reg_data[0];
                        }break;
                        
                        case 0x3000f000:{
                            // 
                            // Local apic:
                            //   Sadly these values are pretty hard to messure as the debugger alters them.
                            //   For now I will just fill in whatever I am confidtent in.
                            // 
                            
                            assert(size == 56 * 4);
                            
                            u32 *data = (u32 *)reg_data;
                            
                            registers.local_apic.id_register       = data[2];
                            registers.local_apic.version_register  = data[3];
                            registers.local_apic.local_destination_register = data[4];
                            registers.local_apic.destination_format_register = data[5];
                            registers.local_apic.spurious_interrupt_vector_register = data[6];
                            
                            registers.local_apic.interrupt_command_register.low = data[42];
                            registers.local_apic.local_vector_table.timer_register = data[43];
                            registers.local_apic.local_vector_table.thermal_sensor_register = data[44]; // could be machine check interrupt register as well...
                            registers.local_apic.local_vector_table.performance_monitoring_counters_register = data[45];
                            registers.local_apic.local_vector_table.lint0_register = data[46];
                            registers.local_apic.local_vector_table.lint1_register = data[47];
                            registers.local_apic.local_vector_table.error_register = data[48];
                            registers.local_apic.timer_divide_configuration_register = data[53];
                            
                            registers.local_apic.highest_interrupt_in_service = apic__get_highest_set_bit(registers.local_apic.in_service_register);
                            registers.local_apic.highest_pending_interrupt    = apic__get_highest_set_bit(registers.local_apic.interrupt_request_register);
                            
                        }break;
                        
                        case 0x30010000:{
                            // 
                            // SINT registers and related pages.
                            // 
                            assert(size == (16 + 4) * 8);
                                    
                            for(u32 index = 0; index < array_count(registers.hv_x64_msr_sint); index++){
                                registers.hv_x64_msr_sint[index] = reg_data[index];
                            }
                            
                            registers.hv_x64_msr_vp_assist_page = reg_data[16];
                            registers.hv_x64_msr_siefp = reg_data[17];
                            registers.hv_x64_msr_simp  = reg_data[18];
                            // There is one more here, but is 0.
                        }break;
                        
                        case 0x30011000:{
                            // 
                            // Timers
                            // 
                            assert(size == (4 + 4) * 8);
                            registers.hv_x64_msr_stimer0_config = reg_data[0];
                            registers.hv_x64_msr_stimer0_count  = reg_data[1];
                            
                            // @note: we currently do not support these.
                            // registers.hv_x64_msr_stimer1_config = reg_data[2];
                            // registers.hv_x64_msr_stimer1_count  = reg_data[3];
                            // registers.hv_x64_msr_stimer2_config = reg_data[4];
                            // registers.hv_x64_msr_stimer2_count  = reg_data[5];
                            // registers.hv_x64_msr_stimer3_config = reg_data[6];
                            // registers.hv_x64_msr_stimer3_count  = reg_data[7];
                            
                        }break;
                        
                        case 0xf0000000:{
                            // break next interation.
                            offset = entry_size - (size + 0x10);
                        }break;
                    }
                    
                    offset += size + 0x10;
                }
            }else if(entry_name.size > 8 && string_match((struct string){.data = entry_name.data, .size = 8}, string("RamBlock"))){
                
                u32 ram_block_number = 0;
                for(u32 offset = 8; offset < entry_name.size; offset++){
                    ram_block_number *= 10;
                    ram_block_number += entry_name.data[offset] - '0';
                }
                
                if(ram_block_number >= ram_block_count){
                    u64 new_count = (ram_block_number + 1) > (ram_block_count * 2) ? (ram_block_number + 1) : (ram_block_count * 2);
                    
                    ram_blocks = realloc(ram_blocks, new_count * sizeof(*ram_blocks));
                    memset(ram_blocks + ram_block_count, 0, (new_count - ram_block_count) * sizeof(*ram_blocks));
                    
                    ram_block_count = new_count;
                }
                
                ram_blocks[ram_block_number].data = entry_data;
                ram_blocks[ram_block_number].size = entry_size;
            }else if(entry_name.size > 14 && string_match((struct string){.data = entry_name.data, .size = 14}, string("RamMemoryBlock"))){
                
                u32 memory_block_number = 0;
                for(u32 offset = 14; offset < entry_name.size; offset++){
                    memory_block_number *= 10;
                    memory_block_number += entry_name.data[offset] - '0';
                }
                
                u64 *values = (u64 *)entry_data;
                
                assert(memory_block_number < array_count(memory_blocks));
                memory_blocks[memory_block_number].pages    = values[1];
                memory_blocks[memory_block_number].previous = values[2];
                memory_blocks[memory_block_number].base     = values[3];
                
                if(memory_block_number + 1 > memory_block_count){
                    memory_block_count = memory_block_number + 1;
                }
            }else if(entry_name.size > 12 && string_match((struct string){.data = entry_name.data, .size = 12}, string("VmbusContext"))){
                
                u32 context_number = 0;
                for(u32 offset = 12; offset < entry_name.size; offset++){
                    context_number *= 10;
                    context_number += entry_name.data[offset] - '0';
                }
                
                // we have VmbusContext 0-11
                // 0 seems to be the two monitor pages (verification pending)
                // 1 seems to be a list of all vmbus channels (1 - 9)
                // all other contexts appear to be gpadls.
                // 
                // This somehow means there is a missmatch (9 + 2 = 11 but there are 12 contexts).
                // 
                
                // u32 context_number;
                // u32 context_kind; // ?
                // u64 context_size;
                assert(context_number == *(u32 *)(entry_data + 0));
                assert(*(u64 *)(entry_data + 8) == entry_size - 0x10);
                
                u8 *data = entry_data + 0x10;
                
                if(context_number == 0){
                    
                    // u16 minor_version;
                    // u16 major_version
                    // u32; // this is 0x11 not sure what that means.
                    // u64 monitor_page1;
                    // u64 monitor_page2;
                    
                    
                    u16 minor_version = *(u16 *)(data + 0);
                    u16 major_version = *(u16 *)(data + 2);
                    if(minor_version != 2 && major_version != 5){
                        print("VMRS Warning: VMBUS version differs from expected (%d.%d vs 5.2 (expected))\n", major_version, minor_version);
                    }
                    
                    globals.vmbus.monitor_page1 = *(u64 *)(data +  8);
                    globals.vmbus.monitor_page2 = *(u64 *)(data + 16);
                    
                    // print_byte_range(entry_data, entry_size, 0);
                }else if(context_number == 1){
                    
                    // print("main context:\n");
                    
                    for(u32 offset = 0x10; offset < entry_size; ){
                        u32 size  = *(u32 *)(entry_data + offset);
                        
                        u8 *channel_data = entry_data + offset;
                        
                        u32 channel_id = *(u32 *)(channel_data + 4);
                        struct guid device_guid = *(struct guid *)(channel_data + 8);
                        // struct guid;
                        u32 gpadl_id = *(u32 *)(channel_data + 8 + 2 * 16);
                        u32 read_ring_buffer_pages = *(u32 *)(channel_data + 8 + 2 * 16 + 4);
                        u32 connection_id = *(u32 *)(channel_data + 8 + 2 * 16 + 8);
                        u8  monitor_id = *(u8 *)(channel_data + 8 + 2 * 16 + 12);
                        
                        struct vmbus_channel *channel = push_struct(&context->permanent_arena, struct vmbus_channel);
                        channel->channel_id = channel_id;
                        channel->gpadl_id = gpadl_id;
                        channel->read_ring_buffer_pages = read_ring_buffer_pages;
                        channel->connection_id = connection_id;
                        channel->monitor_id = monitor_id;
                        
                        channel->device_kind = vmbus_interface_type_id_to_device_type(device_guid);
                        
#if 0
                        print("Channel %u (%d):\n", channel_id, channel->device_kind);
                        print("    guid {%.8x-%.4x-%.4x-%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x}\n", device_guid.Data1, device_guid.Data2, device_guid.Data3, device_guid.Data4[0], device_guid.Data4[1], device_guid.Data4[2], device_guid.Data4[3], device_guid.Data4[4], device_guid.Data4[5], device_guid.Data4[6], device_guid.Data4[7]);
                        print("    gpadl_id %u\n", gpadl_id);
                        print("    read_ring_buffer_pages %u\n", read_ring_buffer_pages);
                        print("    connection_id %x\n", connection_id);
                        print("    monitor_id %u\n", monitor_id);
#endif
                        
                        channel->next = globals.vmbus.channels;
                        globals.vmbus.channels = channel;
                        
                        offset += size;
                    }
                }else{
                    u32 gpadl_id    = *(u32 *)(data + 0x0);
                    u32 channel_id  = *(u32 *)(data + 0x4);
                    u16 range_count = *(u16 *)(data + 0x8);
                    u16 buflen      = *(u16 *)(data + 0xa);
                    // u32 hex_18 = *(u32 *)(data + 0xc);
                    // u64 zero = *(u64 *)(data + 0x10);      // maybe offset?
                    u64 byte_size   = *(u64 *)(data + 0x18);
                    // u64 pages[];
                    
                    u64 amount_of_pages = (buflen-8)/8; // The 'buflen' includes the 'byte_size' and all of the pages.
                    
                    assert(range_count == 1);
                    assert(byte_size == 0x1000 * amount_of_pages);
                    
                    struct gpadl *gpadl = (void *)push_data(&context->permanent_arena, u8, sizeof(struct gpadl) + amount_of_pages*sizeof(u64));
                    gpadl->gpadl_id     = gpadl_id;
                    gpadl->channel_id   = channel_id;
                    gpadl->amount_of_pages = (u32)amount_of_pages; // @cleanup: Maybe get rid of this cast?
                    memcpy(gpadl->pages, data + 0x20, amount_of_pages*sizeof(u64));
                    
                    gpadl->next = globals.vmbus.gpadls;
                    globals.vmbus.gpadls = gpadl;
                    
#if 0
                    print("gpadl %u:\n", gpadl_id);
                    print("    channel_id %u\n", channel_id);
                    print("    range_count %u\n", range_count);
                    print("    buflen %u\n", buflen);
                    print_byte_range(entry_data, entry_size, 0);
#endif
                }
            }
        }
    }
    
    if(memory_block_count == 0){
        print("Error: Parsing VMRS '%s', no memory blocks found.\n", vmrs_file_name);
        print("       This happens if the virtual machine is running instead of being saved.\n");
        return 0;
    }
    
    u64 memory_size = (memory_blocks[memory_block_count-1].base + memory_blocks[memory_block_count-1].pages) * 0x1000;
    
    context->registers = registers;
    
    u64 page_bitmap_size = (memory_size / 0x1000) / 8;
    
    context->physical_memory_size      = memory_size;
    context->physical_memory           = os_allocate_memory(memory_size);
    context->physical_memory_copied    = os_allocate_memory(page_bitmap_size);
    context->physical_memory_executed  = os_allocate_memory(page_bitmap_size);
    memset(context->physical_memory_copied, 0xff, page_bitmap_size);
    
    globals.snapshot.physical_memory_size = memory_size;
    globals.snapshot.physical_memory = context->physical_memory;
    
    for(u64 memory_block_index = 0, ram_block_index = 0; memory_block_index < memory_block_count; memory_block_index++){
        
        struct memory_block memory_block = memory_blocks[memory_block_index];
        
        u64 ram_blocks_for_memory_block = (memory_block.pages * 0x1000) / 0x100000;
        
        assert(ram_block_index + ram_blocks_for_memory_block <= ram_block_count);
        
        for(u64 index = 0; index < ram_blocks_for_memory_block; index++){
            struct ram_block ram_block = ram_blocks[ram_block_index + index];
            assert(ram_block.size);
            
            u8 *block_memory = context->physical_memory + memory_block.base * 0x1000 + index * 0x100000;
            
            if(ram_block.size == 0x100000){
                memcpy(block_memory, ram_block.data, 0x100000);
            }else{
                
                // @note: decompress the block.
                
                u32 out_offset = 0;
                
                for(u32 offset = 0; offset < ram_block.size; ){
                    u32 size = *(u32 *)(ram_block.data + offset);
                    
                    if(size == 0xffffffff) break;
                    
                    if(size == 0xfffffffe || size == 0xfffffffd){
                        u32 amount_of_pages = 0;
                        
                        u64 value = *(u64 *)(ram_block.data + offset + 4);
                        
                        if(size == 0xfffffffe){
                            amount_of_pages = 1;
                            offset += 0xc;
                        }else{
                            amount_of_pages = *(u32 *)(ram_block.data + offset + 0xc);
                            offset += 0x10;
                        }
                        
                        if(out_offset + (amount_of_pages << 9) < memory_size){
                            print("VMRS: Error for compressed block.\n");
                            return 0;
                        }
                        
                        if((amount_of_pages != 0)){
                            __stosq((u64 *)(block_memory + out_offset), value, (amount_of_pages << 9));
                        }
                        
                        out_offset += amount_of_pages * 0x1000;
                    }else{
                        
                        u32 output_size = 0x1000;
                        
                        if(size == 0xfffffffc){
                            output_size = *(u32 *)(ram_block.data + offset + 4);
                            size        = *(u32 *)(ram_block.data + offset + 8);
                            
                            offset += 8;
                        }
                        
                        // size must be smaller or equal to a page.
                        // and must fit in the buffer
                        if(size > 0x1000 || (ram_block.size - offset) < 4 + size){
                            print("VMRS: Decompression error.\n");
                            return 0;
                        }
                        
                        if(output_size > (0x100000 - out_offset)){
                            print("VMRS: Decompression error.\n");
                            return 0;
                        }
                        
                        u8 *source = ram_block.data + offset + 4;
                        u8 *dest = block_memory + out_offset;
                        
                        if(output_size == size){
                            memcpy(dest, source, size);
                        }else{
                            u32 size_decompressed = 0;
                            int Status = RtlDecompressBufferEx(/*COMPRESSION_FORMAT_LZNT1*/3, dest, output_size, source, size, &size_decompressed, 0);
                            if((Status < 0) || size_decompressed != output_size){
                                print("VMRS: Decompression error.\n");
                                return 0;
                            }
                        }
                        
                        offset += 4 + size;
                        out_offset += output_size;
                    }
                }
                
                assert(out_offset == 0x100000);
            }
        }
        ram_block_index += ram_blocks_for_memory_block;
    }
    
    {
        // 
        // @cleanup: where should we do this?
        // 
        // Initialize the TSC page.
        // 
        u64 value = registers.hv_x64_msr_reference_tsc_page;
        
        if(value & 1){
            u64 physical_address = value & ~0xfff;
            assert(physical_address < context->physical_memory_size);
            
            u8 *tsc_page = get_physical_memory_for_write(context, physical_address);
            *(u64 *)(tsc_page + 0)  = 2;
            *(u64 *)(tsc_page + 8)  = 0x00fcd6fc2c3659a2;
            *(u64 *)(tsc_page + 16) = 3;
        }
    }
    
    {
        u64 value = registers.hv_x64_msr_hypercall_page;
        
        if(value & 1){
            u64 physical_address = value & ~0xfff;
            
            assert(physical_address < context->physical_memory_size);
            
            static u8 hypercall_instructions[] = {
                0x0f, 0x01, 0xc1, 0xc3,                                                             // (vmcall ret)
                0x8b, 0xc8, 0xb8, 0x11, 0x00, 0x00, 0x00, 0x0f, 0x01, 0xc1, 0xc3,                   // (hypercall x86)
                0x48, 0x8b, 0xc1, 0x48, 0xc7, 0xc1, 0x11, 0x00, 0x00, 0x00, 0x0f, 0x01, 0xc1, 0xc3, // (hypercall x64)
                0x8b, 0xc8, 0xb8, 0x12, 0x00, 0x00, 0x00, 0x0f, 0x01, 0xc1, 0xc3,                   // (x86)
                0x48, 0x8b, 0xc1, 0x48, 0xc7, 0xc1, 0x12, 0x00, 0x00, 0x00, 0x0f, 0x01, 0xc1, 0xc3, // (x64)
            };
            
            u8 *hypercall_page = get_physical_memory_for_write(context, physical_address);
            memset(hypercall_page, 0x90, 0x1000);
            memcpy(hypercall_page, hypercall_instructions, sizeof(hypercall_instructions));
        }
    }
    
    for(struct vmbus_channel *channel = globals.vmbus.channels; channel; channel = channel->next){
        
        // 
        // This can apparently happen.
        // 
        if(channel->gpadl_id == 0) continue;
        
        // 
        // Set up the read and send buffer of the vmbus channels.
        // 
        
        struct gpadl *gpadl = globals.vmbus.gpadls;
        for(; gpadl; gpadl = gpadl->next){
            if(gpadl->channel_id == channel->channel_id && gpadl->gpadl_id == channel->gpadl_id) break;
        }
        assert(gpadl);
        
        u32 read_ring_buffer_pages = channel->read_ring_buffer_pages;
        
        channel->gpadl_id = gpadl->gpadl_id;
        channel->read_ring_buffer_pages = read_ring_buffer_pages;
        
        if(channel->device_kind == VMBUS_DEVICE_keyboard) os_debug_break();
        
        vmbus_channel_initialize_ringbuffers(channel, gpadl);
        
        // see :feat_pending_send_sz in vmbus.c
        *(u8 *)(context->physical_memory + channel->send_buffer.header + 0x40) = 1;
        
        if(channel->device_kind == VMBUS_DEVICE_mouse)    globals.vmbus.mouse = channel;
        if(channel->device_kind == VMBUS_DEVICE_keyboard) globals.vmbus.keyboard = channel;
        
    }
    
    // @cleanup: How to handle this?
    maybe_find_and_load_ntoskrnl(context);
    stub_out_efi_runtime_services(context);
    
    globals.snapshot.registers = context->registers;
    return 1;
}


