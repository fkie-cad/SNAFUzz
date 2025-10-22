
//
// "Physical Memory":
//
// The physical memory for the guest is virtual memory on the host, 
// which is loaded from the specified snapshot on startup and stored
// at 'globals.snapshot.physical_memory'.
// Because the different threads each want to fuzz independently, 
// they each have their own physical memory state at 'context->physical_memory'.
// Only the main thread, which is also executing in Snapshot Mode or during target_initialize, 
// has 'context->physical_memory = globals.snapshot.physical_memory'.
// Each other thread (the threads used for fuzzing) lazily copies memory pagewise 
// from the snapshot state and sets the corresponding bit in 'context->physical_memory_copied'.
// To be able to reset to the snapshot, each of the fuzz threads also keeps track 
// of which pages have been dirtied (written to) in 'context->physical_memory_dirty'
// and 'context->dirty_physical_pages'.
// Because of x64's strong memory guarantees, each fuzz thread also keeps track of 
// which physical pages have been executed in 'context->physical_memory_executed',
// such that if such memory is ever written, we can either "crash" the fuzz-case,
// or reset the jit state.
// 
// Also see:
//    get_physical_memory_for_read
//    get_physical_memory_for_write
//    guest_write_size
//    reset_to_snapshot
// 
// 
// Guest Virtual Memory:
// 
// Whenever the guest accesses virtual memory, the address has to be translated
// to a physical address. In its most basic form, this is accomplished by:
//    
//    1) Jitted code calls 'guest_read_size', specifying a stack buffer
//       and how many bytes it wants to read.
//    2) 'guest_read_size' calls 'translate_page_number_to_physical',
//        which does a page table walk, starting at 'context->registers.cr3'
//        and, on success, returns the physical address of the virtual page.
//    3) 'guest_read_size' then calls 'get_physical_address_for_read',
//       to ensure the corresponding memory was copied from the snapshot
//       memory at 'globals.snapshot.physical_memory + <physical_address>,
//       to the thread local memory at 'context->physical_memory + <physical_address>'.
//    4) Finally, the read is performed by memcpy'ing into the passed in buffer.
//    
// (If the read spans multiple pages, this is done in a loop and potentially incorrect for writes).
// 
// Because this process is slow, the translation results are stored in
// Translation Lookaside Buffers (TLBs). The TLBs map the last couple bits
// of a translated address to the physical address and the page on the host.
// There is one tlb per access type:
//     context->read_tlb, context->write_tlb, context->execute_tlb.
// 
// For read and write accesses, the JIT also knows how to perform memory translation
// using the TLBs, allowing it to stay inside the JIT.
// 
// Also see:
//     translate_address
//     prefetch_instruction
//     translate_rip_to_physical
//     initialize_jit (for how we access the TLB's from the jit, and how we are calling guest_*_size)
//     
//                                                                        
// Extra Permissions:
// 
// We allow adding extra permissions to virtual memory pages. These are used to 
// track allocations and detect heap-overflows. They are stored in a parallel page table
// and also cached in the TLB entries.
// They are added or removed using 'change_extra_permissions_for_page'
// and are checked inside 'guest_read_size'/'guest_write_size'.
// They are reset each fuzz-run by simply clearing the top level of the extra permission page table.
// 
// Also see:
//     guest_allocate__inner
//     enum extra_permissions
//     
//                                                                        - Pascal Beyer 28.02.2024
// 

// This is here for Snapshot Mode. It gets drawn in hacky_display.c
_Alignas(0x1000) u32 frame_buffer[1024 * 768];

