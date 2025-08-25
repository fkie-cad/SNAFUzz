
//_____________________________________________________________________________________________________________________
// Utilities.

void load_input_directory(char *directory_path){ // @cleanup: How should we handle failiure.
    
#if _WIN32
    struct win32_find_data find_data;
    
    char buffer[/*MAX_PATH*/260 + 1];
    snprintf(buffer, sizeof(buffer), "%s\\*", directory_path);
    
    HANDLE find_handle = FindFirstFileA(buffer, &find_data);
    
    if(find_handle.Unused == /*INVALID_HANDLE_VALUE*/(u64)-1){
        print("Error: Input corpus directory '%s' does not exist.\n", directory_path);
        _exit(1);
    }
    
    print("loading %s:\n", directory_path);
    do{
        if(!(find_data.file_attributes & /*FILE_ATTRIBUTE_DIRECTORY*/0x10)){
            
            print("    %s\n", find_data.file_name);
            
            snprintf(buffer, sizeof(buffer), "%s/%s", directory_path, find_data.file_name);
            
            struct file file = load_file(buffer);
            if(!file.memory){
                print("    -> Warning: Failed to load it.\n");
            }else{
                struct input input = {
                    .data = file.data,
                    .size = file.size,
                };
                
                add_input(input);
            }
        }
    } while(FindNextFileA(find_handle, &find_data));
    
    FindClose(find_handle);
#else
    DIR *dir = opendir(directory_path);
    if(!dir){
        print("Error: Input corpus directory '%s' does not exist.\n", directory_path);
        exit(1);
    }
    
    struct dirent *entry;
    char buffer[PATH_MAX];
    
    printf("loading %s:\n", directory_path);
    
    while ((entry = readdir(dir))) {
        // Skip directories ("." and ".." as well as others)
        snprintf(buffer, sizeof(buffer), "%s/%s", directory_path, entry->d_name);
        
        struct stat file_stat;
        if (stat(buffer, &file_stat) == 0 && S_ISREG(file_stat.st_mode)) {
            printf("    %s\n", entry->d_name);
            
            struct file file = load_file(buffer);
            if (!file.memory) {
                printf("    -> Warning: Failed to load it.\n");
            } else {
                struct input input = {
                    .data = file.data,
                    .size = file.size,
                };
                add_input(input);
            }
        }
    }
    
    closedir(dir);
#endif
}

void apply_simple_mutations(struct input input, u64 guest_input_buffer_base, u64 *seed){
    
    // Mutate round about 8% of the input.
    u32 bytes_to_mutate = (u32)(0.08 * input.size) + 1;
    
    if(input.size < 8){
        if(!input.size) return;
        
        // @note: For small inputs we only change bytes.
        
        for(u32 mutation = 0; mutation < bytes_to_mutate; mutation++){
            switch(xor_shift(seed) & 0x7){
                case 0:{ // flip a bit
                    u64 bit_index  = xor_shift(seed) & 7;
                    u64 byte_index = xor_shift(seed) % input.size;
                    input.data[byte_index] ^= (1 << bit_index);
                }break;
                case 1:{ // change a byte
                    u64 byte_index = xor_shift(seed) % input.size;
                    input.data[byte_index] = (u8)xor_shift(seed);
                }break;
                case 2:{ // increment a byte
                    u64 byte_index = xor_shift(seed) % input.size;
                    input.data[byte_index]++;
                }break;
                case 3:{ // decrement a byte
                    u64 byte_index = xor_shift(seed) % input.size;
                    input.data[byte_index]--;
                }break;
                case 4:{ // write zero bytes
                    u64 byte_index = xor_shift(seed) % input.size;
                    input.data[byte_index] = 0;
                }break;
                case 5:{ // flipp bytes
                    u64 byte_index = xor_shift(seed) % input.size;
                    input.data[byte_index] ^= 0xff;
                }break;
                case 6:{ // write -1 bytes
                    u64 byte_index = xor_shift(seed) % input.size;
                    input.data[byte_index] = (u8)-1;
                }break;
                case 7:{ // repeat a byte
                    u64 byte_index1 = xor_shift(seed) % input.size;
                    u64 byte_index2 = xor_shift(seed) % input.size;
                    
                    input.data[byte_index1] = input.data[byte_index2];
                }break;
            }
        }
        
        return;
    }
    
    for(u32 mutation = 0; mutation < bytes_to_mutate; mutation++){
        switch(xor_shift(seed) & 0xf){
            case 0:{ // flip a bit
                u64 bit_index  = xor_shift(seed) & 7;
                u64 byte_index = xor_shift(seed) % input.size;
                input.data[byte_index] ^= (1 << bit_index);
            }break;
            case 1:{ // change a byte
                u64 byte_index = xor_shift(seed) % input.size;
                input.data[byte_index] = (u8)xor_shift(seed);
                
            }break;
            case 2:{ // write a low u32 (a lot of things in the kernel appear to be low u32's)
                if(input.size > 4){
                    u64 dword_index = xor_shift(seed) % (input.size - 3);
                    *(u32 *)(input.data + dword_index) = xor_shift(seed) % ((xor_shift(seed) & 0x3f) + 1);
                }
            }break;
            
            case 3:{ // add an input buffer address
                u64 qword_offset = xor_shift(seed) % (input.size - 7);
                *(u64 *)(input.data + qword_offset) = (u64)(guest_input_buffer_base + (xor_shift(seed) % input.size));
            }break;
            
            case 4:{ // increment a byte
                u64 byte_index = xor_shift(seed) % input.size;
                input.data[byte_index]++;
            }break;
            case 5:{ // decrement a byte
                u64 byte_index = xor_shift(seed) % input.size;
                input.data[byte_index]--;
            }break;
            
            case 6:{ // add a handle
                u64 qword_offset = xor_shift(seed) % (input.size - 7);
                // add an input buffer address
                *(u64 *)(input.data + qword_offset) = xor_shift(seed) & 0xff;
            }break;
            
            case 7:{// write a low u64 (a lot of things in the kernel appear to be low u64's)
                u64 qword_offset = xor_shift(seed) % (input.size - 7);
                *(u32 *)(input.data + qword_offset) = xor_shift(seed) % ((xor_shift(seed) & 0x3f) + 1);
            }break;
            
            case 8:{ // write zero bytes
                u64 byte_index = xor_shift(seed) % input.size;
                input.data[byte_index] = 0;
            }break;
            case 9:{ // write zero u16
                u64 byte_index = xor_shift(seed) % (input.size - 1);
                *(u16 *)(input.data + byte_index) = 0;
            }break;
            case 10:{ // write zero u32
                u64 byte_index = xor_shift(seed) % (input.size - 3);
                *(u32 *)(input.data + byte_index) = 0;
            }break;
            case 11:{ // write zero u64
                u64 byte_index = xor_shift(seed) % (input.size - 7);
                *(u64 *)(input.data + byte_index) = 0;
            }break;
            
            case 12:{ // flipp bytes
                u64 byte_index = xor_shift(seed) % input.size;
                input.data[byte_index] ^= 0xff;
            }break;
            
            case 13:{ // write -1 bytes
                u64 byte_index = xor_shift(seed) % input.size;
                input.data[byte_index] = (u8)-1;
            }break;
            
            case 14:{ // write -1 u32
                u64 byte_index = xor_shift(seed) % (input.size - 3);
                *(u32 *)(input.data + byte_index) = (u32)-1;
            }break;
            
            case 15:{ // repeat a byte
                u64 byte_index1 = xor_shift(seed) % input.size;
                u64 byte_index2 = xor_shift(seed) % input.size;
                
                input.data[byte_index1] = input.data[byte_index2];
            }break;
            
            invalid_default_case();
        }
    }
}

