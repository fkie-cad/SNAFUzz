
// 
// Coverage handling functions.
// 
// The coverage table (globals.coverage_page_table) maps one bit per byte of guest
// virtual address space. Instruction coverage marks the first byte of each instruction hit. 
// This is done by calling 'update_coverage_table' during instruction decoding.
// Compare coverage and conditional branch coverage (edge coverage) use later bytes of the 
// instruction to indicate additional coverage.
// 
// For compare coverage we mark one byte per byte that was equal during a cmp with an immediate.
// For conditional branch coverage we mark one later byte for 'branch taken' and if there is space
// one later byte for 'branch not taken'.
// 
//                                                                        - Pascal Beyer 23.03.2023

int update_coverage_table(struct context *context, u64 rip){
    
    // We save one bit per instruction in a page table.
    // -> One page is enough to store bits for 8 pages.
    // Hence, in a single pte we can handle an offset of 0x7fff.
    
    u64 coverage_page_index = rip >> 15;
    u32 offset = rip & 0x7fff;
    
    if(coverage_page_index == context->cached_coverage_page_index){
        //
        // Use a bit test intrinsic (bt [page], offset) to atomically set the bit.
        //
        return !_bittestandset((void *)context->cached_coverage_page, offset);
    }
    
    u32 page_indices[4] = {
        (rip >> 42) & 0x1ff, // Top 3 bits are always the sign extension, but whatever.
        (rip >> 33) & 0x1ff, 
        (rip >> 24) & 0x1ff,
        (rip >> 15) & 0x1ff,
    };
    
    u64 *table = globals.coverage_page_table;
    for(u32 page_table_index = 0; page_table_index < array_count(page_indices); page_table_index++){
        u32 page_index = page_indices[page_table_index];
        
        if(table[page_index]){
            //
            // The page is already present.
            //
            table = (u64 *)table[page_index];
        }else{
            //
            // We have to allocate the page.
            //
            
            u8 *previous_current = context->coverage_arena.current;
            u64 *memory = push_data(&context->coverage_arena, u64, 0x200);
            
            u64 *result = atomic_compare_exchange_pointer(&table[page_index], memory, null);
            
            if(result == null){
                // The interlocked compare exchange succeeded.
                table = memory;
            }else{
                // The interlocked compare exchange failed. This means some other thread beat us to the write,
                // and we have the page it allocated in 'result'.
                table = result;
                
                // We must _deallocate_ 'memory' again.
                context->coverage_arena.current = previous_current;
            }
        }
    }
    
    context->cached_coverage_page_index = coverage_page_index;
    context->cached_coverage_page       = (u8 *)table;
    
    //
    // Use a bit test intrinsic (bt [page], offset) to atomically set the bit.
    //
    return !_bittestandset((void *)table, offset);
}

void update_coverage_table_for_compare_coverage(struct context *context, u64 rip, u32 lhs, u32 rhs){
    
    //
    // Mark one byte of the instruction for every equal byte in the operands.
    // We skip past the first byte of the instruction, as it was already marked by instruction coverage.
    //
    u8 *bytes_lhs = (u8 *)&lhs;
    u8 *bytes_rhs = (u8 *)&rhs;
    
    u32 bytes_equal = 0;
    for(u32 index = 0; index < 4; index++){
        bytes_equal += (bytes_lhs[index] == bytes_rhs[index]);
    }
    
    int coverage_increase = 0;
    for(u32 index = 0; index < bytes_equal; index++){
        coverage_increase += update_coverage_table(context, (rip + 1) + index);
    }
    
    context->coverage_increase += coverage_increase;
}

void update_coverage_table_for_conditional_branch(struct context *context, u64 rip, int taken){
    // 
    // @note: For short jumps we can only have a bit for 'we took the branch' and not for 'we did not take the branch'.
    //        We prefer this version over the flipping the two, as it works better for a normal if-statement without an else.
    // 
    context->coverage_increase += update_coverage_table(context, rip + 1 + !taken);
}

void clear_coverage_table(void){
    u64 *p4_table = globals.coverage_page_table;
    for(u32 p4_table_index = 0; p4_table_index < 0x200; p4_table_index++){
        u64 *p3_table = (u64 *)p4_table[p4_table_index];
        if(!p3_table) continue;
        
        for(u32 p3_table_index = 0; p3_table_index < 0x200; p3_table_index++){
            u64 *p2_table = (u64 *)p3_table[p3_table_index];
            if(!p2_table) continue;
            
            for(u32 p2_table_index = 0; p2_table_index < 0x200; p2_table_index++){
                u64 *p1_table = (u64 *)p2_table[p2_table_index];
                if(!p1_table) continue;
                
                for(u32 p1_table_index = 0; p1_table_index < 0x200; p1_table_index++){
                    u8 *page = (u8 *)p1_table[p1_table_index];
                    if(!page) continue;
                    
                    // clear the page
                    memset(page, 0, 0x1000);
                }   
            }
        }
    }
    
    print("Cleared Instruction Coverage Table!\n");
}