u8 *get_physical_memory_for_read(struct context *context, u64 physical_address){
    
    if(0xFFF800000 <= physical_address && physical_address < 0xFFF800000 + sizeof(frame_buffer)){
        
        // 
        // This is the hardcoded guest physical memory range for the EFI-framebuffer.
        // A Generation 2 VM in non-'Enhanced session' uses this framebuffer.
        // In Snapshow Mode we render the framebuffer in 'hacky_display.c', otherwise we just 
        // want to return _any_ valid address.
        // 
        
        if(context->snapshot_mode){
            u64 offset = physical_address - 0xFFF800000;
            return (u8 *)frame_buffer + offset;
        }else{
            return context->fake_page;
        }
    }
    
    if(0xF8000000 <= physical_address && physical_address < 0xF8000000 + sizeof(frame_buffer)){
        
        // 
        // This is the hardcoded guest physical memory range for the EFI-framebuffer.
        // A Generation 2 VM in non-'Enhanced session' uses this framebuffer.
        // In Snapshow Mode we render the framebuffer in 'hacky_display.c', otherwise we just 
        // want to return _any_ valid address.
        // 
        
        if(context->snapshot_mode){
            u64 offset = physical_address - 0xF8000000;
            return (u8 *)frame_buffer + offset;
        }else{
            return context->fake_page;
        }
    }
    
    if(physical_address >= context->physical_memory_size){
        set_crash_information(context, CRASH_internal_error, (u64)"Accessing invalid physical memory.");
        return context->fake_page;
    }
    
    u64 page_index = physical_address >> 12;
    u64 byte_index = page_index >> 3;
    u64 bit_index  = page_index & 7;
    
    u64 bit = 1ull << bit_index;
    
    int page_is_present = (context->physical_memory_copied[byte_index] & bit) != 0;
    if(page_is_present){
        //
        // If the page is already present for the current 'context' we know where it is
        // and can just return the translated address.
        //
        return context->physical_memory + physical_address;
    }
    
    //
    // Copy the page from the snapshot, then we know where it is.
    //
    u8 *dest_page   = context->physical_memory         + page_index * 0x1000;
    u8 *source_page = globals.snapshot.physical_memory + page_index * 0x1000;        
    
    int success = os_commit_memory(dest_page, 0x1000, /*executable*/false);
    assert(success);
    
    memcpy(dest_page, source_page, 0x1000);
    context->physical_memory_copied[byte_index] |= bit;
    
    return context->physical_memory + physical_address;
}

u8 *get_physical_memory_for_write(struct context *context, u64 physical_address){
    u8 *ret = get_physical_memory_for_read(context, physical_address);
    
    if(globals.fuzzing && physical_address < context->physical_memory_size){
        
        u64 page_index = physical_address >> 12;
        u64 byte_index = page_index >> 3;
        u64 bit_index  = page_index & 7;
        
        u64 bit = 1ull << bit_index;
        
        int page_is_dirty = (context->physical_memory_dirty[byte_index] & bit) != 0;
        
        if(!page_is_dirty){
            context->physical_memory_dirty[byte_index] |= bit;
            
            assert(context->amount_of_dirty_physical_pages < DIRTY_PHYSICAL_PAGE_CAPACITY);
            context->dirty_physical_pages[context->amount_of_dirty_physical_pages++] = physical_address & ~0xfff;
            
            // @note: We use 0x100 as an arbitrary "epsilon"... We need to at least mark this page still as dirty.
            if(context->amount_of_dirty_physical_pages > DIRTY_PHYSICAL_PAGE_CAPACITY - 0x100){
                // @note: Abuse of the CRASH_timeout value, maybe I should rename it into CRASH_reset,
                //        or make another value, or alias?
                //        We want the same behaviour as a timeout, don't save the inpu etc.
                set_crash_information(context, CRASH_timeout, (u64)"Dirty Page overflow.");
            }
        }
    }
    
    return ret;
}

//_____________________________________________________________________________________________________________________
// Extra permissions

void *get_or_allocate_extra_permissions_for_page(struct context *context, u64 guest_virtual_page_number){
    u32 page_indices[4] = {
        (guest_virtual_page_number >> (39 - 12)) & 0x1ff,
        (guest_virtual_page_number >> (30 - 12)) & 0x1ff,
        (guest_virtual_page_number >> (21 - 12)) & 0x1ff,
        (guest_virtual_page_number >> (12 - 12)) & 0x1ff,
    };
    
    u64 *table = context->extra_permission_page_table;
    for(u32 page_table_index = 0; page_table_index < array_count(page_indices); page_table_index++){
        u32 page_index = page_indices[page_table_index];
        
        if(!table[page_index]){
            table[page_index] = (u64)push_data(&context->fuzz_run_arena, u64, 0x200);
        }
        
        table = (u64 *)table[page_index];
    }
    
    return table;
}


void *get_extra_permissions_for_page(struct context *context, u64 guest_virtual_page_number){
    u32 page_indices[4] = {
        (guest_virtual_page_number >> (39 - 12)) & 0x1ff,
        (guest_virtual_page_number >> (30 - 12)) & 0x1ff,
        (guest_virtual_page_number >> (21 - 12)) & 0x1ff,
        (guest_virtual_page_number >> (12 - 12)) & 0x1ff,
    };
    
    u64 *table = context->extra_permission_page_table;
    for(u32 page_table_index = 0; page_table_index < array_count(page_indices); page_table_index++){
        u32 page_index = page_indices[page_table_index];
        
        if(!table[page_index]) return null;
        
        table = (u64 *)table[page_index];
    }
    
    return table;
}

