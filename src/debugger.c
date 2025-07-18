// 
// The main function of the debugger is 'handle_debugger'.
// This function is called from both the JIT and hypervisor loops
// and implements the command line debugger interface. 
// 
// Breakpoints are implement by using either 'hypervisor_set_breakpoint',
// which uses dr0 - dr3 for breakpoint, or in the JIT by using 'add_breakpoint'.
// The JIT then, when emitting instruction, looks up whether or not there
// is a breakpoint on the instruction and if so emits special code
// which "crashes" with 'CRASH_enter_debugger'.
// 
// For memory breakpoints, the hypervisor again uses dr0 - dr3 and the JIT checks
// the breakpoints on each 'guest_read_size' and 'guest_write_size'.
// 
// Single stepping is implemented by either 'hypervisor_set_breakpoint_on_next_instruction'
// or in the JIT by using the 'globals.single_stepping' flag.
// If this flag is set, the JIT only ever emit one instruction in a 'jit_block' and then 
// in the run loop, enters the debugger after each instruction.
// 
// To implement 'breakin' in snapshot mode using CTRL-C, the 'hacky_display.c' sets 
// a global variable ('snapshot_mode_should_break_in_debugger') which is checked 
// in the run loop by both the hypervisor and the JIT. On a second 'CTRL-C', this
// global variable is already set, and we exit the program.
// 
//                                                   - Pascal Beyer 21.03.2024


//_____________________________________________________________________________________________________________________
// Breakpoint API

static char *breakpoint_type_to_string[] = {
    // @note: The first letter should be unique for each type of breakpoint, as they are the b* we put in when declaring them
    //        also we print the first letter when listing.
    [BREAKPOINT_execute] = "execute",
    [BREAKPOINT_read]    = "read",
    [BREAKPOINT_write]   = "write",
    [BREAKPOINT_alloc]   = "allocation",
    [BREAKPOINT_free]    = "free",
};

// returns 'success'.
int add_breakpoint(enum breakpoint_type type, u64 address, u64 length, enum breakpoint_flags flags){
    
    int breakpoint_index = 0;
    for(;globals.breakpoints[breakpoint_index].type != BREAKPOINT_none; breakpoint_index++){
        struct breakpoint breakpoint = globals.breakpoints[breakpoint_index];
        if(breakpoint.type == type && breakpoint.address == address && breakpoint.flags == flags){
            // Allow changing the length of a breakpoint by redefining it.
            globals.breakpoints[breakpoint_index].length = length;
            print("Breakpoint %d redefined.\n", breakpoint_index);
            return 1;
        }
    }
    
    // Don't ever use the last breakpoint!
    if(breakpoint_index + 1 >= array_count(globals.breakpoints)){
        print("Too many breakpoints\n");
        return 0;
    }
    
    globals.breakpoints[breakpoint_index].type    = type;
    globals.breakpoints[breakpoint_index].flags   = flags;
    globals.breakpoints[breakpoint_index].address = address;
    globals.breakpoints[breakpoint_index].length  = length;
    
    globals.breakpoint_count += 1;
    
    if(!(flags & BREAKPOINT_FLAG_oneshot)){
        print("Defined breakpoint %x: %c at %p\n", breakpoint_index, breakpoint_type_to_string[type][0], address);
    }
    
    return 1;
}

void clear_breakpoint(int breakpoint_index){
    assert(breakpoint_index < array_count(globals.breakpoints));
    
    if(globals.breakpoints[breakpoint_index].type == BREAKPOINT_none) return;
    
    globals.breakpoint_count -= 1;
    
    globals.breakpoints[breakpoint_index].type = BREAKPOINT_none;
    if(!(globals.breakpoints[breakpoint_index].flags & BREAKPOINT_FLAG_oneshot)){
        print("Breakpoint %x cleared\n", breakpoint_index);
    }
}

int check_breakpoint(enum breakpoint_type type, u64 address_start, u64 size){
    
    if(globals.breakpoint_count == 0) return 0;
    
    u64 address_end = address_start + size;
    
    for(int breakpoint_index = 0; breakpoint_index < array_count(globals.breakpoints); breakpoint_index++){
        if(globals.breakpoints[breakpoint_index].type != type) continue;
        
        struct breakpoint breakpoint = globals.breakpoints[breakpoint_index];
        u64 breakpoint_start = breakpoint.address;
        u64 breakpoint_end   = breakpoint.address + breakpoint.length;
        
        //
        // We are accessing
        //     [address_start, address_end)
        // and the breakpoint range is
        //     [breakpoint_start, breakpoint_end)
        //
        // Therefore we need to avoid the two cases:
        //     breakpoint_end <= address_start
        //     address_end    <= breakpoint_start
        // And therefore we are good if these two conditions are true:
        //     address_start    < breakpoint_end
        //     breakpoint_start < address_end
        
        if(address_start < breakpoint_end && breakpoint_start < address_end){
            globals.breakpoint_hit_index = breakpoint_index;
            return 1;
        }
    }
    return 0;
}

//_____________________________________________________________________________________________________________________
// Utilities for hypervisor breakpoints.

u64 get_address_for_vector(struct context *context, struct registers *registers, u32 vector_number){
    u64 IdtBase = registers->idt_base;
    
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
    
    int success = guest_read_size(context, &idt_entry, IdtBase + sizeof(idt_entry) * vector_number, sizeof(idt_entry), PERMISSION_none);
    assert(success);
    
    u64 offset = ((u64)idt_entry.OffsetHigh << 32) + ((u64)idt_entry.OffsetMiddle << 16) + idt_entry.OffsetLow;
    
    return offset;
}

// @cleanup: This function should live somewhere else.
u64 get_address_of_next_instruction(struct context *context, struct registers *registers){
    
    u8 instruction_buffer[16] = {0};
    u32 instruction_buffer_size = prefetch_instruction(context, registers->rip, instruction_buffer, sizeof(instruction_buffer));
    
    if(!instruction_buffer_size){
        // @note: When it tries to execute this instruction it will page fault.
        return get_address_for_vector(context, registers, 0xe);
    }
    
    struct crash_information crash_information = enter_debugging_routine(context);
    
    u64 next_rip = registers->rip;
    
    try_again_because_move_to_ss_is_weird:;
    
    struct instruction_information decoded_instruction = decode_instruction(instruction_buffer);
    
    if(decoded_instruction.instruction_size > instruction_buffer_size){
        // @note: When it tries to execute this instruction it will page fault.
        exit_debugging_routine(context, crash_information);
        return get_address_for_vector(context, registers, 0xe);
    }
    
    next_rip += decoded_instruction.instruction_size; // This has to be updated for the 'mov ss, '
    u32 augmented_opcode = decoded_instruction.augmented_opcode;
    
    switch(augmented_opcode){
        
        // ret imm16
        case 0xc2: next_rip = guest_read(u64, registers->rsp + *(s16 *)&instruction_buffer[1]); break;
        
        // ret
        case 0xc3: {
            // @cleanup: for the branch history clearing, it can happen that we jump
            //           to the same instruction that we are currently at.
            //           This would cause us to infinitly loop never actually executing one
            //           instruction. Hence, I am hacking it up here.
            //           There is maybe a way to make this work using the 'FLAG_RF'.
            
            u64 rsp = registers->rsp;
            
            do{
                next_rip = guest_read(u64, rsp);
                rsp += 8;
            } while(next_rip == registers->rip);
        }break;
        
        // retf
        case 0xcb:{
            if(decoded_instruction.rex & REXW){
                next_rip = guest_read(u64, registers->rsp);
            }else{
                next_rip = guest_read(u32, registers->rsp);
            }
        }break;
        
        // @note: 0xf1 generates a debug trap, which we catch in the debugger.
        //        0xcc we do not want to catch in the hypervisor.
        //           
        
        case 0xcc:{
            next_rip = get_address_for_vector(context, registers, 3);
        }break;
        
        case 0xcd:{
            u8 vector = (u8)decoded_instruction.immediate;
            next_rip = get_address_for_vector(context, registers, vector);
        }break;
        
        case 0xce:{ 
            if(registers->OF) next_rip = get_address_for_vector(context, registers, 4); 
        }break;
        
        // iret
        case 0xcf:{
            next_rip = guest_read(u64, registers->rsp);
            
            u64 rflags = guest_read(u64, registers->rsp + 0x10);
            
            struct registers temp = context->registers;
            temp.IF = (rflags & FLAG_IF) != 0;
            
            int vector = apic_get_pending_interrupt(&temp);
            if(vector != -1){
                next_rip = get_address_for_vector(context, registers, vector);
            }
            
        }break;
        
        case 0xe0:{ // LOOPNZ - Decrement count; Jump short if count!=0 and ZF=0
            if(registers->ZF == 0 && (registers->rcx-1) != 0){
                next_rip += (s8)decoded_instruction.immediate;
            }
        }break;
        
        case 0xe1:{ // LOOPZ - Decrement count; Jump short if count!=0 and ZF=1
            if(registers->ZF == 1 && (registers->rcx-1) != 0){
                next_rip += (s8)decoded_instruction.immediate;
            }
        }break;
        
        case 0xe2:{ // LOOP - Decrement count; Jump short if count!=0
            if((registers->rcx-1) != 0){
                next_rip += (s8)decoded_instruction.immediate;
            }
        }break;
        
        case 0xe3:{ // JRCXZ - Jump short if rCX register is 0
            if(registers->rcx == 0){
                next_rip += (s8)decoded_instruction.immediate;
            }
        }break;
        
        case 0x8e:{
            // "Loading the SS register with a MOV instruction suppresses or inhibits some debug exceptions
            //  and inhibits interrupts on the following instruction boundary. 
            //  (The inhibition ends after delivery of an exception or the execution of the next instruction.) 
            //  This behavior allows a stack pointer to be loaded into the ESP register with the next instruction 
            //  (MOV ESP, stack-pointer value) before an event can be delivered."
            
            if(decoded_instruction.reg == 2){
                prefetch_instruction(context, next_rip, instruction_buffer, sizeof(instruction_buffer));
                goto try_again_because_move_to_ss_is_weird;
            }
        }break;
        
        case 0x70: if(registers->OF != 0) next_rip += (s8)decoded_instruction.immediate; break;
        case 0x71: if(registers->OF == 0) next_rip += (s8)decoded_instruction.immediate; break;
        case 0x72: if(registers->CF != 0) next_rip += (s8)decoded_instruction.immediate; break;
        case 0x73: if(registers->CF == 0) next_rip += (s8)decoded_instruction.immediate; break;
        case 0x74: if(registers->ZF != 0) next_rip += (s8)decoded_instruction.immediate; break;
        case 0x75: if(registers->ZF == 0) next_rip += (s8)decoded_instruction.immediate; break;
        case 0x76: if(registers->CF != 0 || registers->ZF != 0) next_rip += (s8)decoded_instruction.immediate; break;
        case 0x77: if(registers->CF == 0 && registers->ZF == 0) next_rip += (s8)decoded_instruction.immediate; break;
        case 0x78: if(registers->SF != 0) next_rip += (s8)decoded_instruction.immediate; break;
        case 0x79: if(registers->SF == 0) next_rip += (s8)decoded_instruction.immediate; break;
        case 0x7A: if(registers->PF != 0) next_rip += (s8)decoded_instruction.immediate; break;
        case 0x7B: if(registers->PF == 0) next_rip += (s8)decoded_instruction.immediate; break;
        case 0x7C: if(registers->SF != registers->OF) next_rip += (s8)decoded_instruction.immediate; break;
        case 0x7D: if(registers->SF == registers->OF) next_rip += (s8)decoded_instruction.immediate; break;
        case 0x7E: if((registers->ZF != 0) || (registers->SF != registers->OF)) next_rip += (s8)decoded_instruction.immediate; break;
        case 0x7F: if((registers->ZF == 0) && (registers->SF == registers->OF)) next_rip += (s8)decoded_instruction.immediate; break;
        
        // jmp s8
        case 0xeb: next_rip += (s8)decoded_instruction.immediate; break;
        
        case 0xe9: case 0xe8:{ // call/jmp rel32
            next_rip += (s32)decoded_instruction.immediate;
        }break;
        
        case 0xff:{
            if(decoded_instruction.reg == 2 || decoded_instruction.reg == 4){
                int base = decoded_instruction.regm;
                
                if(decoded_instruction.mod == MOD_REG){
                    next_rip = registers->gpr[decoded_instruction.regm];
                }else{
                    u64 address = decoded_instruction.address_offset;
                    
                    if(decoded_instruction.have_sib){
                        int index = decoded_instruction.index_reg;
                        
                        if(base != INVALID_REGISTER){
                            address += registers->gpr[base];
                        }
                        
                        if(index != INVALID_REGISTER){
                            address += registers->gpr[index] << decoded_instruction.scale;
                        }
                    }else{
                        if(base == INVALID_REGISTER){
                            address += next_rip;
                        }else{
                            address += registers->gpr[base];
                        }
                    }
                    
                    if(decoded_instruction.legacy_prefix_flags & LEGACY_gs_segment_override){
                        address += registers->gs_base;
                    }
                    
                    next_rip = guest_read(u64, address);
                }
            }
        }break;
        
        case 0x180: if(registers->OF != 0) next_rip += (s32)decoded_instruction.immediate; break;
        case 0x181: if(registers->OF == 0) next_rip += (s32)decoded_instruction.immediate; break;
        case 0x182: if(registers->CF != 0) next_rip += (s32)decoded_instruction.immediate; break;
        case 0x183: if(registers->CF == 0) next_rip += (s32)decoded_instruction.immediate; break;
        case 0x184: if(registers->ZF != 0) next_rip += (s32)decoded_instruction.immediate; break;
        case 0x185: if(registers->ZF == 0) next_rip += (s32)decoded_instruction.immediate; break;
        case 0x186: if(registers->CF != 0 || registers->ZF != 0) next_rip += (s32)decoded_instruction.immediate; break;
        case 0x187: if(registers->CF == 0 && registers->ZF == 0) next_rip += (s32)decoded_instruction.immediate; break;
        case 0x188: if(registers->SF != 0) next_rip += (s32)decoded_instruction.immediate; break;
        case 0x189: if(registers->SF == 0) next_rip += (s32)decoded_instruction.immediate; break;
        case 0x18A: if(registers->PF != 0) next_rip += (s32)decoded_instruction.immediate; break;
        case 0x18B: if(registers->PF == 0) next_rip += (s32)decoded_instruction.immediate; break;
        case 0x18C: if(registers->SF != registers->OF) next_rip += (s32)decoded_instruction.immediate; break;
        case 0x18D: if(registers->SF == registers->OF) next_rip += (s32)decoded_instruction.immediate; break;
        case 0x18E: if((registers->ZF != 0) || (registers->SF != registers->OF)) next_rip += (s32)decoded_instruction.immediate; break;
        case 0x18F: if((registers->ZF == 0) && (registers->SF == registers->OF)) next_rip += (s32)decoded_instruction.immediate; break;
        
        // syscall
        case 0x105: next_rip = registers->ia32_lstar; break;
        // sysret
        case 0x107: next_rip = registers->rcx; break;
        
        //
        // @note: We also handle all things here, which have to check for interrupts.
        //        This is because otherwise we cannot know that we hit an interrupt
        //        and get a stay one-shot breakpoint at the interrupt return address.
        //
        
        // mov cr8, regm
        case 0x122:{
            if(decoded_instruction.reg == 8){
                assert(decoded_instruction.mod == MOD_REG); // @cleanup:
                
                struct registers temp = context->registers;
                temp.cr8 = registers->gpr[decoded_instruction.regm];
                
                int vector = apic_get_pending_interrupt(&temp);
                if(vector != -1){
                    next_rip = get_address_for_vector(context, registers, vector);
                }
            }
        }break;
        
        // popf
        case 0x9d:{
            u64 rflags = guest_read(u64, registers->rsp);
            struct registers temp = context->registers;
            temp.IF = (rflags & FLAG_IF) != 0;
            
            int vector = apic_get_pending_interrupt(&temp);
            if(vector != -1){
                next_rip = get_address_for_vector(context, registers, vector);
            }
        }break;
        
        // sti
        case 0xfb:{
            struct registers temp = context->registers;
            temp.IF = 1;
            
            int vector = apic_get_pending_interrupt(&temp);
            if(vector != -1){
                next_rip = get_address_for_vector(context, registers, vector);
            }
        }break;
    }
    
    // If we crashed it's probably a page fault, otherwise rsp would have to be non-canonical.
    if(context->crash) next_rip = get_address_for_vector(context, registers, 0xe);
    
    exit_debugging_routine(context, crash_information);
    
    return next_rip;
}

void hypervisor_clear_oneshot_breakpoint(struct registers *registers, u64 address){
    if(address == registers->dr0 && (globals.breakpoints[0].flags & BREAKPOINT_FLAG_oneshot)) registers->dr7 &= ~0x02; // disable dr0
    if(address == registers->dr1 && (globals.breakpoints[1].flags & BREAKPOINT_FLAG_oneshot)) registers->dr7 &= ~0x08; // disable dr1
    if(address == registers->dr2 && (globals.breakpoints[2].flags & BREAKPOINT_FLAG_oneshot)) registers->dr7 &= ~0x20; // disable dr2
    if(address == registers->dr3 && (globals.breakpoints[3].flags & BREAKPOINT_FLAG_oneshot)) registers->dr7 &= ~0x80; // disable dr3
}

int hypervisor_set_breakpoint(struct context *context, struct registers *registers, enum breakpoint_type type, enum breakpoint_flags flags, u64 address, u64 length){
    
    int type_bits = 0;
    if(type == BREAKPOINT_read)  type_bits = 0b11; // @note: This is read or write, but whatever.
    if(type == BREAKPOINT_write) type_bits = 0b01;
    
    int length_bits = 0;
    if(length == 1) length_bits = 0b00;
    else if(length == 2) length_bits = 0b01;
    else if(length == 4) length_bits = 0b11; // @note: This has some weird swizzle.
    else if(length == 8) length_bits = 0b10;
    else{
        print("Hypervisor does not support breakpoint of length != 1,2,4,8.\n");
        return 1;
    }
    
    registers->dr7 |= (1 << 8) | (1 << 9) | (1 << 10); // Local exact, global exact, reserved must be 1.
    registers->dr7 &= ~((1 << 12) | (1 << 14) | (1 << 15)); // Reserved must be 0.
    
    while(true){
        if((registers->dr7 & 2) == 0 || registers->dr0 == address){
            registers->dr0 = address;
            registers->dr7 = (registers->dr7 & ~(0b1111 << 16)) | (type_bits << 16) | (length_bits << 18) | 2;
            globals.breakpoints[0].type = type;
            globals.breakpoints[0].flags = flags;
        }else if((registers->dr7 & 8) == 0 || registers->dr1 == address){
            registers->dr1 = address;
            registers->dr7 = (registers->dr7 & ~(0b1111 << 20)) | (type_bits << 20) | (length_bits << 22) | 8;
            globals.breakpoints[1].type = type;
            globals.breakpoints[1].flags = flags;
        }else if((registers->dr7 & 0x20) == 0 || registers->dr2 == address){
            registers->dr2 = address;
            registers->dr7 = (registers->dr7 & ~(0b1111 << 24)) | (type_bits << 24) | (length_bits << 26) | 0x20;
            globals.breakpoints[2].type = type;
            globals.breakpoints[2].flags = flags;
        }else if((registers->dr7 & 0x80) == 0 || registers->dr3 == address){
            registers->dr3 = address;
            registers->dr7 = (registers->dr7 & ~(0b1111 << 28)) | (type_bits << 28) | (length_bits << 30) | 0x80;
            globals.breakpoints[3].type = type;
            globals.breakpoints[3].flags = flags;
        }else{
            print("[hypervisor] Too many breakpoints:\n");
            print("    [dr0] %p:", registers->dr0); print_symbol(context, registers->dr0); print("\n");
            print("    [dr1] %p:", registers->dr1); print_symbol(context, registers->dr1); print("\n");
            print("    [dr2] %p:", registers->dr2); print_symbol(context, registers->dr2); print("\n");
            print("    [dr3] %p:", registers->dr3); print_symbol(context, registers->dr3); print("\n");
            
            if(globals.in_debugger) return 0; // failure.
            
            handle_debugger(context);
            continue;
        }
        break;
    }
    
    return 1; // success
}

void hypervisor_set_breakpoint_on_vector(struct context *context, struct registers *registers, u32 vector_number){
    u64 offset = get_address_for_vector(context, registers, vector_number);
    hypervisor_set_breakpoint(context, registers, BREAKPOINT_execute, BREAKPOINT_FLAG_oneshot, offset, 1);
}

int hypervisor_set_breakpoint_on_next_instruction(struct context *context, struct registers *registers){
    
    u64 next_rip = get_address_of_next_instruction(context, registers);
    return hypervisor_set_breakpoint(context, registers, BREAKPOINT_execute, BREAKPOINT_FLAG_oneshot, next_rip, 1);
}

//_____________________________________________________________________________________________________________________
// Parsing addresses

u64 parse_one_address(struct context *context, struct string symbol, int *error){
    
    struct registers *registers = &context->registers;
    
    //
    // Parse general purpose registers.
    //
    if(string_match(symbol, string("rip"))) return registers->rip;
    if(string_match(symbol, string("rax"))) return registers->rax;
    if(string_match(symbol, string("rcx"))) return registers->rcx;
    if(string_match(symbol, string("rdx"))) return registers->rdx;
    if(string_match(symbol, string("rbx"))) return registers->rbx;
    if(string_match(symbol, string("rsi"))) return registers->rsi;
    if(string_match(symbol, string("rdi"))) return registers->rdi;
    if(string_match(symbol, string("rsp"))) return registers->rsp;
    if(string_match(symbol, string("rbp"))) return registers->rbp;
    if(string_match(symbol, string("r8")))  return registers->r8;
    if(string_match(symbol, string("r9")))  return registers->r9;
    if(string_match(symbol, string("r10"))) return registers->r10;
    if(string_match(symbol, string("r11"))) return registers->r11;
    if(string_match(symbol, string("r12"))) return registers->r12;
    if(string_match(symbol, string("r13"))) return registers->r13;
    if(string_match(symbol, string("r14"))) return registers->r14;
    if(string_match(symbol, string("r15"))) return registers->r15;
    
    //
    // Parse segment registers.
    //
    if(string_match(symbol, string("fs"))) return registers->fs_base;
    if(string_match(symbol, string("gs"))) return registers->gs_base;
    
    //
    // Get the address from one of the loaded modules.
    //
    
    struct string module_name = get_module_name_from_symbol_string(symbol);
    
    if(module_name.size){
        symbol.data += module_name.size + 1;
        symbol.size -= module_name.size + 1;
        
        struct loaded_module *module = get_loaded_module(module_name);
        
        if(!module){
            *error = 1;
            return 0;
        }
        
        u64 address = get_symbol_from_module(context, module, symbol);
        if(address) return address;
        
        return get_constant_from_module(context, module, symbol, error);
    }
    
    struct loaded_module *module = get_loaded_module(symbol);
    if(module) return module->guest_image_base;
    
    return parse_number(symbol, error);
}

