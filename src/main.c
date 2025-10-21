
// 
// The main file.
// 
// As the main file does not do anything specific, I am going to take the space
// to talk about the general code organization I usually use and the overall 
// execution flow.
// 
// Compilation happens in a single-compilation-unit way, meaning all the other .c-files 
// are simply included at some point in this file.
// The good thing about this type of build is that there is no need for any header files.
// (sometimes there is still need for some pre-declarations but only a few.)
// 
// Other .c-files try to only contain code related to one specific operation.
// The main.c file contains all code related to the main thread, which sets everything up,
// while potentially calling initialize functions in other .c-files and the main fuzzing loop.
// State is generally contained either in the 'globals' structure or the `context` structure,
// and is NOT isolated for each .c-file. (There isn't a debugger structure or a JIT structure).
// 
// Every thread has a `context` structure it _owns_, and hence can access without synchronization. 
// Setting up and managing the context structures is also part of `main.c`. 
// 
// The main thread execution flow (`main` function):
//     
//     1) Parse the command line arguments and initialize the main thread context.
//     
//     2) Parse the specified snapshot and disk files. This will initialize:
//        * The `globals.snapshot` consisting of the register state and the physical memory state.
//          (If no snapshot file format was specified `preboot_initialization` still initializes `globals.snapshot`.)
//        * If specified the `globals.vhdx_info`.
//        * If contained in the snapshot, the `context->vmbus`.
//        
//     3) If the system is in snapshot mode (i.e. the `--` was not used) the main thread
//        creates a thread for the `hacky_display.c` and then simply continues executing from the snapshot
//        by calling `start_execution_hypervisor`.
//        
//     4) Otherwise, the main thread loads the list of currently active modules by parsing `PsLoadedModuleList`
//        and `_PEB_LTR_DATA.InMemoryOrderModuleList` and calls `target_initialize`.
//        Because the main thread is used for `target_initialize`, it can alter the snapshot.
//        
//     5) Once `target_initialize` is done, the snapshot should not change anymore, as the fuzz threads will use 
//        a copy-on-access mechanism. Hence, we map the `globals.snapshot.physical_memory` as read-only to prevent corruption.
//        
//     6) In repro-mode (the `-r <file-named> option was specified), the main thread sets up a single "fuzzing" thread-context,
//        parses the .repro-file and replays all the inputs by calling `target_execute_input`.
//        
//     7) Otherwise we are in fuzzing mode, and the main thread creates `thread_count` threads which start at `start_fuzzing`.
//        `thread_count` defaults to the logical processor count minus two.
//        
//     8) From here, the main thread, on a one second interval, reports statistics and saves coverage files when necessary.
//     
//     
// Fuzzing thread execution flow (`start_fuzzing` function):
//     
//     1) Each fuzzing thread sets up its thread local `context` structure and generates a random seed.
//     
//     2) They then call `target_get_input` followed by `target_execute_input` in a loop,
//        until a timeout or a crash occurs, or until `FUZZ_CASES_BEFORE_RESET` fuzz-cases have been executed.
//        After one of these conditions, the target gets reset to the snapshot using `reset_to_snapshot`.
//        
//     3) If coverage increases or a new unique crash occurs, the input for the fuzz-case (the last input in the fuzz-run!)
//        gets added to the corpus using `add_input`.
//        
//     4) If a crash occurs, it is looked up in the `globals.crash_table` based on a hash of the crashing stack trace. 
//        If the crash is new or smaller than the previous crash, it gets saved to disk.
//        
//        
//                                                                                           - Pascal Beyer 26.03.2024

#ifdef TARGET_SOURCE
#define TARGET_SOURCE_FILE stringify(TARGET_SOURCE)
#else
#define TARGET_SOURCE_FILE "default_target.c"
#endif


#define _CRT_SECURE_NO_WARNINGS

#ifdef _WIN32
#include <intrin.h>
#else
#include <x86intrin.h>
#endif


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <direct.h> // for _mkdir
#else
#include <unistd.h>
#include <curl/curl.h> // To download PDB's
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/eventfd.h>
#include <poll.h>
#endif

#ifdef _WIN32
#define mkdir _mkdir
#else
#define mkdir(a) mkdir((a), 0777)
#endif

#define null ((void *)0)
#define array_count(a) (sizeof(a)/sizeof(*(a)))
#define print(...) print(__VA_ARGS__)
#define not_implemented()               (print("%s(%d): Not implemented in function %s.\n",      __FILE__, __LINE__, __FUNCTION__), os_panic(1337))
#define invalid_code_path()             (print("%s(%d): Invalid code path in function %s.\n",    __FILE__, __LINE__, __FUNCTION__), os_panic(1337))
#define invalid_default_case() default: (print("%s(%d): Invalid default case in function %s.\n", __FILE__, __LINE__, __FUNCTION__), os_panic(1337))
#define assert(expr)        (!(expr) ?  (print("%s(%d): Assert fired '%s' in function %s.\n",    __FILE__, __LINE__, #expr, __FUNCTION__), os_panic(1337), 1) : 0)
#define false 0
#define true  1
#define offset_in_type(type, member) (s64)(&((type *)0)->member)

#define stringify__internal(a) #a
#define stringify(a) stringify__internal(a)

#define _static_assert_2(expr, line) static int _static_assert_declaration_##line[(expr) ? 1 : -1]
#define _static_assert_1(expr, line) _static_assert_2(expr, line)
#define static_assert(expr) _static_assert_1(expr, __LINE__)


#define thread_local _Thread_local
#define no_return    _Noreturn

#ifdef _WIN32

#define os_debug_break() (IsDebuggerPresent() ? (__debugbreak(), 1) : 0)
#define align_type(n) __declspec(align(n))

#else

#include <signal.h>
#include <sys/ptrace.h>

static int __is_debugger_present;
#define os_debug_break() (__is_debugger_present ? ({__asm__ volatile("int3");}) : (void)0)
#define align_type(n) __attribute__((aligned(n)))

// @note: This really sucks, clang does not allow __FUNCTION__ to be compile time concatinated with other string literals.
//        Hence, we use file and line number as __FUNCTION__.
#define __FUNCTION__ __FILE__ ":" stringify(__LINE__)

#endif

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef struct{
    u64 low;
    u64 high;
} u128;

typedef char      s8;
typedef short     s16;
typedef int       s32;
typedef long long s64;

typedef s64 smm;

typedef struct{ u64 /*fd for lunix*/Unused; } HANDLE;

#if _WIN32
typedef u32 THREAD_RETURN;
#else
typedef void *THREAD_RETURN;
#endif

#if _WIN32

__declspec(dllimport) int GetLastError(void);
__declspec(dllimport) void Sleep(u32 dwMilliseconds);
__declspec(dllimport) u32 IsDebuggerPresent(void);

__declspec(dllimport) u64   VirtualQuery(void *lpAddress, void *memory_information, u64 size);
__declspec(dllimport) void *VirtualAlloc(void *lpAddress, u64 dwSize, u32 flAllocationType, u32 flProtect);
__declspec(dllimport) int   VirtualProtect(void *lpAddress, u64 dwSize, u32 flNewProtect, u32 *lpflOldProtect);
__declspec(dllimport) HANDLE CreateThread(void *lpThreadAttributes, u64 dwStackSize, u32 (*lpStartAddress)(void *), void *lpParameter, u32 dwCreationFlags, u32 *lpThreadId);
__declspec(dllimport) int TerminateThread(HANDLE hThread, u32 dwExitCode);

__declspec(dllimport) HANDLE CreateFileA(char *lpFileName, u32 dwDesiredAccess, u32 dwShareMode, void *lpSecurityAttributes, u32 dwCreationDisposition, u32 dwFlagsAndAttributes, void *hTemplateFile);
__declspec(dllimport) int SetFilePointerEx(HANDLE hFile, u64 liDistanceToMove, u64 *lpNewFilePointer, u32 dwMoveMethod);

__declspec(dllimport) int ReadFile(HANDLE hFile, void *lpBuffer, u32 nNumberOfBytesToRead, u32 *lpNumberOfBytesRead, void *lpOverlapped);
__declspec(dllimport) HANDLE CreateFileMappingA(HANDLE hFile, void *lpFileMappingAttributes, u32 flProtect, u32 dwMaximumSizeHigh, u32 dwMaximumSizeLow, char *lpName);

__declspec(dllimport) void *MapViewOfFileEx(HANDLE hFileMappingObject, u32 dwDesiredAccess, u32 dwFileOffsetHigh, u32 dwFileOffsetLow, u64 dwNumberOfBytesToMap, void *lpBaseAddress);
__declspec(dllimport) int GetFileSizeEx(HANDLE FileHandle, u64 *FileSize);
__declspec(dllimport) int GetFileTime(HANDLE FileHandle, u64 *lpCreationTime, u64 *lpLastAccessTime, u64 *lpLastWriteTime);
__declspec(dllimport) u32 GetFinalPathNameByHandleA(HANDLE FileHandle, u8 *out_FilePath, u32 FilePathSize, u32 Flags);