enum extra_permissions{
    EXTRA_PERMISSION_none,
    EXTRA_PERMISSION_allocation    = 0b00000001,
    EXTRA_PERMISSION_uninitialized = 0b00000010,
    EXTRA_PERMISSION_inaccessible  = 0b00000100,
};

void change_extra_permissions_for_range(struct context *context, u64 base_address, u64 size, u8 extra_permissions_to_add, u8 extra_permissions_to_remove){
    
#if IMPLEMENT_EXTRA_PERMISSIONS 
    u64 start_page_index  = base_address >> 12;
    u64 ending_page_index = (base_address + size - 1) >> 12;
    
    for(u64 page_index = start_page_index; page_index <= ending_page_index; page_index++){
        
        u8 *extra_permission_page = get_or_allocate_extra_permissions_for_page(context, page_index);
        
        u32 start_offset = (page_index == start_page_index)  ? (base_address          & 0xfff) : 0;
        u32 end_offset   = (page_index == ending_page_index) ? ((base_address + size-1) & 0xfff) : 0xfff;
        
        for(u32 offset = start_offset; offset <= end_offset; offset++){
            extra_permission_page[offset] |= extra_permissions_to_add;
            extra_permission_page[offset] &= ~extra_permissions_to_remove;
        }
        
        if(context->read_tlb.entries[page_index & array_count(context->read_tlb.entries)].virtual_page_number == page_index){
            context->read_tlb.entries[page_index & array_count(context->read_tlb.entries)].extra_permission_page = extra_permission_page;
        }
        
        if(context->write_tlb.entries[page_index & array_count(context->write_tlb.entries)].virtual_page_number == page_index){
            context->write_tlb.entries[page_index & array_count(context->write_tlb.entries)].extra_permission_page = extra_permission_page;
        }
        
        if(context->execute_tlb.entries[page_index & array_count(context->execute_tlb.entries)].virtual_page_number == page_index){
            context->execute_tlb.entries[page_index & array_count(context->execute_tlb.entries)].extra_permission_page = extra_permission_page;
        }
    }
#else 
    (void)context, (void)base_address, (void)size, (void)extra_permissions_to_add, (void)extra_permissions_to_remove;
#endif
}

//_____________________________________________________________________________________________________________________
// Virtual memory routines

// On x64 an address looks as follows:
//      0b1111111111111111100000000111111111000000000111111111000000000000 = 0xffff807fc01ff000
//        |     16       ||   9   ||   9   ||   9   ||   9   ||     12   | = 64
//        Sign extension  P4 table P3 table P2 Table P1 Table Page Offset
//
//        Each page table level has 2 ** 9 = 512 entries. The page offset is between 0 and 2 ** 12 = 0x1000 = 4096.
//        
//        Cr3 points to the physical address of P4. The entires of P4 are physical addresses of P3 page tables and so on.
//        Finally P1 entries are the physical addresses of the page.
//        
//        Each of these indirections also store some additional information in the form of bit fields:
//        0 - Present
//        1 - writable
//        2 - User accessible
//        3 - Write Through caching
//        4 - disable cache 
//        5 - accessed
//        6 - dirty
//        7 - huge page
//        8 - global
//        9, 10, 11 - Freely usable by the os
// These bits can be used, as all indirections have to be page aligned.
// 12,..., 51 Store the actual indirection.
// 52,..., 62 Are usable by the os.
// 63 - NX
// The latter ones are only usable, because x64 only allows for 52/48-bits of address space.

int address_is_non_canonical(u64 address){
    
    // 
    // The address is canonical, iff the first 16 bits are all the same.
    // We can check this by shifting the value up by 16 and then 
    // shifting it down again arithmetically.
    // 
    
    return address != (u64)((s64)(address << 16) >> 16);
}

// @cleanup: Use the global flag?

enum permissions{
    PERMISSION_none  = 0x0,
    PERMISSION_read  = 0x1,
    PERMISSION_write = 0x2,
    PERMISSION_execute = 0x4,
};

#define PAGE_TABLE_ENTRY_ADDRESS_MASK 0xffffffffff000

#define PAGE_TABLE_present         (1ull <<  0)  // 0x1
#define PAGE_TABLE_writable        (1ull <<  1)  // 0x2
#define PAGE_TABLE_user            (1ull <<  2)  // 0x4
#define PAGE_TABLE_accessed        (1ull <<  5)  // 0x20
#define PAGE_TABLE_dirty           (1ull <<  6)  // 0x40
#define PAGE_TABLE_large_page      (1ull <<  7)  // 0x80
#define PAGE_TABLE_execute_disable (1ull << 63)

