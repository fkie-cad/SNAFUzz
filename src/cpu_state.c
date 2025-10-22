
struct segment{
    u64 base;
    u32 limit;
    u16 selector;
    struct{
        //
        // Access Byte.
        // 
        
        // This is either the system segment type:
        //     2: LDT, 9: 64-bit TSS (available), b: 64-bit TSS (Busy) (@note: Not sure what any of this means).
        // or the non-system_segment_type:
        //     0 - accessed
        //     1 - read / write bit
        //     2 - Direction / Conforming bit
        //     3 - Execute bit
        u16 segment_type    : 4;
        u16 is_non_system   : 1; // (0 = system segment (e.g Task State Segment/Local Descriptor Table), 1 = code or data segment)
        u16 privilege_level : 2; // (0 = kernel, 3 = user)
        u16 present         : 1; // Should be set for any valid segment.
        
        u16 reserved    : 4; // This is where some part of the limit was.
        
        //
        //  Flags
        //
        u16 available   : 1; // Not sure why Microsoft calls this available...? Osdev.org calls it Reserved.
        u16 long_mode   : 1;
        u16 default_big : 1;
        u16 granularity : 1;
    };
};

struct registers{
    //
    // Gprs are first such that accessing becomes easier in the jit.
    //
    union{
        s64 gpr[16];
        struct{
            s64 rax;
            s64 rcx;
            s64 rdx;
            s64 rbx;
            s64 rsp;
            s64 rbp;
            s64 rsi;
            s64 rdi;
            s64 r8;
            s64 r9;
            s64 r10;
            s64 r11;
            s64 r12;
            s64 r13;
            s64 r14;
            s64 r15;
        };
    };
    
    u64 rip;
    
    // Bit    Name                          Description
    //  0     (PE) Protected Mode Enable    If 1 the system is in protected mode, else real mode.
    //  1     (MP) Monitor Co-Processor     Controls interaction of Wait Instructions with TS flag in CR0.
    //  2     (EM) Emulation                If set no x87 floating-point unit present.
    //  3     (TS) Task Switched            Allows saving x87 task contrext upon task switch.
    //  4     (ET) Extension Type           On the 386, it allowed to specify whether the external math coprocessor was an 80287 or 80387.
    //  5     (NE) Numeric Error            Enable internal x87 floating point error reporting when set, else enables PC style x87 error detection.
    //  16    (WP) Write Protect            When set, the CPU can't write to read-only pages when privilege level is 0.
    //  18    (AM) Alignment Mask           Alignment check enabled if AM set, AC flag (in EFLAGS register) set, and privilege level is 3.
    //  29    (NW) Not-Write Through        Globally enables/disable write-through caching.
    //  30    (CD) Cache Disable            Globally enables/disable the memory cache.
    //  31    (PG) Paging                   If 1, enable paging and use the CR3 register, else disable paging.
    u64 cr0; // dumped from kd: 80050031 = ((1 << 31) | (1 << 18) | (1 << 16) | (1 << 5) | (1 << 4) | (1 << 0))
    
    // Page Fault Linear Address
    u64 cr2;
    
    // Page Directory Base Register
    u64 cr3;
    
    // Bit        Name Description
    //  0        (VME) Virtual-8086 Mode Extensions
    //  1        (PVI) Protected Mode Virtual Interrupts
    //  2        (TSD) Time Stamp enabled only in ring 0
    //  3         (DE) Debugging Extensions
    //  4        (PSE) Page Size Extension
    //  5        (PAE) Physical Address Extension
    //  6        (MCE) Machine Check Extension
    //  7        (PGE) Page Global Enable
    //  8        (PCE) Performance Monitoring Counter Enable
    //  9     (OSFXSR) OS support for fxsave and fxrstor instructions
    // 10 (OSXMMEXCPT) OS support for unmasked simd floating point exceptions
    // 11       (UMIP) User-Mode Instruction Prevention
    // 12              Reserved
    // 13       (VMXE) Virtual Machine Extension Enable
    // 14       (SMXE) Safer Mode Extensions Enable
    // 15              Reserved
    // 16   (FSGSBASE) Enables the instructions RDFSBASE, RDGSBASE, WRFSBASE and WRGSBASE
    // 17      (PCIDE) PCID Enable
    // 18    (OSXSAVE) XSAVE and Processor extended States Enable
    // 19              Reserved
    // 20       (SMEP) Supervisor Mode Executions Protection Enable
    // 21       (SMAP) Supervisor Mode Access Protection Enable
    // 22        (PKE) Enable protection keys for user-mode pages
    // 23        (CET) Enable Control-flow Enforcement Technology
    // 24        (PKS) Enable protection keys for supervisor-mode pages
    u64 cr4;
    
    // Task Priority Register
    u64 cr8;
    
    
    // Bit         Name       Enabled Feature
    //  0          X87        x87 floating point unit (must be supported)
    //  1          SSE        MXCSR and 16 XMM registers
    //  2          AVX        YMM registers
    //  3         BNDREG      Bound registers
    //  4         BNDCSR      Bound config and status registers
    //  5         OPMASK      k-registers
    //  6       ZMM_Hi256     ZMM registers
    //  7       Hi16_ZMM      ZMM16 - ZMM31
    //  8          PT         Processor Trace
    //  9         PKRU        Protection Keys
    // 10         PASID
    // 11         CET_U       User shadow stacks
    // 12         CET_S       Supervisor shadow stacks
    // 13          HDC        Hardware Duty Cycling
    // 14         UINTR       User interrupts
    // 15          LBR        Last Branch Records
    // 16          HWP        Hardware P-states
    // 17       XTILECFG      64-byte TILECFG registers
    // 18       XTILEDATA     Eight 1024-byte TILE registers
    // 19          APX        r16 - r31
    u64 xcr0;
    
    // These contain virtual addresses
    union{
        u64 dr[4];
        struct{
            u64 dr0;
            u64 dr1;
            u64 dr2;
            u64 dr3;
        };
    };
    
    
    // Debug Status Register
    //  Bit   Description
    //   0    Breakpoint #0 Detected
    //   1    Breakpoint #1 Detected
    //   2    Breakpoint #2 Detected
    //   3    Breakpoint #3 Detected
    //  4-10  Reserved
    //  11    Bus Lock Trap
    //  12    SMM or ICE mode entered
    //  13    Debug Register Access Detected
    //  14    Single-Step Execution
    //  15    Task Switch breakpoint
    //  16    Debug Exception inside RTM transaction
    u64 dr6;
    
    //  Bit   Description
    //   0    Local  DR0 Breakpoint  1
    //   1    Global DR0 Breakpoint  2
    //   2    Local  DR1 Breakpoint  4
    //   3    Global DR1 Breakpoint  8
    //   4    Local  DR2 Breakpoint  10
    //   5    Global DR2 Breakpoint  20
    //   6    Local  DR3 Breakpoint  40
    //   7    Global DR3 Breakpoint  80
    //   8    Local exact breakpoint enable
    //   9    Global exact breakpoint enable
    //  10    Reserved must be 1.
    //  11    Restricted transactional memory (?)
    //  12    Reserved must be 0.
    //  13    general detect enable (?)
    // 14-15  Reserved must be 0.   
    // 16-17  DR0 Type
    // 18-19  DR0 Length
    // 20-21  DR1 Type
    // 22-23  DR1 Length
    // 24-25  DR2 Type
    // 26-27  DR2 Length
    // 28-29  DR3 Type
    // 30-31  DR3 Length
    // 
    // Types:
    //     00-Break on execution
    //     01-Break on writes
    //     10-Break on I/O read or writes
    //     11-Break on read or writes but not instruction fetches
    // Length:
    //     00 - 1-byte length
    //     01 - 2-byte length
    //     10 - 8-byte length
    //     11 - 4-byte length
    
    u64 dr7;
    