__declspec(dllimport) int CloseHandle(HANDLE hObject);
__declspec(dllimport) int SetPriorityClass(u64 hProcess, u32 dwPriorityClass);

struct win32_find_data{
    u32 file_attributes;
    struct { u32 low; u32 high; } creation_time;
    struct { u32 low; u32 high; } last_access_time;
    struct { u32 low; u32 high; } last_write_time;
    u32 file_size_high;
    u32 file_size_low;
    u32 reserved0;
    u32 reserved1;
    char file_name[/*MAX_PATH*/260];
    char alternate_file_name[14];
    u32 file_type;
    u32 creator_type;
    u16 finder_flags;
};

__declspec(dllimport) HANDLE FindFirstFileA(char *file_name, struct win32_find_data *find_data);
__declspec(dllimport) int FindNextFileA(HANDLE find_handle, struct win32_find_data *find_data);
__declspec(dllimport) int FindClose(HANDLE hFindFile);



// @note: For downloading .pdb files from the microsoft symbol server.
#pragma comment(lib, "Urlmon.lib")
__declspec(dllimport) int URLDownloadToFileA(void *pCaller, char *URL, char *FileName, int reserved, void *lpfnCb);

// @note: These are really stupid, they essentially proxy to '__rdtsc()' and then reduce the precision.
//        But I guess they come in handy as we can get the associated frequency, thus we use them to 
//        get the current time.
__declspec(dllimport) int QueryPerformanceFrequency(u64 *lpFrequency);
__declspec(dllimport) int QueryPerformanceCounter(u64 *lpCounter);

struct system_info{
    u16 processor_architecture;
    u16 reserved;
    u32 page_size;
    void *minimum_application_address;
    void *maximum_application_address;
    u64 active_processor_mask;
    u32 number_of_processors;
    u32 processor_type;
    u32 allocation_granularity;
    u16 processor_level;
    u16 processor_revision;
};

__declspec(dllimport) void GetSystemInfo(struct system_info *system_info);
#endif

#include "options.c"
#include "uefi_bios.h"
#include "utilities.c"
#include "cpu_state.c"

struct translation_lookaside_buffer{
    struct translation_lookaside_buffer_entry{
        //
        // The guest virtual address divided by the page size, is often called a page number.
        u64 virtual_page_number;
        
        //
        // The address of the page on the host.
        u8 *host_page_address;
        
        //
        // The extra permissions for the page.
        u8 *extra_permission_page;
    } entries[0x1000];
};

// Thread local context structure, passed around to almost every function.
struct context{
    
    int use_hypervisor;
    int snapshot_mode;
    int thread_index;
    
    // 
    // If 'skip_setting_permission_bits' is true, 'translate_page_number_to_physical' skips setting any
    // permission bits. This value should be set/reset whenever we enter a "debugging" function.
    // @Note: Because a "debugging" function often calls another "debugging" function, this value 
    //        should be incremented and decremented rather then set and reset.
    // 
    int skip_setting_permission_bits;
    
    // Fields to manage physical memory for the thread.
    //    'physical_memory'           - Each thread reserves space to copy the entire physical memory space of the guest.
    //    'physical_memory_size'      - Same as 'globals.physical_memory_size'.
    //    'physical_memory_copied'    - A bitmap (one bit per page) which is set when the page (in context->physical_memory) was copied from the original snapshot.
    //                                  The original snapshot is at (globals.snapshot.physical_memory).
    //    'physical_memory_dirty'     - A bitmap (one bit per page) which is set when the page was written during the current fuzz run.
    //                                  This allows us to only track dirty pages once.
    u8 *physical_memory;
    u64 physical_memory_size;
    u8 *physical_memory_copied;    // One bit per page, set when we copy a page from the snapshot (globals.snapshot.physical_memory) to the thread local memory (context->physical_memory).
    u8 *physical_memory_dirty;     // One bit per page, set when we write a page from the thread local memory (context->physical_memory). @WARNING: This is only used if 'globals.fuzzing'
    u8 *physical_memory_executed;  // One bit per page, set when we emit jit for a page.
    u64 amount_of_dirty_physical_pages;
    u64 *dirty_physical_pages;
    
    //
    // These are separate, as coverage arena only ever wants page aligned memory.
    //
    struct memory_arena permanent_arena;
    struct memory_arena coverage_arena; // Used to allocated pages for the 'coverage_page_table' (see globals.coverage_page_table).
    struct memory_arena scratch_arena; // Used for random allocations that are not supposed to last. Reset at random points that feel appropriate.
    
    // A page of memory which is written to, if the framebuffer would be written.
    u8 *fake_page;
    
    //
    // We cache the last accessed coverage page, because usually coverage pages are accessed linearly.
    //
    u64 cached_coverage_page_index;
    u8 *cached_coverage_page;
    
    //
    // Fields that are reset per fuzz case.
    //
    struct{
        u64 coverage_increase;
        
        // This value is reset to 'FUZZ_CASE_TIMEOUT'.
        // It then counts down whenever an instruction is executed.
        // When it reaches 0, we exit with CRASH_timeout, which causes a reset.
        s64 fuzz_case_timeout;
        
        union{
            struct{
                u64 crash_address;
                enum crash_type crash;
            };
            struct crash_information crash_information;
        };
    };
    
    //
    // A 4 level page table containing one byte of extra permissions per byte of guest virtual address space.
    //
    u64 extra_permission_page_table[0x200];
    
    //
    // Fields that are reset in 'reset_to_snapshot'.
    //
    struct{
        
        //
        // Used for heap allocation tracking.
        //
        u64 big_allocation_at; // This is here to speed-up heap allocations while fuzzing.
        
        struct translation_lookaside_buffer read_tlb;    // speed up 'guest_read'.
        struct translation_lookaside_buffer write_tlb;   // speed up 'guest_write'.
        struct translation_lookaside_buffer execute_tlb; // speed up 'prefetch_instruction'.
        
        struct memory_arena fuzz_run_arena;
        
        // We should never actually write to the vhdx, hence we use the temporary write table instead, this reset every fuzz run.
        u64 temporary_write_table[0x200];
    };
    
    //
    // Used for the jit while executing.
    //
    struct instruction_cache_entry{
        void *instruction_jit; // This should not be used directly, call into 'context->jit_entry(context, registers, instruction_cache_entry)' instead.
        u64 physical_rip;
    } instruction_cache[INSTRUCTION_CACHE_SIZE];
    
    //
    // Jit helper members.
    //
    struct{
        
        //
        // The jit_pool holds the rwx-memory used for the jit functions. 
        // We reserve a lot, but then only page it in in 1MB chunks.
        //
        struct {
            u8 *base;
            u8 *current;
            smm committed;
            smm reserved;
        } jit_pool;
        
        //
        // The jit entry, only call this if you want to enter the jit! 
        // This is called from 'start_execution_jit'.
        //
        u8 *(*jit_entry)(struct context *context, struct registers *registers, struct instruction_cache_entry *instruction_cache_entry);
        
        //
        // The 'jit_exit' undoes the stack frame created by 'jit_entry'.
        //
        u8 *jit_exit;
        
        //
        // This is here so we can rip-relative call guest_read/guest_write.
        //
        u8 *jit_import_guest_read;
        u8 *jit_import_guest_read_for_write;
        u8 *jit_import_guest_write;
        
        u8 *jit_guest_read_wrappers[2 * 6]; // 2 - needs write permission {0, 1}, 6 - size {1, 2, 4, 8, 16, 32}
        u8 *jit_guest_write_wrappers[6];    // 6 - size {1, 2, 4, 8, 16, 32}
        u8 *jit_translate_rip_to_physical;
        
        struct{
            u64 maximal_size_minus_one;
            u64 amount_of_entries;
            
            struct jit_block{
                u8 *jit_code;
                u64 physical_rip;
            } *entries;
        } jit_block_table;
        
        _Alignas(64) u8 jit_scratch[64];
        
        // This field is the JIT equivalent of setting the RF flag
        // to skip the breakpoint you have just handled.
        int jit_skip_one_breakpoint;
    };
    
    //
    // Hypervisor members.
    //
    HANDLE Partition;
    u32 hypervisor_require_auto_eoi;
    u64 potentially_usermode_snapshotting_breakpoint;
    
    
    // :timer_interrupts
    // 
    // This is based of 'hv_x64_msr_reference_tsc_page', 'hv_x64_msr_stimer0_{count|config}' and 'ia32_tsc'.
    // We have to base our sense of time / timer-interrupts based of the guest 'ia32_tsc' and not the 
    // host sense of time, as we do not want to send timer-interrupts early and we do increment the guest
    // 'ia32_tsc' for time spend outside of guest execution.
    u64 next_timer_interrupt_time_or_zero; 
    
    // 
    // CPU state members.
    // 
    struct registers registers;
    
    struct{
        struct vmbus_channel{
            struct vmbus_channel *next;
            
            enum vmbus_device_kind{
                VMBUS_DEVICE_unknown,
                VMBUS_DEVICE_scsi,
                VMBUS_DEVICE_mouse,
                VMBUS_DEVICE_keyboard,
                VMBUS_DEVICE_framebuffer,
            } device_kind;
            