//_____________________________________________________________________________________________________________________
// Core allocation tracking helpers.

void guest_free__inner(struct context *context, u64 allocated_address){
    
    u64 page_index   = allocated_address >> 12;
    u32 start_offset = allocated_address & 0xfff;
    
    //
    // @note: Linearly scan for extra permissions which are marked 'EXTRA_PERMISSION_allocation'.
    //        Stop if we hit a page boundary, as I don't think allocations ever span page boundaries, 
    //        if they are not big allocations. For big allocations only handling the first page seems fine.
    //
    u8 *extra_permission_page = get_extra_permissions_for_page(context, page_index);
    u32 offset = start_offset;
    
    if(extra_permission_page){
        for(; offset < 0x1000; offset++){
            if(!(extra_permission_page[offset] & EXTRA_PERMISSION_allocation)) break;
            
            if(extra_permission_page[offset] & EXTRA_PERMISSION_inaccessible){
                set_crash_information(context, CRASH_double_free, allocated_address + offset);
            }
            
            extra_permission_page[offset] |= EXTRA_PERMISSION_inaccessible;
        }
    }
    
    u32 size = offset - start_offset;
    
    // If we did not track the allocation, still report the free as a free of one byte.
    if(!size) size = 1;
    if(check_breakpoint(BREAKPOINT_free, allocated_address, size)) set_crash_information(context, CRASH_enter_debugger, allocated_address);
}

static void simulate_allocation_failure(struct context *context, struct registers *registers, int raise_on_failure){
    
    if(raise_on_failure){
        // We should Raise a status instead.
        static u64 ExRaiseStatus;
        if(!ExRaiseStatus) ExRaiseStatus = get_symbol(context, string("nt!RtlRaiseStatus"));
        
        registers->rcx = 0xc000009a;
        registers->rip = ExRaiseStatus;
        return;
    }
    
    //
    // Simulate a ret.
    //
    registers->rax = 0;
    registers->rip = guest_read(u64, registers->rsp);
    registers->rsp += 8;
    return;
}

// @cleanup: This is a bit wasteful, because it assumes it has to work by kernel rules, but whatever.
void guest_allocate__inner(struct context *context, struct registers *registers, u64 NumberOfBytes, u64 alignment, int raise_on_failure, int initialized){
    
    if(!globals.fuzzing) return; // Prior to fuzzing we want all allocations to be handled by the guest.
    
#if !DETECT_ONE_BYTE_OUT_OF_BOUNDS
    // Align the allocation size to a 16-byte boundary.
    NumberOfBytes = (NumberOfBytes + 0xf) & ~0xf;
#endif
    
    
#ifdef FUZZING_ALLOCATION_LIMIT
    if(NumberOfBytes > FUZZING_ALLOCATION_LIMIT){
        simulate_allocation_failure(context, registers, raise_on_failure);
        return;
    }
#endif
    
    // 
    // Allocate the POOL_HEADER
    // 
    if(context->big_allocation_at + 0x10 > FUZZING_BIG_ALLOCATION_SIZE){
        set_crash_information(context, CRASH_internal_error, (u64)"Hit allocation ceiling.");
        return;
    }
    context->big_allocation_at += 0x10;
    
    if(NumberOfBytes >= 0x1000 && (alignment < 0x1000)){
        // If NumberOfBytes is PAGE_SIZE or greater, a page-aligned buffer is allocated.
        alignment = 0x1000;
    }
    
    if(NumberOfBytes < 0x1000){
        // Memory allocations of PAGE_SIZE or less do not cross page boundaries.
        if((context->big_allocation_at & ~0xfff) != ((context->big_allocation_at + NumberOfBytes) & ~0xfff)){
            context->big_allocation_at = (context->big_allocation_at + 0xfff) & ~0xfff;
        }
    }
    
    context->big_allocation_at = (context->big_allocation_at + (alignment - 1)) & ~(alignment - 1);
    
    if(context->big_allocation_at + NumberOfBytes > FUZZING_BIG_ALLOCATION_SIZE){
        set_crash_information(context, CRASH_internal_error, (u64)"Hit allocation ceiling.");
        return;
    }
    
    u64 allocated_address = globals.big_allocation_base + context->big_allocation_at;
    u64 end_address = allocated_address + NumberOfBytes;
    
    registers->rax = allocated_address;
    registers->rip = guest_read(u64, registers->rsp);
    registers->rsp += 8;
    
    change_extra_permissions_for_range(context, allocated_address-0x10, 0x10, /*add*/0, /*remove*/EXTRA_PERMISSION_inaccessible);
    if(initialized){
        change_extra_permissions_for_range(context, allocated_address, NumberOfBytes, /*add*/EXTRA_PERMISSION_allocation, /*remove*/EXTRA_PERMISSION_inaccessible);
    }else{
        change_extra_permissions_for_range(context, allocated_address, NumberOfBytes, /*add*/EXTRA_PERMISSION_uninitialized | EXTRA_PERMISSION_allocation, /*remove*/EXTRA_PERMISSION_inaccessible);
        
        // For now we don't do uninitialized memory tracking, but let's at least memset it to 0xcd
        
        for(u64 page_index = (allocated_address >> 12); page_index <= (end_address >> 12); page_index += 1){
            
            u32 start_offset = (page_index == (allocated_address >> 12)) ? (allocated_address & 0xfff) : 0;
            u32 end_offset   = (page_index == (end_address >> 12)) ? (end_address & 0xfff) : 0x1000;
            
            u8 *page = translate_address(context, page_index << 12, PERMISSION_write);
            memset(page + start_offset, 0xcd, end_offset - start_offset);
        }
    }
    change_extra_permissions_for_range(context, end_address, 0x10, EXTRA_PERMISSION_inaccessible, /*remove*/0);
    
    context->big_allocation_at += NumberOfBytes + 0x10;
    
    if(NumberOfBytes == 0) NumberOfBytes = 1; // Ensure we can break on zero-byte allocations.
    if(check_breakpoint(BREAKPOINT_alloc, allocated_address, NumberOfBytes)) set_crash_information(context, CRASH_enter_debugger, allocated_address);
    
    // @note: We use the 16-byte before the allocation to track the size.
    //        We allocated this space for the '_POOL_HEADER'.
    guest_write(u64, allocated_address - 8, NumberOfBytes);
}


