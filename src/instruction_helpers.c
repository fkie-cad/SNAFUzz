// 
// Instruction helpers are functions which are called from the jit 
// or the hypervisor, to implement more complicated instructions.
// Some helpers are only called by the jit, e.g.: xsave_helper,
// as the hypervisor implements them, but some, such as
// 'helper_cpuid' are called by both the hypervisor and the jit. 
// 
// Most communication from the guest to host runs through
// a routine in this file, e.g.: helper_wrmsr, helper_vmcall, etc.
// 
// Also see:
//     emit_call_to_helper
//                                              
//                                       - Pascal Beyer 29.02.2024

//_____________________________________________________________________________________________________________________
// XSAVE / XRSTOR :XSAVE/XRSTOR

void xrstors_helper(struct context *context, struct registers *registers, u64 xsave_area_guest_address){
    
    struct xsave_area xsave_area = {0};
    
    // @cleanup: I am loading the whole size, excluding the padding at the end, as it crashed because of the padding.
    //           In the future maybe one should first only load the header and find out which components are present.
    //           Then after that we could only load these components.
    int success = guest_read_size(context, &xsave_area, xsave_area_guest_address, sizeof(xsave_area) - sizeof(xsave_area.padding), PERMISSION_read);
    if(!success) return;
    
    u64 requested_feature_bitmap = (registers->xcr0 /*+ registers->IA32_XSS*/) & ((registers->rdx << 32) | (u32)registers->rax);
    
    if(!(xsave_area.xcomp_bv & 0x8000000000000000)){
        set_crash_information(context, CRASH_non_canonical, xsave_area_guest_address); // @cleanup: non-canonical so we get #GP
    }
    
    u64 format = xsave_area.xcomp_bv & 0x7fffffffffffffff;
    
    // Restore all features which are 
    //     1) Requested
    //     2) Allowed by the format
    //     3) Have the mask bit set
    u64 to_restore = format & requested_feature_bitmap & xsave_area.xstate_bv;
    
    // Initialize all features which are
    //    1) Requested, but masked
    //    2) Requested, but not in the format
    u64 to_initialize = (requested_feature_bitmap & ~xsave_area.xstate_bv) | (requested_feature_bitmap & ~format);
    
    // The bits in these vectors are:
    //     Bit 0 corresponds to the state component used for the x87 FPU execution environment (x87 state).
    //     Bit 1 corresponds to the state component used for registers used by the SIMD extension (SSE state).
    //     Bit 2 corresponds to the state component used for the additional register state used by the Intel (R) Advanced Vector Extensions (AVX state).
    
    if(to_restore & 1){
        //
        // Load x87 state.
        //
        
        registers->fpu_control_word = (xsave_area.fpu_control_word & 0x1f3f) | (1 << 6);
        registers->fpu_status_word  = xsave_area.fpu_status_word;
        registers->fpu_tag_word     = xsave_area.fpu_tag_word;
        
        registers->fpu_instruction_pointer = xsave_area.fpu_instruction_pointer;
        registers->fpu_data_pointer        = xsave_area.fpu_data_pointer;
        
        registers->mxcsr = xsave_area.mxcsr;
        // registers->mxcsr_mask = xsave_area.mxcsr_mask; "XRSTOR and XRSTORS ignore this field."
        
        registers->xinuse |= 1;
        
    }else if(to_initialize & 1){
        //
        // Initialize x87 state.
        //
        //   fpu_control_word 49
        //   fpu_status_word 0
        //   fpu_tag_word 0
        //   fpu_instruction_pointer 0
        //   fpu_data_pointer 0
        //   mxcsr 1f80
        //   mxcsr_mask ffff
        //
        
        registers->fpu_control_word = 0x49;
        registers->fpu_status_word  = 0;
        registers->fpu_tag_word     = 0;
        
        registers->fpu_instruction_pointer = 0;
        registers->fpu_data_pointer        = 0;
        
        registers->xinuse &= ~1;
    }
    
    if(to_restore & 2){
        // 
        // Load SSE state from xsave area.
        // 
        
        for(u32 xmm_reg_index = 0; xmm_reg_index < array_count(registers->simd); xmm_reg_index++){
#if _WIN32
            registers->simd[xmm_reg_index].xmmi.m128i_u64[0] = xsave_area.xmm[xmm_reg_index].low;
            registers->simd[xmm_reg_index].xmmi.m128i_u64[1] = xsave_area.xmm[xmm_reg_index].high;
#else
            registers->simd[xmm_reg_index].xmmi[0] = xsave_area.xmm[xmm_reg_index].low;
            registers->simd[xmm_reg_index].xmmi[1] = xsave_area.xmm[xmm_reg_index].high;
#endif
            
        }
        
        registers->mxcsr = xsave_area.mxcsr; // @cleanup: this might have to be masked
        
        registers->xinuse |= 2;
    }else if(to_initialize & 2){
        // 
        // Set all XMM registers to 0. Load MXCSR of 0x1f80.
        // 
        registers->mxcsr = 0x1f80;
        
        for(u32 xmm_reg_index = 0; xmm_reg_index < array_count(registers->simd); xmm_reg_index++){
#if _WIN32
            registers->simd[xmm_reg_index].xmmi.m128i_u64[0] = 0;
            registers->simd[xmm_reg_index].xmmi.m128i_u64[1] = 0;
#else
            registers->simd[xmm_reg_index].xmmi[0] = 0;
            registers->simd[xmm_reg_index].xmmi[1] = 0;
#endif
        }
        
        registers->xinuse &= ~2;
    }
    
    if(to_restore & 4){
        // 
        // Load the YMM registers from the xsave area.
        // 
        for(u32 ymm_reg_index = 0; ymm_reg_index < array_count(registers->simd); ymm_reg_index++){
#if _WIN32
            registers->simd[ymm_reg_index].xmmi_high.m128i_u64[0] = xsave_area.ymm[ymm_reg_index].low;
            registers->simd[ymm_reg_index].xmmi_high.m128i_u64[1] = xsave_area.ymm[ymm_reg_index].high;
#else
            registers->simd[ymm_reg_index].xmmi_high[0] = xsave_area.ymm[ymm_reg_index].low;
            registers->simd[ymm_reg_index].xmmi_high[1] = xsave_area.ymm[ymm_reg_index].high;
#endif
        }
        
        registers->xinuse |= 4;
    }else if(to_initialize & 4){
        // 
        // Set all YMM registers to 0.
        // 
        
        for(u32 ymm_reg_index = 0; ymm_reg_index < array_count(registers->simd); ymm_reg_index++){
#if _WIN32
            registers->simd[ymm_reg_index].xmmi_high.m128i_u64[0] = 0;
            registers->simd[ymm_reg_index].xmmi_high.m128i_u64[1] = 0;
#else
            registers->simd[ymm_reg_index].xmmi_high[0] = 0;
            registers->simd[ymm_reg_index].xmmi_high[1] = 0;
#endif
            
        }
        
        registers->xinuse &= ~4;
    }
}

void xsaves_helper(struct context *context, struct registers *registers, u64 xsave_area_guest_address){
    struct xsave_area xsave_area = xsave_area_from_registers(registers);
    
    u64 requested_feature_bitmap = (registers->xcr0 /*+ registers->IA32_XSS*/) & ((registers->rdx << 32) | (u32)registers->rax);
    u64 to_save = requested_feature_bitmap & registers->xinuse;
    
    if(registers->mxcsr != 0x1F80) to_save |= 2;
    
    if(to_save & 1){
        
        int success = guest_write_size(context, xsave_area.X86LegacyXSaveArea, xsave_area_guest_address, sizeof(xsave_area.X86LegacyXSaveArea));
        if(!success) return;
    }
    
    if(to_save & 2){
        int success = guest_write_size(context, xsave_area.xmm, xsave_area_guest_address + offset_in_type(struct xsave_area, xmm), sizeof(xsave_area.xmm));
        if(!success) return;
    }
    
    if(to_save & 4){
        int success = guest_write_size(context, xsave_area.ymm, xsave_area_guest_address + offset_in_type(struct xsave_area, ymm), sizeof(xsave_area.ymm));
        if(!success) return;
    }
    
    guest_write(u64, xsave_area_guest_address + offset_in_type(struct xsave_area, xstate_bv), to_save);
    guest_write(u64, xsave_area_guest_address + offset_in_type(struct xsave_area, xcomp_bv),  0x8000000000000000 | requested_feature_bitmap);
}

void fxsave_helper(struct context *context, struct registers *registers, u64 fxsave_area_guest_address){
    // 
    // @note: this does not seem to care whether or not it gets called in 64bit or 32bit mode (REXW or not).
    // 
    
    struct xsave_area xsave_area = xsave_area_from_registers(registers);
    
    // "Bytes 464:511 are available to software use. The processor does not write to bytes 464:511 of an FXSAVE area."
    // Bytes 416:464 are reserved, but also do not seem to be altered.
    guest_write_size(context, xsave_area.X86LegacyXSaveArea, fxsave_area_guest_address, 416);
}

void fxrstor_helper(struct context *context, struct registers *registers, u64 fxsave_area_guest_address/*, int is_64bit*/){
    
    // 
    // @cleanup: from my tests this does not care about 64-bit mode... I feel like from the documentation it should...
    // 
    
    struct xsave_area xsave_area = {0};
    
    int success = guest_read_size(context, xsave_area.X86LegacyXSaveArea, fxsave_area_guest_address, sizeof(xsave_area.X86LegacyXSaveArea), PERMISSION_read);
    if(!success) return;
    
    registers->fpu_control_word = (xsave_area.fpu_control_word & 0x1f3f) | (1 << 6);
    registers->fpu_status_word  = xsave_area.fpu_status_word;
    registers->fpu_tag_word     = xsave_area.fpu_tag_word;
    
    registers->fpu_instruction_pointer = xsave_area.fpu_instruction_pointer;
    registers->fpu_data_pointer        = xsave_area.fpu_data_pointer;
    
    registers->mxcsr = xsave_area.mxcsr;
    // registers->mxcsr_mask = xsave_area.mxcsr_mask; @note: It seems the mxcsr_mask does not (and cannot) change.
    
    for(u32 xmm_reg_index = 0; xmm_reg_index < 16 /*is_64bit ? 16 : 8*/; xmm_reg_index++){
#if _WIN32
        registers->simd[xmm_reg_index].xmmi.m128i_u64[0] = xsave_area.xmm[xmm_reg_index].low;
        registers->simd[xmm_reg_index].xmmi.m128i_u64[1] = xsave_area.xmm[xmm_reg_index].high;
#else
        registers->simd[xmm_reg_index].xmmi[0] = xsave_area.xmm[xmm_reg_index].low;
        registers->simd[xmm_reg_index].xmmi[1] = xsave_area.xmm[xmm_reg_index].high;
#endif
    }
    
}

void fnsave_helper(struct context *context, struct registers *registers, u64 fnsave_area_guest_address){
    
    struct fnsave_area{
        u32 fpu_control_word;
        u32 fpu_status_word;
        u32 fpu_tag_word;
        u32 fpu_instruction_pointer_offset;
        u32 fpu_instruction_pointer_selector;
        u32 fpu_data_pointer_offset;
        u32 fpu_data_pointer_selector;
        
        struct{ u8 data[10]; } fpST[8];
    } fnsave_area = {
        .fpu_control_word = registers->fpu_control_word,
        .fpu_status_word  = registers->fpu_status_word,
        .fpu_tag_word     = registers->fpu_tag_word,
        .fpu_instruction_pointer_offset   = (u32)registers->fpu_instruction_pointer,
        .fpu_instruction_pointer_selector = 0,
        .fpu_data_pointer_offset   = (u32)registers->fpu_data_pointer,
        .fpu_data_pointer_selector = 0,
    };
    
    // @note: We currently do not have these registers (I think) :)
    // for(u32 index = 0; index < array_count(fnsave_area.fpST); index++){
    //     registers->???
    // }
    
    int success = guest_write_size(context, &fnsave_area, fnsave_area_guest_address, 108);
    if(!success) return;
    
    // Reinitialize the fpu.
    registers->fpu_control_word = 0x37f;
    registers->fpu_status_word = 0;
    registers->fpu_tag_word = 0; // @cleanup: the documentation says 0xffff but it seems to be an 8-bit value? Also the hypervisor had it 0?
    registers->fpu_data_pointer = 0;
    registers->fpu_instruction_pointer = 0;
    registers->fpu_opcode = 0;
}

void FNSTENV_helper(struct context *context, struct registers *registers, u64 memory_operand){
    
    struct{
        u32 control_word;
        u32 status_word;
        u32 tag_word;
        u32 data_pointer;
        u32 instruction_pointer;
        u32 opcode;
        u32 cs;
    } data = {
        .control_word        = registers->fpu_control_word,
        .status_word         = registers->fpu_status_word,
        .tag_word            = registers->fpu_tag_word,
        .data_pointer        = (u32)registers->fpu_data_pointer,
        .instruction_pointer = (u32)registers->fpu_instruction_pointer,
        .opcode              = registers->fpu_opcode,
        .cs                  = 0x10, // ?
    };
    
    guest_write_size(context, &data, memory_operand, sizeof(data));
}

void FLDENV_helper(struct context *context, struct registers *registers, u64 memory_operand){
    
    struct{
        u32 control_word;
        u32 status_word;
        u32 tag_word;
        u32 data_pointer;
        u32 instruction_pointer;
        u32 opcode;
        u32 cs;
    } data = {0};
    
    int success = guest_read_size(context, &data, memory_operand, sizeof(data), PERMISSION_read);
    if(!success) return;
    
    registers->fpu_control_word        = (u16)data.control_word;
    registers->fpu_status_word         = (u16)data.status_word;
    registers->fpu_tag_word            = (u8)data.tag_word;
    registers->fpu_data_pointer        = (u64)data.data_pointer;
    registers->fpu_instruction_pointer = (u64)data.instruction_pointer;
    registers->fpu_opcode              = (u16)data.opcode;
}

void FNINIT_helper(struct registers *registers){
    
    // Reinitialize the fpu.
    registers->fpu_control_word = 0x37f;
    registers->fpu_status_word = 0;
    registers->fpu_tag_word = 0; // @cleanup: The documentation says `FPUTagWord := FFFFH`.
    registers->fpu_data_pointer = 0;
    registers->fpu_instruction_pointer = 0;
    registers->fpu_opcode = 0;
}

//_____________________________________________________________________________________________________________________
// String instruction helpers

void helper_movs(struct context *context, struct registers *registers, u8 operand_size, u32 legacy_prefix_flags){
    
    // __debugbreak();
    
    u64 source      = registers->rsi;
    u64 destination = registers->rdi;
    u64 count       = registers->rcx; // @cleanup: Address size and operand size prefixes might do something here.
    
    if(!(legacy_prefix_flags & LEGACY_rep)) count = 1;
    
    if(registers->DF){
        // Slow backwards variant for if the direction flag is set.
        while(count != 0){
            u8 buffer[8];
            int read_success = guest_read_size(context, buffer, source, operand_size, PERMISSION_read);
            if(!read_success) break;
            int write_success = guest_write_size(context, buffer, destination, operand_size);
            if(!write_success) break;
            
            count -= 1;
            destination -= operand_size;
            source -= operand_size;
        }
    }else if((source & (operand_size - 1)) || (destination & (operand_size - 1))){
        // Slow variant for when one of the memory operands is not aligned to the operand size.
        while(count != 0){
            u8 buffer[8];
            int read_success = guest_read_size(context, buffer, source, operand_size, PERMISSION_read);
            if(!read_success) break;
            int write_success = guest_write_size(context, buffer, destination, operand_size);
            if(!write_success) break;
            
            count -= 1;
            destination += operand_size;
            source += operand_size;
        }
    }else{
        while(count != 0){
            u64 bytes_left_in_source      = ((source      + 0x1000) & ~0xfff) - source;
            u64 bytes_left_in_destination = ((destination + 0x1000) & ~0xfff) - destination;
            
            u64 bytes_to_copy = (bytes_left_in_source < bytes_left_in_destination) ? bytes_left_in_source : bytes_left_in_destination;
            bytes_to_copy = bytes_to_copy < (count * operand_size) ? bytes_to_copy : count * operand_size;
            
            u64 source_page_number      = (source      >> 12);
            u64 destination_page_number = (destination >> 12);
            
            u8 *source_page      = null;
            u8 *destination_page = null;
            u8 *source_extra_permission_page      = null;
            u8 *destination_extra_permission_page = null;
            
            {
                // 
                // Lookup the source:
                // 
                
                struct translation_lookaside_buffer_entry *tlb_entry = &context->read_tlb.entries[source_page_number & (array_count(context->read_tlb.entries) - 1)];
                if(tlb_entry->virtual_page_number == source_page_number){
                    // TLB hit! Read from the cached page.
                    source_page = tlb_entry->host_page_address;
                    source_extra_permission_page = tlb_entry->extra_permission_page;
                }else{
                    source_page = translate_address(context, source_page_number << 12, PERMISSION_read);
                    source_extra_permission_page = get_extra_permissions_for_page(context, source_page_number);
                    
                    if(!source_page){
                        set_crash_information(context, CRASH_read, source);
                        goto crash;
                    }
                }
            }
            
            {
                // 
                // Lookup the destination:
                // 
                struct translation_lookaside_buffer_entry *tlb_entry = &context->write_tlb.entries[destination_page_number & (array_count(context->write_tlb.entries) - 1)];
                if(tlb_entry->virtual_page_number == destination_page_number){
                    // TLB hit! Read from the cached page.
                    destination_page = tlb_entry->host_page_address;
                    destination_extra_permission_page = tlb_entry->extra_permission_page;
                }else{
                    destination_page = translate_address(context, destination_page_number << 12, PERMISSION_write);
                    destination_extra_permission_page = get_extra_permissions_for_page(context, destination_page_number);
                    
                    if(!destination_page){
                        set_crash_information(context, CRASH_write, destination);
                        goto crash;
                    }
                }
            }
            
            if(source_extra_permission_page){
                for(u32 index = 0; index < bytes_to_copy; index++){
                    u32 offset = (source & 0xfff) + index;
                    
                    if(source_extra_permission_page[offset] & EXTRA_PERMISSION_inaccessible){
                        set_crash_information(context, CRASH_out_of_bounds_read, source + index);
                        goto crash;
                    }
                }
            }
            
            if(destination_extra_permission_page){
                for(u32 index = 0; index < bytes_to_copy; index++){
                    u32 offset = (destination & 0xfff) + index;
                    
                    if(destination_extra_permission_page[offset] & EXTRA_PERMISSION_inaccessible){
                        set_crash_information(context, CRASH_out_of_bounds_write, destination + index);
                        goto crash;
                    }
                }
            }
            
            destination_page += (destination & 0xfff);
            source_page      += (source      & 0xfff);
            
            // @cleanup: Could I simply use __movsb unconditionally and would that be faster?
            switch(operand_size){
                case 1: __movsb((u8  *)destination_page, (u8  *)source_page, bytes_to_copy);   break;
                case 2: __movsw((u16 *)destination_page, (u16 *)source_page, bytes_to_copy/2); break;
                case 4: __movsd((void *)destination_page, (void *)source_page, bytes_to_copy/4); break;
                case 8: __movsq((u64 *)destination_page, (u64 *)source_page, bytes_to_copy/8); break;
                invalid_default_case();
            }
            
            count -= bytes_to_copy/operand_size;
            source += bytes_to_copy;
            destination += bytes_to_copy;
        }
    }
    
    crash:;
    if(legacy_prefix_flags & LEGACY_rep) registers->rcx = count;
    
    registers->rsi = source;
    registers->rdi = destination;
}