            u32 channel_id;
            u32 connection_id;
            u8  monitor_id;
            
            u32 gpadl_id;
            u32 read_ring_buffer_pages;
            
            struct vmbus_ring_buffer{
                u64 header;
                u64 amount_of_pages;
                u64 *pages;
            } read_buffer; 
            struct vmbus_ring_buffer send_buffer;
            
        } *channels;
        
        struct gpadl{
            struct gpadl *next;
            
            u32 channel_id;
            u32 gpadl_id;
            
            u32 amount_of_pages;
            u64 pages[];
            
        } *gpadls;
        
        u64 monitor_page1;
        u64 monitor_page2;
        
        struct vmbus_channel *keyboard;
        struct vmbus_channel *mouse;
        
        u32 channel_offer_at;
        int send_packet_skip_interrupt;
    } vmbus;
};

static char *vmbus_device_kind_string[] = {
    [VMBUS_DEVICE_unknown] = "unknown",
    [VMBUS_DEVICE_scsi] = "scsi",
    [VMBUS_DEVICE_mouse] = "mouse",
    [VMBUS_DEVICE_keyboard] = "keyboard",
    [VMBUS_DEVICE_framebuffer] = "framebuffer",
};

static void invalidate_translate_lookaside_buffers(struct context *context){
    memset(&context->read_tlb,    0xff, sizeof(context->read_tlb));
    memset(&context->write_tlb,   0xff, sizeof(context->write_tlb));
    memset(&context->execute_tlb, 0xff, sizeof(context->execute_tlb));
}


// This function is needed because after we have jit'ed code for a physical address,
// we need to not have it in the tlb anymore. 
// Otherwise, the code that invalidates the JIT if the page is written again might be skipped.
static void clear_specific_physical_address_from_write_tlb(struct context *context, u64 page_index){
    u8 *host_page_address = context->physical_memory + (page_index << 12);
    
    for(u32 index = 0; index < array_count(context->write_tlb.entries); index++){
        if(context->write_tlb.entries[index].host_page_address == host_page_address){
            memset(&context->write_tlb.entries[index], 0xff, sizeof(context->write_tlb.entries[index]));
        }
    }
}

struct crash_information enter_debugging_routine(struct context *context){
    
    struct crash_information original_crash_information = context->crash_information;
    original_crash_information.debug_depth = context->skip_setting_permission_bits;
    
    context->crash_information = (struct crash_information){0};
    context->skip_setting_permission_bits += 1;
    return original_crash_information;
}

void exit_debugging_routine(struct context *context, struct crash_information original_crash_information){
    context->crash_information = original_crash_information;
    context->skip_setting_permission_bits -= 1;
    
    assert(original_crash_information.debug_depth == context->skip_setting_permission_bits);
}



struct globals{
    
    int fuzzing; // Set once the main thread is about to start the threads.
    
    s64 thread_count;
    
    struct input *inputs;
    s64 maximal_amount_of_inputs;
    s64 amount_of_inputs;
    s64 amount_of_acquired_inputs; // The amount of inputs which are already reserved by some thread, increment this, then copy, then increment amount_of_inputs.
    
    //
    // Tracking information.
    //
    s64 coverage;
    s64 crashes;
    s64 unique_crashes;
    s64 fuzz_cases;
    s64 timeouts;
    s64 instructions_executed;
    s64 resets;
    s64 instructions_in_timeout_inputs;
    
    struct hook{
        //
        // If 'rip' is hit, we _hook_ from the emulator and execute 'hook'. If the 'hook' function
        // alters 'registers->rip', we _jump_ there, otherwise execution continues normally.
        //
        u64 rip;
        void (*hook)(struct context *context, struct registers *registers);
    } hook_table[HOOK_TABLE_SIZE];
    
    // :double_fetch_detection
    // 
    // If `input_buffer_host_physical` is set, any access to this physical page
    // will result in a call to `target_read_guest_input_buffer`. 
    // This allows us to deterministically _swap_ the values contained in the input buffer
    // on each access and thus detect "double_fetch" vulnerabilities.
    u64 input_buffer_physical_address;
    
    //
    // The coverage page table is a 4 level page table, which holds one bit per byte of 'guest virtual address space'.
    // It is atomically allocated using an arena for each thread ('context->coverage_arena').
    //
    u64 coverage_page_table[0x200];
    
    _Alignas(16) struct crash_table_entry{
        u64 crash_hash;
        u32 input_size;
        enum crash_type crash_type;
    } crash_table[CRASH_TABLE_SIZE];
    
    // A spin lock, which is used to save crashing inputs atomically, see 'mark_address_as_crashing_and_lock_if_we_should_save_the_crash'.
    struct ticket_spinlock crash_repro_file_printing_lock;
    
    //
    // Debugger members.
    //
    
    // This value is set if we are running in snapshot mode, or if the '-d' option was specified.
    // It is used to:
    //      1) Only check for read/write breakpoints in the jit, if we are debugging.
    //      2) Skip some checks in 'jit_execute_until_exception', which check if we should break in the debugger.
    //      3) Determine how we handle various "error" conditions.
    int debugger_mode;
    
    // Set to make sure we don't invoke 'handle_debugger' recursively.
    int in_debugger;
    
    // Determines how 'print_registers' behaves.
    int print_mode;
    
    // Breakpoint state used by the jit. The hypervisor also uses the 'oneshot' flag for breakpoints 0-3.
    struct breakpoint{
        enum breakpoint_type{
            BREAKPOINT_none,
            BREAKPOINT_execute,
            BREAKPOINT_read,
            BREAKPOINT_write,
            BREAKPOINT_alloc,
            BREAKPOINT_free,
        } type;
        enum breakpoint_flags{
            BREAKPOINT_FLAG_none    = 0,
            BREAKPOINT_FLAG_oneshot = 1,
        } flags;
        u64 address;
        u64 length;
    } breakpoints[0x10]; // Last breakpoint never used, so we can have this be 'BREAKPOINT_none' terminated.
    
    s32 breakpoint_count;
    s32 breakpoint_hit_index;
    u32 single_stepping;
    u32 print_trace;
    FILE *trace_file;
    struct string module_load_breakpoint_string;
    char KiKernelSysretExit_process_name[16];
    
    struct{
        // @note: While there could be diverging module lists, we only really care about the starting ones
        //        and the ones in 'snapshot_mode' and so we keep the 'module_list' globally instead of per context.
        struct loaded_module *first;
        struct loaded_module *last;
    } module_list;
    
    u64 _padding3[2];
    
    struct{
        u8 *physical_memory;
        u64 physical_memory_size;   // Just here for completeness, I think everyone reads 'context->physical_memory_size' which is the same.
        
        struct registers registers;  // The registers of the initial state.
    } snapshot;
    
    struct{
        u64 amount_of_bat_table_entries;
        u64 *block_allocation_table;
        u64 sectors_per_block;
        u64 chunk_ratio;
    } vhdx_info;
    
    struct{
        u64 cluster_size;
        u64 L2_entries;
        u64 *L1_table;
    } qcow2_info;
    
    struct{
        enum virtual_disk_kind{
            VIRTUAL_DISK_none,
            VIRTUAL_DISK_vhdx,
            VIRTUAL_DISK_qcow2,
        } virtual_disk_kind;
        
        u8 *mapped_address;
        u64 virtual_size;
        u64 modification_time;
        u64 sector_size_in_bytes;
        struct string full_file_path;
    } disk_info;
    
    struct context *main_thread_context;
    
    u64 big_allocation_base;
    u64 process_cr3;
    
    enum cpu_vendor{
        VENDOR_INTEL,
        VENDOR_AMD,
    } cpu_vendor;
    
    // :calculate_tsc_frequency_because_windows_wont_tell_me
    u64 starting_tsc;
    u64 starting_qpc;
} globals;


// :calculate_tsc_frequency_because_windows_wont_tell_me
// 
// I could not find a way to reliably get the tsc frequency.
// Hence, I start timers in the beginning and re-calculate
// the frequency here.
u64 calculate_tsc_frequency(void){
    u64 ending_tsc = __rdtsc();
    u64 ending_qpc;
    QueryPerformanceCounter(&ending_qpc);
    
    u64 cycles = (ending_tsc - globals.starting_tsc);
    u64 ticks  = (ending_qpc - globals.starting_qpc);
    
    u64 frequency;
    QueryPerformanceFrequency(&frequency);
    
    // ticks / frequency = seconds
    // cycles / (ticks / frequency) = cycles/seconds
    // (cycles * frequency) / ticks = cycles/seconds
    
    u64 high;
    u64 low = _umul128(cycles, frequency, &high);
    
    u64 remainder;
    u64 tsc_frequency = _udiv128(high, low, ticks, &remainder); // @cleanup: Make sure this does not crash?
    
    return tsc_frequency;
}

void set_crash_information(struct context *context, enum crash_type crash, u64 crash_address){
    if(context->crash == CRASH_none){
        context->crash         = crash;
        context->crash_address = crash_address;
        
        if((crash == CRASH_internal_error) && !globals.fuzzing && !globals.in_debugger) os_debug_break();
    }
}