    union{
        u32 eflags;
        u64 rflags;
        struct{
            u8 CF        : 1; // carry flag     - overflow unsigned
            u8 Always1   : 1; // Reserved
            u8 PF        : 1; // parity flag    - even
            u8 Reserved1 : 1;
            u8 AF        : 1; // auxiliary carry flag?
            u8 Reserved2 : 1;
            u8 ZF        : 1; // zero     flag  - zero
            u8 SF        : 1; // sign     flag  - negative
            u8 TF        : 1; // trap flag
            u8 IF        : 1; // interrupt flag
            u8 DF        : 1; // direction flag - not really implemented
            u8 OF        : 1; // overflow flag  - overflow signed
            u8 IOPL      : 2; // I/O privilege level
            u8 NT        : 1; // Nested Task flag
            u8 Always0   : 1; 
            
            //
            // Eflags
            //
            u8 RF  : 1; // Resume flag
            u8 VM  : 1; // Virtual 8086 mode flag
            u8 AC  : 1; // Alignment check
            u8 VIF : 1; // Virtual Interrupt flag
            u8 VIP : 1; // Virtual Interrupt Pending
            u8 ID  : 1; // Able to use CPUID
        };
    };
    
    union simd{
        __m128  xmm;
        __m128i xmmi;
        __m128d xmmd;
        
        struct {
            __m128i xmmi_low;
            __m128i xmmi_high;
        };
        
        __m256  ymm;
        __m256i ymmi;
        __m256d ymmd;
    } simd[16];
    
    u64 idt_base;
    u64 gdt_base;
    
    u16 idt_limit;
    u16 gdt_limit;
    
    struct segment cs;
    struct segment ds;
    struct segment es;
    struct segment ss;
    
    struct segment tr;  // @note: this is the selector for the 'tss' called 'tr' or 'task register' for other ones I leave out the 'r', but just calling this 't' seemed wrong.
    struct segment ldt;
    
    struct segment fs;
    struct segment gs;
    
    u64 fs_base; // MSP C0000100
    u64 gs_base; // MSR C0000101
    u64 gs_swap; // MSR C0000102
    
    u64 xinuse;
    
    // FPCW:
    //   Bit - Description:
    //   
    //  Exception Control:
    //    0   - Invalid Operation Mask       (IM)
    //    1   - Denormalized Operation Mask  (DM)
    //    2   - Zero-Divide Mask             (ZM)
    //    3   - Overflow Mask                (OM)
    //    4   - Underflow Mask               (UM)
    //    5   - Precision Mask               (PM)
    //   6-7  - Reserved
    //   8-9  - Precision Control (3 = 80-bits, 2 = 64-bits, 0 = 32-bits)
    //  10-11 - Rounding Control (0 = Round to Nearest, 1 = Round Down, 2 = Round Up, 3 = Round towards 0)
    //   12   - Infinity Control (8087 and 80287 only) (IC)
    //  15-13 - Reserved
    //  
    //  Windows standard value 27f (exceptions masked, 64-bits, Round to Nearest)
    //  Linux   standard value 37f (exceptions masked, 80-bits, Round to Nearest)
    u16 fpu_control_word;
    
    // FPSW:
    // 
    //  Exception Flags:
    //    0 - Invalid Operation
    //    1 - Denormalized Operation
    //    2 - Zero Divide
    //    3 - Overflow
    //    4 - Underflow
    //    5 - Precision
    //   
    //    6 - Stack Fault
    //    7 - Exception Summary Status
    //   
    //  Condition Codes:
    //    8 - C0
    //    9 - C1
    //   10 - C2
    //   14 - C3
    //  
    //  11-13 - Top of Stack Pointer (TOP)
    //    15  - FPU Busy
    // 
    u16 fpu_status_word;
    u8  fpu_tag_word;
    u16 fpu_opcode;
    u64 fpu_instruction_pointer;
    u64 fpu_data_pointer;
    
    u128 fpu_st[8];
    
    // MXCSR:
    //   Bit - Description:
    //   
    //   Bit 0-5 of the MXCSR register indicate whether a SIMD floating-point exception has been detected.
    //     0 - Invalid Operation Flag
    //     1 - Denormal Flag
    //     2 - Divide-by-Zero Flag
    //     3 - Overflow Flag
    //     4 - Underflow Flag
    //     5 - Precision Flag
    //     
    //     6 - Denormals are zero 
    //     
    //   Bits 7-12 provide individual mask bits for the SIMD floating-point exceptions.
    //     7 - Invalid Operation Mask
    //     8 - Divide-by-Zero Mask
    //     9 - Denormal Mask
    //    10 - Overflow Mask
    //    11 - Underflow Mask
    //    12 - Precision Mask
    //    
    //    13:14 - Rounding Control
    //    15    - Flush to Zero
    //    
    u32 mxcsr;
    u32 mxcsr_mask; // "This mask can be used to adjust values written to the MXCSR register, ensuring that reserved bits are set to 0."
    
    u64 ia32_lstar; // 0xc0000082 - Long mode syscall address.
    u64 ia32_cstar; // 0xc0000083 - Compatibility mode syscall address. (@note: We currently don't support compatibility mode).
    u64 ia32_star;  // 0xc0000081 - 32-bit syscall segment + address
    u64 ia32_fmask; // 0xc0000084 - Flag mask for syscalls.
    
    u64 ia32_tsc;
    u64 ia32_tsc_aux; // 0xc0000103
    
    u64 ia32_spec_ctrl; // 0x00000048
    
    u64 ia32_efer; // 0xc0000080
    u64 ia32_pat;  // 0x00000277
    u64 ia32_apic_base;  // 0x0000001b
    u64 ia32_misc_enable;
    
    u64 ia32_sep_sel;
    u64 ia32_sep_rsp;
    u64 ia32_sep_rip;
    
    u64 ia32_mtrr_cap; // 0x000000fe
    u64 ia32_mtrr_def_type;
    
    u64 ia32_mtrr_phys_base;
    u64 ia32_mtrr_phys_mask;
    
    u64 ia32_bios_sign_id; // Something todo with microcode. (https://www.intel.com/content/www/us/en/developer/articles/technical/software-security-guidance/best-practices/microcode-update-guidance.html)
    
    u64 hv_x64_msr_simp;  // Synthetic interrupt message page
    u64 hv_x64_msr_siefp; // synthetic interrupt event flags page
    
    union{
        struct{
            u64 hv_x64_msr_sint0;
            u64 hv_x64_msr_sint1;
            u64 hv_x64_msr_sint2;
            u64 hv_x64_msr_sint3;
        };
        u64 hv_x64_msr_sint[16];
    };
    
    u64 hv_x64_msr_stimer0_count;
    u64 hv_x64_msr_stimer0_config;
    
    u64 hv_x64_msr_vp_assist_page; // Used to be msr_apic_assist_page, but then they put more stuff into it!
    u64 hv_x64_msr_hypercall_page;
    u64 hv_x64_msr_reference_tsc_page;
    
    struct local_apic{
        // 
        // @WARNING: If you think "sweet, this is all documented, clearly its also implemented", that is wrong.
        //           We currently only care about the 'in_service_register' and the 'interrupt_request_register'.
        // 
        
        
        // 
        // [read/write] Specifies a _unique_ id for the local apic.
        // 
        u32 id_register;
        
        // 
        // [read] Bits 0-7 specify the version of the local apic.
        //        [ 0x0 -  0xf]  Discrete APIC (not integrated into the processor)
        //        [0x10 - 0x15]  Integrated APIC.
        //        
        //        Bits 16-23 specify the maximal amount of Local Vector table entries.
        //        Bit  25 indicates support for EOI-broadcast suppression.
        //        
        u32 version_register;
        
        // 
        // [read/write] Bits 4-7 indicate the interrupt priority class. This value is mirrored by cr8.
        //              Bits 0-3 indicated the interrupt priority sub-class (?)
        //              
        // This can be used to temporarily block lower-priority interrupts.
        // 
        u32 task_priority_register;
        
        // 
        // [read] This register serves the same purpose as the task priority register for interrupts
        //        in lowest priority delivery mode.
        // 
        u32 arbitration_priority_register;
        
        // 
        // [read] The current interrupt priority at which the processor is running.
        //        This value is based on the task priority register and the in service register.
        // 
        u32 processor_priority_register;
        