//_____________________________________________________________________________________________________________________
// Core kernel mode hooks.

void hook_bugcheck(struct context *context, struct registers *registers){
    set_crash_information(context, CRASH_bugcheck, registers->rip);
    
    // On a general bugcheck, we set the return address as the rip, so the crash rip is more _unique_.
    // If its an access fault, we parse the parameters outside, in this case rip does not matter!
    registers->rip = guest_read(u64, registers->rsp);
    registers->rsp += 8;
}

void register_bugcheck_hooks(struct context *context){
    u64 KeBugCheck   = get_symbol(context, string("nt!KeBugCheck"));
    u64 KeBugCheck2  = get_symbol(context, string("nt!KeBugCheck2"));
    u64 KeBugCheckEx = get_symbol(context, string("nt!KeBugCheckEx"));
    register_hook(context, KeBugCheck,   hook_bugcheck);
    register_hook(context, KeBugCheck2,  hook_bugcheck);
    register_hook(context, KeBugCheckEx, hook_bugcheck);
}


void hook_return_one(struct context *context, struct registers *registers){
    registers->rax = 1;
    registers->rip = guest_read(u64, registers->rsp);
    registers->rsp += 8;
}

void hook_allocate_pool_type(struct context *context, struct registers *registers){
    
    if(!globals.fuzzing) return;
    
    // @note: 0x400 is zero, which we could also use and pass as initialized...
    
    smm allowed_flags = 
            /*POOL_PAGED*/1 | 
            /*POOL_CACHE_ALIGN*/4 | 
            /*POOL_QUOTA_FAIL_INSTEAD_OF_RAISE*/8 | 
            /*POOL_RAISE_IF_ALLOCATION_FAILURE*/0x10 | 
            /*POOL_TYPE_SESSION*/0x20 | 
            /*POOL_COLD_ALLOCATION*/0x100 | 
            /*POOL_NX_ALLOCATION*/0x200 | 
            /*POOL_ZERO_ALLOCATION*/0x400;
    
    if((registers->rcx & allowed_flags) != registers->rcx) return;
    
    u64 alignment = 0x10;
    
    if(registers->rcx & /*POOL_TYPE_CACHE_ALIGN*/4) alignment = 0x40;
    
    u64 NumberOfBytes = registers->rdx;
    int raise_on_failure = (registers->rcx & /*POOL_TYPE_RAISE_ON_FAILIURE*/0x10);
    int initialized = (registers->rcx & /*POOL_ZERO_ALLOCATION*/0x400);
    guest_allocate__inner(context, registers, NumberOfBytes, alignment, raise_on_failure, initialized);
}

void hook_allocate_pool_flags(struct context *context, struct registers *registers){
    
    if(!globals.fuzzing) return;
    
    // Don't hook if a reserved flag is set.
    smm allowed_flags = /*POOL_FLAG_USE_QUOTA*/1 | /*POOL_FLAG_UNINITIALIZED*/2 | /*POOL_FLAG_SESSION*/4 | /*POOL_FLAG_CACHE_ALIGN*/8
            | /*POOL_FLAG_RAISE_ON_FAILIURE*/0x20 | /*POOL_FLAG_NON_PAGED*/0x40 | /*POOL_FLAG_PAGED*/0x100;
    
    if((registers->rcx & allowed_flags) != registers->rcx) return;
    
    //
    // This is hook is supposed to go on 'nt!ExAllocateHeapPool' which is the internal allocation function.
    // It expects the size to be the second parameter.
    // 
    
    // Assume:
    //     rcx = POOL_FLAGS
    //     rdx = NumberOfBytes
    
    u64 NumberOfBytes = registers->rdx;
    
    u64 alignment = 0x10;
    
    if(registers->rcx & /*POOL_FLAG_CACHE_ALIGN*/8) alignment = 0x40;
    int raise_on_failure = (registers->rcx & /*POOL_FLAG_RAISE_ON_FAILIURE*/0x20);
    int initialized = !(registers->rcx & /*POOL_FLAG_UNINITIALIZED*/2);
    
    guest_allocate__inner(context, registers, NumberOfBytes, alignment, raise_on_failure, initialized);
}

void hook_kernel_free(struct context *context, struct registers *registers){
    
    u64 allocated_address = registers->rcx;
    if(PRINT_HOOK_EVENTS) print("[" __FUNCTION__ "] %p\n", allocated_address);
    
    {
        //
        // Simulate a return from the free, as we never want to actually free memory.
        // While this does change the behavior, it makes us catch use-after-free's
        // and double free's reliably.
        // 
        registers->rip = guest_read(u64, registers->rsp);
        registers->rsp += 8;
    }
    
    guest_free__inner(context, allocated_address);
}