// Needed in 'parse_dmp' to obtain some addresses.
struct crash_information start_execution_jit(struct context *context);

// Everyone should just be able to enter the debugger when they please.
void handle_debugger(struct context *context);

#include "vhdx.c"
#include "qcow2.c"
#include "disk.c"

#include "apic.c"
#include "memory_unit.c"

static u64 patch_in_kernel_cr3(struct context *context){
    u64 cr3 = context->registers.cr3;
    if(context->registers.vtl_state.current_vtl == 0){
        // "If CR4.PCIDE = 1, bit 63 of the source operand to MOV to CR3 determines 
        //  whether the instruction invalidates entries in the TLBs and the paging-structure caches."
        u64 kpcr = (context->registers.cs.selector & 3) ? context->registers.gs_swap : context->registers.gs_base;
        
        // @note: If we don't have a kpcr I assume, that we are pre-boot and don't want to change the cr3.
        if(kpcr){
            u64 kernel_page_table = guest_read(u64, kpcr + 0xb000);
            if(kernel_page_table){ // This happend to be 0, when VaShadows might have been off? Investigate.
                context->registers.cr3 = kernel_page_table & 0x7ffffffffffff000;
            }
        }
    }
    return cr3;
}

static u64 calculate_time_reference_counter(struct context *context, struct registers *registers){
    
    u8 *HvlpReferenceTscPage = get_physical_memory_for_read(context, registers->hv_x64_msr_reference_tsc_page & ~0xfff);
    
    u64 TscScale  = *(u64 *)(HvlpReferenceTscPage +  8);
    u64 TscOffset = *(u64 *)(HvlpReferenceTscPage + 16);
    
    u64 ScaledTscHigh = 0;
    _umul128(registers->ia32_tsc, TscScale, &ScaledTscHigh);
    
    
    return ScaledTscHigh + TscOffset;
}

void set_next_timer_interrupt_time(struct context *context, struct registers *registers){
    if(!context->use_hypervisor) return;
    if(!(registers->hv_x64_msr_reference_tsc_page & 1)) return;
    
    u64 time_reference_counter = calculate_time_reference_counter(context, registers);
    
    u64 timer = registers->hv_x64_msr_stimer0_count;
    if(registers->hv_x64_msr_stimer0_config & /*periodic*/2) timer += time_reference_counter;
    
    if(timer > time_reference_counter){
        context->next_timer_interrupt_time_or_zero = timer;
    }
}


#include "pdb.c"
#include "loaded_module.c"
#include "coverage.c"

#include "interrupts.c"

#include "vmbus.c"

#include "parse_dmp.c"
#include "snapshot.c"
#include "preboot_initialization.c"

#if ENABLE_VMRS
#include "vmrs_parser.c"
#endif

// Needed for linux for some reason.
#define HACKY_EXTERN extern 
#include "hacky_display.h"

#include "hooks.c"
#include "debugger.c"

#include "instruction_helpers.c"

#include "jit.c"
#include "hacky_display_input_handling.c"

#if _WIN32
#include "hyperv.c"
#else
#include "kvm.c"
#endif

//_____________________________________________________________________________________________________________________
// Input handling routines.

// WARNING: also defined in 'linux_weak_aliases.c'.
struct input{
    u8 *data;
    s64 size;
};

void add_input(struct input input){
    
    //
    // Allocate a slot for the input.
    //
    s64 input_index = atomic_postincrement(globals.amount_of_acquired_inputs);
    if(input_index >= globals.maximal_amount_of_inputs){
        print("Error: Cannot save input as we have exceeded the maximal amount of input.\n");
        print("       In the future this should maybe be dynamic....\n");
        return;
    }
    
    //
    // Copy the input into the slot.
    //
    globals.inputs[input_index] = input;
    
    //
    // Wait until we are supposed to finalize our input.
    //
    while(atomic_load(s64, globals.amount_of_inputs) < input_index) _mm_pause();
    
    //
    // Tell all the other threads, that this input is now done and they can use it.
    //
    s64 check_index = atomic_postincrement(globals.amount_of_inputs);
    assert(check_index == input_index);
}

struct input get_random_input(struct memory_arena *arena, u64 *seed){
    if(!globals.amount_of_inputs){
        // @note: We allow not adding a single input to allow for purely generational fuzzers to work.
        print("Warning: '" __FUNCTION__ "' called with 'globals.amount_of_inputs == 0'.\n");
        print("         Returning zero-sized input.\n");
        return (struct input){.data = push_data(arena, u8, 0), .size = 0};
    }
    struct input input = globals.inputs[xor_shift(seed) % globals.amount_of_inputs];
    input.data = memcpy(push_data(arena, u8, input.size), input.data, input.size);
    return input;
}

//_____________________________________________________________________________________________________________________
// Target includes.

#include "core_target_helpers.c"
#include "target_specific_code_api.h"

#include TARGET_SOURCE_FILE

//_____________________________________________________________________________________________________________________
// Thread context managing routines.

void reset_to_snapshot(struct context *context){
    
    // 
    // Reset all pages marked as dirty:
    // 
    for(u64 dirty_page_index = 0; dirty_page_index < context->amount_of_dirty_physical_pages; dirty_page_index++){
        u64 dirty_page_address = context->dirty_physical_pages[dirty_page_index];
        
        u64 page_index = dirty_page_address >> 12;
        u64 byte_index = page_index >> 3;
        u64 bit_index  = page_index & 7;
        u64 bit = 1ull << bit_index;
        assert((context->physical_memory_dirty[byte_index] & bit));
        context->physical_memory_dirty[byte_index] &= ~bit;
        
        memcpy(context->physical_memory + dirty_page_address, globals.snapshot.physical_memory + dirty_page_address, 0x1000);
    }
    context->amount_of_dirty_physical_pages = 0;
    
#if 0
    for(u64 page_index = 0; page_index < (context->physical_memory_size >> 12); page_index++){
        
        u64 byte_index = page_index >> 3;
        u64 bit_index  = page_index & 7;
        
        u64 bit = 1ull << bit_index;
        
        int page_is_present = (context->physical_memory_copied[byte_index] & bit) != 0;
        if(page_is_present){
            assert(memcmp(context->physical_memory + page_index * 0x1000, globals.snapshot.physical_memory + page_index * 0x1000, 0x1000) == 0);
        }
    }
#endif
    
    context->registers = globals.snapshot.registers;
    
    invalidate_translate_lookaside_buffers(context);
    
    //
    // Reset the fuzz case arena.
    //
    context->fuzz_run_arena.current = context->fuzz_run_arena.base;
    
    // Reset the vhdx _write_ state.
    memset(context->temporary_write_table, 0, sizeof(context->temporary_write_table));
    
    //
    // Reset the extra permissions, these are cleared every new fuzz run.
    // While this means you don't have extra permissions for code which you run 
    // prior to 'fuzzing', this allows the reset to be relatively fast.
    //
    memset(context->extra_permission_page_table, 0, sizeof(context->extra_permission_page_table));
    context->big_allocation_at = 0;
    
    // 
    // Notify the target-specific code, that we reset the target.
    // 
    target_reset(context);
}

// @note: I have renamed this like 5 times, but the name is still bad...
//        Used to initialize both the main threads context structure, 
//        as well as the context structure of each fuzzing thread.
void context_initialize_main_and_thread_context_common(struct context *context){
    initialize_arena(&context->fuzz_run_arena);
    initialize_arena(&context->coverage_arena);
    initialize_arena(&context->permanent_arena);
    initialize_arena(&context->scratch_arena);
    
    initialize_jit(context);
    invalidate_translate_lookaside_buffers(context); // This initializes the tlbs.
    
    context->fake_page = arena_allocate_struct(&context->permanent_arena, 0x1000, 0x1000);
    context->dirty_physical_pages = push_data(&context->permanent_arena, u64, DIRTY_PHYSICAL_PAGE_CAPACITY);
    
    context->cached_coverage_page_index = (u64)-1;
}

struct context *allocate_and_initialize_thread_context(int thread_index){
    struct context *context = os_allocate_memory(sizeof(*context));
    //
    // First reserve the 'physical_memory' for the thread.
    // The memory will then get incrementally 'paged-in' during execution.
    //
    
    u64 memory_size = globals.snapshot.physical_memory_size;
    u64 page_bitmap_size = (memory_size / 0x1000) / 8;
    
    context->physical_memory_size      = memory_size;
    context->physical_memory           = os_reserve_memory(memory_size);
    context->physical_memory_copied    = os_allocate_memory(page_bitmap_size);
    context->physical_memory_dirty     = os_allocate_memory(page_bitmap_size);
    context->physical_memory_executed  = os_allocate_memory(page_bitmap_size);
    
    context->registers = globals.snapshot.registers;
    
    context->fuzz_case_timeout = FUZZ_CASE_TIMEOUT;
    
    context_initialize_main_and_thread_context_common(context);
    
    // @note: This seems a bit hacky, as the threads share some memory, 
    //        but I cannot figure out any problems with it, so let's keep it like this for now.
    context->vmbus = globals.main_thread_context->vmbus;
    
    context->thread_index = thread_index;
    
    target_reset(context);
    
    return context;
}