        // 
        // [write] A write to this register indicates the end of an interrupt.
        //         When this register is written the highest bit in the in-service register 
        //         get set to 0 (meaning more interrupts may be allowed).
        // 
        u32 end_of_interrupt_register;
        
        // 
        // [read] 
        // 
        u32 remote_read_register;
        
        // 
        // [read/write] These values are used for 'logical destination' interrupts.
        // 
        u32 local_destination_register;
        u32 destination_format_register;
        
        // 
        // [read/write] 
        // 
        u32 spurious_interrupt_vector_register;
        
        // 
        // [read] Indicates which interrupts are currently being serviced.
        //        When an interrupt is delivered corresponding bit is set.
        //        When the processor writes to the end of interrupt register,
        //        the highest bit is cleared.
        //        While an interrupt is in service, lower priority interrupts 
        //        are not delivered anymore.
        // 
        u32 in_service_register[8];
        
        // 
        // [read] Indicates whether an interrupt pending in the interrupt request 
        //        register is edge or level triggered.
        // 
        u32 trigger_mode_register[8];
        
        // 
        // [read] Indicates pending interrupts.
        //        Whenever an interrupt is requested, but the 'processor_priority_register'
        //        is higher then the priority of the interrupt (bits 7:4 of its vector number),
        //        the corresponding bit in the interrupt request register is set.
        //        When the APIC lowers the process priority and there is a pending interrupt
        //        of a higher priority, the interrupt is delivered.
        //        This causes the corresponding bit in the interrupt request register to be reset, 
        //        and the corresponding bit in the in-service register to be set.
        // 
        u32 interrupt_request_register[8];
        
        // 
        // [read/write] Only writes of 0 are allowed.
        //              Bit | Description
        //              0   | Send Checksum Error
        //              1   | Receive Checksum Error
        //              2   | Send Accept Error
        //              3   | Receive Accept Error
        //              4   | Redirectable IPI
        //              5   | Send Illegal Vector
        //              6   | Received Illegal Vector
        //              7   | Illegal Register Address
        // 
        u32 error_status_register;
        
        // 
        // [read/write] Used to request interrupts. The high value indicates the destination of the interrupt.
        //              When the low value is written, the interrupt is requested.
        //              
        //              Bits 0-7   indicate the vector number.
        //              Bits 8-10  indicate the delivery mode (Fixed, SMI, NMI, INIT, SIPI).
        //              Bit  11    indicates the Destination mode (Physical/Logical).
        //              Bit  14    indicates the level (de-assert/assert).
        //              Bit  15    indicates the trigger mode (Edge/level).
        //              Bits 18-19 indicate the destination shorthand (None, Self, all including self, all excluding self)
        // 
        //              The 'high' value is interpreted based on the 'destination mode', and if logical
        //              based on the 'local_destination_register' and the 'destination_format_register'.
        struct{
            u32 low;
            u32 high;
        } interrupt_command_register;
        
        
        // 
        // [read/write] The local vector table indicates how local interrupts are delivered.
        //              For each register:
        //              Bits 0-7   indicate the vector number.
        //              Bits 8-10  indicate the delivery mode.
        //              Bit  12    indicates the delivery status. (set if pending)
        //              Bit  13    indicates the Interrupt Input Pin Polarity (?).
        //              Bit  14    indicates the Remote IRR Flag (?).
        //              Bit  15    indicates the trigger mode. (Edge/Level)
        //              Bit  16    can be set to mask the interrupt.
        //              Bit  17-18 Is the timer mode (One-Shot, Periodic, TSC-Deadline).
        //              
        //              Some of these bits only apply to some of the vectors.
        // 
        struct{
            u32 corrected_machine_check_interrupt_register;
            u32 timer_register;
            u32 thermal_sensor_register;
            u32 performance_monitoring_counters_register;
            u32 lint0_register;
            u32 lint1_register;
            u32 error_register;
        } local_vector_table;
        
        // 
        // [read/write] Used to configure the APIC timer.
        // 
        u32 timer_initial_count_register;
        
        // 
        // [read] Can be used to read the current timer.
        // 
        u32 timer_current_count_register;
        
        // 
        // [read/write] Bit 0,1,3 indicate the divide value.
        //              This can be used to adjust the 'timer speed'.
        // 
        u32 timer_divide_configuration_register;
        
        
        // 
        // @note: from here on these members are not part of the local_apic, but rather part of our implementation.
        // 
        
        s32 highest_pending_interrupt;
        s32 highest_interrupt_in_service;
        
    } local_apic;
    
    
    struct{
        u32 register_select;
        
        struct{
            u32 low;
            u32 high;
        } redirection_table[0x18];
    } io_apic;
    
    struct{
        u32 address;
        
        /* 0x0a */u8  status; // frequency, divider, update in progress
        
        struct{
            /* 0x00 */u8 seconds;
            /* 0x02 */u8 minutes;
            /* 0x04 */u8 hours;
            /* 0x06 */u8 day_of_the_week;
            /* 0x07 */u8 day;
            /* 0x08 */u8 month;
            /* 0x09 */u8 year;
            /* 0x32 */u8 centuary;
        } RTC;
    } CMOS;
    
    struct vtl_state{
        int current_vtl;
        
        u64 rip;
        u64 rsp;
        u64 rflags;
        u64 cr0;
        u64 cr3;
        u64 cr4;
        // u64 dr7;
        // u64 dr6;
        u64 cr8;
        
        u16 idt_limit;
        u16 gdt_limit;
        u64 idt_base;
        u64 gdt_base;
        
        struct segment cs;
        struct segment ds;
        struct segment es;
        struct segment fs;
        struct segment gs;
        struct segment ss;
        struct segment tr;
        struct segment ldt;
        
        u64 fs_base; // MSP C0000100
        u64 gs_base; // MSR C0000101
        u64 gs_swap; // MSR C0000102
        
        u64 ia32_efer; // 0xc0000080
        u64 ia32_pat;  // 0x00000277
        
        u64 ia32_tsc;
        u64 ia32_tsc_aux; // 0xc0000103
        
        u64 ia32_lstar; // 0xc0000082 - Long mode syscall address.
        u64 ia32_cstar; // 0xc0000083 - Compatibility mode syscall address. (@note: We currently don't support compatibility mode).
        u64 ia32_star;  // 0xc0000081 - 32-bit syscall segment + address
        u64 ia32_fmask; // 0xc0000084 - Flag mask for syscalls.
        
        u64 hv_x64_msr_hypercall_page;
        u64 hv_x64_msr_reference_tsc_page;
        u64 hv_x64_msr_vp_assist_page;
        
        union{
            struct{
                u64 hv_x64_msr_sint0;
                u64 hv_x64_msr_sint1;
                u64 hv_x64_msr_sint2;
                u64 hv_x64_msr_sint3;
            };
            u64 hv_x64_msr_sint[16];
        };
    } vtl_state;
};

enum rflags{
    // CF (bit 0)
    // Carry Flag - Set if an arithmetic operation generates a carry or a borrow out of the most-
    //              significant bit of the result; cleared otherwise. This flag indicates an overflow condition for
    //              unsigned-integer arithmetic. It is also used in multiple-precision arithmetic.
    FLAG_CF = (1 << 0), // 1
    
    // PF (bit 2)
    // Parity Flag - Set if the least-significant byte of the result contains an even number of 1 bits;
    //               cleared otherwise.
    FLAG_PF = (1 << 2), // 4
    
    // AF (bit 4)
    // Auxiliary Carry Flag - Set if an arithmetic operation generates a carry or a borrow out of bit
    //                        3 of the result; cleared otherwise. 
    //                        This flag is used in binary-coded decimal (BCD) arithmetic.
    FLAG_AF = (1 << 4), // 0x10
    
    // ZF (bit 6)
    // Zero Flag - Set if the result is zero; cleared otherwise.
    FLAG_ZF = (1 << 6), // 0x40
    