//_____________________________________________________________________________________________________________________
// Writing coverage files

u64 *get_coverage_page_if_it_is_present(u64 rip){
    assert(!(rip & 0x7fff));
    u32 page_indices[4] = {
        (rip >> 42) & 0x1ff, // Top 3 bits are always the sign extension, but whatever.
        (rip >> 33) & 0x1ff, 
        (rip >> 24) & 0x1ff,
        (rip >> 15) & 0x1ff,
    };
    
    u64 *table = globals.coverage_page_table;
    for(u32 page_table_index = 0; page_table_index < array_count(page_indices); page_table_index++){
        u32 page_index = page_indices[page_table_index];
        
        
        if(!table[page_index]) return null;
        
        table = (u64 *)table[page_index];
    }
    
    return (u64 *)table;
}

void write_coverage_files(void){
    
    //
    // @WARNING: While we are accessing the coverage table here, some of the threads might 
    //           be writing to the coverage table.
    //
    
    for(struct loaded_module *module = globals.module_list.first; module; module = module->next){
        u64 coverage = 0;
        
        u64 start_address = module->guest_image_base;
        u64 start_offset = start_address & 0x7fff;
        u64 start_page   = start_address - start_offset;
        
        u64 end_address   = module->guest_image_base + module->size_of_image;
        u64 end_offset = end_address & 0x7fff;
        u64 end_page   = end_address - end_offset;
        
        for(u64 address = start_page; address <= end_page; address += 0x8000){
            u64 *coverage_page = get_coverage_page_if_it_is_present(address);
            if(!coverage_page) continue;
            
            u64 it_start = (address == start_page) ? (start_offset/8) : 0;
            u64 it_end   = (address == end_page)   ? (end_offset/8)   : 0x1000;
            
            for(u64 it = it_start; it < it_end; it += 8){
                coverage += __popcnt64(coverage_page[it/8]);
            }
        }
        
        if(coverage != module->coverage){
            char file_name_buffer[0x100];
            snprintf(file_name_buffer, sizeof(file_name_buffer), "coverage/%.*s.coverage", module->short_name.size, module->short_name.data);
            
            FILE *coverage_file = fopen(file_name_buffer, "w");
            assert(coverage_file);
            fclose(coverage_file);
            coverage_file = fopen(file_name_buffer, "a");
            assert(coverage_file);
            
            u64 new_coverage = 0;
            for(u64 address = start_page; address <= end_page; address += 0x8000){
                u64 *coverage_page = get_coverage_page_if_it_is_present(address);
                if(!coverage_page) continue;
                
                // 
                // Compute the bounds within the coverage page.
                // 
                // If it is an intermediate page, we should iterate all of it.
                // Otherwise, we need to map the start and end offset from the 
                // normal address space into the _coverage address space_ where one
                // bit corresponds to one byte, and therefore divide the addresses by 8.
                // 
                
                u64 it_start = (address == start_page) ? (start_offset/8) : 0;
                u64 it_end   = (address == end_page)   ? (end_offset/8)   : 0x1000;
                
                for(u64 it = it_start; it < it_end; it += 8){
                    u64 value = coverage_page[it/8];
                    u32 index;
                    
                    // Iterate all set bits in 'value'.
                    while(_BitScanForward64((void *)&index, value)){
                        
                        new_coverage += 1;
                        
                        // Unset the bit, such that in the next iteration we wont get it anymore.
                        value &= ~(1ull << index);
                        
                        // Compute the 'rip':
                        // 
                        // 'address' is in the _normal_ address space and is aligned to a coverage page (0x8000).
                        // 'it' is the byte offset in the coverage page, to convert it to a bit offset 
                        // (which corresponds to a byte offset in the _normal_ address space) we multiply it by 8.
                        // 'index' is the bit offset in 'value'.
                        u64 rip = address + it * 8 + index;
                        
                        assert(start_address <= rip && rip < end_address);
                        
                        int amount_printed = fprintf(coverage_file, "0x%p\n", rip - module->guest_image_base);
                        assert(amount_printed == 19);
                    }
                }
            }
            
            fclose(coverage_file);
            
            // Report the amount of increased coverage per module.
            print("%-20.*s +%-4lld coverage (%lld)\n", module->short_name.size, module->short_name.data, new_coverage - module->coverage, new_coverage);
            module->coverage = new_coverage;
        }
    }
}