//_____________________________________________________________________________________________________________________
// Input handling routines.

int save_inputs_to_file(char *file_name, struct input *inputs, smm amount_of_inputs){
    
    FILE *crash_file = fopen(file_name, "wb");
    if(!crash_file){
        print("Cannot write '%s'. Likely no crashes folder, please make one!\n", file_name);
        return 1;
    }
    fclose(crash_file); // Reset the file.
    
    crash_file = fopen(file_name, "ab"); // Open the file for append.
    
    fwrite(&amount_of_inputs, sizeof(amount_of_inputs), 1, crash_file);
    
    for(smm input_index = 0; input_index < amount_of_inputs; input_index++){
        struct input input = inputs[input_index];
        
        fwrite(&input.size, sizeof(input.size), 1, crash_file);
        fwrite(inputs[input_index].data, 1, input.size, crash_file);
    }
    
    fclose(crash_file);
    
    return 0;
}

// Returns the 'crash_information' of the last input.
struct crash_information replay_inputs(struct context *context, struct input *inputs, smm amount_of_inputs, int print_result){
    struct crash_information result = {0};
    
    smm input_index = 0;
    for(; (input_index < amount_of_inputs) && result.crash_type == CRASH_none; input_index++){
        context->coverage_increase = 0;
        context->fuzz_case_timeout = FUZZ_CASE_TIMEOUT;
        
        result = target_execute_input(context, inputs[input_index]);
        
        if(print_result){
            print_result_status(context, "replay input %lld", input_index);
            print("    Exit Code    0x%x\n", (u32)context->registers.rax);
            print("    Coverage     %lld\n", context->coverage_increase);
            print("    Instructions %llu\n", FUZZ_CASE_TIMEOUT - context->fuzz_case_timeout);
            print("\n\n");
        }
    }
    
    if(input_index < amount_of_inputs){
        result.crash_type = CRASH_replaying_inputs_crashed_earlier_then_expected;
    }
    
    return result;
}

void minimize_crashing_inputs(struct context *context, struct input *inputs, smm amount_of_inputs, char *crash_file_name){
    
    struct crash_information initial_result = replay_inputs(context, inputs, amount_of_inputs, 0);
    if(initial_result.crash_type == CRASH_none){
        print("Error: Initial inputs did not crash. Cannot minimize!\n");
        return;
    }
    
    if(initial_result.crash_type == CRASH_replaying_inputs_crashed_earlier_then_expected){
        print("WARNING: The initial inputs crashed prior to the _last_ input being executed.\n");
        print("         This usually means something screwed up. But if you build these inputs\n");
        print("         by hand, ... or something, you can press enter to continue.\n");
        getchar();
    }
    
    reset_to_snapshot(context);
    
    struct input *copied_inputs = malloc(sizeof(struct input) * amount_of_inputs);
    smm amount_of_copied_inputs = 0;
    
    smm test_input_index = 0;
    while(test_input_index < amount_of_inputs){
        print("%d of %d (%d)\n", test_input_index, amount_of_inputs, amount_of_copied_inputs);
        
        //
        // Execute all the inputs we have deemed necessary.
        //
        replay_inputs(context, copied_inputs, amount_of_copied_inputs, 0);
        
        //
        // Omit 'test_input_index' but execute [test_input_index + 1, amount_of_inputs)
        // to check if 'test_input_index' is necessary.
        //
        struct crash_information result = replay_inputs(context, inputs + (test_input_index + 1), amount_of_inputs - (test_input_index + 1), 0);
        
        
        print("crash_type %s, initial_result.crash_type %s\n", crash_type_string[result.crash_type], crash_type_string[initial_result.crash_type]);
        if(result.crash_type != initial_result.crash_type){
            //
            // The 'test_input_index' was apparently necessary, copy it into the copied inputs.
            //
            
            copied_inputs[amount_of_copied_inputs++] = inputs[test_input_index];
        }
        
        // Advance the input that we test.
        test_input_index++;
        
        // Reset this snapshot so we can test the next input.
        reset_to_snapshot(context);
    }
    
    save_inputs_to_file(crash_file_name, copied_inputs, amount_of_copied_inputs);
    print("wrote '%s'\n", crash_file_name);
}


THREAD_RETURN start_fuzzing(void *thread_index){
    
    //
    // Start setting up the thread 'context' structure.
    //
    
    struct context *context = allocate_and_initialize_thread_context((int)(s64)thread_index);
    
#if 0
    u64 *seed = &(u64){0};
    {
        // Get random seeds using rdrand. We technically do not need this quality of seed, but
        // its one of the easiest ways and I was uncomfortable with '__rdtsc()' though it is probably
        // just as good and more portable.
        int success = 0;
        while(!success) success = _rdrand64_step(seed);
    }
#elif 1
    // 
    // Get an initial seed from __rdtsc(). This should be good enough randomness.
    // 
    u64 *seed = &(u64){__rdtsc()};
#else
    u64 initial_seed = 0x1337133713371337 + (u64)thread_index;
    
    u64 *seed = &(u64){initial_seed};
#endif
    
    print("Initial seed %p\n", *seed);
    
    struct input *saved_inputs = malloc(FUZZ_CASES_BEFORE_RESET * sizeof(*saved_inputs));
    
    u64 instructions_executed_this_fuzz_run = 0;
    
    for(s64 fuzz_case = 0, fuzz_cases_since_reset = 0;; fuzz_case++, fuzz_cases_since_reset++){
        
        //
        // Reset the coverage increase, as we are starting a new fuzz case.
        //
        context->coverage_increase = 0;
        
        // 
        // Reset the fuzz case timeout, as we are beginning a new fuzz case.
        // 
        context->fuzz_case_timeout = FUZZ_CASE_TIMEOUT;
        
        //
        // Ask the target-specific code to give us an input.
        //
        struct input input = target_get_input(context, seed);
        assert(input.size > 0);
        saved_inputs[fuzz_cases_since_reset] = input;
        
        //
        // Ask the target-specific code to execute the input.
        // @note: These two calls are separated, as we use 'target_execute_input' also while replaying.
        //
        struct crash_information result = target_execute_input(context, input);
        
        u64 coverage_increase     = context->coverage_increase;
        int should_reset          = (result.crash_type != CRASH_none);
        int should_feedback_input = (coverage_increase > 0);
        
        instructions_executed_this_fuzz_run += FUZZ_CASE_TIMEOUT - context->fuzz_case_timeout;
        
        if(result.crash_type != CRASH_none && (SAVE_TIMEOUTS || result.crash_type != CRASH_timeout)){
            //
            // We crashed, report this stat and check if this crash is new/should be saved.
            //
            atomic_increment(globals.crashes);
            
#if USE_STACK_TRACE_HASH_FOR_CRASH_UNIQUENESS
            u64 crash_hash = calculate_stack_trace_hash(context);
#else
            u64 crash_hash = context->registers.rip;
#endif
            
            //
            // Lookup the crash in the 'globals.crash_table'.
            // 
            enum crash_info_status{
                CRASH_table_is_full,
                CRASH_is_new_and_unique,
                CRASH_is_old_but_smaller,
                CRASH_is_old_and_boring,
            } crash_status = CRASH_table_is_full; 
            
            {
                u64 crash_index = crash_hash;
                u32 input_size  = (u32)fuzz_cases_since_reset;
                xor_shift(&crash_index);
                
                for(int table_index = 0; table_index < (int)array_count(globals.crash_table); table_index++){
                    int index = (crash_index + table_index) & (array_count(globals.crash_table) - 1);
                    
                    //
                    // Atomically read the table entry.
                    //
                    struct crash_table_entry entry = atomic_load(struct crash_table_entry, globals.crash_table[index]);
                    
                    //
                    // Discard cases where we should continue or return a _boring_ result.
                    //
                    if(entry.crash_hash == crash_hash && entry.crash_type == result.crash_type){
                        if(input_size >= entry.input_size){ 
                            crash_status = CRASH_is_old_and_boring;
                            break;
                        }
                    }else if(entry.crash_type){
                        continue;
                    }
                    
                    //
                    // Attempt to atomically swap the entry into the slot.
                    //
                    
                    int swap_success = _InterlockedCompareExchange128((void volatile *)&globals.crash_table[index], /*low*/((u64)result.crash_type << 32) | input_size, /*high*/crash_hash, (s64 *)&entry);
                    
                    if(swap_success){
                        //
                        // We succeeded in swapping in the 'entry', acquire the file lock!
                        //
                        ticket_spinlock_lock(&globals.crash_repro_file_printing_lock);
                        
                        //
                        // Check if we are still the best, or if there is a better one in line
                        // the other one might in theory actually have already executed, as there might be
                        // time between the '_InterlockedCompareExchange128' and the 'ticket_spinlock_lock'.
                        // But if our input size is good by the time we have the lock everything is good!
                        //
                        if(atomic_load(u32, globals.crash_table[index].input_size) == input_size){
                            crash_status = entry.crash_type ? CRASH_is_old_but_smaller : CRASH_is_new_and_unique;
                            break;
                        }
                        
                        ticket_spinlock_unlock(&globals.crash_repro_file_printing_lock);
                    }
                    
                    table_index--; // Someone was faster then us, check in the next iteration if the one was our rip.    
                }
                
                assert(crash_status != CRASH_table_is_full);
            }
            
            //
            // If its a new crash, report that stat and save the input.
            //
            if(crash_status == CRASH_is_new_and_unique && (SAVE_TIMEOUTS || result.crash_type != CRASH_timeout)){
                atomic_increment(globals.unique_crashes);
                should_feedback_input |= (result.crash_type != CRASH_timeout); // Don't feedback timeouts if they did not increase coverage.
                
                print_crash_information(context, &result);
            }
            
            //
            // If we should save the input, the 'crash_repro_file_printing_lock' is held.
            // Save the input and unlock once we are done.
            //
            if(crash_status != CRASH_is_old_and_boring){
                
                char file_name_buffer[0x100];
                char *crash_string = crash_type_string[result.crash_type];
                
#if USE_STACK_TRACE_HASH_FOR_CRASH_UNIQUENESS
                snprintf(file_name_buffer, sizeof(file_name_buffer), "crashes/%s_at_%p_%p.crash", crash_string, context->registers.rip, crash_hash);
#else
                snprintf(file_name_buffer, sizeof(file_name_buffer), "crashes/%s_at_%p.crash", crash_string, context->registers.rip);
#endif
                
                save_inputs_to_file(file_name_buffer, saved_inputs, fuzz_cases_since_reset + 1);
                
                if(crash_status == CRASH_is_new_and_unique){
                    print("\nSaved repro file at %s\n", file_name_buffer);
                }
                
                ticket_spinlock_unlock(&globals.crash_repro_file_printing_lock);
            }
        }
        
        //
        // Save the input to the input set, so we use it for coverage feedback!
        //
        if(should_feedback_input){
            
            // Copy the input into stable memory.
            input.data = memcpy(push_data(&context->permanent_arena, u8, input.size), input.data, input.size);
            
            add_input(input);
            
            if(SHOULD_SAVE_INPUTS_TO_CORPUS_FOLDER){
                m128 md5 = hash_md5(input.data, input.size);
                
                char file_name_buffer[0x100];
                snprintf(file_name_buffer, sizeof(file_name_buffer), "corpus/%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x.input",
                        md5._u8[0], md5._u8[1], md5._u8[2], md5._u8[3], md5._u8[4], md5._u8[5], md5._u8[6], md5._u8[7], 
                        md5._u8[8], md5._u8[9], md5._u8[10], md5._u8[11], md5._u8[12], md5._u8[13], md5._u8[14], md5._u8[15]);
                
                FILE *input_file = fopen(file_name_buffer, "wb");
                if(input_file){
                    fwrite(input.data, 1, input.size, input_file);
                    fclose(input_file);
                }
            }
            
            //
            // Report the coverage increase!
            //
            print("Coverage increased! (+%lld)\n", coverage_increase);
            atomic_exchange_add(globals.coverage, coverage_increase);
        }
        
        if(fuzz_cases_since_reset + 1 == FUZZ_CASES_BEFORE_RESET){
            //
            // If this was the last fuzz case in this run mark that we should reset!
            //
            should_reset = 1;
        }
        
        if(should_reset){
            
            atomic_exchange_add(globals.fuzz_cases, fuzz_cases_since_reset + 1);
            fuzz_cases_since_reset = -1;
            
            //
            // Sink all the stats!
            //
            atomic_exchange_add(globals.instructions_executed, instructions_executed_this_fuzz_run);
            atomic_preincrement(globals.resets);
            
            if(result.crash_type == CRASH_timeout){
                u64 instructions_this_input = FUZZ_CASE_TIMEOUT - context->fuzz_case_timeout;
                atomic_exchange_add(globals.instructions_in_timeout_inputs, instructions_this_input);
            }
            
            reset_to_snapshot(context);
            
            instructions_executed_this_fuzz_run = 0;
        }
    }
    
    return 0;
}