void helper_stos(struct context *context, struct registers *registers, u8 operand_size, u32 legacy_prefix_flags){
    
    // __debugbreak();
    
    u64 value       = registers->rax;
    u64 destination = registers->rdi;
    u64 count       = registers->rcx; // @cleanup: Address size and operand size prefixes might do something here.
    
    if(!(legacy_prefix_flags & LEGACY_rep)) count = 1;
    
    if(registers->DF){
        // Slow backwards variant for if the direction flag is set.
        while(count != 0){
            
            int write_success = guest_write_size(context, &value, destination, operand_size);
            if(!write_success) break;
            
            count -= 1;
            destination -= operand_size;
        }
    }else if(destination & (operand_size - 1)){
        // Slow variant for when one of the memory operands is not aligned to the operand size.
        while(count != 0){
            int write_success = guest_write_size(context, &value, destination, operand_size);
            if(!write_success) break;
            
            count -= 1;
            destination += operand_size;
        }
    }else{
        while(count != 0){
            u64 bytes_left_in_destination = ((destination + 0x1000) & ~0xfff) - destination;
            
            u64 bytes_to_copy = (bytes_left_in_destination < count * operand_size) ? bytes_left_in_destination : count * operand_size;
            
            u64 destination_page_number = (destination >> 12);
            
            u8 *destination_page = null;
            u8 *destination_extra_permission_page = null;
            
            {
                // 
                // Lookup the destination:
                // 
                struct translation_lookaside_buffer_entry *tlb_entry = &context->write_tlb.entries[destination_page_number & (array_count(context->write_tlb.entries) - 1)];
                if(tlb_entry->virtual_page_number == destination_page_number){
                    // TLB hit! Read from the cached page.
                    destination_page = tlb_entry->host_page_address;
                    destination_extra_permission_page = tlb_entry->extra_permission_page;
                }else{
                    destination_page = translate_address(context, destination_page_number << 12, PERMISSION_write);
                    destination_extra_permission_page = get_extra_permissions_for_page(context, destination_page_number);
                    
                    if(!destination_page){
                        set_crash_information(context, CRASH_write, destination);
                        goto crash;
                    }
                }
            }
            
            if(destination_extra_permission_page){
                for(u32 index = 0; index < bytes_to_copy; index++){
                    u32 offset = (destination & 0xfff) + index;
                    
                    if(destination_extra_permission_page[offset] & EXTRA_PERMISSION_inaccessible){
                        set_crash_information(context, CRASH_out_of_bounds_write, destination + index);
                        goto crash;
                    }
                }
            }
            
            destination_page += (destination & 0xfff);
            
            switch(operand_size){
                case 1: __stosb((u8  *)destination_page, (u8)value, bytes_to_copy);   break;
                case 2: __stosw((u16 *)destination_page, (u16)value, bytes_to_copy/2); break;
                case 4: __stosd((void *)destination_page, (u32)value, bytes_to_copy/4); break;
                case 8: __stosq((u64 *)destination_page, (u64)value, bytes_to_copy/8); break;
                invalid_default_case();
            }
            
            count -= bytes_to_copy/operand_size;
            destination += bytes_to_copy;
        }
    }
    
    crash:;
    if(legacy_prefix_flags & LEGACY_rep) registers->rcx = count;
    
    registers->rdi = destination;
}



//_____________________________________________________________________________________________________________________
// rdrand helper

void rdrand_helper(struct context *context, struct registers *registers, u8 operand_size, u8 regm){
    (void)context;
    
    
    // "Loads a hardware generated random value and stores it in the destination register,
    //  The Carry Flag indicates whether a random value is available at the time the instruction
    //  is executed. CF = 1 indicates that the data in the destination is valid. Otherwise
    //  CF = 0 and the destination will be returned as zeroes of the specified width.
    //  All other flags are forced to 0 in either situation."
    
    registers->OF = registers->SF = registers->PF = registers->ZF = 0;
    registers->CF = 1;
    
    // @note: The pinnacle of randomness!
    switch(operand_size){
        case 2:{
            *(u16 *)&registers->gpr[regm] = 0x1337;
        }break;
        case 4:{
            registers->gpr[regm] = 0x13371337;
        }break;
        case 8:{
            registers->gpr[regm] = 0x1337133713371337;
        }break;
    }
}


//_____________________________________________________________________________________________________________________
// IN / OUT helpers

void read_from_port_helper(struct context *context, struct registers *registers, u16 port, u32 size){
    
    if(port == /*pm_tmr_blk*/0x408){
        u64 value = 0x1337 + registers->ia32_tsc / /*4GHZ/3.5MHZ*/1117;
        
        registers->ia32_tsc += RDTSC_INCREMENT;
        
        memcpy(&registers->rax, &value, size);
        return;
    }
    
    if(port == /*PCI_CONFIG_DATA*/0xcfc){
        memset(&registers->rax, 0xff, size);
        return;
    }
    
    if(port == /*CMOS data*/0x71){
        u32 value = 0;
        
        u64 seconds = registers->ia32_tsc / (4ull * 1024 * 1024 * 1024);
        u64 minutes = seconds / 60;
        
        switch(registers->CMOS.address){
            case 0x0:  value = (registers->CMOS.RTC.seconds + seconds) % 60; break;
            case 0x2:  value = (registers->CMOS.RTC.minutes + minutes) % 60; break;
            case 0x4:  value = registers->CMOS.RTC.hours;                    break;
            case 0x6:  value = registers->CMOS.RTC.day_of_the_week;          break;
            case 0x7:  value = registers->CMOS.RTC.day;                      break;
            case 0x8:  value = registers->CMOS.RTC.month;                    break;
            case 0x9:  value = registers->CMOS.RTC.year;                     break;
            case 0xa:  value = registers->CMOS.status;                       break;
            case 0x32: value = registers->CMOS.RTC.centuary;                 break;
            
            default:{
                set_crash_information(context, CRASH_internal_error, (u64)"CMOS address not handled.");
            }break;
        }
        
        memcpy(&registers->rax, &value, size);
        return;
    }
    
    if(port == /*PM1A_STATUS*/0x400){
        u32 value = 0;
        memcpy(&registers->rax, &value, size);
        return;
    }
    
    if(port == /*PM1A_CNT*/0x404){
        u32 value = 1;
        memcpy(&registers->rax, &value, size);
        return;
    }
    
    if(port == /*GP0_BLK*/0x40c || port == /*GP0_BLK_???*/0x40d || port == /*GP0_BLK_???*/0x40e || port == /*GP0_BLK_???*/0x40f){
        u32 value = 0;
        memcpy(&registers->rax, &value, size);
        return;
    }
    
    if(port == 0x5658){
        // Not implemented io-port
        u32 value = 0xffffffff;
        memcpy(&registers->rax, &value, size);
        return;
    }
    
    memset(&registers->rax, 0xff, size);
    
#if 0
    print("[read_from_port_helper] Unhandled port 0x%x\n", port);
#else
    set_crash_information(context, CRASH_internal_error, (u64)"Read from unhandled port.");
#endif
}


void write_to_port_helper(struct context *context, struct registers *registers, u16 port, u32 value){
    
    if(port == /*PCI_CONFIG_ADDRESS*/0xcf8){
        // ignore PCI_CONFIG_ADDRESS as we don't have any PCI devices.
        return;
    }
    
    if(port == /*PM1A_STATUS*/0x400){
        return;
    }
    
    if(port == /*PM1A_STATUS (?)*/0x402){
        // It uses this to enable
        return;
    }
    
    if(port == /*PM1A_CONTROL*/0x404){
        return;
    }
    
    if(port == /*CMOS address*/0x70){
        registers->CMOS.address = value;
        return;
    }
    
    if(port == /*GP0_BLK*/0x40c || port == /*GP0_BLK_???*/0x40d || port == /*GP0_BLK_???*/0x40e || port == /*GP0_BLK_???*/0x40f){
        return;
    }
    
    
    if(port == /*CMOS data*/0x71){
        switch(registers->CMOS.address){
            case /*RTC seconds*/0x00:{
                registers->CMOS.RTC.seconds = (u8)value;
            }break;
            case /*RTC minutes*/0x02:{
                registers->CMOS.RTC.minutes = (u8)value;
            }break;
            case /*RTC hours*/0x04:{
                registers->CMOS.RTC.hours = (u8)value;
            }break;
            case /*RTC day of the week*/0x06:{
                registers->CMOS.RTC.day_of_the_week = (u8)value;
            }break;
            case /*RTC day*/0x07:{
                registers->CMOS.RTC.day = (u8)value;
            }break;
            case /*RTC month*/0x08:{
                registers->CMOS.RTC.month = (u8)value;
            }break;
            case /*RTC year*/0x09:{
                registers->CMOS.RTC.year = (u8)value;
            }break;
            case /*RTC centuary*/0x32:{
                registers->CMOS.RTC.centuary = (u8)value;
            }break;
            
            case /*status*/0x0a:{
                registers->CMOS.status = value & 0x7f;
            }break;
            default:{
                set_crash_information(context, CRASH_internal_error, (u64)"CMOS address not handled.");
            }break;
        }
        
        return;
    }
    
    if(globals.debugger_mode){
        print("[write_to_port_helper] Unhandled write of 0x%x to unhandled port 0x%x.\n", value, port);
        handle_debugger(context);
    }else{
        set_crash_information(context, CRASH_internal_error, (u64)"write to unhandled port");
    }
}

void helper_interrupt_instruction(struct context *context, u8 interrupt_number){
    
    // 
    // @note: This currently only works from the jit, not the hypervisor.
    // 
    
    if(interrupt_number == 0x2d){
        
        switch(context->registers.rax){
            
            case 1:{
                if(globals.fuzzing && !globals.debugger_mode) break;
                // DebugPrint
                u8 buffer[0x100];
                
                u64 length  = context->registers.rdx;
                u64 address = context->registers.rcx;
                
                if(sizeof(buffer) < length){
                    length = sizeof(buffer);
                }
                
                guest_read_size(context, buffer, address, length, PERMISSION_none);
                
                if(length && buffer[length-1] == '\n') length -= 1;
                if(length && buffer[length-1] == '\r') length -= 1;
                
                // print("%.*s", length, buffer);
                print("DebugPrint: '%.*s'\n", length, buffer);
            }break;
            
            case 3:{
                // DbgLoadImageSymbols
                
                maybe_find_and_load_ntoskrnl(context);
                
                u8 buffer[0x100];
                
                u16 length  = guest_read(u16, context->registers.rcx);
                u64 address = guest_read(u64, context->registers.rcx + 0x8);
                
                if(sizeof(buffer) < length){
                    length = sizeof(buffer);
                }
                
                guest_read_size(context, buffer, address, length, PERMISSION_none);
                
                u64 base_address = guest_read(u64, context->registers.rdx);
                u32 image_size   = guest_read(u32, context->registers.rdx + 0x14); // @cleanup: they have a path for this being 0.
                
                print("guest loading '%.*s' %p %x\n", length, buffer, base_address, image_size);
                struct string image_name = {.data = (char *)buffer, .size = length};
                
                struct loaded_module *module = parse_loaded_module(context, base_address, image_size, image_name);
                
                if(string_match(module->short_name, globals.module_load_breakpoint_string)){
                    handle_debugger(context);
                }
            }break;
            case 4:{
                u8 buffer[0x100];
                
                u16 length  = guest_read(u16, context->registers.rcx);
                u64 address = guest_read(u64, context->registers.rcx + 0x8);
                
                if(sizeof(buffer) < length){
                    length = sizeof(buffer);
                }
                
                guest_read_size(context, buffer, address, length, PERMISSION_none);
                
                print("guest unloading '%.*s'\n", length, buffer);
            }break;
            
            default:{
                print("Unhandled debug service! 0x%x\n", context->registers.rax);
                // set_crash_information(context, CRASH_internal_error, (u64)"Unhandled debug service.");
            }break;
        }
    }else{
        if(globals.debugger_mode) print("Unhandled: int 0x%x instruction\n", interrupt_number);
    }
    
    //
    // @cleanup: @incomplete: Do we have to worry about error codes here? It says "some of them will generate #GP"
    // @note: This always immediately delivers the call to the interrupt handler.
    //        No pending etc.
    deliver_exception_or_interrupt(context, interrupt_number, /*have_error_code*/0, /*error_code*/0);
}

void helper_load_task_register(struct context *context, u16 selector){
    u64 selector_address = context->registers.gdt_base + (selector & ~7);
    
    // Mark the tr as busy:
    u8 access_byte = guest_read(u8, selector_address + 5);
    access_byte = (access_byte & 0xf0) | 0xb;
    guest_write(u8, selector_address + 5, access_byte);
    
    context->registers.tr = parse_segment_from_global_descriptor_table(context, context->registers.gdt_base, selector);
}

void helper_verify_segment(struct context *context, u16 selector, int is_verw){
    crash_assert(is_verw);
    
    context->registers.ZF = 1;
    
    if(selector < context->registers.gdt_limit){
        struct segment segment = parse_segment_from_global_descriptor_table(context, context->registers.gdt_base, selector);
        
        if(segment.segment_type != 0 && segment.is_non_system == 1 && (segment.segment_type & /*code_segment*/(1 << 3)) == 0 && (segment.segment_type & /*rw-bit*/(1 << 1)) == 1){
            context->registers.ZF = 1;
        }
    }
}


void helper_invlpg(struct context *context, u64 address){
    static_assert(array_count(context->read_tlb.entries) == array_count(context->write_tlb.entries));
    static_assert(array_count(context->read_tlb.entries) == array_count(context->execute_tlb.entries));
    
    // 
    // We need to flush the _page_ associated to address.
    // @HACK: This page could be a large page, hence we have to flush the entire tlb for now. uff.
    // 
    
#if 1
    (void)address;
    invalidate_translate_lookaside_buffers(context);
#else
    // We cannot really know whether 'address' was pointing to a large page. 
    // Maybe we should store this information inside the translation_lookaside_buffer_entry?
    u64 tlb_index = (address >> 12) & (array_count(context->read_tlb.entries) - 1);
    
    memset(&context->read_tlb   .entries[tlb_index], 0xff, sizeof(struct translation_lookaside_buffer_entry));
    memset(&context->write_tlb  .entries[tlb_index], 0xff, sizeof(struct translation_lookaside_buffer_entry));
    memset(&context->execute_tlb.entries[tlb_index], 0xff, sizeof(struct translation_lookaside_buffer_entry));
#endif
}

void helper_write_to_cr0(struct context *context, u64 value){
    // "When modifying PE or PG in register CR0, or PSE or PAE in register CR4, 
    //  all TLB entries are flushed, including global entries. 
    //  Software should not depend on this functionality in all Intel 64 or IA-32 processors."
    context->registers.cr0 = value;
    invalidate_translate_lookaside_buffers(context);
}