// @cleanup: This wrapper is pretty useless now.
static u64 read_page_table_entry(struct context *context, u64 physical_address){
    
    // Make sure the address does not straddle a page boundary.
    assert((physical_address & ~0xfff) == ((physical_address + 7) & ~0xfff));
    
    return *(u64 *)get_physical_memory_for_read(context, physical_address);
}

void set_page_table_accessed_and_dirty_bit(struct context *context, u64 physical_address, u64 entry, u64 desired_bits){
    if((entry & desired_bits) != desired_bits){
        u64 *physical_memory = (u64 *)get_physical_memory_for_write(context, physical_address);
        *physical_memory |= desired_bits;
    }
}


u64 translate_page_number_to_physical(struct context *context, u64 page_number, enum permissions permissions, u64 *out_pte){
    
    *out_pte = 0;
    
    // "For any paging-structure entry that is used during linear-address translation, bit 5 is the accessed flag.
    //  For paging-structure entries that map a page (as opposed to referencing another paging structure), 
    //  bit 6 is the dirty flag."   
    // "Whenever the processor uses a paging-structure entry as part of linear-address translation, it sets the accessed
    //  flag in that entry (if it is not already set)."
    
    // "Whenever there is a write to a linear address, the processor sets the dirty flag (if it is not already set) in the paging-
    //  structure entry that identifies the final physical address for the linear address (either a PTE or a paging-structure
    //  entry in which the PS flag is 1)."
    
    // @note: I have observed that the accessed bits were not set when the translation failed.
    //        This could maybe also be a weird artifact of TLB state, but as the Hypervisor
    //        is single stepping, I think its correct CPU behavior.
    
    
    u32 p1_table_index = (page_number >>  0) & 0x1ff;
    u32 p2_table_index = (page_number >>  9) & 0x1ff;
    u32 p3_table_index = (page_number >> 18) & 0x1ff;
    u32 p4_table_index = (page_number >> 27) & 0x1ff;
    
    // "If the PCIDE bit in CR4 is set, the lowest 12 bits are used for the process-context identifier (PCID)."
    u64 page_table_root = (context->registers.cr3 & ~0xfff);
    u64 p4_table_entry_address = page_table_root + 8 * p4_table_index;
    u64 p4_entry = read_page_table_entry(context, p4_table_entry_address);
    if(!(p4_entry & PAGE_TABLE_present)) return 0;
    
    u64 p3_table_entry_address = (p4_entry & PAGE_TABLE_ENTRY_ADDRESS_MASK) + 8 * p3_table_index;
    u64 p3_entry = read_page_table_entry(context, p3_table_entry_address);
    if(!(p3_entry & PAGE_TABLE_present)) return 0;
    
    if(p3_entry & PAGE_TABLE_large_page){
        
        if((permissions & PERMISSION_write)   && !(p3_entry & PAGE_TABLE_writable))        return 0;
        if((permissions & PERMISSION_execute) &&  (p3_entry & PAGE_TABLE_execute_disable)) return 0;
        
        if(!context->skip_setting_permission_bits && permissions != PERMISSION_none){
            set_page_table_accessed_and_dirty_bit(context, p4_table_entry_address, p4_entry, PAGE_TABLE_accessed);
            set_page_table_accessed_and_dirty_bit(context, p3_table_entry_address, p3_entry, PAGE_TABLE_accessed | ((permissions & PERMISSION_write) ? PAGE_TABLE_dirty : 0));
        }
        
        *out_pte = p3_entry;
        u64 physical_address =  (p3_entry & PAGE_TABLE_ENTRY_ADDRESS_MASK) + (p2_table_index << 21) + (p1_table_index << 12);
        
        return physical_address;
    }
    
    u64 p2_table_entry_address = (p3_entry & PAGE_TABLE_ENTRY_ADDRESS_MASK) + 8 * p2_table_index;
    u64 p2_entry = read_page_table_entry(context, p2_table_entry_address);
    if(!(p2_entry & PAGE_TABLE_present)) return 0;
    
    if(p2_entry & PAGE_TABLE_large_page){
        
        if((permissions & PERMISSION_write)   && !(p2_entry & PAGE_TABLE_writable))        return 0;
        if((permissions & PERMISSION_execute) &&  (p2_entry & PAGE_TABLE_execute_disable)) return 0;
        
        if(!context->skip_setting_permission_bits && permissions != PERMISSION_none){
            set_page_table_accessed_and_dirty_bit(context, p4_table_entry_address, p4_entry, PAGE_TABLE_accessed);
            set_page_table_accessed_and_dirty_bit(context, p3_table_entry_address, p3_entry, PAGE_TABLE_accessed);
            set_page_table_accessed_and_dirty_bit(context, p2_table_entry_address, p2_entry, PAGE_TABLE_accessed | ((permissions & PERMISSION_write) ? PAGE_TABLE_dirty : 0));
        }
        
        *out_pte = p2_entry;
        u64 physical_address =  (p2_entry & PAGE_TABLE_ENTRY_ADDRESS_MASK) + (p1_table_index << 12);
        
        return physical_address;
    }
    
    u64 p1_table_entry_address = (p2_entry & PAGE_TABLE_ENTRY_ADDRESS_MASK) + 8 * p1_table_index;
    u64 p1_entry = read_page_table_entry(context, p1_table_entry_address);
    if(!(p1_entry & PAGE_TABLE_present)) return 0;
    
    if((permissions & PERMISSION_write)   && !(p1_entry & PAGE_TABLE_writable))        return 0;
    if((permissions & PERMISSION_execute) &&  (p1_entry & PAGE_TABLE_execute_disable)) return 0;
    
    if(!context->skip_setting_permission_bits && permissions != PERMISSION_none){
        set_page_table_accessed_and_dirty_bit(context, p4_table_entry_address, p4_entry, PAGE_TABLE_accessed);
        set_page_table_accessed_and_dirty_bit(context, p3_table_entry_address, p3_entry, PAGE_TABLE_accessed);
        set_page_table_accessed_and_dirty_bit(context, p2_table_entry_address, p2_entry, PAGE_TABLE_accessed);
        set_page_table_accessed_and_dirty_bit(context, p1_table_entry_address, p1_entry, PAGE_TABLE_accessed | ((permissions & PERMISSION_write) ? PAGE_TABLE_dirty : 0));
    }
    
    *out_pte = p1_entry;
    u64 physical_address = (p1_entry & PAGE_TABLE_ENTRY_ADDRESS_MASK);
    
    return physical_address;
}

