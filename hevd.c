// 
// This is a simple demonstration of how target-specific code might look.
// Compile this into the emulator using 'build.bat hevd.c'.
// 
// Building target-specific code for HEVD.sys is definitely overkill
// but maybe it will serve as an easy example.
//                                             - Pascal Beyer 20.03.2023
// 

struct input_metadata{
    u32 ioctl;
    u32 input_size; // may be different from 'input.size' to cause integer overflows and such.
    u32 output_size;
};

// 
// Globals we initialize on startup, which we will use while fuzzing.
// The emulator does not require this to be here.
// 
struct {
    u64 input_buffer;
    u64 driver_handle;
    u64 isob_buffer;
    u64 NtDeviceIoControlFile;
} target_globals;

// 
// 'target_initialize' is called by the main thread.
// Anything we do here applies changes to the snapshot.
// 
void target_initialize(struct context *context, int target_argc, char *target_argv[]){
    
    // Ignore target-specific arguments.
    (void)target_argc, (void)target_argv;
    
    
    // We expect the .DMP state to be at the start of 'nt!NtSetInformationTransactionManager'
    // With 
    //    rcx = One page of memory.
    //    rdx = One page of memory.
    //    r8  = One page of memory.
    //    r9  = One page of memory.
    //    
    // This is in accordance with 'kernel_snapshot.exe'.
    if(context->registers.rip != get_symbol(context, string("nt!NtSetInformationTransactionManager"))){
        print("Error: Initial register state does not have rip at nt!NtSetInformationTransactionManager.\n");
        print("       .Dmp file is not compatible with the 'hevd.c'.\n");
        _exit(1);
    }
    
    target_globals.input_buffer = context->registers.rdx;
    target_globals.isob_buffer  = context->registers.r8;
    
    //
    // Set up everything we need to call 'nt!NtCreateFile'.
    // As this routine is called before fuzzing, the HANDLE we receive will always be valid during fuzzing.
    //
    
#define DEVICE_STRING L"\\Device\\HackSysExtremeVulnerableDriver"
    struct create_buffer{
        u64 Handle;
        struct{
            u32 Length;
            u64 RootDirectory;
            u64 ObjectName;
            u32 Attributes;
            u64 SecurityDescriptor;
            u64 SecurityQualityOfService;
        } ObjectAttributes;
        struct unicode_string unicode_string;
        wchar_t string[64];
        struct{
            u64 Status;
            u64 Information;
        } IoStatusBlock;
    } create_buffer = {
        .Handle = 0,
        .ObjectAttributes = {
            .Length = sizeof(create_buffer.ObjectAttributes),
            .ObjectName = target_globals.input_buffer + offset_in_type(struct create_buffer, unicode_string),
            .Attributes = 0x40,
        },
        .unicode_string = {
            .length = sizeof(DEVICE_STRING) - 2,
            .maximum_length = sizeof(DEVICE_STRING),
            .buffer = target_globals.input_buffer + offset_in_type(struct create_buffer, string),
        },
        .string = DEVICE_STRING,
    };
    
    // 
    // Write the 'create_buffer' into guest memory.
    // 
    int success = guest_write_size(context, &create_buffer, target_globals.input_buffer, sizeof(create_buffer));
    if(!success){
        print("Error: Crash during 'target_initialize' when setting up the input buffer to NtCreateFile\n");
        _exit(1);
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
    // This is done by setting up the registers correctly and then calling 'start_execution_jit'.
    //
    context->registers.rip = get_symbol(context, string("nt!NtCreateFile"));
    context->registers.rcx = target_globals.input_buffer + offset_in_type(struct create_buffer, Handle);
    context->registers.rdx = 0xc0100080;
    context->registers.r8  = target_globals.input_buffer + offset_in_type(struct create_buffer, ObjectAttributes);
    context->registers.r9  = target_globals.input_buffer + offset_in_type(struct create_buffer, IoStatusBlock);
    guest_write(u64, context->registers.rsp + 0x28, 0);    // AllocationSize = NULL
    guest_write(u64, context->registers.rsp + 0x30, 0x80); // FileAttributes = FILE_ATTRIBUTE_NORMAL
    guest_write(u64, context->registers.rsp + 0x38, 0);    // ShareAccess = 0
    guest_write(u64, context->registers.rsp + 0x40, 1);    // CreateDisposition = FILE_OPEN
    guest_write(u64, context->registers.rsp + 0x48, 0x60); // CreateOptions = FILE_SYNCHRONOUS_IO_NONALERT | FILE_NON_DIRECTORY_FILE
    guest_write(u64, context->registers.rsp + 0x50, 0);    // EaBuffer = NULL
    guest_write(u64, context->registers.rsp + 0x58, 0);    // EaLength = 0
    
    struct crash_information result = start_execution_jit(context);
    
    // 
    // Make sure we did not crash and the returned 'NTSTATUS' is not an error.
    // 
    if(result.crash_type != CRASH_none || (s32)context->registers.rax < 0){
        // 
        // We failed. Print a small status report and exit.
        // 
        print_result_status(context, "HEVD");
        
        print("Error: Execution of NtCreateFile failed during 'target_initialize'.\n");
        _exit(1);
    }
    
    // 
    // Read out the handle and setup all the global state we need during fuzzing.
    // 
    target_globals.driver_handle = guest_read(u64, target_globals.input_buffer + offset_in_type(struct create_buffer, Handle));
    target_globals.NtDeviceIoControlFile = get_symbol(context, string("nt!NtDeviceIoControlFile"));
    
    // 
    // Provide and initial input for each ioctl.
    // 
    
    static int ioctls[] = {
        /*HEVD_IOCTL_BUFFER_OVERFLOW_STACK*/0x222003,
        /*HEVD_IOCTL_BUFFER_OVERFLOW_STACK_GS*/0x222007,
        /*HEVD_IOCTL_ARBITRARY_WRITE*/0x22200b,
        /*HEVD_IOCTL_BUFFER_OVERFLOW_NON_PAGED_POOL*/0x22200f,
        /*HEVD_IOCTL_ALLOCATE_UAF_OBJECT_NON_PAGED_POOL*/0x222013,
        /*HEVD_IOCTL_USE_UAF_OBJECT_NON_PAGED_POOL*/0x222017,
        /*HEVD_IOCTL_FREE_UAF_OBJECT_NON_PAGED_POOL*/0x22201b,
        /*HEVD_IOCTL_ALLOCATE_FAKE_OBJECT_NON_PAGED_POOL*/0x22201f,
        /*HEVD_IOCTL_TYPE_CONFUSION*/0x222023,
        /*HEVD_IOCTL_INTEGER_OVERFLOW*/0x222027,
        /*HEVD_IOCTL_NULL_POINTER_DEREFERENCE*/0x22202b,
        /*HEVD_IOCTL_UNINITIALIZED_MEMORY_STACK*/0x22202f,
        /*HEVD_IOCTL_UNINITIALIZED_MEMORY_PAGED_POOL*/0x222033,
        /*HEVD_IOCTL_DOUBLE_FETCH*/0x222037,
        /*HEVD_IOCTL_INSECURE_KERNEL_FILE_ACCESS*/0x22203b,
        /*HEVD_IOCTL_MEMORY_DISCLOSURE_NON_PAGED_POOL*/0x22203f,
        /*HEVD_IOCTL_BUFFER_OVERFLOW_PAGED_POOL_SESSION*/0x222043,
        /*HEVD_IOCTL_WRITE_NULL*/0x222047,
        /*HEVD_IOCTL_BUFFER_OVERFLOW_NON_PAGED_POOL_NX*/0x22204b,
        /*HEVD_IOCTL_MEMORY_DISCLOSURE_NON_PAGED_POOL_NX*/0x22204f,
        /*HEVD_IOCTL_ALLOCATE_UAF_OBJECT_NON_PAGED_POOL_NX*/0x222053,
        /*HEVD_IOCTL_USE_UAF_OBJECT_NON_PAGED_POOL_NX*/0x222057,
        /*HEVD_IOCTL_FREE_UAF_OBJECT_NON_PAGED_POOL_NX*/0x22205b,
        /*HEVD_IOCTL_ALLOCATE_FAKE_OBJECT_NON_PAGED_POOL_NX*/0x22205f,
        /*HEVD_IOCTL_CREATE_ARW_HELPER_OBJECT_NON_PAGED_POOL_NX*/0x222063,
        /*HEVD_IOCTL_SET_ARW_HELPER_OBJECT_NAME_NON_PAGED_POOL_NX*/0x222067,
        /*HEVD_IOCTL_GET_ARW_HELPER_OBJECT_NAME_NON_PAGED_POOL_NX*/0x22206b,
        /*HEVD_IOCTL_DELETE_ARW_HELPER_OBJECT_NON_PAGED_POOL_NX*/0x22206f,
        /*HEVD_IOCTL_ARBITRARY_INCREMENT*/0x222073,
    };
    
    for(u32 ioctl_index = 0; ioctl_index < array_count(ioctls); ioctl_index++){
        
        struct input input = {
            .data = push_data(&context->permanent_arena, u8, 0x100),
            .size = 0x100,
        };
        
        struct input_metadata *metadata = (struct input_metadata *)input.data;
        metadata->ioctl = ioctls[ioctl_index];
        metadata->input_size = (u32)(input.size - sizeof(struct input_metadata));
        
        add_input(input);
    }
    
    // 
    // Add default hooks to track bugchecks and memory allocations.
    // 
    register_bugcheck_hooks(context);
    register_kernel_memory_allocation_hooks(context);
}

// 
// The 'target_get_input' function is called before every fuzz case.
// 
struct input target_get_input(struct context *context, u64 *seed){
    
    struct input input = get_random_input(&context->fuzz_run_arena, seed);
    apply_simple_mutations(input, target_globals.input_buffer, seed);
    
    if((xor_shift(seed) & 7) == 0){
        // 
        // Change the size of the input.
        // 
        
        s32 size_to_add = (xor_shift(seed) & 0xf) - 7;
        
        input.size += size_to_add;
        if(input.size < sizeof(struct input_metadata)){
            input.size = sizeof(struct input_metadata);
        }
        
        if(size_to_add > 0){
            u8 *added = push_data(&context->fuzz_run_arena, u8, size_to_add);
            for(s32 index = 0; index < size_to_add; index++){
                added[index] = (u8)xor_shift(seed);
            }
        }
    }
    
    return input;
}

// 
// The 'target_execute_input' is supposed to actually perform the fuzzing.
// It gets passed the inputs after they have been mutated by 'target_mutate_input'.
// 
// The 'execution_result' return value should be obtained by a call to 'start_execution'.
// If the 'execution_result.crash_type' is not `CRASH_none` the target will be reset to the snapshot.
// If 'context->coverage_increase' is non-zero, the input will be atomically saved to 'globals.inputs'.
// Crashes will only be added to 'globals.inputs' if either 'context->coverage_increase' is non-zero or 
// the stack trace of the crash is unique.
// 
// For the exact logic take a peek at 'start_fuzzing'.
// 
struct crash_information target_execute_input(struct context *context, struct input input){
    
    // Always start out with the register state of the snapshot (at the start of NtDeviceIoControlFile).
    context->registers = globals.snapshot.registers;
    
    // 
    // Write the input into guest memory.
    // 
    u64 size_to_write = (input.size < 0x1000) ? input.size : 0x1000;
    guest_write_size(context, input.data, target_globals.input_buffer, size_to_write);
    
    struct input_metadata *metadata = (void *)input.data;
    
    // 
    // Call into 'NtDeviceIoControlFile'.
    // 
    context->registers.rip = target_globals.NtDeviceIoControlFile;
    context->registers.rcx = target_globals.driver_handle;
    context->registers.rdx = 0;
    context->registers.r8  = 0;
    context->registers.r9  = 0;
    guest_write(u64, context->registers.rsp + 0x28, target_globals.isob_buffer);
    guest_write(u64, context->registers.rsp + 0x30, metadata->ioctl);
    guest_write(u64, context->registers.rsp + 0x38, target_globals.input_buffer + sizeof(*metadata));
    guest_write(u64, context->registers.rsp + 0x40, metadata->input_size);
    guest_write(u64, context->registers.rsp + 0x48, target_globals.input_buffer + sizeof(*metadata) + metadata->input_size);
    guest_write(u64, context->registers.rsp + 0x50, metadata->output_size);
    
    return start_execution_jit(context);
}

// Nothing to do in reset.
void target_reset(struct context *context){ (void)context; }
