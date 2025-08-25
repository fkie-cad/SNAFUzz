// 
// Target specific code can be compiled in using `build.bat target_specific_code.c`
// and is simply included in `main.c` from where it can use almost all other code.
// If no argument to `build.bat` is provided, it defaults to `default_target.c`.
// Because of the single compilation unit model (where we simply include the 
// target specific code into `main.c`), this file (`target_specific_code_api.h`)
// is not supposed to function as a header file, but rather as "documentation".
// 
// As such, this file only includes the functions that are most useful for writing
// target specific code, but nothing prevents you from calling any function you 
// would like.
// 
// The target specific code is required to implement two functions: 
//     * target_initialize
//     * target_execute_input
//     
// Optionally, target specific code can also implement the following functions:
//     * target_get_input
//     * target_reset
//     * target_read_guest_input_buffer
// 
// (for more information on these functions see below.)
// 
// Each of these functions is passed a thread local 'context' structure, 
// which contains:
// 
//     * The current register state in 'context->registers'.
//     * A memory arena for permanent allocations in 'context->permanent_arena'.
//     * A memory arena for allocations that will be freed after each fuzz-run,
//       in 'context->fuzz_run_arena'.
//     * The current 'crash_information' in 'context->crash_information' or 
//       equivalently 'context->crash' and 'context->crash_address'.
//       
// All global variables are contained in the 'globals' structure. Here, only
// the 'globals.snapshot.registers' structure is relevant for target specific code.
// At the start of each fuzz-run, 'context->registers' gets reset to 
// 'globals.snapshot.registers'.
// 
// Some options in `options.c` are also implemented as globals and may be adjusted
// by the target code. For example, you may adjust the `FUZZ_CASES_BEFORE_RESET`
// or the `FUZZ_CASE_TIMEOUT`. But they should be constant after initialization.
// 
// For examples of target specific code, see `default_target.c`, `hevd.c` and `headerParser.c`.
// 
// You can debug any guest execution of the target specific code, by appending
// the '-d' flag to the fuzzing command. This will cause the debugger to break
// at the start of any guest execution inside `target_initialize` as well as 
// the start of fuzzing, i.e `target_execute_input` (which it will limit to one thread).
// 
//                                                      - Pascal Beyer 25.03.2024
// 

// Ensure all of the members we talked above exist:
typedef int target_specific_member_check[
+ offset_in_type(struct context, registers)
+ offset_in_type(struct context, permanent_arena)
+ offset_in_type(struct context, fuzz_run_arena)
+ offset_in_type(struct context, crash_information)
+ offset_in_type(struct context, crash)
+ offset_in_type(struct context, crash_address)
+ sizeof(globals.snapshot.registers)
+ sizeof(FUZZ_CASE_TIMEOUT)
+ sizeof(FUZZ_CASES_BEFORE_RESET)
+ sizeof(globals.input_buffer_physical_address)
];

//_____________________________________________________________________________________________________________________
// Function which must be implemented by the target-specific code.

// 
// The `target_initialize` function is called by the main thread prior to fuzzing.
// This means any changes to the snapshot are permanent. This can be used to 
// initialize the target, e.g.: open a HANDLE to a device you want to fuzz, 
// by setting up a stack frame and calling `start_execution_jit` or reading
// and writing guest memory by using `guest_read` and `guest_write`.
// 
// `target_initialize` should also allocate at least one input, which is 
// expected to be allocated in `context->permanent_arena` and added using `add_input`.
// Inputs can be loaded from an "inputs" directory using `load_input_directory`.
// 
// Any necessary Hooks should also be registered during `target_initialize`.
// Usually, at least crash hooks have to be registered to detect crashes,
// this can be done using `register_bugcheck_hooks`, for kernel-mode targets,
// or using `register_user_crash_hooks`, for user-space applications.
// 
// Optionally, heap tracking can be enabled using `register_kernel_memory_allocation_hooks`
// or register_user_memory_allocation_hooks.
// 
// (see below for any referenced function).
// 
// `target_argc` and `target_argv` contain the arguments after `--` passed to the emulator,
// e.g: 'foo' and 'bar' for 
// 
//     > emulator.exe test.snapshot -- foo bar
// 
// 
void target_initialize(struct context *context, int target_argc, char *target_argv[]);

// 
// The `target_get_input` function is called prior to each fuzz-case. 
// The returned 'input' is expected to be allocated in the 'context->fuzz_run_arena'.
// Depending on your target, you might want to write generators, specialized
// mutators etc.
// 
struct input target_get_input(struct context *context, u64 *seed);

// This is the default implementation: 