u64 translate_rip_to_physical(struct context *context, u64 address, enum permissions permissions){
    
    u64 offset = address & 0xfff;
    u64 page_number = address >> 12;
    
    struct translation_lookaside_buffer_entry *tlb_entry = &context->execute_tlb.entries[page_number & (array_count(context->execute_tlb.entries) - 1)];
    
    if(page_number == tlb_entry->virtual_page_number){
        return (tlb_entry->host_page_address - context->physical_memory) + offset;
    }
    
    u64 pte = 0;
    u64 physical_address = translate_page_number_to_physical(context, page_number, permissions, &pte);
    
    if(!(pte & PAGE_TABLE_present)) return (u64)-1;
    
    tlb_entry->host_page_address   = get_physical_memory_for_read(context, physical_address);
    tlb_entry->virtual_page_number = page_number;
    
    return physical_address + offset;
}

void *translate_address(struct context *context, u64 address, enum permissions permissions){
    
    if(address_is_non_canonical(address)) return null;
    
    u64 pte = 0;
    u64 offset      = address & 0xfff;
    u64 page_number = address >> 12;
    
    u64 physical_address = translate_page_number_to_physical(context, page_number, permissions, &pte) + offset;
    
    if(!(pte & PAGE_TABLE_present)) return null;
    
    if(permissions & PERMISSION_write){
        return get_physical_memory_for_write(context, physical_address);
    }else{
        return get_physical_memory_for_read(context, physical_address);
    }
}

//_____________________________________________________________________________________________________________________
// Reading, writing, executing guest virtual memory.

// Predefine because we want the breakpoint API to be in 'debugger.c'.
int check_breakpoint(enum breakpoint_type type, u64 address, u64 size);

// Predefine because we want the API to be in `target_specific_code_api.h`.
int target_read_guest_input_buffer(struct context *context, u64 virtual_address, u8 *buffer, u64 size);

static void maybe_crash_or_reset_jit_on_self_modifying_code(struct context *context, u64 physical_address){
    // 
    // @note: we have to range-check here as the framebuffer is not in range of the physical memory.
    //        Maybe its a good idea anyway, as the page table entries might be corrupted or something.
    // 
    if((physical_address < context->physical_memory_size) && _bittest((void *)context->physical_memory_executed, (u32)(physical_address/0x1000))){
        // 
        // If we have executed this address already, and now we are writing to it, reset the jit.
        // 
        
        if(CRASH_ON_SELF_MODIFYING_CODE_DURING_FUZZING && globals.fuzzing){
            // 
            // @WARNING:
            //     Currently, these do not repro, as we keep the 'physical_memory_executed' array around and do not reset it each fuzz-case.
            //     Just like we don't throw away the jit. This means while repro'ing the physical_memory_executed will be different than it is while fuzzing.
            // 
            set_crash_information(context, CRASH_internal_error, (u64)"Writting memory which was already executed.");
        }else{
            u64 pte;
            if(physical_address == translate_page_number_to_physical(context, context->registers.rip >> 12, PERMISSION_none, &pte)){
                if(!context->force_one_instruction){
                    set_crash_information(context, CRASH_self_modifying_code, 0);
                }
            }else{
                set_crash_information(context, CRASH_reset_jit, 0);
            }
        }
    }
}