    // SF (bit 7)
    // Sign Flag - Set equal to the most-significant bit of the result, which is the sign bit of a signed
    //             integer. (0 indicates a positive value and 1 indicates a negative value.)
    FLAG_SF = (1 << 7), // 0x80
    
    // TF (bit 8)
    // Trap Flag - When a system is instructed to single-step, it will execute one instruction and then stop. 
    FLAG_TF = (1 << 8), // 0x100
    
    // IF (bit 9)
    // Interrupt Enable Flag - If the flag is set to 1 maskable interrupts are enabled. If reset (set to 0) such interrupts will be disabled until interrupts are enabled. 
    //                         The Interrupt flag does not affect the handling of non-maskable interrupts (NMIs) or software interrupts generated by the INT instruction.
    FLAG_IF = (1 << 9), // 0x200
    
    // DF (bit 10)
    // Direction Flag - If it is set to 0 (using the clear-direction-flag instruction CLD) it means that string is processed beginning from lowest to highest address.
    //                  In case it is set to 1 (using the set-direction-flag instruction STD) the string is processed from highest to lowest address. This is called auto-decrementing mode.
    FLAG_DF = (1 << 10), // 0x400
    
    // OF (bit 11)
    // Overflow Flag - Set if the integer result is too large a positive number or too small a negative
    //                 number (excluding the sign-bit) to fit in the destination operand; cleared otherwise. 
    //                 This flag indicates an overflow condition for signed-integer (two's complement) arithmetic.
    FLAG_OF = (1 << 11), // 0x800
    
    // NT (bit 14)
    // Nested Task Flag - The processor uses the nested task flag to control chaining of interrupted and called tasks.
    //                    NT influences the operation of the IRET instruction.
    FLAG_NT = (1 << 14), // 0x4000
    
    // RF (bit 16)
    // Resume Flag - "Controls the Processor's response to instruction-breakpoint conditions.
    //                When set, this flag temporarly disables debug exceptions (#DB) from being generated."
    //                The primary function of the RF flag is to allow the restarting of an instruction 
    //                following a debug exception that was caused by an instruction breakpoint condition.
    //                Here, debug software must set this flag in the EFLAGS image on the stack just prior
    //                to returning to the interrupted program with IRETD (to prevent the instruction breakpoint from
    //                causing another debug exception). The processor then automatically clears this flag after the 
    //                instruction return to has been successfully executed. enabling instruction breakpoint faults again."
    FLAG_RF = (1 << 16), // 0x10000
    
    
    FLAG_VM = (1 << 17), // 0x20000
    
    // AC (bit 18)
    // Alignement Check (?) This is for SMAP
    FLAG_AC = (1 << 18), // 0x40000
    
    FLAG_VIF = (1 << 19), // 0x80000
    
    FLAG_VIP = (1 << 20), // 0x100000
    
    FLAG_ID = (1 << 21), // 0x200000
    
};

#define ARITHMETIC_FLAGS (FLAG_CF | FLAG_PF | FLAG_AF | FLAG_ZF | FLAG_SF | FLAG_OF)

struct xsave_area{

    union{
        u8 X86LegacyXSaveArea[512];
        
        struct{
            u16 fpu_control_word; // fcw
            u16 fpu_status_word;  // fsw
            u8  fpu_tag_word;     // ftw
            u8  reserved; 
            u16 fpu_opcode;       // fpop
            
            union{
                struct{ // 32-bit
                    u32 fpu_instruction_pointer_offset;   // fpip
                    u16 fpu_instruction_pointer_selector; // fcs
                    u16 reserved2;
                };
                u64 fpu_instruction_pointer; // 64-bit
            };
            
            union{
                struct{ // 32-bit
                    u32 fpu_data_pointer_offset;   // fdp
                    u16 fpu_data_pointer_selector; // fds
                    u16 reserved3;
                };
                u64 fpu_data_pointer; // 64-bit
            };
            u32 mxcsr;
            u32 mxcsr_mask;
            
            u128 fpST[8];
            u128 xmm[16];
        };
    };
    
    union{
        u8 X86XSaveHeader[64];
    
        struct{
            u64 xstate_bv;
            u64 xcomp_bv;
        };
    };
    
    // XSaveAVX
    u128 ymm[16];
    
    u8 padding [0x80];
};

struct xsave_area xsave_area_from_registers(struct registers *registers){
    struct xsave_area ret = {
        .fpu_control_word = registers->fpu_control_word,
        .fpu_status_word  = registers->fpu_status_word,
        .fpu_tag_word     = registers->fpu_tag_word,
        
        .fpu_instruction_pointer = registers->fpu_instruction_pointer,
        .fpu_data_pointer        = registers->fpu_data_pointer,
        
        .mxcsr      = registers->mxcsr,
        .mxcsr_mask = registers->mxcsr_mask,
        
        // @cleanup: fpregs?
        
        // :XSAVE/XRSTOR
        //
        // The state is realoaded via XRSTOR.
        // This instruction does a full or partial restore of the processor state components from the XSAVE area.
        // Which components are restored depends on 
        //     1) XCR0 
        //     2) The operand to the instruction
        //     3) The xstate_bv member
        //     4) The xcomp_bv member (comp = compacted)
        // The requested feature bitmap RFBP is (XCR0 & EDX:EAX).
        // The top bit of the xcomp_bv member determines whether or not the instruction is in compacted form.
        // The compacted form is preferable for some reason.
        // In the compacted form all bits int (RFBP & xcomp_bv & xstate_bv) are restored (Except the top bit).
        // Each bit corresponds to a component of the XSAVE area.
        //     Bit 0 corresponds to the state component used for the x87 FPU execution environment (x87 state).
        //     Bit 1 corresponds to the state component used for registers used by the SIMD extension (SSE state).
        //     Bit 2 corresponds to the state component used for the additional register state used by the Intel (R) Advanced Vector Extensions (AVX state).
        // And so on, but these are the bits which are interesting to us currently.
        // 
        
        .xstate_bv = 0x7,
        .xcomp_bv  = 0x8000000000000007,
    };
    
    for(u32 xmm_reg_index = 0; xmm_reg_index < array_count(registers->simd); xmm_reg_index++){
#if _WIN32
        ret.xmm[xmm_reg_index].low  = registers->simd[xmm_reg_index].xmmi.m128i_u64[0];
        ret.xmm[xmm_reg_index].high = registers->simd[xmm_reg_index].xmmi.m128i_u64[1];
#else
        ret.xmm[xmm_reg_index].low  = registers->simd[xmm_reg_index].xmmi[0];
        ret.xmm[xmm_reg_index].high = registers->simd[xmm_reg_index].xmmi[1];
#endif
    }
    
    for(u32 xmm_reg_index = 0; xmm_reg_index < array_count(registers->simd); xmm_reg_index++){
#if _WIN32
        ret.ymm[xmm_reg_index].low  = registers->simd[xmm_reg_index].xmmi_high.m128i_u64[0];
        ret.ymm[xmm_reg_index].high = registers->simd[xmm_reg_index].xmmi_high.m128i_u64[1];
#else
        ret.ymm[xmm_reg_index].low  = registers->simd[xmm_reg_index].xmmi_high[0];
        ret.ymm[xmm_reg_index].high = registers->simd[xmm_reg_index].xmmi_high[1];
#endif
    }
    
    return ret;
}