void helper_write_to_cr3(struct context *context, u64 value){
    // "If CR4.PCIDE = 1, bit 63 of the source operand to MOV to CR3 determines 
    //  whether the instruction invalidates entries in the TLBs and the paging-structure caches."
    context->registers.cr3 = value & 0x7fffffffffffffff;
    invalidate_translate_lookaside_buffers(context);
    
    // @note: We do this primarily to set page table 'accessed' bits.
    translate_rip_to_physical(context, context->registers.rip, PERMISSION_execute);
}

void helper_write_to_cr4(struct context *context, u64 value){
    // "When modifying PE or PG in register CR0, or PSE or PAE in register CR4, 
    //  all TLB entries are flushed, including global entries. 
    //  Software should not depend on this functionality in all Intel 64 or IA-32 processors."
    context->registers.cr4 = value;
    invalidate_translate_lookaside_buffers(context);
}

void helper_cpuid(struct context *context, struct registers *registers){
    
    // "Returns processor identification and feature information to the EAX, EBX, ECX, EDX registers,
    //  as determined by input entered in EAX and some cases ECX"
    
    if(PRINT_HOOK_EVENTS) print("%p: cpuid! %x\n", registers->rip, registers->rax);
    
    // "On Intel64 processors, CPUID clears the high 32bits of RAX/RBX/RCX/RDX".
    
    u32 rax = (u32)registers->rax;
    u32 rcx = (u32)registers->rcx;
    u32 rbx = 0;
    u32 rdx = 0;
    
    switch(rax){
        case 0:{
            if(globals.cpu_vendor == VENDOR_INTEL){
                // EAX - Maximum Input Value for Basic CPUID Information
                // EBX - "Genu"
                // EDX - "ntel"
                // ECX - "ineI"
                rax = 0x15;
                rbx = 0x756e6547;
                rdx = 0x49656e69;
                rcx = 0x6c65746e;
            }else{
                // EAX - Maximum Input Value for Basic CPUID Information
                // EBX - "Auth"
                // ECX - "enti"
                // EDX - "cAMD"
                rax = 0xd;
                rbx = 0x68747541;
                rdx = 0x69746e65;
                rcx = 0x444d4163;
            }
        }break;
        
        case 1:{
            // EAX - Version Information: Type, Familiy, Model, and Stepping ID
            // EBX - Brand Index, CLFLUSH line size, Addresseble ID's of processors, Initial APIC ID
            // ECX - Feature Information
            // EDX - Feature Information
            
            // rax=00000000000906ed rbx=0000000000010800 rcx=00000000feda3203 rdx=000000000f8bfbff
            rax =    0x906ed;
            rbx =    0x10800;
            
            // RCX:
            //     0 - SSE
            //     1 - PCLMULQDQ
            //     2 - DTES64
            //     3 - MONITOR
            //     4 - DS-CPL
            //     5 - VMX
            //     6 - SMX
            //     7 - EIST
            //     8 - TM2
            //     9 - SSSE3
            //    10 - CNXT-ID
            //    11 - SDBG
            //    12 - FMA
            //    13 - CMPXCHG16B
            //    14 - xTPR Update Control
            //    15 - PDCM
            //    16 - Reserved
            //    17 - PCID
            //    18 - DCA
            //    19 - SSE4_1
            //    20 - SSE4_2
            //    21 - x2APIC
            //    22 - MOVBE
            //    23 - POPCNT
            //    24 - TSC-Deadline
            //    25 - AESNI
            //    26 - XSAVE
            //    27 - OSXSAVE
            //    28 - AVX
            //    29 - F16C
            //    30 - RDRAND
            //    31 - Hypervisor bit
            
            rcx = 0u
                    | /*SSE*/        (1 <<  0)
                    | /*PCLMULQDQ*/  (1 <<  1)
                    | /*SSSE3*/      (1 <<  9)
                    | /*FMA*/        (1 << 12)
                    | /*CMPXCHG16B*/ (1 << 13)
                    | /*PCID*/       (1 << 17)
                    | /*SSE4_1*/     (1 << 19)
                    | /*SSE4_2*/     (1 << 20)
                    | /*MOVBE*/      (1 << 22)
                    | /*POPCNT*/     (1 << 23)
                    | /*AESNI*/      (1 << 25)
                    | /*XSAVE*/      (1 << 26)
                    | /*AVX*/        (1 << 28)
                    | /*F16C*/       (1 << 29)
                    | /*Hypervisor*/ (1 << 31)
                    ;
            
            // "A value of 1 indicates that the OS has set CR4.OSXSAVE[bit 18] to enable XSETBV/XGETBV instructions 
            //  to access XCR0 and to support processor extended state management using XSAVE/XRSTOR."
            if(registers->cr4 & (1 << 18)) rcx |= /*OSXSAVE*/(1u << 27);
            
            // RDX:
            //     0 - FPU
            //     1 - VME
            //     2 - DE
            //     3 - PSE
            //     4 - TSC
            //     5 - MSR
            //     6 - PAE
            //     7 - MCE
            //     8 - CX8
            //     9 - APIC
            //    10 - Reserved
            //    11 - SEP
            //    12 - MTRR
            //    13 - PGE
            //    14 - MCA
            //    15 - CMOV
            //    16 - PAT
            //    17 - PSE-36
            //    18 - PSN
            //    19 - CLFSH
            //    20 - Reserved
            //    21 - DS
            //    22 - ACPI
            //    23 - MMX
            //    24 - FXSR
            //    25 - SSE
            //    26 - SSE2
            //    27 - SS
            //    28 - HTT
            //    29 - TM
            //    30 - Reserved
            //    31 - PBE
            
            rdx = 0
                    |/*FPU*/   (1 << 0)
                    |/*VME*/   (1 << 1)
                    |/*DE*/    (1 << 2)
                    |/*PSE*/   (1 << 3)
                    |/*TSC*/   (1 << 4)
                    |/*MSR*/   (1 << 5)
                    |/*PAE*/   (1 << 6)
                    |/*MCE*/   (1 << 7)
                    |/*CX8*/   (1 << 8)
                    |/*APIC*/  (1 << 9)
                    |/*SEP*/   (1 << 11)
                    |/*MTRR*/  (1 << 12)
                    |/*PGE*/   (1 << 13)
                    |/*MCA*/   (1 << 14)
                    |/*CMOV*/  (1 << 15)
                    |/*PAT*/   (1 << 16)
                    |/*36*/    (1 << 17)
                    |/*CLFSH*/ (1 << 19)
                    |/*MMX*/   (1 << 23)
                    |/*FXSR*/  (1 << 24)
                    |/*SSE*/   (1 << 25)
                    |/*SSE2*/  (1 << 26)
                    |/*SS*/    (1 << 27)
                    ;
            
        }break;
        
        case 2:{
            // Cache and TLB information (this probably means something...)
            rax = 0x76036301;
            rbx = 0xf0b5ff;
            rcx = 0;
            rdx = 0xc30000;
        }break;
        
        case 3:{
            // Processor Serial Number - Available only on Pentium III.
            rax = 0;
            rbx = 0;
            rcx = 0;
            rdx = 0;
        }break;
        
        case 4:{
            // Deterministic Cache Parameters Leaf
            // 
            // QEMU has:
            //   rcx=0: L1 dcache info
            //   rcx=1: L1 icache info
            //   rcx=2: L2 cache info
            //   rcx=3: L3 cache info    
            //   rcx>3: all zeroes.
            
            // We report "no more caches" for everything.
            rax = 0;
            rbx = 0;
            rcx = 0;
            rdx = 0;
        }break;
        case 5:{
            // Monitor / MWAIT Leaf
            rax = 0;
            rbx = 0;
            rcx = 0;
            rdx = 0;
        }break;
        
        case 6:{
            // Thermal and Power Management Leaf
            rax = 0x7f3;
            rbx = 0x2;
            rcx = 0x9;
            rdx = 0x0;
        }break;
        
        case 7:{
            // Structured Extended Feature Flags Enumeration Leaf
            
            if(rcx == 0){
                
                // Maximum input value for supported leaf 7 sub-leaves.
                rax = 0x0;
                
                // EBX:
                //    0 - FSGSBASE
                //    1 - IA32_TSC_ADJUST
                //    2 - SGX
                //    3 - BMI1
                //    4 - HLE
                //    5 - AVX2
                //    6 - FDP_EXCPTN_ONLY
                //    7 - SMEP
                //    8 - BMI2
                //    9 - Enhanced REP MOVSB/STOSB
                //   10 - INVPCID
                //   11 - RTM
                //   12 - RDT-M
                //   13 - Deprecate FPU CS and FPU DS.
                //   14 - MPX
                //   15 - RDT-A
                //   16 - AVX512F
                //   17 - AVX512DQ
                //   18 - RDSEED
                //   19 - ADX
                //   20 - SMAP
                //   21 - AVX512_IFMA
                //   22 - Reserved
                //   23 - CLFLUSHOPT
                //   24 - CLWB
                //   25 - Intel Processor Trace
                //   26 - AVX512PF
                //   27 - AVX512ER
                //   28 - AVX512CD
                //   29 - SHA
                //   30 - AVX512BW
                //   31 - AVX512VL
                //   
                // FSGSBASE | BMI1 | AVX2 | SMEP | BMI2 | Enhanced REP | INVPCID
                // Deptreate FPU | ADX | SMAP | CLFLUSHOPT
                rbx = 0x9827a9;
                rcx = 0;
                
                // EDX:
                //    10 - MD_CLEAR supported
                //    26 - IBRS and IBPB supported
                //    27 - STIBP supported
                //    28 - L1D_FLUSH supported
                //    29 - IA32_ARCH_CAPABILITIES supported
                //    30 - Reserved
                //    31 - SSBD Supported
                
                rdx = 0xbc000400;
                
                if(globals.cpu_vendor == VENDOR_AMD){
                    rdx &= ~/*IA32_ARCH_CAPABILITIES*/(1 << 29);
                }
                
            }else{
                // All zeroes indicates that this subleaf is invalid.
                rax = 0;
                rbx = 0;
                rcx = 0;
                rdx = 0;
            }
        }break;
        
        case 8:{
            // @cleanup: does not exist?
            rax = 0;
            rbx = 0;
            rcx = 0;
            rdx = 0;
        }break;
        
        case 0x9:{
            rax = 0; // @cleanup: this is bits [31:0] of IA32_PLATFORM_DCA_CAP.
            rbx = 0;
            rcx = 0;
            rdx = 0;
        }break;
        
        case 0xa:{
            rax = 0;
            rbx = 0;
            rcx = 0;
            rdx = 0;
        }break;
        
        case 0xb:{
            rax = 0;
            rbx = 0;
            rcx = (u8)rcx; // Output value in ECX[7:0] always equals input value in ECX[7:0].
            rdx = 0;
        }break;
        
        case 0xc:{
            // @cleanup: does not exist?
            rax = 0;
            rbx = 0;
            rcx = 0;
            rdx = 0;
        }break;
        
        case 0xd:{
            // Processor Extended State Enumeration
            
            // XSAVE area on this laptop: 
            //   0) x87 floating point unit/SSE   0x200
            //   1) XSAVE-Header                   0x40
            //   2) AVX                           0x100
            //   3) MPX                            0x40
            //   4) MPX                            0x40
            
            if(rcx == 0){
                
                // EAX: Reports the supported bits of the lower 32 bits of XCR0
                //      XCR0[n] can be set iff eax[n] is 1.
                //      
                // EBX: Maximum size required by enabled features in XCR0.
                // ECX: Maximum size required by all features supported by the processor.
                // EDX: Same as eax for the upper 32 bits of XCR0.
                
                rax = /*x87*/(1 << 0) | /*SSE*/(1 << 1) | /*AVX*/(1 << 2) | /*MPX((1 << 3) | (1 << 4))*/0;
                rbx = 0x440; // Size for all enabled features. The os might have disabled some features.
                rcx = 0x440; // Maximial size.
                rdx = 0;
            }else if(rcx == 1){
                rax = 0xf;   // xsaveopt, xsavec, xgetbv, xsaves/xrstors
                rbx = 0x3c0; // size of xsave area.
                rcx = 0;
                rdx = 0;
            }else if(rcx == /*AVX*/2){
                // rcx > 1: Size required for feature i.
                rax = /*size*/0x100;
                rbx = /*offset*/0x240;
                rcx = 0;
                rdx = 0;
            }else{
                // No more features.
                rax = 0;
                rbx = 0;
                rcx = 0;
                rdx = 0;
            }
        }break;
        
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:{
            if(rcx == 0 || (u32)rcx == (u32)rax){
                // 
                // @cleanup: Maybe look through them again. We needed them all because SMBios/mpengine query them,
                //           but I don't think it actually cares about the values.
                //           It also queries subleaf == leaf and hyper-v reports 0 for all of these.
                //           
                rax = 0;
                rbx = 0;
                rcx = 0;
                rdx = 0;
            }else{
                crash_assert(!"Unhandled subleaf in CPUID.");
            }
        }break;
        
        case 0x80000000:{
            // EAX Maximum Input Value for Extended Function CPUID Information. EBX Reserved. ECX Reserved. EDX Reserved.
            rax = 0x80000008;
            
            if(globals.cpu_vendor == VENDOR_AMD){
                rbx = 0x68747541;
                rdx = 0x69746e65;
                rcx = 0x444d4163;
            }else{
                rbx = 0;
                rcx = 0;
                rdx = 0;
            }
        }break;
        
        case 0x80000001:{
            // Extended Processor Info and Feature Bits
            
            rax = 0; // Extended Processor Signature and Feature Bits.
            rbx = 0; // Reserved
            rcx = (1 << 0) | (1 << 5) | (1 << 8); // LAHF/SAHF (bit0), LZCNT(bit5), PREFETCHW(bit8)
            rdx = (1 << 11) | (1 << 20) | (1 << 26) | (1 << 27) | (1 << 29); // SYSCALL/SYSRET(bit11), ExecuteDisableBit(bit20), GbytePages(bit26), rdtscp(bit27), IA64(bit29)
        }break;
        
        // @cleanup: Forward to the real __cpuid?
        case 0x80000002:{
            rax = 0x65746e49; // Inte
            rbx = 0x2952286c; // l(R)
            rcx = 0x726f4320; // Cor
            rdx = 0x4d542865; // e(TM
        }break;
        
        case 0x80000003:{
            rax = 0x37692029; // ) i7
            rbx = 0x3538392d; // -985
            rcx = 0x43204830; // 0H C
            rdx = 0x40205550; // PU @
        }break;
        
        case 0x80000004:{
            rax = 0x362e3220; //  2.6
            rbx = 0x7a484730; // 0GHz
            rcx = 0x0;
            rdx = 0x0;
        }break;
        
        case 0x80000005:{ // Cache and TLB Identifiers.
            
            if(globals.cpu_vendor == VENDOR_AMD){
                rax = 0xff40ff40; // ff = Data Cache associativity, 40 Data Chace line size, ff = Instruction Cache associativity, 40 Instruction Chace line size (Large Pages?)
                rbx = 0xff40ff40; // ff = Data Cache associativity, 40 Data Chace line size, ff = Instruction Cache associativity, 40 Instruction Chace line size (4k Pages)
                rcx = 0x20080140; // L1D size, L1D assoc, L1D Lines/tag, L1D line size
                rdx = 0x40040140; // L1I size, L1I assoc, L1I Lines/tag, L1I line size
            }else{
                rax = 0;
                rbx = 0;
                rcx = 0;
                rdx = 0;
            }
        }break;
        
        case 0x80000006:{
            
            if(globals.cpu_vendor == VENDOR_AMD){
                rax = 0x26006400; // L2 TLB parameters, 2M/4M pages
                rbx = 0x66006400; // L2 TLB parameters, 4K pages
                rcx =  0x2006140; // L2 cache parameters
                rdx =   0x808140; // Reserved ?
            }else{
                rax = 0; // reserved
                rbx = 0; // reserved
                rcx = /*Cache line size in bytes*/0x40 | (/*L2 Associativity = 8 ways*/6 << 12) | (/*Cache size in 1K units*/0x100);
                rdx = 0; // reserved
            }
        }break;
        
        case 0x80000007:{
            rax = 0; // reserved
            rbx = 0; // reserved
            rcx = 0; // reserved
            rdx = 0x100; // Invariant TSC available, everything else reserved. @cleanup: I this supposed to be unset for intel?
        }break;
        
        case 0x80000008:{
            rax = 0x3027; // physical address size information (0x30 = 48-bits of linear address space 0x27 bits of physical address space)
            rbx = 0;
            rcx = 0;
            rdx = 0;
        }break;
        
        case 0x80000021:{
            // @cleanup: Why do they query this in "KiInitializeHresetSupport"?
            
            // Extended Feature Identification
            rax = 0;
            rbx = 0;
            rcx = 0;
            rdx = 0;
        }break;
        
        case 0x80000026:{
            rax = 0;
            rbx = 0;
            rcx = 0;
            rdx = 0;
        }break;
        
        // "The range 0x40000000 - 4FFFFFFF is invalid, No existing or future CPU will return processor
        // identification of feature information if the initial EAX value is in this range."
        
        // This range is used by microsoft:
        //    https://docs.microsoft.com/en-us/virtualization/hyper-v-on-windows/tlfs/feature-discovery
        
        // "If the "hypervisor present bit" (in CPUID 0x01), is set, additional CPUID leafs can be
        // queried for more information about the conformant hypervisor and its capabilities.
        // Two Such leaves are guaranteed to be available: 0x40000000 and 0x40000001.
        // These are the "Standard Hypervisor Leaves"
        
        case 0x40000000:{
            // EAX - The maximum input value for hypervisor CPUID information
            // EBX, ECX, EDX - Hypervisor Vendor ID Signature
            
            rax = 0x40000006;
            rbx = 0x7263694d; // "Microsoft Hv"
            rcx = 0x666f736f;
            rdx = 0x76482074;
        }break;
        
        case 0x40000001:{
            // Hypervisor Vendor-Neutral Interface Identification 
            //    EAX - "Hv#1" 
            //    EBX, ECX, EDX - reserved
            rax = 0x31237648;
            rbx = 0;
            rcx = 0;
            rdx = 0;
        }break;
        
        case 0x40000002:{
            // Hypervisor System Identity
            //   EAX - Build Number
            //   EBX - Version
            rax = 0x4a61;
            rbx = 0xa0000;
            rcx = 0;
            rdx = 0;
        }break;
        
        case 0x40000003:{
            // Hypervisor Feature Identification
            
            // EAX = bits 31-0  of the HV_PARTITION_PRIVELEGE_MASK
            // 
            //     0 - VpRunTimeReg
            //     1 - PartitionReferenceCounter
            //     2 - SynicRegs
            //     3 - SyntheticTimerRegs
            //     4 - IntrCtrlRegs
            //     5 - HypercallMsrs
            //     6 - VpIndex
            //     7 - ResetReg
            //     8 - StatsReg                 (x)
            //     9 - PartitionReferenceTsc
            //    10 - GuestIdleReg
            //    11 - FrequencyRegs
            //    12 - DebugRegs                (x)
            //    13 - ReenlightenmentControl
            //     
            rax = 0x2eff;
            
            // EBX = bits 63-32 of the HV_PARTITION_PRIVILEGE_MASK
            // 
            //     0 - CreatePartitions
            //     1 - AccessPartitionId
            //     2 - AccessMemoryPool
            //     3 - Reserved
            //     4 - PostMessages
            //     5 - SignalEvents
            //     6 - CreatePort
            //     7 - ConnectPort
            //     8 - AccessStats
            //     9 - Reserved2
            //    10 - Debugging
            //    11 - CpuManagement
            //    12 - Reserve
            //    13 - Reserved
            //    14 - Reserved
            //    15 - AccessVSM
            //    16 - AccessVpRegisters
            //    17 - Reserved
            //    18 - Reserved
            //    19 - EnableExtendedHypercalls
            //    20 - StartVirtualProcessor
            //     
            rbx = 
                    /*PostMessages*/(1 << 4) | 
                    /*SignalEvents*/(1 << 5) | 
                    
#if ENABLE_VSM
                    /*AccessVSM*/(1 << 15) | 
                    /*AccessVpRegisters*/(1 << 16) |
#endif
                    /*EnableExtendedHypercalls*/(1 << 19) | 
                    0;
            
            // ECX = 0-4 Reserved
            //       5 - Invariant Mperf
            //       6 - Supervisor shadow stack
            //       7 - Architectural PMU
            //       8 - Exception trap intercept
            rcx = 2;
            
            // EDX = 0 - Deprecated (previously MWAIT)
            //       1 - Guest debugging
            //       2 - Performance Monitor
            //       3 - Physical CPU tynamic partitioning events
            //       4 - hypercall input parameter block via XMM registers
            //       5 - virtual guest idle state
            //       6 - hypervisor sleep state
            //       7 - querying NUMA
            //       8 - determining timer frequencies
            //       9 - injecting synthetic machine checks
            //      10 - guest crash MSR
            //      11 - debug MSR
            //      12 - NPIEP
            //      13 - DisableHypervisorAvailable (?)
            //      14 - ExtendedGvaRangesForFlushVirtualAddressList
            //      15 - Support for returning hypercall output via XMM
            //      16 - Reserved
            //      17 - Sint Polling
            //      18 - HypercallMsrLock
            //      19 - Use direct synthtetic timers
            //      20 - PAT registers available for VSM
            //      21 - Suppost for bndcfgs registers available for VSM
            //      22 - Reserved
            //      23 - Support for synthetic time unhalted timer
            //      26 - Intel's Last Branch Record feature 
            rdx = 
                    /*guest debugging*/(1 << 1) | 
                    /*hypercall input XMM*/(1 << 4) | 
                    // /*virtual guest idle*/(1 << 5) | 
                    /*querying NUMA*/(1 << 7) | 
                    /*determinig timer frequencies*/(1 << 8) | 
                    /*injecting synthetic machine checks*/(1 << 9) | 
                    /*guest crash msr*/(1 << 10) | 
                    // /*NPIEP*/(1 << 12) | 
                    /*ExtendedGvaRangesForFlushVirtualAddressList*/(1 << 14) | 
                    /*Hypercall output XMM*/(1 << 15) | 
                    /*Sint polling*/(1 << 17) | 
                    /*HypercallMsrLock*/(1 << 18) | 
                    /*Use direct synthetic timers*/(1 << 19) | 
                    // /*PAT registers available for VSM*/(1 << 20) | 
                    // /*Support for bndcfgs for VSM*/(1 << 21) | 
                    /*Support for synthetic time unhalted timer*/(1 << 23) | 
                    0;
        }break;
        
        case 0x40000004:{
            // Implementation Recommendations
            rax = /*REMOTE_TLB_FLUSH_RECOMMENDED*/  (1 <<  2) 
                    
                    | /*APIC_ACCESS_RECOMMENDED*/       (1 <<  3) 
                    | /*RELAXED_TIING_RECOMMENDED*/     (1 <<  5)
            
#ifdef _WIN32  // :AEOI_on_linux
                    | /*DEPRECATING_AEOI_RECOMMENDED*/  (1 <<  9)
#endif
                    | /*ClUSTER_IPI_RECOMMENDED*/       (1 << 10) 
                    | /*EX_PROCESSOR_MASK_RECOMMENDED*/ (1 << 11)
                    | /*UseDirectLocalFlushEntire*/     (1 << 17);
            rbx = 0xfff; // default number of spinlock retry attempts
            rcx = 46; // Implemented Physical address bits.
            rdx = 0;
        }break;
        
        case 0x40000005:{
            // Hypervisor Implementation limits
            rax = 0xf0;  // Maximum number of virtual processors.
            rbx = 0x400; // Maximum amount of logical processors.
            rcx = 0x96c; // Maximum number of physical interrupt vectors available for interrupt remapping.
            rdx = 0;
        }break;
        
        case 0x40000006:{
            // Implementation Hardware features
            rax = 0xf;
            rbx = 0;
            rcx = 0;
            rdx = 0;
        }break;
        
        case 0x40000080:{
            // @cleanup: This is supposed to be some syndbg (?) stuff. I don't know what that is.
            rax = 0;
            rbx = 0;
            rcx = 0;
            rdx = 0;
        }break;
        
        // 
        // Our hacky cpuid's
        // 
        
        case CPUID_drag_and_drop:{
            if(!context->use_hypervisor) break; // We only do drag and drop in the hypervisor. (Maybe just not fuzzing?)
            
            // No new file was dragged and dropped.
            if(drag_and_drops_processed == drag_and_drops_initiated) break;
            
            struct crash_information crash_information = enter_debugging_routine(context);
            
            FILE *file = null;
            do{ // Breakable scope
                
                struct cpuid_drag_and_drop_input_buffer input_buffer = guest_read(struct cpuid_drag_and_drop_input_buffer, registers->rdx);
                
                u32 current_file = drag_and_drops_processed % array_count(drag_and_drop_files);
                
                // If the guest requested the file data, always treat the file as "processed".
                if(input_buffer.file_data) drag_and_drops_processed += 1;
                
                size_t file_name_size = strlen(drag_and_drop_files[current_file].file_path);
                
                file = fopen(drag_and_drop_files[current_file].file_path, "rb");
                if(!file){
                    print("WARNING: Unable to open drag and dropped file %s\n", drag_and_drop_files[current_file].file_path);
                    break;
                }
                
                fseek(file, 0, SEEK_END);
                size_t file_size = ftell64(file);
                if(file_size == -1){
                    print("WARNING: Unable to ftell drag and dropped file %s\n", drag_and_drop_files[current_file].file_path);
                    break;
                }
                fseek(file, 0, SEEK_SET);
                
                struct string file_path = {.data = drag_and_drop_files[current_file].file_path, .size = file_name_size};
                struct string file_name = string_strip_file_path(file_path);
                
                if(input_buffer.file_name && input_buffer.file_name_size == (u64)file_name.size){
                    
                    int success = guest_write_size(context, file_name.data, (u64)input_buffer.file_name, file_name.size);
                    if(!success){
                        print("WARNING: Unable to write file name for dropped file %s\n", drag_and_drop_files[current_file].file_path);
                        break;
                    }
                }
                
                if(input_buffer.file_data && input_buffer.file_size == file_size){
                    
                    u8 *memory = push_data(&context->scratch_arena, u8, file_size);
                    fread(memory, 1, file_size, file);
                    int success = guest_write_size(context, memory, (u64)input_buffer.file_data, file_size);
                    if(!success){
                        print("WARNING: Unable to write file data for dropped file %s\n", drag_and_drop_files[current_file].file_path);
                        break;
                    }
                }
                
                input_buffer.file_size = file_size;
                input_buffer.file_name_size = file_name.size;
                
                int success = guest_write_size(context, &input_buffer, registers->rdx, sizeof(input_buffer));
                if(!success){
                    print("WARNING: Unable to write input buffer for dropped file %s\n", drag_and_drop_files[current_file].file_path);
                    break;
                }
                
            }while(false);
            
            if(file) fclose(file);
            
            exit_debugging_routine(context, crash_information);
        }break;
        
        
        case CPUID_copy_out:{
            if(!context->use_hypervisor) break; // We only do drag and drop in the hypervisor. (Maybe just not fuzzing?)
            
            struct cpuid_drag_and_drop_input_buffer input_buffer = guest_read(struct cpuid_drag_and_drop_input_buffer, registers->rdx);
            
            // @clenaup: use malloc so we can fail?
            u8 *file_name_buffer = push_data(&context->scratch_arena, u8, input_buffer.file_name_size + 1);
            u8 *file_data_buffer = push_data(&context->scratch_arena, u8, input_buffer.file_size);
            
            struct crash_information crash_information = enter_debugging_routine(context);
            
            guest_read_size(context, file_name_buffer, (u64)input_buffer.file_name, input_buffer.file_name_size, PERMISSION_read);
            guest_read_size(context, file_data_buffer, (u64)input_buffer.file_data, input_buffer.file_size,      PERMISSION_read);
            
            file_name_buffer[input_buffer.file_name_size] = 0;
            
            int success = context->crash == CRASH_none;
            
            exit_debugging_routine(context, crash_information);
            
            struct string file_name = string_strip_file_path((struct string){.data = (char *)file_name_buffer, .size = input_buffer.file_name_size}); // Prevent path traversal (I hope this is enough)
            
            print("NOTICE: Copy out %.*s!\n", file_name.size, file_name.data);
            
            if(success){
                char buffer[0x200];
                snprintf(buffer, sizeof(buffer), "out\\%.*s", file_name.size, file_name.data);
                FILE *file = fopen(buffer, "wb"); // @cleanup: do this wide?
                if(file){
                    fwrite(file_data_buffer, 1, input_buffer.file_size, file);
                    fclose(file);
                }else{
                    print("WARNING: Could not copy out %s, could not fopen!\n", buffer);
                }
            }else{
                print("WARNING: Could not copy out %.*s, crashed while reading!\n", file_name.size, file_name.data);
            }
        }break;
        
        
        // @note: If a value entered for CPUID.EAX is less then or equal to the maximum input value
        //        and the leaf is not supported on that processor the 0 is returned in all 
        default:{
            if(((u32)rax & 0x00ffff00) != 0){
                //
                // If it has the middle bits set, it should be invalid.
                //
                
                rax = rbx = rcx = rdx = 0;
                break;
            }
            
            set_crash_information(context, CRASH_internal_error, (u64)"Unhandled CPUID");
            
            print("Unhandled CPUID 0x%x at %p\n", (u32)rax, registers->rip);
            print_registers(context, stdout);
            print_stack_trace(context);
            
            int cpuinfo[4];
            __cpuid(cpuinfo, (u32)rax);
            print("possible answer eax: 0x%x ebx: 0x%x ecx: 0x%x edx: 0x%x\n",
                    cpuinfo[0], cpuinfo[1], cpuinfo[2], cpuinfo[3]);
            
        }break;
    }
    
    registers->rax = rax;
    registers->rbx = rbx;
    registers->rcx = rcx;
    registers->rdx = rdx;
}