// Returns 1 on success, 0 on crash.
// Can be used to _read for write_ for instructions like 'add [rax], rcx'.
int guest_read_size(struct context *context, void *_buffer, u64 address, u64 size, enum permissions required_permissions){
    
    // 
    // @note: If we are not setting permission bits, we cannot cache this page in the TLB,
    //        otherwise, the permission bits might not get set, next time we access the page
    //        and should set permission bits.
    // 
    int do_not_save_translated_address_in_tlb = (required_permissions == PERMISSION_none) || context->skip_setting_permission_bits;
    
    if(globals.debugger_mode && globals.breakpoint_count != 0){
        
        // @note: The breakpoint type needs to match the tlb we are using, 
        //        otherwise we could populate the write_tlb even though there is a write breakpoint there.
        enum breakpoint_type breakpoint_type = (required_permissions & PERMISSION_write) ? BREAKPOINT_write : BREAKPOINT_read;
        
        if(context->jit_skip_one_breakpoint){
            // Makes sure we enter this function on any read of this page.
            if(check_breakpoint(breakpoint_type, (address & ~0xfff), 0x1000)) do_not_save_translated_address_in_tlb = 1;
        }else{
            
            if(check_breakpoint(breakpoint_type, (address & ~0xfff), 0x1000)){
                if(check_breakpoint(breakpoint_type, address, size)){
                    set_crash_information(context, CRASH_enter_debugger, 0);
                    return 0;
                }
                
                // Makes sure we enter this function on any read of this page.
                do_not_save_translated_address_in_tlb = 1;
            }
        }
    }
    
    u8 *buffer = _buffer;
    
    if(address_is_non_canonical(address)){
        set_crash_information(context, CRASH_non_canonical, address);
        return 0;
    }
    
    u64 starting_page_number = address >> 12;
    u64 ending_page_number   = (address + size - 1) >> 12;
    
    if(starting_page_number == ending_page_number){
        //
        // The range does not straddle a page boundary.
        //
        
        struct translation_lookaside_buffer *tlb = (required_permissions & PERMISSION_write) ? &context->write_tlb : &context->read_tlb;
        
        struct translation_lookaside_buffer_entry *tlb_entry = &tlb->entries[starting_page_number & (array_count(context->read_tlb.entries) - 1)];
        
        u8 *host_page_address;
        u8 *extra_permission_page;
        
        if(starting_page_number == tlb_entry->virtual_page_number){
            //
            // Our "TLB" hit! Read from the cached page!
            //
            host_page_address     = tlb_entry->host_page_address;
            extra_permission_page = tlb_entry->extra_permission_page;
        }else{
            // 
            // Our "TLB" missed! Translate the page and store it in the TLB.
            // 
            
            u64 pte = 0;
            u64 physical_address = translate_page_number_to_physical(context, starting_page_number, required_permissions, &pte);
            
            if(!(pte & PAGE_TABLE_present)){
                enum crash_type crash_type = (required_permissions & PERMISSION_write) ? CRASH_write : CRASH_read;
                set_crash_information(context, crash_type, address);
                return 0;
            }
            
            if(physical_address == /*APIC base*/0xfee00000){
                return local_apic_read(context, (address & 0xfff), buffer, size);
            }
            
            if(physical_address == /*IO APIC base*/0xfec00000){
                return io_apic_read(context, (address & 0xfff), buffer, size);
            }
            
            if(physical_address == globals.input_buffer_physical_address){
                return target_read_guest_input_buffer(context, address, buffer, size);
            }
            
            extra_permission_page = get_extra_permissions_for_page(context, starting_page_number);
            host_page_address     = (required_permissions & PERMISSION_write) ? get_physical_memory_for_write(context, physical_address) : get_physical_memory_for_read(context, physical_address);
            
            if(required_permissions & PERMISSION_write){
                maybe_crash_or_reset_jit_on_self_modifying_code(context, physical_address);
                if(context->crash) return 0; // It crashed, fail the read.
            }
            
            if(!do_not_save_translated_address_in_tlb){
                tlb_entry->host_page_address     = host_page_address;
                tlb_entry->virtual_page_number   = starting_page_number;
                tlb_entry->extra_permission_page = extra_permission_page;
            }
        }
        
        if(extra_permission_page){
            for(u32 index = 0; index < size; index++){
                u32 offset = (address & 0xfff) + index;
                
                if(extra_permission_page[offset] & EXTRA_PERMISSION_inaccessible){
                    set_crash_information(context, CRASH_out_of_bounds_read, address + index);
                    return 0;
                }
            }
        }
        
        memcpy(buffer, host_page_address + (address & 0xfff), size);
        
        return 1;
    }
    
    u64 end_address = address + size;
    
    while(address < end_address){
        u64 page_end = (address + 0x1000) & ~0xfff;
        u64 end = (end_address < page_end) ? end_address : page_end;
        u64 size_to_read = end - address;
        
        int success = guest_read_size(context, buffer, address, size_to_read, required_permissions);
        if(!success) return 0;
        
        address += size_to_read;
        buffer  += size_to_read;
    }
    
    return 1;
}

