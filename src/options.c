
//_____________________________________________________________________________________________________________________
// Fuzzing options

// 'FUZZ_CASES_BEFORE_RESET' determines the amount of inputs in a fuzz-run.
// If this value is '1' the target will be reset after every input.
// Otherwise, if an input executes successfully (does not crash) the next input will be executed without resetting.
s64 FUZZ_CASES_BEFORE_RESET = 0x80;

// 'FUZZ_CASE_TIMEOUT' determines when a fuzz case is considered a timeout. The value is in instructions executed.
s64 FUZZ_CASE_TIMEOUT = 5000000;

// 'FUZZING_ALLOCATION_LIMIT' limits the amount of memory the guest can allocate in a single call to 'ExAllocateHeapPool'.
// This ensures that the guest does not needlessly spends a long time trying to allocate gigabytes of memory.
#define FUZZING_ALLOCATION_LIMIT 0x10000

#define FUZZING_BIG_ALLOCATION_SIZE (100 * 1024 * 1024)

// If 'IMPLEMENT_EXTRA_PERMISSIONS' is '0' we NOP out the implementation of 'add_extra_permissions_for_page'.
// You can toggle this if you want to figure out the ramifications of an out-of-bounds read/write.
#define IMPLEMENT_EXTRA_PERMISSIONS 1

// You can turn this off in which case it will only detect out of bounds accesses
// that overflow the actual allocation (the size aligned to a 16-byte boundary).
// This is here in case stuff like wcslen is annoying.
#define DETECT_ONE_BYTE_OUT_OF_BOUNDS 0

// If 'TIMEOUT_ON_IDLE' is set idle events will cause a 'CRASH_timeout'.
#define TIMEOUT_ON_IDLE 0

// If 'SAVE_TIMEOUTS' is set timeouts are saved in the crashes folder. These are really spammy. 
// This options is purely for debugging timeouts.
#define SAVE_TIMEOUTS 0

// If 'CLEAR_INITIALIZATION_COVERAGE' is set the main thread will clear the coverage generated during the 'target_initialize' call.
// Meaning, the coverage files will not mark the instructions as having been hit.
#define CLEAR_INITIALIZATION_COVERAGE 1

// If 'ENTER_DEBUGGER_MODE_ON_CRASHES_PRE_FUZZING' is set any crash in 'target_initialize' will cause the emulator to enter debugger mode.
// This prevents a lot of confusing misconfiguration scenarios.
#define ENTER_DEBUGGER_MODE_ON_CRASHES_PRE_FUZZING 1

// If 'USE_STACK_TRACE_HASH_FOR_CRASH_UNIQUENESS' is set we will use 'calculate_stack_trace_hash' to determine crash uniqueness.
// Otherwise, we will use the crashing 'rip'. It is highly encouraged to use stack trace uniqueness as otherwise most crashes are
// determined to be at 'KeBugCheckEx' (We do _something_ "smart" to prevent this but not a lot).
#define USE_STACK_TRACE_HASH_FOR_CRASH_UNIQUENESS 1

// Whenever ia32_tsc is accessed in some way, this value is added to it.
#define RDTSC_INCREMENT 0x100

// The amount of pages, which can be written within a fuzz-run, before the system reports an internal error.
#define DIRTY_PHYSICAL_PAGE_CAPACITY 0x10000

// If during fuzzing we encounter the situation where we would write to a page, which was previously executed, 
// we produce an internal error. Otherwise, we would have to reset the JIT, which might degrade performance, if it happens often.
#define CRASH_ON_SELF_MODIFYING_CODE_DURING_FUZZING 1

#define HOOK_TABLE_SIZE  0x100
#define CRASH_TABLE_SIZE 0x1000

// This option causes all inputs in the corpus to be saved under corpus\<input-md5sum>.input
#define SHOULD_SAVE_INPUTS_TO_CORPUS_FOLDER 0

//_____________________________________________________________________________________________________________________
// Snapshot options

#define ENABLE_VMRS _WIN32

#define DIRTY_VTL0_PERMISSION_CAPACITY 0x1000

//_____________________________________________________________________________________________________________________
// JIT options

#define INSTRUCTION_CACHE_SIZE 0x4000

// If `JIT_EMULATE_MXCSR` we use the host mxcsr to emulate the guest mxcsr.
// This has some problems, as it could cause the host to crash etc.
// In practice almost noone cares about the accuracy of the mxcsr.
// (It controls floating point rounding modes and exceptions.)
#define JIT_EMULATE_MXCSR 0

#define DISABLE_JIT_TLB 0

// @cleanup: I don't think this is currently working.
#define DISABLE_TAILCALL_OPTIMIZTIONS 0

#define DISABLE_BRANCH_COVERAGE 0

#define DISABLE_TIMEOUTS 0

//_____________________________________________________________________________________________________________________
// Hypervisor options

#define HYPERVISOR_EXIT_ON_RDTSC  0


// 
// VSM only works partially:
// 
// The system can boot with Virtualization Based Security (VBS) enabled.
// VTL calls are implemented and work fine, but I don't see a good way to implement `HvModifyVtlProtectionMask`,
// which is sort of the main point of VBS. Fundamentally, we would need to be able have two physical memory mappings,
// one for each VTL, as the permissions are different between the two VTL.
// 
// I don't see a way to do this with the Hypervisor Platform APIs. There is probably a way if we go to the undocumented Vid.dll.
// 
// This means while VBS is running, there is no real separation between VTL 0 and VTL 1.
// This is not be much of a problem, except when trying run with HVCI enabled.
// If HVCI is enabled, the Secure Kernel Patch Guard (or Skpg, or Hyperguard) is also enabled.
// During its initialization, it tests that kernel pages are actually protected, by writing to a page and then executing it.
// The function that is being written and then executed is `KiErrata671Present`.
// If the write was successful, it return 0, otherwise it returns 1.
// 
// For us this will incorrectly return 0, and shortly thereafter Skpg will cause a CRITICAL_INITIALIZATION_FAILURE bugcheck.
// 
//                                                                                    - Pascal Beyer 22.10.2025
// This define disables the corresponding cpuid bits.
// 
// UPDATE(23.10.2025):
// 
// We can now boot with HVCI enabled. I realized, that if we just map the secure kernel pages as RWX instead of 
// no permissions, the rest of the permissions can be implemented correctly. Well, except that we also don't get
// access to Mode based execution controls. These give use both a kernel execute and a user execute bit.
// Therefore, I map pages which are user-executable also as kernel executable (this probably means all pages are executable).
// 
// Also see the code for HvModifyVtlProtectionMask inside helper_vmcall.
// 
// So TLDR: The kernel now thinks it works, though it kinda really does not :) I call that success!
// 
#define ENABLE_VSM 0


//_____________________________________________________________________________________________________________________
// Debugging options

#define PRINT_STARTUP_EVENTS    0
#define PRINT_EXECUTION_EVENTS  0
#define PRINT_VMBUS_EVENTS      0
#define PRINT_VMBUS_INITIALIZATION_EVENTS 0
#define PRINT_INTERRUPT_EVENTS  0
#define PRINT_HOOK_EVENTS       0
#define PRINT_MSR_ACESSES       0
#define PRINT_TIMER_EVENTS      0
#define PRINT_INPUT_EVENTS      0
#define PRINT_LOCAL_APIC_EVENTS 0
#define PRINT_IO_APIC_EVENTS    0
#define PRINT_DISK_EVENTS       0
#define PRINT_INSTRUCTION_HELPER_EVENTS 0
#define PRINT_VSM_EVENTS 0