void register_kernel_memory_allocation_hooks(struct context *context){
    
    //
    // Register hooks for tracking crashes and Memory allocations.
    //
    
    {
        // 
        // Use ExAllocate2 to allocate a big buffer.
        // We are going to use this buffer to do linear allocations instead of calling into 'ExAllocateHeapPool'.
        // 
        
        struct registers registers = globals.snapshot.registers;
        assert((s64)registers.rip < 0); // We have to start in the kernel to do this... @cleanup: put this in a define or something?
        
        //
        // Allocate some space on the stack.
        // 0x20 for homing space, 0x8 for the return address. and then 0x18 for random stuff.
        //
        
        registers.rsp -= 0x40;
        
        //
        // Make sure rsp is aligned properly for just having _called_ a function.
        //
        
        if((registers.rsp & 0xf) == 0) registers.rsp -= 8;
        assert((registers.rsp & 0xf) == 8);
        
        guest_write(u64, registers.rsp, DEFAULT_RETURN_RIP);
        
        registers.rip = get_symbol(context, string("nt!ExAllocatePool2"));
        registers.rcx = /*POOL_FLAG_NON_PAGED*/0x40;
        registers.rdx = FUZZING_BIG_ALLOCATION_SIZE; // 100 Megabytes
        registers.r8  = 'HACK';
        
        context->registers = registers;
        struct crash_information execution_result = start_execution_jit(context);
        if(execution_result.crash_type || context->registers.rax == 0){
            print("Error: Initial big guest-allocation of 0x%llx failed.\n", FUZZING_BIG_ALLOCATION_SIZE);
            print("       We intended to use this memory to speed up heap allocations while fuzzing.\n");
            os_panic(1);
        }
        
        globals.big_allocation_base = context->registers.rax;
        
        // Reset the registers just in case.
        context->registers = globals.snapshot.registers;
    }
    
    u64 ExAllocateHeapPool = get_symbol(context, string("nt!ExAllocateHeapPool"));
    register_hook(context, ExAllocateHeapPool, hook_allocate_pool_type);
    
    u64 ExAllocatePoolWithTag = get_symbol(context, string("nt!ExAllocatePoolWithTag"));
    register_hook(context, ExAllocatePoolWithTag, hook_allocate_pool_type);
    
    u64 ExAllocatePool2 = get_symbol(context, string("nt!ExAllocatePool2"));
    register_hook(context, ExAllocatePool2, hook_allocate_pool_flags);
    
    u64 ExAllocatePool3 = get_symbol(context, string("nt!ExAllocatePool3"));
    register_hook(context, ExAllocatePool3, hook_allocate_pool_flags);
    
    u64 ExFreeHeapPool = get_symbol(context, string("nt!ExFreeHeapPool"));
    register_hook(context, ExFreeHeapPool, hook_kernel_free);
    
    u64 ExFreePoolWithTag = get_symbol(context, string("nt!ExFreePoolWithTag"));
    register_hook(context, ExFreePoolWithTag, hook_kernel_free);
    
    u64 ExReturnPoolQuota = get_symbol(context, string("nt!ExReturnPoolQuota"));
    register_hook(context, ExReturnPoolQuota, hook_return_one);
}

//_____________________________________________________________________________________________________________________
// Core user mode hooks.

// hook on ntdll!RtlUserThreadStart$filt$0.
void Unhandled_user_exception_hook(struct context *context, struct registers *registers){
    (void)registers;
    set_crash_information(context, CRASH_unhandled_exception, (u64)"[" __FUNCTION__ "]");
}

void register_user_crash_hooks(struct context *context){
    register_hook(context, get_symbol(context, string("ntdll!RtlReportFatalFailure")), Unhandled_user_exception_hook);
    register_hook(context, get_symbol(context, string("ntdll!RtlUserThreadStart$filt$0")), Unhandled_user_exception_hook);
    
    
    // @cleanup: There apperantly is a 'nt!KiRaiseAssertion' is that relevant?
    register_hook(context, get_symbol(context, string("nt!KiRaiseSecurityCheckFailureShadow")), Unhandled_user_exception_hook);
    register_hook(context, get_symbol(context, string("nt!KiRaiseSecurityCheckFailure")), Unhandled_user_exception_hook);
    
    
    {
        // Alright, this is sort of weird, we overwrite the return address of the function with the DEFAULT_RETURN_RIP, 
        // this means that unwinding will fail and we wont get to `RtlUserThreadStart$filt$0`.
        // Instead `ntdll!KiUserExceptionDispatcher` will call into `ntdll!NtRaiseException`, so we search for said call.
        
        u64 rip = get_symbol(context, string("ntdll!KiUserExceptionDispatcher"));
        u64 NtRaiseException = get_symbol(context, string("ntdll!NtRaiseException"));
        u8 buffer[0x100];
        guest_read_size(context, buffer, rip, sizeof(buffer), PERMISSION_none);
        
        int found = 0;
        
        for(u8 *at = buffer; at + 16 < buffer + sizeof(buffer); ){
            struct instruction_information inst = decode_instruction(at);
            at += inst.instruction_size;
            
            if(inst.augmented_opcode == 0xe8 && (rip + inst.instruction_size + (s32)inst.immediate) == NtRaiseException){
                found = 1;
                break;
            }
            
            rip += inst.instruction_size;
        }
        
        if(!found){
            print("%s: Warning: Could not find the call to ntdll!NtRaiseException in ntdll!KiUserExceptionDispatcher. Crashes with patched return address will not be recognized.\n", __FUNCTION__);
            yes_no_stop_point("Continue?", /*force*/0);
        }else{
            register_hook(context, rip, Unhandled_user_exception_hook);
        }
    }
}


void malloc_hook(struct context *context, struct registers *registers){
    
    if(registers->cr3 != globals.process_cr3) return;
    
    // void *malloc(size_t size);
    
    u64 size = registers->rcx;
    
    guest_allocate__inner(context, registers, size, /*alignement*/16, /*raise_on_failiure*/0, /*initiaized*/0);
    
    if(registers->rax != 0){
        // @note: We use the 16-byte before the allocation to track the size.
        //        'guest_allocate__inner' allocates this for the '_POOL_HEADER'...
        guest_write(u64, registers->rax - 8, size);
    }
}