//
// Ignore the crash and just return the buffer, this means we can cast on the other side!
//
void *guest_read_(struct context *context, void *buffer, u64 address, u64 size){
    guest_read_size(context, buffer, address, size, PERMISSION_read); 
    return buffer;
}
#define guest_read(type, guest_address) (*(type *)guest_read_(context, &(u8[sizeof(type)]){0}, guest_address, sizeof(type)))

void *guest_read_for_write_(struct context *context, void *buffer, u64 address, u64 size){
    guest_read_size(context, buffer, address, size, PERMISSION_read | PERMISSION_write); 
    return buffer;
}

// returns 'success'.
int guest_write_size(struct context *context, void *_buffer, u64 address, u64 size){
    
    // 
    // @note: If we are not setting permission bits, we cannot cache this page in the TLB,
    //        otherwise, the permission bits might not get set, next time we access the page
    //        and should set permission bits.
    // 
    int do_not_save_translated_address_in_tlb = context->skip_setting_permission_bits;
    
    if(globals.debugger_mode && globals.breakpoint_count != 0){
        if(context->jit_skip_one_breakpoint){
            // Makes sure we enter this function on any write of this page.
            if(check_breakpoint(BREAKPOINT_write, (address & ~0xfff), 0x1000)) do_not_save_translated_address_in_tlb = 1;
        }else{
            
            if(check_breakpoint(BREAKPOINT_write, (address & ~0xfff), 0x1000)){
                
                if(check_breakpoint(BREAKPOINT_write, address, size)){
                    set_crash_information(context, CRASH_enter_debugger, 0);
                    return 0;
                }
                
                // Makes sure we enter this function on any write of this page.
                do_not_save_translated_address_in_tlb = 1;
            }
        }
    }
    
    u8 *buffer = _buffer;
    
    if(address_is_non_canonical(address)){
        set_crash_information(context, CRASH_non_canonical, address);
        return 0;
    }
    
    u64 starting_page_number = address >> 12;
    u64 ending_page_number   = (address + size - 1) >> 12;
    
    if(starting_page_number == ending_page_number){
        //
        // The range does not straddle a page boundary.
        //
        
        struct translation_lookaside_buffer *tlb = &context->write_tlb;
        struct translation_lookaside_buffer_entry *tlb_entry = &tlb->entries[starting_page_number & (array_count(context->write_tlb.entries) - 1)];
        
        u8 *host_page_address;
        u8 *extra_permission_page;
        
        if(starting_page_number == tlb_entry->virtual_page_number){
            //
            // Our "TLB" hit! Write to the cached page!
            //
            host_page_address     = tlb_entry->host_page_address;
            extra_permission_page = tlb_entry->extra_permission_page;
        }else{
            // 
            // Our "TLB" missed! Translate the page and store it in the TLB.
            // 
            
            enum permission permission = PERMISSION_write;
            
            if((context->registers.cr0 & /*Write Protect*/(1 << 16)) == 0){
                do_not_save_translated_address_in_tlb = 1;
                permission = PERMISSION_read;
            }
            
            
            u64 pte = 0;
            u64 physical_address = translate_page_number_to_physical(context, starting_page_number, permission, &pte);
            
            if(!(pte & PAGE_TABLE_present)){
                set_crash_information(context, CRASH_write, address);
                return 0;
            }
            
            if(physical_address == /*APIC base*/0xfee00000){
                return local_apic_write(context, (address & 0xfff), buffer, size);
            }
            
            if(physical_address == /*IO APIC base*/0xfec00000){
                return io_apic_write(context, (address & 0xfff), buffer, size);
            }
            
            maybe_crash_or_reset_jit_on_self_modifying_code(context, physical_address);
            if(context->crash) return 0; // It crashed, fail the write.
            
            extra_permission_page = get_extra_permissions_for_page(context, starting_page_number);
            host_page_address     = get_physical_memory_for_write(context, physical_address);
            
            if(!do_not_save_translated_address_in_tlb){
                tlb_entry->host_page_address   = host_page_address;
                tlb_entry->virtual_page_number = starting_page_number;
                tlb_entry->extra_permission_page = extra_permission_page;
            }
        }
        
        if(extra_permission_page){
            for(u32 index = 0; index < size; index++){
                u32 offset = (address & 0xfff) + index;
                
                if(extra_permission_page[offset] & EXTRA_PERMISSION_inaccessible){
                    set_crash_information(context, CRASH_out_of_bounds_write, address + index);
                    return 0;
                }
            }
        }
        
        memcpy(host_page_address + (address & 0xfff), buffer, size);
        return 1;
    }

    u64 end_address = address + size;
    
    while(address < end_address){
        u64 page_end = (address + 0x1000) & ~0xfff;
        u64 end = (end_address < page_end) ? end_address : page_end;
        u64 size_to_write = end - address;
        
        int success = guest_write_size(context, buffer, address, size_to_write);
        if(!success) return 0;
        
        address += size_to_write;
        buffer  += size_to_write;
    }
    
    return 1;
}