void load_xsave_registers(struct registers *registers, struct xsave_area xsave_area){
    registers->fpu_control_word = xsave_area.fpu_control_word;
    registers->fpu_status_word  = xsave_area.fpu_status_word;
    registers->fpu_tag_word     = xsave_area.fpu_tag_word;
    
    registers->fpu_instruction_pointer = xsave_area.fpu_instruction_pointer;
    registers->fpu_data_pointer        = xsave_area.fpu_data_pointer;
    
    registers->mxcsr      = xsave_area.mxcsr;
    // registers->mxcsr_mask = xsave_area.mxcsr_mask;
    
    // @cleanup: fpregs?
    //           xsatate_bv?
    //           xcomp_bv?
    
    for(u32 xmm_reg_index = 0; xmm_reg_index < array_count(registers->simd); xmm_reg_index++){
#if _WIN32
        registers->simd[xmm_reg_index].xmmi.m128i_u64[0] = xsave_area.xmm[xmm_reg_index].low;
        registers->simd[xmm_reg_index].xmmi.m128i_u64[1] = xsave_area.xmm[xmm_reg_index].high;
#else
        registers->simd[xmm_reg_index].xmmi[0] = xsave_area.xmm[xmm_reg_index].low;
        registers->simd[xmm_reg_index].xmmi[1] = xsave_area.xmm[xmm_reg_index].high;
#endif
    }
    
    
    for(u32 ymm_reg_index = 0; ymm_reg_index < array_count(registers->simd); ymm_reg_index++){
#if _WIN32
        registers->simd[ymm_reg_index].xmmi_high.m128i_u64[0] = xsave_area.ymm[ymm_reg_index].low;
        registers->simd[ymm_reg_index].xmmi_high.m128i_u64[1] = xsave_area.ymm[ymm_reg_index].high;
#else
        registers->simd[ymm_reg_index].xmmi_high[0] = xsave_area.ymm[ymm_reg_index].low;
        registers->simd[ymm_reg_index].xmmi_high[1] = xsave_area.ymm[ymm_reg_index].high;
#endif
    }
}

//_____________________________________________________________________________________________________________________
// Instruction decoding 

// register encoding without REX
//      s   i   z   e
//      1   2   4   8
// e 0 AL  AX  EAX RAX
// n 1 CL  CX  ECX RCX
// c 2 DL  DX  EDX RDX
// o 3 BL  BX  EBX RBX
// d 4 AH  SP  ESP RSP
// i 5 CH  BP  EBP RBP
// n 6 DH  SI  ESI RSI
// g 7 BH  DI  EDI RDI

// register encoding with REX
//      s   i   z   e
//      1   2   4   8
// e 0 AL  AX  EAX RAX
// n 1 CL  CX  ECX RCX
// c 2 DL  DX  EDX RDX
// o 3 BL  BX  EBX RBX
// d 4 SPL SP  ESP RSP
// i 5 BPL BP  EBP RBP
// n 6 SIL SI  ESI RSI
// g 7 DIL DI  EDI RDI

enum register_encoding{
    REGISTER_A  = 0, // accumulator
    REGISTER_C  = 1, // count
    REGISTER_D  = 2, // data
    REGISTER_B  = 3, // base pointer to data
    
    REGISTER_SP = 4, // stack pointer
    REGISTER_BP = 5, // stack base pointer
    REGISTER_SI = 6, // source index or pointer to data
    REGISTER_DI = 7, // destination index or pointer to data
    
    REGISTER_R8  = 8 + 0,
    REGISTER_R9  = 8 + 1,
    REGISTER_R10 = 8 + 2,
    REGISTER_R11 = 8 + 3,
    REGISTER_R12 = 8 + 4,
    REGISTER_R13 = 8 + 5,
    REGISTER_R14 = 8 + 6,
    REGISTER_R15 = 8 + 7,
    
    REGISTER_XMM0 = 0,
    REGISTER_XMM1 = 1,
    REGISTER_XMM2 = 2,
    REGISTER_XMM3 = 3,
    REGISTER_XMM4 = 4,
    REGISTER_XMM5 = 5,
    REGISTER_XMM6 = 6,
    REGISTER_XMM7 = 7,
    
    // Used by the jit.
    REG_OPCODE_add = 0,
    REG_OPCODE_or  = 1,
    REG_OPCODE_adc = 2,
    REG_OPCODE_sbb = 3,
    REG_OPCODE_and = 4,
    REG_OPCODE_sub = 5,
    REG_OPCODE_xor = 6,
    REG_OPCODE_cmp = 7,
    
    INVALID_REGISTER = -1, // Used by the jit.
};

char *reg_to_string(enum register_encoding reg, int size){
    if(size == 1){
        switch(reg){
            case REGISTER_A: return "al";
            case REGISTER_C: return "cl";
            case REGISTER_D: return "dl";
            case REGISTER_B: return "bl";
            case REGISTER_SP: return "spl";
            case REGISTER_BP: return "bpl";
            case REGISTER_SI: return "sil";
            case REGISTER_DI: return "dil";
            case REGISTER_R8: return "r8b";
            case REGISTER_R9: return "r9b";
            case REGISTER_R10: return "r10b";
            case REGISTER_R11: return "r11b";
            case REGISTER_R12: return "r12b";
            case REGISTER_R13: return "r13b";
            case REGISTER_R14: return "r14b";
            case REGISTER_R15: return "r15b";
            case INVALID_REGISTER: return "???";
        }
    }else if(size == 2){
        switch(reg){
            case REGISTER_A: return "ax";
            case REGISTER_C: return "cx";
            case REGISTER_D: return "dx";
            case REGISTER_B: return "bx";
            case REGISTER_SP: return "sp";
            case REGISTER_BP: return "bp";
            case REGISTER_SI: return "si";
            case REGISTER_DI: return "di";
            case REGISTER_R8: return "r8w";
            case REGISTER_R9: return "r9w";
            case REGISTER_R10: return "r10w";
            case REGISTER_R11: return "r11w";
            case REGISTER_R12: return "r12w";
            case REGISTER_R13: return "r13w";
            case REGISTER_R14: return "r14w";
            case REGISTER_R15: return "r15w";
            case INVALID_REGISTER: return "???";
        }
    }else if(size == 4){
        switch(reg){
            case REGISTER_A: return "eax";
            case REGISTER_C: return "ecx";
            case REGISTER_D: return "edx";
            case REGISTER_B: return "ebx";
            case REGISTER_SP: return "esp";
            case REGISTER_BP: return "ebp";
            case REGISTER_SI: return "esi";
            case REGISTER_DI: return "edi";
            case REGISTER_R8: return "r8d";
            case REGISTER_R9: return "r9d";
            case REGISTER_R10: return "r10d";
            case REGISTER_R11: return "r11d";
            case REGISTER_R12: return "r12d";
            case REGISTER_R13: return "r13d";
            case REGISTER_R14: return "r14d";
            case REGISTER_R15: return "r15d";
            
            case INVALID_REGISTER: return "???";
        }
    }else if(size == 8){
        switch(reg){
            case REGISTER_A: return "rax";
            case REGISTER_C: return "rcx";
            case REGISTER_D: return "rdx";
            case REGISTER_B: return "rbx";
            case REGISTER_SP: return "rsp";
            case REGISTER_BP: return "rbp";
            case REGISTER_SI: return "rsi";
            case REGISTER_DI: return "rdi";
            case REGISTER_R8: return "r8";
            case REGISTER_R9: return "r9";
            case REGISTER_R10: return "r10";
            case REGISTER_R11: return "r11";
            case REGISTER_R12: return "r12";
            case REGISTER_R13: return "r13";
            case REGISTER_R14: return "r14";
            case REGISTER_R15: return "r15";
            
            case INVALID_REGISTER: return "???";
        }
    }else if(size == 16){
        
        switch(reg){
            case 0: return "xmm0";
            case 1: return "xmm1";
            case 2: return "xmm2";
            case 3: return "xmm3";
            case 4: return "xmm4";
            case 5: return "xmm5";
            case 6: return "xmm6";
            case 7: return "xmm7";
            case 8: return "xmm8";
            case 9: return "xmm9";
            case 10: return "xmm10";
            case 11: return "xmm11";
            case 12: return "xmm12";
            case 13: return "xmm13";
            case 14: return "xmm14";
            case 15: return "xmm15";
            case -1: return "???";
        }
    }else if(size == 32){
        switch(reg){
            case 0: return "ymm0";
            case 1: return "ymm1";
            case 2: return "ymm2";
            case 3: return "ymm3";
            case 4: return "ymm4";
            case 5: return "ymm5";
            case 6: return "ymm6";
            case 7: return "ymm7";
            case 8: return "ymm8";
            case 9: return "ymm9";
            case 10: return "ymm10";
            case 11: return "ymm11";
            case 12: return "ymm12";
            case 13: return "ymm13";
            case 14: return "ymm14";
            case 15: return "ymm15";
            case -1: return "???";
        }
    }else if(size == 64){
        switch(reg){
            case 0: return "zmm0";
            case 1: return "zmm1";
            case 2: return "zmm2";
            case 3: return "zmm3";
            case 4: return "zmm4";
            case 5: return "zmm5";
            case 6: return "zmm6";
            case 7: return "zmm7";
            case 8: return "zmm8";
            case 9: return "zmm9";
            case 10: return "zmm10";
            case 11: return "zmm11";
            case 12: return "zmm12";
            case 13: return "zmm13";
            case 14: return "zmm14";
            case 15: return "zmm15";
            case -1: return "???";
        }
    }
    return "???";
}