u64 parse_address_multiply(struct context *context, struct string *line, int *error){
    
    //
    // Parse addresses, until there was no '*', '/' anymore.
    //
    
    u64 address  = 1;
    int operator = '*';
    
    while(true){
        
        //
        // Eat all leading whitespace.
        //
        string_skip_whitespace(line);
        
        //
        // Get the symbol.
        //
        struct string symbol = *line;
        
        while(line->size){
            if(character_is_whitespace(line->data[0]) || line->data[0] == '*' || line->data[0] == '/' || line->data[0] == '+' || line->data[0] == '-') break;
            
            line->size -= 1;
            line->data += 1;
        }
        
        symbol.size = line->data - symbol.data;
        
        //
        // Eat whitespace after the symbol.
        //
        string_skip_whitespace(line);
        
        //
        // Parse the symbol and merge it into the address.
        //
        u64 symbol_address = parse_one_address(context, symbol, error);
        
        if(*error){
            print("[parse_address] Could not find '%.*s'.\n", symbol.size, symbol.data);
            return 0;
        }
        
        if(operator == '*'){
            address *= symbol_address;
        }else if(operator == '/'){
            if(!symbol_address){
                print("Divide by 0.\n");
                *error = 1;
                return 0;
            }
            address /= symbol_address;
        }
        
        //
        // Check if the next character is a '*' or a '/'.
        //
        if(!line->size) break;
        
        if(line->data[0] == '*' || line->data[0] == '/'){
            operator = line->data[0];
            
            line->size -= 1;
            line->data += 1;
        }else{
            break;
        }
    }
    
    return address;
}

u64 parse_address(struct context *context, struct string *line, int *error){
    
    //
    // Parse addresses, until there was no '+', '-' anymore.
    //
    
    u64 address  = 0;
    int operator = '+';
    
    while(true){
        u64 symbol_address = parse_address_multiply(context, line, error);
        
        if(*error) return 0;
        
        if(operator == '+'){
            address += symbol_address;
        }else if(operator == '-'){
            address -= symbol_address;
        }
        
        //
        // Check if the next character is a '+' or a '-'.
        //
        if(!line->size) break;
        
        if(line->data[0] == '+' || line->data[0] == '-'){
            operator = line->data[0];
            
            line->size -= 1;
            line->data += 1;
        }else{
            break;
        }
    }
    
    return address;
}

void parse_breakpoint(struct context *context, enum breakpoint_type type, struct string *line){
    int error = 0;
    u64 address = parse_address(context, line, &error);
    
    if(error) return;
    
    u64 length = 1;
    if(line->size && line->data[0] == 'L'){
        
        line->size -= 1;
        line->data += 1;
        
        length = parse_address(context, line, &error);
        if(error) return;
    }
    
    if(line->size){
        print("Warning: Junk '%.*s' after breakpoint.\n", line->size, line->data);
    }
    
    if(context->use_hypervisor){
        hypervisor_set_breakpoint(context, &context->registers, type, BREAKPOINT_FLAG_none, address, length);
    }else{
        add_breakpoint(type, address, length, BREAKPOINT_FLAG_none);
    }
}

//_____________________________________________________________________________________________________________________
// Printing registers

void print_flags(u64 rflags, FILE *file){
    if(rflags & FLAG_CF) fprintf(file, " CF");
    if(rflags & FLAG_PF) fprintf(file, " PF");
    if(rflags & FLAG_AF) fprintf(file, " AF");
    if(rflags & FLAG_ZF) fprintf(file, " ZF");
    if(rflags & FLAG_SF) fprintf(file, " SF");
    if(rflags & FLAG_TF) fprintf(file, " TF");
    if(rflags & FLAG_IF) fprintf(file, " IF");
    if(rflags & FLAG_DF) fprintf(file, " DF");
    if(rflags & FLAG_OF) fprintf(file, " OF");
    if(rflags & FLAG_NT) fprintf(file, " NT");
    if(rflags & FLAG_RF) fprintf(file, " RF");
    if(rflags & FLAG_VM) fprintf(file, " VM");
    if(rflags & FLAG_AC) fprintf(file, " AC");
    if(rflags & FLAG_VIF) fprintf(file, " VIF");
    if(rflags & FLAG_VIP) fprintf(file, " VIP");
    if(rflags & FLAG_ID) fprintf(file, " ID");
}

enum print_mode{
    PRINT_rip     = 0x1,
    PRINT_gpr     = 0x2,
    PRINT_flags   = 0x4,
    PRINT_cr      = 0x8,
    PRINT_segment = 0x10,
    PRINT_xmm     = 0x20,
    PRINT_fpu     = 0x40,
    PRINT_symbol  = 0x80,
    
    PRINT_default = PRINT_symbol | PRINT_gpr | PRINT_flags,
    PRINT_all     = PRINT_symbol | PRINT_rip | PRINT_gpr | PRINT_flags | PRINT_cr | PRINT_segment | PRINT_xmm | PRINT_fpu,
    
    PRINT_kd      = 0x100,    
};

void print_registers(struct context *context, FILE *file){
    
    struct registers *registers = &context->registers;
    
    enum print_mode mode = globals.print_mode;
    
    if(mode & PRINT_rip){
        struct loaded_module *module = get_module_for_address(registers->rip);
        if(module){
            fprint(file, "%p: %.*s + 0x%llx\n", registers->rip, module->short_name.size, module->short_name.data, registers->rip - module->guest_image_base);
        }else{
            fprint(file, "%p\n", registers->rip);
        }
    }
    
    if(mode & PRINT_symbol){
        struct loaded_module *module = get_module_for_address(registers->rip);
        
        if(module){
            print_symbol_from_loaded_module(context, module, registers->rip, file);
            fprint(file, "\n");
        }else{
            fprint(file, "%p\n", registers->rip);
        }
    }
    
    if(mode & PRINT_gpr){
        fprint(file, 
                "    rax: %p, rcx: %p, rdx: %p, rbx: %p,\n"
                "    rsp: %p, rbp: %p, rsi: %p, rdi: %p,\n"
                "    r8:  %p, r9:  %p, r10: %p, r11: %p,\n"
                "    r12: %p, r13: %p, r14: %p, r15: %p,\n"
                "\n",
                registers->rax, registers->rcx, registers->rdx, registers->rbx,
                registers->rsp, registers->rbp, registers->rsi, registers->rdi,
                registers->r8,  registers->r9,  registers->r10, registers->r11,
                registers->r12, registers->r13, registers->r14, registers->r15);
    }
    
    if(mode & PRINT_flags){
        fprint(file, "rflags %x:", registers->rflags); print_flags(registers->rflags, file); fprint(file, "\n");
    }
    
    if(mode & PRINT_cr){
        fprint(file, "cr0 %llx, cr2 %llx, cr3 %llx, cr4 %llx, cr8 %llx, xcr0 %llx, efer %llx\n", registers->cr0, registers->cr2, registers->cr3, registers->cr4, registers->cr8, registers->xcr0, registers->ia32_efer);
    }
    
    if(mode & PRINT_segment){
        fprint(file, "cs %.4x ss %.4x ds %.4x es %.4x fs %.4x gs %.4x\n", registers->cs.selector, registers->ss.selector, registers->ds.selector, registers->es.selector, registers->fs.selector, registers->gs.selector);
    }
    
    if(mode & PRINT_xmm){
        for(int i = 0; i < 16; i += 2){
            fprint(file, "    xmm%.2d = %p%p,  xmm%.2d = %p%p \n", i, _mm_extract_epi64(registers->simd[i].xmmi, 1), _mm_extract_epi64(registers->simd[i].xmmi, 0), i+1, _mm_extract_epi64(registers->simd[i + 1].xmmi, 1), _mm_extract_epi64(registers->simd[i + 1].xmmi, 0));
        }
    }
    
    if(mode & PRINT_fpu){
        fprint(file, "fpcw: %x fpsw: %x fptw: %x mxcsr: %x mxcsr_mask: %x\n", registers->fpu_control_word, registers->fpu_status_word, registers->fpu_tag_word, registers->mxcsr, registers->mxcsr_mask);
    }
    
    if(mode & PRINT_kd){
        //
        // Print like kd. This is useful for diffing.
        //
        fprint(file,
                "rax=%.16llx rbx=%.16llx rcx=%.16llx\n"
                "rdx=%.16llx rsi=%.16llx rdi=%.16llx\n"
                "rip=%.16llx rsp=%.16llx rbp=%.16llx\n"
                " r8=%.16llx  r9=%.16llx r10=%.16llx\n"
                "r11=%.16llx r12=%.16llx r13=%.16llx\n"
                "r14=%.16llx r15=%.16llx\n"
                "cs=%.4x  ss=%.4x  ds=%.4x  es=%.4x  fs=%.4x  gs=%.4x             efl=%.8x\n"
                ,
                registers->rax, registers->rbx, registers->rcx,
                registers->rdx, registers->rsi, registers->rdi,
                registers->rip, registers->rsp, registers->rbp,
                
                registers->r8,  registers->r9,  registers->r10,
                registers->r11, registers->r12, registers->r13,
                registers->r14, registers->r15,
                registers->cs.selector, registers->ss.selector, registers->ds.selector, registers->es.selector,
                registers->fs.selector, registers->gs.selector, registers->eflags
                );
    }
}

//_____________________________________________________________________________________________________________________
// Printing disassembly

void print_reg(enum register_encoding reg, int size){
    print("%s", reg_to_string(reg, size));
}

void print_xmm(__m128i reg, u32 index){
    print("xmm%d_u8  = { %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x }\n",
            index, _mm_extract_epi8(reg, 0), _mm_extract_epi8(reg, 1), _mm_extract_epi8(reg, 2), _mm_extract_epi8(reg, 3),
            _mm_extract_epi8(reg, 4), _mm_extract_epi8(reg, 5), _mm_extract_epi8(reg, 6), _mm_extract_epi8(reg, 7),
            _mm_extract_epi8(reg, 8), _mm_extract_epi8(reg, 9), _mm_extract_epi8(reg, 10), _mm_extract_epi8(reg, 11),
            _mm_extract_epi8(reg, 12), _mm_extract_epi8(reg, 13), _mm_extract_epi8(reg, 14), _mm_extract_epi8(reg, 15));
    
    print("xmm%d_u16 = { %.4x, %.4x, %.4x, %.4x, %.4x, %.4x, %.4x, %.4x }\n",
            index, _mm_extract_epi16(reg, 0), _mm_extract_epi16(reg, 1), _mm_extract_epi16(reg, 2), _mm_extract_epi16(reg, 3),
            _mm_extract_epi16(reg, 4), _mm_extract_epi16(reg, 5), _mm_extract_epi16(reg, 6), _mm_extract_epi16(reg, 7));
    
    print("xmm%d_u32 = { %.8x, %.8x, %.8x, %.8x }\n",
            index, _mm_extract_epi32(reg, 0), _mm_extract_epi32(reg, 1), _mm_extract_epi32(reg, 2), _mm_extract_epi32(reg, 3) );
    
    print("xmm%d_u64 = { %.16llx, %.16llx }\n",
            index, _mm_extract_epi64(reg, 0), _mm_extract_epi64(reg, 1) );
    
    print("xmm%d_u64 = { %.16llx, %.16llx }\n",
            index, _mm_extract_epi64(reg, 0), _mm_extract_epi64(reg, 1) );
}

void print_ymm(__m256i reg, u32 index){
    print("ymm%d_u8  = { %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x }\n",
            index, _mm256_extract_epi8(reg, 0), _mm256_extract_epi8(reg, 1), _mm256_extract_epi8(reg, 2), _mm256_extract_epi8(reg, 3),
            _mm256_extract_epi8(reg, 4), _mm256_extract_epi8(reg, 5), _mm256_extract_epi8(reg, 6), _mm256_extract_epi8(reg, 7),
            _mm256_extract_epi8(reg, 8), _mm256_extract_epi8(reg, 9), _mm256_extract_epi8(reg, 10), _mm256_extract_epi8(reg, 11),
            _mm256_extract_epi8(reg, 12), _mm256_extract_epi8(reg, 13), _mm256_extract_epi8(reg, 14), _mm256_extract_epi8(reg, 15),
            _mm256_extract_epi8(reg, 16), _mm256_extract_epi8(reg, 17), _mm256_extract_epi8(reg, 18), _mm256_extract_epi8(reg, 19),
            _mm256_extract_epi8(reg, 20), _mm256_extract_epi8(reg, 21), _mm256_extract_epi8(reg, 22), _mm256_extract_epi8(reg, 23),
            _mm256_extract_epi8(reg, 24), _mm256_extract_epi8(reg, 25), _mm256_extract_epi8(reg, 26), _mm256_extract_epi8(reg, 27),
            _mm256_extract_epi8(reg, 28), _mm256_extract_epi8(reg, 29), _mm256_extract_epi8(reg, 30), _mm256_extract_epi8(reg, 31));
    
    print("ymm%d_u16 = { %.4x, %.4x, %.4x, %.4x, %.4x, %.4x, %.4x, %.4x, %.4x, %.4x, %.4x, %.4x, %.4x, %.4x, %.4x, %.4x }\n",
            index, _mm256_extract_epi16(reg, 0), _mm256_extract_epi16(reg, 1), _mm256_extract_epi16(reg, 2), _mm256_extract_epi16(reg, 3),
            _mm256_extract_epi16(reg, 4), _mm256_extract_epi16(reg, 5), _mm256_extract_epi16(reg, 6), _mm256_extract_epi16(reg, 7),
            _mm256_extract_epi16(reg, 8), _mm256_extract_epi16(reg, 9), _mm256_extract_epi16(reg, 10), _mm256_extract_epi16(reg, 11),
            _mm256_extract_epi16(reg, 12), _mm256_extract_epi16(reg, 13), _mm256_extract_epi16(reg, 14), _mm256_extract_epi16(reg, 15));
    
    print("ymm%d_u32 = { %.8x, %.8x, %.8x, %.8x, %.8x, %.8x, %.8x, %.8x }\n",
            index, _mm256_extract_epi32(reg, 0), _mm256_extract_epi32(reg, 1), _mm256_extract_epi32(reg, 2), _mm256_extract_epi32(reg, 3),
            _mm256_extract_epi32(reg, 4), _mm256_extract_epi32(reg, 5), _mm256_extract_epi32(reg, 6), _mm256_extract_epi32(reg, 7) );
    
    print("ymm%d_u64 = { %.16llx, %.16llx, %.16llx, %.16llx }\n",
            index, _mm256_extract_epi64(reg, 0), _mm256_extract_epi64(reg, 1), _mm256_extract_epi64(reg, 2), _mm256_extract_epi64(reg, 3) );
}

void print_segment(struct segment segment){
    print("{ .base = %p, .limit = %.8x, .selector = 0x%x, .type = 0x%x, .privilege_level = %d, .flags = ", segment.base, segment.limit, segment.selector, segment.segment_type, segment.privilege_level);
    if(segment.is_non_system) print("NS ");
    if(segment.present)       print("P ");
    if(segment.available)     print("A ");
    if(segment.long_mode)     print("LM ");
    if(segment.default_big)   print("DB ");
    if(segment.granularity)   print("G ");
    print("}\n");
}

void print_rep_flags(u32 flags, int rep_is_repz){
    if(rep_is_repz && (flags & LEGACY_rep))  print("repz ");
    if(!rep_is_repz && (flags & LEGACY_rep)) print("rep ");
    if(flags & LEGACY_repn)                  print("repn ");
}

void print_modrm(int operand_size, int have_sib, int regm, int index_reg, u8 mod, enum legacy_prefix legacy_prefix_flags, s32 address_offset, int scale, int is_rip_relative){
    
    if(mod == MOD_REG){
        print_reg(regm, operand_size);
    }else{
        if((operand_size) == -1) print("[");
        if((operand_size) ==  1) print("byte ptr [");
        if((operand_size) ==  2) print("word ptr [");
        if((operand_size) ==  4) print("dword ptr [");
        if((operand_size) ==  8) print("qword ptr [");
        if((operand_size) == 16) print("xmm ptr [");
        if((operand_size) == 32) print("ymm ptr [");
        if((operand_size) == 64) print("zmm ptr [");
        if(legacy_prefix_flags & LEGACY_gs_segment_override){
            print("gs:");
        }
        if(have_sib){
            if(regm != -1){
                print_reg(regm, 8);
            }else{
                u64 disp32 = (s32)address_offset;
                print("0x%llx", disp32);
            }
            if(index_reg != -1){
                print(" + ");
                if(scale) print("%d*", (1 << scale));
                print_reg(index_reg, 8);
            }
        }else{
            if(regm == -1){
                print("rip");
            }else{
                print_reg(regm, 8);
            }
        }
        if(mod == MOD_REGM_OFF8){
            s8 disp8 = (s8)address_offset;
            if(disp8 < 0){
                print(" - 0x%x]", -disp8);
            }else{
                print(" + 0x%x]", disp8);
            }
        }else if(mod == MOD_REGM_OFF32 || is_rip_relative){
            s32 disp32 = address_offset;
            if(disp32 < 0){
                print(" - 0x%x]", -disp32);
            }else{
                print(" + 0x%x]", disp32);
            }
        }else{
            print("]");
        }
    }
}

void print_imm(u32 imm_size, u64 immediate){
    
    if(imm_size == 1){
        s8 imm = (s8)immediate;
        if(imm < 0){
            print("-0x%x", -imm);
        }else{
            print("0x%x", imm);
        }
    }else if(imm_size == 2){
        s16 imm = (s16)immediate;
        if(imm < 0){
            print("-0x%x", -imm);
        }else{
            print("0x%x", imm);
        }
    }else if(imm_size == 4){
        s32 imm = (s32)immediate;
        if(imm < 0){
            print("-0x%x", -imm);
        }else{
            print("0x%x", imm);
        }
    }else if(imm_size == 8){
        s64 imm = (s64)immediate;
        if(imm < 0){
            print("-0x%llx", -imm);
        }else{
            print("0x%llx", imm);
        }
    }
}