void LocalAlloc_hook(struct context *context, struct registers *registers){
    
    if(registers->cr3 != globals.process_cr3) return;
    
    // HLOCAL LocalAlloc([in] UINT uFlags, [in] SIZE_T uBytes);
    
    u64 flags = registers->rcx;
    u64 size  = registers->rdx;
    guest_allocate__inner(context, registers, size, /*alignment*/16, /*raise_on_failiure*/0, /*initialized*/(flags & /*LMEM_ZEROINIT*/0x40) != 0);
    
    if(registers->rax != 0){
        guest_write(u64, registers->rax - 0x10, flags);
    }
}

void reallocate_copy(struct context *context, u64 source, u64 dest, u64 old_size, u64 new_size){
    
    u8 buffer[0x200];
    
    for(u64 size_copied = 0; !context->crash && (size_copied < old_size) && (size_copied < new_size); ){
        u64 old_size_left = old_size - size_copied;
        u64 new_size_left = new_size - size_copied;
        u64 size_left = old_size_left < new_size_left ? old_size_left : new_size_left;
        u64 size_to_copy = sizeof(buffer) < size_left  ? sizeof(buffer) : size_left;
        
        guest_read_size(context, buffer, source + size_copied, size_to_copy, PERMISSION_read);
        guest_write_size(context, buffer, dest + size_copied, size_to_copy);
        
        size_copied += size_to_copy;
    }
}

void realloc_hook(struct context *context, struct registers *registers){
    
    if(registers->cr3 != globals.process_cr3) return;
    
    // void *realloc(void *ptr, size_t new_size);
    
    u64 ptr = registers->rcx;
    u64 new_size = registers->rdx;
    
    if(ptr == 0){
        // "If `ptr` is NULL, the behaviour is the same as calling malloc(new_size)."
        registers->rcx = new_size;
        malloc_hook(context, registers);
        return;
    }
    
    if(globals.big_allocation_base <= ptr && ptr <= globals.big_allocation_base + context->big_allocation_at){
        
        u64 old_size = guest_read(u64, ptr - 8);
        
        // Allocate new memory.
        guest_allocate__inner(context, registers, new_size, /*alignment*/16, /*raise_on_failiure*/0, /*initiaized*/0);
        
        if(registers->rax != 0){
            guest_write(u64, registers->rax - 8, new_size);
            
            u64 source = ptr;
            u64 dest   = registers->rax;
            
            reallocate_copy(context, source, dest, old_size, new_size);
            
            guest_free__inner(context, ptr);
        }
    }
}

void calloc_hook(struct context *context, struct registers *registers){
    
    if(registers->cr3 != globals.process_cr3) return;
    
    // void *calloc(size_t num, size_t size);
    
    u64 num  = registers->rcx;
    u64 size = registers->rdx;
    u64 allocation_size = num * size;
    
    if(size != 0 && (num * size) / size != num){
        // @note: Overflow (@cleanup: The check seems horribly complicated... is there no simple one?)
        simulate_allocation_failure(context, registers, /*raise_on_failiure*/0);
        return;
    }
    
    guest_allocate__inner(context, registers, allocation_size, /*alignement*/16, /*raise_on_failiure*/0, /*initiaized*/1);
}

void aligned_alloc_hook(struct context *context, struct registers *registers){
    
    if(registers->cr3 != globals.process_cr3) return;
    
    // void *aligned_alloc(size_t alignment, size_t size);
    
    u64 alignment = registers->rcx;
    u64 size = registers->rdx;
    
    if(alignment & (alignment - 1)){
        // Alignement not a power of two.
        simulate_allocation_failure(context, registers, /*raise_on_failiure*/0);
        return;
    }
    
    guest_allocate__inner(context, registers, size, alignment, /*raise_on_failiure*/0, /*initiaized*/1);
}

void free_hook(struct context *context, struct registers *registers){
    
    if(registers->cr3 != globals.process_cr3) return;
    
    u64 allocated_address = registers->rcx;
    if(PRINT_HOOK_EVENTS) print("[" __FUNCTION__ "] %p\n", allocated_address);
    
    {
        //
        // Simulate a return from the free, as we never want to actually free memory.
        // While this does change the behavior, it makes us catch use-after-free's
        // and double free's reliably.
        // 
        registers->rip = guest_read(u64, registers->rsp);
        registers->rsp += 8;
    }
    
    if(!allocated_address) return; // free(NULL) does nothing.
    
    guest_free__inner(context, allocated_address);
}

void RtlAllocateHeap_hook(struct context *context, struct registers *registers){
    
    if(registers->cr3 != globals.process_cr3) return;
    
    // void *RtlAllocateHeap(void *heap, ulong flags, size_t Size);
    
    u32 flags = (u32)registers->rdx;
    u64 size = registers->r8;
    
    guest_allocate__inner(context, registers, size, 16, /*raise_on_failiure*/(flags & /*HEAP_GENERATE_EXCEPTIONS*/4) != 0, /*initiaized*/(flags & /*HEAP_ZERO_MEMORY*/8) != 0);
    
    if(registers->rax != 0){
        guest_write(u64, registers->rax - 0x10, flags);
    }
}