enum modrm_mod{
    MOD_REGM       = 0, // [rax]
    MOD_REGM_OFF8  = 1, // [rax + 0x42]
    MOD_REGM_OFF32 = 2, // [rax + 0x13371337]
    MOD_REG        = 3, // rax
};

enum rex{
    REXW = (1 << 3), // The operand size of this instruction is 64-bit.
    REXR = (1 << 2), // The register operand is 'r8 - r15'.
    REXX = (1 << 1), // The sib-index register operand is 'r8 - r15'.
    REXB = (1 << 0), // Either the 'regm' register or the 'sib-base' register is 'r8 - r15'.
};

enum vexL{ 
    VEXL = 0b100,
};

enum legacy_prefix{
    LEGACY_lock = 0x1,
    LEGACY_repn = 0x2,
    LEGACY_rep  = 0x4,
    LEGACY_repz = LEGACY_rep,
    LEGACY_repe = LEGACY_rep,
    
    LEGACY_fs_segment_override = 0x8,
    LEGACY_gs_segment_override = 0x10,
    
    LEGACY_operand_size_override = 0x20,
    LEGACY_address_size_override = 0x40,
    
    // "In 64-bit the CS, SS, DS and ES segment overrides are ignored."
    // Therefore, they are here in the second byte.
    LEGACY_cs_segment_override = 0x100,
    LEGACY_ss_segment_override = 0x200,
    LEGACY_ds_segment_override = 0x400,
    LEGACY_es_segment_override = 0x800,
    
    // There are some mandatory prefixes for SSE2, In instruction tables:
    //   NP  means one of F3, F2 and 66
    //   NPx means one of F3 or F2
    MANDATORY_PREFIX_F3 = LEGACY_rep,
    MANDATORY_PREFIX_F2 = LEGACY_repn,
    MANDATORY_PREFIX_66 = LEGACY_operand_size_override,
};

#include "instruction_table.h"

#define INSTRUCTION_TABLE_SIZE 0x400

u16 normal_instruction_table[INSTRUCTION_TABLE_SIZE];
u16    vex_instruction_table[INSTRUCTION_TABLE_SIZE];
u16   evex_instruction_table[INSTRUCTION_TABLE_SIZE];

void initialize_instruction_tables(void){
    memset(normal_instruction_table, 0xff, sizeof(normal_instruction_table));
    memset(vex_instruction_table,    0xff, sizeof(vex_instruction_table));
    memset(evex_instruction_table,   0xff, sizeof(evex_instruction_table));
    
    struct {
        u16 *instruction_table;
        smm amount_of_instructions;
        struct instruction_table_entry *instructions;
    } tables[] = {
        {normal_instruction_table, array_count(normal_instructions), normal_instructions},
        {   vex_instruction_table, array_count(vex_instructions),       vex_instructions},
        {  evex_instruction_table, array_count(evex_instructions),     evex_instructions},
    };
    
    for(u32 table_index = 0; table_index < array_count(tables); table_index++){
        
        for(u32 instruction_index = 0; instruction_index < tables[table_index].amount_of_instructions; instruction_index++){
            struct instruction_table_entry entry = tables[table_index].instructions[instruction_index];
            
            u16 *index_value = &tables[table_index].instruction_table[entry.extended_opcode];
            if(*index_value == 0xffff){
                assert(instruction_index < 0xffff);
                *index_value = (u16)instruction_index;
            }
        }
    }
}

#define MULTIBYTE_0F (1 << 8)
#define MULTIBYTE_38 (2 << 8)
#define MULTIBYTE_3A (3 << 8)

struct instruction_information{
    u32 instruction_size;
    
    u32 legacy_prefix_flags;
    
    u8 rex;
    u8 vex;
    u8 modrm;
    u8 mod;
    u8 scale;
    u8 is_rip_relative;
    u8 have_sib;
    u8 immediate_size;
    u8 instruction_has_modrm;
    
    int reg;
    int regm;
    int index_reg;
    int vex_reg;
    
    s32 address_offset;
    
    u32 augmented_opcode;
    