void helper_far_jump(struct context *context){
    
    //
    // On a far jump, we just issue a __fastfail (interrupt 0x29).
    // 
    
    deliver_exception_or_interrupt(context, 0x29, 0, 0);
    
    char image_name[16];
    if(globals.debugger_mode) print("***** CRASHING ON FAR JUMP %s\n", get_image_name(context, image_name, 0));
}

//_____________________________________________________________________________________________________________________

void pend_timer_interrupt(struct context *context, struct registers *registers, u64 time){
    
    struct {
        u32 MessageType;
        u8 PayloadSize;
        u8 MessageFlags;
        u16 reserved;
        
        u64 something;
        
        struct{
            u32 TimerIndex;
            u32 Reserved;
            u64 ExpirationTime;
            u64 DeliveryTime;
        } TimerPayload;
    } TimerMessage = {
        .MessageType = /*HvMessageTimerExpired*/0x80000010,
        .PayloadSize = sizeof(TimerMessage.TimerPayload),
        .MessageFlags = 0,
        .something = 0,
        .TimerPayload = {
            .TimerIndex = 0, // We are currently assuming it uses stimer0.
            .ExpirationTime = time, // @note: It does not even read these!
            .DeliveryTime   = time, //        So whatever...
        },
    };
    
    if(PRINT_TIMER_EVENTS) print("[" __FUNCTION__ "] interrupt time %f\n", time * 100.0 / 1.0e+9);
    
    //
    // Write the timer message to the 'sint_message_page' where the guest can then read it.
    //
    
    u32 synthetic_interrupt_number = (registers->hv_x64_msr_stimer0_config >> 16) & 0xf;
    
    u8 *message_page = get_physical_memory_for_write(context, registers->hv_x64_msr_simp & ~0xfff);
    memcpy(message_page + 0x100 * synthetic_interrupt_number, &TimerMessage, sizeof(TimerMessage));
    
    // 
    // @cleanup: We are not adjusting registers->rip here anywhere, meaning if this interrupt would trigger 
    //           immediately it would return to this instruction and do it again?
    // 
    if(synthetic_interrupt_number == 3){
        pend_interrupt(context, registers, registers->hv_x64_msr_sint3 & 0xff);
    }else{
        set_crash_information(context, CRASH_internal_error, (u64)"unhandled synthetic interrupt number");
    }
}

void helper_immediately_pend_timer_interrupt(struct context *context, struct registers *registers){
    
    if(PRINT_HOOK_EVENTS){
        print_symbol(context, registers->rip); print(": idle!\n");
    }
    
    if(TIMEOUT_ON_IDLE && globals.fuzzing){
        set_crash_information(context, CRASH_timeout, registers->rip);
    }
    
    if(!(registers->hv_x64_msr_reference_tsc_page & 1)) return;
    
    // @note: Copy and paste from `calculate_time_reference_counter`.
    u8 *HvlpReferenceTscPage = get_physical_memory_for_read(context, registers->hv_x64_msr_reference_tsc_page & ~0xfff);
    
    u64 TscScale  = *(u64 *)(HvlpReferenceTscPage +  8);
    u64 TscOffset = *(u64 *)(HvlpReferenceTscPage + 16);
    
    u64 ScaledTscHigh = 0;
    _umul128(registers->ia32_tsc, TscScale, &ScaledTscHigh);
    
    u64 time_reference_counter = ScaledTscHigh + TscOffset;
    
    // 
    // Set the timer to the next timer we are supposed to execute!
    // 
    
    u64 timer = registers->hv_x64_msr_stimer0_count;
    
    if(registers->hv_x64_msr_stimer0_config & /*periodic*/2){
        timer += time_reference_counter;
    }else{
        registers->hv_x64_msr_stimer0_count = 0; // reset the counter
    }
    
    if(time_reference_counter < timer){
        u64 remainder = 0;
        u64 new_ia32_tsc = _udiv128(timer - TscOffset, 0, TscScale, &remainder); // @cleanup: Make sure this does not crash?
        assert(new_ia32_tsc >= registers->ia32_tsc);
        
        if(PRINT_TIMER_EVENTS) print("[%s] Changed to timer, ia32_tsc %p -> %p time_reference_counter %p -> %p (%fs increment)\n", __FUNCTION__, registers->ia32_tsc, new_ia32_tsc, time_reference_counter, timer, (timer - time_reference_counter) * 100.0 / 1.0e+9);
        
        if(context->use_hypervisor){
            // :timer_interrupts
            double time_to_sleep = (double)((s64)timer - (s64)time_reference_counter) * 100.0 / 1.0e+9;
            if(time_to_sleep > 0){
                s64 time_to_sleep_milies = (s64)(1000.0 * time_to_sleep);
                if(time_to_sleep_milies > 16) time_to_sleep_milies = 16;
                sleep_miliseconds((u32)time_to_sleep_milies);
            }
        }
        
        time_reference_counter = timer;
        registers->ia32_tsc = new_ia32_tsc; // @cleanup: Offset?
    }else{
        if(PRINT_TIMER_EVENTS) print("[%s] time_reference_counter %p ia32_tsc %p\n", __FUNCTION__, time_reference_counter, registers->ia32_tsc);
    }
    
    
    pend_timer_interrupt(context, registers, time_reference_counter);
}