void RtlReAllocateHeap_hook(struct context *context, struct registers *registers){
    
    if(registers->cr3 != globals.process_cr3) return;
    
    // void *RtlReAllocateHeap(void *heap, ulong flags, void *ptr, size_t new_size);
    
    u64 flags = registers->rdx; // @cleanup: There is a only inplace flag.
    u64 ptr = registers->r8;
    u64 new_size = registers->r9;
    
    if(ptr == 0){
        // "If `ptr` is NULL, the behaviour is the same as calling malloc(new_size)."
        registers->r8 = new_size;
        RtlAllocateHeap_hook(context, registers);
        return;
    }
    
    int should_free = 1;
    u64 old_size;
    if(globals.big_allocation_base <= ptr && ptr <= globals.big_allocation_base + context->big_allocation_at){
        old_size = guest_read(u64, ptr - 8);
    }else{
        static u64 RtlSizeHeap = 0;
        if(!RtlSizeHeap) RtlSizeHeap = get_symbol(context, string("ntdll!RtlSizeHeap"));
        
        // SIZE_T RtlSizeHeap(PVOID HeapHandle, ULONG Flags, PVOID BaseAddress);
        
        u64 saved_rsp = registers->rsp;
        u64 saved_rip = registers->rip;
        
        registers->rsp -= 0x20;
        registers->rip = RtlSizeHeap;
        
        guest_write(u64, registers->rsp, DEFAULT_RETURN_RIP);
        
        struct crash_information crash_information = start_execution_jit(context);
        if(crash_information.crash_type != CRASH_none) return; // Crash information is already set on context.
        
        old_size = registers->rax;
        
        registers->rsp = saved_rsp;
        registers->rip = saved_rip;
        
        should_free = 0;
    }
    
    // Allocate new memory.
    guest_allocate__inner(context, registers, new_size, /*alignment*/16, /*raise_on_failiure*/(flags & /*HEAP_GENERATE_EXCEPTIONS*/4) != 0, /*initiaized*/(flags & /*HEAP_ZERO_MEMORY*/8) != 0);
    
    if(registers->rax != 0){
        guest_write(u64, registers->rax - 8, new_size);
        
        u64 source = ptr;
        u64 dest   = registers->rax;
        reallocate_copy(context, source, dest, old_size, new_size);
        if(should_free) guest_free__inner(context, ptr);
    }
}

void RtlFreeHeap_hook(struct context *context, struct registers *registers){
    
    if(registers->cr3 != globals.process_cr3) return;
    
    u64 allocated_address = registers->r8;
    if(PRINT_HOOK_EVENTS) print("[" __FUNCTION__ "] %p\n", allocated_address);
    
    {
        //
        // Simulate a return from the free, as we never want to actually free memory.
        // While this does change the behavior, it makes us catch use-after-free's
        // and double free's reliably.
        // 
        registers->rip = guest_read(u64, registers->rsp);
        registers->rsp += 8;
    }
    
    // "RtlFreeHeap returns TRUE if the block was freed successfully; FALSE otherwise."
    registers->rax = 1;
    
    
    if(!allocated_address) return;
    guest_free__inner(context, allocated_address);
}

void RtlSizeHeap_hook(struct context *context, struct registers *registers){
    
    if(registers->cr3 != globals.process_cr3) return;
    
    // SIZE_T RtlSizeHeap(PVOID HeapHandle, ULONG Flags, PVOID BaseAddress);
    u64 ptr = registers->r8;
    
    if(globals.big_allocation_base <= ptr && ptr <= globals.big_allocation_base + context->big_allocation_at){
        // If we allocated this slot, return its size that way, 
        // otherwise, just continue execution.
        registers->rax = (guest_read(u64, ptr - 8) + 0xf) & ~0xf;
        registers->rip = guest_read(u64, registers->rsp);
        registers->rsp += 8;
    }
}

void GlobalFlags_hook(struct context *context, struct registers *registers){
    
    if(registers->cr3 != globals.process_cr3) return;
    
    // UINT GlobalFlags([in] HGLOBAL hMem);
    u64 ptr = registers->rcx;
    if(globals.big_allocation_base <= ptr && ptr <= globals.big_allocation_base + context->big_allocation_at){
        registers->rax = guest_read(u64, ptr - 0x10);
        registers->rip = guest_read(u64, registers->rsp);
        registers->rsp += 8;
    }
}

void GlobalSize_hook(struct context *context, struct registers *registers){
    
    if(registers->cr3 != globals.process_cr3) return;
    
    // SIZE_T GlobalSize([in] HGLOBAL hMem);
    u64 ptr = registers->rcx;
    
    if(globals.big_allocation_base <= ptr && ptr <= globals.big_allocation_base + context->big_allocation_at){
        // If we allocated this slot, return its size that way, 
        // otherwise, just continue execution.
        registers->rax = (guest_read(u64, ptr - 8) + 0xf) & ~0xf;
        registers->rip = guest_read(u64, registers->rsp);
        registers->rsp += 8;
    }
}