u32 print_disassembly_for_buffer(struct context *context, u64 rip, u8 *instruction_buffer, u32 instruction_buffer_size){
    
    struct instruction_information info = decode_instruction(instruction_buffer);
    
    if(info.instruction_size > instruction_buffer_size){
        print("Could not read instruction at %p\n", rip);
        print("It starts with ");
        for(u32 index = 0; index < instruction_buffer_size; index++){
            print("%.2x ", instruction_buffer[index]);
        }
        print("");
        return instruction_buffer_size;
    }
    
    struct instruction_table_entry *instructions = normal_instructions;
    smm amount_of_instructions = array_count(normal_instructions);
    u16 *instruction_table = normal_instruction_table;
    
    if(info.vex){
        instructions = vex_instructions;
        amount_of_instructions = array_count(vex_instructions);
        instruction_table = vex_instruction_table;
    }
    
    try_again_because_there_might_have_been_an_unnecessary_rexw:;
    
    u16 instruction_index = instruction_table[info.augmented_opcode];
    
    int unhandled_instruction = 0;
    
    if(instruction_index == 0xffff){
        unhandled_instruction = 1;
    }else{
        for(; instruction_index < amount_of_instructions; instruction_index++){
            struct instruction_table_entry instruction = instructions[instruction_index];
            
            if((u32)instruction.extended_opcode != info.augmented_opcode){
                unhandled_instruction = 1;
                break;
            }
            
            //
            // In the table we *first* have the prefixed instructions, then the one without a prefix.
            //
            if(instruction.legacy_prefix_f2 && !(info.legacy_prefix_flags & MANDATORY_PREFIX_F2)) continue;
            if(instruction.legacy_prefix_f3 && !(info.legacy_prefix_flags & MANDATORY_PREFIX_F3)) continue;
            if(instruction.legacy_prefix_66 && !(info.legacy_prefix_flags & MANDATORY_PREFIX_66)) continue;
            
            if(instruction.rex_W != ((info.rex & REXW) != 0)) continue;
            
            if(instruction.regm_only && info.mod == MOD_REG) continue;
            if(instruction.vex_L != ((info.vex & VEXL) != 0)) continue; // @cleanup: evex needs 2 bits for vex_L.
            
            if(info.instruction_has_modrm){
                if(instruction.modrm_opcode != -1 && instruction.modrm_opcode != info.modrm) continue;
                if((instruction.reg_opcode < 8) && instruction.reg_opcode != (info.reg & 7)) continue;
            }
            
            //
            // We have found our instruction!
            // We will handle it below to reduce scoping!
            //
            break;
        }
    }
    
    if(unhandled_instruction){
        
        if(info.rex & REXW){ // @cleanup: we should maybe handle this in the table, maybe not...?
            info.rex &= ~REXW;
            goto try_again_because_there_might_have_been_an_unnecessary_rexw;
        }
        
        print("??? (");
        
        for(u32 index = 0; index < info.instruction_size; index++){
            print("%.2x ", instruction_buffer[index]);
        }
        print("= opcode 0x%x, vexL %d, prefixes", info.augmented_opcode, (info.vex & VEXL) != 0);
        
        if(info.legacy_prefix_flags == 0) print(" 0");
        if(info.legacy_prefix_flags & MANDATORY_PREFIX_F3) print(" 0xF3");
        if(info.legacy_prefix_flags & MANDATORY_PREFIX_F2) print(" 0xF2");
        if(info.legacy_prefix_flags & MANDATORY_PREFIX_66) print(" 0x66");
        if(info.legacy_prefix_flags & LEGACY_lock) print(" 0xF0");
        if(info.legacy_prefix_flags & LEGACY_cs_segment_override) print(" 0x2E");
        if(info.legacy_prefix_flags & LEGACY_ss_segment_override) print(" 0x36");
        if(info.legacy_prefix_flags & LEGACY_ds_segment_override) print(" 0x3E");
        if(info.legacy_prefix_flags & LEGACY_es_segment_override) print(" 0x26");
        if(info.legacy_prefix_flags & LEGACY_fs_segment_override) print(" 0x64");
        if(info.legacy_prefix_flags & LEGACY_gs_segment_override) print(" 0x65");
        if(info.legacy_prefix_flags & LEGACY_address_size_override) print(" 0x67");
        print(")");
        return info.instruction_size;
    }
    
    if(info.legacy_prefix_flags & LEGACY_lock) print("lock ");
    
    struct instruction_table_entry instruction = instructions[instruction_index];
    
    print("%.*s ", instruction.mnemonic.size, instruction.mnemonic.data);
    
    for(u32 operand_index = 0; operand_index < instruction.amount_of_operands; operand_index++){
        enum operand_kind kind = instruction.operands[operand_index].kind;
        
        switch(kind){
            
            case OPERAND_imm8:  print_imm(1, info.immediate); break;
            case OPERAND_imm16: print_imm(2, info.immediate); break;
            case OPERAND_imm32: print_imm(4, info.immediate); break;
            case OPERAND_imm64: print_imm(8, info.immediate); break;
            
            case OPERAND_rel8:  context ? print_symbol(context, rip + info.instruction_size +  (s8)info.immediate) : (void)print("%+d", (s8)info.immediate); break;
            case OPERAND_rel16: context ? print_symbol(context, rip + info.instruction_size + (s16)info.immediate) : (void)print("%+d", (s16)info.immediate); break;
            case OPERAND_rel32: context ? print_symbol(context, rip + info.instruction_size + (s32)info.immediate) : (void)print("%+d", (s32)info.immediate); break;
            
            // @cleanup: I have no idea about far jumps.
            case OPERAND_1: print("1"); break;
            case OPERAND_al: print("al"); break;
            case OPERAND_cl: print("cl"); break;
            case OPERAND_ax: print("ax"); break;
            case OPERAND_dx: print("dx"); break;
            case OPERAND_eax: print("eax"); break;
            case OPERAND_edx: print("edx"); break;
            case OPERAND_rax: print("rax"); break;
            case OPERAND_xmm0: print("xmm0"); break;
            
            case OPERAND_reg8:  print_reg(info.reg, 1); break;
            case OPERAND_reg16: print_reg(info.reg, 2); break;
            case OPERAND_reg32: print_reg(info.reg, 4); break;
            case OPERAND_reg64: print_reg(info.reg, 8); break;
            
            case OPERAND_vex_reg32: print_reg(info.vex_reg, 4); break;
            case OPERAND_vex_reg64: print_reg(info.vex_reg, 8); break;
            case OPERAND_vex_xmm:   print_reg(info.vex_reg, 16); break;
            case OPERAND_vex_ymm:   print_reg(info.vex_reg, 32); break;
            case OPERAND_vex_zmm:   print_reg(info.vex_reg, 64); break;
            
            case OPERAND_opcode8:  print_reg((info.augmented_opcode & 7) | ((info.rex & REXB) ? 8 : 0), 1); break;
            case OPERAND_opcode16: print_reg((info.augmented_opcode & 7) | ((info.rex & REXB) ? 8 : 0), 2); break;
            case OPERAND_opcode32: print_reg((info.augmented_opcode & 7) | ((info.rex & REXB) ? 8 : 0), 4); break;
            case OPERAND_opcode64: print_reg((info.augmented_opcode & 7) | ((info.rex & REXB) ? 8 : 0), 8); break;
            
            // @cleanup: @hack: The 'vex_reg' vs 'reg' should also come from the table.
            case OPERAND_xmm: print_reg(info.reg, 16); break;
            case OPERAND_ymm: print_reg(info.reg, 32); break;
            case OPERAND_zmm: print_reg(info.reg, 64); break;
            
            case OPERAND_mem:{
                // @note: unsized memory operand.
                print_modrm(-1, info.have_sib, info.regm, info.index_reg, info.mod, info.legacy_prefix_flags, info.address_offset, info.scale, info.is_rip_relative);
            }break;
            
            case OPERAND_m8:
            case OPERAND_regm8:{
                print_modrm(1, info.have_sib, info.regm, info.index_reg, info.mod, info.legacy_prefix_flags, info.address_offset, info.scale, info.is_rip_relative);
            }break;
            
            case OPERAND_m16:
            case OPERAND_regm16:{
                print_modrm(2, info.have_sib, info.regm, info.index_reg, info.mod, info.legacy_prefix_flags, info.address_offset, info.scale, info.is_rip_relative);
            }break;
            
            case OPERAND_m32:
            case OPERAND_regm32:{
                print_modrm(4, info.have_sib, info.regm, info.index_reg, info.mod, info.legacy_prefix_flags, info.address_offset, info.scale, info.is_rip_relative);
            }break;
            
            case OPERAND_m64:
            case OPERAND_regm64:{
                print_modrm(8, info.have_sib, info.regm, info.index_reg, info.mod, info.legacy_prefix_flags, info.address_offset, info.scale, info.is_rip_relative);
            }break;
            
            case OPERAND_regm8_zero_extended:{
                if(info.mod == MOD_REG){
                    print_reg(info.regm, 8);
                }else{
                    print_modrm(1, info.have_sib, info.regm, info.index_reg, info.mod, info.legacy_prefix_flags, info.address_offset, info.scale, info.is_rip_relative);
                }
            }break;
            case OPERAND_regm16_zero_extended:{
                if(info.mod == MOD_REG){
                    print_reg(info.regm, 8);
                }else{
                    print_modrm(2, info.have_sib, info.regm, info.index_reg, info.mod, info.legacy_prefix_flags, info.address_offset, info.scale, info.is_rip_relative);
                }
            }break;
            
            case OPERAND_moffs8:
            case OPERAND_moffs16:
            case OPERAND_moffs32:
            case OPERAND_moffs64:{
                print("[0x%llx]", info.immediate);
            }break;
            
            case OPERAND_segment_register:{
                switch(info.reg){
                    case 0: print("es"); break;
                    case 1: print("cs"); break;
                    case 2: print("ss"); break;
                    case 3: print("ds"); break;
                    case 4: print("fs"); break;
                    case 5: print("gs"); break;
                    default: print("???"); break;
                }
            }break;
            
            case OPERAND_cr: print("cr%d", info.reg); break;
            case OPERAND_dr: print("dr%d", info.reg); break;
            
            case OPERAND_ds: print("ds"); break;
            case OPERAND_ss: print("ss"); break;
            case OPERAND_cs: print("cs"); break;
            case OPERAND_es: print("es"); break;
            case OPERAND_fs: print("fs"); break;
            case OPERAND_gs: print("gs"); break;
            
            case OPERAND_m128:
            case OPERAND_m256:
            case OPERAND_m512:
            case OPERAND_xmmm8:
            case OPERAND_xmmm16:
            case OPERAND_xmmm32:
            case OPERAND_xmmm64:
            case OPERAND_xmmm128:
            case OPERAND_ymmm256:
            case OPERAND_zmmm512:{
                int size = 1;
                
                switch((int)kind){
                    case OPERAND_xmmm8:   size = 1; break;
                    case OPERAND_xmmm16:  size = 2; break;
                    case OPERAND_xmmm32:  size = 4; break;
                    case OPERAND_xmmm64:  size = 8; break;
                    case OPERAND_xmmm128: size = 16; break;
                    case OPERAND_ymmm256: size = 32; break;
                    case OPERAND_zmmm512: size = 64; break;
                }
                if(info.mod == MOD_REG){
                    size = (size < 16) ? 16 : size;
                    print_reg(info.regm, size);
                }else{
                    print_modrm(size, info.have_sib, info.regm, info.index_reg, info.mod, info.legacy_prefix_flags, info.address_offset, info.scale, info.is_rip_relative);
                }
            }break;
            
            case OPERAND_ST0: print("ST(0)"); break;
            case OPERAND_STi: print("ST(%u)", (info.regm & 7)); break;
            
            default:{
                print("UNIMPLEMENTED_OPERAND_KIND_%d", kind);
            }break;
        }
        
        if(operand_index + 1 < instruction.amount_of_operands) print(", ");
    }
    
    return info.instruction_size;
}

u32 print_disassembly(struct context *context, u64 rip, int *crash){
    
    u8 instruction_buffer[16] = {0};
    u32 instruction_buffer_size = prefetch_instruction(context, rip, instruction_buffer, sizeof(instruction_buffer));
    if(instruction_buffer_size == 0){
        print("Could not read memory at %p", rip);
        if(crash) *crash = 1;
        return 0;
    }
    
    u32 instruction_size = print_disassembly_for_buffer(context, rip, instruction_buffer, instruction_buffer_size);
    if(instruction_size > instruction_buffer_size){
        print("Could not read memory at %p", rip + instruction_buffer_size);
        if(crash) *crash = 1;
        return 0;
    }
    
    return instruction_size;
}

void print_crash_information(struct context *context, struct crash_information *info){
    
    struct registers *registers = &context->registers;
    
    print("Crash %s at %p accessing %p\n", crash_type_string[info->crash_type], registers->rip, info->crash_address);
    
    if(info->crash_type == CRASH_internal_error && info->crash_address != 0){
        print("Internal Error Message: '%s'\n", (char *)info->crash_address);
    }
    
    if(info->crash_type == CRASH_bugcheck){
        print("Bugcheck: 0x%x %p %p %p\n", (u32)registers->rcx, registers->rdx, registers->r8, registers->r9);
    }
    
    if(info->crash_type == CRASH_unhandled_exception){
        // @incomplete: 
        // print("Bugcheck: 0x%x %p %p %p\n", (u32)registers->rcx, registers->rdx, registers->r8, registers->r9);
    }
    
    if(info->crash_type == CRASH_unimplemented_instruction && info->crash_address != 0){
        u64 rip = info->crash_address;
        
        u8 instruction_buffer[16] = {0};
        u32 instruction_buffer_size = prefetch_instruction(context, rip, instruction_buffer, sizeof(instruction_buffer));
        
        print("\n");
        u32 instruction_size = print_disassembly_for_buffer(context, rip, instruction_buffer, instruction_buffer_size);
        print("\n");
        
        print("raw instruction: ");
        for(u32 index = 0; index < instruction_size; index++){
            print("%.2x ", instruction_buffer[index]);
        }
        print("\n");
    }
    
    print_registers(context, stdout);
    
    print("\n\nStack Trace:\n");
    print_stack_trace(context);
}


void print_result_status(struct context *context, char *format, ...){
    
    char prefix[0x100];
    
    va_list va;
    va_start(va, format);
    vsnprintf(prefix, sizeof(prefix), format, va);
    va_end(va);
    
    struct crash_information *info = &context->crash_information;
    struct registers *registers = &context->registers;
    
    char *crash_type = (info->crash_type < array_count(crash_type_string)) ? crash_type_string[info->crash_type]  : "????";
    print("[%s] %s at %p status 0x%x\n", prefix, crash_type, info->crash_address, (int)registers->rax);
    if(info->crash_type == CRASH_internal_error && info->crash_address != 0){
        print("    internal error string: %s\n", (char *)info->crash_address);
    }
}

//_____________________________________________________________________________________________________________________
// Miscellaneous information routines

char *get_image_name(struct context *context, char image_name[16], u64 *pid){
    
    //
    // Get and restore the 'crash_information' so we can call this without causing a _crash_.
    //
    struct crash_information crash_information = enter_debugging_routine(context);
    
    u64 kpcr = (context->registers.cs.selector & 3) ? context->registers.gs_swap : context->registers.gs_base;
    u64 cr3 = patch_in_kernel_cr3(context);
    
    u64 thread  = guest_read(u64, kpcr   + get_member_offset(context, string("nt!_KPCR.Prcb.CurrentThread")));
    u64 process = guest_read(u64, thread + get_member_offset(context, string("nt!_KTHREAD.ApcState.Process")));
    
    guest_read_size(context, image_name, process + get_member_offset(context, string("nt!_EPROCESS.ImageFileName")), 16, PERMISSION_none);
    
    if(pid) guest_read_size(context, pid, process + get_member_offset(context, string("nt!_EPROCESS.UniqueProcessId")), 8, PERMISSION_none);
    
    context->registers.cr3 = cr3;
    
    exit_debugging_routine(context, crash_information);
    
    return image_name;
}

void if_we_have_any_information_about_the_current_rip_print_what_we_know(struct context *context, struct registers *registers){
    
    if(registers->rip == get_symbol(context, string("nt!NtDeviceIoControlFile")) || registers->rip == get_symbol(context, string("nt!NtFsControlFile"))){
        u64 FileHandle = registers->rcx;
        u64 Event      = registers->rdx;
        u64 ApcRoutine = registers->r8;
        u64 ApcContext = registers->r9;
        
        u64 IoStatusBlock = guest_read(u64, registers->rsp + 0x28);
        
        u32 Ioctl = guest_read(u32, registers->rsp + 0x30);
        
        u64 InputBuffer       = guest_read(u64, registers->rsp + 0x38);
        u32 InputBufferLength = guest_read(u32, registers->rsp + 0x40);
        
        u64 OutputBuffer       = guest_read(u64, registers->rsp + 0x48);
        u32 OutputBufferLength = guest_read(u32, registers->rsp + 0x50);
        
        print_symbol(context, registers->rip); print(":\n");
        print("    FileHandle:    %p\n", FileHandle);
        print("    Event:         %p\n", Event);
        print("    ApcRoutine:    %p\n", ApcRoutine);
        print("    ApcContext:    %p\n", ApcContext);
        print("    IoStatusBlock: %p\n", IoStatusBlock);
        print("\n");
        print("    Ioctl: 0x%x\n", Ioctl);
        print("    InputBufferSize: 0x%x\n", InputBufferLength);
        
        {
            u8 *data = malloc(InputBufferLength);
            if(data){
                int success = guest_read_size(context, data, InputBuffer, InputBufferLength, PERMISSION_none);
                if(!success){
                    print("Failed to read input buffer.\n");
                }else{
                    print_byte_range(data, InputBufferLength, InputBuffer);
                }
                
                free(data);
            }else{
                print("Failed to allocate memory for input buffer.\n");
            }
        }
        
        print("\n");
        print("    OutputBufferSize: 0x%x\n", OutputBufferLength);
        
        u8 *data = malloc(OutputBufferLength);
        if(data){
            int success = guest_read_size(context, data, OutputBuffer, OutputBufferLength, PERMISSION_none);
            if(!success){
                print("Failed to read output buffer.\n");
            }else{
                print_byte_range(data, OutputBufferLength, OutputBuffer);
            }
            
            free(data);
        }else{
            print("Failed to allocate memory for output buffer.\n");
        }
    }else if(registers->rip == get_symbol(context, string("nt!NtCreateFile"))){
        u32 DesiredAccess     = (u32)registers->rdx;
        u64 ObjectAttributes  = registers->r8;
        u64 AllocationSize    = guest_read(u64, registers->rsp + 0x28);
        u32 FileAttributes    = guest_read(u32, registers->rsp + 0x30);
        u32 ShareAccess       = guest_read(u32, registers->rsp + 0x38);
        u32 CreateDisposition = guest_read(u32, registers->rsp + 0x40);
        u32 CreateOptions     = guest_read(u32, registers->rsp + 0x48);
        u64 EaBuffer          = guest_read(u64, registers->rsp + 0x50);
        u32 EaLength          = guest_read(u32, registers->rsp + 0x58);
        
        print_symbol(context, registers->rip); print("\n");
        print("    DesiredAccess 0x%x\n", DesiredAccess);
        print("    ObjectAttributes %p {\n", ObjectAttributes);
        if(ObjectAttributes){
            print("        RootDirectory            %p\n", guest_read(u64, ObjectAttributes + 0x8));
            u64 ObjectName = guest_read(u64, ObjectAttributes + 0x10);
            print("        ObjectName               %p {\n", ObjectName);
            if(ObjectName){
                struct unicode_string Name = {0};
                guest_read_size(context, &Name, ObjectName, sizeof(Name), PERMISSION_none);
                u8 *data = push_data(&context->scratch_arena, u8, Name.length + 3); // @note: length is at most 65536, + 3 so it is zero terminated in any case
                guest_read_size(context, data, Name.buffer, Name.length, PERMISSION_none);
                
                print("           length         0n%u\n", Name.length);
                print("           maximum length 0n%u\n", Name.maximum_length);
                print("           buffer           %p (%ws)\n", Name.buffer, data);
            }
            print("        }\n");
            
            print("        Attributes             0x%x\n", guest_read(u32, ObjectAttributes + 0x18));
            print("        SecurityDescriptor       %p\n", guest_read(u64, ObjectAttributes + 0x20));
            print("        SecurityQualityOfService %p\n", guest_read(u64, ObjectAttributes + 0x28));
        }
        print("     }\n");
        print("    AllocationSize    %p\n", AllocationSize);
        print("    FileAttributes    0x%x\n", FileAttributes);
        print("    ShareAccess       0x%x\n", ShareAccess);
        print("    CreateDisposition 0x%x\n", CreateDisposition);
        print("    CreateOptions     0x%x\n", CreateOptions);
        print("    EaBuffer          %p\n", EaBuffer);
        print("    EaLength          0x%x\n", EaLength);
        
        if(EaBuffer && EaLength){
            u8 *data = push_data(&context->scratch_arena, u8, EaLength); // @note: length is at most 65536, + 3 so it is zero terminated in any case
            guest_read_size(context, data, EaBuffer, EaLength, PERMISSION_none);
            
            print_byte_range(data, EaLength, EaBuffer);
        }
        
    }else if(registers->rip == get_symbol(context, string("nt!KiPageFault"))){
        print("Pagefault:\n");
        print("    Address: %p\n", registers->cr2);
        u64 error_code = guest_read(u64, registers->rsp);
        print("    Error Code: 0x%llx =", error_code);
        if(error_code & (1 << 0)) print(" Present (1)");
        if(error_code & (1 << 1)) print(" Write (2)");
        if(error_code & (1 << 2)) print(" User (4)");
        if(error_code & (1 << 4)) print(" Fetch (0x10)");
        print("\n");
        u64 return_rip = guest_read(u64, registers->rsp + 1 * 8);
        print("    Return rip %p (", return_rip); print_symbol(context, return_rip); print(")\n");
        print("    Return cs 0x%x\n", guest_read(u32, registers->rsp + 2 * 8));
        u64 rflags = guest_read(u64, registers->rsp + 3 * 8);
        print("    Rflags %x", rflags); print_flags(rflags, stdout); print("\n");
        print("    Return rsp %p\n", guest_read(u64, registers->rsp + 4 * 8));
        print("    Return ss 0x%x\n", guest_read(u32, registers->rsp + 5 * 8));
    }else{
        print_symbol(context, registers->rip); print("\n");
        print("    No information.\n");
    }
}

void print_bit_meaning_for_register(u64 value, char *flags[], u64 amount_of_flags){
    
    if(!value){
        print("\n");
        return;
    }
    
    print("( ");
    for(u32 index = 0; index < 32; index++){
        if(value & (1ull << index)){
            if(index < amount_of_flags){
                print("%s ", flags[index]);
            }else{
                print("?(bit %d) ", index);
            }
        }
    }
    print(")\n");
}

void print_mdl(struct context *context, struct loaded_module *nt, u64 MdlAddress){
    (void)nt;
    
    struct{
        u64 Next;
        u16 Size;
        u16 MdlFlags;
        u16 AllocationProcessorNumber;
        u16 Reserved;
        u64 Process;
        u64 MappedSystemVa;
        u64 StartVa;
        u32 ByteCount;
        u32 ByteOffset;
    } MDL;
    
    int success = guest_read_size(context, &MDL, MdlAddress, sizeof(MDL), PERMISSION_read);
    if(!success){
        print("Could not read Mdl at %p.\n", MdlAddress);
        return;
    }
    
    static char *mdl_flags[] = {
        "MDL_MAPPED_TO_SYSTEM_VA",
        "MDL_PAGES_LOCKED",
        "MDL_SOURCE_IS_NONPAGED_POOL",
        "MDL_ALLOCATED_FIXED_SIZE",
        "MDL_PARTIAL",
        "MDL_PARTIAL_HAS_BEEN_MAPPED",
        "MDL_IO_PAGE_READ",
        "MDL_WRITE_OPERATION",
        "MDL_LOCKED_PAGE_TABLES",
        "MDL_FREE_EXTRA_PTES",
        "MDL_DESCRIBES_AWE",
        "MDL_IO_SPACE",
        "MDL_NETWORK_HEADER",
        "MDL_MAPPING_CAN_FAIL",
        "MDL_PAGE_CONTENTS_INVARIANT",
        "MDL_INTERNAL",
    };
    
    print("MDL at %p:\n", MdlAddress);
    print("    Flags 0x%x ", MDL.MdlFlags); print_bit_meaning_for_register(MDL.MdlFlags, mdl_flags, array_count(mdl_flags));
    print("    Process %p\n", MDL.Process);
    print("    MappedSystemVa %p\n", MDL.MappedSystemVa);
    print("    StartVa %p\n", MDL.StartVa);
    print("    ByteCount %p\n", MDL.ByteCount);
    print("    ByteOffset %p\n", MDL.ByteOffset);
    
    u64 PageCount = (MDL.ByteOffset + MDL.ByteCount + 0x1000-1) / 0x1000;
    print("PageCount = 0x%x\n", PageCount);
    for(u64 index = 0; index < PageCount; index++){
        u64 page = guest_read(u64, MdlAddress + sizeof(MDL) + index * 8);
        print("   [%d] %p\n", index, page);
    }
}

