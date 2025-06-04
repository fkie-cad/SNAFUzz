
struct segment parse_segment_from_global_descriptor_table(struct context *context, u64 gdt_virtual_address, u16 selector){
    struct crash_information crash_information = enter_debugging_routine(context);
    
    // u16 requested_privilege_level = selector & 3;
    u16 table_index = (selector >> 2) & 1;
    assert(table_index == 0);
    
    u16 selector_offset = selector & ~7;
    
    struct{
        u16 limit_0_15;
        u16 base_0_15;
        
        u32 base_16_23     : 8;
        
        //
        // Access Byte.
        //
        u32 segment_type    : 4; // Type
        u32 is_non_system   : 1; // S
        u32 privilege_level : 2; // DPL
        u32 is_present      : 1; // P
        
        u32 limit_16_19     : 4;
        
        //
        // Flags
        //
        u32 reserved       : 1; // avl
        u32 long_mode      : 1; // L
        u32 default_big    : 1; // D/B
        u32 granularity    : 1; // G
        
        u32 base_24_31     : 8;
    } gdt_entry;
    
    int success = guest_read_size(context, &gdt_entry, gdt_virtual_address + selector_offset, sizeof(gdt_entry), PERMISSION_none);
    if(!success){
        print("Error: Could not read selector 0x%x. gdt_virtual_address is %p\n", selector, gdt_virtual_address);
        return /*"null" segment*/(struct segment){.limit = 0x000fffff};
    }
    
    u64 base  = (gdt_entry.base_0_15  << 0) + (gdt_entry.base_16_23  << 16) + (gdt_entry.base_24_31 << 24);
    u32 limit = (gdt_entry.limit_0_15 << 0) + (gdt_entry.limit_16_19 << 16);
    
    if(!gdt_entry.is_non_system){
        u32 base_32_63;
        
        success = guest_read_size(context, &base_32_63, gdt_virtual_address + selector_offset + sizeof(gdt_entry), sizeof(base_32_63), PERMISSION_none);
        if(!success){
            print("Error: Could not read base extension for selector 0x%x. gdt_virtual_address is %p\n", selector, gdt_virtual_address);
            return /*"null" segment*/(struct segment){.limit = 0x000fffff};
        }
        
        base += ((u64)base_32_63 << 32);
    }
    
    struct segment ret = {
        .base  = base,
        .limit = limit,
        .selector = selector,
        
        //
        // Attributes
        // 
        .segment_type    = gdt_entry.segment_type,
        .is_non_system   = gdt_entry.is_non_system,
        .privilege_level = gdt_entry.privilege_level,
        .present         = gdt_entry.is_present,
        .available       = gdt_entry.reserved,
        .long_mode       = gdt_entry.long_mode,
        .default_big     = gdt_entry.default_big,
        .granularity     = gdt_entry.granularity,
    };
    
    exit_debugging_routine(context, crash_information);
    
    return ret;
}