//_____________________________________________________________________________________________________________________
// rdmsr / wrmsr

// https://github.com/torvalds/linux/blob/master/arch/x86/include/asm/hyperv-tlfs.h
// https://learn.microsoft.com/en-us/virtualization/hyper-v-on-windows/tlfs/feature-discovery

//
// https://learn.microsoft.com/en-us/virtualization/hyper-v-on-windows/tlfs/timers
//

#define HV_X64_MSR_TIME_REF_COUNT 0x40000020 // Time Reference Count a 100ns-tick timer that starts at 0 when the partition (guest vm) starts up.
#define HV_X64_MSR_REFERENCE_TSC  0x40000021 // Guest Physical Page of the TSC (Time Stamp Counter) Page
#define HV_X64_MSR_TSC_FREQUENCY  0x40000022
#define HV_X64_MSR_APIC_FREQUENCY 0x40000023

#define HV_X64_MSR_STIMER0_CONFIG 0x400000B0 // Configuration register for timer 0
#define HV_X64_MSR_STIMER0_COUNT  0x400000B1 // Expiration time or period for timer 0
#define HV_X64_MSR_STIMER1_CONFIG 0x400000B2
#define HV_X64_MSR_STIMER1_COUNT  0x400000B3
#define HV_X64_MSR_STIMER2_CONFIG 0x400000B4
#define HV_X64_MSR_STIMER2_COUNT  0x400000B5
#define HV_X64_MSR_STIMER3_CONFIG 0x400000B6
#define HV_X64_MSR_STIMER3_COUNT  0x400000B7


// https://gerhart01.github.io/msdn.microsoft.com/en-us/library/windows/hardware/ff542396(v%3dvs.85).html
#define HV_X64_MSR_EOI 0x40000070 // Accesses the APIC EOI
#define HV_X64_MSR_ICR 0x40000071 // Accesses the APIC ICR high and ICR low
#define HV_X64_MSR_TPR 0x40000072 // Access the APIC TPR


// https://gerhart01.github.io/msdn.microsoft.com/en-us/library/windows/hardware/ff542738(v%3dvs.85).html
#define HV_X64_MSR_SCONTROL 0x40000080 // SynIC Control              (Enabled)
#define HV_X64_MSR_SVERSION 0x40000081 // SynIC Version              (Version)
#define HV_X64_MSR_SIEFP    0x40000082 // Interrupt Event Flags Page (Guest Physical Address | Enabled)
#define HV_X64_MSR_SIMP     0x40000083 // Interrupt Message Page     (Guest Physical Address | Enabled)
#define HV_X64_MSR_EOM      0x40000084 // End of message
#define HV_X64_MSR_SINT0    0x40000090 // Interrupt source 0 (hypervisor)
#define HV_X64_MSR_SINT1    0x40000091 // Interrupt source 1
#define HV_X64_MSR_SINT2    0x40000092 // Interrupt source 2
#define HV_X64_MSR_SINT3    0x40000093 // Interrupt source 3
#define HV_X64_MSR_SINT4    0x40000094 // Interrupt source 4
#define HV_X64_MSR_SINT5    0x40000095 // Interrupt source 5
#define HV_X64_MSR_SINT6    0x40000096 // Interrupt source 6
#define HV_X64_MSR_SINT7    0x40000097 // Interrupt source 7
#define HV_X64_MSR_SINT8    0x40000098 // Interrupt source 8
#define HV_X64_MSR_SINT9    0x40000099 // Interrupt source 9
#define HV_X64_MSR_SINT10   0x4000009A // Interrupt source 10
#define HV_X64_MSR_SINT11   0x4000009B // Interrupt source 11
#define HV_X64_MSR_SINT12   0x4000009C // Interrupt source 12
#define HV_X64_MSR_SINT13   0x4000009D // Interrupt source 13
#define HV_X64_MSR_SINT14   0x4000009E // Interrupt source 14
#define HV_X64_MSR_SINT15   0x4000009F // Interrupt source 15

#define HV_X64_MSR_GUEST_IDLE 0x400000F0

#define IA32_MTRR_CAP       0xfe
#define IA32_MTRR_DEF_TYPE  0x2ff

#define IA32_MTRR_PHYS_BASE 0x200
#define IA32_MTRR_PHYS_MASK 0x201

#define IA32_TSC            0x10
#define IA32_EFER           0xc0000080
#define IA32_FS_BASE        0xc0000100
#define IA32_GS_BASE        0xc0000101
#define IA32_KERNEL_GS_BASE 0xc0000102
#define IA32_TSC_AUX        0xc0000103

// According to ChatGPT: The MSR_PP1_ENERGY_STATUS register contains the current energy consumed by the processor package, 
//                       measured in units of microjoules. The value in this register is cumulative and is updated at a constant rate (usually once per second). 
//                       The energy consumption can be used to monitor the power consumption of the processor and to make decisions about power management.
#define MSR_PP1_ENERGY_STATUS 0x641

#define IA32_PRED_CMD 0x49

void helper_rdmsr(struct context *context, struct registers *registers){
    // "Reads the contests of a 64-bit model specific register (MSR) specified in the ECX register into
    //  EDX:EAX. The high order 32bits of RCX are ignored. The EDX register is loaded with the high-order 32
    //  bits of the MSR and the EAX register is loaded with the low-order 32 bits. (High orders of these are
    //  Cleared.)"
    
    u64 msr_value = 0;
    
    switch((u32)registers->rcx){
        
        
        case BIOS_log:{
            
            u8 buffer[0x1000];
            u64 size = ((u64)registers->r8 < sizeof(buffer)) ? registers->r8 : sizeof(buffer);
            guest_read_size(context, buffer, registers->rdx, size, PERMISSION_none);
            print("[bios log] %.*s\n", size, buffer);
        }break;
        
        case BIOS_crash:{
            set_crash_information(context, CRASH_internal_error, (u64)"Bios crashed.");
        }break;
        
        case BIOS_disk_read:{
            u64 buffer_size = registers->r8;
            u64 buffer      = registers->r9;
            
            u64 logical_block_address   = registers->rdx;
            u64 transfer_size_in_blocks = (buffer_size + 0x1ff)/0x200;
            
            if(PRINT_DISK_EVENTS) print("[Disk] Bios-Read 0x%x into %p from %p\n", transfer_size_in_blocks, buffer, logical_block_address);
            
            u8 *sectors = disk_read_sectors(&context->scratch_arena, transfer_size_in_blocks, logical_block_address);
            
            if(context != globals.main_thread_context){
                // First apply the writes which were applied prior to fuzzing.
                disk_apply_temporary_writes(globals.main_thread_context, sectors, logical_block_address, transfer_size_in_blocks);
            }
            
            disk_apply_temporary_writes(context, sectors, logical_block_address, transfer_size_in_blocks);
            
            guest_write_size(context, sectors, buffer, buffer_size);
        }break;
        case BIOS_disk_write:{
            u64 buffer_size  = registers->r8;
            u64 guest_buffer = registers->r9;
            
            u64 logical_block_address   = registers->rdx;
            u64 transfer_size_in_blocks = (buffer_size + 0x1ff)/0x200;
            
            if(PRINT_DISK_EVENTS) print("[Disk] Bios-Write 0x%x into %p from %p\n", transfer_size_in_blocks, guest_buffer, logical_block_address);
            
            u8 *buffer = push_data(&context->scratch_arena, u8, buffer_size); // @note: Gets copied in `vhdx_register_tempoary_write`.
            guest_read_size(context, buffer, guest_buffer, buffer_size, PERMISSION_read);
            
            disk_register_temporary_write(context, buffer, logical_block_address, transfer_size_in_blocks);
        }break;
        
        case BIOS_read_key:{
            struct hacky_event event = {0};
            
            while(events_processed < events_initiated){
                event = event_buffer[events_processed % array_count(event_buffer)];
                events_processed++;
                
                if(event.kind == HACKY_EVENT_key_event){
                    break;
                }
            }
            
            u16 scan_code = event.kind == HACKY_EVENT_key_event ? event.keycode : 0;
            guest_write(u16, registers->rdx, scan_code);
        }break;
        
        case /*MSR_POWER_CTL*/  0x1fc: msr_value = 0; break;
        case /*IA32_MC0_STATUS*/0x401: msr_value = 0; break;
        
        case /*IA32_MCG_CAP*/0x179:{
            // registers->rax = 0x1000001; @cleanup: not sure, this is this value in my own efi thing, but in the hypervisor it seems to be 0.
            msr_value = 0;
        }break;
        
        case /*IA32_APIC_BASE*/0x1b:       msr_value = registers->ia32_apic_base;    break;
        case /*IA32_PAT*/0x277:            msr_value = registers->ia32_pat;          break;
        case /*IA32_BIOS_SIGN_ID*/0x8b:    msr_value = registers->ia32_bios_sign_id; break;
        case /*IA32_FEATURE_CONTROL*/0x3a: msr_value = /*locked*/1;                  break;
        
        case /*IA32_ARCH_CAPABILITIES*/0x10a:{
            // bit - Name
            //  0  - RDCL_NO
            //  1  - IBRS_ALL
            //  2  - RSBA
            //  3  - SKIP_L1DFL_VMENTRY
            //  4  - SSB_NO
            //  5  - MDS_NO
            //  6  - IF_PSCHANGE_MC_NO
            //  7  - TSX_CTRL
            //  8  - TAA_NO
            //  9  - Reserved
            //  10 - MISC_PACKAGE_CTRLS
            //  ...
            
            msr_value = /*RDCL_NO | IBRS_ALL | RSBA | MDS_NO*/0x27;
        }break;
        
        
        case /*MSR_IA32_PLATFORM_ID*/0x17: msr_value = 0; break;
        
        case 0x174: msr_value = registers->ia32_sep_sel; break;
        case 0x175: msr_value = registers->ia32_sep_rsp; break;
        case 0x176: msr_value = registers->ia32_sep_rip; break;
        
        case /*IA32_STAR */0xC0000081: msr_value = registers->ia32_star;  break;
        case /*IA32_LSTAR*/0xC0000082: msr_value = registers->ia32_lstar; break;
        case /*IA32_CSTAR*/0xC0000083: msr_value = registers->ia32_cstar; break;
        case /*IA32_FMASK*/0xC0000084: msr_value = registers->ia32_fmask; break;
        
        case IA32_TSC_AUX: msr_value = registers->ia32_tsc_aux; break;
        
        case IA32_MTRR_CAP:       msr_value = registers->ia32_mtrr_cap;       break;
        case IA32_MTRR_DEF_TYPE:  msr_value = registers->ia32_mtrr_def_type;  break;
        case IA32_MTRR_PHYS_BASE: msr_value = registers->ia32_mtrr_phys_base; break;
        case IA32_MTRR_PHYS_MASK: msr_value = registers->ia32_mtrr_phys_mask; break;
        
        case IA32_MTRR_PHYS_BASE + 2:
        case IA32_MTRR_PHYS_BASE + 3:
        case IA32_MTRR_PHYS_BASE + 4:
        case IA32_MTRR_PHYS_BASE + 5:
        case IA32_MTRR_PHYS_BASE + 6:
        case IA32_MTRR_PHYS_BASE + 7:
        case IA32_MTRR_PHYS_BASE + 8:
        case IA32_MTRR_PHYS_BASE + 9:
        case IA32_MTRR_PHYS_BASE + 10:
        case IA32_MTRR_PHYS_BASE + 11:
        case IA32_MTRR_PHYS_BASE + 12:
        case IA32_MTRR_PHYS_BASE + 13:
        case IA32_MTRR_PHYS_BASE + 14:
        case IA32_MTRR_PHYS_BASE + 15:{
            msr_value = 0;
        }break;
        
        case /*MSR_MTRRfix64K_00000*/0x250: case /*MSR_MTRRfix16K_80000*/0x258:{
            msr_value = 0x0606060606060606;
        }break;
        
        /*MSR_MTRRfix16K_A0000 - MSR_MTRRfix4K_F8000*/
        case 0x259:
        case 0x268:case 0x269:case 0x26a:case 0x26b:case 0x26c:case 0x26d:case 0x26e:case 0x26f:{
            msr_value = 0;
        }break;
        
        case IA32_EFER: msr_value = registers->ia32_efer; break;
        
        case IA32_TSC: msr_value = registers->ia32_tsc; break;
        
        case /*IA32_MISC_ENABLE*/0x1a0: msr_value = registers->ia32_misc_enable; break;
        
        case MSR_PP1_ENERGY_STATUS: msr_value = 0; break;
        
        case IA32_FS_BASE: msr_value = registers->fs_base; break;
        
        case IA32_KERNEL_GS_BASE: msr_value = registers->gs_swap; break;
        
        case /*MSR_AMD64_SYSCFG*/0xC0010010:{
            // 21 TOM2 MtrrTom2En R/W
            // 20 MVDM MtrrVarDramEn R/W
            // 19 MFDM MtrrFixDramModEn R/W
            // 18 MFDE MtrrFixDramEn R/W
            msr_value = 0;
        }break;
        
        case HV_X64_MSR_TIME_REF_COUNT:{
            u64 HvlpReferenceTscPage = registers->hv_x64_msr_reference_tsc_page & ~0xfff;
            
            u64 time_reference_counter = 0;
            
            if(registers->hv_x64_msr_reference_tsc_page & 1){
                u8 *memory = get_physical_memory_for_read(context, HvlpReferenceTscPage);
                
                u64 TscScale  = *(u64 *)(memory + HvlpReferenceTscPage +  8);
                u64 TscOffset = *(u64 *)(memory + HvlpReferenceTscPage + 16);
                
                u64 ScaledTscHigh = 0;
                _umul128(registers->ia32_tsc, TscScale, &ScaledTscHigh);
                
                time_reference_counter = ScaledTscHigh + TscOffset;
            }else{
                
                u64 tsc_frequency = 3200ull * 1000 * 1000;
                if(context->use_hypervisor) tsc_frequency = calculate_tsc_frequency(); // In the JIT we want consistency!
                
                u64 remainder;
                u64 scale = _udiv128(/*high*/10000000, /*low*/0, tsc_frequency, &remainder); // @cleanup: Makes sure this does not crash?
                
                _umul128(registers->ia32_tsc, scale, &time_reference_counter);
            }
            
            msr_value = time_reference_counter;
        }break;
        
        case HV_X64_MSR_REFERENCE_TSC: msr_value = registers->hv_x64_msr_reference_tsc_page; break;
        
        case /*HV_X64_MSR_HYPERCALL*/0x40000001: msr_value = registers->hv_x64_msr_hypercall_page; break;
        case /*HV_X64_MSR_VP_INDEX */0x40000002: msr_value = 1; break;
        case /*HV_X64_MSR_VP_ASSIST*/0x40000073: msr_value = registers->hv_x64_msr_vp_assist_page; break;
        
        case HV_X64_MSR_GUEST_IDLE:{
            // @note: This is not hit anymore, as I disabled the corresponding bit in the cpuid.
            
            msr_value = 0;
            helper_immediately_pend_timer_interrupt(context, registers);
        }break;
        
        case HV_X64_MSR_SVERSION: msr_value = 1; break;
        case HV_X64_MSR_SCONTROL: msr_value = 1; break;
        
        
        case HV_X64_MSR_SIMP:  msr_value = registers->hv_x64_msr_simp; break;
        case HV_X64_MSR_SIEFP: msr_value = registers->hv_x64_msr_siefp; break;
        
        case HV_X64_MSR_TSC_FREQUENCY:{
            u64 tsc_frequency = 3200ull * 1000 * 1000;
            if(context->use_hypervisor) tsc_frequency = calculate_tsc_frequency(); // In the JIT we want consistency!
            msr_value = tsc_frequency;
        }break;
        
        case HV_X64_MSR_APIC_FREQUENCY: msr_value = 0xbebc200ull; break;
        
        case HV_X64_MSR_SINT0:
        case HV_X64_MSR_SINT1:
        case HV_X64_MSR_SINT2:
        case HV_X64_MSR_SINT3:
        case HV_X64_MSR_SINT4:
        case HV_X64_MSR_SINT5:
        case HV_X64_MSR_SINT6:
        case HV_X64_MSR_SINT7:
        case HV_X64_MSR_SINT8:
        case HV_X64_MSR_SINT9:
        case HV_X64_MSR_SINT10:
        case HV_X64_MSR_SINT11:
        case HV_X64_MSR_SINT12:
        case HV_X64_MSR_SINT13:
        case HV_X64_MSR_SINT14:
        case HV_X64_MSR_SINT15:{
            msr_value = registers->hv_x64_msr_sint[(u32)registers->rcx - HV_X64_MSR_SINT0];
        }break;
        
        default:{
            if(globals.debugger_mode){
                print("***** Unhandled rdmsr 0x%x\n", (u32)registers->rcx);
            }else{
                set_crash_information(context, CRASH_internal_error, (u64)"Unimplmented msr.");
            }
        }break;
    }
    
    registers->rdx = (u32)(msr_value >> 32);
    registers->rax = (u32)(msr_value >> 0);
    
    if(PRINT_HOOK_EVENTS || PRINT_MSR_ACESSES) print("rdmsr 0x%x returns 0x%llx\n", registers->rcx, msr_value);
}