void guest_write_(struct context *context, u64 address, u64 size, u64 value){
    assert(size <= 8);
    
    guest_write_size(context, (char *)&value, address, size);
}
#define guest_write(type, guest_address, value) guest_write_(context, guest_address, sizeof((type){0}), value)

// Does not care about permissions.
int guest_force_write(struct context *context, void *_buffer, u64 address, u64 size){
    u8 *buffer = _buffer;
    
    u64 end_address = address + size;
    while(address < end_address){
        u64 page_end = (address + 0x1000) & ~0xfff;
        u64 end = (end_address < page_end) ? end_address : page_end;
        u64 size_to_write = end - address;
        
        u64 pte = 0;
        u64 physical_address = translate_page_number_to_physical(context, address >> 12, PERMISSION_none, &pte);
        if(!(pte & PAGE_TABLE_present)) return 0; // @cleanup: return size written?
        
        u8 *page = get_physical_memory_for_write(context, physical_address);
        u8 *dest = page + (address & 0xfff);
        memcpy(dest, buffer, size);
        
        address += size_to_write;
        buffer  += size_to_write;
    }
    
    return 1;
}

static u32 prefetch_instruction(struct context *context, u64 address, u8 *instruction_buffer, u32 size){
    
    if(address_is_non_canonical(address)) return 0;
    
    u64 starting_page_number = address >> 12;
    u64 ending_page_number   = (address + size - 1) >> 12;
    
    if(starting_page_number == ending_page_number){
        //
        // The range does not straddle a page boundary.
        //
        struct translation_lookaside_buffer_entry *tlb_entry = &context->execute_tlb.entries[starting_page_number & (array_count(context->execute_tlb.entries) - 1)];
        
        if(starting_page_number == tlb_entry->virtual_page_number){
            //
            // Our "TLB" hit! Read from the cached page!
            //
            
            memcpy(instruction_buffer, tlb_entry->host_page_address + (address & 0xfff), size);
            return size;
        }
        
        u64 pte = 0;
        u64 physical_address = translate_page_number_to_physical(context, starting_page_number, PERMISSION_execute, &pte);
        
        if(!(pte & PAGE_TABLE_present)) return 0;
        
        u8 *translated = get_physical_memory_for_read(context, physical_address);
        memcpy(instruction_buffer, translated + (address & 0xfff), size);
        
        tlb_entry->host_page_address     = translated;
        tlb_entry->virtual_page_number   = starting_page_number;
        
        return size;
    }
    
    assert(size < 0x1000);
    
    u32 size_in_first_page = 0x1000 - (address & 0xfff);
    
    u32 size_read_from_first_page = prefetch_instruction(context, address, instruction_buffer, size_in_first_page);
    if(!size_read_from_first_page) return 0;
    
    u64 next_page_address = address + size_read_from_first_page;
    u8 *buffer = instruction_buffer + size_read_from_first_page;
    u32 rest_size = size - size_read_from_first_page;
    
    u32 size_read_from_second_page = prefetch_instruction(context, next_page_address, buffer, rest_size);
    
    return size_read_from_first_page + size_read_from_second_page;
}

