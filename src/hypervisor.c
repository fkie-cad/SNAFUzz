
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

int hacky_display_input_handling(struct context *context){
    
    if(events_processed == events_initiated) return 0;
    
    //
    // Check for pending keyboard/mouse updates.
    //
    
    struct hacky_event event = event_buffer[events_processed % array_count(event_buffer)];
    events_processed++;
    
    switch(event.kind){
        
        case HACKY_EVENT_key_event:{
            
            if(!context->vmbus.keyboard) return 0; // @cleanup:
            
            u16 keycode = event.keycode;
            
            if(PRINT_INPUT_EVENTS || PRINT_HOOK_EVENTS) print("[input] Send key%s \n", ((keycode >> 8) & 2) ? "down" : "up");
            
            struct keystroke{
                struct vmbus_packet_description description;
                u32 type;
                u16 make_code;
                u16 __padding;
                u32 information;
                u32 __padding2;
            } keystroke = {
                .description = {
                    .PacketType = 6,
                    .PacketDataOffsetDiv8 = offset_in_type(struct keystroke, type) / 8,
                    .PacketLengthDiv8 = sizeof(keystroke) / 8,
                },
                
                .type = /*SYNTH_KBD_EVENT*/3,
                .make_code = (u8)keycode,
                .information = (keycode >> 8),
            }; 
            
            vmbus_send_packet(context, context->vmbus.keyboard, &keystroke.description);
            return 1;
        }break;
        
        case HACKY_EVENT_mouse_move:
        case HACKY_EVENT_mouse_event:{
            if(!context->vmbus.mouse) return 0; // @cleanup:
            
            if(PRINT_INPUT_EVENTS || PRINT_HOOK_EVENTS) print("[input] Send mouse event {.x = 0x%x .y = 0x%x, .z = 0x%x, .button = 0x%x}\n", 
                    event.mouse_x, event.mouse_y, event.wheel, event.button);
            
            struct mouse_event{
                struct vmbus_packet_description description;
                struct pipe_msg{
                    u32 type;
                    u32 size;
                } pipe_msg;
                struct hid_msg{
                    u32 type;
                    u32 size;
                } hid_msg;
                
                //
                // Absolutely positioned hid mouse according to this random commit of a random project: 
                //     https://github.com/hathach/tinyusb/pull/1363/files/8c79b8924eabf441f40a8ce3cab8828688575b6d
                //
                
                u8 button;
                
                // These are unaligned -.-
                u8 mouse_x_low;
                u8 mouse_x_high;
                u8 mouse_y_low;
                u8 mouse_y_high;
                
                u8 wheel_low;
                u8 wheel_high;
                // u8 pan; // Not sure what this is :)
                
                u8 unused;
            } mouse_event = {
                .description = {
                    .PacketType = 6,
                    .PacketDataOffsetDiv8 = offset_in_type(struct mouse_event, pipe_msg) / 8,
                    .PacketLengthDiv8 = sizeof(mouse_event) / 8,
                },
                .pipe_msg = {
                    .type = /*PIPE_MESSAGE_DATA*/1,
                    .size = sizeof(mouse_event) - sizeof(mouse_event.description) - sizeof(mouse_event.pipe_msg),
                },
                
                .hid_msg = {
                    .type = /*SYNTH_HID_INPUT_REPORT*/4,
                    .size = 7,
                },
                
                .button = event.button,
                .mouse_x_low  = (u8)(event.mouse_x >> 0),
                .mouse_x_high = (u8)(event.mouse_x >> 8),
                .mouse_y_low  = (u8)(event.mouse_y >> 0),
                .mouse_y_high = (u8)(event.mouse_y >> 8),
                .wheel_low  = (u8)(event.wheel >> 0),
                .wheel_high = (u8)(event.wheel >> 8),
            };
            
            vmbus_send_packet(context, context->vmbus.mouse, &mouse_event.description);
            
            return 1;
        }break;
    }
    
    return 0;
}