#define MSR_KVM_HYPERCALL 0x1337766d

void helper_wrmsr(struct context *context, struct registers *registers){
    // "Writes the contents of registers of EDX:EAX to the MSR specified in the ECX register."
    
    u64 value_low  = (u32)registers->rax;
    u64 value_high = (u32)registers->rdx;
    u64 value      = (value_high << 32) | value_low;
    
    if(PRINT_HOOK_EVENTS || PRINT_MSR_ACESSES) print("wrmsr 0x%x <- 0x%llx\n", registers->rcx, value);
    
    switch((u32)registers->rcx){
        
        case HV_X64_MSR_SCONTROL:{
            crash_assert(value == 1);
        }break;
        
        case HV_X64_MSR_SIMP:{
            registers->hv_x64_msr_simp = value;
        }break;
        
        case HV_X64_MSR_SIEFP:{
            registers->hv_x64_msr_siefp = value;
        }break;
        
        case HV_X64_MSR_SINT0:{
            registers->hv_x64_msr_sint0 = value;
        }break;
        
        case HV_X64_MSR_SINT1:{
            registers->hv_x64_msr_sint1 = value;
        }break;
        
        case HV_X64_MSR_SINT2:{
            registers->hv_x64_msr_sint2 = value;
        }break;
        
        case HV_X64_MSR_SINT3:{
            registers->hv_x64_msr_sint3 = value;
        }break;
        
        case /*IA32_PAT*/0x277:{
            registers->ia32_pat = value;
        }break;
        
        case /*IA32_BIOS_SIGN_ID*/0x8b:{
            // @cleanup: for some reason this does not change on a write...
            // print("IA32_BIOS_SIGN_ID %p\n", value);
            // registers->ia32_bios_sign_id = value;
        }break;
        
        case /*TSX_CTL*/0x122:{
            // @cleanup: maybe we have to care about TSX_CPUID_CLEAR?
        }break;
        
        case /*IA32_APIC_BASE*/0x1b:{
            if(registers->ia32_apic_base != value){
                not_implemented();
            }
        }break;
        
        case IA32_MTRR_PHYS_BASE:{
            registers->ia32_mtrr_phys_base = value;
        }break;
        case IA32_MTRR_PHYS_BASE + 1:{
            registers->ia32_mtrr_phys_mask = value;
        }break;
        
        // Machine Check registers.
        case /*IA32_MC0_CTL*/0x400:{
            print("IA32_MC0_CTL %p\n", value);
        }break;
        
        case /*MSR_IA32_SPEC_CTRL*/0x48:{
            registers->ia32_spec_ctrl = value;
        }break;
        
        case 0x250: case 0x258:
        case 0x259:case 0x268:case 0x269:case 0x26a:case 0x26b:case 0x26c:case 0x26d:case 0x26e:case 0x26f:
        case IA32_MTRR_PHYS_BASE + 2:
        case IA32_MTRR_PHYS_BASE + 3:
        case IA32_MTRR_PHYS_BASE + 4:
        case IA32_MTRR_PHYS_BASE + 5:
        case IA32_MTRR_PHYS_BASE + 6:
        case IA32_MTRR_PHYS_BASE + 7:
        case IA32_MTRR_PHYS_BASE + 8:
        case IA32_MTRR_PHYS_BASE + 9:
        case IA32_MTRR_PHYS_BASE + 10:
        case IA32_MTRR_PHYS_BASE + 11:
        case IA32_MTRR_PHYS_BASE + 12:
        case IA32_MTRR_PHYS_BASE + 13:
        case IA32_MTRR_PHYS_BASE + 14:
        case IA32_MTRR_PHYS_BASE + 15:{
            // Ignore these for now.
        }break;
        
        case 0x2ff:{ // MSR_MTRRdefType
            registers->ia32_mtrr_def_type = value;
        }break;
        
        case 0x174:{
            registers->ia32_sep_sel = value;
        }break;
        case 0x175:{
            registers->ia32_sep_rsp = value;
        }break;
        case 0x176:{
            registers->ia32_sep_rip = value;
        }break;
        
        case /*IA32_STAR*/0xC0000081:{
            registers->ia32_star = value;
        }break;
        case /*IA32_CSTAR*/0xC0000082:{
            registers->ia32_lstar = value;
        }break;
        case /*IA32_CSTAR*/0xC0000083:{
            registers->ia32_cstar = value;
        }break;
        case /*IA32_FMASK*/0xC0000084:{
            registers->ia32_fmask = value;
        }break;
        
        case IA32_EFER:{
            registers->ia32_efer = value;
        }break;
        
        case IA32_TSC_AUX:{
            registers->ia32_tsc_aux = value;
        }break;
        
        case IA32_PRED_CMD:{
            // some branch predictor stuff
        }break;
        
        case HV_X64_MSR_EOM:{
            vmbus_offer_channel(context);
        }break;
        case HV_X64_MSR_STIMER0_CONFIG:{
            
            registers->hv_x64_msr_stimer0_config = value;
            if(PRINT_TIMER_EVENTS) print("[HV_X64_MSR_STIMER0_CONFIG] = %p\n", value);
            
        }break;
        case HV_X64_MSR_STIMER0_COUNT:{
            
            // 
            // @note: It does not really make sense to calculate the due time here, 
            //        as the timer could be either periodic or single shot depending
            //        on what is written to the config register afterwards.
            // 
            
            registers->hv_x64_msr_stimer0_count = value;
            if(PRINT_TIMER_EVENTS) print("HV_X64_MSR_STIMER0_COUNT %p\n", value);
        }break;
        
        case HV_X64_MSR_EOI:{
            // "The EOI register is a write-only register.
            //  The hypervisor sets a value into the APIC EOI register.
            //  Attempts to read from this register will result in a #GP fault."
            
            u32 EOI = (u32)registers->rax;
            if(PRINT_HOOK_EVENTS || PRINT_INTERRUPT_EVENTS) print("Writing Eoi 0x%x\n", EOI);
            
            apic_perform_end_of_interrupt(registers);
        }break;
        
        case HV_X64_MSR_ICR:{
            // Interrupt Command Register
            
            // "The values of ICR high and ICR low are read from or written into the corresponding
            //  APIC ICR high and low registers."
            
            
            u32 ICR_high = (u32)registers->rdx;
            u32 ICR_low  = (u32)registers->rax;
            u64 ICR = (((u64)ICR_high) << 32) | ICR_low;
            
            if(PRINT_HOOK_EVENTS) print("\nWriting ICR (Interrupt Command Register) 0x%llx!\n", ICR);
            if(PRINT_HOOK_EVENTS) print_stack_trace(context);
            
            // "The interrupt command register is made of two 32-bit registers; one at 0x300 and the other at 0x310.
            //  It is used for sending interrupts to different processors.
            //  The interrupt is issued when 0x300 is written to, but not when 0x310 is written to.
            //  Thus, to send an interrupt command one should first write to 0x310, then to 0x300.
            //  At 0x310 there is one field at bits 24-27, which is local APIC ID of the target processor
            //  (for a physical destination mode)."
            
#define get_bit_range(number, start, end) (((number) >> start) & ((1ull << ((end) - (start))) - 1))
            u32 vector_number     = get_bit_range(ICR, 0, 8);
            u32 destination_mode  = get_bit_range(ICR, 8, 11);
            u32 destination_mode2 = get_bit_range(ICR, 11, 12);
            u32 delivery_status   = get_bit_range(ICR, 12, 13);
            u32 init_level_clear  = get_bit_range(ICR, 14, 15);
            u32 init_level_set    = get_bit_range(ICR, 15, 16);
            u32 destination_type  = get_bit_range(ICR, 18, 20);
            
            if(PRINT_HOOK_EVENTS) print("   vector_number:     0x%x\n", vector_number);
            if(PRINT_HOOK_EVENTS) print("   destination_mode:  0x%x\n", destination_mode);
            if(PRINT_HOOK_EVENTS) print("   destination_mode2: 0x%x\n", destination_mode2);
            if(PRINT_HOOK_EVENTS) print("   delivery_status:   0x%x\n", delivery_status);
            if(PRINT_HOOK_EVENTS) print("   init_level_clear:  0x%x\n", init_level_clear);
            if(PRINT_HOOK_EVENTS) print("   init_level_set:    0x%x\n", init_level_set);
            if(PRINT_HOOK_EVENTS) print("   destination_type:  0x%x\n", destination_type);
#undef get_bit_range
            
            // @cleanup: Error codes for vectors < 22.
            crash_assert(vector_number >= 22);
            
            pend_interrupt(context, registers, vector_number);
        }break;
        
        case /*HV_X64_MSR_GUEST_OS_ID*/0x40000000:{
            // ignore this I guess, it tells us that the guest is windows... which we assume anyway.
        }break;
        case /*HV_X64_MSR_HYPERCALL*/0x40000001:{
            
            registers->hv_x64_msr_hypercall_page = value;
            
            u64 physical_address = value & ~0xfff;
            
            // @note: I think this should GP.
            crash_assert(physical_address < context->physical_memory_size);
            
            u8 *hypercall_page = get_physical_memory_for_write(context, physical_address);
            memset(hypercall_page, 0x90, 0x1000);
            
#ifndef _WIN32
            if(context->use_hypervisor){
                // linux - I could not figure out how to make vmcall exit to user space...
                
                static u8 loonix_hypercall_instructions[] = {
                    // mov rax, rcx
                    // mov rcx, MSR_KVM_HYPERCALL
                    // rdsmr
                    // ret
                    0x48, 0x89, 0xC8, 
                    0x48, 0xC7, 0xC1, 0x6D, 0x76, 0x37, 0x13, 
                    0x0F, 0x30, 
                    0xC3,
                    0xC3,
                    0xC3,
                    0xC3,
                    0xC3,
                    0xC3,
                    0xC3,
                };
                memcpy(hypercall_page, loonix_hypercall_instructions, sizeof(loonix_hypercall_instructions));      
            }else
#endif
            
            if(globals.cpu_vendor == VENDOR_INTEL){
                static u8 intel_hypercall_instructions[] = {
                    0x0f, 0x01, 0xc1, 0xc3,                                                             // (vmcall ret)
                    0x8b, 0xc8, 0xb8, 0x11, 0x00, 0x00, 0x00, 0x0f, 0x01, 0xc1, 0xc3,                   // (hypercall x86)
                    0x48, 0x8b, 0xc1, 0x48, 0xc7, 0xc1, 0x11, 0x00, 0x00, 0x00, 0x0f, 0x01, 0xc1, 0xc3, // (hypercall x64)
                    0x8b, 0xc8, 0xb8, 0x12, 0x00, 0x00, 0x00, 0x0f, 0x01, 0xc1, 0xc3,                   // (x86)
                    0x48, 0x8b, 0xc1, 0x48, 0xc7, 0xc1, 0x12, 0x00, 0x00, 0x00, 0x0f, 0x01, 0xc1, 0xc3, // (x64)
                };
                memcpy(hypercall_page, intel_hypercall_instructions, sizeof(intel_hypercall_instructions));
            }else if(globals.cpu_vendor == VENDOR_AMD){
                static u8 amd_hypercall_instructions[] = {
                    0x0f, 0x01, 0xd9, 0xc3,                                                             // (vmmcall ret)
                    0x8b, 0xc8, 0xb8, 0x11, 0x00, 0x00, 0x00, 0x0f, 0x01, 0xd9, 0xc3,                   // (hypercall x86)
                    0x48, 0x8b, 0xc1, 0x48, 0xc7, 0xc1, 0x11, 0x00, 0x00, 0x00, 0x0f, 0x01, 0xd9, 0xc3, // (hypercall x64)
                    0x8b, 0xc8, 0xb8, 0x12, 0x00, 0x00, 0x00, 0x0f, 0x01, 0xd9, 0xc3,                   // (x86)
                    0x48, 0x8b, 0xc1, 0x48, 0xc7, 0xc1, 0x12, 0x00, 0x00, 0x00, 0x0f, 0x01, 0xd9, 0xc3, // (x64)
                };
                memcpy(hypercall_page, amd_hypercall_instructions, sizeof(amd_hypercall_instructions));
            }else{
                not_implemented();
            }
            
        }break;
        
        case /*HV_X64_MSR_VP_ASSIST*/0x40000073:{
            registers->hv_x64_msr_vp_assist_page = value;
        }break;
        
        case HV_X64_MSR_REFERENCE_TSC:{
            registers->hv_x64_msr_reference_tsc_page = value;
            
            if(PRINT_TIMER_EVENTS) print("hv_x64_msr_reference_tsc_page <- %p\n", value);
            
            if(value & 1){
                u64 physical_address = value & ~0xfff;
                crash_assert(physical_address < context->physical_memory_size);
                
                u8 *tsc_page = get_physical_memory_for_write(context, physical_address);
                
                // :calculate_tsc_frequency_because_windows_wont_tell_me
                // 
                // Root formula:
                //     nsec/100 = ticks * scale / (2**64) + offset
                //    
                // assume offset = 0:
                //    
                //     nsec/100 = ticks * scale / (2 ** 64)
                //     
                // per 1 sec:
                // 
                //     1e9/100 = 3.2e9 * scale / (2 ** 64)
                //     
                //     (2 ** 64) / 320 = scale = 0x00ccccccccccccd0 ~ 0x00cccb492a4c99ba
                //     (2 ** 64) / 260 = scale = 0x00fc0fc0fc0fc100 ~ 0x00fcd6fc2c3659a2
                //     
                // 
                // It is supprisingly vital, to report the approximately correct tsc-frequency.
                // This is because (and I am not sure if this is a bug in Windows) inside 
                // `KiPrepareReadyThreadForRescheduling` it does an unsigned subtraction and comparison:
                //     `if(KUSER_SHARED_DATA.TickCount.low - 300U < thread->WaitTime)`
                // Which underflows and, for the first 300 ticks, causes every thread to 'KiSetPriorityBoost'.
                // Without this priority boost the `vmbus!XPartReceiveMessageThread` never reschedules
                // and the vmbus does not initialize properly.
                // Hence, if the reported frequency is "too slow" too many ticks happen before 
                // this priority boost is "supposed" to happen.
                // 
                //                                                          - Pascal Beyer 22.04.2024
                //
                // :vmbus_tsc_frequency_hack
                //  
                // UPDATE(12.03.2025): Because this got even worse on linux (wsl), I am not pretending 
                //                     to have a really high tsc-frequency until this thread is loaded
                //                     and then reset it to to the _correct_ one.
                // 
                
                u64 tsc_frequency = 3200ull * 1000 * 1000;
                if(context->use_hypervisor){  // In the JIT we want consistency!
                    tsc_frequency = calculate_tsc_frequency();
                    
                    if(context->vmbus.gpadls == null){
                        // :vmbus_tsc_frequency_hack
                        tsc_frequency *= 20;
                    }
                }
                
                u64 remainder;
                u64 scale = _udiv128(/*high*/10000000, /*low*/0, tsc_frequency, &remainder); // @cleanup: Make sure this does not crash?
                
                if(PRINT_TIMER_EVENTS) print("Tsc Scale 0x%llx (actual frequency 0x%llx, pretending 0x%llx for hacky purposes)\n", scale, tsc_frequency/20, tsc_frequency);
                
                *(u64 *)(tsc_page + 0) += 1;
                *(u64 *)(tsc_page + 8)  = scale;
                *(u64 *)(tsc_page + 16) = 0;
            }
        }break;
        
        case IA32_FS_BASE:{
            registers->fs_base = value;
        }break;
        
        case IA32_GS_BASE:{
            registers->gs_base = value;
        }break;
        
        case IA32_KERNEL_GS_BASE:{
            registers->gs_swap = value;
        }break;
        
        case /*IA32_MISC_ENABLE*/0x1a0:{
            registers->ia32_misc_enable = value;
        }break;
        
        default:{
            if(globals.debugger_mode){
                print("***** Unhandled wrmsr 0x%x <- 0x%llx\n", (u32)registers->rcx, value);
            }else{
                set_crash_information(context, CRASH_internal_error, (u64)"Unimplemented msr.");
            }
        }break;
    }
}

//_____________________________________________________________________________________________________________________
// vmcall

#if ENABLE_VSM && !defined(_WIN32)
#error Currently no VSM for lunix.
#endif

#if ENABLE_VSM
// @cleanup: factoring.
__declspec(dllimport) s32 WHvMapGpaRange(HANDLE Partition, void *SourceAddress, u64 PhysicalGuestAddress, u64 SizeInBytes, u32 Flags);
#endif