void lock_user_addressspace_range(struct context *context, u64 address_to_lock, u64 size_to_lock, struct string site){
    
    // 
    // Lock all modules into memory.
    // 
    
    u64 GetProcessWorkingSetSizeEx = get_symbol(context, string("kernelbase!GetProcessWorkingSetSizeEx"));
    u64 SetProcessWorkingSetSizeEx = get_symbol(context, string("kernelbase!SetProcessWorkingSetSizeEx"));
    u64 NtLockVirtualMemory = get_symbol(context, string("ntdll!NtLockVirtualMemory"));
    
    if(!NtLockVirtualMemory || !GetProcessWorkingSetSizeEx || !GetProcessWorkingSetSizeEx){
        print("[%s]" "Failed to get necessary symbols to lock userspace modules.\n", __FUNCTION__);
        print("   Needed modules are 'ntdll' for 'NtLockVirtualMemory' and 'kernelbase' for\n");
        print("   'GetProcessWorkingSetSizeEx' and 'SetProcessWorkingSetSizeEx'.\n");
        return;
    }
    
    struct registers original_registers = context->registers;
    
    struct registers *registers = &context->registers;
    
    // Set up a stack frame to call stuff.
    registers->rsp -= 0xa0;
    if((registers->rsp & 0xf) == 0) registers->rsp -= 8;
    guest_write(u64, registers->rsp, DEFAULT_RETURN_RIP);
    
    struct virtual_lock_parameters{
        
        u64 Address;
        u64 Size;
        
        u64 MinimumWorkingSetSize;
        u64 MaximumWorkingSetSize;
        u64 Flags;
    } parameters;
    
    u64 parameter_address = registers->rsp + 0x60;
    
    // Write the parameter block into the guest memory.
    parameters.Address = address_to_lock;
    parameters.Size    = size_to_lock;
    guest_write_size(context, &parameters, parameter_address, sizeof(parameters));
    
    for(int attempt = 0; attempt < 10; attempt++){
        // Attempt to lock the memory:
        //      NTSTATUS NtLockVirtualMemoryStatus = NtLockVirtualMemory(TargetProcessInformation.hProcess, &Address, &MemoryBasicInformation.RegionSize, /*MAP_PROCESS*/1);
        registers->rcx = (u64)-1;
        registers->rdx = parameter_address + offset_in_type(struct virtual_lock_parameters, Address);
        registers->r8  = parameter_address + offset_in_type(struct virtual_lock_parameters, Size);
        registers->r9  = 1;
        registers->rip = NtLockVirtualMemory;
        struct crash_information execution_result = start_execution_jit(context);
        if(execution_result.crash_type || (registers->rax != 0 && registers->rax != /*STATUS_WORKING_SET_QUOTA*/0xc00000a1 && registers->rax != /*STATUS_WAS_LOCKED*/0x40000019)){
            print_result_status(context, "NtLockVirtualMemory");
            print("Failed while trying to lock user module %.*s address: %p size: 0x%llx\n", site.size, site.data, parameters.Address, parameters.Size);
            os_panic(1);
        }
        
        if(registers->rax == /*Success*/0 || registers->rax == /*STATUS_WAS_LOCKED*/0x40000019) break;
        
        // We exceeded the quota necessary.
        // 
        //     BOOL GetProcessWorkingSetSizeExSuccess = GetProcessWorkingSetSizeEx(TargetProcessInformation.hProcess, &MinimumWorkingSetSize, &MaximumWorkingSetSize, &Flags);
        //     BOOL SetProcessWorkingSetSizeExSuccess = SetProcessWorkingSetSizeEx(TargetProcessInformation.hProcess, MinimumWorkingSetSize, MaximumWorkingSetSize, Flags);
        //     
        registers->rcx = (u64)-1;
        registers->rdx = parameter_address + offset_in_type(struct virtual_lock_parameters, MinimumWorkingSetSize);
        registers->r8  = parameter_address + offset_in_type(struct virtual_lock_parameters, MaximumWorkingSetSize);
        registers->r9  = parameter_address + offset_in_type(struct virtual_lock_parameters, Flags);
        registers->rip = GetProcessWorkingSetSizeEx;
        execution_result = start_execution_jit(context);
        if(execution_result.crash_type || (registers->rax == 0)){
            print_result_status(context, "GetProcessWorkingSetSizeEx");
            print("Failed to GetProcessWorkingSetSizeEx for user module %.*s address: %p size: 0x%llx\n", site.size, site.data, parameters.Address, parameters.Size);
            os_panic(1);
        }
        
        guest_read_size(context, &parameters, parameter_address, sizeof(parameters), PERMISSION_read);
        
        registers->rcx = (u64)-1;
        registers->rdx = parameters.MinimumWorkingSetSize * 2;
        registers->r8  = parameters.MaximumWorkingSetSize * 2;
        registers->r9  =/*QUOTA_LIMITS_HARDWS_MIN_ENABLE*/1 | /*QUOTA_LIMITS_HARDWS_MAX_DISABLE*/8;
        registers->rip = SetProcessWorkingSetSizeEx;
        
        execution_result = start_execution_jit(context);
        if(execution_result.crash_type || (registers->rax == 0)){
            print_result_status(context, "SetProcessWorkingSetSizeEx");
            print("Failed to SetProcessWorkingSetSizeEx for user module %.*s address: %p size: 0x%llx\n", site.size, site.data, parameters.Address, parameters.Size);
            os_panic(1);
        }
    }
    
    context->registers = original_registers;
}