THREAD_RETURN initialize_hacky_display(void *);

int main(int argc, char *argv[]){
    
    {
        // 
        // Use __cpuid to determine the cpu vendor.
        // We need to know this so we can return the correct thing in some cpuids.
        // And only set supported registers in the hypervisor.
        // 
        
        int basic_information[4];
        
        __cpuid(basic_information, 0);
        
        char identifier[13];
        memcpy(identifier + 0, (char *)&basic_information[1], 4);
        memcpy(identifier + 4, (char *)&basic_information[3], 4);
        memcpy(identifier + 8, (char *)&basic_information[2], 4);
        identifier[12] = 0;
        
        if(strcmp(identifier, "GenuineIntel") == 0){
            globals.cpu_vendor = VENDOR_INTEL;
        }else if(strcmp(identifier, "AuthenticAMD") == 0){
            globals.cpu_vendor = VENDOR_AMD;
        }else{
            print("Error: Unknown CPU vendor '%s'.\n", identifier);
            return 1;
        }
        
        
        // :calculate_tsc_frequency_because_windows_wont_tell_me
        // 
        // Start a "timer" to messure the frequency of __rdtsc as windows is not willing to tell me.
        globals.starting_tsc = __rdtsc();
        QueryPerformanceCounter(&globals.starting_qpc);
    }
    
    int is_call_for_help = 0;
    for(int arg_index = 0; arg_index < argc; arg_index++){
        char *arg = argv[arg_index];
        
        static char *calls_for_help[] = {
            "-h", "-help", "--help", "-?",
            "/h", "/help", "/?",
        };
        
        for(u32 index = 0; index < array_count(calls_for_help); index++){
            if(strcmp(arg, calls_for_help[index]) == 0) is_call_for_help = 1;
        }
    }
    
    if(is_call_for_help || argc < 2){
        print("Usage: %s [disk] [snapshot] [options...] -- [target options...] -- [options...]\n", argv[0]);
        print("\n");
        print("disk-formats:\n");
        print("    .vhdx\n");
        print("    .qcow2\n");
        print("\n");
        print("snapshot-formats:\n");
        print("    .dmp\n");
        print("    .snapshot\n");
        print("    .vmrs (experimental!)\n");
        print("\n");
        print("options:\n");
        print("    -r <.crash-file> [-m <out-minimized>] | Reproduce a crash and optionally minimize it.\n");
        print("    -d / -debugger                        | Start in the debugger.\n");
        print("    -y / -yes                             | Say 'y' to every '(y/n)' prompt.\n");
        print("    -thread_count <number>                | Specify the number of fuzzing threads (default: #cores - 2).\n");
        print("    -convert <output.snapshot>            | Immediately take a snapshot after loading and then exit.\n");
        print("\n");
        print("Examples:\n");
        print("  %s disk.vhdx                        | Boot in Snapshot Mode from the disk.vhdx.\n", argv[0]);
        print("  %s snap.snapshot -d                 | Debug snap.snapshot in Snapshot Mode.\n", argv[0]);
        print("  %s dump.dmp disk.vhdx -convert snap | Convert the snapshot in dump.dmp to a snap.snapshot.\n", argv[0]);
        print("\n");
        print("  %s snap.snapshot --\n", argv[0]);
        print("      Start fuzzing from the snap.snapshot passing no arguments to the target-specific code.\n");
        print("  %s snap.snapshot -- \\Device\\Afd -- -r bugcheck.crash -d\n", argv[0]);
        print("      Debug a bugcheck.crash found while fuzzing snap.snapshot with target-specific argument \"\\Device\\Afd\".\n");
        return 1;
    }
    
    int use_jit = 0;
    
    // Disk options:
    char *vhdx_file_name = null;
    char *qcow2_file_name = null;
    
    // Snapshot options:
    char *vmrs_file_name = null;
    char *dmp_file_name  = null;
    char *snapshot_file_name = null;
    
    // Repro options:
    char *repro_file_name    = null;
    char *minimize_file_name = null;
    
    // Converting a .DMP into a .snapshot
    char *convert_file_name    = null;
    
    // This should probably be supported for both (stop on first instruction for snapshot mode).
    int start_in_debugger_mode = 0;
    int start_in_tracing_mode = 0;
    
    // Target code arguments.
    int target_argc = 0;
    char **target_argv = null;
    
    s64 thread_count = -1;
    
    for(int argument_index = 1; argument_index < argc; argument_index++){
        char *arg = argv[argument_index];
        
        if(strcmp(arg, "--") == 0){
            
            if(target_argv){
                print("Error: Too many '--'.\n");
                return 1;
            }
            
            target_argc = argc - (argument_index + 1);
            target_argv = argv + (argument_index + 1);
            
            for(argument_index++; argument_index < argc; argument_index++){
                if(strcmp(argv[argument_index], "--") == 0){
                    target_argc -= (argc - argument_index);
                    break;
                }
            }
            
            continue;
        }
        
        if(strcmp(arg, "-d") == 0 || strcmp(arg, "-debugger") == 0){
            start_in_debugger_mode = 1;
            continue;
        }
        
        if(strcmp(arg, "-t") == 0){
            start_in_debugger_mode = 1;
            start_in_tracing_mode = 1;
            globals.print_mode = PRINT_rip;
            
            if(argv[argument_index+1] && argv[argument_index+1][0] != '-'){
                char buf[0x100];
                
                char *trace_file = argv[argument_index+1];
                if(!cstring_ends_with_case_insensitive(trace_file, ".log")){
                    snprintf(buf, sizeof(buf), "%s.log", trace_file);
                    trace_file = buf;
                }
                
                globals.trace_file = fopen(trace_file, "w");
                if(!globals.trace_file){
                    print("Error: Could not open trace file %s\n", trace_file);
                    return 1;
                }
                
                print("Logging to file %s\n", trace_file);
                argument_index++;
            }
            continue;
        }
        
        if(strcmp(arg, "-jit") == 0){
            use_jit = 1;
            continue;
        }
        
        if(strcmp(arg, "-thread_count") == 0){
            char *argument = argv[++argument_index];
            if(!argument){
                print("Expected an argument after '%s'.\n", arg);
                return 1;
            }
            
            char *end = 0;
            u32 value = strtoul(argument, &end, 0);
            if(!value || value == 0xffffffff || *end != 0){
                print("Could not parse '%s' argument '%s'\n", arg, argument);
                return 1;
            }
            
            thread_count = value;
            continue;
        }
        
        if(strcmp(arg, "-y") == 0 || strcmp(arg, "-yes") == 0){
            g_always_answer_yes = 1;
            continue;
        }
        
#define option(format)                                                 \
if(cstring_ends_with_case_insensitive(arg, "." #format)){              \
    if(format##_file_name){                                            \
        print("Error: More than one ." #format "-file specified.\n");  \
        return 1;                                                      \
    }                                                                  \
    format##_file_name = arg;                                          \
    continue;                                                          \
}
        
#if ENABLE_VMRS
        option(vmrs);
#endif
        
        option(dmp);
        option(snapshot);
        option(vhdx);
        option(qcow2);
        
#undef option
        
        // 
        // C specifies that the 'argv' array is NULL-string terminated.
        // We use this here to first check whether the 'arg' is correct, 
        // then whether there was an argument.
        // 
        char *argument = argv[++argument_index];
        if(strcmp(arg, "-r") == 0){
            repro_file_name = argument;
        }else if(strcmp(arg, "-m") == 0){
            minimize_file_name = argument;
        }else if(strcmp(arg, "-convert") == 0){
            convert_file_name = argument;
        }else{
            print("Error: Unknown option '%s'.\n", arg);
            return 1;
        }
        
        if(!argument){
            print("Error: Expected an argument after '%s'.\n", arg);
            return 1;
        }
    }
    
    if(thread_count == -1){
        // Default to using almost all logical cores on the system.
#if _WIN32
        struct system_info system_info;
        GetSystemInfo(&system_info);
        thread_count = system_info.number_of_processors - 2;
        if(thread_count < 1) thread_count = 1;   
#else
        smm number_of_logical_cores = sysconf(_SC_NPROCESSORS_ONLN);
        thread_count = number_of_logical_cores - 2;
        if(thread_count < 1) thread_count = 1;
#endif
    }
    
    // 
    // Validate the arguments as much as we can, before trying to load anything.
    // 
    
    if(!repro_file_name && minimize_file_name){
        print("Error: Cannot minimize (-m), if there is no repro file (-r) specified.\n");
        return 1;
    }
    
    {
        // 
        // Validate that there is at most one snapshot file format 
        // (specifying the physical memory state).
        // 
        int amount_of_snapshot_files = 0;
        if(vmrs_file_name)     amount_of_snapshot_files++;
        if(snapshot_file_name) amount_of_snapshot_files++;
        if(dmp_file_name)      amount_of_snapshot_files++;
        
        if(amount_of_snapshot_files > 1){
            print("Error: More than one snapshot file format specified.\n");
            print("       Snapshot file formats are: .snapshot, .dmp and .vmrs\n");
            return 1;
        }
    }
    
    // If '--' was specified we are in fuzzing mode.
    int fuzzing_mode = (target_argv != 0);
    
    // Repro mode is fuzzing mode until the setup is done.
    if(repro_file_name) fuzzing_mode = 1;
    
    if(fuzzing_mode){
        
        if((start_in_debugger_mode || start_in_tracing_mode) && minimize_file_name){
            print("WARINING: Cannot debug (-d) or trace (-t) and minimize (-m) at the same time.\n");
            print("          Removing -d and -t.\n");
            start_in_debugger_mode = 0;
            start_in_tracing_mode  = 0;
        }
        
    }else{
        // 
        // We are in snapshot mode!
        // 
        
        char *option_to_error = null; // Currently all options are valid in snapshot mode...
        
        if(option_to_error){
            print("Error: Option '%s' is not valid in Snapshot Mode. It's for fuzzing!\n", option_to_error);
            return 1;
        }
    }
    
    if(!globals.print_mode) globals.print_mode = PRINT_default;
    globals.breakpoint_hit_index = -1;
    if(!globals.trace_file) globals.trace_file = stdout;
    globals.input_buffer_physical_address = (u64)-1;
    
    initialize_instruction_tables();
    
    memset(frame_buffer, 0xff, sizeof(frame_buffer)); // All white!
    
    // Some of this JIT stuff does not have to be initialized in snapshot mode.
    // But we will just initialize it anyway.
    struct context *context = os_allocate_memory(sizeof(*context));
    globals.main_thread_context = context;
    context_initialize_main_and_thread_context_common(context);
    context->thread_index = -1;
    context->fuzz_case_timeout = 0x7fffffffffffffff; // @note: make sure the main thread never _times out_.
    
    if(vhdx_file_name && qcow2_file_name){
        print("Error: More than one virtual disk specified, currently not supported.\n");
        print("       Disks:\n");
        print("            %s\n", vhdx_file_name);
        print("            %s\n", qcow2_file_name);
        return 1;
    }
    
    char *disk_file_name = null;
    if(vhdx_file_name)  disk_file_name =  vhdx_file_name;
    if(qcow2_file_name) disk_file_name = qcow2_file_name;
    
    if(disk_file_name){
        // Parse the disk device.
        int parse_disk_success = parse_disk(disk_file_name);
        if(!parse_disk_success) return 1;
    }
    
    // 
    // Load the snapshot file.
    // 
    
    if(vmrs_file_name){
#if ENABLE_VMRS
        int success = parse_vmrs(context, vmrs_file_name);
#else
        int success = 0;
#endif
        if(!success) return 1;
    }else if(snapshot_file_name){
        int success = load_snapshot(context, snapshot_file_name);
        if(!success) return 1;
    }else if(dmp_file_name){
        int success = parse_dmp(context, dmp_file_name);
        if(!success) return 1;
    }else{
        if(!disk_file_name){
            print("Error: Neither a disk nor a snapshot format specified.\n");
            return 1;
        }
        
        // 
        // If there is no snapshot file format specified, boot from disk.
        // 
        int success = efi_setup_initial_state(context);
        if(!success) return 1;
    }
    
    // Ensure the register state is correct. This is probably already correct.
    context->registers = globals.snapshot.registers;
    
    if(convert_file_name){
        // We were asked to convert this state into a snapshot, so do that then exit.
        write_snapshot(context, convert_file_name);
        return 0;
    }
    
    if(!fuzzing_mode){
        
        // We have survived startup, disable this option.
        g_always_answer_yes = 0;
        
        // 
        // We are in snapshot mode!
        //     
        context->snapshot_mode = 1;
        globals.debugger_mode = 1;
        
        // Create the display.
#if _WIN32
        CreateThread(null, 0, initialize_hacky_display, 0, 0, null);
#else
        // int pthread_create(pthread_t *thread, pthread_attr_t *attr, void *start_routine(void *), void *arg);
        //      attr - "If attr is NULL, then the thread is created with default attributes."
        pthread_t ignored;
        pthread_create(&ignored, NULL, initialize_hacky_display, NULL);
#endif
        
        if(start_in_debugger_mode) globals.single_stepping = 1;
        if(start_in_tracing_mode){
            globals.print_trace = 1;
            maybe_find_nt_and_load_module_list(context);
        }
        
        if(use_jit){
            start_execution_jit(context);
        }else{
            
            start_execution_hypervisor(context);
        }
        
        // @note: We only get here if the jit encounters an error and then the user exits the debugger.
        return 1;
    }
    
    //
    // Fuzzing Mode:
    // 
    //     1) Ensure the module list is loaded. So the target specific code has access to it.
    //     2) Execute the 'target_initialize' function.
    //     3) Start reproing/fuzzing/minimizing.
    
    maybe_find_nt_and_load_module_list(context);
    
    if(start_in_debugger_mode){
        globals.debugger_mode = 1;
        globals.single_stepping = 1;
    }
    
    if(start_in_tracing_mode) globals.print_trace = 1;
    
    globals.thread_count = thread_count;
    
    globals.maximal_amount_of_inputs = 0x4000;
    globals.inputs = malloc(sizeof(*globals.inputs) * globals.maximal_amount_of_inputs);
    
    //
    // Initialize the target specific code.
    //
    if(PRINT_STARTUP_EVENTS) print("Calling 'target_initialize'.\n");
    target_initialize(context, target_argc, target_argv);
    if(PRINT_STARTUP_EVENTS) print("Done calling 'target_initialize'.\n");
    
    if(globals.amount_of_inputs == 0){
        print("Error: The target specific code must add at least one input to the corpus using the `add_input` function.\n");
        return 1;
    }
    
#if _WIN32
    {
        //
        // Change the memory permissions of the snapshot to make it impossible to corrupt it!
        //
        
        struct memory_basic_information{
            void *BaseAddress;
            void *AllocationBase;
            u32 AllocationProtect;
            u16 PartitionId;
            u16 _padding1;
            u64 RegionSize;
            u32 State;
            u32 Protect;
            u32 Type;
            u32 _padding2;
        } memory_basic_information = {0};
        
        u8 *start = globals.snapshot.physical_memory;
        u8 *end   = globals.snapshot.physical_memory + globals.snapshot.physical_memory_size;
        for(u8 *address = start; address < end; address += memory_basic_information.RegionSize){
            // SIZE_T VirtualQuery(
            //     [in, optional] LPCVOID                   lpAddress,
            //     [out]          PMEMORY_BASIC_INFORMATION lpBuffer,
            //     [in]           SIZE_T                    dwLength
            // );
            
            u64 SizeReturned = VirtualQuery(address, &memory_basic_information, sizeof(memory_basic_information));
            if(SizeReturned < sizeof(memory_basic_information)) break;
            
            if(memory_basic_information.Protect != /*PAGE_READ_WRITE*/4) continue;
            
            u32 old_protect = 0;
            
            // BOOL VirtualProtect(
            //     [in]  LPVOID lpAddress,
            //     [in]  SIZE_T dwSize,
            //     [in]  DWORD  flNewProtect,
            //     [out] PDWORD lpflOldProtect
            // );
            
            int success = VirtualProtect(address, memory_basic_information.RegionSize, /*PAGE_READONLY*/2, &old_protect);
            
            if(!success){
                print("[VirtualProtect] failure %d\n", GetLastError());
                
                print("%p:\n", address);
                print("    BaseAddress:       %p\n", memory_basic_information.BaseAddress);
                print("    AllocationBase:    %p\n", memory_basic_information.AllocationBase);
                print("    AllocationProtect: %u\n", memory_basic_information.AllocationProtect);
                print("    PartitionId:       %u\n", memory_basic_information.PartitionId);
                print("    RegionSize:        %llu\n", memory_basic_information.RegionSize);
                print("    State:             %u\n", memory_basic_information.State);
                print("    Protect:           %u\n", memory_basic_information.Protect);
                print("    Type:              %u\n", memory_basic_information.Type);
            }
            
            assert(success);
            assert(old_protect == /*PAGE_READ_WRITE*/4);
        }
    }
#else
    if(ptrace(PTRACE_TRACEME, 0, NULL, 0) == -1) __is_debugger_present = 1;
#endif
    
    if(repro_file_name){
        //
        // The user has specified a repro file he would like to replay or minimize it.
        // Load the file, then replay the file.
        //
        
        struct file repro_file = load_file(repro_file_name);
        if(!repro_file.memory){
            print("Error: Could not open repro file '%s'.\n", repro_file_name);
            return 1;
        }
        
        if(repro_file.size < 8){
            print("Error: Repro file '%s' is to small.\n", repro_file_name);
            return 1;
        }
        
        u64 amount_of_inputs = *(u64 *)repro_file.data;
        
        struct input *inputs = malloc(sizeof(*inputs) * amount_of_inputs);
        if(!inputs){
            // @cleanup: This code path is unreachable because my 'malloc' exits on failiure...
            print("Error: Could not allocate memory for %lld inputs for repro file '%s'.\n", amount_of_inputs, repro_file_name);
            return 1;
        }
        
        for(u64 input_index = 0, file_offset = 8; input_index < amount_of_inputs; input_index++){
            if(file_offset + 8 > repro_file.size){
                print("Error: Repro file '%s' contains less inputs than it specifies.\n", repro_file_name);
                return 1;
            }
            
            u64 input_size = *(u64 *)(repro_file.data + file_offset);
            
            file_offset += 8;
            
            if((file_offset + input_size) > repro_file.size || (file_offset + input_size) < file_offset){
                print("Error: Input %llu of repro file %s has corrupted size 0x%llx.\n", input_index, repro_file_name, input_size);
                return 1;
            }
            
            u8 *input_data = repro_file.data + file_offset;
            
            inputs[input_index].data = input_data;
            inputs[input_index].size = input_size;
            
            file_offset += input_size;
        }
        
        //
        // This was set when the crash file was created and hooks may work differently
        // depending on if this is set or not.
        //
        globals.fuzzing = 1;
        
        if(start_in_debugger_mode){
            globals.debugger_mode = 1;
            globals.single_stepping = 1;
        }
        
        struct context *thread_context = allocate_and_initialize_thread_context(/*thread_index*/0);
        
        
        if(minimize_file_name){
            print("\n\nMinimizing '%s' (%d inputs)\n", repro_file_name, amount_of_inputs);
            
            minimize_crashing_inputs(thread_context, inputs, amount_of_inputs, minimize_file_name);
        }else{
            print("\n\nReproing '%s' (%d inputs)\n", repro_file_name, amount_of_inputs);
            
            struct crash_information result = replay_inputs(thread_context, inputs, amount_of_inputs, /*print_result*/1);
            
            if(result.crash_type == CRASH_replaying_inputs_crashed_earlier_then_expected){
                print("WARNING: Repro file crashed earlier than expected.\n");
            }else if(result.crash_type == CRASH_none){
                print("WARNING: Repro file did not crash.\n");
            }else{
                print_stack_trace(thread_context);
            }
            
            if(start_in_debugger_mode){
                handle_debugger(context);
            }
        }
        
        return 0;
    }
    
    print("\n\n********************* Starting To Fuzz *********************\n\n");
    
#if _WIN32
    // @note: Go brrr!
    if(!SetPriorityClass(/*current_process*/(u64)-1, /*REALTIME_PRIORITY_CLASS*/0x00000100)){
        printf("[SetPriorityClass] Error %d\n", GetLastError());
    }
#endif
    
    globals.fuzzing = 1;
    
    if(CLEAR_INITIALIZATION_COVERAGE) clear_coverage_table();
    
    if(start_in_debugger_mode){ 
        print("\n\n");
        print("Warning: Starting to \"fuzz\" in debugger mode. This means only one thread will be fuzzing.\n");
        print("         This option is purely for debugging purposes. If you actually want to fuzz, remove the '-d' option.\n");
        print("\n\n");
        
        // Only one thread can be active in the debugger at the same time.
        thread_count = 1;
        
        // Reset it to single stepping, such that the debugger breaks
        // on the first instruction of the fuzzing.
        globals.single_stepping = true; 
    }
    
    //
    // Send the threads on their way!
    //
    for(u32 thread_index = 0; thread_index < thread_count; thread_index++){
#if _WIN32
        
        // HANDLE CreateThread(
        //     [in, optional]  LPSECURITY_ATTRIBUTES   lpThreadAttributes,
        //     [in]            SIZE_T                  dwStackSize,
        //     [in]            LPTHREAD_START_ROUTINE  lpStartAddress,
        //     [in, optional]  __drv_aliasesMem LPVOID lpParameter,
        //     [in]            DWORD                   dwCreationFlags,
        //     [out, optional] LPDWORD                 lpThreadId
        // );
        HANDLE handle = CreateThread(NULL, 0, start_fuzzing, (void *)(u64)thread_index, 0, null);
        assert(handle.Unused); // returns NULL on failure
#else
        // int pthread_create(pthread_t *thread, pthread_attr_t *attr, void *start_routine(void *), void *arg);
        //      attr - "If attr is NULL, then the thread is created with default attributes."
        pthread_t ignored;
        int error = pthread_create(&ignored, NULL, start_fuzzing, (void *)(u64)thread_index);
        assert(error == 0);
#endif
    }
    
    //
    // Report while the threads are fuzzing!
    //
    time_t start_time = time(NULL);
    u64 saved_coverage = 0;
    while(true){
        
        // Sleep for one second so we don't over-report.
#if _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
        
        time_t current_time = time(null);
        time_t uptime = current_time - start_time;
        
        u64 coverage = atomic_load(u64, globals.coverage);
        if(saved_coverage < coverage){
            write_coverage_files();
            saved_coverage = coverage;
        }
        
        if(!globals.debugger_mode){
            print("uptime %4d | cases %d | inputs %5d | coverage %d | mips %5.1f | fcps %5.1f | crashes %d | fcpr %5.1f | toi %5.1f%%\n", uptime, globals.fuzz_cases, globals.amount_of_inputs, globals.coverage, (double)globals.instructions_executed/(double)(uptime * 1000000.0), (double)globals.fuzz_cases/(double)uptime, globals.unique_crashes, (double)globals.fuzz_cases/(double)globals.resets, (double)globals.instructions_in_timeout_inputs/(double)globals.instructions_executed * 100.0);
        }
    }
    
    return 0;
}