void print_irp(struct context *context, struct loaded_module *nt, u64 IrpAddress){
    
    int error = 0; // @cleanup: Currently Ignored.
    
    // u64 MdlAddress   = guest_read(u64, IrpAddress + pdb_get_member_offset(nt->pdb_context, string("_IRP"), string("MdlAddress"), &error));
    u64 SystemBuffer = guest_read(u64, IrpAddress + pdb_get_member_offset(nt->pdb_context, string("_IRP"), string("AssociatedIrp.SystemBuffer"), &error));
    u64 CurrentStackLocation = guest_read(u64, IrpAddress + pdb_get_member_offset(nt->pdb_context, string("_IRP"), string("Tail.Overlay.CurrentStackLocation"), &error));
    
    print("CurrentStackLocation %p\n", CurrentStackLocation);
    
    u8 MajorFunction = guest_read(u8, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("MajorFunction"), &error));
    u8 MinorFunction = guest_read(u8, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("MinorFunction"), &error));
    
    char *MajorFunctionString = "???";
    
    static char *MajorFunctionsEnums[] = {
        "IRP_MJ_CREATE",
        "IRP_MJ_CREATE_NAMED_PIPE",
        "IRP_MJ_CLOSE",
        "IRP_MJ_READ",
        "IRP_MJ_WRITE",
        "IRP_MJ_QUERY_INFORMATION",
        "IRP_MJ_SET_INFORMATION",
        "IRP_MJ_QUERY_EA",
        "IRP_MJ_SET_EA",
        "IRP_MJ_FLUSH_BUFFERS",
        "IRP_MJ_QUERY_VOLUME_INFORMATION",
        "IRP_MJ_SET_VOLUME_INFORMATION",
        "IRP_MJ_DIRECTORY_CONTROL",
        "IRP_MJ_FILE_SYSTEM_CONTROL",
        "IRP_MJ_DEVICE_CONTROL",
        "IRP_MJ_INTERNAL_DEVICE_CONTROL",
        "IRP_MJ_SHUTDOWN",
        "IRP_MJ_LOCK_CONTROL",
        "IRP_MJ_CLEANUP",
        "IRP_MJ_CREATE_MAILSLOT",
        "IRP_MJ_QUERY_SECURITY",
        "IRP_MJ_SET_SECURITY",
        "IRP_MJ_POWER",
        "IRP_MJ_SYSTEM_CONTROL",
        "IRP_MJ_DEVICE_CHANGE",
        "IRP_MJ_QUERY_QUOTA",
        "IRP_MJ_SET_QUOTA",
        "IRP_MJ_PNP",
    };
    
    if(MajorFunction < array_count(MajorFunctionsEnums)){
        MajorFunctionString = MajorFunctionsEnums[MajorFunction];
    }
    
    print("MajorFunction = 0x%x (%s)\n", MajorFunction, MajorFunctionString);
    
    if(MajorFunction == /*IRP_MJ_POWER*/0x16){
        
        char *PowerMinorFunctionString = "???";
        
        static char *PowerMinorFunctions[] = {
            [0x00] = "IRP_MN_WAIT_WAKE",
            [0x01] = "IRP_MN_POWER_SEQUENCE",
            [0x02] = "IRP_MN_SET_POWER",
            [0x03] = "IRP_MN_QUERY_POWER",
        };
        
        if(MinorFunction < array_count(PowerMinorFunctions)){
            PowerMinorFunctionString = PowerMinorFunctions[MinorFunction];
        }
        
        print("MinorFunction = 0x%x (%s)\n", MinorFunction, PowerMinorFunctionString);
        
    }else if(MajorFunction == /*IRP_MJ_PNP*/0x1b){
        
        char *PnpMinorFunctionString = "???";
        
        static char *PnpMinorFunctions[] = {
            [0x00] = "IRP_MN_START_DEVICE",
            [0x01] = "IRP_MN_QUERY_REMOVE_DEVICE",
            [0x02] = "IRP_MN_REMOVE_DEVICE",
            [0x03] = "IRP_MN_CANCEL_REMOVE_DEVICE",
            [0x04] = "IRP_MN_STOP_DEVICE",
            [0x05] = "IRP_MN_QUERY_STOP_DEVICE",
            [0x06] = "IRP_MN_CANCEL_STOP_DEVICE",
            [0x07] = "IRP_MN_QUERY_DEVICE_RELATIONS",
            [0x08] = "IRP_MN_QUERY_INTERFACE",
            [0x09] = "IRP_MN_QUERY_CAPABILITIES",
            [0x0A] = "IRP_MN_QUERY_RESOURCES",
            [0x0B] = "IRP_MN_QUERY_RESOURCE_REQUIREMENTS",
            [0x0C] = "IRP_MN_QUERY_DEVICE_TEXT",
            [0x0D] = "IRP_MN_FILTER_RESOURCE_REQUIREMENTS",
            [0x0F] = "IRP_MN_READ_CONFIG",
            [0x10] = "IRP_MN_WRITE_CONFIG",
            [0x11] = "IRP_MN_EJECT",
            [0x12] = "IRP_MN_SET_LOCK",
            [0x13] = "IRP_MN_QUERY_ID",
            [0x14] = "IRP_MN_QUERY_PNP_DEVICE_STATE",
            [0x15] = "IRP_MN_QUERY_BUS_INFORMATION",
            [0x16] = "IRP_MN_DEVICE_USAGE_NOTIFICATION",
            [0x17] = "IRP_MN_SURPRISE_REMOVAL",
            [0x18] = "???",
            [0x19] = "IRP_MN_DEVICE_ENUMERATED",
        };
        
        if(MinorFunction < array_count(PnpMinorFunctions)){
            PnpMinorFunctionString = PnpMinorFunctions[MinorFunction];
        }
        
        print("MinorFunction = 0x%x (%s)\n", MinorFunction, PnpMinorFunctionString);
    }else{
        if(MinorFunction) print("MinorFunction = 0x%x\n", MinorFunction);
    }
    
    {
#if 0
        if(Flags){
            print("Flags: 0x%x", Flags);
            if(Flags & 0x01) print(" SL_KEY_SPECIFIED");
            if(Flags & 0x02) print(" SL_OVERRIDE_VERIFY_VOLUME");
            if(Flags & 0x04) print(" SL_WRITE_THROUGH");
            if(Flags & 0x08) print(" SL_FT_SEQUENTIAL_WRITE");
            if(Flags & 0x10) print(" SL_FORCE_DIRECT_WRITE");
            if(Flags & 0x20) print(" SL_REALTIME_STREAM");
            print("\n");
        }
#endif
        
        u8 Control = guest_read(u8, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Control"), &error));
        if(Control){
            print("Control: 0x%x", Control);
            if(Control & 0x01) print(" SL_PENDING_RETURN");
            print("\n");
        }
    }
    
    switch(MajorFunction){
        case /*IRP_MJ_CREATE*/0:{
            u8 IrpSpFlags = guest_read(u8, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Flags"),   &error));
            
            static char *IrpSpFlagStrings[] = {
                [0] = "SL_FORCE_ACCESS_CHECK",
                [1] = "SL_OPEN_PAGING_FILE",
                [2] = "SL_OPEN_TARGET_DIRECTORY",
                [3] = "SL_STOP_ON_SYMLINK",
                [6] = "SL_IGNORE_READONLY_ATTRIBUTE",
                [7] = "SL_CASE_SENSITIVE",
            };
            
            print("    IrpSp->Flags = 0x%x ", IrpSpFlags); print_bit_meaning_for_register(IrpSpFlags, IrpSpFlagStrings, array_count(IrpSpFlagStrings));
            
            print("    SecurityContext: %16p\n", guest_read(u64, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Parameters.Create.SecurityContext"), &error)));
            print("    Options:         %16x\n", guest_read(u32, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Parameters.Create.Options"),         &error)));
            print("    FileAttributes:  %16x\n", guest_read(u16, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Parameters.Create.FileAttributes"),  &error)));
            print("    ShareAccess:     %16x\n", guest_read(u16, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Parameters.Create.ShareAccess"),     &error)));
            
            u32 EaLength = guest_read(u32, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Parameters.Create.EaLength"),        &error));
            print("    EaLength:        %16x\n", EaLength);
            
            for(u32 Offset = 0; Offset < EaLength;){
                u32 NextEntryOffset = guest_read(u32, SystemBuffer + Offset + 0);
                // u8  Flags           = guest_read(u8,  SystemBuffer + Offset + 4);
                u8  EaNameLength    = guest_read(u8,  SystemBuffer + Offset + 5);
                u16 EaValueLength   = guest_read(u16, SystemBuffer + Offset + 6);
                
                u32 EaNameOffset  = Offset + 8;
                u32 EaValueOffset = EaNameOffset + EaNameLength + 1;
                u32 ComputedNextEntryOffset = EaValueOffset + EaValueLength;
                
                u8 *string = push_data(&context->scratch_arena, u8, EaNameLength);
                u8 *memory = push_data(&context->scratch_arena, u8, EaValueLength);
                
                guest_read_size(context, string, SystemBuffer + EaNameOffset,  EaNameLength,  PERMISSION_read);
                guest_read_size(context, memory, SystemBuffer + EaValueOffset, EaValueLength, PERMISSION_read);
                
                print("\nEaName = %.*s\n", EaNameLength, string);
                print_byte_range(memory, EaValueLength, EaValueOffset);
                
                if(NextEntryOffset == 0) break;
                
                if(ComputedNextEntryOffset != NextEntryOffset){
                    print("NextEntryOffset (0x%x) != ComputedNextEntryOffset (0x%x)\n", NextEntryOffset, ComputedNextEntryOffset);
                    break;
                }
                
                Offset = ComputedNextEntryOffset;
            }
            
        }break;
        case /*IRP_MJ_CREATE_NAMED_PIPE*/1:{
            
        }break;
        case /*IRP_MJ_CLOSE*/2:{
            
        }break;
        case /*IRP_MJ_READ*/3:{
            
            // DeviceObject DO_BUFFERED_IO or DO_DIRECT_IO
            
            u32 Length     = guest_read(u32, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Parameters.Read.Length"), &error));
            u32 Key        = guest_read(u32, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Parameters.Read.Key"), &error));
            u32 Flags      = guest_read(u32, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Parameters.Read.Flags"), &error));
            u64 ByteOffset = guest_read(u64, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Parameters.Read.ByteOffset"), &error));
            
            print("Length 0x%x\n", Length);
            print("Key    0x%x\n", Key);
            print("Flags  0x%x\n", Flags);
            print("ByteOffset 0x%llx\n", ByteOffset);
        }break;
        case /*IRP_MJ_WRITE*/4:{
            u32 Length     = guest_read(u32, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Parameters.Write.Length"), &error));
            u32 Key        = guest_read(u32, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Parameters.Write.Key"), &error));
            u32 Flags      = guest_read(u32, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Parameters.Write.Flags"), &error));
            u64 ByteOffset = guest_read(u64, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Parameters.Write.ByteOffset"), &error));
            
            print("Length 0x%x\n", Length);
            print("Key    0x%x\n", Key);
            print("Flags  0x%x\n", Flags);
            print("ByteOffset 0x%llx\n", ByteOffset);
        }break;
        case /*IRP_MJ_QUERY_INFORMATION*/5:{
            
        }break;
        case /*IRP_MJ_SET_INFORMATION*/6:{
            
        }break;
        case /*IRP_MJ_QUERY_EA*/7:{
            
        }break;
        case /*IRP_MJ_SET_EA*/8:{
            
        }break;
        case /*IRP_MJ_FLUSH_BUFFERS*/9:{
            
        }break;
        case /*IRP_MJ_QUERY_VOLUME_INFORMATION*/0xa:{
            
            
        }break;
        case /*IRP_MJ_SET_VOLUME_INFORMATION*/0xb:{
            
        }break;
        case /*IRP_MJ_DIRECTORY_CONTROL*/0xc:{
            
        }break;
        case /*IRP_MJ_FILE_SYSTEM_CONTROL*/0xd:{
            
        }break;
        case /*IRP_MJ_INTERNAL_DEVICE_CONTROL*/0xf:
        case /*IRP_MJ_DEVICE_CONTROL*/0xe:{
            u32 OutputBufferLength = guest_read(u32, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Parameters.DeviceIoControl.OutputBufferLength"), &error));
            u32 InputBufferLength  = guest_read(u32, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Parameters.DeviceIoControl.InputBufferLength"),  &error));
            u32 IoControlCode      = guest_read(u32, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Parameters.DeviceIoControl.IoControlCode"),      &error));
            u64 Type3InputBuffer   = guest_read(u64, CurrentStackLocation + pdb_get_member_offset(nt->pdb_context, string("_IO_STACK_LOCATION"), string("Parameters.DeviceIoControl.Type3InputBuffer"),   &error));
            
            // @cleanup: Print the parts of the Ioctl.
            print("IoControlCode 0x%x\n", IoControlCode);
            
            u8 *memory = push_data(&context->scratch_arena, u8, InputBufferLength);
            
            if((IoControlCode & 3) == /*METHOD_BUFFERED*/0){
                // Both Input and Output Buffer are SystemBuffer.
                
                print("OutputBufferLength 0x%x\n", OutputBufferLength);
                print("InputBufferLength 0x%x\n", InputBufferLength);
                guest_read_size(context, memory, SystemBuffer, InputBufferLength, PERMISSION_read);
            }else if((IoControlCode & 3) == /*METHOD_NEITER*/3){
                // InputBuffer  = Type3InputBuffer, OutputBuffer = Irp->UserBuffer
                print("OutputBuffer %p OutputBufferSize 0x%x\n", guest_read(u64, IrpAddress + pdb_get_member_offset(nt->pdb_context, string("_IRP"), string("UserBuffer"), &error)), OutputBufferLength);
                guest_read_size(context, memory, Type3InputBuffer, InputBufferLength, PERMISSION_read);
            }else{
                print("@cleanup: In-direct / Out-direct.\n");
            }
            
            print_byte_range(memory, InputBufferLength, 0);
        }break;
        case /*IRP_MJ_SHUTDOWN*/0x10:{
            
        }break;
        case /*IRP_MJ_LOCK_CONTROL*/0x11:{
            
        }break;
        case /*IRP_MJ_CLEANUP*/0x12:{
            
        }break;
        case /*IRP_MJ_CREATE_MAILSLOT*/0x13:{
            
        }break;
        case /*IRP_MJ_QUERY_SECURITY*/0x14:{
            
        }break;
        case /*IRP_MJ_SET_SECURITY*/0x15:{
            
        }break;
        case /*IRP_MJ_POWER*/0x16:{
            
        }break;
        case /*IRP_MJ_SYSTEM_CONTROL*/0x17:{
            
        }break;
        case /*IRP_MJ_DEVICE_CHANGE*/0x18:{
            
        }break;
        case /*IRP_MJ_QUERY_QUOTA*/0x19:{
            
        }break;
        case /*IRP_MJ_SET_QUOTA*/0x1a:{
            
        }break;
        case /*IRP_MJ_PNP*/0x1b:{
            
        }break;
        default:{
            print("Unknown MajorFunction\n");
        }break;
    }
}

void KiKernelSysretExit_brocess_hook(struct context *context, struct registers *registers){
    
    // Ensure we can 'g' from this breakpoint.
    if(context->jit_skip_one_breakpoint){
        context->jit_skip_one_breakpoint = 0;
        return;
    }
    
    char image_name_buffer[16] = {0};
    u64 pid = 0;
    char *image_name = get_image_name(context, image_name_buffer, &pid);
    
    if(strncmp(image_name, globals.KiKernelSysretExit_process_name, 16) == 0){
        set_crash_information(context, CRASH_enter_debugger, registers->rip);
        context->jit_skip_one_breakpoint = 1;
    }
}


void handle_debugger(struct context *context){
    
    struct registers *registers = &context->registers;
    
    //
    // We save the crash information right here and restore it upon return.
    //
    struct crash_information original_crash_information = enter_debugging_routine(context);
    
    assert(!globals.in_debugger); // Make sure we don't call this recursively.
    
    globals.in_debugger = true;
    
    if(context->use_hypervisor){
        for(u32 bit_index = 0; bit_index < 4; bit_index++){
            if(registers->dr6 & (1ull << bit_index)){
                globals.breakpoint_hit_index = bit_index;
            }
        }
        
        enum breakpoint_type type = globals.breakpoints[globals.breakpoint_hit_index].type;
        
        if(globals.breakpoint_hit_index >= 0){
            if(globals.breakpoints[globals.breakpoint_hit_index].flags & BREAKPOINT_FLAG_oneshot){
                // Don't print anything for oneshot breakpoints, as it get annoying,
                // when single stepping.
            }else{
                print("\n%s breakpoint %x hit!\n", breakpoint_type_to_string[type], globals.breakpoint_hit_index);
            }
        }
    }else{
        // 
        // We call 'check_breakpoint' here to set 'globals.breakpoint_hit_index'.
        // 
        check_breakpoint(BREAKPOINT_execute, context->registers.rip, 1);
        
        //
        // WARNING: In the loop below don't return as in the very end we reset 'globals.breakpoint_hit_index'.
        //
        if(globals.breakpoint_hit_index >= 0){
            assert(globals.breakpoint_hit_index < array_count(globals.breakpoints));
            
            enum breakpoint_type type = globals.breakpoints[globals.breakpoint_hit_index].type;
            
            if(globals.breakpoints[globals.breakpoint_hit_index].flags & BREAKPOINT_FLAG_oneshot){
                //
                // On a one-shot breakpoint (usually used with 'n' or 'f'), do not do some annoying print
                // and delete the breakpoint after hitting it.
                //
                clear_breakpoint(globals.breakpoint_hit_index);
            }else{
                print("\n%s breakpoint %x hit!\n", breakpoint_type_to_string[type], globals.breakpoint_hit_index);
            }
        }
    }
    
    struct breakpoint breakpoint_hit = {0}; 
    if(globals.breakpoint_hit_index >= 0) breakpoint_hit = globals.breakpoints[globals.breakpoint_hit_index];
    
    globals.single_stepping = false;
    
    if(globals.print_trace && globals.trace_file != stdout){
        // Make sure the trace file is flushed, when we enter the debugger.
        fflush(globals.trace_file);
    }
    
    
    // 
    // Aggressively, search out all of the loaded modules.
    // 
    struct loaded_module *nt = maybe_find_nt_and_load_module_list(context);
    
    // 
    // Try to print where we are in the code.
    // 
    
    struct loaded_module *module_at_rip = get_module_for_address(registers->rip);
    if(module_at_rip){ print_symbol_from_loaded_module(context, module_at_rip, registers->rip, stdout); print("\n"); }
    
    print("%p: ", registers->rip);
    u64 next_rip = registers->rip;
    next_rip += print_disassembly(context, next_rip, null);
    print("\n");
    
    context->scratch_arena.current = context->scratch_arena.base; // Reset the `scratch_arena`.
    
    snapshot_mode_currently_in_debugger = true; // @note: We set this while in the debugger, so that we can CTRL-C.
    
    static struct string last_command = {0}; // only ever "s" or "n".
    
    static struct{
        int active;
        struct string script;
    } script;
    
    while(true){
        context->crash = CRASH_none;
        context->crash_address = 0;
        
        struct string line;
        
        if(script.active){
            line = string_eat_line(&script.script);
            string_skip_whitespace(&script.script);
            script.active = script.script.size != 0;
            print("script: %.*s", line.size, line.data);
        }else{
            print("debugger: ");
            
            //
            // Read a single line from 'stdin'. We limit the line size to '0x100', hopefully this is fine for everyone :)
            //
            char line_buffer[0x100] = {0};
            fgets(line_buffer, sizeof(line_buffer), stdin);
            size_t line_size = strlen(line_buffer);
            if(line_size <= 0) continue;
            
            line = (struct string){
                .data = line_buffer,
                .size = line_size,
            };
        }
        
        //
        // Remove trailing whitespace from the command, as it sometimes gets annoying while parsing.
        //
        while(line.size && character_is_whitespace(line.data[line.size - 1])) line.size -= 1;
        
        //
        // Eat any leading whitespace before the command.
        //
        string_skip_whitespace(&line);
        
        //
        // The first _identifier_ is the command we want to execute.
        //
        struct string command = string_eat_nonwhitespace(&line);
        
        if(!command.size) command = last_command;
        
        //
        // There was only whitespace in the 'line'.
        //
        if(command.size == 0){
            print("Expected a command. See 'help' for list of commands.\n");
            continue;
        }
        
        //
        // Eat whitespace before the arguments, to give the code below an easier time parsing.
        //
        string_skip_whitespace(&line);
        
        //
        // Execute the command.
        //
        
        if(string_match(command, string("s"))){
            //
            // Step a single instruction.
            //
            
            globals.single_stepping = true;
            last_command = string("s");
            break;
        }
        
        if(string_match(command, string("n"))){
            //
            // Step over one instruction, this could be a call.
            //
            u64 address = registers->rip;
            
            u8 instruction_buffer[16] = {0};
            u32 instruction_buffer_size = prefetch_instruction(context, address, instruction_buffer, sizeof(instruction_buffer));
            
            struct instruction_information decoded_instruction = decode_instruction(instruction_buffer);
            
            if(decoded_instruction.instruction_size > instruction_buffer_size){
                // If we are stepping into an unmapped page, we should break on the interrupt vector, 
                // hence, it should be fine to single step here.
                globals.single_stepping = true;
                break;
            }
            
            int is_call = 0;
            
            if(decoded_instruction.augmented_opcode == /*call rel32*/0xe8){
                is_call = 1;
            }else if((decoded_instruction.augmented_opcode == 0xff) && (decoded_instruction.reg == /*reg opcode call*/2)){
                is_call = 1;
            }
            
            if(is_call){
                int success;
                if(context->use_hypervisor){
                    success = hypervisor_set_breakpoint(context, &context->registers, BREAKPOINT_execute, BREAKPOINT_FLAG_oneshot, next_rip, 1);
                }else{
                    success = add_breakpoint(BREAKPOINT_execute, next_rip, 1, BREAKPOINT_FLAG_oneshot);
                }
                if(!success) continue;
            }else{
                globals.single_stepping = true;
            }
            
            last_command = string("n");
            break;
        }
        
        last_command = string("");
        
        if(string_match(command, string("f"))){
            //
            // 'finish' the current function.
            //
            
            if(!module_at_rip){
                print("Current 'rip' is not within a module.\n");
                continue;
            }
            
            if(!module_at_rip->have_unwind_information){
                loaded_module_try_to_load_unwind_information(context, module_at_rip);
                if(!module_at_rip->have_unwind_information){
                    print("Failed to load unwind information for module '%.*s'.\n", module_at_rip->short_name.size, module_at_rip->short_name.data);
                    if(!module_at_rip->pdata.rva){
                        print("This is because the header is not paged in.\n");
                    }else if(!module_at_rip->pdata.base){
                        print("This is because the .pdata-section is not completely paged in.\n");
                    }else if(!module_at_rip->xdata.base){
                        print("This is because the .xdata-section is not completely paged in.\n");
                    }
                    
                    continue;
                }
            }
            
            struct registers unwound_registers = *registers;
            
            unwind_one_function(context, module_at_rip, &unwound_registers, 0);
            
            u64 return_address = unwound_registers.rip;
            
            if(context->crash != CRASH_none || !translate_address(context, return_address, PERMISSION_execute)){
                print("Could not read return address of current function.\n");
                continue;
            }
            
            int success;
            if(context->use_hypervisor){
                success = hypervisor_set_breakpoint(context, &context->registers, BREAKPOINT_execute, BREAKPOINT_FLAG_oneshot, return_address, 1);
            }else{
                success = add_breakpoint(BREAKPOINT_execute, return_address, 1, BREAKPOINT_FLAG_oneshot);
            }
            
            if(success) break;
            
            continue;
        }
        
        if(string_match(command, string("g"))){
            //
            // Continue execution.
            //
            print("Continuing!\n");
            break;
        }
        
        if(string_match(command, string("pm"))){
            if(!line.size){
                
                if(globals.print_mode & PRINT_kd){
                    print("Current print mode is \"kd-like\".\n");
                    continue;
                }
                
                enum print_mode mode = globals.print_mode;
                
                print("Current print mode is: ");
                if(mode & PRINT_rip)     print("'rip' ");
                if(mode & PRINT_symbol)  print("'symbol' ");
                if(mode & PRINT_gpr)     print("'gpr' ");
                if(mode & PRINT_flags)   print("'flags' ");
                if(mode & PRINT_cr)      print("'cr' ");
                if(mode & PRINT_segment) print("'segment' ");
                if(mode & PRINT_xmm)     print("'xmm' ");
                print("\n\n");
                
                print("Options are 'rip', 'symbol', 'gpr', 'flags', 'cr', 'segment', 'xmm'.\n");
                continue;
            }
            
            globals.print_mode = 0;
            
            while(line.size){
                struct string mode = string_eat_nonwhitespace(&line);
                string_skip_whitespace(&line);
                
                if(0){}
                else if(string_match(mode, string("rip")))     globals.print_mode |= PRINT_rip;
                else if(string_match(mode, string("symbol")))  globals.print_mode |= PRINT_symbol;
                else if(string_match(mode, string("gpr")))     globals.print_mode |= PRINT_gpr;
                else if(string_match(mode, string("flags")))   globals.print_mode |= PRINT_flags;
                else if(string_match(mode, string("cr")))      globals.print_mode |= PRINT_cr;
                else if(string_match(mode, string("segment"))) globals.print_mode |= PRINT_segment;
                else if(string_match(mode, string("xmm")))     globals.print_mode |= PRINT_xmm;
                
                else if(string_match(mode, string("default"))) globals.print_mode |= PRINT_default;
                else if(string_match(mode, string("all")))     globals.print_mode |= PRINT_all;
                
                else if(string_match(mode, string("kd")))      globals.print_mode = PRINT_kd;
                
                else{
                    print("Unknown print mode '%.*s'. Execute 'pm' for list of options.\n", mode.size, mode.data);
                }
            }
            
            continue;
        }
        
        if(string_match(command, string("t"))){
            //
            // Enable/disable instruction tracing.
            //
            
            if(globals.print_trace && globals.trace_file != stdout){
                fclose(globals.trace_file);
                globals.trace_file = stdout;
            }
            
            if(line.size){
                // 
                // Attempt to set the trace file.
                // 
                
                line.data[line.size] = 0; // This will likely overwrite the newline.
                char *trace_file = (char *)line.data;
                if(!cstring_ends_with_case_insensitive(trace_file, ".log")){
                    char buffer[0x100];
                    snprintf(buffer, sizeof(buffer), "%s.log", trace_file);
                    trace_file = buffer;
                }
                
                globals.trace_file = fopen(trace_file, "w");
                if(!globals.trace_file){
                    print("Error: Could not open trace file %s\n", trace_file);
                    globals.trace_file = stdout;
                    continue;
                }
                
                print("Logging to file '%s'.\n", trace_file);
                globals.print_trace = true;
            }else{
                globals.print_trace = !globals.print_trace;
            }
            
            print("print_trace now '%s'.\n\n", globals.print_trace ? "enabled" : "disabled"); // @note: Two newlines so editors can _jump_ to the beginning of a trace more easily.
            continue;
        }
        
        if(string_match(command, string("r"))){
            //
            // Print some (or all) registers.
            //
            
            if(line.size == 0){
                //
                // No arguments given, print all registers.
                //
                print_registers(context, stdout);
                continue;
            }
            
            while(line.size){
                struct string reg = string_eat_nonwhitespace(&line);
                assert(reg.size > 0); // Should be given, by how the loop is constructed.
                
                //
                // Eat the whitespace for the next iteration.
                //
                string_skip_whitespace(&line);
                
                //
                // Strip separating ',' if it is there.
                //
                if(reg.data[reg.size] == ',') reg.size -= 1;
                
                //
                // 8-bit general purpose registers.
                //
                
                else if(string_match(reg, string("al"))){ print("al = %x\n", (u8)registers->rax); }
                else if(string_match(reg, string("cl"))){ print("cl = %x\n", (u8)registers->rcx); }
                else if(string_match(reg, string("dl"))){ print("dl = %x\n", (u8)registers->rdx); }
                else if(string_match(reg, string("bl"))){ print("bl = %x\n", (u8)registers->rbx); }
                
                else if(string_match(reg, string("sil"))){ print("sil = %x\n", (u8)registers->rsi); }
                else if(string_match(reg, string("dil"))){ print("dil = %x\n", (u8)registers->rdi); }
                else if(string_match(reg, string("spl"))){ print("spl = %x\n", (u8)registers->rsp); }
                else if(string_match(reg, string("bpl"))){ print("bpl = %x\n", (u8)registers->rbp); }
                
                else if(string_match(reg, string("r8b"))){  print("r8b = %x\n", (u8)registers->r8); }
                else if(string_match(reg, string("r9b"))){  print("r9b = %x\n", (u8)registers->r9); }
                else if(string_match(reg, string("r10b"))){ print("r10b = %x\n", (u8)registers->r10); }
                else if(string_match(reg, string("r11b"))){ print("r11b = %x\n", (u8)registers->r11); }
                else if(string_match(reg, string("r12b"))){ print("r12b = %x\n", (u8)registers->r12); }
                else if(string_match(reg, string("r13b"))){ print("r13b = %x\n", (u8)registers->r13); }
                else if(string_match(reg, string("r14b"))){ print("r14b = %x\n", (u8)registers->r14); }
                else if(string_match(reg, string("r15b"))){ print("r15b = %x\n", (u8)registers->r15); }
                
                //
                // 16-bit general purpose registers.
                //
                
                else if(string_match(reg, string("ax"))){ print("ax = %x\n", (u16)registers->rax); }
                else if(string_match(reg, string("cx"))){ print("cx = %x\n", (u16)registers->rcx); }
                else if(string_match(reg, string("dx"))){ print("dx = %x\n", (u16)registers->rdx); }
                else if(string_match(reg, string("bx"))){ print("bx = %x\n", (u16)registers->rbx); }
                else if(string_match(reg, string("si"))){ print("si = %x\n", (u16)registers->rsi); }
                else if(string_match(reg, string("di"))){ print("di = %x\n", (u16)registers->rdi); }
                else if(string_match(reg, string("sp"))){ print("sp = %x\n", (u16)registers->rsp); }
                else if(string_match(reg, string("bp"))){ print("bp = %x\n", (u16)registers->rbp); }
                
                else if(string_match(reg, string("r8w"))){  print("r8w = %x\n", (u16)registers->r8); }
                else if(string_match(reg, string("r9w"))){  print("r9w = %x\n", (u16)registers->r9); }
                else if(string_match(reg, string("r10w"))){ print("r10w = %x\n", (u16)registers->r10); }
                else if(string_match(reg, string("r11w"))){ print("r11w = %x\n", (u16)registers->r11); }
                else if(string_match(reg, string("r12w"))){ print("r12w = %x\n", (u16)registers->r12); }
                else if(string_match(reg, string("r13w"))){ print("r13w = %x\n", (u16)registers->r13); }
                else if(string_match(reg, string("r14w"))){ print("r14w = %x\n", (u16)registers->r14); }
                else if(string_match(reg, string("r15w"))){ print("r15w = %x\n", (u16)registers->r15); }
                
                //
                // 32-bit general purpose registers.
                //
                
                else if(string_match(reg, string("eax"))){ print("eax = %x\n", (u32)registers->rax); }
                else if(string_match(reg, string("ecx"))){ print("ecx = %x\n", (u32)registers->rcx); }
                else if(string_match(reg, string("edx"))){ print("edx = %x\n", (u32)registers->rdx); }
                else if(string_match(reg, string("ebx"))){ print("ebx = %x\n", (u32)registers->rbx); }
                else if(string_match(reg, string("esi"))){ print("esi = %x\n", (u32)registers->rsi); }
                else if(string_match(reg, string("edi"))){ print("edi = %x\n", (u32)registers->rdi); }
                else if(string_match(reg, string("esp"))){ print("esp = %x\n", (u32)registers->rsp); }
                else if(string_match(reg, string("ebp"))){ print("ebp = %x\n", (u32)registers->rbp); }
                
                else if(string_match(reg, string("r8d"))){  print("r8d = %x\n", (u32)registers->r8); }
                else if(string_match(reg, string("r9d"))){  print("r9d = %x\n", (u32)registers->r9); }
                else if(string_match(reg, string("r10d"))){ print("r10d = %x\n", (u32)registers->r10); }
                else if(string_match(reg, string("r11d"))){ print("r11d = %x\n", (u32)registers->r11); }
                else if(string_match(reg, string("r12d"))){ print("r12d = %x\n", (u32)registers->r12); }
                else if(string_match(reg, string("r13d"))){ print("r13d = %x\n", (u32)registers->r13); }
                else if(string_match(reg, string("r14d"))){ print("r14d = %x\n", (u32)registers->r14); }
                else if(string_match(reg, string("r15d"))){ print("r15d = %x\n", (u32)registers->r15); }
                
                //
                // 64-bit general purpose registers.
                //
                
                else if(string_match(reg, string("rax"))){ print("rax = %p\n", registers->rax); }
                else if(string_match(reg, string("rcx"))){ print("rcx = %p\n", registers->rcx); }
                else if(string_match(reg, string("rdx"))){ print("rdx = %p\n", registers->rdx); }
                else if(string_match(reg, string("rbx"))){ print("rbx = %p\n", registers->rbx); }
                else if(string_match(reg, string("rsi"))){ print("rsi = %p\n", registers->rsi); }
                else if(string_match(reg, string("rdi"))){ print("rdi = %p\n", registers->rdi); }
                else if(string_match(reg, string("rsp"))){ print("rsp = %p\n", registers->rsp); }
                else if(string_match(reg, string("rbp"))){ print("rbp = %p\n", registers->rbp); }
                
                else if(string_match(reg, string("r8"))){  print("r8 = %p\n", registers->r8); }
                else if(string_match(reg, string("r9"))){  print("r9 = %p\n", registers->r9); }
                else if(string_match(reg, string("r10"))){ print("r10 = %p\n", registers->r10); }
                else if(string_match(reg, string("r11"))){ print("r11 = %p\n", registers->r11); }
                else if(string_match(reg, string("r12"))){ print("r12 = %p\n", registers->r12); }
                else if(string_match(reg, string("r13"))){ print("r13 = %p\n", registers->r13); }
                else if(string_match(reg, string("r14"))){ print("r14 = %p\n", registers->r14); }
                else if(string_match(reg, string("r15"))){ print("r15 = %p\n", registers->r15); }
                
                // 
                // Rip.
                // 
                else if(string_match(reg, string("rip"))){ print("rip = %p\n", registers->rip); }
                
                //
                // Segment registers.
                //
                else if(string_match(reg, string("cs"))){ print_segment(registers->cs); }
                else if(string_match(reg, string("es"))){ print_segment(registers->es); }
                else if(string_match(reg, string("ss"))){ print_segment(registers->ss); }
                else if(string_match(reg, string("ds"))){ print_segment(registers->ds); }
                else if(string_match(reg, string("gs"))){ print("gs = %p, gs_swap = %p\n", registers->gs_base, registers->gs_swap); }
                else if(string_match(reg, string("fs"))){ print("fs = %p\n", registers->fs_base); }
                
                else if(string_match(reg, string("tr"))){ print_segment(registers->tr); print("reloaded: "); print_segment(parse_segment_from_global_descriptor_table(context, registers->gdt_base, registers->tr.selector));}
                else if(string_match(reg, string("ldt"))){ print_segment(registers->ldt); }
                
                // 
                // Table registers.
                // 
                
                else if(string_match(reg, string("gdt"))){ print("gdtl = 0x%x gdtr = %p\n", registers->gdt_limit, registers->gdt_base); }
                else if(string_match(reg, string("idt"))){ print("idtl = 0x%x idtr = %p\n", registers->idt_limit, registers->idt_base); }
                
                //
                // Control registers.
                //
                
                else if(string_match(reg, string("cr0"))){ 
                    print("cr0 = %llx ", registers->cr0); 
                    
                    static char *flags[] = {
                        [0] = "PE", [1] = "MP", [2] = "EM", [3] = "TS", [4] = "ET", [5] = "NE", [16] = "WP", [18] = "AM", [29] = "NW", [30] = "CD", [31] = "PG",
                    };
                    
                    print_bit_meaning_for_register(registers->cr0, flags, array_count(flags));
                }
                
                else if(string_match(reg, string("cr2"))){ print("cr2 = %llx\n", registers->cr2); }
                else if(string_match(reg, string("cr3"))){ print("cr3 = %llx\n", registers->cr3); }
                else if(string_match(reg, string("cr4"))){ 
                    print("cr4 = %llx ", registers->cr4); 
                    
                    static char *flags[] = {
                        [0] = "VME", [1] = "PVI", [2] = "TSD", [3] = "DE", [4] = "PSE", [5] = "PAE", [6] = "MCE", [7] = "PGE", [8] = "PCE", [9] = "OSFXSR", [10] = "OSXMMEXCPT", [11] = "UMIP", [12] = "LA57", [13] = "VMXE", [14] = "SMXE", [15] = "RESERVED", [16] = "FSBASE", [17] = "PCIDE", [18] = "OSXSAVE", [19] = "KL", [20] = "SMEP", [21] = "SMAP", [22] = "PKE", [23] = "CET", [24] = "PKS", [25] = "UNITR",
                    };
                    
                    print_bit_meaning_for_register(registers->cr4, flags, array_count(flags));
                }
                else if(string_match(reg, string("cr8"))){ print("cr8 = %llx\n", registers->cr8); }
                
                else if(string_match(reg, string("xcr0"))){ 
                    print("xcr0 = %llx\n", registers->xcr0); 
                    
                    static char *flags[] = {
                        [0] = "X87", [1] = "SSE", [2] = "AVX", [3] = "BNDREG", [4] = "BNDCSR", [5] = "opmask", [6] = "ZMM_hi256", [7] = "Hi16_ZMM", [8] = "PT", [9] = "PKRU", [10] = "PASID", [11] = "CET_U", [12] = "CET_S", [13] = "HDC", [14] = "UINTR", [15] = "LBR", [16] = "HWP", [17] = "AMX-TILECFG", [18] = "AMX-TILEDATA", [19] = "APX-extended-GPRs",
                    };
                    
                    print_bit_meaning_for_register(registers->xcr0, flags, array_count(flags));
                }
                else if(string_match(reg, string("efer"))){ 
                    print("efer = %llx\n", registers->ia32_efer); 
                    
                    static char *flags[32] = {
                        [0] = "SCE", [1] = "DPE", [2] = "SEWBED", [3] = "GEWBED", [4] = "L2D", [8] = "LME", [9] = "Reserved", [10] = "LMA", [11] = "NXE", [12] = "SVME", [13] = "LMSLE", [14] = "FFXSR", [15] = "TCE", [16] = "Reserved", [17] = "MCOMMIT", [18] = "INTWB", [19] = "Reserved", [20] = "UAIE", [21] = "AIBRSE", 
                    };
                    
                    print_bit_meaning_for_register(registers->ia32_efer, flags, array_count(flags));
                }
                
                //
                // Debug registers.
                //
                
                else if(string_match(reg, string("dr0"))){ print("dr0 = %llx (", registers->dr0); print_symbol(context, registers->dr0); print(")\n");}
                else if(string_match(reg, string("dr1"))){ print("dr1 = %llx (", registers->dr1); print_symbol(context, registers->dr1); print(")\n"); }
                else if(string_match(reg, string("dr2"))){ print("dr2 = %llx (", registers->dr2); print_symbol(context, registers->dr2); print(")\n"); }
                else if(string_match(reg, string("dr3"))){ print("dr3 = %llx (", registers->dr3); print_symbol(context, registers->dr3); print(")\n"); }
                else if(string_match(reg, string("dr6"))){ 
                    print("dr6 = %llx ( ", registers->dr6); 
                    if(registers->dr6 & 1) print(" #0");
                    if(registers->dr6 & 2) print(" #1");
                    if(registers->dr6 & 3) print(" #2");
                    if(registers->dr6 & 4) print(" #4");
                    if(registers->dr6 & (1 << 11)) print(" BLD");
                    if(registers->dr6 & (1 << 12)) print(" BK");
                    if(registers->dr6 & (1 << 13)) print(" BD");
                    if(registers->dr6 & (1 << 14)) print(" BS");
                    if(registers->dr6 & (1 << 15)) print(" BT");
                    if(registers->dr6 & (1 << 16)) print(" RTM");
                    print(")\n");
                    
                }else if(string_match(reg, string("dr7"))){ 
                    print("dr7 = %llx\n", registers->dr7); 
                    
                    if(registers->dr7 & (1ull <<  0)) print("    #0 is locally enabled\n");
                    if(registers->dr7 & (1ull <<  1)) print("    #0 is globally enabled\n");
                    if(registers->dr7 & (1ull <<  2)) print("    #1 is locally enabled\n");
                    if(registers->dr7 & (1ull <<  3)) print("    #1 is globally enabled\n");
                    if(registers->dr7 & (1ull <<  4)) print("    #2 is locally enabled\n");
                    if(registers->dr7 & (1ull <<  5)) print("    #2 is globally enabled\n");
                    if(registers->dr7 & (1ull <<  6)) print("    #3 is locally enabled\n");
                    if(registers->dr7 & (1ull <<  7)) print("    #3 is globally enabled\n");
                    if(registers->dr7 & (1ull <<  8)) print("    LE - Local Exact (386 only)\n");
                    if(registers->dr7 & (1ull <<  9)) print("    GE - Global Exact (386 only)\n");
                    if(registers->dr7 & (1ull << 11)) print("    RTM\n");
                    if(registers->dr7 & (1ull << 12)) print("    IR, SMIE (386/486 only)\n");
                    if(registers->dr7 & (1ull << 13)) print("    GD - Global Detect Enabled\n");
                    
                    for(int breakpoint_index = 0; breakpoint_index < 4; breakpoint_index++){
                        u64 active_bit = 1ull << (1 + 2 * breakpoint_index);
                        
                        u32 type   = (registers->dr7 >> (16 + 4 * breakpoint_index)) & 0x3;
                        u32 length = (registers->dr7 >> (18 + 4 * breakpoint_index)) & 0x3;
                        
                        if(registers->dr7 & active_bit){
                            print("    #%d: ", breakpoint_index);
                            
                            if(type == 0b11) print(" [read]");
                            if(type == 0b01) print(" [write]");
                            
                            if(length == 0b01) print(" [2-byte]");
                            if(length == 0b11) print(" [4-byte]"); // @note: This has some weird swizzle.
                            if(length == 0b10) print(" [8-byte]");
                            
                            print("\n");
                        }
                    }
                }
                
                
                //
                // Xmm registers.
                //
                else if(string_match(reg, string("xmm0"))){  print_xmm(registers->simd[0].xmmi, 0); }
                else if(string_match(reg, string("xmm1"))){  print_xmm(registers->simd[1].xmmi, 1); }
                else if(string_match(reg, string("xmm2"))){  print_xmm(registers->simd[2].xmmi, 2); }
                else if(string_match(reg, string("xmm3"))){  print_xmm(registers->simd[3].xmmi, 3); }
                else if(string_match(reg, string("xmm4"))){  print_xmm(registers->simd[4].xmmi, 4); }
                else if(string_match(reg, string("xmm5"))){  print_xmm(registers->simd[5].xmmi, 5); }
                else if(string_match(reg, string("xmm6"))){  print_xmm(registers->simd[6].xmmi, 6); }
                else if(string_match(reg, string("xmm7"))){  print_xmm(registers->simd[7].xmmi, 7); }
                else if(string_match(reg, string("xmm8"))){  print_xmm(registers->simd[8].xmmi, 8); }
                else if(string_match(reg, string("xmm9"))){  print_xmm(registers->simd[9].xmmi, 9); }
                else if(string_match(reg, string("xmm10"))){ print_xmm(registers->simd[10].xmmi, 10); }
                else if(string_match(reg, string("xmm11"))){ print_xmm(registers->simd[11].xmmi, 11); }
                else if(string_match(reg, string("xmm12"))){ print_xmm(registers->simd[12].xmmi, 12); }
                else if(string_match(reg, string("xmm13"))){ print_xmm(registers->simd[13].xmmi, 13); }
                else if(string_match(reg, string("xmm14"))){ print_xmm(registers->simd[14].xmmi, 14); }
                else if(string_match(reg, string("xmm15"))){ print_xmm(registers->simd[15].xmmi, 15); }
                
                //
                // Ymm registers.
                //
                else if(string_match(reg, string("ymm0"))){  print_ymm(registers->simd[0].ymmi, 0); }
                else if(string_match(reg, string("ymm1"))){  print_ymm(registers->simd[1].ymmi, 1); }
                else if(string_match(reg, string("ymm2"))){  print_ymm(registers->simd[2].ymmi, 2); }
                else if(string_match(reg, string("ymm3"))){  print_ymm(registers->simd[3].ymmi, 3); }
                else if(string_match(reg, string("ymm4"))){  print_ymm(registers->simd[4].ymmi, 4); }
                else if(string_match(reg, string("ymm5"))){  print_ymm(registers->simd[5].ymmi, 5); }
                else if(string_match(reg, string("ymm6"))){  print_ymm(registers->simd[6].ymmi, 6); }
                else if(string_match(reg, string("ymm7"))){  print_ymm(registers->simd[7].ymmi, 7); }
                else if(string_match(reg, string("ymm8"))){  print_ymm(registers->simd[8].ymmi, 8); }
                else if(string_match(reg, string("ymm9"))){  print_ymm(registers->simd[9].ymmi, 9); }
                else if(string_match(reg, string("ymm10"))){ print_ymm(registers->simd[10].ymmi, 10); }
                else if(string_match(reg, string("ymm11"))){ print_ymm(registers->simd[11].ymmi, 11); }
                else if(string_match(reg, string("ymm12"))){ print_ymm(registers->simd[12].ymmi, 12); }
                else if(string_match(reg, string("ymm13"))){ print_ymm(registers->simd[13].ymmi, 13); }
                else if(string_match(reg, string("ymm14"))){ print_ymm(registers->simd[14].ymmi, 14); }
                else if(string_match(reg, string("ymm15"))){ print_ymm(registers->simd[15].ymmi, 15); }
                
                
                else if(string_match(reg, string("rdtsc")) || string_match(reg, string("tsc"))){ print("0x%llx\n", registers->ia32_tsc); }
                
                //
                // Flags.
                //
                
                else if(string_match(reg, string("CF"))){ print("CF = %d\n", registers->CF); }
                else if(string_match(reg, string("ZF"))){ print("ZF = %d\n", registers->ZF); }
                else if(string_match(reg, string("SF"))){ print("SF = %d\n", registers->SF); }
                else if(string_match(reg, string("PF"))){ print("PF = %d\n", registers->PF); }
                else if(string_match(reg, string("OF"))){ print("OF = %d\n", registers->OF); }
                else if(string_match(reg, string("flags")) || string_match(reg, string("rflags")) || string_match(reg, string("eflags"))){
                    print("rflags: %p\n\n", registers->rflags);
                    print("Flags:\n");
                    print("   CF %d\n", registers->CF);
                    print("   PF %d\n", registers->PF);
                    print("   AF %d\n", registers->AF);
                    print("   ZF %d\n", registers->ZF);
                    print("   SF %d\n", registers->SF);
                    print("   TF %d\n", registers->TF);
                    print("   IF %d\n", registers->IF);
                    print("   DF %d\n", registers->DF);
                    print("   OF %d\n", registers->OF);
                    print("   IO %d\n", registers->IOPL);
                    print("   NT %d\n", registers->NT);
                    
                    print("Eflags:\n");
                    print("   RF  %d\n", registers->RF);
                    print("   VM  %d\n", registers->VM);
                    print("   AC  %d\n", registers->AC);
                    print("   VIF %d\n", registers->VIF);
                    print("   VIP %d\n", registers->VIP);
                    print("   ID  %d\n", registers->ID);
                }else{
                    print("Could not parse '%.*s' as a register.\n", reg.size, reg.data);
                }
            }
            
            continue;
        }
        
        if(string_match(command, string("m")) || string_match(command, string("lm"))){
            
            if(line.size){
                struct string module_name = line;
                
                //
                // Print information for all loaded modules.
                //
                for(struct loaded_module *module = globals.module_list.first; module; module = module->next){
                    
                    if(string_match(module->short_name, module_name)){
                        print("%.*s %p %p\n", module->short_name.size, module->short_name.data, module->guest_image_base, module->guest_image_base + module->size_of_image);
                        
                        if(module->pdb_context) print("Symbols data loaded.\n");
                        if(module->have_unwind_information) print("Unwind data loaded.\n");
                        if(module->tried_to_load_pdb) print("Attempted to load pdb.\n");
                        break;
                    }
                }
            }
            
            
            //
            // Print information for all loaded modules.
            //
            for(struct loaded_module *module = globals.module_list.first; module; module = module->next){
                print("%-20s %p %p  ", module->short_name.data, module->guest_image_base, module->guest_image_base + module->size_of_image);
                
                if(module->pdb_context) print("[symbols]");
                if(module->have_unwind_information) print("[unwind]");
                
                print("\n");
                
            }
            continue;
        }
        
        if(string_match(command, string("x")) || string_match(command, string("?"))){
            //
            // Evaluate the given address and print all information we know about it (address, mod-off, symbol).
            //
            
            int error = 0;
            
            u64 address = parse_address(context, &line, &error);
            if(error) continue;
            
            for(struct loaded_module *module = globals.module_list.first; module; module = module->next){
                if(module->guest_image_base <= address && address < module->guest_image_base + module->size_of_image){
                    
                    print_symbol_from_loaded_module(context, module, address, stdout); print("\n");
                    print("%s + %llx\n", module->short_name.data, address - module->guest_image_base);
                    break;
                }
            }
            
            print("%p\n", (void *)address);
            continue;
        }
        
        if(string_match(command, string("k"))){
            //
            // Print a stack trace.
            //
            print_stack_trace(context);
            continue;
        }
        
        if(string_match(command, string("u"))){
            //
            // Disassemble at address.
            //
            
            int error = 0;
            u64 address = parse_address(context, &line, &error);
            if(error) continue;
            
            u64 count = 0;
            
            if(line.size){
                count = parse_number(line, &error);
                if(error) continue;
                
                if(error){
                    print("Could not parse count '%.*s'\n", line.size, line.data);
                    continue;
                }
            }
            
            if(address == 0){
                address = registers->rip;
            }
            
            if(!count) count = 10;
            
            u64 cr3 = patch_in_kernel_cr3(context);
            
            for(u64 i = 0; i < count; i++){
                print("%p: ", address);
                int crash = 0;
                address += print_disassembly(context, address, &crash);
                print("\n");
                if(crash) break;
            }
            
            context->registers.cr3 = cr3;
            continue;
        }
        
        if(string_match(command, string("dt")) || string_match(command, string("list"))){
            //
            // Print a symbolized _dump_. Syntax is:
            //     dt [module!]<type>[.member_string] <address> [member_string]
            // Where <module> is some loaded_module, <type> is some type name and [member_string] are fields like 'Parameters.DeviceIoControl'
            // to read specific members for some compound type.
            //
            
            if(!line.size){
                if(string_match(command, string("dt"))){
                    print("dt [module!]<type>[.member_string] [address] [member_string]\n");
                    print("\n");
                    print("e.g.: dt nt!_IRP rdx\n");
                    print("e.g.: dt _IRP rdx\n");
                    print("e.g.: dt _IRP\n");
                    print("e.g.: dt nt!_IRP.Tail.Overlay rdx\n");
                    print("e.g.: dt nt!_IRP rdx Tail.Overlay.Thread\n");
                }
                
                if(string_match(command, string("list"))){
                    print("list [module!]<type>[.member_string] <address> [member_string]\n");
                    print("\n");
                    print("Assumes <address> is a pointer to <type> and <member_string> is the member inside the type that forms the 'Next' pointer.\n");
                }
                
                continue;
            }
            
            
            print("\n"); // Give us an empty line to jump to!
            
            struct string symbol    = string_eat_nonwhitespace(&line);
            struct string module_name = get_module_name_from_symbol_string(symbol);
            
            struct string type_name = symbol;
            if(module_name.data){
                type_name.data += module_name.size + 1; // @note: +1 for the '!'.
                type_name.size -= module_name.size + 1;
            }
            
            struct string member_string = {0};
            for(smm index = 0; index < type_name.size; index++){
                if(type_name.data[index] == '.'){
                    member_string.size = type_name.size - index;
                    member_string.data = type_name.data + index;
                    
                    type_name.size = index;
                    break;
                }
            }
            
            string_skip_whitespace(&line);
            
            int have_address = 0;
            u64 address = 0;
            
            if(line.size){
                int error = 0;
                address = parse_address(context, &line, &error);
                if(error) continue;
                
                have_address = 1;
            }
            
            if(line.size){
                //
                // Also allow specifying the member string at the very end.
                //
                if(!member_string.data){
                    member_string = string_eat_nonwhitespace(&line);
                }
            }
            
            struct loaded_module *module = null;
            
            if(module_name.data){
                module = get_loaded_module(module_name);
                if(!module){
                    print("Could not find module '%.*s'.\n", module_name.size, module_name.data);
                    continue;
                }
            }else{
                //
                // @note: Hacky loop to check all modules.
                //
                
                for(struct loaded_module *it = globals.module_list.first; it; it = it->next){
                    if(!it->pdb_context) continue;
                    
                    if(pdb_hash_table_get(&it->pdb_context->type_table, type_name)){
                        module = it;
                        break;
                    }
                }
                
                if(!module){
                    print("Could not find '%.*s' in any module.\n", type_name.size, type_name.data);
                    continue;
                }
                
            }
            
            if(!module->tried_to_load_pdb) loaded_module_try_to_load_pdb(context, module);
            if(!module->pdb_context){
                print("Failed to load the PDB for module '%s'.\n", module->short_name.data);
                continue;
            }
            
            if(string_match(command, string("list"))){
                if(member_string.size == 0) member_string = string("ListEntry");
                
                if(!have_address){
                    print("\"list\" command requires an address.\n");
                    continue;
                }
                
                int error = 0;
                u64 member_offset = pdb_get_member_offset(module->pdb_context, type_name, member_string, &error);
                if(error){
                    print("Could not get offset of '%.*s' in '%.*s'\n", member_string.size, member_string.data, type_name.size, type_name.data); 
                    continue;
                } 
                
                u64 starting_address = address;
                
                int count = 0;
                
                u64 user_cr3 = patch_in_kernel_cr3(context);
                do{
                    print("Entry %d at %p:\n", count, address);
                    pdb_dump_type(context, module->pdb_context, type_name, /*member_string*/string(""), address, have_address);
                    
                    u64 next_address;
                    int success = guest_read_size(context, &next_address, address + member_offset, sizeof(next_address), PERMISSION_none);
                    if(!success) break;
                    
                    address = next_address - member_offset;
                    
                    if(count++ == 100){ 
                        print("Exceeded 100 members in the list.\n");
                        break;
                    }
                } while(!context->crash && address && (address != starting_address));
                
                context->registers.cr3 = user_cr3;
            }else{
                // dt <type> [<address>]
                
                u64 user_cr3 = patch_in_kernel_cr3(context);
                
                pdb_dump_type(context, module->pdb_context, type_name, member_string, address, have_address);
                
                context->registers.cr3 = user_cr3;
            }
            continue;
        }
        
        if(string_match(command, string("db")) || string_match(command, string("dw")) || string_match(command, string("dd")) || string_match(command, string("dq")) || string_match(command, string("dp")) || string_match(command, string("dps"))){
            
            //
            // Dump bytes at location.
            //
            // @cleanup: maybe this should be a common utility function,
            //           so we can call it at more places and be sure not to _crash_.
            //
            
            int is_phys = 0;
            if(line.size >= 2 && line.data[0] == '/' && line.data[1] == 'p'){
                is_phys = 1;
                line.size -= 2;
                line.data += 2;
                string_skip_whitespace(&line);
                
                if(!string_match(command, string("db"))){
                    print("Error: Printing physical memory currently only implemented for 'db'.\n");
                    continue;
                }
            }
            
            int error = 0;
            u64 address = parse_address(context, &line, &error);
            if(error) continue;
            
            u64 count = 0;
            
            if(line.size){
                count = parse_number(line, &error);
                if(error) continue;
                
                if(error){
                    print("Could not parse count '%.*s'\n", line.size, line.data);
                    continue;
                }
            }
            
            u64 user_cr3 = patch_in_kernel_cr3(context);
            
            switch(command.data[1]){
                case 'b':{
                    if(!count) count = 0x80;
                    
                    if(count > 0x8000) count = 0x8000;
                    
                    u64 row_count = (count + 0xf)/0x10;
                    
                    for(u64 row_index = 0; row_index < row_count; row_index++){
                        print("%p: ", address + row_index * 0x10);
                        
                        for(u64 column_index = 0; column_index < 0x10; column_index++){
                            
                            if(0x10 * row_index + column_index < count){
                                
                                context->crash = CRASH_none;
                                u8 byte = is_phys ? *get_physical_memory_for_read(context, address + row_index * 0x10 + column_index) : guest_read(u8, address + row_index * 0x10 + column_index);
                                
                                if(context->crash){
                                    print("?? ");
                                }else{
                                    print("%.2x ", byte);
                                }
                            }else{
                                print("   ");
                            }
                            
                            if(column_index == 7) print("- ");
                        }
                        
                        print("   ");
                        
                        u64 column_count = (row_index == row_count - 1) ? (count - row_index * 0x10) : 0x10;
                        
                        for(u64 column_index = 0; column_index < column_count; column_index++){
                            
                            context->crash = CRASH_none;
                            u8 byte = is_phys ? *get_physical_memory_for_read(context, address + row_index * 0x10 + column_index) : guest_read(u8, address + row_index * 0x10 + column_index);
                            
                            if(context->crash){
                                print(".");
                            }else if(32 <= byte && byte <= 126){
                                print("%c", byte);
                            }else{
                                print(".");
                            }
                        }
                        
                        print("\n");
                    }
                    
                }break;
                case 'w':{
                    if(!count) count = 0x40;
                    
                    if(count > 0x4000) count = 0x4000;
                    
                    // @note: 8 words per row.
                    u64 row_count = (count + 0x7)/0x8;
                    
                    for(u64 row_index = 0; row_index < row_count; row_index++){
                        print("%p: ", address + row_index * 0x10);
                        
                        u64 column_count = ((row_index == row_count - 1) ? (count - row_index * 8) : 8);
                        
                        for(u64 column_index = 0; column_index < column_count; column_index++){
                            
                            if(0x8 * row_index + column_index < count){
                                
                                context->crash = CRASH_none;
                                u16 word = guest_read(u16, address + row_index * 0x10 + 2 * column_index);
                                
                                if(context->crash){
                                    print("???? ");
                                }else{
                                    print("%.4x ", word);
                                }
                            }else{
                                print("     ");
                            }
                            
                            if(column_index == 3) print("- ");
                        }
                        print("\n");
                    }
                }break;
                case 'd':{
                    if(!count) count = 0x20;
                    
                    if(count > 0x2000) count = 0x2000;
                    
                    // @note: 4 dword per row.
                    u64 row_count = (count + 0x3)/0x4;
                    
                    for(u64 row_index = 0; row_index < row_count; row_index++){
                        print("%p: ", address + row_index * 0x10);
                        
                        u64 column_count = ((row_index == row_count - 1) ? (count - row_index * 4) : 4);
                        
                        for(u64 column_index = 0; column_index < column_count; column_index++){
                            
                            if(0x4 * row_index + column_index < count){
                                
                                context->crash = CRASH_none;
                                u32 dword = guest_read(u32, address + row_index * 0x10 + 4 * column_index);
                                
                                if(context->crash){
                                    print("???????? ");
                                }else{
                                    print("%.8x ", dword);
                                }
                            }else{
                                print("         ");
                            }
                        }
                        print("\n");
                    }
                }break;
                case 'q':{
                    if(!count) count = 0x10;
                    
                    if(count > 0x1000) count = 0x1000;
                    
                    // @note: 2 qword per row.
                    u64 row_count = (count + 0x1)/0x2;
                    
                    for(u64 row_index = 0; row_index < row_count; row_index++){
                        print("%p: ", address + row_index * 0x10);
                        
                        u64 column_count = ((row_index == row_count - 1) ? (count - row_index * 2) : 2);
                        
                        for(u64 column_index = 0; column_index < column_count; column_index++){
                            
                            if(0x2 * row_index + column_index < count){
                                
                                context->crash = CRASH_none;
                                u64 qword = guest_read(u64, address + row_index * 0x10 + 8 * column_index);
                                
                                if(context->crash){
                                    print("???????????????? ");
                                }else{
                                    print("%.16llx ", qword);
                                }
                            }else{
                                print("                 ");
                            }
                        }
                        print("\n");
                    }
                }break;
                case 'p':{
                    if(!count) count = 0x10;
                    
                    for(u64 row_index = 0; row_index < count; row_index++){
                        print("%p: ", address + row_index * 0x8);
                        
                        context->crash = CRASH_none;
                        u64 qword = guest_read(u64, address + row_index * 8);
                        
                        if(context->crash){
                            print("???????????????? ");
                        }else{
                            print("%p ", qword);
                            print_symbol(context, qword);
                        }
                        print("\n");
                    }
                }break;
            }
            
            context->registers.cr3 = user_cr3;
            
            continue;
        }
        
        if(string_match(command, string("guid"))){
            
            int error = 0;
            u64 address = parse_address(context, &line, &error);
            if(error) continue;
            
            struct guid guid;
            guest_read_size(context, &guid, address, sizeof(guid), PERMISSION_none);
            
            print(PRINT_GUID_FORMAT "\n", PRINT_GUID_MEMBERS(guid));
            continue;
        }
        
        if(string_match(command, string("heap"))){
            
            if(!line.size){
                print("Heap: [%p - %p] at %p (used %p) %.2f\n", globals.big_allocation_base, globals.big_allocation_base + FUZZING_BIG_ALLOCATION_SIZE, globals.big_allocation_base + context->big_allocation_at, context->big_allocation_at, (double)context->big_allocation_at/(double)FUZZING_BIG_ALLOCATION_SIZE);
                print("\n");
                print("For information on a specific address use heap <address>\n");
                continue;
            }else{
                int error = 0;
                u64 address = parse_address(context, &line, &error);
                if(error) continue;
                
                if(globals.big_allocation_base <= address && address <= globals.big_allocation_base + context->big_allocation_at){
                    print("Address is on the heap\n");
                }else if(globals.big_allocation_base <= address && address < globals.big_allocation_base + FUZZING_BIG_ALLOCATION_SIZE){
                    print("Address is on the heap, but not yet allocated.\n");
                    continue;
                }else{
                    print("Address is not on the heap.\n");
                    continue;
                }
                
                print("\n");
                
                for(u64 at = globals.big_allocation_base; at < address; ){
                    
                    u64 size = guest_read(u64, at + 8);
                    u64 aligned_size = ((size + 0xf) & ~0xf) + 0x10;
                    
                    if(at + aligned_size > address){
                        u64 flags = guest_read(u64, at);
                        print("Allocation: %p size: 0x%llx (aligned: 0x%llx) flags: 0x%llx\n\n", at, size, aligned_size, flags);
                        
                        if(aligned_size > FUZZING_ALLOCATION_LIMIT){
                            print("Allocation somehow exceeds `FUZZING_ALLOCATION_LIMIT` this should not be possible, heap corruption..\n");
                        }else{
                            if(size <= 0x80 || yes_no_stop_point("Dump Bytes", /*force*/1)){
                                u8 *bytes = push_data(&context->scratch_arena, u8, size);
                                int success = guest_read_size(context, bytes, at + 0x10, size, PERMISSION_none);
                                if(!success){
                                    print("Failed to read bytes, probably allocation was already freed.\n");
                                }else{
                                    print_byte_range(bytes, size, at);
                                }
                            }
                        }
                    }
                    
                    at += aligned_size;
                }
            }
        }
        
        if(string_match(command, string("b")) || string_match(command, string("bp"))){
            //
            // Set an execution breakpoint on the given address.
            //
            
            parse_breakpoint(context, BREAKPOINT_execute, &line);
            continue;
        }
        
        if(string_match(command, string("bw"))){
            //
            // Set a write breakpoint on the given address.
            //
            
            parse_breakpoint(context, BREAKPOINT_write, &line);
            
            // Makes sure we hit the 'guest_write_size' when reading the address.
            invalidate_translate_lookaside_buffers(context);
            continue;
        }
        
        if(string_match(command, string("br"))){
            //
            // Set a read breakpoint on the given address.
            //
            
            parse_breakpoint(context, BREAKPOINT_read, &line);
            
            // Makes sure we hit the 'guest_read_size' when reading the address.
            invalidate_translate_lookaside_buffers(context);
            continue;
        }
        
        if(string_match(command, string("ba"))){
            //
            // Set an allocation breakpoint on the given address (fires when 'ExAllocatePool' returns this address).
            //
            
            if(context->use_hypervisor){
                print("Hypervisor does not support allocation breakpoints.\n");
                continue;
            }
            
            parse_breakpoint(context, BREAKPOINT_alloc, &line);
            continue;
        }
        
        if(string_match(command, string("bf"))){
            //
            // Set a free breakpoint on the given address (fires when this address is the argument to 'ExFreePool').
            //
            
            if(context->use_hypervisor){
                print("Hypervisor does not support freeing breakpoints.\n");
                continue;
            }
            
            parse_breakpoint(context, BREAKPOINT_free, &line);
            continue;
        }
        
        if(string_match(command, string("blm"))){
            
            if(context->use_hypervisor){
                print("Hypervisor does not support module loading breakpoints.\n");
                continue;
            }
            
            struct string module_name = string_eat_nonwhitespace(&line);
            
            struct loaded_module *module = get_loaded_module(module_name);
            if(module){
                print("Module '%.*s' is already loaded.", module_name.size, module_name.data);
                continue;
            }
            
            if(globals.module_load_breakpoint_string.data) free(globals.module_load_breakpoint_string.data);
            globals.module_load_breakpoint_string.data = malloc(module_name.size + 1);
            globals.module_load_breakpoint_string.size = module_name.size;
            globals.module_load_breakpoint_string.data[module_name.size] = 0;
            memcpy(globals.module_load_breakpoint_string.data, module_name.data, module_name.size);
            
            print("Breaking when '%.*s' is loaded!\n", module_name.size, module_name.data);
            continue;
        }
        
        if(string_match(command, string("brocess"))){
            
            u64 KiKernelSysretExit = get_symbol(context, string("nt!KiKernelSysretExit"));
            struct hook *hook = lookup_hook(KiKernelSysretExit);
            if(!hook){
                register_hook(context, KiKernelSysretExit, KiKernelSysretExit_brocess_hook);
            }else if(hook->hook != KiKernelSysretExit_brocess_hook){
                print("Error: Already have hook at nt!KiKernelSysretExit but its not our hook.\n");
                continue;
            }
            
            struct string module_name = string_eat_nonwhitespace(&line);
            
            if(module_name.size > 15){
                print("Warning: Truncating the name to '%.15s' because the 'nt!_EPROCESS.ImageFileName' is at most 15 bytes.\n");
                module_name.size = 15;
            }
            memcpy(globals.KiKernelSysretExit_process_name, module_name.data, module_name.size);
            globals.KiKernelSysretExit_process_name[module_name.size] = 0;
            continue;
        }
        if(string_match(command, string("bl"))){
            //
            // List all breakpoints.
            //
            
            if(context->use_hypervisor){
                
                for(int breakpoint_index = 0; breakpoint_index < 4; breakpoint_index++){
                    print("[dr%d] ", breakpoint_index);
                    
                    u64 active_bit = 1ull << (1 + 2 * breakpoint_index);
                    u64 address = registers->dr[breakpoint_index];
                    
                    u32 type   = (registers->dr7 >> (16 + 4 * breakpoint_index)) & 0x3;
                    u32 length = (registers->dr7 >> (18 + 4 * breakpoint_index)) & 0x3;
                    
                    if(registers->dr7 & active_bit){
                        print("%p (", address); 
                        print_symbol(context, address);
                        print(")");
                        
                        if(registers->dr6 & (1ull << breakpoint_index)) print(" [hit]");
                        if(globals.breakpoints[0].flags & BREAKPOINT_FLAG_oneshot) print(" [one-shot]");
                        if(type == 0b11) print(" [read]");
                        if(type == 0b01) print(" [write]");
                        
                        if(length == 0b01) print(" [2-byte]");
                        if(length == 0b11) print(" [4-byte]"); // @note: This has some weird swizzle.
                        if(length == 0b10) print(" [8-byte]");
                    }
                    
                    print("\n");
                }
            }else{
                for(int breakpoint_index = 0; breakpoint_index < array_count(globals.breakpoints); breakpoint_index++){
                    if(globals.breakpoints[breakpoint_index].type != BREAKPOINT_none){
                        struct breakpoint breakpoint = globals.breakpoints[breakpoint_index];
                        char *string  = breakpoint_type_to_string[breakpoint.type];
                        
                        print("[%x] %c breakpoint at %p(", breakpoint_index, string[0], breakpoint.address);
                        print_symbol(context, breakpoint.address);
                        print(") for 0x%llx", breakpoint.length);
                        
                        if(breakpoint.flags){
                            print("( ");
                            if(breakpoint.flags & BREAKPOINT_FLAG_oneshot) print("oneshot ");
                            print(")");
                        }
                        print("\n");
                    }
                }
            }
            continue;
        }
        
        if(string_match(command, string("bc"))){
            //
            // Clear breakpoints.
            //
            
            while(line.size){
                
                struct string breakpoint = string_eat_nonwhitespace(&line);
                string_skip_whitespace(&line);
                
                //
                // Optionally, remove a ',' this is so we can do 'bc 1, 2, 3'.
                //
                if(breakpoint.size == 2 && breakpoint.data[1] == ',') breakpoint.size = 1;
                
                if(breakpoint.size != 1){
                    print("Could not parse breakpoint '%.*s'\n", breakpoint.size, breakpoint.data);
                    break;
                }
                
                char breakpoint_character = breakpoint.data[0];
                
                if(breakpoint_character == '*'){
                    if(context->use_hypervisor){
                        registers->dr0 = 0; registers->dr7 &= ~0x02;
                        registers->dr1 = 0; registers->dr7 &= ~0x08;
                        registers->dr2 = 0; registers->dr7 &= ~0x20;
                        registers->dr3 = 0; registers->dr7 &= ~0x80;
                    }else{
                        for(u32 index = 0; index < array_count(globals.breakpoints); index++){
                            clear_breakpoint(index);
                        }
                    }
                    break;
                }
                
                int breakpoint_index = -1;
                
                // Parse the index in hex! we only have breakpoints 0 to F, so its easy to parse!
                if('0' <= breakpoint_character && breakpoint_character <= '9'){
                    breakpoint_index = breakpoint_character - '0';
                }
                
                if('a' <= breakpoint_character && breakpoint_character <= 'f'){
                    breakpoint_index = breakpoint_character - 'a' + 10;
                }
                
                if('A' <= breakpoint_character && breakpoint_character <= 'F'){
                    breakpoint_index = breakpoint_character - 'A' + 10;
                }
                
                if(breakpoint_index != -1){
                    if(context->use_hypervisor){
                        switch(breakpoint_index){
                            case 0: registers->dr0 = 0; registers->dr7 &= ~0x02; break;
                            case 1: registers->dr1 = 0; registers->dr7 &= ~0x08; break;
                            case 2: registers->dr2 = 0; registers->dr7 &= ~0x20; break;
                            case 3: registers->dr3 = 0; registers->dr7 &= ~0x80; break;
                            default:{
                                print("Maximal hypervisor breakpoint is 3, but specified was %d.\n", breakpoint_index);
                            }break;
                        }
                    }else{
                        clear_breakpoint(breakpoint_index);
                    }
                }else{
                    print("Could not parse breakpoint '%.*s'!\n", breakpoint.size, breakpoint.data);
                }
            }
            
            continue;
        }
        
        if(string_match(command, string("process"))){
            //
            // Prints the name of the current process.
            //
            
            u64 kpcr = (registers->cs.selector & 3) ? registers->gs_swap : registers->gs_base;
            
            u64 thread  = guest_read(u64, kpcr   + get_member_offset(context, string("nt!_KPCR.Prcb.CurrentThread")));
            u64 process = guest_read(u64, thread + get_member_offset(context, string("nt!_KTHREAD.ApcState.Process")));
            
            char image_name[16];
            int success = guest_read_size(context, image_name, process + get_member_offset(context, string("nt!_EPROCESS.ImageFileName")), 16, PERMISSION_none);
            
            if(!success){
                print("failed to read gs->thread->process->ImageFileName (%p, %p, %p)\n", kpcr, thread, process);
            }else{
                print("process %p:\n", process);
                print("   Image: %.15s\n", image_name);
                print("   cr3:   %p\n", guest_read(u64, process + get_member_offset(context, string("nt!_KPROCESS.DirectoryTableBase"))));
            }
            
            continue;
        }
        
        if(string_match(command, string("pte"))){
            //
            // Walks the page table for a given address.
            //
            
            int error = 0;
            u64 address = parse_address(context, &line, &error);
            if(error) continue;
            
            u64 offset_in_page = (address >>  0) & 0xfff;
            u32 p1_table_index = (address >> 12) & 0x1ff;
            u32 p2_table_index = (address >> 21) & 0x1ff;
            u32 p3_table_index = (address >> 30) & 0x1ff;
            u32 p4_table_index = (address >> 39) & 0x1ff;
            
            u64 p4_table_offset = registers->cr3 & ~0xfff;
            print("Page Table Root = 0x%llx\n", p4_table_offset);
            u64 p4_entry = read_page_table_entry(context, p4_table_offset + 8 * p4_table_index);
            
            print("P4 Table (%p) Entry %4d: %llx\n", p4_table_offset, p4_table_index, p4_entry);
            if(!(p4_entry & PAGE_TABLE_present)){
                print("  --> P4 entry is not present\n");
                continue;
            }
            
            u64 p3_table_offset = p4_entry & PAGE_TABLE_ENTRY_ADDRESS_MASK;
            u64 p3_entry = read_page_table_entry(context, p3_table_offset + 8 * p3_table_index);
            print("P3 Table (%p) Entry %4d: %llx\n", p3_table_offset, p3_table_index, p3_entry);
            if(!(p3_entry & PAGE_TABLE_present)){
                print("  --> P3 entry is not present\n");
                continue;
            }
            
            if(p3_entry & PAGE_TABLE_large_page){
                u64 physical_address = (p3_entry & PAGE_TABLE_ENTRY_ADDRESS_MASK) + (p2_table_index << 21) + (p1_table_index << 12) + offset_in_page;
                print("  --> Large Page at %p\n", physical_address);
                continue;
            }
            
            u64 p2_table_offset = p3_entry & PAGE_TABLE_ENTRY_ADDRESS_MASK;
            u64 p2_entry = read_page_table_entry(context, p2_table_offset + 8 * p2_table_index);
            print("P2 Table (%p) Entry %4d: %llx (r%s%s)\n", p2_table_offset, p2_table_index, p2_entry, (p2_entry & PAGE_TABLE_writable) ? "w" : "", (p2_entry & PAGE_TABLE_execute_disable) ? "" : "x");
            if(!(p2_entry & PAGE_TABLE_present)){
                print("  --> P2 entry is not present\n");
                continue;
            }
            
            if(p2_entry & PAGE_TABLE_large_page){
                u64 physical_address = (p2_entry & PAGE_TABLE_ENTRY_ADDRESS_MASK) + (p1_table_index << 12) + offset_in_page;
                print("  --> Large Page at %p\n", physical_address);
                continue;
            }
            
            u64 p1_table_offset = p2_entry & PAGE_TABLE_ENTRY_ADDRESS_MASK;
            u64 p1_entry = read_page_table_entry(context, p1_table_offset + 8 * p1_table_index);
            print("P1 Table (%p) Entry %4d: %llx (r%s%s)\n", p1_table_offset, p1_table_index, p1_entry, (p1_entry & PAGE_TABLE_writable) ? "w" : "", (p1_entry & PAGE_TABLE_execute_disable) ? "" : "x");
            if(!(p1_entry & PAGE_TABLE_present)){
                print("  --> P1 entry is not present\n");
                continue;
            }
            
            u64 physical_address = (p1_entry & PAGE_TABLE_ENTRY_ADDRESS_MASK) + offset_in_page;
            print("  --> Page is at %p\n", physical_address);
            
            continue;
        }
        
        if(string_match(command, string("info"))){
            if_we_have_any_information_about_the_current_rip_print_what_we_know(context, registers);
            continue;
        }
        
        if(string_match(command, string("load_module"))){
            
            u64 address = 0;
            
            struct loaded_module *module = null;
            
            if(line.size){
                int error = 0;
                address = parse_address(context, &line, &error);
                if(error) continue;
                
                module = get_module_for_address(address);
            }else{
                address = registers->rip;
                module  = module_at_rip;
            }
            
            u64 original_address = address;
            
            if(module){
                print("Module '%.*s' at %p is already loaded.\n", module->short_name.size, module->short_name.data, address);
                continue;
            }
            
            // 
            // This is mostly here to load modules prior to the kernel booting up.
            // Afterwards, we can use 'PsLoadedModuleList' but for 'winload' we 
            // don't really get a heads up.
            // 
            
            address &= ~0xfff;
            
            for(; !context->crash; address -= 0x1000){
                if(guest_read(u16, address) == 'ZM'){
                    u32 pe_header_offset = guest_read(u32, address + 0x3c);
                    u32 image_size       = guest_read(u32, address + pe_header_offset + 4 + 20 + 56);
                    
                    struct string name = {0};
                    
                    module = parse_loaded_module(context, address, image_size, name);
                    break;
                }
            }
            
            if(module){
                if(!module->tried_to_load_pdb) loaded_module_try_to_load_pdb(context, module);
                
                // Maybe we loaded the module at rip.
                if(!module_at_rip) module_at_rip = get_module_for_address(registers->rip);
            }else{
                print("Could not find module at %p.\n", original_address);
            }
            continue;
        }
        
        if(string_match(command, string("write_coverage_files"))){
            write_coverage_files();
            continue;
        }
        
        if(string_match(command, string("clear_coverage"))){
            print("Clearing Coverage Table!\n");
            context->cached_coverage_page_index = (u64)-1;
            clear_coverage_table();
            
            for(struct loaded_module *module = globals.module_list.first; module; module = module->next){
                module->coverage = 0;
            }
            continue;
        }
        
        if(string_match(command, string("user_modules"))){
            
            u64 address = 0;
            if(line.size){
                int error = 0;
                address = parse_address(context, &line, &error);
                if(error) continue;
                
                print("Searching for user module at %p\n", address);
            }
            
            u64 TIB = (registers->cs.selector & 3) ? registers->gs_base : registers->gs_swap;
            u64 PEB = guest_read(u64, TIB + get_member_offset(context, string("nt!_TEB.ProcessEnvironmentBlock")));
            u64 Ldr = guest_read(u64, PEB + get_member_offset(context, string("nt!_PEB.Ldr")));
            
            print("TIB %p\n", TIB);
            print("PEB %p\n", PEB);
            print("Ldr %p\n", Ldr);
            
            u64 InMemoryOrderModuleList = guest_read(u64, Ldr + get_member_offset(context, string("nt!_PEB_LDR_DATA.InMemoryOrderModuleList")));
            
            u64 DataTableEntryLink = InMemoryOrderModuleList;
            do{
                u64 DataTableEntry = DataTableEntryLink - get_member_offset(context, string("nt!_LDR_DATA_TABLE_ENTRY.InMemoryOrderLinks"));
                
                u64 DllBase = guest_read(u64, DataTableEntry + get_member_offset(context, string("nt!_LDR_DATA_TABLE_ENTRY.DllBase")));
                u32 DllSize = guest_read(u32, DataTableEntry + get_member_offset(context, string("nt!_LDR_DATA_TABLE_ENTRY.SizeOfImage")));
                
                struct unicode_string BaseDllName = {0};
                guest_read_size(context, &BaseDllName, DataTableEntry + get_member_offset(context, string("nt!_LDR_DATA_TABLE_ENTRY.FullDllName")), sizeof(BaseDllName), PERMISSION_none);
                
                char Buffer[0x100] = {0};
                u64 read_size = BaseDllName.length > (array_count(Buffer) - 1) ? array_count(Buffer) - 1 : BaseDllName.length;
                guest_read_size(context, Buffer, BaseDllName.buffer, read_size, PERMISSION_none);
                
                if(address == 0){
                    // Print all of them!
                    print("%p %p %ws\n", DllBase, DllBase + DllSize, Buffer);
                }else if(DllBase <= address && address <= DllBase + DllSize){
                    print("%p %p %ws\n", DllBase, DllBase + DllSize, Buffer);
                    print("   -> Offset 0x%llx\n", address - DllBase);
                }
                
                DataTableEntryLink = guest_read(u64, DataTableEntryLink);
            }while(!context->crash && (DataTableEntryLink != InMemoryOrderModuleList) && DataTableEntryLink);
            
            continue;
        }
        
        if(string_match(command, string("kernel_modules"))){
            if(!nt){
                print("Error: Kernel (ntoskrnl.exe) not loaded yet (or lstar not set yet).\n");
                continue;
            }
            
            u64 PsLoadedModuleList = get_symbol_from_module(context, nt, string("PsLoadedModuleList"));
            
            print("PsLoadedModuleList %p\n", PsLoadedModuleList);
            
            for(u64 entry_guest_address = guest_read(u64, PsLoadedModuleList); !context->crash && entry_guest_address && (entry_guest_address != PsLoadedModuleList); entry_guest_address = guest_read(u64, entry_guest_address)){
                
                u64 image_base = guest_read(u64, entry_guest_address + 6 * 8);
                u64 image_size = guest_read(u64, entry_guest_address + 8 * 8);
                
                struct string name = guest_read_unicode_string(context, &context->scratch_arena, entry_guest_address + 9 * 8);
                
                print("%p %p %.*s\n", image_base, image_base + image_size, name.size, name.data);
            }
            continue;
        }
        
        if(string_match(command, string("load_pdb"))){
            
            if(line.size == 0){
                print("usage: load_pdb <file-name>\n");
                continue;
            }
            
            struct string pdb_name = line;
            if(pdb_name.size > 2 && pdb_name.data[0] == '"' && pdb_name.data[pdb_name.size-1] == '"'){
                pdb_name.data += 1;
                pdb_name.size -= 2;
            }
            
            struct string module_name = string_strip_file_path(pdb_name);
            
            for(smm index = module_name.size - 1; index > 0; index--){
                if(module_name.data[index] == '.'){
                    module_name.size = index;
                    break;
                }
            }
            
            struct loaded_module *loaded_module = get_loaded_module(module_name);
            if(!loaded_module){
                print("Module '%.*s' is not loaded.\n", module_name.size, module_name.data);
                continue;
            }
            
            char *file_name  = push_cstring_from_string(&context->scratch_arena, pdb_name);
            struct file file = load_file(file_name);
            if(!file.data){
                print("Error: failed to load '%s'\n", file_name);
                continue;
            }
            
            struct pdb_context *pdb_context = load_pdb(file);
            if(pdb_context){
                loaded_module->pdb_context = pdb_context;
            }
            
            free(file.data); // The .pdb was copied by 'load_pdb'.
            
            continue;
        }
        
        if(string_match(command, string("snapshot"))){
            
            if(line.size == 0){
                print("usage: snapshot <file-name>\n");
                continue;
            }
            
            struct string snapshot_name = line;
            if(snapshot_name.size > 2 && snapshot_name.data[0] == '"' && snapshot_name.data[snapshot_name.size-1] == '"'){
                snapshot_name.data += 1;
                snapshot_name.size -= 2;
            }
            
            char *file_name = push_cstring_from_string(&context->scratch_arena, snapshot_name);
            
            write_snapshot(context, file_name);
            continue;
        }
        
        if(string_match(command, string("write"))){
            
            int error = 0;
            u64 address = parse_address(context, &line, &error);
            if(error) continue;
            
            while(line.size >= 2){
                struct string line_save = line;
                u64 byte = parse_address(context, &line, &error);
                if(error || byte > 0xff){
                    print("Error: Unable to parse byte at '%.*s'.\n", line_save.size, line_save.data);
                    break;
                }
                
                u8 *write_to = translate_address(context, address, PERMISSION_none);
                if(!write_to){
                    print("Error: Address %p is not writeable.\n", address);
                    break;
                }
                
                *write_to = (u8)byte;
                address += 1;
            }
            
            continue;
        }
        
        if(string_match(command, string("irp"))){
            if(!nt || !nt->pdb_context){
                print("Error: Kernel (ntoskrnl.exe) not loaded yet (or lstar not set yet).\n");
                continue;
            }
            
            int error = 0;
            u64 IrpAddress = parse_address(context, &line, &error);
            if(error) continue;
            
            print_irp(context, nt, IrpAddress);
            continue;
        }
        
        if(string_match(command, string("mdl"))){
            if(!nt || !nt->pdb_context){
                print("Error: Kernel (ntoskrnl.exe) not loaded yet (or lstar not set yet).\n");
                continue;
            }
            
            int error = 0;
            u64 MdlAddress = parse_address(context, &line, &error);
            if(error) continue;
            
            print_mdl(context, nt, MdlAddress);
            continue;
        }
        
        //
        // Everything above this should have an entry in 'help'.
        //
        
        if(string_match(command, string("help")) || string_match(command, string("h"))){
            print("Execution Commands:\n");
            print("    g - Continue execution.\n");
            print("    s - Single step instruction.\n");
            print("    n - Step over function call.\n");
            print("    f - Finish function.\n");
            print("\n");
            print("Breakpoint Commands:\n");
            print("    b, bp   - Set an execution breakpoint at the given address.\n");
            print("    br      - Set a read breakpoint at the given address.\n");
            print("    bw      - Set a write breakpoint at the given address.\n");
            print("    ba      - Set an allocation breakpoint at the given address. (Fires when address is allocated.)\n");
            print("    bf      - Set a free breakpoint at the given address. (Fires when address is freed.)\n");
            print("              (ba and bf are only usable if the target specific code has registered memory allocation hooks.)\n");
            print("    blm     - Break if a module is loaded. (e.g.: 'blm nt')\n");
            print("    bl      - List all breakpoint.\n");
            print("    bc <bp> - Clears the breakpoint <bp>, <bp> can be '*' to clear all breakpoints.\n");
            print("\n");
            print("Print Commands:\n");
            print("    pm <mode>      - Specifies the current print mode. Affects 'r' and 't' command.\n");
            print("    r [reg]        - Prints a specific register, or all if none is specified. (Depended on the print mode.)\n");
            print("    t              - Enables or disables tracing.\n");
            print("    x, ? <address> - Prints information about a given address.\n");
            print("    m, lm          - Prints information about all loaded modules.\n");
            print("    k              - Prints a stack trace.\n");
            print("    u <address>    - Prints disassembly at a given address.\n");
            print("\n");
            print("Dump Commands:\n");
            print("    db <address> <count> - Prints bytes at a given address.\n");
            print("    dw <address> <count> - Prints words at a given address.\n");
            print("    dd <address> <count> - Prints dwords at a given address.\n");
            print("    dq <address> <count> - Prints qwords at a given address.\n");
            print("    dp,dps <address>     - Prints pointers at a given address.\n");
            print("    dt <type> [address]  - Print type at a given address.\n");
            print("\n");
            print("Semantic Commands:\n");
            print("    snapshot <file-name>    - Creates a snapshot of the current state and saves it under '<file-name>.snapshot'.\n");
            print("    write <address> <bytes> - Write <bytes> to <address>. (e.g.: 'write CI!g_CiOptions 00')\n");
            print("    pte <address>           - Walks the page table for a given address.\n");
            print("    process                 - Prints the image name based on the _EPROCESS structure.\n");
            print("    info                    - Prints any known information if the current rip is a known function\n");
            print("                              (e.g.: nt!NtDeviceIoControlFile).\n");
            print("    user_modules            - Print user modules based on the '_PEB'.\n");
            print("    kernel_modules          - Print kernel modules based on the 'nt!PsLoadedModuleList'.\n");
            print("    load_module [<address>] - Loads a module by walking page-wise backwards until it finds an 'MZ' signature.\n");
            print("    load_pdb <pdb-file>     - Loads the specified pdb and uses it for the module of the same name.\n");
            print("    write_coverage_files    - Writes the current state of coverage to the coverage files.\n");
            print("    clear_coverage          - Clear all current coverage information.\n");
            print("\n");
            continue;
        }
        
        
        if(string_match(command, string("script"))){
            
            if(string_match(line, string("nt"))){
                script.active = 1;
                script.script = string(
                        "bp bootx64!Archpx64TransferTo64BitApplicationAsm + a4\n"
                        "g\n"
                        "s\n"
                        "load_module\n"
                        "bp winload_prod!OslArchTransferToKernel + 78\n"
                        "g\n"
                        "s\n"
                        "load_module\n"
                        "bc *\n"
                        "load_boot_modules rcx\n");
            }else{
                print("Unknown script. Currently only nt.\n");
            }
            
            continue;
        }
        
        if(string_match(command, string("lock_user_modules"))){
            
            if((s64)registers->rip < 0){
                print("Error: lock_user_modules can only be executed while in user space.\n");
                continue;
            }
            
            void lock_userspace_module_memory(struct context *context);
            
            struct registers save = context->registers;
            
            int depth = context->skip_setting_permission_bits;
            s64 fuzz_case_timeout = context->fuzz_case_timeout;
            int use_hypervisor = context->use_hypervisor;
            
            context->skip_setting_permission_bits = 0;
            context->fuzz_case_timeout = 0x7fffffffffffffff;
            context->use_hypervisor = 0;
            
            lock_userspace_module_memory(context);
            
            context->skip_setting_permission_bits = depth;
            context->fuzz_case_timeout = fuzz_case_timeout;
            context->use_hypervisor = use_hypervisor;
            
            context->registers = save;
            continue;
        }
        
        
        if(string_match(command, string("load_boot_modules"))){
            
            u64 KeLoaderBlock;
            
            if(line.size){
                int error = 0;
                KeLoaderBlock = parse_address(context, &line, &error);
                if(error) continue;
            }else{
                if(!nt){
                    print("Error: Kernel (ntoskrnl.exe) not loaded yet (or lstar not set yet).\n");
                    continue;
                }
                
                KeLoaderBlock = guest_read(u64, get_symbol_from_module(context, nt, string("KeLoaderBlock")));
            }
            
            for(u64 entry_guest_address = guest_read(u64, KeLoaderBlock + 0x10); entry_guest_address && (entry_guest_address != KeLoaderBlock + 0x10); entry_guest_address = guest_read(u64, entry_guest_address)){
                
                u64 image_base = guest_read(u64, entry_guest_address + 6 * 8);
                u64 image_size = guest_read(u64, entry_guest_address + 8 * 8);
                
                struct string name = guest_read_unicode_string(context, &context->scratch_arena, entry_guest_address + 9 * 8);
                
                parse_loaded_module(context, image_base, image_size, name);
            }
            
            continue;
        }
        
        //
        // After this point there are things you only really care about if you are debugging specific internals.
        //
        
        if(string_match(command, string("KeLoaderBlock"))){
            if(!nt){
                print("Error: Kernel (ntoskrnl.exe) not loaded yet (or lstar not set yet).\n");
                continue;
            }
            
            u64 KeLoaderBlock = guest_read(u64, get_symbol_from_module(context, nt, string("KeLoaderBlock")));
            
            print("KeLoaderBlock %p\n\n", KeLoaderBlock);
            
            u8 *current = context->scratch_arena.current;
            
            print("LoadOrderList:\n"); // _KLDR_DATA_TABLE_ENTRY
            for(u64 entry_guest_address = guest_read(u64, KeLoaderBlock + 0x10); entry_guest_address && (entry_guest_address != KeLoaderBlock + 0x10); entry_guest_address = guest_read(u64, entry_guest_address)){
                
                u64 image_base = guest_read(u64, entry_guest_address + 6 * 8);
                u64 image_size = guest_read(u64, entry_guest_address + 8 * 8);
                
                struct string name = guest_read_unicode_string(context, &context->scratch_arena, entry_guest_address + 9 * 8);
                
                print("%p %p %.*s\n", image_base, image_base + image_size, name.size, name.data);
            }
            print("\n");
            
            print("BootDriverList:\n"); // _BOOT_DRIVER_LIST_ENTRY 
            for(u64 entry_guest_address = guest_read(u64, KeLoaderBlock + 0x30); entry_guest_address && (entry_guest_address != KeLoaderBlock + 0x30); entry_guest_address = guest_read(u64, entry_guest_address)){
                
                struct string name = guest_read_unicode_string(context, &context->scratch_arena, entry_guest_address + 0x10);
                
                print("   %.*s\n", name.size, name.data);
            }
            print("\n");
            
            print("EarlyLaunch:\n"); // _BOOT_DRIVER_LIST_ENTRY 
            for(u64 entry_guest_address = guest_read(u64, KeLoaderBlock + 0x40); entry_guest_address && (entry_guest_address != KeLoaderBlock + 0x40); entry_guest_address = guest_read(u64, entry_guest_address)){
                
                struct string name = guest_read_unicode_string(context, &context->scratch_arena, entry_guest_address + 0x10);
                
                print("   %.*s\n", name.size, name.data);
            }
            print("\n");
            
            print("CoreDriver:\n"); // _BOOT_DRIVER_LIST_ENTRY 
            for(u64 entry_guest_address = guest_read(u64, KeLoaderBlock + 0x50); entry_guest_address && (entry_guest_address != KeLoaderBlock + 0x50); entry_guest_address = guest_read(u64, entry_guest_address)){
                
                struct string name = guest_read_unicode_string(context, &context->scratch_arena, entry_guest_address + 0x10);
                
                print("   %.*s\n", name.size, name.data);
            }
            print("\n");
            
            context->scratch_arena.current = current;
            
            continue;
        }
        
        if(string_match(command, string("handles"))){
            
            // 
            // Get the _HANDLE_TABLE of the current process.
            // 
            
            u64 kpcr = (context->registers.cs.selector & 3) ? context->registers.gs_swap : context->registers.gs_base;
            u64 cr3 = patch_in_kernel_cr3(context);
            
            u64 thread  = guest_read(u64, kpcr   + get_member_offset(context, string("nt!_KPCR.Prcb.CurrentThread")));
            u64 process = guest_read(u64, thread + get_member_offset(context, string("nt!_KTHREAD.ApcState.Process")));
            
            u64 ObjectTable = guest_read(u64, process + get_member_offset(context, string("nt!_EPROCESS.ObjectTable")));
            
            u64 HandleTableFlink = get_member_offset(context, string("nt!_HANDLE_TABLE.HandleTableList.Flink"));
            
            print("cr3 %p, kpcr %p, thread %p, process %p, object table %p\n", cr3, kpcr, thread, process, ObjectTable);
            
            u64 HandleTableListEntry = ObjectTable + HandleTableFlink;
            do{
                u64 HandleTableEntry = HandleTableListEntry - HandleTableFlink;
                
                u64 TableCode = guest_read(u64, HandleTableEntry + get_member_offset(context, string("nt!_HANDLE_TABLE.TableCode")));
                print("HandleTable %p, TableCode %p\n", HandleTableEntry, TableCode);
                
                u64 NextHandleNeedingPool = guest_read(u64, HandleTableEntry + get_member_offset(context, string("nt!_HANDLE_TABLE.NextHandleNeedingPool")));
                
                for(u32 handle_index = 0; handle_index < NextHandleNeedingPool; handle_index += 4){
                    
                    u64 handle_information = 0;
                    
                    // TableCode & 3 appears to be the table depth.
                    if((TableCode & 3) == 0){
                        handle_information = TableCode + handle_index * 4;
                    }else if((TableCode & 3) == 1){
                        u64 inner = guest_read(u64, (TableCode-1) + (handle_index >> 10) * 8);
                        handle_information = inner + (handle_index & 0x3ff) * 4;
                    }else {
                        u64 inner1 = guest_read(u64, (TableCode - 2) + (handle_index >> 0x13) * 8);
                        u64 inner2 = guest_read(u64, inner1 + ((handle_index >> 10) & 0x1ff) * 8);
                        handle_information = inner2 + (handle_index & 0x3ff) * 4;
                    }
                    
                    struct{
                        u64 Unlocked : 1;
                        u64 RefCount : 16;
                        u64 Attributes : 3;
                        u64 ObjectPointerBits : 44;
                        u32 GrantedAccessBits : 25;
                        u32 NoRightsUpgrade : 1;
                        u32 Spare1 : 6;
                        u32 Spare2;
                    } handle_table_entry;
                    
                    int success = guest_read_size(context, &handle_table_entry, handle_information, sizeof(handle_table_entry), PERMISSION_read);
                    if(!success){
                        print("Failed to read handle information at %p\n", handle_information);
                        break;
                    }
                    
                    if(handle_table_entry.ObjectPointerBits){
                        u64 ObjectPointer = (handle_table_entry.ObjectPointerBits << 4) | (0xffffull << 48);
                        print("[0x%llx] Object: %p handle info: %p\n", handle_index, ObjectPointer, handle_information);
                    }else{
                        print("[0x%llx] handle info: %p\n", handle_index, handle_information);
                    }
                    
                }
                
                HandleTableListEntry = guest_read(u64, HandleTableListEntry);
            } while(HandleTableListEntry != ObjectTable && 0); // @cleanup: We oncly iterate the first one, as it seems to me that that is the top-level table and all the otherones are lower level tables referenced by it?
            
            context->registers.cr3 = cr3;
            continue;
        }
        
        
        if(string_match(command, string("threads"))){
            
            u64 kpcr  = (context->registers.cs.selector & 3) ? context->registers.gs_swap : context->registers.gs_base;
            u64 kprcb = kpcr + get_member_offset(context, string("nt!_KPCR.Prcb"));
            u64 cr3 = patch_in_kernel_cr3(context);
            
            u64 current_thread = guest_read(u64, kpcr + get_member_offset(context, string("nt!_KPCR.Prcb.CurrentThread")));
            u64 process = guest_read(u64, current_thread + get_member_offset(context, string("nt!_KTHREAD.ApcState.Process")));
            
            struct {
                char *name;
                u64 list_entry_offset;
                u64 list_start;
            } thread_lists[] = {
                {
                    "Ready Threads",
                    .list_entry_offset = get_member_offset(context, string("nt!_KTHREAD.WaitListEntry.Flink")),
                    .list_start = process + get_member_offset(context, string("nt!_KPROCESS.ReadyListHead")),
                },
#if 0                
                {
                    "Waiting Threads",
                    .list_entry_offset = get_member_offset(context, string("nt!_KTHREAD.WaitListEntry.Flink")),
                    .list_start = kprcb + get_member_offset(context, string("nt!_KPRCB.WaitListHead")),
                },
#endif
                {
                    "All Threads",
                    .list_entry_offset = get_member_offset(context, string("nt!_ETHREAD.ThreadListEntry.Flink")),
                    .list_start = process + get_member_offset(context, string("nt!_EPROCESS.ThreadListHead")),
                },
            };
            (void)kprcb;
            // BoostList?
            // DeboostList?
            // KiDispatcherReadyListHead
            
            for(u32 list_index = 0; list_index < array_count(thread_lists); list_index++){
                
                u64 list_entry_offset = thread_lists[list_index].list_entry_offset;
                u64 thread_list_head = thread_lists[list_index].list_start;
                
                print("\n\n%s:\n", thread_lists[list_index].name);
                
                for(u64 thread_list_entry = guest_read(u64, thread_lists[list_index].list_start); (thread_list_entry != thread_list_head) && !context->crash; thread_list_entry = guest_read(u64, thread_list_entry)){
                    u64 thread = thread_list_entry - list_entry_offset;
                    
                    u8 state = guest_read(u8, thread + get_member_offset(context, string("nt!_KTHREAD.State")));
                    static char *thread_state_strings[] = {
                        [0] = "Initialized",
                        [1] = "Ready",
                        [2] = "Running",
                        [3] = "Standby",
                        [4] = "Terminated",
                        [5] = "Waiting",
                        [6] = "Transition",
                        [7] = "DeferredReady",
                        [8] = "GateWait",
                    };
                    
                    
                    u8 BasePriority = guest_read(u8, thread + get_member_offset(context, string("nt!_KTHREAD.BasePriority")));
                    u8 Priority = guest_read(u8, thread + get_member_offset(context, string("nt!_KTHREAD.Priority")));
                    s16 PriorityDecrement = guest_read(s16, thread + get_member_offset(context, string("nt!_KTHREAD.PriorityDecrement")));
                    s16 ForegroundBoost = PriorityDecrement & 0xf;
                    s16 UnusualBoost = (PriorityDecrement >> 4) & 0xff;
                    
                    // u32 MiscFlags = guest_read(u32, thread + get_member_offset(context, string("nt!_KTHREAD.MiscFlags")));
                    
                    struct{
                        u64 UniqueProcess;
                        u64 UniqueThread;
                    } Cid;
                    
                    guest_read_size(context, &Cid, thread + get_member_offset(context, string("nt!_ETHREAD.Cid")), sizeof(Cid), PERMISSION_none);
                    
                    char *thread_state_string = (state < array_count(thread_state_strings)) ? thread_state_strings[state] : "???";
                    print("%.4llx.%.4llx (%p) State: %-10s (%d) Priority: %2d (%d + %d + %d) %s\n", Cid.UniqueProcess, Cid.UniqueThread, thread, thread_state_string, state, Priority, BasePriority, ForegroundBoost, UnusualBoost, thread == current_thread ? "[*]" : "");
                    
                    u64 thread_name = guest_read(u64, thread + get_member_offset(context, string("nt!_ETHREAD.ThreadName")));
                    if(thread_name){
                        print("ThreadName: %p\n", thread_name);
                    }
                    
                    
                    // u64 StartAddress = guest_read(u64, thread + get_member_offset(context, string("nt!_ETHREAD.StartAddress")));
                    // print("StartAddress: %p (", StartAddress); print_symbol(context, StartAddress); print(")\n");
                    
                    
                }
            }
            
            context->registers.cr3 = cr3;
            continue;
        }
        
        
        if(string_match(command, string("exec_0xcc"))){
#if _WIN32
            __debugbreak();
#else
            __asm__ volatile("int3");
#endif
            continue;
        }
        
        if(string_match(command, string("apic"))){
            //
            // Print information about the apic.
            //
            
            print("apic base %p\n\n", registers->ia32_apic_base);
            
            print("Interrupts in service: ");
            for(u32 index = 0; index < 256; index++){
                if(registers->local_apic.in_service_register[index/32] & (1u << (index % 32))){
                    print("%x ", index);
                }
            }
            print("\n");
            print("highest interrupt in service: %x\n", registers->local_apic.highest_interrupt_in_service);
            
            print("Interrupts requested: ");
            for(u32 index = 0; index < 256; index++){
                if(registers->local_apic.interrupt_request_register[index/32] & (1u << (index % 32))){
                    print("%x ", index);
                }
            }
            print("\n");
            print("highest pending interrupt:    %x\n", registers->local_apic.highest_pending_interrupt);
            
            
            continue;
        }
        
        if(string_match(command, string("tlb"))){
            
            u64 address = 0;
            if(line.size){
                int error = 0;
                address = parse_address(context, &line, &error);
                if(error) continue;
                
                print("Address: %p\n", address);
            }else{
                print("Expected guest virtual address\n");
                continue;
            }
            
            u64 page_number = address >> 12;
            print("page_number %p\n", page_number);
            
            u64 pte;
            u64 physical_address = translate_page_number_to_physical(context, page_number, PERMISSION_none, &pte);
            print("physical_address %p pte %p\n", physical_address, pte);
            
            if(pte & PAGE_TABLE_present){
                assert(physical_address < context->physical_memory_size);
                
                u64 page_index = physical_address >> 12;
                u64 byte_index = page_index >> 3;
                u64 bit_index  = page_index & 7;
                
                u64 bit = 1ull << bit_index;
                
                int page_is_present = (context->physical_memory_copied[byte_index] & bit) != 0;
                
                if(page_is_present){
                    print("page_copied: %p (original %p)\n", context->physical_memory + physical_address, globals.snapshot.physical_memory + physical_address);
                }else{
                    print("page not copied: %p\n", globals.snapshot.physical_memory + physical_address);
                }
                
            }else{
                print("(not present)\n");
            }
            
            
            {
                struct translation_lookaside_buffer_entry *tlb_entry = &context->read_tlb.entries[page_number & (array_count(context->read_tlb.entries) - 1)];
                print("read tlb:\n");
                print("    virtual page number   %p\n", tlb_entry->virtual_page_number);
                print("    host_page_address     %p (%p)\n", tlb_entry->host_page_address, tlb_entry->host_page_address - context->physical_memory);
                print("    extra_permission_page %p\n", tlb_entry->extra_permission_page);
            }
            
            {
                struct translation_lookaside_buffer_entry *tlb_entry = &context->write_tlb.entries[page_number & (array_count(context->write_tlb.entries) - 1)];
                print("write tlb:\n");
                print("    virtual page number   %p\n", tlb_entry->virtual_page_number);
                print("    host_page_address     %p (%p)\n", tlb_entry->host_page_address, tlb_entry->host_page_address - context->physical_memory);
                print("    extra_permission_page %p\n", tlb_entry->extra_permission_page);
            }
            
            {
                struct translation_lookaside_buffer_entry *tlb_entry = &context->execute_tlb.entries[page_number & (array_count(context->execute_tlb.entries) - 1)];
                print("execute tlb:\n");
                print("    virtual page number   %p\n", tlb_entry->virtual_page_number);
                print("    host_page_address     %p (%p)\n", tlb_entry->host_page_address, tlb_entry->host_page_address - context->physical_memory);
                print("    extra_permission_page %p\n", tlb_entry->extra_permission_page);
            }
            continue;
        }
        
        if(string_match(command, string("idt"))){
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
            } idt[0x100];
            
            int success = guest_read_size(context, idt, registers->idt_base, sizeof(idt), PERMISSION_none);
            if(!success){
                print("Unable to read idt at %p\n", registers->idt_base);
                continue;
            }
            
            
            for(u32 index = 0; index < array_count(idt); index++){
                
                struct _KIDTENTRY64 idt_entry = idt[index];
                
                u64 offset = ((u64)idt_entry.OffsetHigh << 32) + ((u64)idt_entry.OffsetMiddle << 16) + idt_entry.OffsetLow;
                u64 KiIsrThunk = get_symbol(context, string("nt!KiIsrThunk"));
                
                
                if(KiIsrThunk <= offset && offset < KiIsrThunk + 0x800){
                    //
                    // Get the interrupt from _KPRCB.InterruptObject.
                    //
                    u64 kpcr  = (registers->cs.selector & 3) ? registers->gs_swap : registers->gs_base;
                    u64 InterruptObject = guest_read(u64, kpcr + get_member_offset(context, string("nt!_KPCR.Prcb.InterruptObject")) + index * 8);
                    u64 ServiceRoutine  = guest_read(u64, InterruptObject + get_member_offset(context, string("nt!_KINTERRUPT.ServiceRoutine")));
                    
                    if(ServiceRoutine){
                        print("[%.2x] ", index); print_symbol(context, offset); print(" ("); print_symbol(context, ServiceRoutine); print(")\n");
                    }
                }else{
                    print("[%.2x] ", index); print_symbol(context, offset); print("\n");
                }
                
            }
            continue;
        }
        
        if(string_match(command, string("vmbus"))){
            
            print("monitor_page1 = %p\n", context->vmbus.monitor_page1);
            print("monitor_page2 = %p\n", context->vmbus.monitor_page2);
            
            print("Channels:\n");
            for(struct vmbus_channel *channel = context->vmbus.channels; channel; channel = channel->next){
                
                char *device_kind_string = "???";
                if(channel->device_kind == VMBUS_DEVICE_unknown)     device_kind_string = "unknown";
                if(channel->device_kind == VMBUS_DEVICE_scsi)        device_kind_string = "scsi";
                if(channel->device_kind == VMBUS_DEVICE_mouse)       device_kind_string = "mouse";
                if(channel->device_kind == VMBUS_DEVICE_keyboard)    device_kind_string = "keyboard";
                if(channel->device_kind == VMBUS_DEVICE_framebuffer) device_kind_string = "framebuffer";
                
                print("[0x%x] = {\n", channel->channel_id);
                print("    .device_kind = %s\n", device_kind_string);
                print("    .monitor_id  = %d\n", channel->monitor_id);
                print("    .gpadl_id    = 0x%x\n", channel->gpadl_id);
                print("    .read_buffer(header %p):\n", channel->read_buffer.header);
                for(u32 index = 0; index < channel->read_buffer.amount_of_pages; index++){
                    print("        [%u] = %p,\n", index, channel->read_buffer.pages[index]);
                }
                print("    .send_buffer(header %p):\n", channel->send_buffer.header);
                for(u32 index = 0; index < channel->send_buffer.amount_of_pages; index++){
                    print("        [%u] = %p,\n", index, channel->send_buffer.pages[index]);
                }
                print("}\n");
            }
            
            print("Gpadls:\n");
            for(struct gpadl *gpadl = context->vmbus.gpadls; gpadl; gpadl = gpadl->next){
                print("[0x%x] = {\n", gpadl->gpadl_id);
                print("    .channel_id = %x\n", gpadl->channel_id);
                print("    .pages:\n");
                for(u32 index = 0; index < gpadl->amount_of_pages; index++){
                    print("        [%u] = %p,\n", index, gpadl->pages[index]);
                }
                print("}\n");
            }
            
            continue;
        }
        
        if(string_match(command, string("timeout"))){
            // 
            // Print the timeout value.
            // 
            if(globals.fuzzing){
                print("Timeout current: %llu\n", context->fuzz_case_timeout);
                print("Timeout start:   %llu\n", FUZZ_CASE_TIMEOUT);
                print("Timeout passed:  %llu\n", FUZZ_CASE_TIMEOUT - context->fuzz_case_timeout);
            }else{
                print("Uptime: %llu\n", 0x7fffffffffffffff - context->fuzz_case_timeout);
            }
            continue;
        }
        
        print("Unknown command '%.*s'. See 'help' for list of commands.\n", command.size, command.data);
        
    } // while(true)
    
    
    if(globals.print_trace) globals.single_stepping = 1;
    
    if(!context->use_hypervisor){
        // If the breakpoint we are currently at did not change, skip it when we get back to it!
        // This is our hacky implementation of the RF flag.
        if(globals.breakpoint_hit_index >= 0 && memcmp(&breakpoint_hit, &globals.breakpoints[globals.breakpoint_hit_index], sizeof(breakpoint_hit)) == 0){
            context->jit_skip_one_breakpoint = 1;
        }
    }
    
    exit_debugging_routine(context, original_crash_information);
    
    globals.breakpoint_hit_index = -1;
    globals.in_debugger    = false;
    snapshot_mode_currently_in_debugger = false;
}