#if _WIN32
#pragma comment(linker, "/ALTERNATENAME:target_get_input=target_get_input__default")
#endif
struct input target_get_input__default(struct context *context, u64 *seed){
    struct input input = get_random_input(&context->fuzz_run_arena, seed);
    apply_simple_mutations(input, 0, seed);
    return input;
}

// 
// The `target_execute_input` function is called to inject and execute each fuzz-case and 
// is always supposed to call `start_execution_jit` at least once.
// Here is a simple implementation:
// 
// struct crash_information target_execute_input(struct context *context, struct input input){
//     context->registers = globals.snapshot.registers;                                           // Reset the register state to be as it was when taking the snapshot.
//     guest_write_size(context, input.data, /*input_buffer*/context->registers.rcx, input.size); // Write in the input into the guest.
//     guest_write(u64, context->registers.rsp, DEFAULT_RETURN_RIP);                              // Set up returning as "successful" execution.
//     return start_execution_jit(context);                                                       // Execute the function under test.
// }
//     
// This implementation assumes:
// 
//     * `target_initialize` has set up `globals.snapshot.registers` as needed.
//     * the input buffer, which needs fuzzing is contained in rcx and is at least `input.size` big.
// 
// 
struct crash_information target_execute_input(struct context *context, struct input input);

// 
// The target_reset function is called after we have reset the target to the snapshot.
// Target-specific code structures can be reset in this function.
// 
void target_reset(struct context *context);

// The default implementation does nothing:
#if _WIN32
#pragma comment(linker, "/ALTERNATENAME:target_reset=target_reset__default")
#endif
void target_reset__default(struct context *context){
    (void)context;
}

// 
// The `target_read_guest_input_buffer` function only has to be implemented if you want to implement "double fetch" detection for your target.
// In this case you have to tell the system, which physical page the input buffer is located in.
// This is done by setting `globals.input_buffer_physical_address`. If you know the virtual address of the input buffer,
// you can get its physical address by using `translate_page_number_to_physical`, e.g.:
// 
//     globals.input_buffer_physical_address = translate_page_number_to_physical(context, input_buffer_virtual_address >> 12, PERMISSION_none, /*ignored pte*/&(u64){0});
// 
// Whenever the guest attempts to read this physical address, instead `target_read_guest_input_buffer` is called instead.
// 
// `target_read_guest_input_buffer` should return 1, if the read was successful, and 0 if the read crashed, 
// in which case also `set_crash_information` should be called.
// 
// An implementation might look as follows:
//    
//    thread_local struct input current_input;
//    thread_local u64 offset_in_input_buffer;
//    
//    int target_read_guest_input_buffer(struct context *context, u64 virtual_address, u8 *buffer, u64 size){
//        if(offset_in_input_buffer + size < (u64)current_input.size){
//             memcpy(buffer, current_input.data + offset_in_input_buffer, size);
//             offset_in_input_buffer += size;
//             return 1;
//        }
//        set_crash_information(context, CRASH_internal_error, (u64)"Ran out of input."); // We cannot cause a page fault, as the page is still present in the page tables, causing windows to infinitely loop.
//        return 0;
//    }
//    
// 
int target_read_guest_input_buffer(struct context *context, u64 virtual_address, u8 *buffer, u64 size);

// The default implementation simply crashes.
#if _WIN32
#pragma comment(linker, "/ALTERNATENAME:target_read_guest_input_buffer=target_read_guest_input_buffer__default")
#endif
void target_read_guest_input_buffer__default(struct context *context){
    (void)context; 
    not_implemented();
}



// (After this point, all functions are implemented by the system and can be used in one of the functions above).

//_____________________________________________________________________________________________________________________
// Functions to control the input corpus.

// `add_input` atomically adds an input to `globals.inputs`.
// Target specific code should only used this function during `target_initialize`
// as the system takes care of saving inputs, once fuzzing starts.
// This function expects `input` to be in stable memory.
void add_input(struct input input);

// `load_input_directory` iterates a directory, loads each file and adds 
// it as an input using `add_input`.
void load_input_directory(char *directory_path);

// `get_random_input` gets a random input from `globals.inputs` and
// copies it into a buffer allocated from `arena`. This function is usually called 
// during `target_get_input`. The returned input can also be extended by simply 
// allocating more bytes onto `arena` as arenas are linear allocators.
struct input get_random_input(struct memory_arena *arena, u64 *seed);

//_____________________________________________________________________________________________________________________
// Mutating bytes.

// `apply_simple_mutations` can be used if only a simple mutator is necessary.
// The `guest_input_buffer_base` is used to write pointer values to the input.
void apply_simple_mutations(struct input input, u64 guest_input_buffer_base, u64 *seed);