void register_user_memory_allocation_hooks(struct context *context){
    
    //
    // Register hooks for tracking crashes and Memory allocations.
    // We use a big initial allocation to speed up tracking.
    //
    
    {
        // Allocate some space on the stack. 0x20 for homing space, 0x8 for the return address. and then 0x18 for random stuff.
        context->registers.rsp -= 0x50;
        
        //
        // Make sure rsp is aligned properly for just having _called_ a function.
        //
        
        if((context->registers.rsp & 0xf) == 0) context->registers.rsp -= 8;
        assert((context->registers.rsp & 0xf) == 8);
        
        guest_write(u64, context->registers.rsp, DEFAULT_RETURN_RIP);
        
        struct{
            u64 base_address;
            u64 region_size;
        } input = {
            .base_address = 0, // let the kernel decide.
            .region_size  = FUZZING_BIG_ALLOCATION_SIZE,
        };
        
        u64 input_guest_address = context->registers.rsp + 0x40;
        
        guest_write_size(context, &input, input_guest_address, sizeof(input));
        
        // NTSTATUS NtAllocateVirtualMemory(
        //         [in]      HANDLE    ProcessHandle,
        //         [in, out] PVOID     *BaseAddress,
        //         [in]      ULONG_PTR ZeroBits,
        //         [in, out] PSIZE_T   RegionSize,
        //         [in]      ULONG     AllocationType,
        //         [in]      ULONG     Protect
        //         )
        
        context->registers.rip = get_symbol(context, string("ntdll!NtAllocateVirtualMemory"));
        context->registers.rcx = (u64)-1; // Current Process
        context->registers.rdx = input_guest_address; // 'base_address'
        context->registers.r8  = 0;
        context->registers.r9 = input_guest_address + 8; // 'region_size'
        guest_write(u64, context->registers.rsp + 0x28, /*MEM_COMMIT | MEM_RESERVE*/0x3000);
        guest_write(u64, context->registers.rsp + 0x30, /*PAGE_READ_WRITE*/4);
        
        struct crash_information execution_result = start_execution_jit(context);
        
        guest_read_size(context, &input, input_guest_address, sizeof(input), PERMISSION_read);
        
        if(execution_result.crash_type || context->registers.rax != 0 || input.base_address == 0){
            print_result_status(context, "NtAllocateVirtualMemory");
            print("Error: Initial big guest-allocation of 0x%llx failed.\n", FUZZING_BIG_ALLOCATION_SIZE);
            print("       We intended to use this memory to speed up heap allocations while fuzzing.\n");
            os_panic(1);
        }
        
        globals.big_allocation_base = input.base_address;
        globals.process_cr3 = context->registers.cr3;
        
        // Lock the range!
        lock_user_addressspace_range(context, globals.big_allocation_base, FUZZING_BIG_ALLOCATION_SIZE, string("Big-Fuzzing-Allocation"));
        
        // Reset the registers just in case.
        context->registers = globals.snapshot.registers;
    }
    
    // 
    // Register the hooks.
    // 
    
    struct loaded_module *loaded_module = get_module_for_address(context->registers.rip);
    if(loaded_module){
        u64 malloc_address = get_symbol_from_module(context, loaded_module, string("malloc"));
        if(malloc_address) register_hook(context, malloc_address, malloc_hook);
        
        u64 realloc_address = get_symbol_from_module(context, loaded_module, string("realloc"));
        if(realloc_address) register_hook(context, realloc_address, realloc_hook);
        
        u64 calloc_address = get_symbol_from_module(context, loaded_module, string("calloc"));
        if(calloc_address) register_hook(context, calloc_address, calloc_hook);
        
        u64 aligned_alloc_address = get_symbol_from_module(context, loaded_module, string("aligned_alloc"));
        if(aligned_alloc_address) register_hook(context, aligned_alloc_address, aligned_alloc_hook);
        
        u64 free_address = get_symbol_from_module(context, loaded_module, string("free"));
        if(free_address) register_hook(context, free_address, free_hook);
    }
    
    if(get_loaded_module(string("ucrtbase"))){
        register_hook(context, get_symbol(context, string("ucrtbase!malloc")), malloc_hook);
        register_hook(context, get_symbol(context, string("ucrtbase!realloc")), realloc_hook);
        register_hook(context, get_symbol(context, string("ucrtbase!calloc")), calloc_hook);
        // register_hook(context, get_symbol(context, string("ucrtbase!aligned_alloc")), aligned_alloc_hook);
        register_hook(context, get_symbol(context, string("ucrtbase!free")), free_hook);
    }
    
    if(get_loaded_module(string("msvcrt"))){
        register_hook(context, get_symbol(context, string("msvcrt!malloc")), malloc_hook);
        register_hook(context, get_symbol(context, string("msvcrt!realloc")), realloc_hook);
        register_hook(context, get_symbol(context, string("msvcrt!calloc")), calloc_hook);
        // register_hook(context, get_symbol(context, string("msvcrt!_aligned_alloc")), aligned_alloc_hook);
        register_hook(context, get_symbol(context, string("msvcrt!_aligned_free")), free_hook);
        register_hook(context, get_symbol(context, string("msvcrt!free")), free_hook);
    }
    
    if(get_loaded_module(string("kernelbase"))){
        register_hook(context, get_symbol(context, string("kernelbase!LocalAlloc")), LocalAlloc_hook);
        register_hook(context, get_symbol(context, string("kernelbase!LocalFree")), free_hook);
        
        register_hook(context, get_symbol(context, string("kernelbase!GlobalAlloc")), LocalAlloc_hook);
        register_hook(context, get_symbol(context, string("kernelbase!GlobalFree")), free_hook);
        register_hook(context, get_symbol(context, string("kernelbase!GlobalFlags")), GlobalFlags_hook);
        register_hook(context, get_symbol(context, string("kernelbase!GlobalSize")), GlobalSize_hook);
    }
    
    if(get_loaded_module(string("ntdll"))){
        register_hook(context, get_symbol(context, string("ntdll!RtlAllocateHeap")), RtlAllocateHeap_hook);
        register_hook(context, get_symbol(context, string("ntdll!RtlReAllocateHeap")), RtlReAllocateHeap_hook);
        register_hook(context, get_symbol(context, string("ntdll!RtlFreeHeap")), RtlFreeHeap_hook);
        register_hook(context, get_symbol(context, string("ntdll!RtlSizeHeap")), RtlSizeHeap_hook);
        
    }
}

//_____________________________________________________________________________________________________________________
// Locking userspace module memory.

void lock_userspace_module_memory(struct context *context){
    
    // 
    // Lock all user modules in the current process.
    // 
    u64 TIB = (context->registers.cs.selector & 3) ? context->registers.gs_base : context->registers.gs_swap;
    u64 PEB = guest_read(u64, TIB + get_member_offset(context, string("nt!_TEB.ProcessEnvironmentBlock")));
    u64 Ldr = guest_read(u64, PEB + get_member_offset(context, string("nt!_PEB.Ldr")));
    
    u64 InMemoryOrderModuleList = Ldr + get_member_offset(context, string("nt!_PEB_LDR_DATA.InMemoryOrderModuleList"));
    u64 DataTableEntryLink = guest_read(u64, InMemoryOrderModuleList);
    
    do{
        u64 DataTableEntry = DataTableEntryLink - get_member_offset(context, string("nt!_LDR_DATA_TABLE_ENTRY.InMemoryOrderLinks"));
        
        struct string BaseDllName = guest_read_unicode_string(context, &context->scratch_arena, DataTableEntry + get_member_offset(context, string("nt!_LDR_DATA_TABLE_ENTRY.FullDllName")));
        print("Locking '%.*s'\n", BaseDllName.size, BaseDllName.data);
        
        u64 address = guest_read(u64, DataTableEntry + get_member_offset(context, string("nt!_LDR_DATA_TABLE_ENTRY.DllBase")));
        u64 size    = guest_read(u32, DataTableEntry + get_member_offset(context, string("nt!_LDR_DATA_TABLE_ENTRY.SizeOfImage")));
        lock_user_addressspace_range(context, address, size, BaseDllName);
        
        DataTableEntryLink = guest_read(u64, DataTableEntryLink);
    }while(!context->crash && (DataTableEntryLink != InMemoryOrderModuleList) && DataTableEntryLink);
}

//_____________________________________________________________________________________________________________________
// Debug hooks

void hook_crash(struct context *context, struct registers *registers){
    (void)registers;
    set_crash_information(context, CRASH_internal_error, (u64)"[" __FUNCTION__ "]");
}

void hook_print_stack_trace(struct context *context, struct registers *registers){
    (void)registers;
    print_stack_trace(context);
}

void hook_print_registers(struct context *context, struct registers *registers){
    (void)registers;
    print_registers(context, stdout);
}