//
// Vector | Description        |   Type    | Error Code 
//    0   | Divide Error       | Fault     |     No
//    1   | Debug Exception    | Fault     |     No
//    2   | NMI Interrupt      | Interrupt |     No
//    3   | Breakpoint         | Trap      |     No
//    4   | Overflow           | Trap      |     No
//    5   | BOUND Range        | Fault     |     No
//    6   | Invalid Opcode     | Fault     |     No
//    7   | WAIT/FWAIT         | Fault     |     No
//    8   | Double Fault       | Abort     |  Yes (Zero)
//    9   | Reserved           | Fault     |     No
//   10   | Invalid TSS        | Fault     |    Yes
//   11   | Segment            | Fault     |    Yes
//   12   | Stack-Segment      | Fault     |    Yes
//   13   | General Protection | Fault     |    Yes
//   14   | Page Fault         | Fault     |    Yes
//   15   | Reserved           | Fault     |     No
//   16   | WAIT/FWAIT         | Fault     |     No
//   17   | Alignment Check    | Fault     |  Yes (Zero)
//   18   | Machine Check      | Abort     |     No
//   19   | SIMD Exception     | Fault     |     No
//   20   | Virtualization     | Fault     |     No
//   21   | Control Protection | Fault     |    Yes
//  22-31 | Reserved           |---------- | --------
// 32-255 | Maskable interrupt |           |
// 
void deliver_exception_or_interrupt(struct context *context, u32 vector_number, int have_error_code, u32 error_code){
    
    struct registers *registers = &context->registers;
    
    struct _KIDTENTRY64{
        u16 OffsetLow;
        u16 Selector;
        struct {
            u16 IstIndex : 3;
            u16 Reserved0 : 5;
            u16 GateType : 5; // 0xE -> 64-bit Interrupt Gate, 0xF -> 64-bit Trap Gate
            u16 Dpl : 2;
            u16 Present : 1;
        };
        
        u16 OffsetMiddle;
        u32 OffsetHigh;
        u32 Reserved1;
    } idt_entry;
    
    int success = guest_read_size(context, &idt_entry, registers->idt_base + sizeof(idt_entry) * vector_number, sizeof(idt_entry), PERMISSION_none);
    crash_assert(success);
    
    u64 offset = ((u64)idt_entry.OffsetHigh << 32) + ((u64)idt_entry.OffsetMiddle << 16) + idt_entry.OffsetLow;
    
    if(PRINT_INTERRUPT_EVENTS){
        print("%p: Executing interrupt %x (priority %d, cr8 %d) -> ", registers->rip, vector_number, vector_number>>4, registers->cr8);
        print_symbol(context, offset);
        print("\n");
    }
    
    u64 previous_rsp = registers->rsp;
    u16 previous_ss  = registers->ss.selector;
    
    if((registers->cs.selector & 3) > (idt_entry.Selector & 3)){
        //
        // "If the handler procedure is going to be executed at a numerically lower privilege level, a stack switch occurs.
        //  The segment selector and stack pointer for the stack to be used by the handler are obtained from the TSS for the
        //  currently executing task. On this new stack the processor pushes the stack segment selector and stack pointer
        //  of the interrupted procedure."
        //
        
        registers->tr = parse_segment_from_global_descriptor_table(context, registers->gdt_base, registers->tr.selector);
        
        u64 InterruptStackTable = registers->tr.base;
        registers->rsp = guest_read(u64, InterruptStackTable + 4);
        
        // "The new SS is set to NULL if there is a change in CPL."
        registers->ss = (struct segment){.limit = 0x000fffff}; // This is what the vm does.
    }
    
    
    {
        // "In IA-32e mode, the RSP is aligned to a 16-byte boundary before pushing the stack frame. The stack
        //  frame itself is aligned on a 16-byte boundary when the interrupt handler is called. The processor can arbitrarily
        //  realign the new RSP on interrupts because the previous (possibly unaligned) RSP is unconditionally saved on the
        //  newly aligned stack. The previous RSP will be automatically restored by a subsequent IRET."
        registers->rsp = registers->rsp & ~0xf;
    }
    
    // "When the CPU calls the interrupt handlers, it changes the value in the RSP register 
    //  to the value specified in the IST, and if there is none, the stack stays the same. 
    //  Onto the new stack, the CPU pushes these values in this order:"
    
    registers->rsp -= 8; guest_write(u64, registers->rsp, previous_ss);            // ss
    registers->rsp -= 8; guest_write(u64, registers->rsp, previous_rsp);           // rsp
    registers->rsp -= 8; guest_write(u64, registers->rsp, registers->rflags);      // rflags
    registers->rsp -= 8; guest_write(u64, registers->rsp, registers->cs.selector); // cs
    registers->rsp -= 8; guest_write(u64, registers->rsp, registers->rip);         // rip
    
    registers->IOPL = 0;
    
    if(have_error_code){
        registers->rsp -= 8; guest_write(u64, registers->rsp, error_code);
    }
    
    if(idt_entry.GateType == 0xE){
        // "If an interrupt or exception handler is called through an interrupt gate, 
        //  the processor clears the interrupt enable (IF) flag in the EFLAGS register 
        //  to prevent subsequent interrupts from interfering with the execution of the handler.
        //  When a handler is called through a trap gate, the state of the IF flag is not changed."
        registers->IF = 0;
    }
    
    registers->rip = offset;
    registers->cs = parse_segment_from_global_descriptor_table(context, registers->gdt_base, idt_entry.Selector);
    
    // Check the sint registers to see if we should perform an auto-eoi.
    for(u32 index = 0; index < 16; index++){
        u64 value = context->registers.hv_x64_msr_sint[index];
        if(!(value & /*masked*/0x10000) && (value & /*auto-eoi*/0x20000) && (u8)value == vector_number){
            apic_perform_end_of_interrupt(&context->registers);
        }
    }
}

void hypervisor_pend_interrupt(struct context *context, struct registers *registers, u32 vector_number);

void pend_interrupt(struct context *context, struct registers *registers, u32 vector_number){
    
    if(context->use_hypervisor){
        hypervisor_pend_interrupt(context, registers, vector_number);
        return;
    }
    
    // We don't call 'deliver_exception_or_interrupt' that should be done in check_for_interrupts.
    apic_pend_interrupt(registers, vector_number);
}

// Called from the jit after an instruction is executed that might cause a pending interrupt to be delivered.
int check_for_interrupts(struct context *context, struct registers *registers){
    
    int interrupt_requested = apic_get_pending_interrupt(registers);
    if(interrupt_requested != -1){
        deliver_exception_or_interrupt(context, interrupt_requested, /*have_error_code*/0, /*error_code*/0);
        return 1;
    }
    return 0;
}