// `xor_shift` is a very simple and fast random number generator.
u64 xor_shift(u64 *number);

//_____________________________________________________________________________________________________________________
// Querying and hooking symbols.

// Symbols are based on public symbols provided by the Microsoft symbol server 
// and are downloaded on demand. Because symbol routines are rather heavy, 
// after `target_initialize`, they should only be used on once and then cached.

// `get_symbol` can be used to retrieve the address of any symbol we have debug information for, e.g.: 
// 
//     u64 NtDeviceIoControlFile = get_symbol(context, string("nt!NtDeviceIoControlFile"));
// 
// On failure, `get_symbol` sometimes prints some cryptic string and then returns 0.
u64 get_symbol(struct context *context, struct string symbol);

// `get_member_offset` can be used to retrieve the offset of a member in a struct contained in the 
// debug information for a module, e.g:
// 
//     u64 process_offset = get_member_offset(context, string("nt!_KTHREAD.ApcState.Process"));
// 
// On failure, `get_member_offset` sometimes prints some cryptic string and then returns 0.
u64 get_member_offset(struct context *context, struct string symbol);

// `parse_address` can be used to parse more complicated expressions like "5 * rcx + 10" 
// or "target!FuzzMeBuffer + 100". All integers are interpreted as hex.
u64 parse_address(struct context *context, struct string *line, int *error);

// If you are working with a user-space target, symbols might not load automatically,
// because parts of the image are paged out. In this case, you can load the symbols
// manually (provided you have the .pdb), by doing the following:
// 
//     struct loaded_module *module = get_loaded_module(string("<name-of-your-module>"));
//     module->pdb_context = load_pdb(load_file("<path/to/the/module.pdb>"));
//     
// In the future, there should probably be a better API here.
struct loaded_module *get_loaded_module(struct string module_name);
struct file load_file(char *file_name);
struct pdb_context *load_pdb(struct file pdb_file);

//_____________________________________________________________________________________________________________________
// Hooks.

// Hooks are callbacks which are executed once a certain rip is reached.
// This can be used for example to track allocations, detect crashes,
// or inject inputs. For example, one might redirect `fread` and `fseek` to use 
// the `current_input` and a `current_offset` which were previously 
// (in `target_execute_input`) stashed in a structure like:
// 
//     thread_local struct {
//         struct input current_input;
//         u64 current_offset;
//     } target_context;
// 
// Hooks have to be registered in the `target_initialize` function!
// 
// For more information see `hooks.c`. 
void register_hook_(struct context *context, u64 rip, hook_callback *hook, char *hook_string);
#define register_hook(context, rip, hook) register_hook_((context), (rip), (hook), #hook)

// The most important hooks are crash hooks.
// These hooks more or less define what is considered a "crash" for your target.
// 
// For kernel-mode targets, this is the `register_bugcheck_hooks` function,
// which hooks `nt!KeBugCheck`, `nt!KeBugCheck2` and `nt!KeBugCheckEx`.
// 
// For user-mode targets, this is the `register_user_crash_hooks` function,
// that tries to check for unhandled exceptions in multiple ways.
void register_bugcheck_hooks(struct context *context);
void register_user_crash_hooks(struct context *context);

// Hooks can also be used to enable memory allocation tracking.
// This enabled the system to have some ASAN-like features.
// To enable these features call either `register_kernel_memory_allocation_hooks`
// or `register_user_memory_allocation_hooks` depending on your context.
void register_user_memory_allocation_hooks(struct context *context);
void register_kernel_memory_allocation_hooks(struct context *context);

// Internally, the allocation tracking first (when called from `target_initialize`) allocates a big allocation
// of `FUZZING_BIG_ALLOCATION_SIZE` bytes, and then registers hooks on `malloc`, `calloc`, `realloc`, `free`, etc.
// These hooks then prevent the underlying allocation and instead linealy allocate memory from the "big allocation".
// Once set up, you can use this system to allocate guest memory through the `guest_allocate__inner` function.
// Though only for allocations up to `FUZZING_ALLOCATION_LIMIT`.
// This memory can also be _freed_ using `guest_free__inner`, but all this means is marking the whole range as being
// "inaccessible", i.e. causing a crash when accessed by the guest.
// The "big allocation" is only ever really freed, when the guest is reset to the snapshot.
void guest_allocate__inner(struct context *context, struct registers *registers, u64 NumberOfBytes, u64 alignment, int raise_on_failure, int initialized);
void guest_free__inner(struct context *context, u64 allocated_address);

//_____________________________________________________________________________________________________________________
// Reading and writing guest memory.