    u64 immediate;
    
} decode_instruction(u8 *instruction_buffer){
    
    u32 offset_in_instruction = 0;
    u8 instruction_byte = instruction_buffer[offset_in_instruction++];
    
    u32 legacy_prefix_flags = 0;
    while(1){
        u32 should_break = 0;
        switch(instruction_byte){
            case 0xF0: legacy_prefix_flags |= LEGACY_lock; break;
            case 0xF2: legacy_prefix_flags |= LEGACY_repn; break;
            case 0xF3: legacy_prefix_flags |= LEGACY_rep;  break;
            
            // @note: 2e, 3e are also branch hints.
            case 0x26: legacy_prefix_flags |= LEGACY_es_segment_override; break;
            case 0x2E: legacy_prefix_flags |= LEGACY_cs_segment_override; break;
            case 0x36: legacy_prefix_flags |= LEGACY_ss_segment_override; break;
            case 0x3E: legacy_prefix_flags |= LEGACY_ds_segment_override; break;
            case 0x64: legacy_prefix_flags |= LEGACY_fs_segment_override; break;
            case 0x65: legacy_prefix_flags |= LEGACY_gs_segment_override; break;
            
            case 0x66: legacy_prefix_flags |= LEGACY_operand_size_override; break;
            case 0x67: legacy_prefix_flags |= LEGACY_address_size_override; break;
            
            default: should_break = 1; break;
        }
        if(should_break) break;
        
        instruction_byte = instruction_buffer[offset_in_instruction++];
    }
    
    u8 rex = (instruction_byte & 0xf0) == 0x40 ? instruction_byte : 0;
    if(rex) instruction_byte = instruction_buffer[offset_in_instruction++];
    
    // 0 = opcode
    // 1 = 0F opcode
    // 2 = 0F 38 opcode
    // 3 = 0F 3A opcode
    int multibyte_mode = 0;
    
    u8 vex = 0;
    u8 opcode = 0;
    
    u8 vex_reg = 0;
    
    if(instruction_byte == 0x0f){
        //
        // Two byte instruction.
        //
        multibyte_mode = 1;
        
        instruction_byte = instruction_buffer[offset_in_instruction++];
        
        if(instruction_byte == 0x38){
            multibyte_mode = 2;
            instruction_byte = instruction_buffer[offset_in_instruction++];
        }else if(instruction_byte == 0x3a){
            multibyte_mode = 3;
            instruction_byte = instruction_buffer[offset_in_instruction++];
        }
        
        opcode = instruction_byte;
    }else if(instruction_byte == 0xc5){
        //
        // One byte VEX-prefix.
        //
        multibyte_mode = 1;
        
        u8 RvvvvLpp = instruction_buffer[offset_in_instruction++];
        rex |= (RvvvvLpp >> 7) ? 0 : REXR;
        
        vex_reg = (~(RvvvvLpp >> 3)) & 0b1111;
        
        switch(RvvvvLpp & 3){
            case 0: break;
            case 1: legacy_prefix_flags |= MANDATORY_PREFIX_66; break;
            case 2: legacy_prefix_flags |= MANDATORY_PREFIX_F3; break;
            case 3: legacy_prefix_flags |= MANDATORY_PREFIX_F2; break;
        }
        
        vex = (RvvvvLpp | 0x80); // Ensure this is not zero.
        
        opcode = instruction_buffer[offset_in_instruction++];
    }else if(instruction_byte == 0xc4){
        //
        // Two byte VEX-prefix.
        //
        u8 RXBmmmmm = instruction_buffer[offset_in_instruction++];
        rex |= ((RXBmmmmm >> 7) & 1) ? 0 : REXR;
        rex |= ((RXBmmmmm >> 6) & 1) ? 0 : REXX;
        rex |= ((RXBmmmmm >> 5) & 1) ? 0 : REXB;
        u8 mmmmm = (RXBmmmmm & 0x1f);
        multibyte_mode = mmmmm & 3; // Rest of the 'mmmmm' are currently not used.
        
        u8 WvvvvLpp = instruction_buffer[offset_in_instruction++];
        rex |= (WvvvvLpp >> 7) ? REXW : 0; // Apparently this is not flipped...
        
        vex_reg = (~(WvvvvLpp >> 3)) & 0xf;
        
        switch(WvvvvLpp & 3){
            case 0: break;
            case 1: legacy_prefix_flags |= MANDATORY_PREFIX_66; break;
            case 2: legacy_prefix_flags |= MANDATORY_PREFIX_F3; break;
            case 3: legacy_prefix_flags |= MANDATORY_PREFIX_F2; break;
        }
        
        vex = (WvvvvLpp | 0x80); // Ensure this is not zero.
        
        opcode = instruction_buffer[offset_in_instruction++];
    }else{
        //
        // One byte instruction.
        //
        opcode = instruction_byte;
    }
    
    u32 augmented_opcode = (multibyte_mode << 8) | opcode;
    
    s32 address_offset = 0;
    int reg = 0, regm = -1, index_reg = -1;
    u8  mod = MOD_REG;
    int scale = 0;
    int is_rip_relative = 0;
    u8  modrm = 0;
    int have_sib = 0;
    
    int instruction_has_modrm = !instruction_has_no_modrm[augmented_opcode];
    if(instruction_has_modrm){
        modrm = instruction_buffer[offset_in_instruction++];
        
        mod    = ((modrm >> 6) & 3);
        reg    = ((modrm >> 3) & 7) | ((rex & REXR) ? 8 : 0);
        u8 mem = ((modrm >> 0) & 7);
        
        if(mod == MOD_REG){
            regm = mem | ((rex & REXB) ? 8 : 0);
        }else{
            if(mem == REGISTER_SP){
                //
                // There is a sib byte.
                //
                u8 sib = instruction_buffer[offset_in_instruction++];
                
                have_sib = 1;
                scale = (sib >> 6) & 3;
                
                u8 index = ((sib >> 3) & 7) | ((rex & REXX) ? 8 : 0);
                u8 base  = ((sib >> 0) & 7)| ((rex & REXB) ? 8 : 0);
                
                if(index != REGISTER_SP) index_reg = index;
                if(mod != MOD_REGM || base  != REGISTER_BP) regm = base;
            }else{
                if(mem == REGISTER_BP && mod == MOD_REGM){
                    is_rip_relative = 1;
                }else{
                    regm = mem | ((rex & REXB) ? 8 : 0);
                }
            }
            
            static u8 address_size_for_mod[4] = { [MOD_REGM_OFF8] = 1, [MOD_REGM_OFF32] = 4 };
            u32 address_size = address_size_for_mod[mod];
            
            // Apparently you cannot do 'add rax, [r13]' but have to do 'add rax, [r13 + 0]'.
            if(mod == MOD_REGM && regm == INVALID_REGISTER){
                // Rip relative, or absolute. depending on whether we have sib.
                address_size = 4;
            }
            
            if(address_size){
                memcpy(&address_offset, instruction_buffer + offset_in_instruction, address_size);
                offset_in_instruction += address_size;
            }
        }
    }
    
    u32 immediate_size = instruction_immediate_size[augmented_opcode];
    if(immediate_size == IMM_OP_SIZE_MAX32){
        immediate_size = (legacy_prefix_flags & LEGACY_operand_size_override) ? 2 : 4;
    }
    
    u8 operand_size = 4;
    if(legacy_prefix_flags & LEGACY_operand_size_override) operand_size = 2;
    if(rex & REXW) operand_size = 8;
    
    if(immediate_size == INSTRUCTION_IS_WEIRD){
        
        switch(opcode){
            case 0xf6: case 0xf7:{
                //
                // Immediate size is only 1 if (reg <= 1).
                //
                
                if(opcode == 0xf6){
                    immediate_size = (reg <= 1) ? 1 : 0;
                }else{
                    u32 has_operand_size_override = (legacy_prefix_flags & LEGACY_operand_size_override);
                    immediate_size = (reg <= 1) ? (has_operand_size_override ? 2 : 4) : 0;
                }
            }break;
            
            case 0xB8:case 0xb9:case 0xba:case 0xbb:case 0xbc:case 0xbd:case 0xbe:case 0xbf:{
                // mov reg, imm16/32/64
                immediate_size = operand_size;
            }break;
        }
    }
    
    u64 immediate = 0;
    if(immediate_size){
        memcpy(&immediate, instruction_buffer + offset_in_instruction, immediate_size);
        offset_in_instruction += immediate_size;
    }
    
    struct instruction_information ret ={
        .instruction_size = offset_in_instruction,
        
        .legacy_prefix_flags = legacy_prefix_flags,
        
        .rex = rex,
        .vex = vex,
        .modrm = modrm,
        .mod = mod,
        .scale = (u8)scale,
        .is_rip_relative = (u8)is_rip_relative,
        .have_sib = (u8)have_sib,
        .instruction_has_modrm = (u8)instruction_has_modrm,
        
        .reg = reg,
        .regm = regm,
        .index_reg = index_reg,
        .vex_reg = vex_reg,
        
        .immediate_size = (u8)immediate_size,
        .immediate = immediate,
        .address_offset = address_offset,
        .augmented_opcode = augmented_opcode,
    };
    
    return ret;
}

//_____________________________________________________________________________________________________________________
// Crash information

enum crash_type{
    
    //
    // Crashes which might be caught by an exception handler.
    //
    
    CRASH_none,          // Success case, has to be 0.
    CRASH_read,          // We read a page we are not allowed to read.
    CRASH_write,         // We wrote a page we are not allowed to write.
    CRASH_non_canonical, // We accessed a non-canonical address.
    CRASH_divide,        // A divide by zero or overflow divide.
    CRASH_execute,       // We executed and address which was not present or had NX set. @note: This could be a page fault, so not necessarily fatal.
    
    CRASH_exception_count,
    
    // 
    // These are just for convenience, they get set after we have identified a crash, based on the crash address.
    // 
    
    CRASH_read_null,     // We read  a low address (<0x1000).
    CRASH_write_null,    // We wrote a low address (<0x1000).
    
    //
    // Everything below this line always ends the fuzz case.
    //
    
    CRASH_bugcheck,                  // We called one of the BugCheck procedures.
    CRASH_unhandled_exception,       // An unhandled user mode exception occured (also see Unhandled_user_exception_hook which is a hook on ntdll!RtlUserThreadStart$filt$0).
    CRASH_debug_break,               // We executed an 'int 3' .
    CRASH_out_of_bounds_read,        // We read  some memory which was marked as inaccessible by the extra permissions.
    CRASH_out_of_bounds_write,       // We wrote some memory which was marked as inaccessible by the extra permissions.
    CRASH_double_free,               // We freed the same address twice.
    CRASH_timeout,                   // The fuzz case timed out.
    CRASH_uninitialized_memory_leak, // Memory which was marked _uninitialized_ by the extra permissions was written to user space.
    
    //
    // Emulator errors.
    //
    
    CRASH_internal_error,            // An internal (emulator) error occurred. Usually, something which is not or incorrectly implemented.
    CRASH_unimplemented_instruction, // We hit an instruction which the emulator does not implement.
    
    // Internal use CRASH. If we are minimizing and we crash prior to to executing the last input, we treat the input as important.
    CRASH_replaying_inputs_crashed_earlier_then_expected,
    
