// 
// This is an example of target-specific code for a user mode program.
// The user mode program in question is the "headerParser":
// 
//     https://github.com/fkie-cad/headerParser
// 
// This is only intended to serve as an example of how to use SNAFUzz 
// to attack user mode programs.
// 
// To build this file into snafuzz as the target-specific code, use
//     
//     build.bat headerParser.c
//     
// Taking a snapshot:
// 
// One core annoyance with fuzzing user mode programs is that it is 
// more complicated to set breakpoints. The kernel is always mapped 
// into memory, and therefore, you can set a breakpoint on a kernel
// function whenever you like. With user space applications, you
// don't know where they will be located before they are launched.
// Further, even after they are launched it might be hard to locate
// the address range.
// 
// Furthermore, user-mode memory is often mapped out, causing us not
// to be able to read the program headers and therefore not being able
// to load debug information.
// 
// There are two ways to deal with this issue:
// 
//   1. You somehow manage to set a breakpoint when the application
//      is running, for example setting a breakpoint on a rarely
//      called kernel function e.g.: afd!AfdConnect if the application
//      connects a socket on startup.
//      And then, after you have a breakpoint, inside the application
//      use the `lock_user_modules` debugger command. This will lock
//      all user modules in guest physical memory and therefore allow
//      us to load debug information.
//      
//   2. You can use something like the `user_snapshot.c`.
//      
//          user_snapshot.exe <breakpoint offset> -- <target command line>
//      
//      This snapshotting utility is a small "debugger" that on startup,
//      sets a breakpoint on the main executable plus <breakpoint offset>
//      and when the breakpoint is hit locks the whole guest address space
//      and then causes a breakpoint the Virtual Machine debugger 
//      
// For the headerParser, option 2. makes it very easy. 
// First let's get a version of the headerParser:
// 
//    git clone https://github.com/fkie-cad/headerParser.git --branch v1.15.13
//    cd headerParser
//    winBuild.bat /pts v143 /pdb /p:RunTimeLib=Debug
// 
// (It's a little annoying for this, that we don't ship the .pdb's so we have to build it manually, but whatever).
// The function that we want to fuzz is 'parseHeader' and for my build of the headerParser
// its at offset 0x26c90.
// 
// Build the `user_snapshot.exe` by using `cl user_snaphshot.c` and copy both files to the virtual machine
// (either through the drag_and_drop.c service or by using Hyper-V).
// 
// If not already, boot the virtual machine in the snafuzz snapshot mode (snafuzz.exe <.vhdx>).
// Now taking a snapshot should be as easy as doing:
// 
//    user_snapshot.exe 0x26c90 -- parseHeader.exe parseHeader.exe
//    
// inside the guest, and then when snafuzz breaks in the debugger, 
// taking a snapshot using `snapshot fuzz`.
// 
// Now, if you have taken a snapshot and build snafuzz using `build.bat HeaderParser.c`,
// the last thing to do before fuzzing is to provide an input corpus in a `corpus_HeaderParser` directory.
// This directory is expected to live in the root-directory of snafuzz.
// After that, fuzzing should be as simple as `snafuzz fuzz.snapshot --`
// 
//                                                             - Pascal Beyer 25.08.2025
// 

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

thread_local struct{
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
    
    if(0 <= offset && offset <= thread_locals.current_input.size){
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
    FUZZ_CASE_TIMEOUT = 4000000;
    
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
    u64 input_buffer = context->registers.r8 + 0x208;
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