// 
// `guest_read_size` and `guest_write_size` return 1 on success and 0 on failure.
// Additionally, on failure `context->crash` is set accordingly.
// `guest_read_size` behaves different on each permission: 
//      `PERMISSION_read`  - Normal read of a value (as performed by `guest_read_`).
//      `PERMISSION_write` - Checks if the address is writable and only if it is, performs the read,
//                           otherwise set `context->crash` to `CRASH_write`.
//      `PERMISSION_none`  - Uses the same path as `PERMISSON_read` but does not change accessed bits in the page table.
// You are not supposed to pass `PERMISSION_execute`, use `prefetch_instruction` instead.
//         
int guest_read_size(struct context *context, void *_buffer, u64 address, u64 size, enum permissions required_permissions);
int guest_write_size(struct context *context, void *_buffer, u64 address, u64 size);

// The `guest_read` and `guest_write` macros are the main tools for parsing and writing guest memory, e.g.:
// 
//     * u64 PsLoadedModuleList = guest_read(u64, get_symbol(context, string("nt!PsLoadedModuleList")));
//     * guest_write(u64, registers.rsp + 0x28, /*fifth_argument*/0x1337);
#define guest_read(type, guest_address) (*(type *)guest_read_(context, &(u8[sizeof(type)]){0}, guest_address, sizeof(type)))
#define guest_write(type, guest_address, value) guest_write_(context, guest_address, sizeof((type){0}), value)

// `guest_force_write` behaves like `guest_write_size` but ignores permissions and does not set accessed bits.
// This can be used to write to code or read only data of a module.
int guest_force_write(struct context *context, void *_buffer, u64 address, u64 size);

// `prefetch_instruction` checks for `PERMISSION_execute` and can read at most 0xfff bytes.
// It returns the amount of bytes it was able to read, but never sets `CRASH_execute`.
// Usually, this function is used to try to read the at most 16-bytes, which make up the next instruction.
u32 prefetch_instruction(struct context *context, u64 address, u8 *instruction_buffer, u32 size);

//_____________________________________________________________________________________________________________________
// Executing code.

// `start_execution_jit` is the routine which actually does the fuzzing.
// It should be called from `target_execute_input` and returns `crash_information` which are the same
// as `context->crash_information`.
// Usually, execution starts at the start of some function, e.g. `NtDeviceIoControlFile` in which case 
// the return value should be overwritten with the `DEFAULT_RETURN_RIP` to detect a successful execution
// of the input.
// `start_execution_jit` can also be used during `target_initialize` to setup the snapshot for fuzzing, 
// for example one could open a device HANDLE and then use this handle during fuzzing to call `NtDeviceIoControlFile`.
struct crash_information start_execution_jit(struct context *context);

// Arbitrary value we use to detect "successful" (no crash) execution of the target.
#define DEFAULT_RETURN_RIP 0x1337133713371337

//_____________________________________________________________________________________________________________________
// Debugging routines.

// `handle_debugger` breaks into the command-line debugger, and can be used to debug hooks.
// WARNING: When called from a hook, single_stepping does not work as one would expect.
// `handle_debugger` should only be used when in debugger mode (check `globals.debugger_mode`),
// which can be entered using the '-d' command line option to the emulator.
void handle_debugger(struct context *context);

// 
// Various useful debug printing routines.
// 
void print_symbol(struct context *context, u64 address);
void print_stack_trace(struct context *context);
void print_registers(struct context *context, FILE *trace_file);
u32 print_disassembly(struct context *context, u64 rip, int *crash);
u32 print_disassembly_for_buffer(struct context *context, u64 rip, u8 *instruction_buffer, u32 instruction_buffer_size);

// Prints something like "[<format>] write at <registers->rip> with status 0x<(u32)registers->rax>."
void print_result_status(struct context *context, char *format, ...);

// When you want to implement similar debugging routines, which read a bunch 
// of guest memory and then print it (or whatever), you can start them by 
// calling `enter_debugging_routine` and end with `exit_debugging_routine`.
// This will cause any invalid guest memory access to be ignored 
// and access bits in the page table not to be set.
struct crash_information enter_debugging_routine(struct context *context);
void exit_debugging_routine(struct context *context, struct crash_information original_crash_information);

//_____________________________________________________________________________________________________________________
// Allocation routines.

// Arenas are linear memory allocators, for which we reserve a giant chunk of virtual memory 
// and then "commit" them one MiB at a time.
void *arena_allocate_struct(struct memory_arena *arena, smm size, smm alignment);

#define push_struct(arena, type) (type *)arena_allocate_struct(arena, sizeof((type){0}), _Alignof(type))
#define push_data(arena, type, size) (type *)arena_allocate_struct(arena, (size) * sizeof((type){0}), _Alignof(type))