    CRASH_enter_debugger, // Used to implement breakpoints in the jit.
    CRASH_reset_jit,      // Used to reset the jit in case a page is written which was previously executed.
    CRASH_self_modifying_code,
    
    CRASH_type_count,
};

static char *crash_type_string[] = {
    [CRASH_none]          = "success",
    [CRASH_read]          = "read",
    [CRASH_write]         = "write",
    [CRASH_execute]       = "execute",
    [CRASH_divide]        = "divide",
    [CRASH_non_canonical] = "non-canonical_access",
    [CRASH_read_null]     = "read_null",
    [CRASH_write_null]    = "write_null",
    
    [CRASH_bugcheck]                 = "bugcheck",
    [CRASH_unhandled_exception]      = "unhandled_exception",
    [CRASH_debug_break]              = "debug_break",
    [CRASH_out_of_bounds_read]       = "out_of_bounds_read",
    [CRASH_out_of_bounds_write]      = "out_of_bounds_write",
    [CRASH_double_free]              = "double_free",
    [CRASH_timeout]                  = "timeout",
    [CRASH_uninitialized_memory_leak] = "uninitialized_memory_leak",
    
    [CRASH_unimplemented_instruction] = "unimplemented_instruction",
    [CRASH_internal_error]            = "internal_error", 
    
    [CRASH_replaying_inputs_crashed_earlier_then_expected] = "replaying_input_error",
    
    [CRASH_reset_jit] = "reset_jit",
};

// We usually overwrite the return address with this value.
// When we then observe an execution crash, where it tries 
// to return to this specific value, we treat it as successful.
#define DEFAULT_RETURN_RIP 0x1337133713371337

#define crash_assert(condition, ...) if(!(condition)) { set_crash_information(context, CRASH_internal_error, (u64)("[" __FUNCTION__ "] " #condition)); return __VA_ARGS__; }
#define crash_invalid_default_case(message, ...) default: { set_crash_information(context, CRASH_internal_error, (u64)("[" __FUNCTION__ "] invalid default case: " message)); return __VA_ARGS__; }

struct crash_information{
    u64 crash_address;
    enum crash_type crash_type;
    int debug_depth; // Used to ensure calls of 'enter_debugging_routine' match calls of 'exit_debugging_routine'.
};


static void switch_vtl(struct registers *registers){
    
    struct vtl_state current_vtl_state = registers->vtl_state;
    
    // 
    // Save VTL state:
    // 
    registers->vtl_state.rip = registers->rip;
    registers->vtl_state.rsp = registers->rsp;
    registers->vtl_state.rflags = registers->rflags;
    registers->vtl_state.cr0 = registers->cr0;
    registers->vtl_state.cr3 = registers->cr3;
    registers->vtl_state.cr4 = registers->cr4;
    // registers->vtl_state.dr7 = registers->dr7;
    // registers->vtl_state.dr6 = registers->dr6;
    registers->vtl_state.cr8 = registers->cr8;
    
    registers->vtl_state.idt_limit = registers->idt_limit;
    registers->vtl_state.gdt_limit = registers->gdt_limit;
    registers->vtl_state.idt_base = registers->idt_base;
    registers->vtl_state.gdt_base = registers->gdt_base;
    
    registers->vtl_state.cs = registers->cs;
    registers->vtl_state.ds = registers->ds;
    registers->vtl_state.es = registers->es;
    registers->vtl_state.fs = registers->fs;
    registers->vtl_state.gs = registers->gs;
    registers->vtl_state.ss = registers->ss;
    registers->vtl_state.tr = registers->tr;
    registers->vtl_state.ldt = registers->ldt;
    
    registers->vtl_state.fs_base = registers->fs_base; // MSP C0000100
    registers->vtl_state.gs_base = registers->gs_base; // MSR C0000101
    registers->vtl_state.gs_swap = registers->gs_swap; // MSR C0000102
    
    registers->vtl_state.ia32_efer = registers->ia32_efer; // 0xc0000080
    registers->vtl_state.ia32_pat = registers->ia32_pat;  // 0x00000277
    
    registers->vtl_state.ia32_tsc = registers->ia32_tsc;
    registers->vtl_state.ia32_tsc_aux = registers->ia32_tsc_aux; // 0xc0000103
    
    registers->vtl_state.ia32_lstar = registers->ia32_lstar; // 0xc0000082 - Long mode syscall address.
    registers->vtl_state.ia32_cstar = registers->ia32_cstar; // 0xc0000083 - Compatibility mode syscall address. (@note: We currently don't support compatibility mode).
    registers->vtl_state.ia32_star = registers->ia32_star;  // 0xc0000081 - 32-bit syscall segment + address
    registers->vtl_state.ia32_fmask = registers->ia32_fmask; // 0xc0000084 - Flag mask for syscalls.
    
    registers->vtl_state.hv_x64_msr_hypercall_page = registers->hv_x64_msr_hypercall_page;
    registers->vtl_state.hv_x64_msr_reference_tsc_page = registers->hv_x64_msr_reference_tsc_page;
    registers->vtl_state.hv_x64_msr_vp_assist_page = registers->hv_x64_msr_vp_assist_page;
    
    for(u32 index = 0; index < 16; index++){
        registers->vtl_state.hv_x64_msr_sint[index] = registers->hv_x64_msr_sint[index];
    }
    
    // 
    // Apply VTL state:
    // 
    registers->rip = current_vtl_state.rip;
    registers->rsp = current_vtl_state.rsp;
    registers->rflags = current_vtl_state.rflags;
    registers->cr0 = current_vtl_state.cr0;
    registers->cr3 = current_vtl_state.cr3;
    registers->cr4 = current_vtl_state.cr4;
    // registers->dr7 = current_vtl_state.dr7;
    // registers->dr6 = current_vtl_state.dr6;
    registers->cr8 = current_vtl_state.cr8;
    
    registers->idt_limit = current_vtl_state.idt_limit;
    registers->gdt_limit = current_vtl_state.gdt_limit;
    registers->idt_base = current_vtl_state.idt_base;
    registers->gdt_base = current_vtl_state.gdt_base;
    
    registers->cs = current_vtl_state.cs;
    registers->ds = current_vtl_state.ds;
    registers->es = current_vtl_state.es;
    registers->fs = current_vtl_state.fs;
    registers->gs = current_vtl_state.gs;
    registers->ss = current_vtl_state.ss;
    registers->tr = current_vtl_state.tr;
    registers->ldt = current_vtl_state.ldt;
    
    registers->fs_base = current_vtl_state.fs_base; // MSP C0000100
    registers->gs_base = current_vtl_state.gs_base; // MSR C0000101
    registers->gs_swap = current_vtl_state.gs_swap; // MSR C0000102
    
    registers->ia32_efer = current_vtl_state.ia32_efer; // 0xc0000080
    registers->ia32_pat = current_vtl_state.ia32_pat;  // 0x00000277
    
    registers->ia32_tsc = current_vtl_state.ia32_tsc;
    registers->ia32_tsc_aux = current_vtl_state.ia32_tsc_aux; // 0xc0000103
    
    registers->ia32_lstar = current_vtl_state.ia32_lstar; // 0xc0000082 - Long mode syscall address.
    registers->ia32_cstar = current_vtl_state.ia32_cstar; // 0xc0000083 - Compatibility mode syscall address. (@note: We currently don't support compatibility mode).
    registers->ia32_star = current_vtl_state.ia32_star;  // 0xc0000081 - 32-bit syscall segment + address
    registers->ia32_fmask = current_vtl_state.ia32_fmask; // 0xc0000084 - Flag mask for syscalls.
    
    registers->hv_x64_msr_hypercall_page = current_vtl_state.hv_x64_msr_hypercall_page;
    registers->hv_x64_msr_reference_tsc_page = current_vtl_state.hv_x64_msr_reference_tsc_page;
    registers->hv_x64_msr_vp_assist_page = current_vtl_state.hv_x64_msr_vp_assist_page;
    
    for(u32 index = 0; index < 16; index++){
        registers->hv_x64_msr_sint[index] = current_vtl_state.hv_x64_msr_sint[index];
    }
}
