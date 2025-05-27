
// 
// We want to fuzz 'parseHeader(u8 force, /*out*/PHeaderData hd, /*in*/PGlobalParams gp, PPEParams pep, PElfParams elfp, PDexParams dexp)'.
// 
//    The buffers we care about are at 'gp->data.block_main' and 'gp->data.block_sub'.
//    They get written all over the place using the 'readFile' utility (which we will have to hook).
//    
//    PEParams:  struct { u32 info_level; char *certificate_directory; }
//    ElfParams: struct { u32 info_level; }
//    DexParams: struct { u32 info_level; }
//    
//    GlobalParams also has an 'info_level' and a 'info_show_offsets'. 
//    I don't really see any reason not to put these 'info_levels' all to 0xffffffff.
//    
// 
// 

__declspec(thread) struct{
    struct input current_input;
    s64 current_offset;
} thread_locals;

void fread_hook(struct context *context, struct registers *registers){
    // 
    // fread(buffer, size, count, stream)
    // 
    
    s64 out   = registers->rcx;
    s64 start = thread_locals.current_offset;
    s64 size  = registers->rdx * registers->r8;
    
    struct input input = thread_locals.current_input;
    
    s64 start_offset = start;
    s64 end_offset   = start + size;
    
    end_offset = (end_offset < input.size) ? end_offset : input.size;
    
    if(start_offset < input.size && end_offset > start_offset){
        guest_write_size(context, input.data + start_offset, out, end_offset - start_offset);
        
        registers->rax = end_offset - start_offset;
    }else{
        registers->rax = 0;
    }
    
    registers->rip = guest_read(u64, registers->rsp);
    registers->rsp += 8;
}

void fseek_hook(struct context *context, struct registers *registers){
    // 
    // fseek(file, offset, origin)
    // 
    
    s64 offset = registers->rdx;
    s64 origin = registers->r8;
    
    if(origin == /*SEEK_SET*/0){
        
    }else if(origin == /*SEEK_CUR*/1){
        offset += thread_locals.current_offset;
    }else if(origin == /*SEEK_END*/2){
        offset = thread_locals.current_input.size + offset;
    }
    
    if(offset < thread_locals.current_input.size){
        thread_locals.current_offset = offset;
        registers->rax = 0;
    }else{
        registers->rax = 1;
    }
    
    registers->rip = guest_read(u64, registers->rsp);
    registers->rsp += 8;
}

void printf_hook(struct context *context, struct registers *registers){
    registers->rax = 0;
    registers->rip = guest_read(u64, registers->rsp);
    registers->rsp += 8;
}

void sprintf_hook(struct context *context, struct registers *registers){
    guest_write(u8, registers->rcx, 0);
    
    registers->rax = 0;
    registers->rip = guest_read(u64, registers->rsp);
    registers->rsp += 8;
}

void target_initialize(struct context *context, int target_argc, char *target_argv[]){
    (void)target_argc;
    (void)target_argv;
    
    FUZZ_CASES_BEFORE_RESET = 1;
    FUZZ_CASE_TIMEOUT = 4'000'000;
    
    struct registers *registers = &context->registers;
    
    // parseHeader:
    //    rcx - force
    //    rdx - header_data
    //    r8  - global_params
    //    r9  - pe_params
    //    [rsp + 0x28] - elf_params
    //    [rsp + 0x30] - dex_params
    
    guest_write(u32, registers->r8 + get_member_offset(context, string("HeaderParser!GlobalParams.info_level")), 0xffffffff);
    guest_write(u32, registers->r8 + get_member_offset(context, string("HeaderParser!GlobalParams.info_show_offsets")), 1);
    guest_write(u32, registers->r9, 0xffffffff);
    guest_write(u32, guest_read(u64, registers->rsp + 0x28), 0xffffffff);
    guest_write(u32, guest_read(u64, registers->rsp + 0x30), 0xffffffff);
    
    load_input_directory("corpus_HeaderParser");
    
    register_hook(context, get_symbol(context, string("ucrtbase!fread")), fread_hook);
    register_hook(context, get_symbol(context, string("ucrtbase!_fseeki64")), fseek_hook);
    
    register_hook(context, get_symbol(context, string("HeaderParser!printf")), printf_hook);
    register_hook(context, get_symbol(context, string("HeaderParser!fprintf")), printf_hook);
    register_hook(context, get_symbol(context, string("HeaderParser!sprintf")), sprintf_hook);
    register_hook(context, get_symbol(context, string("ucrtbase!strftime")), sprintf_hook);
    register_hook(context, get_symbol(context, string("ucrtbase!_localtime64")), printf_hook);
    
    register_user_crash_hooks(context);
    register_user_memory_allocation_hooks(context);
}

struct input target_get_input(struct context *context, u64 *seed){
    struct input input = get_random_input(&context->fuzz_run_arena, seed);
    apply_simple_mutations(input, 0, seed);
    return input;
}

struct crash_information target_execute_input(struct context *context, struct input input){
    
    // 
    // Inject the first read into the input.
    u64 input_buffer = context->registers.r8 + 0x200;
    u64 size_to_write = (input.size < 0x400) ? input.size : 0x400;
    guest_write_size(context, input.data, input_buffer, size_to_write);
    
    // Save the input in a thread local such that we can use it in the 'readFile_hook'.
    thread_locals.current_input  = input;
    thread_locals.current_offset = size_to_write;
    
    // 
    // Set up the return value of 'DEFAULT_RETURN_RIP' which will mark the success case.
    // 
    guest_write(u64, context->registers.rsp, DEFAULT_RETURN_RIP);
    
    // 
    // Emulate the call to 'parseHeader'.
    // 
    return start_execution_jit(context);
}

void target_reset(struct context *context){ (void)context; }