void helper_vmcall(struct context *context, struct registers *registers){
    
    if(PRINT_HOOK_EVENTS) print("[" __FUNCTION__ "] %p\n", registers->rip);
    
    //
    // https://docs.microsoft.com/en-us/virtualization/hyper-v-on-windows/tlfs/hypercalls/overview
    //
    
    u16 CallCode = (u16)registers->rcx;
    int Fast     = (int)((registers->rcx >> 16) & 1);
    // int variable_header_size = extract_bits(registers->rcx, 17, 26);
    // int nested =  (registers->rcx >> 31) & 1;
    int rep_count = extract_bits(registers->rcx, 32, 43);
    // int rep_start_index = extract_bits(registers->rcx, 38, 59);
    
    //
    // There are two calling conventions, depending on whether _fast_ is set.
    // 
    //     1) _Fast_ hypercalls are register based.
    //     2) Otherwise they are Memory based.
    //
    // The difference is only how the inputs are passed. 
    
    // Register mapping for hypercall inputs when the Fast flag is zero:
    //     rcx - Hypercall Input Value
    //     rdx - Input  Parameter GPA
    //     r8  - Output Parameter GPA
    
    struct{
        u64 rdx;
        u64 r8;
        __m128i xmm0;
        __m128i xmm1;
        __m128i xmm2;
        __m128i xmm3;
        __m128i xmm4;
        __m128i xmm5;
    } fast_buffer = {
        .rdx = registers->rdx,
        .r8  = registers->r8,
        .xmm0 = registers->simd[0].xmmi,
        .xmm1 = registers->simd[1].xmmi,
        .xmm2 = registers->simd[2].xmmi,
        .xmm3 = registers->simd[3].xmmi,
        .xmm4 = registers->simd[4].xmmi,
        .xmm5 = registers->simd[5].xmmi,
    };
    
    u64 input_gpa = registers->rdx;
    u64 output_gpa = registers->r8; // @cleanup: bounds check?
    
    registers->rax = (u64)rep_count << 32; // Assume we did everything perfectly. If we fail, we should set it to something else later.
    
    switch(CallCode){
        
        case /*HvCallSendSyntheticClusterIpi*/0xb:{
            //
            // Send an inter-processor interrupt (IPI) to a target processor.
            //
            crash_assert(Fast);
            
            struct {
                u32 Vector;
                u8  TargetVtl;
                u8  Padding[3];
                u64 ProcessorMask;
            } *Parameter = (void *)&fast_buffer;
            
            if(PRINT_HOOK_EVENTS){
                print("[HvCallSendSyntheticClusterIpi] Vector %x, TargetVtl %x, ProcessorMask %x\n", Parameter->Vector, Parameter->TargetVtl, Parameter->ProcessorMask);
            }
            
            pend_interrupt(context, registers, Parameter->Vector);
        }break;
        
        case /*HvCallNotifyLongSpinWait*/0x8:{
            
            // @cleanup: We could check the `next_timer_interrupt_time_or_zero` here to figure out more accurate
            //           timing for the timer interrupt.
            
            helper_immediately_pend_timer_interrupt(context, registers);
        }break;
        
        case /*HvCallPostMessage*/0x5c:{
            
            crash_assert(!Fast);
            
            context->registers.rax = 0;
            
            u8 *input_buffer = get_physical_memory_for_read(context, input_gpa);
            
            u32 connection_id = *(u32 *)(input_buffer + 0);
            u32 message_type  = *(u32 *)(input_buffer + 8);
            u32 payload_size  = *(u32 *)(input_buffer + 12);
            
            if(message_type == /*HV_MESSAGE_VMBUS*/1){
                
                void *payload = input_buffer + 16;
                
                vmbus_handle_message(context, connection_id, payload, payload_size);
            }else{
                set_crash_information(context, CRASH_internal_error, (u64)"Unimplemented post message type.");
            }
        }break;
        
        case /*HvCallSignalEvent*/0x5d:{
            
            crash_assert(Fast);
            
            struct {
                u32 connection_id;
                u16 flag_number; // @note: This is the index of the flag in the SIEFP. "Relative to the base flag number associated with the port"?
                u16 reserved;
            } *parameters = (void *)&fast_buffer;
            
            u32 connection_id = parameters->connection_id;
            
            if(0x2000 <= connection_id && connection_id < 0x3000){
                // 
                // VMBUS connection
                // 
                
                vmbus_handle_event(context, connection_id);
                registers->rax = 0;
                return;
            }
            
            crash_assert(false);
        }break;
        
        case 0x8001:{ // HvExtCallQueryCapabilities
            crash_assert(!Fast);
            
            crash_assert(output_gpa + 7 < context->physical_memory_size);
            
            *(u64 *)get_physical_memory_for_write(context, output_gpa) = 0;
            registers->rax = 0;
        }break;
        
        // 
        // Some stuff needed by the Vsm stuff, but not actually related to it.
        // 
        
        case /*HvCallFlushVirtualAddressSpace*/2:
        case /*HvCallFlushVirtualAddressList*/3:{
            // Sure buddy :)
            invalidate_translate_lookaside_buffers(context); // @cleanup?
        }break;
        
#if ENABLE_VSM
        case /*HvModifyVtlProtectionMask*/0xc:{
            
            // 
            // From what I can tell, there is no good way for me to accurately implement 
            // this hypercall. The reason is, that I don't think I can have multiple 
            // VMCS (Virtual Machine Control Structures) for one partition.
            // At least not using the Windows Hypervisor Platform API's.
            // 
            // The corresponding function:
            // 
            //    s32 WHvMapGpaRange(HANDLE Partition, void *SourceAddress, u64 PhysicalGuestAddress, u64 SizeInBytes, u32 Flags);
            //    
            // Does not allow me to specify a "VTL".
            // Having multiple Partitions one for each VTL also did not seem to work.
            // Mapping the same range with another Partition was complaining.
            // 
            // BUT, I have a hack idea:
            // 
            // The secure kernel only (mostly?) tries to protect itself (not readable nor writeable from normal mode) 
            // and certain sections (not readable or not executable).
            // 
            // Hence, we can simply keep all of the sections from the secure kernel but apply all the other permissions.
            // This should mean that while the secure kernel is not protected, if no one tries to take advantage of that
            // the system looks like it should.
            // 
            
            struct {
                u64 PartitionId;
                u32 MapFlags;
                u8  TargetVtl;
                u8  Reserved[3];
                u64 GpaPageList[];
            } *Parameters = Fast ? (void *)&fast_buffer : get_physical_memory_for_read(context, input_gpa);
            
            if(PRINT_VSM_EVENTS){
                
                char *read = (Parameters->MapFlags & 1) ? " Read" : "";
                char *write = (Parameters->MapFlags & 2) ? " Write" : "";
                char *execute = (Parameters->MapFlags & 4) ? " Exec" : "";
                char *user_execute = (Parameters->MapFlags & 8) ? " UserExec" : "";
                char *none = (Parameters->MapFlags  == 0) ? " None" : "";
                
                print("HvModifyVtlProtectionMask(%s): %llx %x %x%s%s%s%s%s\n", Fast ? "Fast" : "Slow", Parameters->PartitionId, Parameters->TargetVtl, Parameters->MapFlags, read, write, execute, user_execute, none);
                for(int index = 0; index < rep_count; index++){
                    print("    %p\n", Parameters->GpaPageList[index]);
                }
            }
            
            for(int index = 0; index < rep_count; index++){
                u64 Page = Parameters->GpaPageList[index];
                
                u64 Index  = Page / 2;
                u64 Nibble = Page % 2;
                
                u8 Mask = 0xf << (Nibble * 4);
                u8 Value = (Parameters->MapFlags & 0xf) << (Nibble * 4);
                
                context->vtl0_permissions[Index] &= ~Mask; // @cleanup: Bounds check.
                context->vtl0_permissions[Index] |= Value;
                
                if(globals.fuzzing){
                    if(context->amount_of_dirty_vtl0_permissions == DIRTY_VTL0_PERMISSION_CAPACITY){
                        set_crash_information(context, CRASH_timeout, (u64)"DIRTY_VTL0_PERMISSION_CAPACITY exceeded!");
                    }else{
                        context->dirty_vtl0_permssions[context->amount_of_dirty_vtl0_permissions++] = Page;
                    }
                }
            }
            
            if(Parameters->MapFlags == 0){
                // See comment above, we have to somehow "merge" the permissions for VTL0 and VTL1.
                // MapFlags == 0 probably means this is a secure kernel GPA.
                break;
            }
            
            for(int index = 0; index < rep_count; index++){
                u64 Gpa = Parameters->GpaPageList[index] << 12;  // @cleanup: maybe merge ranges?
                u8 *SourceAddress = context->physical_memory + Gpa; // @cleanup: Bounds check?
                
                // Well it seems, I cannot do mode based execution controls (separate executable bit for kernel and userspace) with `WHvMapGpaRange`.
                // So I guess a page is executable if it is executable either in user space or in kernel space.
                // As I think all pages are executable in user space, this means they are all executable... sigh.
                
                u32 flags = Parameters->MapFlags & 0x7;
                if(Parameters->MapFlags & 0x8) flags |= 4;
                
                if(context->use_hypervisor){
                    s32 WHvMapGpaRangeResult = WHvMapGpaRange(context->Partition, SourceAddress, Gpa, 0x1000, flags);
                    if(WHvMapGpaRangeResult != 0){
                        print("WHvMapGpaRangeResult = %x (%p %p 0x1000, %x)\n", WHvMapGpaRangeResult, SourceAddress, Gpa, flags);
                    }
                }
            }
            
        }break;
        
        case /*HvTranslateVirtualAddress*/0x52:{
            assert(Fast);
            
            struct {
                u64 PartitionId;
                u32 VpIndex;
                u64 ControlFlags; // Permissions / Input vtl mask.
                u64 GvaPage;
            } *Parameters = (void *)&fast_buffer;
            
            // @cleanup: Do we need more? Cr0 Cr4?
            u64 current_cr3 = context->registers.cr3;
            context->registers.cr3 = context->registers.vtl_state.cr3;
            
            if(PRINT_VSM_EVENTS) print("HvTranslateVirtualAddress %llx %d %p\n", Parameters->ControlFlags & 0x3f, Parameters->ControlFlags >> (8 * 7), Parameters->GvaPage);
            
            enum permissions permissions = 0;
            if(Parameters->ControlFlags & /*HV_TRANSLATE_GVA_VALIDATE_READ*/1)  permissions |= PERMISSION_read;
            if(Parameters->ControlFlags & /*HV_TRANSLATE_GVA_VALIDATE_WRITE*/2) permissions |= PERMISSION_write;
            if(Parameters->ControlFlags & /*HV_TRANSLATE_GVA_VALIDATE_EXEC*/4) permissions |= PERMISSION_execute;
            
            // HV_TRANSLATE_GVA_PRIVILEGE_EXEMPT    0x08 
            // HV_TRANSLATE_GVA_SET_PAGE_TABLE_BITS 0x10 
            // HV_TRANSLATE_GVA_TLB_FLUSH_INHIBIT   0x20
            
            int set_page_table_bits = (Parameters->ControlFlags & /*HV_TRANSLATE_GVA_SET_PAGE_TABLE_BITS*/0x10) != 0;
            
            context->skip_setting_permission_bits += !set_page_table_bits;
            
            u64 page_number = Parameters->GvaPage;
            u64 pte;
            
            u64 physical_address = translate_page_number_to_physical(context, page_number, permissions, &pte);
            
            u64 return_code = /*HvTranslateGvaSuccess*/0;
            if(!(pte & PAGE_TABLE_present)){
                return_code = /*HvTranslateGvaPageNotPresent*/1;
            }else if(physical_address >= globals.snapshot.physical_memory_size){
                return_code = /*HvTranslateGvaGpaUnmapped*/4;
            }else{
                u64 page_index = physical_address >> 12;
                u64 permission_index  = page_index / 2;
                u64 permission_nibble = page_index % 2;
                
                u8 value = (context->vtl0_permissions[permission_index] >> (permission_nibble * 4)) & 0xf;
                
                if((permissions & value) != permissions){
                    
                    if((permissions & PERMISSION_write) && !(value & PERMISSION_write)){
                        return_code = /*WHvTranslateGvaResultGpaNoWriteAccess*/6;
                    }else if((permissions & PERMISSION_read) && !(value & PERMISSION_read)){
                        return_code = /*WHvTranslateGvaResultGpaNoReadAccess*/5;
                    }else{
                        // ummm what to do here?
                        print("Invalid case in HvTranlateVirtualAddress\n");
                        handle_debugger(context);
                    }
                }
            }
            
            *(u64 *)&registers->simd[1].xmmi = return_code | (/*HvCacheTypeX64WriteBack*/6ull << 32);
            *((u64 *)&registers->simd[1].xmmi + 1) = physical_address>>12;
            
            if(PRINT_VSM_EVENTS) print("       -> %d %p\n", return_code, physical_address);
            
            context->skip_setting_permission_bits -= !set_page_table_bits;
            
            context->registers.cr3 = current_cr3;
        }break;
#endif
        
        // 
        // Vsm stuff.
        // Reference: https://learn.microsoft.com/en-us/virtualization/hyper-v-on-windows/tlfs/vsm
        // 
        
        case /*HvCallGetVpRegisters*/0x50:{
            crash_assert(Fast);
            
            struct {
                u64 PartitionId;
                u32 VpIndex;
                u8 TargetVtl;
                u8 padding[3];
                u32 register_names[]; // I think this would be an array of rep_count registers?
            } *Parameters = (void *)&fast_buffer;
            
            if(PRINT_VSM_EVENTS){
                print("HvCallGetVpRegisters %llx %x %x\n", Parameters->PartitionId, Parameters->VpIndex, Parameters->TargetVtl);
                for(int index = 0; index < rep_count; index++){
                    print("    %x\n", Parameters->register_names[index]);
                }
            }
            
            crash_assert(rep_count == 1);
            
            // 
            // The fastpath output stuff is pretty crazy, the output comes immediately after the input, 
            // but aligned to the next register. In this case that would start at XMM1, But in the future,
            // if we support looking up more than one register, there would be some weird math involved.
            // 
            u64 output = 0, output_high = 0;
            switch(Parameters->register_names[0]){
                case /*HvRegisterVsmCapabilities/HV_X64_REGISTER_VSM_CAPABILITIES*/0xD0006:{
                    // 63 Dr6Shared
                    // 62:47 MbecVtlMask
                    // 46 DenyLowerVtlStartup
                    output = 0;
                }break;
                case /*HvRegisterVsmCodePageOffsets*/0xD0002:{
                    // UINT64 VtlCallOffset : 12;
                    // UINT64 VtlReturnOffset : 12;
                    output = 15 | (40 << 12);
                }break;
                
                // 
                // I assume for now that you are trying to read the other guys registers!
                // 
                case 0x00020010: output = context->registers.vtl_state.rip; break;
                case 0x00020004: output = context->registers.vtl_state.rsp; break;
                case 0x00020011: output = context->registers.vtl_state.rflags; break;
                case 0x00040000: output = context->registers.vtl_state.cr0; break;
                case 0x00040002: output = context->registers.vtl_state.cr3; break;
                case 0x00040003: output = context->registers.vtl_state.cr4; break;
                // case 0x00050005: output = context->registers.vtl_state.dr7; break;
                // case 0x00050004: output = context->registers.vtl_state.dr6; break;
                // case 0x00090012: output = context->registers.vtl_state.cr8; break;
                
                case 0x00070000: output = (u64)context->registers.vtl_state.idt_limit << 48; output_high = context->registers.vtl_state.idt_base; break;
                case 0x00070001: output = (u64)context->registers.vtl_state.gdt_limit << 48; output_high = context->registers.vtl_state.gdt_base; break;
                
                case 0x00060001: output = *(u64 *)&context->registers.vtl_state.cs; output_high = ((u64 *)&context->registers.vtl_state.cs)[1]; break;
                case 0x00060003: output = *(u64 *)&context->registers.vtl_state.ds; output_high = ((u64 *)&context->registers.vtl_state.ds)[1]; break;
                case 0x00060000: output = *(u64 *)&context->registers.vtl_state.es; output_high = ((u64 *)&context->registers.vtl_state.es)[1]; break;
                case 0x00060004: output = *(u64 *)&context->registers.vtl_state.fs; output_high = ((u64 *)&context->registers.vtl_state.fs)[1]; break;
                case 0x00060005: output = *(u64 *)&context->registers.vtl_state.gs; output_high = ((u64 *)&context->registers.vtl_state.gs)[1]; break;
                case 0x00060002: output = *(u64 *)&context->registers.vtl_state.ss; output_high = ((u64 *)&context->registers.vtl_state.ss)[1]; break;
                case 0x00060007: output = *(u64 *)&context->registers.vtl_state.tr; output_high = ((u64 *)&context->registers.vtl_state.tr)[1]; break;
                case 0x00060006: output = *(u64 *)&context->registers.vtl_state.ldt; output_high = ((u64 *)&context->registers.vtl_state.ldt)[1]; break;
                
                case 0x00080002: output = context->registers.vtl_state.gs_swap; break;
                
                case 0x00080001: output = context->registers.vtl_state.ia32_efer; break;
                case 0x00080004: output = context->registers.vtl_state.ia32_pat; break;
                
                case 0x00080000: output = context->registers.vtl_state.ia32_tsc; break;
                case 0x0008007B: output = context->registers.vtl_state.ia32_tsc_aux; break;
                
                case 0x00080009: output = context->registers.vtl_state.ia32_lstar; break;
                case 0x0008000A: output = context->registers.vtl_state.ia32_cstar; break;
                case 0x00080008: output = context->registers.vtl_state.ia32_star; break;
                case 0x0008000B: output = context->registers.vtl_state.ia32_fmask; break;
                
                case 0x00090001: output = context->registers.vtl_state.hv_x64_msr_hypercall_page; break;
                case 0x00090017: output = context->registers.vtl_state.hv_x64_msr_reference_tsc_page; break;
                case 0x00090013: output = context->registers.vtl_state.hv_x64_msr_vp_assist_page; break;
                
                // 
                // Hmm, are these supposed to be private as well?
                // 
                case 0x00080003: output = context->registers.ia32_apic_base; break;
                
                case /*HvX64RegisterSysenterCs */0x00080005: output = context->registers.ia32_sep_sel; break;
                case /*HvX64RegisterSysenterRip*/0x00080006: output = context->registers.ia32_sep_rip; break;
                case /*HvX64RegisterSysenterRsp*/0x00080007: output = context->registers.ia32_sep_rsp; break;
                
                default:{
                    print("**** Unhandled GetVpRegister 0x%x!\n", Parameters->register_names[0]);
                    handle_debugger(context);
                }break;
            }
            
            if(PRINT_VSM_EVENTS) print("        -> 0x%p %p\n", output, output_high);
            
            *(u64 *)&registers->simd[1].xmmi = output;
            *((u64 *)&registers->simd[1].xmmi + 1) = output_high;
        }break;
        
        case /*HvCallSetVpRegisters*/0x51:{
            crash_assert(Fast);
            
            struct {
                u64 PartitionId;
                u32 VpIndex;
                u8 TargetVtl;
                u8 padding[3];
                struct{
                    u32 register_name;
                    u32 padding[3];
                    union{
                        struct{
                            u64 value_low;
                            u64 value_high;
                        };
                        struct segment segment;
                    };
                }mapping[]; // I think this would be an array of rep_count registers?
            } *Parameters = (void *)&fast_buffer;
            
            if(PRINT_VSM_EVENTS){
                print("HvCallSetVpRegisters %llx %x %x\n", Parameters->PartitionId, Parameters->VpIndex, Parameters->TargetVtl);
                for(int index = 0; index < rep_count; index++){
                    print("    %x %llx %llx\n", Parameters->mapping[index].register_name, Parameters->mapping[index].value_low, Parameters->mapping[index].value_high);
                }
            }
            
            crash_assert(rep_count == 1);
            
            switch(Parameters->mapping[0].register_name){
                case /*HV_REGISTER_VSM_PARTITION_CONFIG*/0xd0007:{
                    struct {
                        u64 EnableVtlProtection : 1;
                        u64 DefaultVtlProtectionMask : 4;
                        u64 ZeroMemoryOnReset : 1;
                        u64 DenyLowerVtlStartup : 1;
                        u64 Reserved : 2;
                        u64 InterceptVpStartup : 1;
                        u64 Reserved2 : 54;
                    } *config = (void *)&Parameters->mapping[0].value_low;
                    
                    if(PRINT_VSM_EVENTS){
                        print("HV_REGISTER_VSM_PARTITION_CONFIG:\n");
                        print("    config->EnableVtlProtection = %llx\n", config->EnableVtlProtection);
                        print("    config->DefaultVtlProtectionMask = %llx\n", config->DefaultVtlProtectionMask);
                        print("    config->ZeroMemoryOnReset = %llx\n", config->ZeroMemoryOnReset);
                        print("    config->DenyLowerVtlStartup = %llx\n", config->DenyLowerVtlStartup);
                        print("    config->InterceptVpStartup = %llx\n", config->InterceptVpStartup);
                    }
                }break;
                
                case /*HvRegisterVsmVpSecureConfigVtl0*/0xd0010:{
                    
                    struct {
                        u64 MbecEnabled : 1;
                        u64 TlbLocked : 1;
                        u64 Reserved : 62;
                    } *config = (void *)&Parameters->mapping[0].value_low;
                    
                    if(PRINT_VSM_EVENTS){
                        print("HvRegisterVsmVpSecureConfigVtl0:\n");
                        print("    config->MbecEnabled = %llx\n", config->MbecEnabled);
                        print("    config->TlbLocked = %llx\n", config->TlbLocked);
                    }
                }break;
                
                case /*HvRegisterVsmVina*/0xd0005:{
                    
                    struct {
                        u64 Vector : 8;
                        u64 Enabled : 1;
                        u64 AutoReset : 1;
                        u64 AutoEoi : 1;
                        u64 Reserved : 52;
                    } *config = (void *)&Parameters->mapping[0].value_low;
                    
                    if(PRINT_VSM_EVENTS){
                        print("HvRegisterVsmVina:\n");
                        print("    config->Vector = %llx\n", config->Vector);
                        print("    config->Enabled = %llx\n", config->Enabled);
                        print("    config->AutoReset = %llx\n", config->AutoReset);
                        print("    config->AutoEoi = %llx\n", config->AutoEoi);
                    }
                }break;
                
                case /*HvX64RegisterCrInterceptControl*/0xE0000:{
                    if(PRINT_VSM_EVENTS){
                        print("HvX64RegisterCrInterceptControl:\n");
                        print("    %p\n", Parameters->mapping[0].value_low); // ?
                    }
                }break;
                case /*HvX64RegisterCrInterceptCr0Mask*/0xE0001:{
                    if(PRINT_VSM_EVENTS){
                        print("HvX64RegisterCrInterceptCr0Mask:\n");
                        print("    %p\n", Parameters->mapping[0].value_low); // ?
                    }
                }break;
                case /*HvX64RegisterCrInterceptCr4Mask*/0xE0002:{
                    if(PRINT_VSM_EVENTS){
                        print("HvX64RegisterCrInterceptCr4Mask:\n");
                        print("    %p\n", Parameters->mapping[0].value_low); // ?
                    }
                }break;
                case /*HvX64RegisterCrInterceptIa32MiscEnableMask*/0xE0003:{
                    if(PRINT_VSM_EVENTS){
                        print("HvX64RegisterCrInterceptIa32MiscEnableMask:\n");
                        print("    %p\n", Parameters->mapping[0].value_low); // ?
                    }
                }break;
                
                case /*HvRegisterVpAssistPage*/0x90013:{
                    // @note: Concerning!
                    context->registers.vtl_state.hv_x64_msr_vp_assist_page = Parameters->mapping[0].value_low; // I assume for now that you are trying to read the other guys registers?
                }break;
                
                
                // @note: These are set during SkpgxDefeatureProcessorForBugCheck, other than cr8 I don't think any other are ever set.
                case 0x00020011: context->registers.vtl_state.rflags = Parameters->mapping[0].value_low; break;
                
                case 0x00040003: context->registers.vtl_state.cr4 = Parameters->mapping[0].value_low; break;
                case 0x00040004: context->registers.vtl_state.cr8 = Parameters->mapping[0].value_low; break; // @note: Documentation says this is cr5, which does not exist, but the corresponding sekurekernel function is called 'ShvlSetNormalIrql'
               
                case 0x00060006: context->registers.vtl_state.ldt = Parameters->mapping[0].segment; break;
                case 0x00070000: context->registers.vtl_state.idt_limit = Parameters->mapping[0].value_low >> 48; context->registers.vtl_state.idt_base = Parameters->mapping[0].value_high; break;
                case 0x00070001: context->registers.vtl_state.gdt_limit = Parameters->mapping[0].value_low >> 48; context->registers.vtl_state.gdt_base = Parameters->mapping[0].value_high; break;
                
                case 0x00080002: context->registers.vtl_state.gs_swap      = Parameters->mapping[0].value_low; break;
                case 0x00080001: context->registers.vtl_state.ia32_efer    = Parameters->mapping[0].value_low; break;
                case 0x00080004: context->registers.vtl_state.ia32_pat     = Parameters->mapping[0].value_low; break;
                case 0x00080005: {} break; // Sysenter CS not sure we have that?
                case 0x00080000: context->registers.vtl_state.ia32_tsc     = Parameters->mapping[0].value_low; break;
                case 0x0008007B: context->registers.vtl_state.ia32_tsc_aux = Parameters->mapping[0].value_low; break;
                case 0x00080009: context->registers.vtl_state.ia32_lstar   = Parameters->mapping[0].value_low; break;
                case 0x0008000A: context->registers.vtl_state.ia32_cstar   = Parameters->mapping[0].value_low; break;
                case 0x00080008: context->registers.vtl_state.ia32_star    = Parameters->mapping[0].value_low; break;
                case 0x0008000B: context->registers.vtl_state.ia32_fmask   = Parameters->mapping[0].value_low; break;
                
                default:{
                    print("**** Unhandled SetVpRegister 0x%x!\n", Parameters->mapping[0].register_name);
                    if(globals.fuzzing){
                        set_crash_information(context, CRASH_internal_error, (u64)"Unhandled SetVpRegister");
                    }else{
                        handle_debugger(context);
                    }
                }break;
            }
            
        }break;
        
        case /*HvCallEnablePartitionVtl*/0x0d:{
            crash_assert(Fast);
            
            struct {
                u64 TargetPartitionId;
                u8 TargetVtl;
                u8 Flags;
                u8 Reserved[6];
            } *Parameters = (void *)&fast_buffer;
            
            if(PRINT_VSM_EVENTS) print("HvCallEnablePartitionVtl %llx %x %x\n", Parameters->TargetPartitionId, Parameters->TargetVtl, Parameters->Flags);
            
            u64 permission_size = (globals.snapshot.physical_memory_size / 0x1000) / 2; // 4 bits per physical page.
            context->vtl0_permissions = os_allocate_memory(permission_size);
            memset(context->vtl0_permissions, 0xff, permission_size);
        }break;
        
        case /*HvEnableVpVtl*/0x0f:{
            crash_assert(!Fast);
            
            u8 *input_buffer = get_physical_memory_for_read(context, input_gpa);
            
            struct {
                u64 TargetPartitionId;
                u32 VpIndex;
                u8 TargetVtl;
                u8 Reserved[3];
                
                struct{
                    u64 Rip;
                    u64 Rsp;
                    u64 Rflags;
                    
                    struct segment cs;
                    struct segment ds;
                    struct segment es;
                    struct segment fs;
                    struct segment gs;
                    struct segment ss;
                    struct segment tr;
                    struct segment ldtr;
                    
                    struct {u16 padding[3]; u16 Limit; u64 Base; } idtr, gdtr;
                    
                    u64 Efer;
                    u64 Cr0;
                    u64 Cr3;
                    u64 Cr4;
                    u64 MsrCrPat;
                } InitialVpContext;
            } *Parameters = (void *)input_buffer;
            
            if(Parameters->VpIndex != 0){
                registers->rax = 0xE; // @cleanup: Does this not need some error bit?
                break;
            }
            
            if(PRINT_VSM_EVENTS){
                print("HvEnableVpVtl %llx %x %x\n", Parameters->TargetPartitionId, Parameters->VpIndex, Parameters->TargetVtl);
                
                print("Rip %p Rsp %p Rflags %p (", Parameters->InitialVpContext.Rip, Parameters->InitialVpContext.Rsp, Parameters->InitialVpContext.Rflags); print_flags(Parameters->InitialVpContext.Rflags, stdout); print(")\n");
                print("cs = "); print_segment(Parameters->InitialVpContext.cs);
                print("ds = "); print_segment(Parameters->InitialVpContext.ds);
                print("es = "); print_segment(Parameters->InitialVpContext.es);
                print("fs = "); print_segment(Parameters->InitialVpContext.fs);
                print("gs = "); print_segment(Parameters->InitialVpContext.gs);
                print("ss = "); print_segment(Parameters->InitialVpContext.ss);
                print("tr = "); print_segment(Parameters->InitialVpContext.tr);
                print("ldtr = "); print_segment(Parameters->InitialVpContext.ldtr);
                
                print("idtl = 0x%x idtr = %p\n", Parameters->InitialVpContext.idtr.Limit, Parameters->InitialVpContext.idtr.Base);
                print("gdtl = 0x%x gdtr = %p\n", Parameters->InitialVpContext.gdtr.Limit, Parameters->InitialVpContext.gdtr.Base);
                
                print("Efer %p, Cr0 %p, Cr3 %p, Cr4 %p, MsrCrPat %p\n", Parameters->InitialVpContext.Efer, Parameters->InitialVpContext.Cr0, Parameters->InitialVpContext.Cr3, Parameters->InitialVpContext.Cr4, Parameters->InitialVpContext.MsrCrPat);
            }
            
            registers->vtl_state.rip       = Parameters->InitialVpContext.Rip;
            registers->vtl_state.rsp       = Parameters->InitialVpContext.Rsp;
            registers->vtl_state.rflags    = Parameters->InitialVpContext.Rflags;
            registers->vtl_state.cs        = Parameters->InitialVpContext.cs;
            registers->vtl_state.ds        = Parameters->InitialVpContext.ds;
            registers->vtl_state.es        = Parameters->InitialVpContext.es;
            registers->vtl_state.fs        = Parameters->InitialVpContext.fs;
            registers->vtl_state.gs        = Parameters->InitialVpContext.gs;
            registers->vtl_state.ss        = Parameters->InitialVpContext.ss;
            registers->vtl_state.tr        = Parameters->InitialVpContext.tr;
            registers->vtl_state.ldt       = Parameters->InitialVpContext.ldtr;
            registers->vtl_state.idt_base  = Parameters->InitialVpContext.idtr.Base;
            registers->vtl_state.idt_limit = Parameters->InitialVpContext.idtr.Limit;
            registers->vtl_state.gdt_base  = Parameters->InitialVpContext.gdtr.Base;
            registers->vtl_state.gdt_limit = Parameters->InitialVpContext.gdtr.Limit;
            registers->vtl_state.ia32_efer = Parameters->InitialVpContext.Efer;
            registers->vtl_state.cr0       = Parameters->InitialVpContext.Cr0;
            registers->vtl_state.cr3       = Parameters->InitialVpContext.Cr3;
            registers->vtl_state.cr4       = Parameters->InitialVpContext.Cr4;
            registers->vtl_state.ia32_pat  = Parameters->InitialVpContext.MsrCrPat; // Is this correct?
            
            // @cleanup: Why do we have both of these?
            registers->vtl_state.fs_base = Parameters->InitialVpContext.fs.base;
            registers->vtl_state.gs_base = Parameters->InitialVpContext.gs.base;
            
            // @note: Each vtl has its own local apic. Not sure what the initialization is...
            registers->vtl_state.local_apic.destination_format_register = 0xffffffff; 
            registers->vtl_state.local_apic.spurious_interrupt_vector_register = 0xff;
            
            registers->vtl_state.local_apic.local_vector_table.timer_register = /*masked*/0x10000;
            registers->vtl_state.local_apic.local_vector_table.thermal_sensor_register = /*masked*/0x10000;
            registers->vtl_state.local_apic.local_vector_table.performance_monitoring_counters_register = /*masked*/0x10000;
            registers->vtl_state.local_apic.local_vector_table.lint0_register = /*masked*/0x10000;
            registers->vtl_state.local_apic.local_vector_table.lint1_register = /*masked*/0x10000;
            registers->vtl_state.local_apic.local_vector_table.error_register = /*masked*/0x10000;
            
            registers->vtl_state.local_apic.highest_interrupt_in_service = -1;
            registers->vtl_state.local_apic.highest_pending_interrupt    = -1;
        }break;
        
        case /*HvCallVtlCall*/0x11:
        case /*HvCallVtlReturn*/0x12:{
            if(PRINT_VSM_EVENTS) print("HVCallVtl%s\n", CallCode == 0x11 ? "Call" : "Return");
            
            // We "control" the vmcall through the hypercall page, so for now this is fine I think.
            context->registers.rip += 3;
            
            context->registers.vtl_state.current_vtl += (CallCode == 0x11) ? 1 : -1;
            
            // I think we should always take the lower assist page.
            u64 vp_assist_msr = (CallCode == /*HvCallVtlCall*/0x11) ? registers->hv_x64_msr_vp_assist_page : context->registers.vtl_state.hv_x64_msr_vp_assist_page;
            
            u8 *vp_assist_page = get_physical_memory_for_write(context, vp_assist_msr & ~0xfff);
            crash_assert(vp_assist_page);
            
            switch_vtl(&context->registers);
            
            struct{
                u32 EntryReason;
                u32 VinaAsserted;
                u64 VtlReturnX64Rax;
                u64 VtlReturnX64Rcx;
            } *vtl_control = (void *)(vp_assist_page + 8);
            
            if(CallCode == /*HvCallVtlCall*/0x11){
                vtl_control->EntryReason = /*HvVtlEntryVtlCall*/1;
            }else{
                context->registers.rax = vtl_control->VtlReturnX64Rax;
                context->registers.rcx = vtl_control->VtlReturnX64Rcx;
            }
            
            invalidate_translate_lookaside_buffers(context); // We need to invalidate the tlb because the cr3 changed (we could do this only for jit, but whatever!).
        }break;
        
        default:{
            if(globals.debugger_mode){
                print("****** Unhandled vmcall 0x%x at %p\n", (u16)registers->rcx, guest_read(u64, registers->rsp));
                handle_debugger(context);
            }else{
                set_crash_information(context, CRASH_internal_error, (u64)"Unimplmented vm call.");
            }
        }break;
    }
}


