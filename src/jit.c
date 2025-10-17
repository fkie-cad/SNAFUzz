
//
// The general structure of the JIT is as follows:
//     
//     * The JIT state is completely thread local and contained in the 'context' structure of each thread.
//       It contains:
//          * A 'jit_pool', which is rwx-memory containing the JIT-compiled code.
//          * A 'jit_block_table', mapping guest physical addresses to JIT code for the block starting there.
//          * An 'instruction_cache', which speeds up the above mapping for recently executed pages.
//     
//     
//     * While executing, we keep track of the _physical rip_. We first check whether this rip is contained
//       in the instruction cache (at index 'physical_rip & (INSTRUCTION_CACHE_SIZE - 1)').
//       Otherwise, we call 'handle_instruction_cache_miss', which checks the 'jit_block_table'.
//       If we can also not find the block in the 'jit_block_table', we call 'emit_jit' 
//       and insert the resulting JIT-code into the 'jit_block_table' and the 'instruction_cache'.
//     
//         
//     * 'emit_jit' decodes instructions one at a time and linearly emits equivalent JIT-code into the 'jit_pool'.
//        For example, the instruction 'mov rcx, rdx' would result in the JIT
//        
//           mov rcx, dword ptr [registers + .rdx]
//           mov dword ptr [registers + .rcx], rcx
//           
//        Where 'registers' is a non-volatile register established when entering the jit, containing '&context->registers'.
//        For memory accesses like 'mov rcx, [rdx]' the resulting JIT looks like:
//           
//           mov rax, [registers + .rdx]
//           mov r8, rax
//           
//           call jit_guest_read_wrapper[/*log2(size=8)*/4]
//           
//           mov rcx, [rax]
//           mov [registers + .rcx], rcx
//         
//       Where these 'jit_guest_read_wrapper's are in-JIT functions which are created during 'initialize_jit'
//       and are used to 
//           * first try to translate the address to the host page using the 'context->read_tlb'
//           * and if that fails call 'guest_read_size(context, context->jit_scratch, address /*coming from r8*/, 8, PERMISSION_read)'.
//           
//       'emit_jit' translates instructions in this way until it hits a terminating instruction like a jump, or until
//       it would cover more than two pages. In the end the JIT-block calls 'context->jit_exit', which acts as the function epilog
//       for the JIT-code.
//     
//     
//     * Once it has JIT-code corresponding to a physical rip, the run loop calls
//     
//         void (context->jit_entry)(struct context *context, struct registers *registers, struct instruction_cache_entry *entry);
//         
//       which set up non-volatile registers for 'context', '&context->registers', 'context->registers.rip' and 'context->fuzz_case_timeout'
//       and then jumps to 'entry->instruction_jit'.
//     
// Complications:
// 
// There are two factors which make writing the JIT especially hard: 
//     1) Instructions can span two (virtual!) pages.
//     2) Code pages can be re-written in order to contain different data.
// 
// To deal with (1), the 'jit_block's contain the starting 'physical_rip'
// and (if they span more than one page) the 'physical_second_page'.
// 
// To deal with (2), we keep track of which physical page has been executed
// at 'context->physical_memory_executed'. If a physical page which was previously
// executed is written, we exit with a 'CRASH_reset_jit' (or 'CRASH_internal_error' 
// if 'CRASH_ON_SELF_MODIFYING_CODE_DURING_FUZZING' is set).
// 

//
// Since it gets confusing to talk about registers on the 'host' (the registers we use to emulate)
// and in the 'guest' the registers coming from 'registers'. We introduce static types for them here.
//

struct guest_register{ enum register_encoding encoding; };
#define guest(reg) ((struct guest_register){reg})

struct host_register{ enum register_encoding encoding; };
#define host(reg) ((struct host_register){reg})


u8 *emit_get_current(struct context *context){
    return context->jit_pool.current;
}

void emit_bytes(struct context *context, u8 *bytes, u64 amount){
    
    while((s64)(context->jit_pool.current - context->jit_pool.base + amount) > context->jit_pool.committed){
        u8 *new_base = context->jit_pool.base + context->jit_pool.committed;
        int success = os_commit_memory(new_base, 0x1000000, /*executable*/true);
        context->jit_pool.committed += 0x1000000;
        if(!success){
            print("Internal Error: JIT out of memory. Could not commit during jit.\n");
            os_panic(1);
        }
    }
    
    memcpy(context->jit_pool.current, bytes, amount);
    context->jit_pool.current += amount;
}

#define emit(...) emit_bytes(context, (u8 []){ __VA_ARGS__ }, sizeof((u8 []){ __VA_ARGS__ }))

#define emit16(_u16) emit_bytes(context, (u8 *)&(u16){_u16}, 2)
#define emit32(_u32) emit_bytes(context, (u8 *)&(u32){_u32}, 4)
#define emit64(_u64) emit_bytes(context, (u8 *)&(u64){_u64}, 8)

#define make_modrm(mod, r, m) (u8)(((mod & 3) << 6) | (r & 7) << 3 | (m & 7) << 0)
#define make_sib(scale, index, base) (u8)(((scale & 3) << 6) | (index & 7) << 3 | (base & 7) << 0)

#define make_vex(R, VVVV, L, pp) (u8)(((~(R) & 1) << 7) | ((~(VVVV) & 0b1111) << 3) | (((L) & 1) << 2) | (((pp) & 3)))
#define make_two_byte_vex(R, X, B, mmmmm, W, VVVV, L, pp) (u8)((((~(R)) & 1) << 7) | (((~(X)) & 1) << 6) | (((~(B)) & 1) << 5) | (mmmmm)), (u8)((((W) & 1) << 7) | ((~(VVVV) & 0b1111) << 3) | (((L) & 1) << 2) | (((pp) & 3)))


//_____________________________________________________________________________________________________________________
// emit_inst - macro magic

// 
// "By merely writing this macro, I am a horrible person who deserves terrible things. 
//  I hope that exposure to this terror does not warp your mind too much. Use this knowledge with care.
//                                                                 - Mike Ash 20.03.2015"
// https://mikeash.com/pyblog/friday-qa-2015-03-20-preprocessor-abuse-and-optional-parentheses.html
#define PASTE(x, ...) x ## __VA_ARGS__
#define EVALUATING_PASTE(x, ...) PASTE(x, __VA_ARGS__)
#define EXTRACT(...) EXTRACT __VA_ARGS__
#define NOTHING_EXTRACT
#define UNPAREN(x) EVALUATING_PASTE(NOTHING_, EXTRACT x)


#define NEED_SMALL_REX(R, B, X) (((R) >= 4) | ((B) >= 4) | ((X) >= 4))

#define NEED_SMALL_REX_sib(opsize, mode, R, scale, X, B) NEED_SMALL_REX(R, B, X)
#define NEED_SMALL_REX_reg(opsize, R, B) NEED_SMALL_REX(R, B, 0)
#define NEED_SMALL_REX_regm(opsize, R, B) NEED_SMALL_REX(R, B, 0)
#define NEED_SMALL_REX_regm8(opsize, R, B) NEED_SMALL_REX(R, B, 0)
#define NEED_SMALL_REX_regm32(opsize, R, B) NEED_SMALL_REX(R, B, 0)

#define REX(W, R, B, X) ((W) | (((R) >= 8) ? REXR : 0) | (((B) >= 8) ? REXB : 0) | (((X) >= 8) ? REXX : 0))

#define REX_sib(opsize, mode, R, scale, X, B) REX(((opsize) == 8) ? REXW : 0, R, B, X)
#define REX_reg(opsize, R, B) REX(((opsize) == 8) ? REXW : 0, R, B, 0)
#define REX_regm(opsize, R, B) REX(((opsize) == 8) ? REXW : 0, R, B, 0)
#define REX_regm8(opsize, R, B) REX(((opsize) == 8) ? REXW : 0, R, B, 0)
#define REX_regm32(opsize, R, B) REX(((opsize) == 8) ? REXW : 0, R, B, 0)

#define OPSIZE_sib(opsize, ...) opsize
#define OPSIZE_reg(opsize, ...) opsize
#define OPSIZE_regm(opsize, ...) opsize
#define OPSIZE_regm8(opsize, ...) opsize
#define OPSIZE_regm32(opsize, ...) opsize

#define modrm_sib(opsize, mode, R, scale, X, B) make_modrm(mode, R, REGISTER_SP), make_sib(scale, X, B)
#define modrm_reg(opsize, R, B) make_modrm(MOD_REG, R, B)
#define modrm_regm(opsize, R, B) make_modrm(MOD_REGM, R, B)
#define modrm_regm8(opsize, R, B) make_modrm(MOD_REGM_OFF8, R, B)
#define modrm_regm32(opsize, R, B) make_modrm(MOD_REGM_OFF32, R, B)

#define emit_inst(op, modrm, ...) {              \
    if(OPSIZE_##modrm == 2) emit(0x66);          \
    if(REX_##modrm) emit(0x40 | REX_##modrm);    \
    else if(OPSIZE_##modrm == 1 && NEED_SMALL_REX_##modrm) emit(0x40); \
    emit(UNPAREN(op), modrm_##modrm, __VA_ARGS__);        \
}

//_____________________________________________________________________________________________________________________
// VTUNE Jit profiling code

#define VTUNE_JIT_PROFILING 0
#if VTUNE_JIT_PROFILING
#include "C:\Program Files (x86)\Intel\oneAPI\vtune\latest\sdk\include\jitprofiling.h"

void vtune_jit_profiling_routine(u8 *start, u8 *end, char *format, ...){
    if(!globals.fuzzing) return;
    
    va_list va;
    va_start(va, format);
    
    char buffer[0x20];
    vsnprintf(buffer, sizeof(buffer), format, va);
    
    va_end(va);
    
    iJIT_Method_Load event = {0};
    event.method_id = iJIT_GetNewMethodID();
    event.method_name = buffer;
    event.method_load_address = start;
    event.method_size = (u32)(end - start);
    iJIT_NotifyEvent(iJVM_EVENT_TYPE_METHOD_LOAD_FINISHED, (void*)&event);
}
#else
#define vtune_jit_profiling_routine(...)
#endif

// 
// @note: @WARNING: We should not exceed 6 non-volatile registers as the system-V calling convention only supports 6 non-volatiles.
//                  Currently we support both te system-v and the Windows-x64 calling convention.
//    
//    Register   System-V    Windows-x64
//      rax          v           v
//      rcx          v           v
//      rdx          v           v
//      rbx          nv          nv
//      rsp          nv          nv
//      rbp          nv          nv
//      rsi          v           nv
//      rdi          v           nv
//      r8           v           v
//      r9           v           v
//      r10          v           v
//      r11          v           v
//      r12          nv          nv
//      r13          nv          nv
//      r14          nv          nv
//      r15          nv          nv
//    
// We assume there are non-volatile registers and there are volatile-argument registers.
// Because of the table above, we use the non-volatile RBP and RBX for the `context` and `registers`.
// @note: @WARNING: We cannot use RBP without an offset ([rbp]). Hence, it cannot be `registers` as we want to use rax sometimes.
// This allows us to skip checking that they are not extended registers (r8-r15) in some places.
// 

#if _WIN32

#define ARG_REG_1 REGISTER_C
#define ARG_REG_2 REGISTER_D
#define ARG_REG_3 REGISTER_R8
#define ARG_REG_4 REGISTER_R9

// #define NONVOL_flex                    REGISTER_SI
#define NONVOL_flex                    REGISTER_R13

#else

// @note: I guess these go _backwards_ 7, 6, 2, 1
#define ARG_REG_1 REGISTER_DI
#define ARG_REG_2 REGISTER_SI
#define ARG_REG_3 REGISTER_D
#define ARG_REG_4 REGISTER_C

#define NONVOL_flex                    REGISTER_R13
#endif


#define NONVOL_count                   5
#define NONVOL_context                 REGISTER_BP
#define NONVOL_registers               REGISTER_B

#define NONVOL_rip                     REGISTER_R15
#define NONVOL_timeout_counter         REGISTER_R14


//                8                      8*(n+1)                                  RSP-0x20          v RSP
// RETURN ADDRESS | NON_VOLATILE_REGISTERS | POTENTIALLY_8PADDING | JIT_TEMP_STORAGE | HOMING_SPACE | 
//
// Currently, we use 5 non-volatiles -> 0x30 space for non-volatiles and the return address.
// The biggest registers we have are the YMM registers which are 0x20 bytes.
// Hence, the JIT_TEMP_STORAGE is 0x20. We allocate the NON_VOLATILE_REGISTERS space by push/pop,
// therefore its not part of the JIT_STACK_ALLOCATION_SIZE.
//                                                                               - Pascal Beyer 13.02.2023

#define JIT_HOMING_SPACE_SIZE     0x20
#define JIT_STACK_ALLOCATION_SIZE (((JIT_HOMING_SPACE_SIZE + 8 * (NONVOL_count + 1)) + 7) & ~7)

void initialize_jit(struct context *context){
    
    memset(context->instruction_cache, 0xff, sizeof(context->instruction_cache));
    
    {
        // 
        // Mark the whole of physical memory as not having been executed.
        // 
        u64 memory_size = globals.snapshot.physical_memory_size;
        u64 page_bitmap_size = (memory_size / 0x1000) / 8;
        memset(context->physical_memory_executed, 0, page_bitmap_size);
    }
    
    if(context->jit_pool.base){
        // 
        // Reinitialize the 'jit_pool'.
        // 
        context->jit_pool.current = context->jit_pool.base;
        
        // We should not reset the jit if this option is true.
        assert(!(CRASH_ON_SELF_MODIFYING_CODE_DURING_FUZZING && globals.fuzzing) || globals.debugger_mode);
    }else{   
        //
        // Initialize the 'jit_pool'.
        //
        u64 reserved = 0x1000000000;
        u8 *rwx_memory = os_reserve_memory(reserved);
        if(!rwx_memory){
            print("Error: Could not reserve rwx-memory for jit pool.\n");
            os_panic(1);
        }
        
        context->jit_pool.committed = 0;
        context->jit_pool.reserved = reserved;
        context->jit_pool.current  = rwx_memory;
        context->jit_pool.base     = rwx_memory;
    }
    
    if(context->jit_block_table.entries){
        // 
        // Reinitialize the 'jit_block_table'.
        // 
        memset(context->jit_block_table.entries, 0, (context->jit_block_table.maximal_size_minus_one + 1) * sizeof(*context->jit_block_table.entries));
        context->jit_block_table.amount_of_entries = 0;
    }else{   
        //
        // Initialize the 'jit_block_table'.
        //
        context->jit_block_table.maximal_size_minus_one = 0xfff;
        context->jit_block_table.entries = push_data(&context->permanent_arena, struct jit_block, context->jit_block_table.maximal_size_minus_one + 1);
    }
    
    {   //
        // Initialize the 'jit_imports'.
        //
        u64 guest_read_address  = (u64)guest_read_;
        context->jit_import_guest_read = emit_get_current(context);
        emit64(guest_read_address);
        
        u64 guest_read_for_write_address  = (u64)guest_read_for_write_;
        context->jit_import_guest_read_for_write = emit_get_current(context);
        emit64(guest_read_for_write_address);
        
        u64 guest_write_address = (u64)guest_write_size;
        context->jit_import_guest_write = emit_get_current(context);
        emit64(guest_write_address);
    }
    
    for(u32 size_index = 0; size_index < array_count(context->jit_guest_read_wrappers); size_index++){
        
        // 
        // This expects the guest virtual address in 'r8' and returns the host address in 'rax'.
        // 
        
        context->jit_guest_read_wrappers[size_index] = emit_get_current(context);
        
        u8 size = (u8)(1 << (size_index >> 1));
        int need_write_permission = size_index & 1;
        
        // 
        // First attempt to translate the address (inside address_reg) to the physical address,
        // by looking it up in the tlb.
        // 
        // 1. Check that the virtual address (in r8) does not straddle a page boundary.
        // 
        //    mov rcx, r8
        //    lea rax, [r8 + size]
        //    shr rcx, 12
        //    shr rax, 12
        //    
        //    cmp rcx, rax
        //    jnz .slow_path
        //    
        // 2. Get the tlb_entry corresponding to the page index.
        //    
        //    and rcx, array_count(tlb.entries)-1
        //    lea rcx, [(sizeof(tlb_entry)/8) * rcx]
        //    lea rcx, [context + 8 * rcx + offset_of(context, tlb)]
        //    
        //    cmp [rcx + .virtual_page_number], rax
        //    jnz .slow_path
        //    
        // 3. Check for extra permissions.
        //    mov rax, [rcx + .extra_permission_page]
        //    test rax, rax
        //    je .no_extra_permission
        //    
        //    mov r9, r8
        //    and r9, 0xfff
        //    test size [rax + r9], mask
        //    jnz .slow_path
        //    
        //  .no_extra_permission:
        //    
        // 4. Calculate the host address and return it.
        // 
        //    and r8, 0xfff
        //    mov rcx, [rcx + .host_page_addres]
        //    lea rax, [rcx + r8]
        //    ret
        //    
        // 5. Slow path: Perform a call to 'void *guest_read_(context, buffer, address, size)'.
        // 
        //    mov rcx, context
        //    lea rdx, [rsp + temp_buffer]
        //    mov r8,  address_reg ; already in there
        //    mov r9,  size
        //    call [rip + .jit_import_guest_read]
        //    
        //    test eax, eax
        //    jz [context + .jit_exit]
        //    
        //    ret
        //    
        // Then move the result into 'dest_reg'.
        // 
        
#if !DISABLE_JIT_TLB
        {
            u8 *patch_1 = null;
            
            // 1. 
            //    mov rcx, r8
            //    lea rax, [r8 + size - 1]
            //    shr rcx, 12
            //    shr rax, 12
            //    
            //    cmp rcx, rax
            //    jnz .slow_path
            emit_inst(0x8B, reg(8, REGISTER_C, REGISTER_R8));
            emit_inst(0x8D, regm8(8, REGISTER_C, REGISTER_R8), size-1);
            emit_inst(0xC1, reg(8, /*SHR*/5, REGISTER_C), 12);
            emit_inst(0xC1, reg(8, /*SHR*/5, REGISTER_A), 12);
            
            if(size != 1){    
                emit_inst(0x39, reg(8, REGISTER_C, REGISTER_A));
                emit(0x75); patch_1 = emit_get_current(context); emit(0);
            }
            
            // 2.
            //    and ecx, array_count(tlb.entries)-1
            //    lea ecx, [(sizeof(tlb_entry)/8) * rcx]
            //    lea rcx, [context + 8 * rcx + offset_of(context, tlb) + .virtual_page_number]
            //    
            //    cmp [rcx], rax
            //    jnz .slow_path
            static_assert(sizeof(struct translation_lookaside_buffer_entry) == 0x18);
            static_assert(offset_in_type(struct translation_lookaside_buffer_entry, virtual_page_number) == 0);
            
            emit_inst(0x81, reg(4, REG_OPCODE_and, REGISTER_C)); emit32(array_count(context->read_tlb.entries) - 1);
            emit_inst(0x8D, sib(4, MOD_REGM, REGISTER_C, /*log(2)*/1, REGISTER_C, REGISTER_C));
            emit_inst(0x8D, sib(8, MOD_REGM_OFF32, REGISTER_C, /*log(8)*/3, REGISTER_C, NONVOL_context));
            
            if(need_write_permission){
                emit32(offset_in_type(struct context, write_tlb.entries) + offset_in_type(struct translation_lookaside_buffer_entry, virtual_page_number));
            }else{
                emit32(offset_in_type(struct context, read_tlb.entries) + offset_in_type(struct translation_lookaside_buffer_entry, virtual_page_number));
            }
            
            emit_inst(0x3B, regm(8, REGISTER_A, REGISTER_C));
            emit(0x75); u8 *patch_2 = emit_get_current(context); emit(0);
            
            static_assert(offset_in_type(struct translation_lookaside_buffer_entry, virtual_page_number) == 0); // Need this for the offset in thype below to make sense.
            
            // 3.
            //    mov rax, [rcx + .extra_permission_page]
            //    test rax, rax
            //    je .no_extra_permission
            emit_inst(0x8B, regm8(8, REGISTER_A, REGISTER_C), (u8)offset_in_type(struct translation_lookaside_buffer_entry, extra_permission_page));
            emit_inst(0x85, reg(8, REGISTER_A, REGISTER_A));
            emit(0x74); u8 *patch_no_extra_permissions = emit_get_current(context); emit(0);
            
            //    mov r9, r8
            //    and r9, 0xfff
            //    test size[rax + r9], mask
            emit_inst(0x8B, reg(8, REGISTER_R9, REGISTER_R8));
            emit_inst(0x81, reg(8, REG_OPCODE_and, REGISTER_R9)); emit32(0xfff);
            
            emit_inst(0xf6 + (size != 1), sib(size, MOD_REGM, /*test*/0, /*log2(1)*/0, REGISTER_A, REGISTER_R9));
            for(u32 index = 0; index < size; index++) emit(EXTRA_PERMISSION_inaccessible);
            
            emit(0x75); u8 *patch_extra_permission_present = emit_get_current(context); emit(0);
            
            // .no_extra_permissions:
            *patch_no_extra_permissions = (u8)(emit_get_current(context) - (patch_no_extra_permissions + 1));
            
            // 4. 
            //    and r8, 0xfff
            //    mov rcx, [rcx + .host_page_address]
            //    lea rax, [rcx + r8]
            //    ret
            emit_inst(0x81, reg(8, REG_OPCODE_and, REGISTER_R8)); emit32(0xfff);
            emit_inst(0x8B, regm8(8, REGISTER_C, REGISTER_C), (u8)offset_in_type(struct translation_lookaside_buffer_entry, host_page_address));
            emit_inst(0x8D, sib(8, MOD_REGM, REGISTER_A, /*log2(1)*/0, REGISTER_C, REGISTER_R8));
            emit(0xc3);
            
            if(patch_1) *patch_1 = (u8)(emit_get_current(context) - (patch_1 + 1));
            *patch_2 = (u8)(emit_get_current(context) - (patch_2 + 1));
            *patch_extra_permission_present = (u8)(emit_get_current(context) - (patch_extra_permission_present + 1));
        }
#endif // !DISABLE_JIT_TLB
        
        // We need a _stack frame_ as we needs shadow space for the argument registers.
        //    sub rsp, 0x28
        emit(0x48, 0x83, 0xEC, 0x28);
        
        //    lea arg2, [context + jit_scratch]
        //    mov arg4, size
        //    mov arg1, context
        //    mov arg3, r8 (linux)
        //    call [rip + .jit_import_guest_read]
        emit_inst(0x8D, regm32(8, ARG_REG_2, NONVOL_context)); emit32(offset_in_type(struct context, jit_scratch));
        emit_inst(0xC7, reg(4, /*mov*/0, ARG_REG_4)); emit32(size);
        if(ARG_REG_3 != REGISTER_R8) emit_inst(0x8b, reg(8, ARG_REG_3, REGISTER_R8));
        emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
        
        u8 *current_rip = emit_get_current(context) + 6;
        
        u8 *import = need_write_permission ? context->jit_import_guest_read_for_write : context->jit_import_guest_read;
        
        s64 offset = import - current_rip;
        assert((s32)offset == offset);
        emit(0xff, 0x15); emit32((s32)offset);
        
        // Jump out if we crashed.
        //     cmp dword [context + .crash], 0
        //     jz success
        emit_inst(0x83, regm32(4, REG_OPCODE_cmp, NONVOL_context)); emit32(offset_in_type(struct context, crash)); emit(0);
        emit(0x74); u8 *patch = emit_get_current(context); emit(0);
        
        // We crashed, pop the return address from the stack and leave the jit.
        //    add rsp, 0x30
        //    jmp [context->jit_exit]
        emit(0x48, 0x83, 0xC4, 0x30);
        emit_inst(0xff, regm32(4, /*jmp*/4, NONVOL_context)); emit32(offset_in_type(struct context, jit_exit));
        
        // success:
        //    add rsp, 0x28
        //    ret
        *patch = (u8)(emit_get_current(context) - (patch + 1));
        emit(0x48, 0x83, 0xC4, 0x28);
        emit(0xc3);
        
        vtune_jit_profiling_routine(context->jit_guest_read_wrappers[size_index], emit_get_current(context), "jit: guest_read_wrappers[%d]", size_index);
    }
    
    for(u32 size_index = 0; size_index < array_count(context->jit_guest_write_wrappers); size_index++){
        
        // 
        // This expects the guest virtual address in 'r8' and returns the host address in 'rax'.
        // 
        
        context->jit_guest_write_wrappers[size_index] = emit_get_current(context);
        
        u8 size = (u8)(1 << size_index);
        
#if !DISABLE_JIT_TLB
        {
            u8 *patch_1 = null;
            
            // 1. 
            //    mov rcx, r8
            //    lea rax, [r8 + size]
            //    shr rcx, 12
            //    shr rax, 12
            //    
            //    cmp rcx, rax
            //    jnz .slow_path
            emit_inst(0x8B, reg(8, REGISTER_C, REGISTER_R8));
            emit_inst(0x8D, regm8(8, REGISTER_A, REGISTER_R8), size - 1);
            emit_inst(0xC1, reg(8, /*SHR*/5, REGISTER_C), 12);
            emit_inst(0xC1, reg(8, /*SHR*/5, REGISTER_A), 12);
            
            if(size != 1){
                emit_inst(0x39, reg(8, REGISTER_C, REGISTER_A));
                emit(0x75); patch_1 = emit_get_current(context); emit(0);
            }
            
            // 2.
            //    and ecx, array_count(tlb.entries)-1
            //    lea ecx, [(sizeof(tlb_entry)/8) * rcx]
            //    lea rcx, [context + 8 * rcx + offset_of(context, tlb)  + .virtual_page_number]
            //    
            //    cmp [rcx], rax
            //    jnz .slow_path
            static_assert(sizeof(struct translation_lookaside_buffer_entry) == 0x18);
            static_assert(offset_in_type(struct translation_lookaside_buffer_entry, virtual_page_number) == 0);
            
            emit_inst(0x81, reg(4, REG_OPCODE_and, REGISTER_C)); emit32(array_count(context->read_tlb.entries) - 1);
            emit_inst(0x8D, regm(4, REGISTER_C, REGISTER_SP), make_sib(/*log(2)*/1, REGISTER_C, REGISTER_C));
            emit_inst(0x8D, sib(8, MOD_REGM_OFF32, REGISTER_C, /*log(8)*/3, REGISTER_C, NONVOL_context));
            
            emit32(offset_in_type(struct context, write_tlb.entries) + offset_in_type(struct translation_lookaside_buffer_entry, virtual_page_number));
            
            static_assert(offset_in_type(struct translation_lookaside_buffer_entry, virtual_page_number) == 0); // Need this for the offset_in_type below to make sense.
            
            emit_inst(0x3B, regm(8, REGISTER_A, REGISTER_C)); 
            emit(0x75); u8 *patch_2 = emit_get_current(context); emit(0);
            
            // 3.
            //    mov rax, [rcx + .extra_permission_page]
            //    test rax, rax
            //    je .no_extra_permission
            emit_inst(0x8B, regm8(8, REGISTER_A, REGISTER_C), (u8)offset_in_type(struct translation_lookaside_buffer_entry, extra_permission_page));
            emit_inst(0x85, reg(8, REGISTER_A, REGISTER_A));
            emit(0x74); u8 *patch_no_extra_permissions = emit_get_current(context); emit(0);
            
            //    mov r9, r8
            //    and r9, 0xfff
            //    test size[rax + r9], mask
            emit_inst(0x8B, reg(8, REGISTER_R9, REGISTER_R8));
            emit_inst(0x81, reg(8, REG_OPCODE_and, REGISTER_R9)); emit32(0xfff);
            
            emit_inst(0xf6 + (size != 1), sib(size, MOD_REGM, /*test*/0, /*log2(1)*/0, REGISTER_A, REGISTER_R9));
            for(u32 index = 0; index < size; index++) emit(EXTRA_PERMISSION_inaccessible);
            
            emit(0x75); u8 *patch_extra_permission_present = emit_get_current(context); emit(0);
            
            // .no_extra_permissions:
            *patch_no_extra_permissions = (u8)(emit_get_current(context) - (patch_no_extra_permissions + 1));
            
            // 4. 
            //    and r8, 0xfff
            //    mov rcx, [rcx + .host_page_addres]
            //    movzx size ptr[rcx + r8], source_register
            //    ret
            emit_inst(0x81, reg(8, REG_OPCODE_and, REGISTER_R8)); emit32(0xfff);
            emit_inst(0x8b, regm8(8, REGISTER_C, REGISTER_C), (u8)offset_in_type(struct translation_lookaside_buffer_entry, host_page_address));
            
            // mov rax, size [rdx]
            switch(size){
                case 1:{
                    emit(0x0f, 0xb6, make_modrm(MOD_REGM, REGISTER_A, REGISTER_D));
                }break;
                case 2:{
                    emit(0x0f, 0xb7, make_modrm(MOD_REGM, REGISTER_A, REGISTER_D));
                }break;
                case 4:{
                    emit(0x8b, make_modrm(MOD_REGM, REGISTER_A, REGISTER_D));
                }break;
                case 8:{
                    emit(0x48, 0x8b, make_modrm(MOD_REGM, REGISTER_A, REGISTER_D));
                }break;
                case 16:{
                    emit(0xc4, make_two_byte_vex(0, 0, 0, /*two_byte*/1, 0, 0, /*vexL*/0, 0), 0x10, make_modrm(MOD_REGM, REGISTER_A, REGISTER_D));
                }break;
                case 32:{
                    emit(0xc4, make_two_byte_vex(0, 0, 0, /*two_byte*/1, 0, 0, /*vexL*/1, 0), 0x10, make_modrm(MOD_REGM, REGISTER_A, REGISTER_D));
                }break;
                invalid_default_case();
            }
            
            // mov size [rcx + r8], rax
            switch(size){
                case 1:{
                    emit(0x40 | REXB, 0x88, make_modrm(MOD_REGM, REGISTER_A, REGISTER_SP), make_sib(/*log(1)*/0, REGISTER_C, REGISTER_R8));
                }break;
                case 2:{
                    emit(0x66, 0x40 | REXB, 0x89, make_modrm(MOD_REGM, REGISTER_A, REGISTER_SP), make_sib(/*log(1)*/0, REGISTER_C, REGISTER_R8));
                }break;
                case 4:{
                    emit(0x40 | REXB, 0x89, make_modrm(MOD_REGM, REGISTER_A, REGISTER_SP), make_sib(/*log(1)*/0, REGISTER_C, REGISTER_R8));
                }break;
                case 8:{
                    emit(0x48 | REXB, 0x89, make_modrm(MOD_REGM, REGISTER_A, REGISTER_SP), make_sib(/*log(1)*/0, REGISTER_C, REGISTER_R8));
                }break;
                case 16:{
                    emit(0xc4, make_two_byte_vex(0, 0, 1, /*two_byte*/1, 0, 0, /*vexL*/0, 0), 0x11, make_modrm(MOD_REGM, REGISTER_A, REGISTER_SP), make_sib(/*log(1)*/0, REGISTER_C, REGISTER_R8));
                }break;
                case 32:{
                    emit(0xc4, make_two_byte_vex(0, 0, 1, /*two_byte*/1, 0, 0, /*vexL*/1, 0), 0x11, make_modrm(MOD_REGM, REGISTER_A, REGISTER_SP), make_sib(/*log(1)*/0, REGISTER_C, REGISTER_R8));
                }break;
                invalid_default_case();
            }
            
            emit(0xc3);
            
            if(patch_1) *patch_1 = (u8)(emit_get_current(context) - (patch_1 + 1));
            *patch_2 = (u8)(emit_get_current(context) - (patch_2 + 1));
            *patch_extra_permission_present = (u8)(emit_get_current(context) - (patch_extra_permission_present + 1));
        }
#endif // !DISABLE_JIT_TLB
        
        // 
        // We need a _stack frame_ as we needs shadow space for the argument registers.
        //    sub rsp, 0x28
        emit(0x48, 0x83, 0xEC, 0x28);
        
        // mov arg4, size
        // mov arg1, context
        // mov arg3, r8 (linux)
        emit_inst(0xC7, reg(4, /*mov*/0, ARG_REG_4)); emit32(size);
        emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
        if(ARG_REG_2 != REGISTER_D) emit_inst(0x8b, reg(8, ARG_REG_2, REGISTER_D));
        if(ARG_REG_3 != REGISTER_R8) emit_inst(0x8b, reg(8, ARG_REG_3, REGISTER_R8));
        
        // call [rip + .jit_import_guest_write]
        u8 *current_rip = emit_get_current(context) + 6;
        s64 offset = context->jit_import_guest_write - current_rip;
        assert((s32)offset == offset);
        emit(0xff, 0x15); emit32((s32)offset);
        
        // Jump out if we crashed.
        //      cmp dword [context + .crash], 0
        //      jz success
        emit_inst(0x83, regm32(4, REG_OPCODE_cmp, NONVOL_context)); emit32(offset_in_type(struct context, crash)); emit(0);
        emit(0x74); u8 *patch = emit_get_current(context); emit(0);
        
        // We crashed, pop the return address from the stack and leave the jit.
        //    add rsp, 0x30
        //    jmp [context->jit_exit]
        emit(0x48, 0x83, 0xC4, 0x30);
        emit(0xff, make_modrm(MOD_REGM_OFF32, 4, NONVOL_context));
        emit32(offset_in_type(struct context, jit_exit));
        
        // success:
        //    add rsp, 0x28
        //    ret
        *patch = (u8)(emit_get_current(context) - (patch + 1));
        emit(0x48, 0x83, 0xC4, 0x28);
        emit(0xc3);
        
        vtune_jit_profiling_routine(context->jit_guest_write_wrappers[size_index], emit_get_current(context), "jit: guest_write_wrappers[%d]", size_index);
    }
    
    
    {   //
        // Initialize the `jit_translate_rip_to_physical` jit call.
        // 
        context->jit_translate_rip_to_physical = emit_get_current(context);
        
        // 
        // First check the `execute_tlb` to see if we can simply grab the physical address.
        // @cleanup: we could potentially get rid of a couple instruction by assuming array_count(tlb.entries) == 0x1000.
        // 
        
        //     mov rcx, NONVOL_rip
        //     shr rcx, 12
        //     mov rax, rcx
        //     and ecx, array_count(tlb.entries)-1
        //     lea ecx, [sizeof(tlb_entry)/8 * rcx]
        //     lea rcx, [context + 8 * rcx + offset_of(context, tlb)]
        //     cmp [rcx + .virtual_page_number], rax
        //     jnz .slow_path
        // 
        //     mov rax, [rcx + .host_page_address]
        //     sub rax, [context + .physical_memory]
        //     mov rcx, NONVOL_rip
        //     and rcx, 0xfff
        //     add rax, rcx
        //     jmp patchable_exit
        static_assert(sizeof(struct translation_lookaside_buffer_entry) == 0x18);
        static_assert(offset_in_type(struct translation_lookaside_buffer_entry, virtual_page_number) == 0);
        
        emit_inst(0x8B, reg(8, REGISTER_C, NONVOL_rip));
        emit_inst(0xC1, reg(8, /*SHR*/5, REGISTER_C), 12);
        emit_inst(0x8B, reg(8, REGISTER_A, REGISTER_C));
        emit_inst(0x81, reg(4, REG_OPCODE_and, REGISTER_C)); emit32(array_count(context->execute_tlb.entries) - 1);
        emit_inst(0x8D, sib(4, MOD_REGM, REGISTER_C, /*log(2)*/1, REGISTER_C, REGISTER_C));
        emit_inst(0x8D, sib(8, MOD_REGM_OFF32, REGISTER_C, /*log(8)*/3, REGISTER_C, NONVOL_context)); emit32(offset_in_type(struct context, execute_tlb.entries));
        emit_inst(0x3B, regm(8, REGISTER_A, REGISTER_C));
        emit(0x75); u8 *slow_path = emit_get_current(context); emit(0);
        
        emit_inst(0x8B, regm8(8, REGISTER_A, REGISTER_C), (u8)offset_in_type(struct translation_lookaside_buffer_entry, host_page_address));
        emit_inst(0x8B, reg(8, REGISTER_C, NONVOL_rip));
        emit_inst(0x81, reg(4, REG_OPCODE_and, REGISTER_C)); emit32(0xfff);
        
        emit_inst(0x2B, regm8(8, REGISTER_A, NONVOL_context)); emit(offset_in_type(struct context, physical_memory));
        emit_inst(0x03, reg(8, REGISTER_A, REGISTER_C));
        
        emit(0xc3);
        
        *slow_path = (u8)(emit_get_current(context) - (slow_path + 1));
        
        // 
        // We need a _stack frame_ as we needs shadow space for the argument registers.
        //    sub rsp, 0x28
        emit(0x48, 0x83, 0xEC, 0x28);
        
        
        // First attempt, simply translate NONVOL_rip to physical and then emit a patchable jit entry.
        //     translate_rip_to_physical(context, NONVOL_rip, PERMISSION_execute)
        emit_inst(0x8B, reg(8, ARG_REG_1, NONVOL_context));
        emit_inst(0x8B, reg(8, ARG_REG_2, NONVOL_rip));
        emit_inst(0xC7, reg(8, /*mov*/0, ARG_REG_3)); emit32(PERMISSION_execute);
        
        // Call translate_rip_to_physical.
        //     mov rax, helper
        //     call rax
        emit(0x48, 0xB8); emit64((u64)translate_rip_to_physical);
        emit_inst(0xff, reg(4, /*call*/2, REGISTER_A));
        
        
        // success:
        //    add rsp, 0x28
        //    ret
        
        emit(0x48, 0x83, 0xC4, 0x28);
        emit(0xc3);
        
        vtune_jit_profiling_routine(context->jit_translate_rip_to_physical, emit_get_current(context), "jit: translate_rip_to_physical");
    }
    
    
    {   //
        // Initialize the 'jit_entry'. The 'jit_entry' is here to establish a stack frame and jump to the first instruction.
        //
        context->jit_entry = (void *)emit_get_current(context);
        
        //
        // jit_entry: (rcx: context, rdx: registers, r8: instruction_cache_entry)
        //    
        
        // 
        // push non-volatiles
        // 
#define emit_push(a) if((a) >= 8) emit(0x40 | REXB, 0x50 | ((a) & 7)); else emit(0x50 | (a));
        
        emit_push(NONVOL_context);
        emit_push(NONVOL_registers);
        emit_push(NONVOL_flex);
        emit_push(NONVOL_rip);
        emit_push(NONVOL_timeout_counter);
        
        //    sub rsp, JIT_STACK_ALLOCATION_SIZE  ; Allocate homing space for later calls.
        emit_inst(0x83, reg(8, REG_OPCODE_sub, REGISTER_SP), JIT_STACK_ALLOCATION_SIZE); // @WARNING: We need to keep the stack aligned to 0x10 here!
        
        //    mov context,   arg1
        //    mov registers, arg2
        emit_inst(0x8B, reg(8, NONVOL_context,   ARG_REG_1));
        emit_inst(0x8B, reg(8, NONVOL_registers, ARG_REG_2));
        
        //    mov nonvol_rip,     [registers + .rip]
        //    mov nonvol_timeout, [context + .fuzz_case_timeout]
        emit_inst(0x8B, regm32(8, NONVOL_rip, NONVOL_registers)); emit32(offset_in_type(struct registers, rip));
        emit_inst(0x8B, regm32(8, NONVOL_timeout_counter, NONVOL_context)); emit32(offset_in_type(struct context, fuzz_case_timeout));
        
#if JIT_EMULATE_MXCSR
        // ldmxcsr [registers + .mxcsr] :linux_refactor
        emit(0x0f, 0xae, make_modrm(MOD_REGM_OFF32, /*ldmxcsr*/2, NONVOL_registers)); emit32(offset_in_type(struct registers, mxcsr));
#endif
        
        //    jmp [r8 + .instruction_jit]
        emit_inst(0xFF, regm8(4, /*jmp*/4, ARG_REG_3), (u8)offset_in_type(struct instruction_cache_entry, instruction_jit));
        
        vtune_jit_profiling_routine((void *)context->jit_entry, emit_get_current(context), "jit: jit_entry");
    }
    
    {
        //
        // The 'jit_exit' just pops the function frame established by 'jit_entry' and returns.
        //
        context->jit_exit = emit_get_current(context);
        
        emit_inst(0x31, reg(4, REGISTER_A, REGISTER_A)); // xor eax, erax
        
#if JIT_EMULATE_MXCSR
        // stmxcsr [registers + .mxcsr] :linux_refactor
        emit(0x0f, 0xae, make_modrm(MOD_REGM_OFF32, /*ldmxcsr*/3, NONVOL_registers)); emit32(offset_in_type(struct registers, mxcsr));
#endif
        
        // mov qword [registers + .rip], nonvol_rip
        // mov qword [context + .fuzz_case_timeout], nonvol_timeout
        emit_inst(0x89, regm32(8, NONVOL_rip, NONVOL_registers)); emit32(offset_in_type(struct registers, rip));
        emit_inst(0x89, regm32(8, NONVOL_timeout_counter, NONVOL_context)); emit32(offset_in_type(struct context, fuzz_case_timeout));
        
        
        // add rsp, JIT_STACK_ALLOCATION_SIZE
        emit_inst(0x83, reg(8, REG_OPCODE_add, REGISTER_SP), JIT_STACK_ALLOCATION_SIZE); // @WARNING: We need to keep the stack aligned to 0x10 here!
        
        //
        // pop non-volatiles
        // 
#define emit_pop(a) if((a) >= 8) emit(0x40 | REXB, 0x58 | ((a) & 7)); else emit(0x58 | (a));
        
        emit_pop(NONVOL_timeout_counter);
        emit_pop(NONVOL_rip);
        emit_pop(NONVOL_flex);
        emit_pop(NONVOL_registers);
        emit_pop(NONVOL_context);
        
        // ret
        emit(0xc3);
        vtune_jit_profiling_routine(context->jit_exit, emit_get_current(context), "jit: jit_exit");
    }
}

enum helper_flags{
    HELPER_simple_call = 0,
    
    HELPER_cares_about_rip = 1,
    HELPER_might_change_rip = 2,
    HELPER_might_crash = 4,
    HELPER_do_not_print = 8,
};

void print_helper(struct context *context, u64 rip, char *name){
    print_symbol(context, rip);
    print(": Calling helper '%s'.\n", name);
}

#define emit_call_to_helper(context, helper, flags) emit_call_to_helper_(context, helper, flags, #helper) 

u8 *emit_call_to_helper_(struct context *context, void *helper, enum helper_flags flags, char *helper_name){
    u8 *start_of_the_wrapper = emit_get_current(context);
    
    if(flags & HELPER_cares_about_rip){
        // Store the rip, as the helper will expect it to be accurate.
        //    mov [registers + .rip], nonvol_rip
        emit_inst(0x89, regm32(8, NONVOL_rip, NONVOL_registers)); emit32(offset_in_type(struct registers, rip));
        
#if JIT_EMULATE_MXCSR
        // stmxcsr [registers + .mxcsr]
        emit(0x0f, 0xae, make_modrm(MOD_REGM_OFF32, /*ldmxcsr*/3, NONVOL_registers)); emit32(offset_in_type(struct registers, mxcsr));
#endif
    }
    
    // Call the helper.
    //     mov rax, helper
    //     call rax
    emit(0x48, 0xB8); emit64((u64)helper);
    emit_inst(0xff, reg(4, /*call*/2, REGISTER_A));
    
#if PRINT_INSTRUCTION_HELPER_EVENTS
    if(!(flags & HELPER_do_not_print)){
        // Call print_helper.
        //     mov arg1, context
        //     mov arg2, NONVOL_rip
        //     mov arg3, helper_name
        //     mov rax,  helper
        //     call rax
        emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
        emit_inst(0x8b, reg(8, ARG_REG_2,  NONVOL_rip));
        emit(0x48 | ((ARG_REG_2 >= 8) ? REXB : 0), 0xB8 + (ARG_REG_2 & 7)); emit64((u64)helper_name);
        emit(0x48, 0xB8); emit64((u64)print_helper);
        emit(0xff, make_modrm(MOD_REG, /*call*/2, REGISTER_A));
    }
#else
    (void)helper_name;
#endif
    
#if JIT_EMULATE_MXCSR
    // ldmxcsr [registers + .mxcsr]
    emit(0x0f, 0xae, make_modrm(MOD_REGM_OFF32, /*ldmxcsr*/2, NONVOL_registers)); emit32(offset_in_type(struct registers, mxcsr));
#endif
    
    u8 *  rip_compare = null;
    u8 *crash_compare = null;
    
    if(flags & HELPER_might_change_rip){
        // Check if we have to exit the jit, because the helper changed 'registers->rip'.
        //     cmp nonvol_rip, qword [registers + .rip]
        //     mov nonvol_rip, qword [registers + .rip]
        //     jnz exit_jit
        emit_inst(0x3B, regm32(8, NONVOL_rip, NONVOL_registers)); emit32(offset_in_type(struct registers, rip));
        emit_inst(0x8B, regm32(8, NONVOL_rip, NONVOL_registers)); emit32(offset_in_type(struct registers, rip));
        emit(0x75); rip_compare = emit_get_current(context); emit(0);
    }
    
    if(flags & HELPER_might_crash){
        // Check if the helper set 'context->crash'.
        //     cmp dword [context + .crash], 0
        //     jnz exit_jit
        emit_inst(0x83, regm32(4, REG_OPCODE_cmp, NONVOL_context)); emit32(offset_in_type(struct context, crash)); emit(0);
        emit(0x75); crash_compare = emit_get_current(context); emit(0);
    }
    
    if(flags & (HELPER_might_crash | HELPER_might_change_rip)){
        // jmp sucess
        emit(0xEB); u8 *success_end_patch = emit_get_current(context); emit(0);
        
        // exit_jit:
        //     we changed rip or crashed
        u8 *jit_exit = emit_get_current(context);
        if(  rip_compare)   *rip_compare = (u8)(jit_exit -   (rip_compare + 1));
        if(crash_compare) *crash_compare = (u8)(jit_exit - (crash_compare + 1));
        
        // jmp [context->jit_exit]
        emit_inst(0xff, regm32(4, /*jmp*/4, NONVOL_context)); emit32(offset_in_type(struct context, jit_exit));
        
        // success:
        u8 *success = emit_get_current(context);
        *success_end_patch = (u8)(success - (success_end_patch + 1));
    }
        
    return start_of_the_wrapper;
}


//_____________________________________________________________________________________________________________________
// Register accessors

u8 reg_offset(struct guest_register reg, u8 size, u8 rex){
    u8 offset8 = (u8)(reg.encoding * 8);
    if(size == 1 && !rex && reg.encoding >= 4){
        assert(reg.encoding < 8); // otherwise how is there no rex
        offset8 = (u8)((reg.encoding - 4) * 8 + 1);
    }
    return offset8;
}

//
// Emits something like 'movzx dest, size ptr [registers + source * 8]'.
//
void emit_read_gpr(struct context *context, struct host_register dest, struct guest_register source, u8 size, u8 operation_rex){
    
    // Register encoding with REX | Register encoding without REX
    //      s   i   z   e         |      s   i   z   e
    //      1   2   4   8         |      1   2   4   8
    // e 0 AL  AX  EAX RAX        | e 0 AL  AX  EAX RAX
    // n 1 CL  CX  ECX RCX        | n 1 CL  CX  ECX RCX
    // c 2 DL  DX  EDX RDX        | c 2 DL  DX  EDX RDX
    // o 3 BL  BX  EBX RBX        | o 3 BL  BX  EBX RBX
    // d 4 SPL SP  ESP RSP        | d 4 AH  SP  ESP RSP
    // i 5 BPL BP  EBP RBP        | i 5 CH  BP  EBP RBP
    // n 6 SIL SI  ESI RSI        | n 6 DH  SI  ESI RSI
    // g 7 DIL DI  EDI RDI        | g 7 BH  DI  EDI RDI
    
    u8 offset8 = reg_offset(source, size, operation_rex);
    
    switch(size){
        case 1:{
            // 'movzx dest, byte ptr [registers + source * 8]' or 'movzx dest, byte ptr [registers + (source - 4) * 8 + 1]'
            emit_inst((0x0f, 0xb6), regm8(4, dest.encoding, NONVOL_registers), offset8);
        }break;
        case 2:{
            // 'movzx dest, word ptr [registers + source * 8]'
            emit_inst((0x0f, 0xb7), regm8(4, dest.encoding, NONVOL_registers), offset8);
        }break;
        case 4:case 8:{
            // 'mov dest, d/qword ptr [registers + source * 8]'
            emit_inst(0x8b, regm8(size, dest.encoding, NONVOL_registers), offset8);
        }break;
        invalid_default_case();
    }
}

//
// Emits something like 'mov byte [registers + dest * 8], source'.
// If the size is 4 the caller has to make sure the 'source' is zero extend.
//
void emit_write_gpr(struct context *context, struct guest_register dest, struct host_register source, u8 size, u8 operation_rex){
    
    // Register encoding with REX | Register encoding without REX
    //      s   i   z   e         |      s   i   z   e
    //      1   2   4   8         |      1   2   4   8
    // e 0 AL  AX  EAX RAX        | e 0 AL  AX  EAX RAX
    // n 1 CL  CX  ECX RCX        | n 1 CL  CX  ECX RCX
    // c 2 DL  DX  EDX RDX        | c 2 DL  DX  EDX RDX
    // o 3 BL  BX  EBX RBX        | o 3 BL  BX  EBX RBX
    // d 4 SPL SP  ESP RSP        | d 4 AH  SP  ESP RSP
    // i 5 BPL BP  EBP RBP        | i 5 CH  BP  EBP RBP
    // n 6 SIL SI  ESI RSI        | n 6 DH  SI  ESI RSI
    // g 7 DIL DI  EDI RDI        | g 7 BH  DI  EDI RDI
    
    if(size == 4) size = 8;
    if(size == 2) emit(0x66);
    
    u8 rex = 0;
    if(size == 1 && source.encoding >= 4) rex |= 0x40; // We never want to write ah or something!
    
    if(source.encoding >= 8){
        rex = 0x40 | REXR;
        source.encoding &= 0x7;
    }
    if(size == 8) rex |= 0x40 | REXW;
    if(rex) emit(rex);
    
    u8 offset8 = reg_offset(dest, size, operation_rex);
    u8 modrm = make_modrm(MOD_REGM_OFF8, source.encoding, NONVOL_registers);
    u8 opcode = size == 1 ? 0x88 : 0x89;
    
    // 'mov size ptr [registers + dest * 8], source' or 'mov byte ptr [registers + (dest - 4) * 8 + 1], source'
    emit(opcode, modrm, offset8);
}

//_____________________________________________________________________________________________________________________
// RFLAGS handling

// @note: This is called "destructively" as it alters the host rflags.
//        Therefore, if you need the state of the intact, you have to save them first.
void emit_destructively_update_flags(struct context *context, struct host_register reg){
    // pusfq
    emit(0x9c);
    
    // pop reg
    u8 rex = ((reg.encoding > 7) ? (0x40|REXB) : 0);
    if(rex) emit(rex);
    emit(0x58 + (reg.encoding & 7));
    
    // and reg, arithmetic_flags
    if(rex) emit(rex);
    emit(0x81, make_modrm(MOD_REG, REG_OPCODE_and, reg.encoding));
    emit32(ARITHMETIC_FLAGS);
    
    // and [registers + offset_of(struct registers, rflags)], ~ARITHMETIC_FLAGS
    emit(0x81, make_modrm(MOD_REGM_OFF32, REG_OPCODE_and, NONVOL_registers)); emit32(offset_in_type(struct registers, rflags));
    emit32((u32)(~ARITHMETIC_FLAGS));
    
    // or [registers + offset_of(struct registers, rflags)], reg
    if(rex) emit(0x40 | REXR);
    emit(0x09, make_modrm(MOD_REGM_OFF32, reg.encoding, NONVOL_registers)); emit32(offset_in_type(struct registers, rflags));
}

void emit_load_flags(struct context *context){
    // push dword ptr [registers + .rflags - 1]
    emit(0xff, make_modrm(MOD_REGM_OFF32, 6, NONVOL_registers)); emit32(offset_in_type(struct registers, rflags));
    
    // and qword [rsp], ARITHMETIC_FLAGS
    emit(0x48, 0x81, make_modrm(MOD_REGM, REG_OPCODE_and, REGISTER_SP), make_sib(0, REGISTER_SP, REGISTER_SP));
    emit32(ARITHMETIC_FLAGS);
    
    // popf
    emit(0x9D);
}

//_____________________________________________________________________________________________________________________
// SIMD xmm reads and writes

void emit_simd_prefix(struct context *context, enum legacy_prefix flags){
    if(flags & MANDATORY_PREFIX_F3) emit(0xF3); // si2ss
    if(flags & MANDATORY_PREFIX_F2) emit(0xF2); // si2sd
    if(flags & MANDATORY_PREFIX_66) emit(0x66); // pi2pd
}

// Emits one of 'movups dest, xmm ptr [registers + .source]', 'vmovups dest, xmm ptr [registers + .source]'
// or 'vmovups dest, ymm ptr [registers + .source]'. depending on 'vex'.
void emit_read_xmm_register(struct context *context, struct host_register dest, struct guest_register source, u8 vex){
    assert(dest.encoding < 8);
    assert(source.encoding != INVALID_REGISTER);
    
    if(vex){
        emit(0xc5, make_vex(0, 0, (vex >> 2) & 1, 0));
    }else{
        emit(0x0f);
    }
    
    // (v)movups dest, [registers + .source]
    emit(0x10, make_modrm(MOD_REGM_OFF32, dest.encoding, NONVOL_registers));
    emit32(source.encoding * 32 + offset_in_type(struct registers, simd));
}

// Emits one of 'movups xmm ptr [registers + .dest], source', 'vmovups xmm ptr [registers + .dest], source'
// or 'vmovups ymm ptr [registers + .dest], source'. depending on 'vex'.
void emit_write_xmm_register(struct context *context, struct guest_register dest, struct host_register source, u8 vex){
    assert(source.encoding < 8);
    if(vex){
        emit(0xc5, make_vex(0, 0, 1, 0)); // @note: always emit vexL, because any vex operation zeroes the top part.
    }else{
        emit(0x0f);
    }
    
    // (v)movups [registers + .dest], source
    emit(0x11, make_modrm(MOD_REGM_OFF32, source.encoding, NONVOL_registers));
    emit32(dest.encoding * 32 + offset_in_type(struct registers, simd));
}

//_____________________________________________________________________________________________________________________
// Memory reads

// Emits a call to jit wrapper of 'guest_read_' or 'guest_read_for_write_', which return a pointer to the value in rax.
void emit_read_into_temp_buffer_and_return_pointer_in_rax(struct context *context, struct host_register address_reg, u8 size, int need_write_permission){
    
    if(address_reg.encoding != REGISTER_R8){
        // First load the 'address_reg', just in case it is one of the other 3 argument registers.
        //      mov r8, address_reg
        emit_inst(0x8b, reg(8, REGISTER_R8, address_reg.encoding));
    }
    
    u32 size_index;
    _BitScanForward((unsigned long32 *)&size_index, size);
    
    u64 jit_guest_read_wrapper_index = need_write_permission + (size_index << 1);
    assert(jit_guest_read_wrapper_index < array_count(context->jit_guest_read_wrappers));
    
    u8 *destination = context->jit_guest_read_wrappers[jit_guest_read_wrapper_index];
    assert(destination);
    
    // call off(rip, guest_read_wrapper)
    
    u8 *current_rip = emit_get_current(context) + 5;
    s64 offset = destination - current_rip;
    assert((s32)offset == offset);
    emit(0xE8); emit32((s32)offset);
}

//
// Both 'dest_reg' and 'address_reg' are host-registers.
// Reads from the the guest_address specified in 'address_reg' and stores the result in 'dest_reg'.
// If the size is less then 16, the result is zero-extended into the general purpose register specified by 'dest_reg'.
// Else, it is assumed that 'dest_reg' specifies an xmm/ymm register.
//
void emit_read_into_gpr(struct context *context, struct host_register dest_register, struct host_register address_reg, u8 size, int need_write_permission){
    
    emit_read_into_temp_buffer_and_return_pointer_in_rax(context, address_reg, size, need_write_permission);
    
    //
    // Store the value into 'dest_reg'.
    //
    
    switch(size){
        case 1:{
            // movzx dest_reg, byte ptr[rax]
            emit_inst((0x0f, 0xb6), regm(4, dest_register.encoding, REGISTER_A));
        }break;
        case 2:{
            // movzx dest_reg, word ptr[rax]
            emit_inst((0x0f, 0xb7), regm(4, dest_register.encoding, REGISTER_A));
        }break;
        case 4: case 8:{
            // mov dest_reg, dword ptr[rax]
            emit_inst(0x8b, regm(size, dest_register.encoding, REGISTER_A));
        }break;
        invalid_default_case();
    }
}

u8 get_size_for_simd(enum legacy_prefix prefix, u8 vex){
    u8 size = 16;
    if(prefix & MANDATORY_PREFIX_F3) size = 4;
    if(prefix & MANDATORY_PREFIX_F2) size = 8;
    if(vex & VEXL) size = 32;
    return size;
}

void emit_read_into_xmm(struct context *context, struct host_register dest, struct host_register source, enum legacy_prefix prefix, u8 vex, int need_write_permission){
    assert(dest.encoding < 8);
    assert(source.encoding < 8);
    
    u8 size = get_size_for_simd(prefix, vex);
    
    emit_read_into_temp_buffer_and_return_pointer_in_rax(context, source, size, need_write_permission);
    
    if(vex){
        // vmovups/vmovupd/vmovusd/vmovuss dest, xmm/ymm ptr[rax]
        emit(0xc5, make_vex(0, 0, (vex >> 2) & 1, vex & 3), 0x10, make_modrm(MOD_REGM, dest.encoding, REGISTER_A));
    }else{
        emit_simd_prefix(context, prefix);
        // movups/movupd/movusd/movuss dest, [rax]
        emit(0x0f, 0x10, make_modrm(MOD_REGM, dest.encoding, REGISTER_A));
    }
}

//_____________________________________________________________________________________________________________________
// Memory writes

//
// Emits a call to a jit wrapper of 'guest_write_size(context, source_reg, dest_reg, size)'.
// The caller has to make sure 'host_address_reg' contains a valid memory location.
// 'host_address_reg' cannot contain a value. Use 'emit_write_host_register' instead.
// 'guest_address_reg' should contain a guest_address, which is supposed to be written.
//
// Prefers 'r8' for 'guest_address_reg' and 'rdx' for 'host_address_reg'.
//
void emit_write_pointer(struct context *context, struct host_register guest_address_reg, struct host_register host_address_reg, u8 size){
    assert(host_address_reg.encoding < 8);
    
    if(guest_address_reg.encoding != REGISTER_R8){
        // First move into r8 as we know (for now) that that is save.
        //      mov r8, guest_address_reg
        emit_inst(0x8b, reg(8, REGISTER_R8, guest_address_reg.encoding));
    }
    
    if(host_address_reg.encoding != REGISTER_D){
        // mov rdx, host_address_reg
        emit_inst(0x8b, reg(8, REGISTER_D, host_address_reg.encoding));
    }
    
    u32 size_index;
    _BitScanForward((unsigned long32 *)&size_index, size);
    
    u64 jit_guest_write_wrapper_index = size_index;
    assert(jit_guest_write_wrapper_index < array_count(context->jit_guest_write_wrappers));
    
    u8 *destination = context->jit_guest_write_wrappers[jit_guest_write_wrapper_index];
    assert(destination);
    
    u8 *current_rip = emit_get_current(context) + 5;
    s64 offset = destination - current_rip;
    assert((s32)offset == offset);
    
    emit(0xE8); emit32((s32)offset);
}

//
// Writes the 'source_reg' to the the memory location specified by 'guest_address_reg'.
// This routine simply stores 'source_reg' to the stack and then calls 'emit_write'.
// If the size is less then 16, the 'source_reg' is treated as a general purpose register.
// Else it is assumed that 'source_reg' specifies an xmm/ymm register.
//
// Prefers 'r8' for 'guest_address_reg'.
//
void emit_write_host_register(struct context *context, struct host_register guest_address_reg, struct host_register source_reg, u8 size){
    assert(source_reg.encoding < 8); // for now don't allow r8-r15
    assert(guest_address_reg.encoding != REGISTER_D);
    assert(source_reg.encoding != REGISTER_D);
    
    // lea rdx, [context + .jit_scratch]
    emit_inst(0x8D, regm32(8, REGISTER_D, NONVOL_context)); emit32(offset_in_type(struct context, jit_scratch));
    
    u8 modrm = make_modrm(MOD_REGM, source_reg.encoding, REGISTER_D);
    
    // mov size ptr [rdx], source_reg
    switch(size){
        case 1: case 2: case 4:{
            // mov [rdx], source_reg
            emit(0x89, modrm);
        }break;
        case 8:{
            // mov [rdx], source_reg
            emit(0x48, 0x89, modrm);
        }break;
        case 16:{
            // movups [rdx], source_reg
            emit(0x0F, 0x11, modrm);
        }break;
        case 32:{
            // vmovups [rdx], source_reg
            emit(0xc5, 0xfc, 0x11, modrm);
        }break;
    }
    
    emit_write_pointer(context, guest_address_reg, host(REGISTER_D), size);
}

//
// Faster implementation for storing a guest register.
//     'guest_address_reg' is a host-register containing a guest_address.
//     'guest_source_register' is a guest-registers, the contents of which are stored to 'guest_address'.
//
// Prefers 'r8' for 'guest_address_reg' and 'rdx' for 'host_address_reg'
//
void emit_write_guest_register(struct context *context, struct host_register guest_address_reg, struct guest_register guest_source_reg, u8 size, u8 rex){
    assert(guest_address_reg.encoding != REGISTER_D);
    
    if(size < 16){
        // lea rdx, [registers + .source_reg]
        emit_inst(0x8D, regm8(8, REGISTER_D, NONVOL_registers), reg_offset(guest_source_reg, size, rex));
    }else{
        // lea rdx, [registers + .source_reg]
        emit_inst(0x8D, regm32(8, REGISTER_D, NONVOL_registers)); emit32(guest_source_reg.encoding * 32 + offset_in_type(struct registers, simd));
    }
    
    emit_write_pointer(context, guest_address_reg, host(REGISTER_D), size);
}

// We use that this does not touch eax. :linux_refactor
void emit_push_pop_fpu_stack(struct context *context, int is_push){
    
    // Get and decrement the top of the stack.
    //     movzx ecx, [registers + .fpu_status_word]
    //     mov edx, ecx
    //     shr ecx, 11
    // inc/dec ecx
    //     and ecx, 7
    emit(0x0f, 0xb7, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_status_word));
    emit(0x8b, make_modrm(MOD_REG, REGISTER_D, REGISTER_C));
    emit(0xC1, make_modrm(MOD_REG, /*shr*/5, REGISTER_C), 11);
    
    if(!is_push){
        // Load guest `ST(0)` into host `ST(0)`.
        //     and ecx, 7
        //     lea r8, [2 * ecx]
        //     fld [registers + .st + 8 * r8]
        emit(0x83, make_modrm(MOD_REG, REG_OPCODE_and, REGISTER_C), 7);
        emit(0x40 | REXR, 0x8d, make_modrm(MOD_REGM, REGISTER_R8, REGISTER_SP), make_sib(0, REGISTER_C, REGISTER_C));
        emit(0x40 | REXX, 0xdb, make_modrm(MOD_REGM_OFF32, /*fld*/8, REGISTER_SP), make_sib(/*log2(8)*/3, REGISTER_R8, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_st));
    }
    
    emit(0xff, make_modrm(MOD_REG, /*inc = 0, dec = 1*/(is_push != 0), REGISTER_C));
    emit(0x83, make_modrm(MOD_REG, REG_OPCODE_and, REGISTER_C), 7);
    
    if(is_push){
        // Save off the index into the stack we should store too.
        //     lea r8, [2 * ecx]
        emit(0x40 | REXR, 0x8d, make_modrm(MOD_REGM, REGISTER_R8, REGISTER_SP), make_sib(0, REGISTER_C, REGISTER_C));
    }
    
    // Adjust the top of the stack.
    //     and edx, ~(7 << 11)
    //     shl ecx, 11
    //     or edx, ecx
    //     mov [registers + .fpu_status_word], edx
    emit(0x81, make_modrm(MOD_REG, REG_OPCODE_and, REGISTER_D)); emit32((u32)(~(7 << 11)));
    emit(0xC1, make_modrm(MOD_REG, /*shl*/4, REGISTER_C), 11);
    emit(0x0b, make_modrm(MOD_REG, REGISTER_D, REGISTER_C));
    emit(0x66, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_D, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_status_word));
    
    if(is_push){
        // Store host `ST(0)` into guest `ST(0)`.
        //     fstp [registers + .st + 8 * r8]
        emit(0x40 | REXX, 0xdb, make_modrm(MOD_REGM_OFF32, /*fstp*/7, REGISTER_SP), make_sib(/*log2(8)*/3, REGISTER_R8, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_st));
    }
}

#if !DISABLE_TAILCALL_OPTIMIZTIONS

enum branch_information{
    BRANCH_unconditional,
    BRANCH_taken,
    BRANCH_not_taken,
};

#pragma pack(push,1)

struct patchable_jit_exit{
    // patchable_jit_exit:
    //     movabs rcx, saved_physical
    //     cmp rcx, rax
    //     jz success (initialized to failiure)
    //     
    // failiure:
    //     lea rax, [rip - patchable_jit_exit]
    //     jmp context->jit_exit + sizeof(xor eax, eax)
    // 
    
    u8 movabs[2]; u64 saved_physical;
    u8 cmp[3];
    u8 jz[2];  u32 success;
};

#pragma pack(pop)

void emit_patchable_jit_exit(struct context *context, u64 branch_rip, enum branch_information branch_information){
    
    // call jit_translate_rip_to_physical @cleanup: there is a slight optimization here, where we patch this as well.
    {
        u8 *current_rip = emit_get_current(context) + 5;
        s64 offset = context->jit_translate_rip_to_physical - current_rip;
        assert((s32)offset == offset);
        emit(0xE8); emit32((s32)offset);
    }
    
    struct host_register physical_address = {REGISTER_A};
    
    assert(physical_address.encoding < 8);
    
    u8 *start = emit_get_current(context);
    
    enum register_encoding saved_physical_reg = (physical_address.encoding == REGISTER_A) ? REGISTER_C : REGISTER_A;
    
    emit(0x48, (u8)(0xb8 + saved_physical_reg)); emit64(0); // saved_physical starts out at 0, it does not matter as success will not jump either way.
    
    emit_inst(0x3B, reg(8, saved_physical_reg, physical_address.encoding));
    emit(0x0f, 0x84); emit32(0);
    
#if !DISABLE_BRANCH_COVERAGE
    if(branch_information != BRANCH_unconditional){
        // Mark the branch as being taken.
        //     mov arg1, NONVOL_context
        //     (arg2 already contains the current 'rip')
        //     mov arg3, 1 ; taken
        //     mov rax, 
        emit_inst(0x8b, reg(8, ARG_REG_1,  NONVOL_context));
        emit(0x48, (u8)(0xb8 + ARG_REG_2)); emit64(branch_rip);
        emit_inst(0xC7, reg(4, /*mov*/0, ARG_REG_3)); emit32(branch_information == BRANCH_taken);
        emit(0x48, 0xB8); emit64((u64)update_coverage_table_for_conditional_branch);
        emit(0xff, make_modrm(MOD_REG, /*call*/2, REGISTER_A));
    }
#endif
    
    emit(0x48, 0x8D, 0x05); emit32((u32)(start - (emit_get_current(context) + 4)));
    
    u32 exit_patch = (s32)((context->jit_exit + /*sizeof(xor eax, eax)*/2) - (emit_get_current(context) + 5));
    emit(0xe9); emit32(exit_patch);
    
}


#pragma pack(push,1)

struct patchable_jit_exit_for_jump_within_page{
    u8 jmp1; u32 rel32;
};


#pragma pack(pop)

void emit_patchable_jit_exit_for_jump_within_page(struct context *context, u64 branch_rip, enum branch_information branch_information){
    
    u8 *start = emit_get_current(context);
    
    emit(0xe9); emit32(0);
    
#if !DISABLE_BRANCH_COVERAGE
    if(branch_information != BRANCH_unconditional){
        // Mark the branch as being taken.
        //     mov arg1, NONVOL_context
        //     (arg2 already contains the current 'rip')
        //     mov arg3, 1 ; taken
        emit_inst(0x8b, reg(8, ARG_REG_1,  NONVOL_context));
        emit(0x48, (u8)(0xb8 + ARG_REG_2)); emit64(branch_rip);
        emit_inst(0xC7, reg(4, /*mov*/0, ARG_REG_3)); emit32(branch_information == BRANCH_taken);
        emit(0x48, 0xB8); emit64((u64)update_coverage_table_for_conditional_branch);
        emit(0xff, make_modrm(MOD_REG, /*call*/2, REGISTER_A));
    }
#endif
    
    emit(0x48, 0x8D, 0x05); emit32((u32)(start - (emit_get_current(context) + 4)));
    u32 exit_patch = (s32)((context->jit_exit + /*sizeof(xor eax, eax)*/2) - (emit_get_current(context) + 5));
    emit(0xe9); emit32(exit_patch);
}

#endif

struct emit_jit_result{
    u8 *jit_code;
    
    u64 block_start_rip;
    u64 block_end_rip;
};

struct emit_jit_result emit_jit(struct context *context, u64 instruction_rip){
    
    struct emit_jit_result emit_jit_result = {0};
    
    //
    // Save the beginning of the jit, this is what we will return in the end.
    //
    u8 *beginning_of_the_jit = emit_get_current(context);
    
    if(!DISABLE_TIMEOUTS){
        // 
        // Check if the timeout counter hit zero.
        // 
        
        // sub NONVOL_timeout_counter, amount_of_instructions_in_block
        emit(0x48 | REXB, 0x81, make_modrm(MOD_REG, REG_OPCODE_sub, NONVOL_timeout_counter)); emit32(0);
        // emit32(amount_of_instructions_in_block);
        
        // jns .continue
        emit(0x79); u8 *continue_patch = emit_get_current(context); emit(0);
        
        // mov [context + .crash], CRASH_timeout
        emit(0xC7, make_modrm(MOD_REGM_OFF32, 0, NONVOL_context)); emit32(offset_in_type(struct context, crash)); emit32(CRASH_timeout);
        
        // jmp [context->jit_exit]
        emit(0xff, make_modrm(MOD_REGM_OFF32, 4, NONVOL_context));
        emit32(offset_in_type(struct context, jit_exit));
        
        // .continue:
        *continue_patch = (u8)(emit_get_current(context) - (continue_patch + 1));
    }
    
    u64 initial_rip = instruction_rip;
    int is_terminating_instruction = 0;
    u32 amount_of_instructions_in_block = 0;
    
    int had_page_boundary = 0;
    int should_check_for_interrupts = 0;
    int skip_jit_exit = 0;
    
    while(!is_terminating_instruction && (instruction_rip - initial_rip) < 0xf00){
        
        // 
        // @note: Only emit one byte blocks, when we should single step.
        //        This is useful for 
        //            1) single stepping in the debugger
        //            2) comparing the jit to the hypervisor
        // 
        is_terminating_instruction = globals.single_stepping;
        
        if(globals.debugger_mode && globals.breakpoint_count != 0){
            for(u32 breakpoint_index = 0; breakpoint_index < array_count(globals.breakpoints); breakpoint_index++){
                struct breakpoint breakpoint = globals.breakpoints[breakpoint_index];
                if(breakpoint.type != BREAKPOINT_execute) continue;
                
                if(breakpoint.address == instruction_rip){
                    // cmp dword [context + .jit_skip_one_breakpoint], 0
                    // jnz .skip
                    emit_inst(0x83, regm32(4, REG_OPCODE_cmp, NONVOL_context)); emit32(offset_in_type(struct context, jit_skip_one_breakpoint)); emit(0);
                    emit(0x75); u8 *skip = emit_get_current(context); emit(0);
                    
                    // mov [context + .crash], CRASH_enter_debugger
                    // jmp [context->jit_exit]
                    emit_inst(0xC7, regm32(4, /*mov*/0, NONVOL_context)); emit32(offset_in_type(struct context, crash)); emit32(CRASH_enter_debugger);
                    emit_inst(0xff, regm32(4, /*jmp*/4, NONVOL_context)); emit32(offset_in_type(struct context, jit_exit));
                    
                    // .skip:
                    *skip = (u8)(emit_get_current(context) - (skip + 1));
                    
                    // 
                    // @note: Resetting is done at the end of this loop for all breakpoint types.
                    //        This is important, because read/write breakpoints rely on `jit_skip_one_breakpoint` to be set until after the first instruction completes executing.
                    // 
                    // mov [context + .jit_skip_one_breakpoint], 0
                    // emit(0xC7, make_modrm(MOD_REGM_OFF32, 0, NONVOL_context)); emit32(offset_in_type(struct context, jit_skip_one_breakpoint)); emit32(0);
                }
            }
        }
        
        struct hook *hook = lookup_hook(instruction_rip);
        if(hook){
            emit_inst(0x8B, reg(8, ARG_REG_1, NONVOL_context));
            emit_inst(0x8B, reg(8, ARG_REG_2, NONVOL_registers));
            emit_call_to_helper(context, hook->hook, HELPER_cares_about_rip | HELPER_might_change_rip | HELPER_might_crash);
        }
        
        if(!DISABLE_TIMEOUTS){
            // dec NONVOL_timeout_counter
            emit_inst(0xFF, reg(8, /*dec*/1, NONVOL_timeout_counter));
        }
        
        u8 instruction[16] = {0};
        u32 instruction_buffer_size = prefetch_instruction(context, instruction_rip, instruction, sizeof(instruction));
        
        u32 offset_in_instruction = 0;
        u8 instruction_byte = instruction[offset_in_instruction++];
        
        u32 legacy_prefix_flags = 0;
        while(1){
            u32 should_break = 0;
            switch(instruction_byte){
                case 0xF0: legacy_prefix_flags |= LEGACY_lock; break;
                case 0xF2: legacy_prefix_flags |= LEGACY_repn; break;
                case 0xF3: legacy_prefix_flags |= LEGACY_rep;  break;
                
                // @note: 2e, 3e are also branch hints
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
            
            instruction_byte = instruction[offset_in_instruction++];
        }
        
        u8 rex = (instruction_byte & 0xf0) == 0x40 ? instruction_byte : 0;
        if(rex) instruction_byte = instruction[offset_in_instruction++];
        
        // 0 = opcode
        // 1 = 0F opcode
        // 2 = 0F 38 opcode
        // 3 = 0F 3A opcode
        int multibyte_mode = 0;
        
        u8 vex = 0;
        u8 opcode = 0;
        
        struct guest_register vex_reg = guest(INVALID_REGISTER);
        
        if(instruction_byte == 0x0f){
            //
            // Two byte instruction.
            //
            multibyte_mode = 1;
            
            instruction_byte = instruction[offset_in_instruction++];
            
            if(instruction_byte == 0x38){
                multibyte_mode = 2;
                instruction_byte = instruction[offset_in_instruction++];
            }else if(instruction_byte == 0x3a){
                multibyte_mode = 3;
                instruction_byte = instruction[offset_in_instruction++];
            }
            
            opcode = instruction_byte;
        }else if(instruction_byte == 0xc5){
            //
            // One byte VEX-prefix.
            //
            multibyte_mode = 1;
            
            u8 RvvvvLpp = instruction[offset_in_instruction++];
            rex |= (RvvvvLpp >> 7) ? 0 : REXR;
            
            vex_reg = guest((~(RvvvvLpp >> 3)) & 0b1111);
            
            switch(RvvvvLpp & 3){
                case 0: break;
                case 1: legacy_prefix_flags |= MANDATORY_PREFIX_66; break;
                case 2: legacy_prefix_flags |= MANDATORY_PREFIX_F3; break;
                case 3: legacy_prefix_flags |= MANDATORY_PREFIX_F2; break;
            }
            
            vex = (RvvvvLpp | 0x80); // Ensure vex is not zero if it was present.
            
            opcode = instruction[offset_in_instruction++];
        }else if(instruction_byte == 0xc4){
            //
            // Two byte VEX-prefix.
            //
            u8 RXBmmmmm = instruction[offset_in_instruction++];
            rex |= ((RXBmmmmm >> 7) & 1) ? 0 : REXR;
            rex |= ((RXBmmmmm >> 6) & 1) ? 0 : REXX;
            rex |= ((RXBmmmmm >> 5) & 1) ? 0 : REXB;
            u8 mmmmm = (RXBmmmmm & 0x1f);
            multibyte_mode = mmmmm & 3; // Rest of the 'mmmmm' are currently not used.
            
            u8 WvvvvLpp = instruction[offset_in_instruction++];
            rex |= (WvvvvLpp >> 7) ? REXW : 0; // Apparently this is not flipped...
            
            vex_reg = guest((~(WvvvvLpp >> 3)) & 0xf);
            
            switch(WvvvvLpp & 3){
                case 0: break;
                case 1: legacy_prefix_flags |= MANDATORY_PREFIX_66; break;
                case 2: legacy_prefix_flags |= MANDATORY_PREFIX_F3; break;
                case 3: legacy_prefix_flags |= MANDATORY_PREFIX_F2; break;
            }
            
            vex = (WvvvvLpp | 0x80); // Ensure vex is not zero if it was present.
            
            opcode = instruction[offset_in_instruction++];
        }else{
            //
            // One byte instruction.
            //
            opcode = instruction_byte;
        }
        
        u32 augmented_opcode = (multibyte_mode << 8) | opcode;
        
        struct guest_register reg = guest(INVALID_REGISTER), regm = guest(INVALID_REGISTER), index_reg = guest(INVALID_REGISTER);
        u8  mod = MOD_REG;
        int scale = 0;
        int is_rip_relative = 0;
        u8  modrm = 0;
        
        u32 address_size = 0;
        u8 *address_offset = null;
        
        if(!instruction_has_no_modrm[augmented_opcode]){
            modrm = instruction[offset_in_instruction++];
            
            mod    = ((modrm >> 6) & 3);
            reg    = guest(((modrm >> 3) & 7) | ((rex & REXR) ? 8 : 0));
            u8 mem = ((modrm >> 0) & 7);
            
            if(mod == MOD_REG){
                regm = guest(mem | ((rex & REXB) ? 8 : 0));
            }else{
                if(mem == REGISTER_SP){
                    //
                    // There is a sib byte.
                    //
                    u8 sib = instruction[offset_in_instruction++];
                    
                    scale = (sib >> 6) & 3;
                    
                    u8 index = ((sib >> 3) & 7) | ((rex & REXX) ? 8 : 0);
                    u8 base  = ((sib >> 0) & 7)| ((rex & REXB) ? 8 : 0);
                    
                    if(index != REGISTER_SP) index_reg = guest(index);
                    if(mod != MOD_REGM || base  != REGISTER_BP) regm = guest(base);
                }else{
                    if(mem == REGISTER_BP && mod == MOD_REGM){
                        is_rip_relative = 1;
                    }else{
                        regm = guest(mem | ((rex & REXB) ? 8 : 0));
                    }
                }
                
                static u8 address_size_for_mod[4] = { [MOD_REGM_OFF8] = 1, [MOD_REGM_OFF32] = 4};
                address_size = address_size_for_mod[mod];
                
                // Apparently you cannot do 'add rax, [r13]' but have to do 'add rax, [r13 + 0]'.
                if(mod == MOD_REGM && regm.encoding == INVALID_REGISTER){
                    // rip relative, or absolute. depending on whether we have sib.
                    address_size = 4;
                }
                
                if(address_size){
                    address_offset = instruction + offset_in_instruction;
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
                        immediate_size = (reg.encoding <= 1) ? 1 : 0;
                    }else{
                        u32 has_operand_size_override = (legacy_prefix_flags & LEGACY_operand_size_override);
                        immediate_size = (reg.encoding <= 1) ? (has_operand_size_override ? 2 : 4) : 0;
                    }
                }break;
                
                case 0xB8:case 0xb9:case 0xba:case 0xbb:case 0xbc:case 0xbd:case 0xbe:case 0xbf:{
                    // mov reg, imm16/32/64
                    immediate_size = operand_size;
                }break;
            }
        }
        
        s8 imm8 = 0;
        u64 immediate = 0;
        if(immediate_size){
            imm8 = *(instruction + offset_in_instruction);
            memcpy(&immediate, instruction + offset_in_instruction, immediate_size);
            
            offset_in_instruction += immediate_size;
        }
        
        u32 instruction_size = offset_in_instruction;
        
        if(instruction_size > instruction_buffer_size){
            // 
            // If the 'instruction_size' exceeds the 'instruction_buffer_size', 
            // this means only part (or no part) of the instruction was on a valid page.
            // 
            // If we have already emitted something for this block, we will end this block here. 
            // If we 'survive' the execution of the block, we will get here again and then we will
            // emit a 'CRASH_execute'.
            // 
            
            if(instruction_rip == initial_rip){
                set_crash_information(context, CRASH_execute, instruction_rip + instruction_buffer_size);
                return emit_jit_result;
            }
            
            // 
            // We "finish" this jit block.
            // 
            break;
        }
        
        if(!had_page_boundary && (initial_rip & ~0xfff) != ((instruction_rip + instruction_size - 1) & ~0xfff)){
            had_page_boundary = 1;
            
            // 
            // If the instruction does not start this block and 
            //    1) the instruction is the first instruction on a new page, or
            //    2) the instruction stattles a page boundary,
            // (we check both by checking that the end is not on the initial page), we emit a call to 
            //   'translate_rip_to_physical(context, instruction_rip + instruction_size, PERMISSION_execute)'.
            // to make sure the access bits get set correctly.
            // 
            //    mov arg1, context
            //    lea arg2, [NONVOL_rip + instruction_size]
            //    mov arg3, PERMISSION_read
            //    mov rax, translate_rip_to_physical
            //    call rax
            emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
            emit_inst(0x8d, regm8(8, ARG_REG_2, NONVOL_rip), (u8)instruction_size);
            emit_inst(0xC7, reg(4, /*mov*/0, ARG_REG_3)); emit32(PERMISSION_read); // @cleanup: Why does this say read
            emit(0x48, 0xB8); emit64((u64)translate_rip_to_physical);
            emit(0xff, make_modrm(MOD_REG, /*call*/2, REGISTER_A));
            
            // 
            // Check if the instruction matches what we expect.
            // If it matches, we can continue. If it matches `-1` meaning the address is not paged in, return a CRASH_execute.
            // Otherwise, our jit is wrong and we need to reset.
            // 
            //     mov rcx, instruction_rip + instruction_size
            //     cmp rax, rcx
            //     je .continue
            // 
            //     mov rdx, CRASH_reset_jit
            //     mov rcx, CRASH_execute
            //     add rax, 1
            //     cmovz rdx, rcx
            //     
            //     mov [context + .crash], rdx
            //     jmp [context->jit_exit]
            //     
            // .continue:
            // 
            
            u64 second_page = translate_rip_to_physical(context, instruction_rip + instruction_size, PERMISSION_execute);
            emit(0x48, (u8)(0xb8 + REGISTER_C)); emit64(second_page); // saved_physical starts out at 0, it does not matter as success will not jump either way.
            emit_inst(0x3B, reg(8, REGISTER_A, REGISTER_C));
            emit(0x74); u8 *continue_patch = emit_get_current(context); emit(0);
            
            emit(0xC7, make_modrm(MOD_REG, 0, REGISTER_D)); emit32(CRASH_reset_jit);
            emit(0xC7, make_modrm(MOD_REG, 0, REGISTER_C)); emit32(CRASH_execute);
            emit_inst(0x83, reg(8, REG_OPCODE_add, REGISTER_A), 1);
            emit_inst((0x0f, 0x44), reg(8, REGISTER_D, REGISTER_C));
            
            emit_inst(0x89, regm32(8, REGISTER_D, NONVOL_context)); emit32(offset_in_type(struct context, crash));
            emit(0xff, make_modrm(MOD_REGM_OFF32, 4, NONVOL_context)); emit32(offset_in_type(struct context, jit_exit));
            
            // .continue:
            *continue_patch = (u8)(emit_get_current(context) - (continue_patch + 1));
        }
        
        amount_of_instructions_in_block += 1;
        context->coverage_increase += update_coverage_table(context, instruction_rip);
        
        // 
        // Instruction jit start:
        // 
        
        if(mod != MOD_REG){
            // If we have a modrm we are most likely calling either
            //     void *guest_read(struct context *context, void *buffer, u64 address, u64 size);
            // and/or
            //     void *guest_write(struct context *context, void *buffer, u64 address, u64 size);
            // therefore load the 'address' into a register.
            
            // most complicated memory operand would look something like this:
            //     [gs: regm + index * shift + offset]
            //
            
            if(regm.encoding == INVALID_REGISTER){
                //
                // There is no base register. this means either [rip + disp32] or [disp32].
                //
                assert(mod == MOD_REGM && address_size == 4);
                
                // mov rax, disp32
                emit_inst(0xc7, reg(8, REG_OPCODE_add, REGISTER_A)); emit_bytes(context, address_offset, address_size);
                
                if(is_rip_relative){
                    // add rax, NONVOL_rip
                    // add rax, instruction_size
                    emit_inst(0x03, reg(8, REGISTER_A, NONVOL_rip));
                    emit_inst(0x83, reg(8, REG_OPCODE_add, REGISTER_A), (u8)instruction_size);
                }
            }else{
                emit_read_gpr(context, host(REGISTER_A), regm, 8, 0);
            }
            
            if(legacy_prefix_flags & LEGACY_gs_segment_override){
                // add rax, [registers + .gs_base]
                emit_inst(0x03, regm32(8, REGISTER_A, NONVOL_registers)); emit32(offset_in_type(struct registers, gs_base));
            }
            
            //
            // @note: we are using 'mod' here also to write the 'lea' in the end.
            //
            
            if(index_reg.encoding != INVALID_REGISTER){
                emit_read_gpr(context, host(REGISTER_C), index_reg, 8, 0);
                
                // lea rax, [rax + rcx * scale (+ address_offset)]
                emit(0x48, 0x8d, make_modrm(mod, REGISTER_A, REGISTER_SP), make_sib(scale, REGISTER_C, REGISTER_A));
                
                if(mod != MOD_REGM) emit_bytes(context, address_offset, address_size);
            }else if(mod != MOD_REGM){
                // lea rax, [rax + address_offset]
                emit(0x48, 0x8d, make_modrm(mod, REGISTER_A, REGISTER_A)); emit_bytes(context, address_offset, address_size);
            }
        }
        
        //
        // Going into this switch, we have the 'guest_address' stored in 'rax'.
        // Otherwise, we only know what the non-volatiles are.
        //
        
        u8 *jump_patch = null;
        int is_unconditional_jump = false;
        u64 conditional_branch_rip = 0;
        
        switch(augmented_opcode){
            //
            // For instructions that work _very_ similar, meaning we only use a different opcode in
            // the generation for the code, we use the 'opcode_to_opcode' map to unify some code paths.
            //
            static u8 opcode_to_opcode[] = {
                // add
                [0x00] = 0x00,
                [0x01] = 0x01,
                [0x02] = 0x00,
                [0x03] = 0x01,
                [0x04] = make_modrm(MOD_REGM, REG_OPCODE_add, NONVOL_registers),
                [0x05] = 0x01,
                
                // or
                [0x08] = 0x08,
                [0x09] = 0x09,
                [0x0a] = 0x08,
                [0x0b] = 0x09,
                [0x0c] = make_modrm(MOD_REGM, REG_OPCODE_or, NONVOL_registers),
                [0x0d] = 0x09,
                
                
                // adc
                [0x10] = 0x10,
                [0x11] = 0x11,
                [0x12] = 0x10,
                [0x13] = 0x11,
                [0x14] = make_modrm(MOD_REGM, REG_OPCODE_adc, NONVOL_registers),
                [0x15] = 0x11,
                
                // sbb
                [0x18] = 0x18,
                [0x19] = 0x19,
                [0x1a] = 0x18,
                [0x1b] = 0x19,
                [0x1c] = make_modrm(MOD_REGM, REG_OPCODE_sbb, NONVOL_registers),
                [0x1d] = 0x19,
                
                // and
                [0x20] = 0x20,
                [0x21] = 0x21,
                [0x22] = 0x20,
                [0x23] = 0x21,
                [0x24] = make_modrm(MOD_REGM, REG_OPCODE_and, NONVOL_registers),
                [0x25] = 0x21,
                
                // sub
                [0x28] = 0x28,
                [0x29] = 0x29,
                [0x2a] = 0x28,
                [0x2b] = 0x29,
                [0x2c] = make_modrm(MOD_REGM, REG_OPCODE_sub, NONVOL_registers),
                [0x2d] = 0x29,
                
                // xor
                [0x30] = 0x30,
                [0x31] = 0x31,
                [0x32] = 0x30,
                [0x33] = 0x31,
                [0x34] = make_modrm(MOD_REGM, REG_OPCODE_xor, NONVOL_registers),
                [0x35] = 0x31,
                
                // cmp
                [0x38] = 0x38,
                [0x39] = 0x39,
                [0x3a] = 0x38,
                [0x3b] = 0x39,
                [0x3c] = make_modrm(MOD_REGM, REG_OPCODE_cmp, NONVOL_registers),
                [0x3d] = 0x39,
            };
            
            
            case 0x38:  // cmp regm8, reg8
            case 0x30:  // xor regm8, reg8
            case 0x28:  // sub regm8, reg8
            case 0x20:  // and regm8, reg8
            case 0x18:  // sbb regm8, reg8
            case 0x10:  // adc regm8, reg8
            case 0x08:  // or  regm8, reg8
            case 0x00:{ // add regm8, reg8
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_C), reg, 1, rex);
                    if(0x10 <= opcode && opcode <= 0x1f) emit_load_flags(context); // Load flags for adc and sbb.
                    
                    // op byte ptr [registers + .regm], cl
                    emit(opcode_to_opcode[opcode], make_modrm(MOD_REGM_OFF8, REGISTER_C, NONVOL_registers), reg_offset(regm, 1, rex));
                    emit_destructively_update_flags(context, host(REGISTER_D));
                }else{
                    // mov flex, rax ; address
                    emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                    
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), /*size*/1, /*need_write_permission*/(opcode != 0x38));
                    
                    emit_read_gpr(context, host(REGISTER_C), reg, 1, rex);
                    if(0x10 <= opcode && opcode <= 0x1f) emit_load_flags(context); // Load flags for adc and sbb.
                    
                    // op al, cl
                    emit(opcode_to_opcode[opcode], make_modrm(MOD_REG, REGISTER_C, REGISTER_A));
                    emit_destructively_update_flags(context, host(REGISTER_D));
                    
                    if(opcode != 0x38){
                        emit_write_host_register(context, host(NONVOL_flex), host(REGISTER_A), 1);
                    }
                }
            }break;
            
            case 0x39:  // cmp regm, reg
            case 0x31:  // xor regm, reg
            case 0x29:  // sub regm, reg
            case 0x21:  // and regm, reg
            case 0x19:  // sbb regm, reg
            case 0x11:  // adc regm, reg
            case 0x09:  // or  regm, reg
            case 0x01:{ // add regm, reg
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_C), reg, operand_size, rex);
                    
                    if(0x10 <= opcode && opcode <= 0x1f) emit_load_flags(context); // Load flags for adc and sbb.
                    
                    // op size ptr [registers + .regm], rcx
                    emit_inst(opcode_to_opcode[opcode], regm8(operand_size, REGISTER_C, NONVOL_registers), (u8)(regm.encoding * 8));
                    emit_destructively_update_flags(context, host(REGISTER_D));
                    
                    if(opcode != 0x39 && operand_size == 4){
                        // mov dword ptr[registers + .regm + 4], 0
                        emit(0xC7, make_modrm(MOD_REGM_OFF8, 0, NONVOL_registers), (u8)(8 * regm.encoding + 4), 0x00, 0x00, 0x00, 0x00);
                    }
                }else{
                    // mov flex, rax ; address
                    emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                    
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), operand_size, /*need_write_permission*/(opcode != 0x39));
                    
                    emit_read_gpr(context, host(REGISTER_C), reg, operand_size, rex);
                    if(0x10 <= opcode && opcode <= 0x1f) emit_load_flags(context); // Load flags for adc and sbb.
                    
                    // op rax, rcx
                    emit_inst(opcode_to_opcode[opcode], reg(operand_size, REGISTER_C, REGISTER_A));
                    emit_destructively_update_flags(context, host(REGISTER_D));
                    
                    if(opcode != 0x39){
                        emit_write_host_register(context, host(NONVOL_flex), host(REGISTER_A), operand_size);
                    }
                }
            }break;
            
            case 0x3a:  // cmp reg8, regm8
            case 0x32:  // xor reg8, regm8
            case 0x2a:  // sub reg8, regm8
            case 0x22:  // and reg8, regm8
            case 0x1a:  // sbb reg8, regm8
            case 0x12:  // adc reg8, regm8
            case 0x0a:  // or  reg8, regm8
            case 0x02:{ // add reg8, regm8
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_C), regm, 1, rex);
                }else{
                    emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), /*size*/1, /*need_write_permission*/0);
                }
                
                if(0x10 <= opcode && opcode <= 0x1f) emit_load_flags(context); // Load flags for adc and sbb.
                
                // op byte ptr [registers + .reg], cl
                u8 offset8 = reg_offset(reg, 1, rex);
                emit(opcode_to_opcode[opcode], make_modrm(MOD_REGM_OFF8, REGISTER_C, NONVOL_registers), offset8);
                emit_destructively_update_flags(context, host(REGISTER_D));
            }break;
            
            case 0x3b:  // cmp reg, regm
            case 0x33:  // xor reg, regm
            case 0x2b:  // sub reg, regm
            case 0x23:  // and reg, regm
            case 0x1b:  // sbb reg, regm
            case 0x13:  // adc reg, regm
            case 0x0b:  // or  reg, regm
            case 0x03:{ // add reg, regm
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_C), regm, operand_size, rex);
                }else{
                    emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), operand_size, /*need_write_permission*/0);
                }
                
                if(0x10 <= opcode && opcode <= 0x1f) emit_load_flags(context); // Load flags for adc and sbb.
                
                // op size ptr[registers + .reg], rcx
                emit_inst(opcode_to_opcode[opcode], regm8(operand_size, REGISTER_C, NONVOL_registers), (u8)(8 * reg.encoding));
                emit_destructively_update_flags(context, host(REGISTER_D));
                
                if(opcode != 0x3b && operand_size == 4){
                    // mov dword ptr[registers + .reg + 4], 0
                    emit_inst(0xC7, regm8(4, /*mov*/0, NONVOL_registers), (u8)(8 * reg.encoding + 4), 0x00, 0x00, 0x00, 0x00);
                }
            }break;
            
            case 0x3c:  // cmp al, imm8
            case 0x34:  // xor al, imm8
            case 0x2c:  // sub al, imm8
            case 0x24:  // and al, imm8
            case 0x1c:  // sbb al, imm8
            case 0x14:  // adc al, imm8
            case 0x0c:  // or  al, imm8
            case 0x04:{ // add al, imm8
                if(0x10 <= opcode && opcode <= 0x1f) emit_load_flags(context); // Load flags for adc and sbb.
                
                // op byte ptr [registers], imm8
                emit(0x80, opcode_to_opcode[opcode], imm8);
                emit_destructively_update_flags(context, host(REGISTER_D));
            }break;
            
            case 0x3d:  // cmp rax, imm32
            case 0x35:  // xor rax, imm32
            case 0x2d:  // sub rax, imm32
            case 0x25:  // and rax, imm32
            case 0x1d:  // sbb rax, imm32
            case 0x15:  // adc rax, imm32
            case 0x0d:  // or  rax, imm32
            case 0x05:{ // add rax, imm32
                if(0x10 <= opcode && opcode <= 0x1f) emit_load_flags(context); // Load flags for adc and sbb.
                
                emit_read_gpr(context, host(REGISTER_A), guest(REGISTER_A), operand_size, rex);
                
                // op rax, imm32
                if(operand_size == 2) emit(0x66);
                if(operand_size == 8) emit(0x48);
                emit(opcode);
                emit_bytes(context, (u8 *)&immediate, immediate_size);
                emit_destructively_update_flags(context, host(REGISTER_D));
                
                if(opcode != /*cmp*/0x3d){
                    emit_write_gpr(context, guest(REGISTER_A), host(REGISTER_A), operand_size, rex);
                }
                
                if(opcode == /*cmp*/0x3d || opcode == /*sub*/0x2d){
                    
                    // @cleanup: This was not here before the :linux_refactor. Check that this works correctly.
                    emit_inst(0xC7, reg(8, /*mov*/0, REGISTER_C)); emit_bytes(context, (u8 *)&immediate, 4);
                    
                    if(opcode == /*sub*/0x2d){
                        // 
                        // Restore the initial operand value
                        //     add rax, rcx
                        emit_inst(0x03, reg(8, REGISTER_A, REGISTER_C));
                    }
                    
                    //
                    // Compare coverage emit a call to 'update_coverage_table_for_compare_coverage'.
                    //
                    //     mov arg4, rcx
                    //     mov arg3, rax
                    //     mov arg1, context
                    //     mov arg2, nonvol_rip
                    emit_inst(0x8b, reg(8, ARG_REG_4, REGISTER_C));
                    emit_inst(0x8b, reg(8, ARG_REG_3, REGISTER_A));
                    emit_inst(0x8b, reg(8, ARG_REG_1,  NONVOL_context));
                    emit_inst(0x8b, reg(8, ARG_REG_2,  NONVOL_rip));
                    
                    //     mov  rax, update_coverage_table_for_compare_coverage
                    //     call rax
                    emit(0x48, 0xB8); emit64((u64)update_coverage_table_for_compare_coverage);
                    emit(0xff, make_modrm(MOD_REG, /*call*/2, REGISTER_A));
                }
            }break;
            
            case 0x50:case 0x51:case 0x52:case 0x53:case 0x54:case 0x55:case 0x56:case 0x57:{
                // push 0x50 + reg
                struct guest_register reg_to_push = guest((opcode - 0x50) | ((rex & REXB) ? 8 : 0));
                
                // Load the current stack pointer into r8.
                emit_read_gpr(context, host(REGISTER_R8), guest(REGISTER_SP), 8, 0);
                
                // sub r8, 8
                emit_inst(0x83, reg(8, REG_OPCODE_sub, REGISTER_R8), 0x08);
                
                // Write the guest register to the stack.
                emit_write_guest_register(context, host(REGISTER_R8), reg_to_push, 8, rex);
                
                // Now that the write succeeded, allocate 8 bytes on the stack.
                //     sub qword [registers + 8 * .rsp], 8
                emit_inst(0x83, regm8(8, REG_OPCODE_sub, NONVOL_registers), (u8)(REGISTER_SP * 8), 0x08);
            }break;
            
            case 0x58:case 0x59:case 0x5a:case 0x5b:case 0x5c:case 0x5d:case 0x5e:case 0x5f:{
                // pop 0x50 + reg
                struct guest_register reg_to_pop = guest((opcode - 0x58) | ((rex & REXB) ? 8 : 0));
                emit_read_gpr(context, host(REGISTER_C), guest(REGISTER_SP), 8, rex);
                emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_C), 8, /*need_write_permission*/0);
                emit_write_gpr(context, reg_to_pop, host(REGISTER_A), 8, rex);
                
                // Deallocate 8 byte of the stack.
                //     add qword [registers + 8 * rsp], 8
                emit_inst(0x83, regm8(8, REG_OPCODE_add, NONVOL_registers), (u8)(REGISTER_SP * 8), 0x08);
            }break;
            
            case 0x63:{ // movsxd reg, regm32
                crash_assert(operand_size == 8 || operand_size == 4, emit_jit_result);
                
                if(mod == MOD_REG){
                    // movsxd rax, dword ptr [registers + .regm]
                    emit_inst(0x63, regm8(8, REGISTER_A, NONVOL_registers), (u8)(regm.encoding * 8));
                }else{
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), /*size*/4,/*need_write_permission*/0);
                    
                    // movsxd rax, rax @cleanup CBW
                    emit_inst(0x63, reg(8, REGISTER_A, REGISTER_A));
                }
                emit_write_gpr(context, reg, host(REGISTER_A), 8, rex);
            }break;
            
            
            case 0x6a:  // push imm8
            case 0x68:{ // push imm16/32
                crash_assert(operand_size == 4, emit_jit_result);
                
                s32 imm32 = imm8;
                if(opcode == 0x68) imm32 = (s32)immediate;
                
                // mov rax, sign extended imm32
                emit_inst(0xc7, reg(8, 0, REGISTER_A)); emit32(imm32);
                
                // Write the immediate.
                emit_read_gpr(context, host(REGISTER_C), guest(REGISTER_SP), 8, rex);
                
                // sub rcx, 8
                emit_inst(0x83, reg(8, REG_OPCODE_sub, REGISTER_C), 0x08);
                
                emit_write_host_register(context, host(REGISTER_C), host(REGISTER_A), 8);
                
                // sub qword [registers + rsp * 8], 8
                emit_inst(0x83, regm8(8, REG_OPCODE_sub, NONVOL_registers), (u8)(REGISTER_SP * 8), 0x08);
            }break;
            
            case 0x6b:{ // imul reg, regm, imm8
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_C), regm, operand_size, rex);
                }else{
                    emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), operand_size, /*need_write_permission*/0);
                }
                
                // imul rax, rcx, immediate
                emit_inst(opcode, reg(operand_size, REGISTER_A, REGISTER_C)); emit(imm8);
                emit_destructively_update_flags(context, host(REGISTER_D));
                
                emit_write_gpr(context, reg, host(REGISTER_A), operand_size, rex);
            }break;
            case 0x69:{ // imul reg, regm, imm16/32
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_A), regm, operand_size, rex);
                }else{
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), operand_size, /*need_write_permission*/0);
                }
                
                // imul rcx, rax, imm
                emit_inst(opcode, reg(operand_size, REGISTER_C, REGISTER_A)); emit_bytes(context, (u8*)&immediate, immediate_size);
                emit_destructively_update_flags(context, host(REGISTER_D));
                
                emit_write_gpr(context, reg, host(REGISTER_C), operand_size, rex);
            }break;
            
            case 0x180: // jo  rel32
            case 0x181: // jno rel32
            case 0x182: // jc  rel32
            case 0x183: // jnc rel32
            case 0x184: // jz  rel32
            case 0x185: // jnz rel32
            case 0x186: // jbe rel32
            case 0x187: // ja  rel32
            case 0x188: // js  rel32
            case 0x189: // jns rel32
            case 0x18a: // jp  rel32
            case 0x18b: // jnp rel32
            case 0x18c: // jl  rel32
            case 0x18d: // jnl rel32
            case 0x18e: // jng rel32
            case 0x18f: // jg  rel32
            
            case 0x70:  // jo  rel8
            case 0x71:  // jno rel8
            case 0x72:  // jc  rel8
            case 0x73:  // jnc rel8
            case 0x74:  // jz  rel8
            case 0x75:  // jnz rel8
            case 0x76:  // jbe rel8
            case 0x77:  // ja  rel8
            case 0x78:  // js  rel8
            case 0x79:  // jns rel8
            case 0x7a:  // jp  rel8
            case 0x7b:  // jnp rel8
            case 0x7c:  // jl  rel8
            case 0x7d:  // jnl rel8
            case 0x7e:  // jng rel8
            case 0x7f:{ // jg  ret8
                //
                // We use one byte jump instructions here, even for 4 byte jump instruction, 
                // as the jump only affects whether on not we alter rip.
                // The real 'jump' happens at the end.
                //
                u8 jcc_opcode = (opcode < 0x80) ? opcode : (opcode - 0x80 + 0x70);
                
                emit_load_flags(context);
                
                // jcc failure
                emit(jcc_opcode ^ 1); jump_patch = emit_get_current(context); emit(0);
                {
                    // mov arg1, nonvol_rip
                    emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_rip));
                    
                    if(opcode < 0x80){
                        s32 disp = instruction_size + (s32)imm8;
                        
                        conditional_branch_rip = instruction_rip + disp;
                        
                        // add arg1, disp + instruction_size
                        emit_inst(0x81, reg(8, REG_OPCODE_add, ARG_REG_1)); emit32(disp);
                    }else{
                        // add arg1, instruction_size
                        emit_inst(0x83, reg(8, REG_OPCODE_add, ARG_REG_1), (u8)instruction_size);
                        
                        // add arg1, disp32
                        emit_inst(0x81, reg(8, REG_OPCODE_add, ARG_REG_1)); emit32((s32)immediate);
                        
                        conditional_branch_rip = instruction_rip + (s32)immediate + (u64)instruction_size;
                    }
                    
                    // @cleanup: Maybe there are two unnecessary instructions here.
                    // mov nonvol_rip, arg1
                    emit_inst(0x8b, reg(8, NONVOL_rip, ARG_REG_1));
                    
                }
                
            }break;
            
            case 0xe3:{ // JRCXZ - jump short if RCX is zero.
                // @cleanup: JECXZ
                // @cleanup: branch coverage.
                
                emit_read_gpr(context, host(REGISTER_C), guest(REGISTER_C), 8, 0);
                
                emit(0xe3); emit(0x02);
                emit(0xEB); jump_patch = emit_get_current(context); emit(0);
                
                // mov rcx, nonvol_rip
                emit_inst(0x8b, reg(8, REGISTER_C, NONVOL_rip));
                s32 disp = instruction_size + (s32)imm8;
                conditional_branch_rip = instruction_rip + disp;
                
                // add rcx, disp + instruction_size
                emit_inst(0x81, reg(8, REG_OPCODE_add, REGISTER_C)); emit32(disp);
                
                // @cleanup: Maybe there are two unnecessary instructions here.
                // mov nonvol_rip, rcx
                emit_inst(0x8b, reg(8, NONVOL_rip, REGISTER_C));
                
            }break;
            
            // op = { add, or, adc, sbb, and, sub, xor, cmp }
            case 0x80:  // op regm8, imm8
            case 0x83:{ // op regm, imm8
                if(opcode == 0x80) operand_size = 1;
                
                if(mod == MOD_REG){
                    if(reg.encoding == REG_OPCODE_adc || reg.encoding == REG_OPCODE_sbb) emit_load_flags(context); // Load flags for adc and sbb.
                    
                    // op size ptr [registers + .regm], imm
                    emit_inst(opcode, regm8(operand_size, reg.encoding, NONVOL_registers), reg_offset(regm, operand_size, rex), imm8);
                    emit_destructively_update_flags(context, host(REGISTER_D));
                    
                    if((reg.encoding != REG_OPCODE_cmp) && operand_size == 4){
                        // mov dword ptr[registers + .regm + 4], 0
                        emit_inst(0xC7, regm8(4, /*mov*/0, NONVOL_registers), (u8)(8 * regm.encoding + 4), 0x00, 0x00, 0x00, 0x00);
                    }
                }else{
                    if(reg.encoding != /*cmp*/7){
                        // mov flex, rax ; address
                        emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                    }
                    
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), operand_size, /*need_write_permission*/(reg.encoding != REG_OPCODE_cmp));
                    
                    if(reg.encoding == REG_OPCODE_adc || reg.encoding == REG_OPCODE_sbb) emit_load_flags(context); // Load flags for adc and sbb.
                    
                    // op size ptr rax, imm
                    emit_inst(opcode, reg(operand_size, reg.encoding, REGISTER_A), imm8);
                    emit_destructively_update_flags(context, host(REGISTER_D));
                    
                    if(reg.encoding != REG_OPCODE_cmp){
                        emit_write_host_register(context, host(NONVOL_flex), host(REGISTER_A), operand_size);
                    }
                }
            }break;
            
            case 0x81:{ // op regm, imm
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_A), regm, operand_size, rex);
                }else{
                    // mov flex, rax ; address
                    emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), operand_size, /*need_write_permission*/(reg.encoding != REG_OPCODE_cmp));
                }
                
                if(reg.encoding == REG_OPCODE_adc || reg.encoding == REG_OPCODE_sbb) emit_load_flags(context); // load flags for adc and sbb
                
                // op rax, immediate
                emit_inst(opcode, reg(operand_size, reg.encoding, REGISTER_A)); emit_bytes(context, (u8 *)&immediate, immediate_size);
                emit_destructively_update_flags(context, host(REGISTER_D));
                
                if(reg.encoding != REG_OPCODE_cmp){
                    if(mod == MOD_REG){
                        emit_write_gpr(context, regm, host(REGISTER_A), operand_size, rex);
                    }else{
                        if(reg.encoding == REG_OPCODE_sub){
                            //
                            // For compare coverage, we cannot write the value here, as that would distroy 
                            // the contents of rax and rcx. Hence instead we just write the value of rax to the
                            // temp_buffer and then after we are done with compare coverage, we call 'emit_write_pointer'.
                            //
                            //    mov [context + .jit_scratch], rax
                            emit_inst(0x89, regm32(8, REGISTER_A, NONVOL_context)); emit32(offset_in_type(struct context, jit_scratch));
                        }else{
                            emit_write_host_register(context, host(NONVOL_flex), host(REGISTER_A), operand_size);
                        }
                    }
                }
                
                if(reg.encoding == REG_OPCODE_cmp || reg.encoding == REG_OPCODE_sub){
                    
                    // @cleanup: This was not here before the :linux_refactor. Check that this works correctly.
                    emit_inst(0xC7, reg(8, /*mov*/0, REGISTER_C)); emit_bytes(context, (u8 *)&immediate, 4);
                    
                    if(reg.encoding == REG_OPCODE_sub){
                        // 
                        // Restore the initial operand value.
                        //     add rax, rcx
                        emit_inst(0x03, reg(operand_size, REGISTER_A, REGISTER_C));
                    }
                    
                    //
                    // Compare coverage emit a call to 'update_coverage_table_for_compare_coverage'.
                    //
                    //     mov r9,  rcx
                    //     mov r8,  rax
                    //     mov rcx, context
                    //     mov rdx, nonvol_rip
                    emit_inst(0x8b, reg(8, ARG_REG_4, REGISTER_C));
                    emit_inst(0x8b, reg(8, ARG_REG_3, REGISTER_A));
                    emit_inst(0x8b, reg(8, ARG_REG_1,  NONVOL_context));
                    emit_inst(0x8b, reg(8, ARG_REG_2,  NONVOL_rip));
                    
                    //     mov  rax, update_coverage_table_for_compare_coverage
                    //     call rax
                    emit(0x48, 0xB8); emit64((u64)update_coverage_table_for_compare_coverage);
                    emit(0xff, make_modrm(MOD_REG, /*call*/2, REGISTER_A));
                    
                    if(mod != MOD_REG && reg.encoding == REG_OPCODE_sub){
                        // lea rdx, [context + .jit_scratch]
                        emit_inst(0x8D, regm32(8, REGISTER_D, NONVOL_context)); emit32(offset_in_type(struct context, jit_scratch));
                        
                        emit_write_pointer(context, host(NONVOL_flex), host(REGISTER_D), operand_size);
                    }
                }
            }break;
            
            case 0x85:  // test regm, reg
            case 0x84:{ // test regm8, reg8
                if(opcode == 0x84) operand_size = 1;
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_C), regm, operand_size, rex);
                }else{
                    emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), operand_size, /*need_write_permission*/0);
                }
                
                emit_read_gpr(context, host(REGISTER_A), reg, operand_size, rex);
                
                // test rcx, rax
                emit_inst(opcode, reg(operand_size, REGISTER_A, REGISTER_C));
                emit_destructively_update_flags(context, host(REGISTER_D));
            }break;
            
            
            case 0x86:  // xchg reg8, regm8
            case 0x87:{ // xchg reg, regm
                if(opcode == 0x86) operand_size = 1;
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_A), regm, operand_size, rex);
                    emit_read_gpr(context, host(REGISTER_C), reg,  operand_size, rex);
                    
                    emit_write_gpr(context, reg,  host(REGISTER_A), operand_size, rex);
                    emit_write_gpr(context, regm, host(REGISTER_C),  operand_size, rex);
                }else{
                    // mov flex, rax ; address
                    emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                    
                    // Read the 'guest_address'.
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), operand_size, /*need_write_permission*/1);
                    
                    // Save the value we loaded in the 'flex' and load the address into r8.
                    //     mov r8, flex
                    //     mov flex, rax
                    emit_inst(0x8b, reg(8, REGISTER_R8, NONVOL_flex));
                    emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                    
                    // Write the contents of 'reg' to 'guest_address'.
                    emit_write_guest_register(context, host(REGISTER_R8), reg, operand_size, rex);
                    
                    // Write the value to 'reg'.
                    emit_write_gpr(context, reg, host(NONVOL_flex), operand_size, rex);
                }
            }break;
            
            case 0x88:  // mov regm8, reg8
            case 0x89:{ // mov regm, reg
                if(opcode == 0x88) operand_size = 1;
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_C), reg, operand_size, rex);
                    emit_write_gpr(context, regm, host(REGISTER_C), operand_size, rex);
                }else{
                    emit_write_guest_register(context, host(REGISTER_A), reg, operand_size, rex);
                }
            }break;
            
            case 0x8a:  // mov reg8, regm8
            case 0x8b:{ // mov reg, regm
                if(opcode == 0x8a) operand_size = 1;
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_C), regm, operand_size, rex);
                }else{
                    emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), operand_size, /*need_write_permission*/0);
                }
                emit_write_gpr(context, reg, host(REGISTER_C), operand_size, rex);
            }break;
            
            case 0x8C:{ // mov regm, seg
                
                u32 offset = 0;
                switch(reg.encoding){
                    case 0: offset = offset_in_type(struct registers, es.selector); break;
                    case 1: offset = offset_in_type(struct registers, cs.selector); break;
                    case 2: offset = offset_in_type(struct registers, ss.selector); break;
                    case 3: offset = offset_in_type(struct registers, ds.selector); break;
                    case 4: offset = offset_in_type(struct registers, fs.selector); break;
                    case 5: offset = offset_in_type(struct registers, gs.selector); break;
                    crash_invalid_default_case("Unhandled segment in 'mov regm, seg'.", emit_jit_result);
                }
                
                // movzx  rcx, word ptr [registers + .seg] - :linux_refactor
                emit(0x0f, 0xb7, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset);
                
                if(mod == MOD_REG){
                    emit_write_gpr(context, regm, host(REGISTER_C), operand_size, rex);
                }else{
                    emit_write_host_register(context, host(REGISTER_A), host(REGISTER_C), 2);
                }
            }break;
            
            case 0x8d:{ // lea reg, m
                crash_assert(mod != MOD_REG, emit_jit_result);
                
                if(operand_size == 4){
                    //
                    // We have to truncate the register, as 'emit_write_gpr' will write the whole 8 bytes.
                    //
                    emit_inst(0x89, reg(4, REGISTER_A, REGISTER_A));
                }
                
                emit_write_gpr(context, reg, host(REGISTER_A), operand_size, rex);
            }break;
            
            case 0x8e:{ // mov seg, regm
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_C), regm, 2, 0);
                }else{
                    emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), 2, /*need_write_permission*/0);
                }
                
                u32 offset = 0;
                switch(reg.encoding){
                    case 0: offset = offset_in_type(struct registers, es.selector); break;
                    case 1: offset = offset_in_type(struct registers, cs.selector); break;
                    case 2: offset = offset_in_type(struct registers, ss.selector); break;
                    case 3: offset = offset_in_type(struct registers, ds.selector); break;
                    case 4: offset = offset_in_type(struct registers, fs.selector); break;
                    case 5: offset = offset_in_type(struct registers, gs.selector); break;
                    crash_invalid_default_case("Unhandled segment in 'mov seg, regm'.", emit_jit_result);
                }
                
                // mov word ptr [registers + .seg], rcx
                emit_inst(0x89, regm32(2, REGISTER_C, NONVOL_registers)); emit32(offset);
            }break;
            
            case 0x8f:{ // pop regm
                crash_assert(reg.encoding == 0, emit_jit_result); // Only pop regm defined.
                
                if(mod != MOD_REG){
                    // mov flex, rax ; address
                    emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                }
                
                // Load the stack pointer.
                emit_read_gpr(context, host(REGISTER_A), guest(REGISTER_SP), 8, rex);
                
                // Read from the stack.
                emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), 8, /*need_write_permission*/0);
                
                if(mod == MOD_REG){
                    emit_write_gpr(context, reg, host(REGISTER_C), 8, rex);
                }else{
                    
                    if(regm.encoding == REGISTER_SP){
                        // For `pop [rsp]` the address is decremented before the store, hence this should be:
                        // 
                        //     mov temp, [rsp] (top of stack)
                        //     add rsp, 8
                        //     mov [rsp], temp ([rsp] being the memory operand).
                        //     
                        // Because we have loaded the memory operand into flex with the assumption 
                        // that `rsp` did not change, we have to adjust the value here.
                        // 
                        
                        // add flex, 8
                        emit_inst(0x83, reg(8, REG_OPCODE_add, NONVOL_flex), 0x08);
                    }
                    
                    emit_write_host_register(context, host(NONVOL_flex), host(REGISTER_C), operand_size);
                }
                
                // Deallocate 8 byte of the stack.
                //    add qword [registers + 8 * rsp], 8
                emit_inst(0x83, regm8(8, REG_OPCODE_add, NONVOL_registers), (u8)(REGISTER_SP * 8), 0x08);
            }break;
            
            case 0x90:case 0x91:case 0x92:case 0x93:case 0x94:case 0x95:case 0x96:case 0x97:{
                // xchg + reg, rax
                struct guest_register xchg_reg = guest((opcode - 0x90) | ((rex & REXB) ? 8 : 0));
                
                if(xchg_reg.encoding == 0) break; // 0x90 is a nop, no matter the prefix. This appears to be a special case!
                
                emit_read_gpr(context, host(REGISTER_C), xchg_reg,         operand_size, rex);
                emit_read_gpr(context, host(REGISTER_A), guest(REGISTER_A), operand_size, rex);
                
                emit_write_gpr(context, xchg_reg,          host(REGISTER_A), operand_size, rex);
                emit_write_gpr(context, guest(REGISTER_A), host(REGISTER_C), operand_size, rex);
            }break;
            
            case 0x98:{ // CBW, CWDE, CDQE
                emit_read_gpr(context, host(REGISTER_A), guest(REGISTER_A), operand_size, rex);
                if(operand_size == 2) emit(0x66);
                if(operand_size == 8) emit(0x48);
                emit(0x98);
                emit_write_gpr(context, guest(REGISTER_A), host(REGISTER_A), operand_size, rex);
            }break;
            
            case 0x99:{ // CBW, CWDE, CDQE
                emit_read_gpr(context, host(REGISTER_A), guest(REGISTER_A), operand_size, rex);
                if(operand_size == 2) emit(0x66);
                if(operand_size == 8) emit(0x48);
                emit(0x99);
                emit_write_gpr(context, guest(REGISTER_D), host(REGISTER_D), operand_size, rex);
            }break;
            
            case 0x9b:{ // FWAIT
                // Do nothing. For now we don't care about x87 floating point exceptions (they don't exists!)
            }break;
            
            case 0x9c:{ // pushf
                // mov rax, qword [registers + .rflags]
                emit_inst(0x8B, regm32(8, REGISTER_A, NONVOL_registers)); emit32(offset_in_type(struct registers, rflags));
                
                // and rax, 0xfcffff
                emit(0x48, 0x25); emit32(0xfcffff);
                
                // Load the stack pointer.
                emit_read_gpr(context, host(REGISTER_R8), guest(REGISTER_SP), 8, rex);
                
                // Subtract 8 from the stack pointer.
                //      sub r8, 8
                emit_inst(0x83, reg(8, REG_OPCODE_sub, REGISTER_R8), 0x08);
                
                // Write the rflags to the stack.
                emit_write_host_register(context, host(REGISTER_R8), host(REGISTER_A), 8);
                
                // If the write succeeds commit the stack allocation.
                //      sub qword [registers + 8 * rsp], 8
                emit_inst(0x83, regm8(8, REG_OPCODE_sub, NONVOL_registers), (u8)(REGISTER_SP * 8), 0x08);
            }break;
            
            case 0x9d:{ // popf
                // Get the stack pointer.
                emit_read_gpr(context, host(NONVOL_flex), guest(REGISTER_SP), 8, rex);
                
                // Read the flags from the stack.
                emit_read_into_gpr(context, host(REGISTER_A), host(NONVOL_flex), 4, /*need_write_permission*/0);
                
                // 
                // Updating the flags:
                // 
                //    Because there are some "privileged" flags, we have to only restore certain flags here.
                //    This depends on the value of the CPL, the value of IOPL, as well as the operand size.
                //    We assume 'IOPL == 0' and 'operand size == 64'. The value of IOPL controls whether IF is restored.
                //    Then the following updates are necessary:
                //    
                //             CF PF AF ZF SF TF IF DF OF IOPL NT RF VM AC VIF VIP ID
                //    CPL 0:    S  S  S  S  S  S  S  S  S  S    S  0  N  S  N   N   S 
                //    CPL 1-3   S  S  S  S  S  S  N  S  S  N    S  0  N  S  N   N   S
                // 
                // S = Updated From Stack
                // 0 = Value is cleared (only for RF)
                // N = No change in value
                // 
                
                u32 flags_to_change_user   = FLAG_CF | FLAG_PF | FLAG_AF | FLAG_ZF | FLAG_SF | FLAG_TF | FLAG_DF | FLAG_OF | FLAG_NT | FLAG_AC | FLAG_ID;
                u32 flags_to_change_kernel = flags_to_change_user | FLAG_IF; // @cleanup: IOPL ?
                
                // Compute the mask we should use to filter in ecx: :linux_refactor
                //     mov ecx, flags_to_change_user
                //     mov edx, flags_to_change_kernel
                //     test [registers + .cs.selector], 3
                //     movz ecx, edx
                emit(0xb8 + REGISTER_C); emit32(flags_to_change_user);
                emit(0xb8 + REGISTER_D); emit32(flags_to_change_kernel);
                emit_inst(0xf6, regm32(4, /*test*/0, NONVOL_registers)); emit32(offset_in_type(struct registers, cs.selector)); emit(3);
                emit(0x0f, 0x44, make_modrm(MOD_REG, REGISTER_C, REGISTER_D));
                
                // Comput the new values in rax and add them incrementally into [registers + .rflags]
                //     and rax, rcx
                //     not rcx
                //     and qword [registers + .rflags], rcx
                //     or  qword [registers + .rflags], rax
                emit_inst(0x23, reg(8, REGISTER_A, REGISTER_C));
                emit_inst(0xf7, reg(8, /*not*/2, REGISTER_C));
                emit_inst(0x21, regm32(8, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, rflags));
                emit_inst(0x09, regm32(8, REGISTER_A, NONVOL_registers)); emit32(offset_in_type(struct registers, rflags));
                
                // Deallocate 8 byte of the stack.
                //     add qword [registers + 8 * rsp], 8
                emit_inst(0x83, regm8(8, REG_OPCODE_add, NONVOL_registers), (u8)(REGISTER_SP * 8), 0x08);
                
                // IF might have changed, so we should check for interrupts.
                should_check_for_interrupts = 1;
            }break;
            
            case 0x9e:{ // sahf - store AH into flags
                // mov al, [registers + .ah]
                emit_read_gpr(context, host(REGISTER_A), guest(REGISTER_A + 4), 1, /*no rex*/0);
                
                // mov byte [registers + .rflags], al
                u32 rflags_offset = offset_in_type(struct registers, rflags);
                emit_inst(0x88, regm32(1, REGISTER_A, NONVOL_registers)); emit32(rflags_offset);
            }break;
            
            case 0x9f:{ // lahf - load status flags into AH
                // mov eax, dword [registers + .rflags]
                emit_inst(0x8B, regm32(4, REGISTER_A, NONVOL_registers)); emit32(offset_in_type(struct registers, rflags));
                
                // and eax, ~0x28
                // or  eax, 2
                emit_inst(0x83, reg(4, REG_OPCODE_and, REGISTER_A), 0xd7);
                emit_inst(0x83, reg(4, REG_OPCODE_or,  REGISTER_A), 0x02);
                
                // Write flags to AH.
                emit_write_gpr(context, guest(REGISTER_A + 4), host(REGISTER_A), 1, /*no rex*/0);
            }break;
            
            case 0xa0:  // mov al,  movoffs8
            case 0xa1:{ // mov rax, movoffs
                if(opcode == 0xa0) operand_size = 1;
                
                // mov rax, address
                emit(0x48, 0xB8); emit64(immediate);
                
                emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), operand_size, /*need_write_permission*/0);
                emit_write_gpr(context, guest(REGISTER_A), host(REGISTER_A), operand_size, rex);
            }break;
            
            case 0xa2:  // mov movoffs8, al
            case 0xa3:{ // mov movoffs,  rax
                if(opcode == 0xa2) operand_size = 1;
                
                // mov rax, address
                emit(0x48, 0xB8); emit64(immediate);
                
                emit_write_guest_register(context, host(REGISTER_A), guest(REGISTER_A), operand_size, rex);
            }break;
            
            case 0xa4: case 0xa5:{
                if(opcode == 0xa4) operand_size = 1;
                
                // mov arg1, context
                // mov arg2, registers
                // mov arg3, operand_size
                // mov arg4, legacy_prefix_flags
                emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                emit_inst(0x8b, reg(8, ARG_REG_2, NONVOL_registers));
                emit_inst(0xC7, reg(8, /*mov*/0, ARG_REG_3)); emit32(operand_size);
                emit_inst(0xC7, reg(8, /*mov*/0, ARG_REG_4)); emit32(legacy_prefix_flags);
                emit_call_to_helper(context, helper_movs, HELPER_might_crash);
            }break;
            
            case 0xa6: case 0xa7:{ // @cleanup: stupid cmpsb
                crash_assert(legacy_prefix_flags & LEGACY_repz, emit_jit_result);
                
                // @incomplete: DF
                
                if(opcode == 0xa6) operand_size = 1;
                
                u8 *failed_patch_address;
                u8 *success_patch_address;
                u8 *start_address = emit_get_current(context);
                {
                    // Read the source address.
                    emit_read_gpr(context, host(REGISTER_R8), guest(REGISTER_SI), 8, 0);
                    
                    // Load the source value to the non-volatile flex register, so it does not get destroyed by the read below.
                    emit_read_into_gpr(context, host(NONVOL_flex), host(REGISTER_R8), operand_size, /*need_write_permission*/0);
                    
                    // Load the destination address.
                    emit_read_gpr(context, host(REGISTER_R8), guest(REGISTER_DI), 8, 0);
                    
                    // Read the value of the destination address.
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_R8), operand_size, /*need_write_permission*/0);
                    
                    // Perform the comparison.
                    //     cmp byte(flex), al
                    emit_inst(0x3A + (operand_size != 1), reg(operand_size, NONVOL_flex, REGISTER_A)); // specify rex just in case
                    
                    // Jump out if the result was not zero:
                    //     jnz failed
                    emit(0x75); failed_patch_address = emit_get_current(context); emit(0);
                    
                    emit_destructively_update_flags(context, host(REGISTER_R9));
                    
                    // Increment rsi and rdi by the operand size.
                    if(operand_size == 1){
                        // inc qword [registers + .reg]
                        emit_inst(0xff, regm8(8, /*inc*/0, NONVOL_registers), (u8)(REGISTER_SI * 8));
                        emit_inst(0xff, regm8(8, /*inc*/0, NONVOL_registers), (u8)(REGISTER_DI * 8));
                    }else{
                        // add qword [registers + .reg], operand_size
                        emit_inst(0x83, regm8(8, REG_OPCODE_add, NONVOL_registers), (u8)(REGISTER_SI * 8), operand_size);
                        emit_inst(0x83, regm8(8, REG_OPCODE_add, NONVOL_registers), (u8)(REGISTER_DI * 8), operand_size);
                    }
                    
                    // dec qword [registers + .rcx]
                    emit_inst(0xff, regm8(8, /*dec*/1, NONVOL_registers), (u8)(REGISTER_C * 8));
                    
                    // jnz start_address
                    u8 *end_address = emit_get_current(context);
                    s64 jump_disp = (start_address - (end_address + 6));
                    assert(jump_disp == (s32)jump_disp);
                    emit(0x0f, 0x85); emit32((s32)jump_disp);
                    
                    // jmp success
                    emit(0xeb); success_patch_address = emit_get_current(context); emit(0);
                }
                
                {
                    // failed:
                    u8 *end = emit_get_current(context);
                    s64 jump_disp = (end - (failed_patch_address + 1));
                    assert(jump_disp == (s8)jump_disp);
                    *failed_patch_address = (u8)jump_disp;
                }
                emit_destructively_update_flags(context, host(REGISTER_R9));
                
                // Increment rsi and rdi by the operand size.
                if(operand_size == 1){
                    // inc qword [registers + .reg]
                    emit_inst(0xff, regm8(8, /*inc*/0, NONVOL_registers), (u8)(REGISTER_SI * 8));
                    emit_inst(0xff, regm8(8, /*inc*/0, NONVOL_registers), (u8)(REGISTER_DI * 8));
                }else{
                    // add qword [registers + .reg], operand_size
                    emit_inst(0x83, regm8(8, REG_OPCODE_add, NONVOL_registers), (u8)(REGISTER_SI * 8), operand_size);
                    emit_inst(0x83, regm8(8, REG_OPCODE_add, NONVOL_registers), (u8)(REGISTER_DI * 8), operand_size);
                }
                
                // dec qword [registers + .rcx]
                emit_inst(0xff, regm8(8, /*dec*/1, NONVOL_registers), (u8)(REGISTER_C * 8));
                {
                    // success:
                    u8 *end = emit_get_current(context);
                    s64 jump_disp = (end - (success_patch_address + 1));
                    assert(jump_disp == (s8)jump_disp);
                    *success_patch_address = (s8)jump_disp;
                }
            }break;
            
            
            case 0xae:
            case 0xaf:{ // @cleanup: stupid scasb
                crash_assert((legacy_prefix_flags & LEGACY_repz) || (legacy_prefix_flags & LEGACY_repn), emit_jit_result);
                
                if(opcode == 0xae) operand_size = 1;
                
                // Load the source compare value (rax) to the non-volatile flex register, so it does not get destroyed by the reads below.
                emit_read_gpr(context, host(NONVOL_flex), guest(REGISTER_A), operand_size, 0);
                
                u8 *failed_patch_address;
                u8 *success_patch_address;
                u8 *start_address = emit_get_current(context);
                {
                    
                    // Load the destination address.
                    emit_read_gpr(context, host(REGISTER_R8), guest(REGISTER_DI), 8, 0);
                    
                    // Read the value of the destination address.
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_R8), operand_size, /*need_write_permission*/0);
                    
                    // Perform the comparison.
                    //     cmp flex, rax
                    emit_inst(0x3A + (operand_size != 1), reg(operand_size, NONVOL_flex, REGISTER_A)); // specify rex just in case
                    
                    
                    if(legacy_prefix_flags & LEGACY_repz){
                        // Jump out if the result was not zero:
                        //     jnz failed
                        emit(0x75); failed_patch_address = emit_get_current(context); emit(0);
                    }else{
                        assert(legacy_prefix_flags & LEGACY_repn);
                        // Jump out if the result was zero:
                        //     jz failed
                        emit(0x74); failed_patch_address = emit_get_current(context); emit(0);
                    }
                    
                    
                    emit_destructively_update_flags(context, host(REGISTER_R9));
                    
                    // Increment rsi and rdi by the operand size.
                    if(operand_size == 1){
                        // inc qword [registers + .reg]
                        emit_inst(0xff, regm8(8, /*inc*/0, NONVOL_registers), (u8)(REGISTER_DI * 8));
                    }else{
                        // add qword [registers + .reg], operand_size
                        emit_inst(0x83, regm8(8, REG_OPCODE_add, NONVOL_registers), (u8)(REGISTER_DI * 8), operand_size);
                    }
                    
                    // dec qword [registers + .rcx]
                    emit_inst(0xff, regm8(8, /*dec*/1, NONVOL_registers), (u8)(REGISTER_C * 8));
                    // jnz start_address
                    
                    u8 *end_address = emit_get_current(context);
                    s64 jump_disp = (start_address - (end_address + 6));
                    assert(jump_disp == (s32)jump_disp);
                    emit(0x0f, 0x85); emit32((s32)jump_disp);
                    
                    // jmp success
                    emit(0xeb); success_patch_address = emit_get_current(context); emit(0);
                }
                
                {
                    // failed:
                    u8 *end = emit_get_current(context);
                    s64 jump_disp = (end - (failed_patch_address + 1));
                    assert(jump_disp == (s8)jump_disp);
                    *failed_patch_address = (u8)jump_disp;
                }
                emit_destructively_update_flags(context, host(REGISTER_R9));
                
                // Increment rsi and rdi by the operand size.
                if(operand_size == 1){
                    // inc qword [registers + .reg]
                    emit_inst(0xff, regm8(8, /*inc*/0, NONVOL_registers), (u8)(REGISTER_DI * 8));
                }else{
                    // add qword [registers + .reg], operand_size
                    emit_inst(0x83, regm8(8, REG_OPCODE_add, NONVOL_registers), (u8)(REGISTER_DI * 8), operand_size);
                }
                
                // dec qword [registers + .rcx]
                emit_inst(0xff, regm8(8, /*dec*/1, NONVOL_registers), (u8)(REGISTER_C * 8));
                
                {
                    // success:
                    u8 *end = emit_get_current(context);
                    s64 jump_disp = (end - (success_patch_address + 1));
                    assert(jump_disp == (s8)jump_disp);
                    *success_patch_address = (s8)jump_disp;
                }
            }break;
            
            
            case 0xa9:  // test rax, imm
            case 0xa8:{ // test al, imm8
                if(opcode == 0xa8) operand_size = 1;
                
                emit_read_gpr(context, host(REGISTER_A), guest(REGISTER_A), operand_size, 0);
                
                if(operand_size == 2) emit(0x66);
                if(operand_size == 8) emit(0x48);
                emit(opcode);
                emit_bytes(context, (u8 *)&immediate, immediate_size);
                emit_destructively_update_flags(context, host(REGISTER_D));
            }break;
            
            case 0xaa: case 0xab:{
                if(opcode == 0xaa) operand_size = 1;
                
                // mov arg1, context
                // mov arg2, registers
                // mov arg3, operand_size
                // mov arg4, legacy_prefix_flags
                emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                emit_inst(0x8b, reg(8, ARG_REG_2, NONVOL_registers));
                emit_inst(0xC7, reg(8, 0, ARG_REG_3)); emit32(operand_size);
                emit_inst(0xC7, reg(8, 0, ARG_REG_4)); emit32(legacy_prefix_flags);
                emit_call_to_helper(context, helper_stos, HELPER_might_crash);
            }break;
            
            case 0xac: case 0xad:{ // LODSB, LODSW, LODSD, LODSQ - Load xxx at address RSI into rAX.
                assert((legacy_prefix_flags & LEGACY_rep) == 0);
                if(opcode == 0xac) operand_size = 1;
                
                // Load the source address.
                emit_read_gpr(context, host(REGISTER_R8), guest(REGISTER_SI), /*operand_size*/8, /*rex*/0);
                
                // Load the source value.
                emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_R8), operand_size, /*need_write_permission*/0);
                
                emit_write_gpr(context, guest(REGISTER_A), host(REGISTER_A), operand_size, /*rex*/0);
                
                // Increment rsi and rdi by the operand size.
                if(operand_size == 1){
                    // inc qword [registers + .reg]
                    emit_inst(0xff, regm8(8, /*inc*/0, NONVOL_registers), (u8)(REGISTER_SI * 8));
                }else{
                    // add qword [registers + .reg], operand_size
                    emit_inst(0x83, regm8(8, REG_OPCODE_add, NONVOL_registers), (u8)(REGISTER_SI * 8), operand_size);
                }
            }break;
            
            case 0xB0: case 0xB1: case 0xB2: case 0xB3: case 0xB4: case 0xB5: case 0xB6: case 0xB7:{
                // mov reg8, imm8
                u8 dest_reg = (opcode - 0xB0) | ((rex & REXB) ? 8 : 0);
                
                // mov byte ptr[registers + .dest_reg], imm8
                emit_inst(0xc6, regm8(1, 0, NONVOL_registers), (u8)(dest_reg * 8), imm8);
            }break;
            
            case 0xB8: case 0xB9: case 0xBa: case 0xBb: case 0xBc: case 0xBd: case 0xBe: case 0xBf:{
                // mov reg, imm
                struct guest_register dest_reg = guest((opcode - 0xB8) | ((rex & REXB) ? 8 : 0));
                
                // mov rax, imm
                emit(0x48, 0xB8); emit64(immediate);
                
                emit_write_gpr(context, dest_reg, host(REGISTER_A), operand_size, 0);
            }break;
            
            // xxx = { rol, ror, rcl, rcr, shl, shr, sal, sar }
            case 0xC1:  // xxx regm,  imm8
            case 0xC0:{ // xxx regm8, imm8
                if(opcode == 0xC0) operand_size = 1;
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_A), regm, operand_size, rex);
                    
                    emit_load_flags(context); // These have some unaffected flags!
                    
                    // xxx size ptr rax, imm8
                    emit_inst(opcode, reg(operand_size, reg.encoding, REGISTER_A), imm8);
                    emit_destructively_update_flags(context, host(REGISTER_D));
                    
                    emit_write_gpr(context, regm, host(REGISTER_A), operand_size, rex);
                }else{
                    // mov flex, rax ; address
                    emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                    
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), operand_size, /*need_write_permission*/1);
                    
                    emit_load_flags(context); // These have some unaffected flags!
                    
                    // op size ptr rax, imm8
                    emit_inst(opcode, reg(operand_size, reg.encoding, REGISTER_A), imm8);
                    emit_destructively_update_flags(context, host(REGISTER_D));
                    
                    emit_write_host_register(context, host(NONVOL_flex), host(REGISTER_A), operand_size);
                }
            }break;
            
            case 0xC2:{ // ret imm16
                u16 imm = (u16)immediate; // @cleanup: should this be signed?
                
                // Attempt to read the return value.
                emit_read_gpr(context, host(REGISTER_D), guest(REGISTER_SP), 8, rex);
                
                // add rdx, imm
                emit_inst(0x81, reg(8, REG_OPCODE_add, REGISTER_D)); emit32(imm);
                
                // Attempt to read the stack at offset 'imm16'.
                emit_read_into_gpr(context, host(REGISTER_D), host(REGISTER_D), 8, /*need_write_permission*/0);
                
                // if we succeeded, add 'immediate + 8' to rsp and set the value of rip
                // add qword [registers + .rsp], (imm + 8)
                // mov qword [registers + .rip], rax
                
                emit_inst(0x81, regm8(8, REG_OPCODE_add, NONVOL_registers), (u8)(REGISTER_SP * 8)); emit32(imm + 8);
                emit_inst(0x89, regm32(8, REGISTER_A, NONVOL_registers)); emit32(offset_in_type(struct registers, rip));
                
                // mov nonvol_rip, rdx
                emit_inst(0x8b, reg(8, NONVOL_rip, REGISTER_D));
                
                is_unconditional_jump = 1;
            } break;
            
            case 0xC3:{
                // Pop the return value.
                emit_read_gpr(context, host(REGISTER_D), guest(REGISTER_SP), 8, rex);
                emit_read_into_gpr(context, host(REGISTER_D), host(REGISTER_D), 8, /*need_write_permission*/0);
                
                // add rsp, 8
                emit_inst(0x83, regm8(8, REG_OPCODE_add, NONVOL_registers), (u8)(REGISTER_SP * 8), 8);
                
                // mov nonvol_rip, rdx
                emit_inst(0x8b, reg(8, NONVOL_rip, REGISTER_D));
                
                is_unconditional_jump = 1;
            }break;
            
            case 0xC9:{ // LEAVE
                
                // LEAVE (rsp = rbp + 8, rbp = [rbp]):
                // 
                //    mov rdx, [registers + .rbp]
                //    guest_read rcx, [rdx]
                // 
                //    add rdx, 8
                //    mov [registers + .rsp], rdx
                //    mov [registers + .rbp], rcx
                //    
                
                emit_read_gpr(context,  host(REGISTER_D), guest(REGISTER_BP), 8, 0);
                
                emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_D), 8, /*need_write_permission*/0);
                
                emit_inst(0x83, reg(8, REG_OPCODE_add, REGISTER_D), 8);
                
                emit_write_gpr(context, guest(REGISTER_SP), host(REGISTER_D), 8, 0);
                emit_write_gpr(context, guest(REGISTER_BP), host(REGISTER_C), 8, 0);
            }break;
            
            case 0xcb:{ // retf - lets hope this is just a way to set the cs register. @cleanup: this should only read once...
                // Pop the return value.
                emit_read_gpr(context, host(REGISTER_D), guest(REGISTER_SP), 8, rex);
                emit_read_into_gpr(context, host(REGISTER_D), host(REGISTER_D), 8, /*need_write_permission*/0);
                
                // add rsp, 8
                emit_inst(0x83, regm8(8, REG_OPCODE_add, NONVOL_registers), (u8)(REGISTER_SP * 8), 8);
                
                // mov nonvol_rip, rdx
                emit_inst(0x8b, reg(8, NONVOL_rip, REGISTER_D));
                
                emit_read_gpr(context, host(REGISTER_D), guest(REGISTER_SP), 8, rex);
                emit_read_into_gpr(context, host(REGISTER_D), host(REGISTER_D), 8, /*need_write_permission*/0);
                emit_inst(0x89, regm32(2, REGISTER_D, NONVOL_registers)); emit32(offset_in_type(struct registers, cs.selector));
                
                // add rsp, 8
                emit_inst(0x83, regm8(8, REG_OPCODE_add, NONVOL_registers), (u8)(REGISTER_SP * 8), 8);
                
                is_unconditional_jump = 1;
            }break;
            
            case 0xcf:{ // IRET
                crash_assert(operand_size == 8, emit_jit_result);
                
                // IF changes, so we should check for interrupts!
                should_check_for_interrupts = 1;
                
                // Associated code that uses iretq for a far jump:
                //     mov    rdi, rsp
                //     mov    r12, desired_rip
                //     push   0x0              ; ss
                //     push   rdi              ; rsp
                //     pushfq                  ; rflags
                //     push   0x10             ; cs
                //     push   r12              ; desired rip
                //     iretq
                
                // mov rip,    [rsp + 0 * 8]
                // mov cs,     [rsp + 1 * 8]
                // mov rflags, [rsp + 2 * 8]
                // mov rsp,    [rsp + 3 * 8]
                // mov ss,     [rsp + 4 * 8]
                
                emit_read_gpr(context, host(NONVOL_flex), guest(REGISTER_SP), 8, rex);
                
                //
                // Read the two _bounds_ first (rip and ss).
                // After that, the whole range [rsp + 0, rsp + 0x20) should be readable
                // and we can stop worrying about any read crashing.
                //
                
                // load rip
                emit_read_into_gpr(context, host(REGISTER_A), host(NONVOL_flex), 8, /*need_write_permission*/0);
                
                // lea r8, [flex + 4 * 8]
                emit_inst(0x8D, regm8(8, REGISTER_R8, NONVOL_flex), 4 * 8);
                
                // mov flex, rax
                emit_inst(0x8B, reg(8, NONVOL_flex, REGISTER_A));
                
                emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_R8), 8, /*need_write_permission*/0);
                
                //
                // At this point we know that all reads should succeed.
                // Therefore, we can start writing to registers.
                //
                
                // mov nonvol_rip, flex ; rip
                emit_inst(0x89, reg(8, NONVOL_flex, NONVOL_rip));
                
                // mov word [registers + .ss], ax ; ss
                emit_inst(0x89, regm32(2, REGISTER_A, NONVOL_registers)); emit32(offset_in_type(struct registers, ss.selector));
                
                
                // Reload the stack pointer into _flex_, where it'll stay from now on.
                emit_read_gpr(context, host(NONVOL_flex), guest(REGISTER_SP), 8, rex);
                
                {
                    // lea r8, [flex + 1 * 8] ; cs
                    emit_inst(0x8D, regm8(8, REGISTER_R8, NONVOL_flex), 1 * 8);
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_R8), 8, /*need_write_permission*/0);
                    
                    // mov word [registers + .cs], ax ; cs
                    emit_inst(0x89, regm32(2, REGISTER_A, NONVOL_registers)); emit32(offset_in_type(struct registers, cs.selector));
                }
                
                {
                    // lea r8, [flex + 2 * 8] ; rflags
                    emit_inst(0x8D, regm8(8, REGISTER_R8, NONVOL_flex), 2 * 8);
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_R8), 4, /*need_write_permission*/0);
                    
                    // @cleanup: IOPL and iretq at CPL != 0 ?
                    u32 valid_flags = FLAG_CF | FLAG_PF | FLAG_AF | FLAG_ZF | FLAG_SF | FLAG_TF | FLAG_DF | FLAG_OF | FLAG_NT | FLAG_IF | FLAG_AC | FLAG_VIF | FLAG_VIP;
                    emit(0xb8 + REGISTER_C); emit32(valid_flags);
                    
                    // Compute the new values in rax and add them incrementally into [registers + .rflags]
                    //     and rax, rcx
                    //     not rcx
                    //     and qword [registers + .rflags], rcx
                    //     or  qword [registers + .rflags], rax
                    emit_inst(0x23, reg(8, REGISTER_A, REGISTER_C));
                    emit_inst(0xf7, reg(8, /*not*/2, REGISTER_C));
                    emit_inst(0x21, regm32(8, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, rflags));
                    emit_inst(0x09, regm32(8, REGISTER_A, NONVOL_registers)); emit32(offset_in_type(struct registers, rflags));
                }
                
                {
                    // lea r8, [flex + 3 * 8] ; rsp
                    emit_inst(0x8D, regm8(8, REGISTER_R8, NONVOL_flex), 3 * 8);
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_R8), 8, /*need_write_permission*/0);
                    
                    // mov qword [registers + .rsp], rax ; rsp
                    emit_inst(0x89, regm8(8, REGISTER_A, NONVOL_registers), offset_in_type(struct registers, rsp));
                }
                
                is_unconditional_jump = 1;
            }break;
            
            case 0xC6:  // mov regm8, imm8
            case 0xC7:{ // mov regm,  imm
                crash_assert(reg.encoding == 0, emit_jit_result);
                
                if(opcode == 0xC6) operand_size = 1;
                
                // mov rcx, imm
                emit_inst(opcode, reg(operand_size, /*mov*/0, REGISTER_C)); emit_bytes(context, (u8 *)&immediate, immediate_size);
                
                if(mod == MOD_REG){
                    emit_write_gpr(context, regm, host(REGISTER_C), operand_size, rex);
                }else{
                    emit_write_host_register(context, host(REGISTER_A), host(REGISTER_C), operand_size);
                }
            }break;
            
            // int3
            // int cb
            case 0xCC: case 0xCD:{
                
                u32 vector = (opcode == 0xcc) ? 3 : (u8)immediate;
                
                // 
                // helper_interrupt_instruction(context, vector);
                // 
                
                // move past the instruction and save of the nonvol_rip.
                //     add nonvol_rip, instruction_size
                //     mov [registers + .rip], nonvol_rip
                emit_inst(0x83, reg(8, REG_OPCODE_add, NONVOL_rip), (u8)instruction_size);
                emit_inst(0x89, regm32(8, NONVOL_rip, NONVOL_registers)); emit32(offset_in_type(struct registers, rip));
                
                emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                emit_inst(0xC7, reg(8, /*mov*/0, ARG_REG_2)); emit32(vector); // :linux_refactor
                emit(0x48, 0xB8); emit64((u64)helper_interrupt_instruction);
                emit(0xff, make_modrm(MOD_REG, /*call*/2, REGISTER_A));
                
                // @note: we have to reload the non-volatile rip, as the helper has changed it.
                //     mov nonvol_rip, [registers + .rip]
                emit_inst(0x8b, regm32(8, NONVOL_rip, NONVOL_registers)); emit32(offset_in_type(struct registers, rip));
                
                is_unconditional_jump = 1;
            }break;
            
            // xxx = { rol, ror, rcl, rcr, shl, shr, sal, sar }
            case 0xD0:  // xxx regm8, 1
            case 0xD1:{ // xxx regm, 1
                if(opcode == 0xD0) operand_size = 1;
                
                if(mod == MOD_REG){
                    emit_load_flags(context); // These have some unaffected flags!
                    
                    // xxx size ptr[registers + .regm], 1
                    emit_inst(opcode, regm8(operand_size, reg.encoding, NONVOL_registers), reg_offset(regm, operand_size, rex));
                    emit_destructively_update_flags(context, host(REGISTER_D));
                    
                    if(operand_size == 4){
                        // mov dword ptr[registers + .regm + 4], 0
                        emit_inst(0xC7, regm8(4, 0, NONVOL_registers), (u8)(8 * regm.encoding + 4), 0x00, 0x00, 0x00, 0x00);
                    }
                }else{
                    // mov flex, rax ; address
                    emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                    
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), operand_size, /*need_write_permission*/1);
                    
                    emit_load_flags(context); // These have some unaffected flags!
                    
                    // xxx size ptr rax, 1
                    emit_inst(opcode, reg(operand_size, reg.encoding, REGISTER_A));
                    emit_destructively_update_flags(context, host(REGISTER_D));
                    
                    emit_write_host_register(context, host(NONVOL_flex), host(REGISTER_A), operand_size);
                }
            }break;
            
            // xxx = { rol, ror, rcl, rcr, shl, shr, sal, sar }
            case 0xD2:  // xxx regm8, cl
            case 0xD3:{ // xxx regm, cl
                if(opcode == 0xD2) operand_size = 1;
                
                if(mod == MOD_REG){
                    
                    emit_read_gpr(context, host(REGISTER_C), guest(REGISTER_C), 4, 0);
                    emit_load_flags(context); // These have some unaffected flags!
                    
                    // xxx size ptr[registers + .regm], cl
                    emit_inst(opcode, regm8(operand_size, reg.encoding, NONVOL_registers), reg_offset(regm, operand_size, rex));
                    emit_destructively_update_flags(context, host(REGISTER_D));
                    
                    if(operand_size == 4){
                        // mov dword ptr[registers + .regm + 4], 0
                        emit_inst(0xC7, regm8(4, 0, NONVOL_registers), (u8)(8 * regm.encoding + 4), 0x00, 0x00, 0x00, 0x00);
                    }
                }else{
                    // mov flex, rax ; address
                    emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                    
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), operand_size, /*need_write_permission*/1);
                    
                    emit_read_gpr(context, host(REGISTER_C), guest(REGISTER_C), 4, 0);
                    emit_load_flags(context); // These have some unaffected flags!
                    
                    // xxx size ptr rax, cl
                    emit_inst(opcode, reg(operand_size, reg.encoding, REGISTER_A));
                    emit_destructively_update_flags(context, host(REGISTER_D));
                    
                    emit_write_host_register(context, host(NONVOL_flex), host(REGISTER_A), operand_size);
                }
            }break;
            
            case 0xd8:{
                if(mod == MOD_REG){ // :linux_refactor
                    // D8 /0 fadd  ST(0), ST(i)
                    // D8 /1 fmul  ST(0), ST(i)
                    // D8 /2 fcom  ST(0), ST(i)
                    // D8 /3 fcomp ST(0), ST(i)
                    // D8 /4 fsub  ST(0), ST(i)
                    // D8 /5 fsubr ST(0), ST(i)
                    // D8 /6 fdiv  ST(0), ST(i) - Divide ST(0) by ST(i) and store result in ST(0).
                    // D8 /7 fdivr ST(0), ST(i) - Divide ST(i) by ST(0) and store result in ST(0).
                    
                    // 
                    // Get the current TOP (in the low 3 bits).
                    //     movzx ecx, [registers + .fpu_status_word]
                    //     mov edx, ecx
                    //     shr ecx, 11
                    //     and ecx, 7
                    emit(0x0f, 0xb7, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_status_word));
                    emit(0x8b, make_modrm(MOD_REG, REGISTER_D, REGISTER_C));
                    emit(0xC1, make_modrm(MOD_REG, /*shr*/5, REGISTER_C), 11);
                    emit(0x83, make_modrm(MOD_REG, REG_OPCODE_and, REGISTER_C), 7);
                    
                    // Save off the index of the guest `ST(0)`.
                    //     lea edx, [2 * ecx]
                    emit(0x8d, make_modrm(MOD_REGM, REGISTER_D, REGISTER_SP), make_sib(0, REGISTER_C, REGISTER_C));
                    
                    // Add `i` to TOP to get the index of `ST(i)`.
                    //     add ecx, i
                    //     and ecx, 7
                    emit(0x83, make_modrm(MOD_REG, REG_OPCODE_add, REGISTER_C), (u8)regm.encoding);
                    emit(0x83, make_modrm(MOD_REG, REG_OPCODE_and, REGISTER_C), 7);
                    
                    // fld guest `ST(i)` into host `ST(0)` (soon to be `ST(1)`)
                    //     lea ecx, [2 * ecx]
                    //     fld [registers + .st + ecx * 8]
                    emit(0x8d, make_modrm(MOD_REGM, REGISTER_C, REGISTER_SP), make_sib(0, REGISTER_C, REGISTER_C));
                    emit(0xdb, make_modrm(MOD_REGM_OFF32, /*fld*/8, REGISTER_SP), make_sib(/*log2(8)*/3, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_st));
                    
                    // fld guest `ST(0)` into host `ST(0)`
                    //     fld [registers + .st + edx * 8]
                    emit(0xdb, make_modrm(MOD_REGM_OFF32, /*fld*/8, REGISTER_SP), make_sib(/*log2(8)*/3, REGISTER_D, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_st));
                    
                    // Guest ST(0) = Host ST(0)
                    // Guest ST(i) = Host ST(1)
                    // Execute the instruction, it will save the result to the host `ST(0)`.
                    emit(0xd8, make_modrm(MOD_REG, reg.encoding, /*ST*/1));
                    
                    // Store the result in the guest ST(0):
                    //     fstp [registers + .st + edx * 8] ; edx is still loaded from the above.
                    emit(0xdb, make_modrm(MOD_REGM_OFF32, /*fld*/7, REGISTER_SP), make_sib(/*log2(8)*/3, REGISTER_D, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_st));
                    
                    // "Free `ST(1)`" I.e.: pop the top of the stack which was the other operand.
                    //     fstp ST(0)
                    emit(0xDD, 0xD8);
                }else{
                    // D8 /0 fadd  m32fp
                    // D8 /1 fmul  m32fp
                    // D8 /2 fcom  m32fp
                    // D8 /3 fcomp m32fp
                    // D8 /4 fsub  m32fp
                    // D8 /5 fsubr m32fp
                    // D8 /6 fdiv  m32fp - Divide ST(0) by m32fp and store result in ST(0).
                    // D8 /7 fdivr m32fp - Divide m32fp by ST(0) and store result in ST(0).
                    
                    emit_read_into_temp_buffer_and_return_pointer_in_rax(context, host(REGISTER_A), 4, /*need_write_permission*/0);
                    
                    // 
                    // Get the current TOP (in the low 3 bits).
                    //     movzx ecx, [registers + .fpu_status_word]
                    //     mov edx, ecx
                    //     shr ecx, 11
                    //     and ecx, 7
                    emit(0x0f, 0xb7, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_status_word));
                    emit(0x8b, make_modrm(MOD_REG, REGISTER_D, REGISTER_C));
                    emit(0xC1, make_modrm(MOD_REG, /*shr*/5, REGISTER_C), 11);
                    emit(0x83, make_modrm(MOD_REG, REG_OPCODE_and, REGISTER_C), 7);
                    
                    // fld guest `ST(0)` into host `ST(0)`
                    //     lea edx, [2 * ecx]
                    //     fld [registers + .st + edx * 8]
                    emit(0x8d, make_modrm(MOD_REGM, REGISTER_D, REGISTER_SP), make_sib(0, REGISTER_C, REGISTER_C));
                    emit(0xdb, make_modrm(MOD_REGM_OFF32, /*fld*/8, REGISTER_SP), make_sib(/*log2(8)*/3, REGISTER_D, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_st));
                    
                    // 
                    // Perform the operation
                    //     op [rax]
                    emit(0xd8, make_modrm(MOD_REGM, reg.encoding, REGISTER_A));
                    
                    // Store the result in the guest ST(0):
                    //     fstp [registers + .st + edx * 8] ; edx is still loaded from the above.
                    emit(0xdb, make_modrm(MOD_REGM_OFF32, /*fld*/7, REGISTER_SP), make_sib(/*log2(8)*/3, REGISTER_D, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_st));
                }
            }break;
            
            case 0xd9:{ 
                
                if(mod == MOD_REG){
                    
                    switch(reg.encoding){// :linux_refactor
                        case 0:{ // fld ST(i) - Push ST(i) onto the FPU register stack.
                            // Get the current TOP (in the low 3 bits).
                            //     movzx ecx, [registers + .fpu_status_word]
                            //     mov edx, ecx
                            //     shr ecx, 11
                            emit(0x0f, 0xb7, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_status_word));
                            emit(0x8b, make_modrm(MOD_REG, REGISTER_D, REGISTER_C));
                            emit(0xC1, make_modrm(MOD_REG, /*shr*/5, REGISTER_C), 11);
                            
                            // Add `i` to TOP to get the index of `ST(i)`.
                            //     add ecx, i
                            //     and ecx, 7
                            emit(0x83, make_modrm(MOD_REG, REG_OPCODE_add, REGISTER_C), (u8)regm.encoding);
                            emit(0x83, make_modrm(MOD_REG, REG_OPCODE_and, REGISTER_C), 7);
                            
                            // fld guest `ST(i)` into host `ST(0)`.
                            //     lea edx, [2 * ecx]
                            //     fld [registers + .st + edx * 8]
                            emit(0x8d, make_modrm(MOD_REGM, REGISTER_D, REGISTER_SP), make_sib(0, REGISTER_C, REGISTER_C));
                            emit(0xdb, make_modrm(MOD_REGM_OFF32, /*fld*/8, REGISTER_SP), make_sib(/*log2(8)*/3, REGISTER_D, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_st));
                            
                            // Push the loaded value from the host `ST(0)` onto guest ST-stack.
                            emit_push_pop_fpu_stack(context, /*is_push*/1);
                        }break;
                        
                        case 3:{ // fstp ST(i) - Copy ST(0) to ST(i) and pop register stack.
                            
                            // Pop the guest `ST(0)` into the host `ST(0)`.
                            emit_push_pop_fpu_stack(context, /*is_push*/0);
                            
                            // Get the current TOP (in the low 3 bits).
                            //     movzx ecx, [registers + .fpu_status_word]
                            //     mov edx, ecx
                            //     shr ecx, 11
                            emit(0x0f, 0xb7, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_status_word));
                            emit(0x8b, make_modrm(MOD_REG, REGISTER_D, REGISTER_C));
                            emit(0xC1, make_modrm(MOD_REG, /*shr*/5, REGISTER_C), 11);
                            
                            // Add `i-1` to TOP to get the index of `ST(i-1)` which is `ST(i)` after poping `ST(0)`.
                            //     add ecx, i
                            //     and ecx, 7
                            emit(0x83, make_modrm(MOD_REG, REG_OPCODE_add, REGISTER_C), (u8)(regm.encoding - 1));
                            emit(0x83, make_modrm(MOD_REG, REG_OPCODE_and, REGISTER_C), 7);
                            
                            // Store the host `ST(0)` into the guest `ST(i-1)`.
                            emit(0xdb, make_modrm(MOD_REGM_OFF32, /*fstp*/7, REGISTER_SP), make_sib(/*log2(8)*/3, REGISTER_D, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_st));
                            emit(0x8d, make_modrm(MOD_REGM, REGISTER_D, REGISTER_SP), make_sib(0, REGISTER_C, REGISTER_C));
                        }break;
                        
                        case 6:{
                            if(regm.encoding == 7){
                                
                                // @copy_and_paste from `emit_push_pop_fpu_stack`.
                                
                                // Get and decrement the top of the stack.
                                //     movzx ecx, [registers + .fpu_status_word]
                                //     mov edx, ecx
                                //     shr ecx, 11
                                // inc/dec ecx
                                //     and ecx, 7
                                emit(0x0f, 0xb7, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_status_word));
                                emit(0x8b, make_modrm(MOD_REG, REGISTER_D, REGISTER_C));
                                emit(0xC1, make_modrm(MOD_REG, /*shr*/5, REGISTER_C), 11);
                                
                                emit(0xff, make_modrm(MOD_REG, 0, REGISTER_C));
                                emit(0x83, make_modrm(MOD_REG, REG_OPCODE_and, REGISTER_C), 7);
                                
                                // Adjust the top of the stack.
                                //     and edx, ~(7 << 11)
                                //     shl ecx, 11
                                //     or edx, ecx
                                //     mov [registers + .fpu_status_word], edx
                                emit(0x81, make_modrm(MOD_REG, REG_OPCODE_and, REGISTER_D)); emit32((u32)(~(7 << 11)));
                                emit(0xC1, make_modrm(MOD_REG, /*shl*/4, REGISTER_C), 11);
                                emit(0x0b, make_modrm(MOD_REG, REGISTER_D, REGISTER_C));
                                emit(0x66, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_D, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_status_word));
                            }else{
                                crash_assert("deep in the weeds of d9", emit_jit_result);
                            }
                        }break;
                        
                        crash_invalid_default_case("d9 reg", emit_jit_result);
                    }
                }else{
                    switch(reg.encoding){
                        
                        case 0:{ // fld [80-bit-float]
                            emit_read_into_temp_buffer_and_return_pointer_in_rax(context, host(REGISTER_A), /*size*/4, /*need_write_permission*/0);
                            
                            // Store the loaded value into the new ST(0)
                            //     op [rax]
                            emit(opcode, make_modrm(MOD_REGM, reg.encoding, REGISTER_A));
                            
                            // Push the loaded value from the host `ST(0)` onto guest ST-stack.
                            emit_push_pop_fpu_stack(context, /*is_push*/1);
                        }break;
                        
                        case 3:{
                            // Pop the value from the guest `ST(0)` onto host ST-stack.
                            emit_push_pop_fpu_stack(context, /*is_push*/0);
                            
                            // lea rdx, [context + .jit_scratch]
                            emit(0x48, 0x8D, make_modrm(MOD_REGM_OFF32, REGISTER_D, NONVOL_context)); emit32(offset_in_type(struct context, jit_scratch));
                            
                            // fstp [rdx]
                            emit(opcode, make_modrm(MOD_REGM, reg.encoding, REGISTER_D));
                            
                            emit_write_pointer(context, host(REGISTER_A), host(REGISTER_D), 16);
                        }break;
                        
                        case 4:{ // FNLDENV 
                            // mov arg1, context
                            // mov arg2, registers
                            // mov arg3, rax (address)
                            // call FNSTENV_helper
                            emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                            emit_inst(0x8b, reg(8, ARG_REG_2, NONVOL_registers));
                            emit_inst(0x8b, reg(8, ARG_REG_3, REGISTER_A));
                            
                            emit_call_to_helper(context, FLDENV_helper, HELPER_might_crash);
                            
                            // fldcw [registers + .fpucw]
                            emit(0xd9, make_modrm(MOD_REGM_OFF32, /*FLDCW*/5, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_control_word));
                        }break;
                        
                        case 5:{ // FLDCW - Load x87 FPU Control Word
                            emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), 2, 0);
                            
                            emit(0x66, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_control_word));
                            
                            // fldcw [registers + .fpucw]
                            emit(0xd9, make_modrm(MOD_REGM_OFF32, /*FLDCW*/5, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_control_word));
                        }break;
                        
                        case 6:{ // FNSTENV 
                            // mov arg1, context
                            // mov arg2, registers
                            // mov arg3, rax
                            // call FNSTENV_helper
                            emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                            emit_inst(0x8b, reg(8, ARG_REG_2, NONVOL_registers));
                            emit_inst(0x8b, reg(8, ARG_REG_3, REGISTER_A));
                            
                            emit_call_to_helper(context, FNSTENV_helper, HELPER_might_crash);
                        }break;
                        
                        case 7:{ // FSTCW - Store x87 FPU Control Word
                            emit(0x8b, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_control_word));
                            
                            emit_write_host_register(context, host(REGISTER_A), host(REGISTER_C), 2);
                        }break;
                        
                        crash_invalid_default_case("d9 regm", emit_jit_result);
                    }
                }
            }break;
            
            case 0xDB:{
                switch(modrm){
                    
                    case 0xe2:{ // FNCLEX 
                        // mov word ptr[registers + .fpu_status_word], 0
                        emit(0x66, 0xC7, make_modrm(MOD_REGM_OFF32, 0, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_status_word)); emit16(0);
                    }break;
                    
                    case 0xe3:{ // FNINIT
                        emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_registers));
                        emit_call_to_helper(context, FNINIT_helper, HELPER_simple_call);
                    }break;
                    
                    default:{
                        switch(reg.encoding){
                            case 5:  // FLD  [m80fp]  - F load.
                            case 0:{ // FILD [m32int] - F integer Load.
                                crash_assert(mod == MOD_REGM, emit_jit_result);
                                
                                emit_read_into_temp_buffer_and_return_pointer_in_rax(context, host(REGISTER_A), /*size*/4, /*need_write_permission*/0);
                                
                                // Perform the operation into the host `ST(0)`.
                                //     op [rax]
                                emit(0xdb, make_modrm(MOD_REGM, reg.encoding, REGISTER_A));
                                
                                // Push the loaded value from the host `ST(0)` onto guest ST-stack.
                                emit_push_pop_fpu_stack(context, /*is_push*/1);
                            }break;
                            
                            case 7:{ // FSTP [m80fp] - F store pop
                                // Pop the value from the guest `ST(0)` onto host ST-stack.
                                emit_push_pop_fpu_stack(context, /*is_push*/0);
                                
                                // lea rdx, [context + .jit_scratch]
                                emit(0x48, 0x8D, make_modrm(MOD_REGM_OFF32, REGISTER_D, NONVOL_context)); emit32(offset_in_type(struct context, jit_scratch));
                                
                                // fstp [rdx]
                                emit(opcode, make_modrm(MOD_REGM, reg.encoding, REGISTER_D));
                                
                                emit_write_pointer(context, host(REGISTER_A), host(REGISTER_D), 16);
                            }break;
                            
                            crash_invalid_default_case("db", emit_jit_result);
                        }
                    }break;
                }
            }break;
            
            case 0xdd:{
                if(mod == MOD_REG){
                    switch(reg.encoding){
                        case 0:{ // FFREE
                            // "Sets the tag for the register to empty (11B). Contents and TOP are not affected."
                            
                            // I guess we ignore this for now...
                            
                        }break;
                        crash_invalid_default_case("dd", emit_jit_result);
                    }
                }else{
                    switch(reg.encoding){
                        case 0:{ // FLD [m64real]
                            emit_read_into_temp_buffer_and_return_pointer_in_rax(context, host(REGISTER_A), /*size*/4, /*need_write_permission*/0);
                            
                            // Store the loaded value into the host `ST(0)`
                            //     op [rax]
                            emit(opcode, make_modrm(MOD_REGM, reg.encoding, REGISTER_A));
                            
                            // Push the loaded value from the host `ST(0)` onto guest ST-stack.
                            emit_push_pop_fpu_stack(context, /*is_push*/1);
                        }break;
                        
                        case 3:{ // FSTP [m64fp] - F store pop
                            // Pop the value from the guest `ST(0)` onto host ST-stack.
                            emit_push_pop_fpu_stack(context, /*is_push*/0);
                            
                            // lea rdx, [context + .jit_scratch]
                            emit(0x48, 0x8D, make_modrm(MOD_REGM_OFF32, REGISTER_D, NONVOL_context)); emit32(offset_in_type(struct context, jit_scratch));
                            
                            // fstp [rdx]
                            emit(opcode, make_modrm(MOD_REGM, reg.encoding, REGISTER_D));
                            
                            emit_write_pointer(context, host(REGISTER_A), host(REGISTER_D), 16);
                        }break;
                        
                        case 6:{ // FNSAVE mem
                            
                            // call the helper routine:
                            //     mov arg1, context
                            //     mov arg2, registers
                            //     mov arg3, rax (guest_address)
                            //     call fnsave_helper
                            emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                            emit_inst(0x8b, reg(8, ARG_REG_2, NONVOL_registers));
                            emit_inst(0x8b, reg(8, ARG_REG_3, REGISTER_A));
                            
                            emit_call_to_helper(context, fnsave_helper, HELPER_might_crash);
                        }break;
                        crash_invalid_default_case("dd", emit_jit_result);
                    }
                }
            }break;
            
            case 0xdf:{
                if(mod == MOD_REG){
                    if(modrm == 0xE0){ // FNSTSW AX
                        emit(0x8b, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_control_word));
                        emit_write_gpr(context, guest(REGISTER_A), host(REGISTER_C), 2, 0);
                    }else{
                        crash_assert(false, emit_jit_result);
                    }
                }else{
                    switch(reg.encoding){
                        case 0:{ // FLD [m16int]
                            emit_read_into_temp_buffer_and_return_pointer_in_rax(context, host(REGISTER_A), /*size*/4, /*need_write_permission*/0);
                            
                            // Store the loaded value into the host `ST(0)`
                            //     op [rax]
                            emit(opcode, make_modrm(MOD_REGM, reg.encoding, REGISTER_A));
                            
                            // Push the loaded value from the host `ST(0)` onto guest ST-stack.
                            emit_push_pop_fpu_stack(context, /*is_push*/1);
                        }break;
                        crash_invalid_default_case("df", emit_jit_result);
                    }
                }
            }break;
            
            
            case 0xE2:{ // LOOP - Decrement count; jump short if count != 0
                
                // mov rcx, [registers + .rcx]
                // dec rcx
                // jz failure
                emit_read_gpr(context, host(REGISTER_C), guest(REGISTER_C), 8, 0);
                emit(0x48, 0xFF, 0xC9); 
                emit_write_gpr(context, guest(REGISTER_C), host(REGISTER_C), 8, 0);
                
                emit(0x74); jump_patch = emit_get_current(context); emit(0);
                {
                    // mov rcx, nonvol_rip
                    emit(0x48 | REXB, 0x8b, make_modrm(MOD_REG, REGISTER_C, NONVOL_rip));
                    
                    s32 disp = instruction_size + (s32)imm8;
                    conditional_branch_rip = instruction_rip + disp;
                    
                    // add rcx, disp + instruction_size
                    emit(0x48, 0x81, make_modrm(MOD_REG, REG_OPCODE_add, REGISTER_C));
                    emit32(disp);
                    
                    // @cleanup: Maybe there are two unnecessary instructions here.
                    // mov nonvol_rip, rcx
                    emit(0x48 | REXR, 0x8b, make_modrm(MOD_REG, NONVOL_rip, REGISTER_C));
                    
                }
                
                //
                // @note: Just use the usual next_instruction path to perform the jump.
                //
            }break;
            
            case 0xE8:{ // call rel32
                
                {
                    //
                    // Compute the next rip in 'rax'.
                    //
                    
                    // @cleanup: These three instructions could now be done in one!
                    
                    // mov rax, nonvol_rip
                    emit(0x48 | REXB, 0x8b, make_modrm(MOD_REG, REGISTER_A, NONVOL_rip));
                    
                    // add rax, instruction_size
                    emit(0x48, 0x83, make_modrm(MOD_REG, REG_OPCODE_add, REGISTER_A), (u8)instruction_size);
                    
                    // Save the current rip in the flex register.
                    //      mov flex, rax
                    emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                }
                
                // Push the return address to the stack.
                emit_read_gpr(context, host(REGISTER_R8), guest(REGISTER_SP), 8, 0);
                
                // sub r8, 8
                emit(0x49, 0x83, 0xE8, 0x08);
                
                // Store 'rip' on the stack.
                emit_write_host_register(context, host(REGISTER_R8), host(REGISTER_A), 8);
                
                // If the write succeeded commit the allocation of 8 bytes.
                emit(0x48, 0x83, make_modrm(MOD_REGM_OFF8, REG_OPCODE_sub, NONVOL_registers), (u8)(REGISTER_SP * 8), 0x08);
                
                // Compute the call address and save it to rip.
                //     add flex, rel32
                //     mov nonvol_rip, flex
                emit_inst(0x81, reg(8, REG_OPCODE_add, NONVOL_flex)); emit32((s32)immediate);
                emit_inst(0x8b, reg(8, NONVOL_rip, NONVOL_flex));
                
                is_unconditional_jump = 1;
            }break;
            
            case 0xE9:  // jmp rel32
            case 0xEB:{ // jmp rel8
                
                u64 next_instruction;
                
                if(opcode == 0xEB){
                    s32 disp = instruction_size + (s32)imm8;
                    
                    next_instruction = instruction_rip + disp;
                    
                    // add nonvol_rip, disp + instruction_size
                    emit(0x48 | REXB, 0x81, make_modrm(MOD_REG, REG_OPCODE_add, NONVOL_rip)); emit32(disp);
                }else{
                    
                    // add nonvol_rip, instruction_size
                    emit(0x48 | REXB, 0x83, make_modrm(MOD_REG, REG_OPCODE_add, NONVOL_rip), (u8)instruction_size);
                    
                    // add nonvol_rip, disp + instruction_size
                    emit(0x48 | REXB, 0x81, make_modrm(MOD_REG, REG_OPCODE_add, NONVOL_rip)); emit32((s32)immediate);
                    
                    next_instruction = instruction_rip + (s32)immediate + (u64)instruction_size;
                }
                
                if((instruction_rip & ~0xfff) == (next_instruction & ~0xfff)){
                    emit_patchable_jit_exit_for_jump_within_page(context, 0, BRANCH_unconditional);
                    skip_jit_exit = 1;
                }
                
                is_unconditional_jump = 1;
            }break;
            
            case 0xe4:  // IN al,  imm8 - read from port imm8 into al.
            case 0xe5:{ // IN eax, imm8 - read from port imm8 into eax.
                
                if(opcode == 0xe4) operand_size = 1;
                // mov arg1, context
                // mov arg2, registers
                // mov arg3, imm8
                // mov arg4, operand_size
                // call read_from_port_helper
                
                emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                emit_inst(0x8b, reg(8, ARG_REG_2, NONVOL_registers));
                emit_inst(0xC7, reg(8, 0, ARG_REG_3)); emit32(imm8);
                emit_inst(0xC7, reg(8, 0, ARG_REG_4)); emit32(operand_size);
                
                emit_call_to_helper(context, read_from_port_helper, HELPER_might_crash);
            }break;
            
            case 0xe6:  // OUT imm8, al  - write al  to port imm8.
            case 0xe7:{ // OUT imm8, eax - write eax to port imm8.
                
                if(opcode == 0xe6) operand_size = 1;
                // mov arg1, context
                // mov arg2, registers
                // mov arg3, imm8
                // mov arg4, value
                // call write_to_port_helper
                
                emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                emit_inst(0x8b, reg(8, ARG_REG_2, NONVOL_registers));
                emit_inst(0xC7, reg(8, 0, ARG_REG_3)); emit32(imm8);
                emit_read_gpr(context, host(REGISTER_R9), guest(REGISTER_A), operand_size, 0x48 | REXB);
                
                emit_call_to_helper(context, write_to_port_helper, HELPER_might_crash);
            }break;
            
            case 0xec:  // IN al,  dx - read from port dx into al.
            case 0xed:{ // IN eax, dx - read from port dx into eax.
                
                if(opcode == 0xec) operand_size = 1;
                // mov arg1, context
                // mov arg2, registers
                // mov arg3, guest_dx
                // mov arg4, operand_size
                // call read_from_port_helper
                
                emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                emit_inst(0x8b, reg(8, ARG_REG_2, NONVOL_registers));
                emit_read_gpr(context, host(ARG_REG_3), guest(REGISTER_D), 2, 0);
                emit_inst(0xC7, reg(8, 0, ARG_REG_4)); emit32(operand_size);
                
                emit_call_to_helper(context, read_from_port_helper, HELPER_might_crash);
            }break;
            
            case 0xee:  // OUT dx, al  - write al  to port dx.
            case 0xef:{ // OUT dx, eax - write eax to port dx.    
                
                if(opcode == 0xee) operand_size = 1;
                // mov arg1, context
                // mov arg2, registers
                // mov arg3, guest_dx
                // mov arg4, value
                // call write_to_port_helper
                
                emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                emit_inst(0x8b, reg(8, ARG_REG_2, NONVOL_registers));
                emit_read_gpr(context, host(ARG_REG_3), guest(REGISTER_D), 2, 0);
                emit_read_gpr(context, host(ARG_REG_4), guest(REGISTER_A), operand_size, 0x48 | REXB);
                
                emit_call_to_helper(context, write_to_port_helper, HELPER_might_crash);
            }break;
            
            case 0xf4:{ // hlt
                emit_inst(0x8B, reg(8, ARG_REG_1, NONVOL_context));
                emit_inst(0x8B, reg(8, ARG_REG_2, NONVOL_registers));
                emit_call_to_helper(context, helper_immediately_pend_timer_interrupt, HELPER_cares_about_rip | HELPER_might_change_rip | HELPER_might_crash);
                should_check_for_interrupts = 1;
            }break;
            
            case 0xf5:{ // cmc
                // xor byte [registers + .rflags], CF
                emit(0x80, make_modrm(MOD_REGM_OFF32, REG_OPCODE_xor, NONVOL_registers));
                emit32(offset_in_type(struct registers, rflags));
                emit(0x01);
            }break;
            
            
            case 0xF6: case 0xF7:{
                if(opcode == 0xf6) operand_size = 1;
                
                switch(reg.encoding){
                    case 0: case 1:{ // test regm8, imm8 / test regm, imm
                        
                        if(mod == MOD_REG){
                            emit_read_gpr(context, host(REGISTER_C), regm, operand_size, rex);
                        }else{
                            emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), operand_size, /*need_write_permission*/0);
                        }
                        
                        // test rcx, imm
                        if(operand_size == 2) emit(0x66);
                        if(operand_size == 8) emit(0x48);
                        emit(opcode, make_modrm(MOD_REG, reg.encoding, REGISTER_C)); emit_bytes(context, (u8 *)&immediate, immediate_size);
                        
                        emit_destructively_update_flags(context, host(REGISTER_D));
                    }break;
                    case 3:  // neg regm8 / neg regm
                    case 2:{ // not regm8 / not regm
                        if(mod == MOD_REG){
                            // not/neg size ptr[registers + .regm]
                            if(operand_size == 2) emit(0x66);
                            if(operand_size == 8) emit(0x48);
                            emit(opcode, make_modrm(MOD_REGM_OFF8, reg.encoding, NONVOL_registers), reg_offset(regm, operand_size, rex));
                            if(reg.encoding == 3) emit_destructively_update_flags(context, host(REGISTER_D)); // neg changes flags, not does not.
                            
                            if(operand_size == 4){
                                // mov dword ptr[registers + .regm + 4], 0
                                emit(0xC7, make_modrm(MOD_REGM_OFF8, 0, NONVOL_registers), (u8)(8 * regm.encoding + 4), 0x00, 0x00, 0x00, 0x00);
                            }
                        }else{
                            // mov flex, rax ; address
                            emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                            
                            emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), operand_size, /*need_write_permission*/1);
                            
                            // not/neg size ptr rax
                            if(operand_size == 2) emit(0x66);
                            if(operand_size == 8) emit(0x48);
                            emit(opcode, make_modrm(MOD_REG, reg.encoding, REGISTER_A));
                            if(reg.encoding == 3) emit_destructively_update_flags(context, host(REGISTER_D)); // neg changes flags, not does not.
                            
                            emit_write_host_register(context, host(NONVOL_flex), host(REGISTER_A), operand_size);
                        }
                    }break;
                    case 4:  // MUL  rdx, rax, regm
                    case 5:{ // IMUL rdx, rax, regm
                        if(mod == MOD_REG){
                            emit_read_gpr(context, host(REGISTER_C), regm, operand_size, rex);
                        }else{
                            emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), operand_size, /*need_write_permission*/0);
                        }
                        emit_read_gpr(context, host(REGISTER_A), guest(REGISTER_A), operand_size, rex);
                        
                        // op rdx, rax, rcx
                        if(operand_size == 2) emit(0x66);
                        if(operand_size == 8) emit(0x48);
                        emit(opcode, make_modrm(MOD_REG, reg.encoding, REGISTER_C));
                        
                        // 
                        // MUL and IMUL set the flags.
                        // 
                        emit_destructively_update_flags(context, host(REGISTER_R9));
                        
                        if(operand_size != 1){
                            //
                            // Save the two out registers.
                            //
                            emit_write_gpr(context, guest(REGISTER_D), host(REGISTER_D), operand_size, rex);
                            emit_write_gpr(context, guest(REGISTER_A), host(REGISTER_A), operand_size, rex);
                        }else{
                            // For one byte multiplies its: AX:= AL * r/m byte.
                            emit_write_gpr(context, guest(REGISTER_A), host(REGISTER_A), 2, rex);
                        }
                    }break;
                    
                    case 6:  // DIV  rdx, rax, regm
                    case 7:{ // IDIV rdx, rax, regm
                        
                        if(mod == MOD_REG){
                            emit_read_gpr(context, host(REGISTER_C), regm, operand_size, rex);
                        }else{
                            emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), operand_size, /*need_write_permission*/0);
                        }
                        
                        // 
                        // Checking for Divide Error (#DE) exceptions:
                        // 
                        //    test rcx, rcx
                        //    jz fail
                        //    
                        emit(0x48, 0x85, make_modrm(MOD_REG, REGISTER_C, REGISTER_C));
                        emit(0x74); u8 *patch_fail_zero = emit_get_current(context); emit(0);
                        
                        if(operand_size == 1 && reg.encoding == /*div*/6){
                            // Unsigned divide AX by r/m8, with result stored in AL := Quotient, AH := Remainder.
                            
                            emit_read_gpr(context, host(REGISTER_A), guest(REGISTER_A), 2, 0);
                            
                            // Check for unsigned overflow, we have:
                            // 
                            //       ax / src >= 0x100
                            //   <=> ax >= src * 0x100
                            //   <=> ah >= src
                            //      
                            //    cmp ah, cl
                            //    jae fail
                            emit(0x38, 0xcc);
                            emit(0x73); u8 *patch_fail_overflow = emit_get_current(context); emit(0);
                            
                            // op ax, cl
                            emit(opcode, make_modrm(MOD_REG, /*div*/6, REGISTER_C)); // @note: Always perform a div, not an idiv.
                            
                            emit(0xeb); u8 *patch_jump_success = emit_get_current(context); emit(0);
                            {
                                // On failiure exit the jit after setting context->crash to 'CRASH_divide'.
                                //    mov [context + .crash], CRASH_divide
                                //    jmp context->jit_exit
                                *patch_fail_zero     = (u8)(emit_get_current(context) - (patch_fail_zero + 1));
                                *patch_fail_overflow = (u8)(emit_get_current(context) - (patch_fail_overflow + 1));
                                
                                
                                emit(0xC7, make_modrm(MOD_REGM_OFF32, 0, NONVOL_context)); emit32(offset_in_type(struct context, crash)); emit32(CRASH_divide);
                                u32 patch = (s32)(context->jit_exit - (emit_get_current(context) + 5));
                                emit(0xe9);  emit32(patch);
                            }
                            *patch_jump_success = (u8)(emit_get_current(context) - (patch_jump_success + 1));
                            
                            emit_write_gpr(context, guest(REGISTER_A), host(REGISTER_A), 2, 0);
                            break;
                        }
                        
                        // @incomplete: idiv for operand size 1.
                        crash_assert(operand_size != 1, emit_jit_result);
                        
                        emit_read_gpr(context, host(REGISTER_A), guest(REGISTER_A), operand_size, rex);
                        emit_read_gpr(context, host(REGISTER_D), guest(REGISTER_D), operand_size, rex);
                        
                        if(reg.encoding == /*idiv*/7){
                            // We implement idiv by performing a div after taking absolute values:
                            // 
                            // Save original values
                            //     mov r8, rcx
                            //     mov r9, rdx
                            // 
                            // We already have the sign bit of rcx in SF
                            //     jns rcx_unsigned
                            //     neg rcx
                            //     
                            // rcx_unsigned:
                            // 
                            // Check if rdx is negative:
                            //     test rdx, rdx
                            //     jns rdx_unsigned
                            //     
                            // rdx_signed:
                            //     not rdx
                            //     not rax
                            //     add rax, 1
                            //     adc rdx, 0
                            // 
                            // rdx_unsigned:
                            
                            emit(0x48 | REXR, 0x8b, make_modrm(MOD_REG, REGISTER_R8, REGISTER_C));
                            emit(0x48 | REXR, 0x8b, make_modrm(MOD_REG, REGISTER_R9, REGISTER_D));
                            
                            emit(0x79); u8 *patch_rcx_unsigned = emit_get_current(context); emit(0);
                            {
                                if(operand_size == 2) emit(0x66);
                                if(operand_size == 8) emit(0x48);
                                emit(0xf7, make_modrm(MOD_REG, /*neg*/3, REGISTER_C));
                            }
                            *patch_rcx_unsigned = (u8)(emit_get_current(context) - (patch_rcx_unsigned + 1));
                            
                            if(operand_size == 2) emit(0x66);
                            if(operand_size == 8) emit(0x48);
                            emit(0x85, make_modrm(MOD_REG, REGISTER_D, REGISTER_D));
                            emit(0x79); u8 *patch_rdx_unsigned = emit_get_current(context); emit(0);
                            {
                                if(operand_size == 2) emit(0x66);
                                if(operand_size == 8) emit(0x48);
                                emit(0xf7, make_modrm(MOD_REG, /*neg*/2, REGISTER_D));
                                
                                if(operand_size == 2) emit(0x66);
                                if(operand_size == 8) emit(0x48);
                                emit(0xf7, make_modrm(MOD_REG, /*neg*/2, REGISTER_A));
                                
                                if(operand_size == 2) emit(0x66);
                                if(operand_size == 8) emit(0x48);
                                emit(0x83, make_modrm(MOD_REG, REG_OPCODE_add, REGISTER_A), 1);
                                
                                if(operand_size == 2) emit(0x66);
                                if(operand_size == 8) emit(0x48);
                                emit(0x83, make_modrm(MOD_REG, REG_OPCODE_adc, REGISTER_D), 0);
                            }
                            *patch_rdx_unsigned = (u8)(emit_get_current(context) - (patch_rdx_unsigned + 1));
                        }
                        
                        // Check for unsigned overflow, we have:
                        // 
                        //       [rdx:rax] / src >= (2 ** 64)
                        //   <=> [rdx:rax] >= [src:0]
                        //   <=> rdx >= src
                        //      
                        //    cmp rdx, rcx
                        //    jae fail
                        emit(0x48, 0x3B, make_modrm(MOD_REG, REGISTER_D, REGISTER_C));
                        emit(0x73); u8 *patch_fail_overflow = emit_get_current(context); emit(0);
                        
                        // op rdx, rax, rcx
                        if(operand_size == 2) emit(0x66);
                        if(operand_size == 8) emit(0x48);
                        emit(opcode, make_modrm(MOD_REG, /*div*/6, REGISTER_C)); // @note: Always perform a div, not an idiv.
                        
                        u8 *patch_idiv_success = 0;
                        u8 *patch_idiv_overflow_unsigned = 0;
                        u8 *patch_idiv_overflow_signed = 0;
                        
                        if(reg.encoding == /*idiv*/7){
                            // 
                            // Check for signed overflow and fix up negated registers.
                            // 
                            //     Test if the result is signed:
                            //         xor r8, r9
                            //         js result_is_signed
                            //         
                            //       result_is_unsigned:
                            //           test rax, rax
                            //           js patch_overflow_unsigned
                            //           
                            //           jmp success
                            //         
                            //       result_is_signed:
                            //           neg rax
                            //           test rax, rax
                            //           jz success
                            //           jns patch_overflow_signed
                            //           
                            //      We are successful, negate the reminder, if the original quotient was negative.
                            //      
                            //        success:
                            //           test r9, r9
                            //           jns idiv_success
                            //           
                            //           neg rdx
                            
                            u8 *patch_overflow_unsigned_success = 0;
                            u8 *patch_overflow_signed_success = 0;
                            
                            if(operand_size == 2) emit(0x66);
                            emit(0x40 | 8* (operand_size == 8) | REXR | REXB, 0x33, make_modrm(MOD_REG, REGISTER_R8, REGISTER_R9));
                            emit(0x78); u8 *patch_result_signed = emit_get_current(context); emit(0);
                            {
                                if(operand_size == 2) emit(0x66);
                                if(operand_size == 8) emit(0x48);
                                emit(0x85, make_modrm(MOD_REG, REGISTER_A, REGISTER_A));
                                emit(0x78); patch_idiv_overflow_unsigned = emit_get_current(context); emit(0);
                                
                                emit(0xeb); patch_overflow_unsigned_success = emit_get_current(context); emit(0);
                            }
                            
                            *patch_result_signed = (u8)(emit_get_current(context) - (patch_result_signed + 1));
                            {
                                // neg rax
                                if(operand_size == 2) emit(0x66);
                                if(operand_size == 8) emit(0x48);
                                emit(0xf7, make_modrm(MOD_REG, /*neg*/3, REGISTER_A));
                                
                                // test rax, rax
                                if(operand_size == 2) emit(0x66);
                                if(operand_size == 8) emit(0x48);
                                emit(0x85, make_modrm(MOD_REG, REGISTER_A, REGISTER_A));
                                
                                // jz patch_overflow_signed_success
                                emit(0x74); patch_overflow_signed_success = emit_get_current(context); emit(0);
                                // jns patch_idiv_overflow_signed
                                emit(0x79); patch_idiv_overflow_signed = emit_get_current(context); emit(0);
                            }
                            
                            *patch_overflow_unsigned_success = (u8)(emit_get_current(context) - (patch_overflow_unsigned_success + 1));
                            *patch_overflow_signed_success   = (u8)(emit_get_current(context) - (patch_overflow_signed_success + 1));
                            
                            if(operand_size == 2) emit(0x66);
                            emit(0x40 | 8 * (operand_size == 8) | REXR | REXB, 0x85, make_modrm(MOD_REG, REGISTER_R9, REGISTER_R9));
                            emit(0x79); patch_idiv_success = emit_get_current(context); emit(0);
                            
                            if(operand_size == 2) emit(0x66);
                            if(operand_size == 8) emit(0x48);
                            emit(0xf7, make_modrm(MOD_REG, /*neg*/3, REGISTER_D));
                        }
                        
                        emit(0xeb); u8 *patch_jump_success = emit_get_current(context); emit(0);
                        
                        {
                            // On failiure exit the jit after setting context->crash to 'CRASH_divide'.
                            //    mov [context + .crash], CRASH_divide
                            //    jmp context->jit_exit
                            *patch_fail_zero     = (u8)(emit_get_current(context) - (patch_fail_zero + 1));
                            *patch_fail_overflow = (u8)(emit_get_current(context) - (patch_fail_overflow + 1));
                            
                            if(patch_idiv_overflow_unsigned) *patch_idiv_overflow_unsigned = (u8)(emit_get_current(context) - (patch_idiv_overflow_unsigned + 1));
                            if(patch_idiv_overflow_signed)   *patch_idiv_overflow_signed   = (u8)(emit_get_current(context) - (patch_idiv_overflow_signed + 1));
                            
                            emit(0xC7, make_modrm(MOD_REGM_OFF32, 0, NONVOL_context)); emit32(offset_in_type(struct context, crash)); emit32(CRASH_divide);
                            u32 patch = (s32)(context->jit_exit - (emit_get_current(context) + 5));
                            emit(0xe9);  emit32(patch);
                        }
                        
                        *patch_jump_success = (u8)(emit_get_current(context) - (patch_jump_success + 1));
                        if(patch_idiv_success) *patch_idiv_success = (u8)(emit_get_current(context) - (patch_idiv_success + 1));
                        
                        //
                        // Save the two out registers.
                        //
                        emit_write_gpr(context, guest(REGISTER_D), host(REGISTER_D), operand_size, rex);
                        emit_write_gpr(context, guest(REGISTER_A), host(REGISTER_A), operand_size, rex);
                    }break;
                    crash_invalid_default_case("f6 f7", emit_jit_result);
                }
            }break;
            
            case 0xf8:{ // clc
                // and byte [registers + .rflags], ~CF
                emit(0x80, make_modrm(MOD_REGM_OFF32, REG_OPCODE_and, NONVOL_registers));
                emit32(offset_in_type(struct registers, rflags));
                emit((u8)~FLAG_CF);
            }break;
            case 0xf9:{ // stc
                // or byte [registers + .rflags], CF
                emit(0x80, make_modrm(MOD_REGM_OFF32, REG_OPCODE_or, NONVOL_registers));
                emit32(offset_in_type(struct registers, rflags));
                emit(FLAG_CF);
            }break;
            
            case 0xfa:{ // cli
                // and dword [registers + .rflags], ~IF
                emit(0x81, make_modrm(MOD_REGM_OFF32, REG_OPCODE_and, NONVOL_registers));
                emit32(offset_in_type(struct registers, rflags));
                emit32((u32)(~FLAG_IF));
            }break;
            
            case 0xfb:{ // sti
                // or dword [registers + .rflags], IF
                emit(0x81, make_modrm(MOD_REGM_OFF32, REG_OPCODE_or, NONVOL_registers)); emit32(offset_in_type(struct registers, rflags)); emit32((u32)(FLAG_IF));
            }break;
            
            case 0xfc:{ // cld
                // and dword [registers + .rflags], ~DF
                emit(0x81, make_modrm(MOD_REGM_OFF32, REG_OPCODE_and, NONVOL_registers));
                emit32(offset_in_type(struct registers, rflags));
                emit32((u32)(~FLAG_DF));
            }break;
            
            case 0xfd:{ // std
                // or dword [registers + .rflags], DF
                emit(0x81, make_modrm(MOD_REGM_OFF32, REG_OPCODE_or, NONVOL_registers));
                emit32(offset_in_type(struct registers, rflags));
                emit32(FLAG_DF);
            }break;
            
            case 0xfe: case 0xff:{
                crash_assert(opcode != 0xfe || reg.encoding == 0 || reg.encoding == 1, emit_jit_result); // 0xfe only supports 'inc' and 'dec'.
                if(opcode == 0xfe) operand_size = 1;
                
                switch(reg.encoding){
                    case 0: case 1:{ // inc/dec regm
                        if(mod == MOD_REG){
                            
                            emit_load_flags(context); // "The CF flag is not affected."
                            // inc/dec size ptr [registers + .regm]
                            if(operand_size == 2) emit(0x66);
                            if(operand_size == 8) emit(0x48);
                            emit(opcode, make_modrm(MOD_REGM_OFF8, reg.encoding, NONVOL_registers), reg_offset(regm, operand_size, rex));
                            emit_destructively_update_flags(context, host(REGISTER_D));
                            
                            if(operand_size == 4){
                                // mov dword ptr[registers + .regm + 4], 0
                                emit(0xC7, make_modrm(MOD_REGM_OFF8, 0, NONVOL_registers), (u8)(8 * regm.encoding + 4), 0x00, 0x00, 0x00, 0x00);
                            }
                        }else{
                            // mov flex, rax ; address
                            emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                            emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), operand_size, /*need_write_permission*/1);
                            
                            emit_load_flags(context); // "The CF flag is not affected."
                            // inc/dec rax
                            if(operand_size == 2) emit(0x66);
                            if(operand_size == 8) emit(0x48);
                            emit(opcode, make_modrm(MOD_REG, reg.encoding, REGISTER_A));
                            emit_destructively_update_flags(context, host(REGISTER_D));
                            
                            emit_write_host_register(context, host(NONVOL_flex), host(REGISTER_A), operand_size);
                        }
                    }break;
                    case 2:{// call regm
                        //
                        // Write the call address to the flex register, so we can store it in nonvol_rip, 
                        // after we have attempted to store the return address on the stack.
                        //
                        if(mod == MOD_REG){
                            emit_read_gpr(context, host(NONVOL_flex), regm, 8, rex);
                        }else{
                            emit_read_into_gpr(context, host(NONVOL_flex), host(REGISTER_A), 8, /*need_write_permission*/0);
                        }
                        
                        {
                            //
                            // Compute the next rip in 'rax' and store it on the stack.
                            //
                            
                            // mov rax, nonvol_rip
                            emit(0x48 | REXB, 0x8b, make_modrm(MOD_REG, REGISTER_A, NONVOL_rip));
                            
                            // add rax, instruction_size
                            emit(0x48, 0x83, make_modrm(MOD_REG, REG_OPCODE_add, REGISTER_A), (u8)instruction_size);
                            
                            // Push the return address to the stack.
                            //     mov r8, [registers  + .rsp]
                            //     add r8, 8
                            emit_read_gpr(context, host(REGISTER_R8), guest(REGISTER_SP), 8, 0);
                            emit(0x49, 0x83, 0xE8, 0x08);
                            emit_write_host_register(context, host(REGISTER_R8), host(REGISTER_A), 8);
                            
                            // If the write succeeded commit the allocation of 8 bytes.
                            emit(0x48, 0x83, make_modrm(MOD_REGM_OFF8, REG_OPCODE_sub, NONVOL_registers), (u8)(REGISTER_SP * 8), 0x08);
                        }
                        
                        // mov nonvol_rip, flex
                        emit_inst(0x8b, reg(8, NONVOL_rip, NONVOL_flex));
                        
                        is_unconditional_jump = 1;
                    }break;
                    case 4:{ // jmp  regm
                        //
                        // Write the jump address to 'registers.rip'.
                        //
                        if(mod == MOD_REG){
                            emit_read_gpr(context, host(REGISTER_C), regm, 8, rex);
                        }else{
                            emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), 8, /*need_write_permission*/0);
                        }
                        
                        // @cleanup: This could be done above shaving one instruction.
                        //     mov nonvol_rip, rcx
                        emit(0x48 | REXR, 0x8b, make_modrm(MOD_REG, NONVOL_rip, REGISTER_C));
                        
                        is_unconditional_jump = 1;
                    }break;
                    
                    case 5:{ // jmpf
                        //
                        // @note: This is a far jump. This is only relevant for WoW64 stuff.
                        //        We just issue a __fastfail (interrupt 0x29) to terminate the WoW64 application.
                        //
                        
                        // call helper_far_jump:
                        //     mov arg1, context
                        //     call helper_far_jump
                        
                        emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                        emit_call_to_helper(context, helper_far_jump, HELPER_cares_about_rip | HELPER_might_change_rip | HELPER_might_crash);
                        
                        is_unconditional_jump = 1;
                    }break;
                    
                    case 6:{ // push regm64
                        // Always load 8 bytes I think...
                        if(mod == MOD_REG){
                            emit_read_gpr(context, host(REGISTER_C), regm, 8, 0);
                        }else{
                            emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), 8, /*need_write_permission*/0);
                        }
                        
                        // Load the stack pointer.
                        emit_read_gpr(context, host(REGISTER_R8), guest(REGISTER_SP), 8, 0);
                        
                        // sub r8, 8
                        emit(0x49, 0x83, 0xE8, 0x08);
                        
                        // Store the value to the stack.
                        emit_write_host_register(context, host(REGISTER_R8), host(REGISTER_C), 8);
                        
                        // If the write succeeded commit the allocation of 8 bytes.
                        emit(0x48, 0x83, make_modrm(MOD_REGM_OFF8, REG_OPCODE_sub, NONVOL_registers), (u8)(REGISTER_SP * 8), 0x08);
                    }break;
                    
                    crash_invalid_default_case("ff fe", emit_jit_result);
                }
            }break;
            
            //
            // Two byte instructions (0f opcode) 0x100 - 0x1ff
            //
            
            case 0x100:{
                switch(reg.encoding){
                    case 0:{ // SLDT
                        // movzx rcx, word  [registers + .ldg.selector]
                        emit(0x48, 0x0f, 0xB7, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, ldt.selector));
                        
                        if(mod == MOD_REG){
                            emit_write_gpr(context, regm, host(REGISTER_C), operand_size, rex);
                        }else{
                            emit_write_host_register(context, host(REGISTER_A), host(REGISTER_C), 2);
                        }
                    }break;
                    
                    case 1:{ // STR
                        // movzx rcx, word  [registers + .tr.selector]
                        emit(0x48, 0x0f, 0xB7, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, tr.selector));
                        
                        if(mod == MOD_REG){
                            emit_write_gpr(context, regm, host(REGISTER_C), operand_size, rex);
                        }else{
                            emit_write_host_register(context, host(REGISTER_A), host(REGISTER_C), 2);
                        }
                    }break;
                    
                    case 2:{ // LLDT
                        
                        if(mod == MOD_REG){
                            emit_read_gpr(context, host(REGISTER_C), regm, 4, 0);
                        }else{
                            emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), 2, /*need_write_permission*/0);
                        }
                        
                        emit(0x66, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, ldt.selector));
                    }break;
                    
                    case 3:{ // ltr - load task register
                        
                        // mov arg2, selector (reg or address)
                        // mov arg1, context
                        // call helper_load_task_register
                        if(mod == MOD_REG){
                            emit_read_gpr(context, host(ARG_REG_2), regm, 4, 0);
                        }else{
                            emit_read_into_gpr(context, host(ARG_REG_2), host(REGISTER_A), 2, /*need_write_permission*/0);
                        }
                        emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                        emit_call_to_helper(context, helper_load_task_register, HELPER_might_crash);
                    }break;
                    
                    case 4:  // verr m16
                    case 5:{ // verw m16
                        
                        // mov arg2, selector
                        // mov arg1, context
                        // mov arg3, is_verw
                        // call helper_verify_segment
                        
                        if(mod == MOD_REG){
                            emit_read_gpr(context, host(ARG_REG_2), regm, 4, 0);
                        }else{
                            emit_read_into_gpr(context, host(ARG_REG_2), host(REGISTER_A), 2, /*need_write_permission*/0);
                        }
                        emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                        emit_inst(0xC7, reg(8, /*mov*/0, ARG_REG_3)); emit32((reg.encoding == 5));
                        
                        emit_call_to_helper(context, helper_verify_segment, HELPER_might_crash);
                    }break;
                    
                    crash_invalid_default_case("0f 00", emit_jit_result);
                }
            }break;
            
            case 0x101:{
                switch(modrm){
                    case 0xD0:{ // XGETBV
                        // "Reads an XCR specified by ECX into EDX:EAX."
                        // "XCR0 is supported on any processor that supports the XGETBV instruction."
                        //  XGETBV with rcx = 1, only in special cases.
                        
                        emit_read_gpr(context, host(REGISTER_C), guest(REGISTER_C), 4, 0);
                        
                        //  test rcx, rcx
                        //  jz .success
                        emit(0x85, make_modrm(MOD_REG, REGISTER_C, REGISTER_C));
                        emit(0x74); u8 *patch = emit_get_current(context); emit(0);
                        
                        // .crash:
                        //    mov [context + .crash], CRASH_execute
                        //    jmp context->jit_exit
                        emit(0xC7, make_modrm(MOD_REGM_OFF32, 0, NONVOL_context)); emit32(offset_in_type(struct context, crash)); emit32(CRASH_divide);
                        u32 exit_patch = (s32)(context->jit_exit - (emit_get_current(context) + 5));
                        emit(0xe9);  emit32(exit_patch);
                        
                        *patch = (u8)(emit_get_current(context) - (patch + 1));
                        // .success:
                        //     mov edx, [registers + .xcr0 + 4]
                        //     mov eax, [registers + .xcr0]
                        emit(0x8B, make_modrm(MOD_REGM_OFF32, REGISTER_D, NONVOL_registers)); emit32(offset_in_type(struct registers, xcr0) + 4);
                        emit(0x8B, make_modrm(MOD_REGM_OFF32, REGISTER_A, NONVOL_registers)); emit32(offset_in_type(struct registers, xcr0));
                        
                        emit_write_gpr(context, guest(REGISTER_A), host(REGISTER_A), 8, 0);
                        emit_write_gpr(context, guest(REGISTER_D), host(REGISTER_D), 8, 0);
                    }break;
                    
                    case 0xD1:{  // XSETBV
                        emit_read_gpr(context, host(REGISTER_C), guest(REGISTER_C), 4, 0);
                        
                        //  test rcx, rcx
                        //  jz .success
                        emit(0x85, make_modrm(MOD_REG, REGISTER_C, REGISTER_C));
                        emit(0x74); u8 *patch = emit_get_current(context); emit(0);
                        
                        // .crash:
                        //    mov [context + .crash], CRASH_execute
                        //    jmp context->jit_exit
                        emit(0xC7, make_modrm(MOD_REGM_OFF32, 0, NONVOL_context)); emit32(offset_in_type(struct context, crash)); emit32(CRASH_divide);
                        u32 exit_patch = (s32)(context->jit_exit - (emit_get_current(context) + 5));
                        emit(0xe9);  emit32(exit_patch);
                        
                        *patch = (u8)(emit_get_current(context) - (patch + 1));
                        
                        emit_read_gpr(context, host(REGISTER_A), guest(REGISTER_A), 8, 0);
                        emit_read_gpr(context, host(REGISTER_D), guest(REGISTER_D), 8, 0);
                        
                        // .success:
                        //     mov [registers + .xcr0 + 4], edx
                        //     mov [registers + .xcr0 + 0], eax
                        
                        emit(0x8B, make_modrm(MOD_REGM_OFF32, REGISTER_D, NONVOL_registers)); emit32(offset_in_type(struct registers, xcr0) + 4);
                        emit(0x8B, make_modrm(MOD_REGM_OFF32, REGISTER_A, NONVOL_registers)); emit32(offset_in_type(struct registers, xcr0));
                    }break;
                    
                    case 0xC2:  // VMLAUNCH
                    case 0xC3:  // VMRESUME
                    case 0xC4:  // VMXOFF
                    case 0xC8:  // MONITOR
                    case 0xC9:  // MWAIT
                    {
                        set_crash_information(context, CRASH_unimplemented_instruction, 0);
                        
                    }break;
                    
                    case 0xC1:{ // VMCALL
                        emit(0x48, 0x8B, make_modrm(MOD_REG, ARG_REG_1, NONVOL_context));
                        emit(0x48, 0x8B, make_modrm(MOD_REG, ARG_REG_2, NONVOL_registers));
                        emit_call_to_helper(context, helper_vmcall, HELPER_cares_about_rip | HELPER_might_change_rip | HELPER_might_crash);
                        should_check_for_interrupts = 1;
                    }break;
                    
                    case 0xF9:{ // RDTSCP
                        //
                        // "Reads the current value of the processors time-stamp counter (a 64-bit MSR) into the EDX:EAX registers
                        //  and also reads the value of the IA32_TSC_AUX MSR (address C0000103H) into the ECX register."
                        //
                        
                        // Increment 'ia32_tsc'
                        //     mov rdx, qword [registers + .ia32_tsc]
                        //     add rdx, RDTSC_INCREMENT
                        //     mov qword [registers + .ia32_tsc], rdx
                        //     
                        // Load eax:edx with the resulting tsc.
                        //     mov eax, edx
                        //     shr rdx, 32
                        emit(0x48, 0x8b, make_modrm(MOD_REGM_OFF32, REGISTER_D, NONVOL_registers)); emit32(offset_in_type(struct registers, ia32_tsc));
                        emit(0x48, 0x81, make_modrm(MOD_REG, REG_OPCODE_add, REGISTER_D)); emit32(RDTSC_INCREMENT);
                        emit(0x48, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_D, NONVOL_registers)); emit32(offset_in_type(struct registers, ia32_tsc));
                        emit(0x8b, make_modrm(MOD_REG, REGISTER_A, REGISTER_D));
                        emit(0x48, 0xC1, make_modrm(MOD_REG, 5, REGISTER_D), 32);
                        
                        // Load the ia32_tsc_aux:
                        //     mov rcx, qword[registers + .ia32_tsc_aux]
                        emit(0x48, 0x8b, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, ia32_tsc_aux));
                        
                        // Write to the guest registers:
                        emit_write_gpr(context, guest(REGISTER_A), host(REGISTER_A), 4, 0);
                        emit_write_gpr(context, guest(REGISTER_D), host(REGISTER_D), 4, 0);
                        emit_write_gpr(context, guest(REGISTER_C), host(REGISTER_C), 4, 0);
                    }break;
                    
                    
                    case 0xCA:{ // CLAC - Clear the AC flag (Access Control) in the EFLAGS register
                        // and dword [registers + .rflags], ~AC
                        emit(0x81, make_modrm(MOD_REGM_OFF32, REG_OPCODE_and, NONVOL_registers));
                        emit32(offset_in_type(struct registers, rflags));
                        emit32((u32)(~FLAG_AC));
                    }break;
                    case 0xCB:{ // STAC - Set the AC flag (Access Control) in the EFLAGS register
                        // or byte [registers + .rflags + 1], IF
                        emit(0x81, make_modrm(MOD_REGM_OFF32, REG_OPCODE_or, NONVOL_registers));
                        emit32(offset_in_type(struct registers, rflags));
                        emit32((u32)(FLAG_AC));
                    }break;
                    
                    case 0xF8:{ // SWAPGS
                        // mov rcx, qword [registers + .gs_base]
                        // mov rax, qword [registers + .gs_swap]
                        emit(0x48, 0x8b, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, gs_base));
                        emit(0x48, 0x8b, make_modrm(MOD_REGM_OFF32, REGISTER_A, NONVOL_registers)); emit32(offset_in_type(struct registers, gs_swap));
                        
                        // mov qword [registers + .gs_swap], rcx
                        // mov qword [registers + .gs_base], rax
                        emit(0x48, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, gs_swap));
                        emit(0x48, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_A, NONVOL_registers)); emit32(offset_in_type(struct registers, gs_base));
                    }break;
                    
                    default:{
                        //
                        // If it is not one of the 3-byte instructions it is an instruction with 'op' as modrm.
                        //
                        
                        switch(reg.encoding){
                            case 0:{ // sgdt - Stores the content of the global descriptor table register in the destination operand.
                                crash_assert(mod != MOD_REG, emit_jit_result);
                                
                                // mov flex, rax ; address
                                emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                                
                                // movzx rcx, word  [registers + .gdt_limit]
                                emit(0x48, 0x0f, 0xB7, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, gdt_limit));
                                emit_write_host_register(context, host(NONVOL_flex), host(REGISTER_C), 2);
                                
                                emit_inst(0x81, reg(8, REG_OPCODE_add, NONVOL_flex)); emit32((s32)2);
                                
                                // mov   rcx, qword [registers + .gdt_base]
                                emit(0x48, 0x8b, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, gdt_base));
                                emit_write_host_register(context, host(NONVOL_flex), host(REGISTER_C), 8);
                            }break;
                            
                            case 1:{ // sidt - Stores the content of the interrupt descriptor table register in the destination operand.
                                crash_assert(mod != MOD_REG, emit_jit_result);
                                
                                // mov flex, rax ; address
                                emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                                
                                // movzx rcx, word  [registers + .idt_limit]
                                emit(0x48, 0x0f, 0xB7, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, idt_limit));
                                emit_write_host_register(context, host(NONVOL_flex), host(REGISTER_C), 2);
                                
                                emit_inst(0x81, reg(8, REG_OPCODE_add, NONVOL_flex)); emit32((s32)2);
                                
                                // mov   rcx, qword [registers + .idt_base]
                                emit(0x48, 0x8b, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, idt_base));
                                emit_write_host_register(context, host(NONVOL_flex), host(REGISTER_C), 8);
                            }break;
                            
                            case 2:{ // lgdt m16xm64
                                crash_assert(mod != MOD_REG, emit_jit_result);
                                
                                // GDTR(Limit) := SRC[0:15];
                                // GDTR(Base) := SRC[16:79];
                                
                                // mov flex, rax ; address
                                emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                                
                                emit_read_into_gpr(context, host(REGISTER_A), host(NONVOL_flex), /*size*/2, 0);
                                
                                // mov qword [registers + .gdt_limit], rax
                                emit(0x66, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_A, NONVOL_registers)); emit32(offset_in_type(struct registers, gdt_limit));
                                
                                // add flex, 2
                                emit_inst(0x81, reg(8, REG_OPCODE_add, NONVOL_flex)); emit32((s32)2);
                                
                                emit_read_into_gpr(context, host(REGISTER_A), host(NONVOL_flex), /*size*/8, 0);
                                
                                // mov qword [registers + .gdt_base], rax
                                emit(0x48, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_A, NONVOL_registers)); emit32(offset_in_type(struct registers, gdt_base));
                                
                                // @note: @hack: Read the gdt_base. This sets the access bits, usually this only happens after a ret.
                                emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), /*size*/8, 0);
                            }break;
                            
                            case 3:{ // lidt m16xm64
                                crash_assert(mod != MOD_REG, emit_jit_result);
                                
                                // IDTR(Limit) := SRC[0:15];
                                // IDTR(Base) := SRC[16:79];
                                
                                // mov flex, rax ; address
                                emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                                
                                emit_read_into_gpr(context, host(REGISTER_A), host(NONVOL_flex), /*size*/2, 0);
                                
                                // mov word [registers + .idt_limit], ax
                                emit(0x66, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_A, NONVOL_registers)); emit32(offset_in_type(struct registers, idt_limit));
                                
                                // add flex, 2
                                emit_inst( 0x81, reg(8, REG_OPCODE_add, NONVOL_flex)); emit32((s32)2);
                                
                                emit_read_into_gpr(context, host(REGISTER_A), host(NONVOL_flex), /*size*/8, 0);
                                
                                // mov qword [registers + .idt_base], rax
                                emit(0x48, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_A, NONVOL_registers)); emit32(offset_in_type(struct registers, idt_base));
                            } break;
                            
                            case 4:{ // SMSW
                                
                                // mov rcx, qword ptr [registers + .cr0]
                                emit(0x48, 0x8B, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, cr0));
                                
                                if(mod == MOD_REG){
                                    // In 64-bit mode, the behavior of the SMSW instruction is defined by the following examples:
                                    //
                                    // SMSW r16 operand size 16, store CR0[15:0] in r16
                                    // SMSW r32 operand size 32, zero-extend CR0[31:0], and store in r32
                                    // SMSW r64 operand size 64, zero-extend CR0[63:0], and store in r64
                                    
                                    emit_write_gpr(context, regm, host(REGISTER_C), operand_size, rex);
                                }else{
                                    //
                                    // "When the destination operand is a memory location,
                                    //  the low-order 16 bits of register CR0 are written to memory as a 16-bit quantity,
                                    //  regardless of the operand size."
                                    //
                                    emit_write_host_register(context, host(REGISTER_A), host(REGISTER_C), /*size*/2);
                                }
                            }break;
                            
                            case 7:{ // invlpg regm
                                crash_assert(mod != MOD_REG, emit_jit_result);
                                
                                // helper_invlpg(context, address):
                                //     mov  arg1, context
                                //     mov  arg2, address(rax)
                                //     call helper_invlpg
                                emit_inst(0x8B, reg(8, ARG_REG_1, NONVOL_context));
                                emit_inst(0x8B, reg(8, ARG_REG_2, REGISTER_A));
                                emit_call_to_helper(context, helper_invlpg, HELPER_simple_call);
                            }break;
                            
                            crash_invalid_default_case("0f 01", emit_jit_result);
                        }
                        
                    }break;
                }
            }break;
            
            case 0x105:{ // syscall
                
                {
                    //
                    // Compute the return address in rax and store it in rcx.
                    //
                    
                    // lea rax, [nonvol_rip + instruction_size]
                    // mov [registers + .rcx], rax
                    emit(0x48 | REXB, 0x8d, make_modrm(MOD_REGM_OFF8, REGISTER_A, NONVOL_rip), (u8)instruction_size);
                    emit_write_gpr(context, guest(REGISTER_C), host(REGISTER_A), 8, 0);
                }
                
                // mov nonvol_rip, [registers + .lstar]
                emit(0x48 | REXR, 0x8b, make_modrm(MOD_REGM_OFF32, NONVOL_rip, NONVOL_registers)); emit32(offset_in_type(struct registers, ia32_lstar));
                
                {
                    // "SYSCALL also saves RFLAGS into R11 and then masks RFLAGS using the IA32_FMASK MSR (MSR address C0000084H);
                    //  specifically, the processor clears in RFLAGS every bit corresponding to a bit that is set in the IA32_FMASK MSR."
                    
                    // Save the rflags in r11.
                    //      mov rcx, [registers + .rflags]
                    emit(0x48, 0x8b, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, rflags));
                    
                    emit_write_gpr(context, guest(REGISTER_R11), host(REGISTER_C), 8, 0);
                    
                    // mov rdx, [registers + .fmask]
                    // not rdx
                    // and rcx, rdx
                    emit(0x48, 0x8b, make_modrm(MOD_REGM_OFF32, REGISTER_D, NONVOL_registers)); emit32(offset_in_type(struct registers, ia32_fmask));
                    emit(0x48, 0xF7, make_modrm(MOD_REG, /*not*/2, REGISTER_D));
                    emit(0x48, 0x23, make_modrm(MOD_REG, REGISTER_C, REGISTER_D));
                    
                    // mov [registers + .rflags], rcx
                    emit(0x48, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, rflags));
                }
                
                //
                // @incomplete: I am supposed to write the whole segment here to fixed values.
                //              We are ignoring segment, so only the selector really matters,
                //              as code will look at it.
                //
                
                // The cs and ss selectors are loaded from IA32_STAR[47:32].
                //     mov ecx, dword ptr [registers + IA32_STAR + 4]
                //     and ecx, 0xfffc
                //     mov word ptr [registers + .cs.selector], ecx
                //     add ecx, 8
                //     mov word ptr [registers + .ss.selector], ecx
                emit(0x8b, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, ia32_star) + 4);
                emit(0x81, make_modrm(MOD_REG, REG_OPCODE_and, REGISTER_C)); emit32(0xfffc);
                emit(0x66, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, cs.selector));
                emit(0x83, make_modrm(MOD_REG, REG_OPCODE_add, REGISTER_C)); emit(8);
                emit(0x66, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, ss.selector));
                
                is_unconditional_jump = 1;
            }break;
            
            case 0x107:{ // sysret
                
                // "SYSRET loads the CS and SS selectors with values derived from bits of the IA32_STAR MSR."
                // The cs and ss selectors are loaded from IA32_STAR[63:48].
                //     movzx ecx, word ptr [registers + IA32_STAR + 6]
                //     or ecx, 3
                //     add ecx, 16
                //     mov word ptr [registers + .cs.selector], ecx
                //     sub ecx, 8
                //     mov word ptr [registers + .ss.selector], ecx
                emit(0x0f, 0xb7, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, ia32_star) + 6);
                emit(0x83, make_modrm(MOD_REG, REG_OPCODE_or, REGISTER_C)); emit(3);
                emit(0x83, make_modrm(MOD_REG, REG_OPCODE_add, REGISTER_C)); emit(16);
                emit(0x66, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, cs.selector));
                emit(0x83, make_modrm(MOD_REG, REG_OPCODE_sub, REGISTER_C)); emit(8);
                emit(0x66, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, ss.selector));
                
                {
                    //
                    // Load the rflags from r11.
                    //     mov rcx, [registers + .r11]
                    //     and rcx, 0x3c7fd7
                    //     or  rcx, 2
                    //     mov [registers + .rflags], rcx
                    emit_read_gpr(context, host(REGISTER_C), guest(REGISTER_R11), 8, 0);
                    emit(0x81, make_modrm(MOD_REG, REG_OPCODE_and, REGISTER_C)); emit32(0x3c7fd7);
                    emit(0x83, make_modrm(MOD_REG, REG_OPCODE_or, REGISTER_C)); emit(2);
                    emit(0x48, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, rflags));
                }
                
                //
                // Load the new rip from rcx, and jump to it.
                //
                emit_read_gpr(context, host(NONVOL_rip), guest(REGISTER_C), 8, 0);
                
                is_unconditional_jump = 1;
            }break;
            
            case 0x109: break; // WBINVD
            
            case 0x12b:  // movntps m, xmm
            case 0x129:{  // movaps m, xmm
                
                crash_assert(legacy_prefix_flags == 0 || legacy_prefix_flags == MANDATORY_PREFIX_66, emit_jit_result);
                
                if(mod == MOD_REG){
                    emit_read_xmm_register(context, host(REGISTER_XMM1), reg, vex);
                    emit_write_xmm_register(context, regm, host(REGISTER_XMM1), vex);
                }else{
                    emit_write_guest_register(context, host(REGISTER_A), reg, (vex & VEXL) ? 32 : 16, 0);
                }
            }break;
            
            case 0x16f:{
                
                crash_assert(legacy_prefix_flags == MANDATORY_PREFIX_F3 || legacy_prefix_flags == MANDATORY_PREFIX_66, emit_jit_result);
                //         66 0F     6F /r  MOVDQA xmm1, xmm2/m128 SSE2 Move aligned packed integer values from xmm2/mem to xmm1.
                // VEX.128.66.0F.WIG 6F /r VMOVDQA xmm1, xmm2/m128 AVX  Move aligned packed integer values from xmm2/mem to xmm1.
                // VEX.256.66.0F.WIG 6F /r VMOVDQA ymm1, ymm2/m256 AVX  Move aligned packed integer values from ymm2/mem to ymm1.
                
                //         F3 0F     6F /r  MOVDQU xmm1, xmm2/m128 SSE2 Move unaligned packed integer values from xmm2/m128 to xmm1.
                // VEX.128.F3.0F.WIG 6F /r VMOVDQU xmm1, xmm2/m128 AVX  Move unaligned packed integer values from xmm2/m128 to xmm1.
                // VEX.256.F3.0F.WIG 6F /r VMOVDQU ymm1, ymm2/m256 AVX  Move unaligned packed integer values from ymm2/m256 to ymm1.
                
                if(mod == MOD_REG){
                    emit_read_xmm_register(context, host(REGISTER_XMM0), regm, vex);
                }else{
                    // @note: manual vex here because we just care about it being 64 bit
                    emit_read_into_xmm(context, host(REGISTER_XMM0), host(REGISTER_A), 0, make_vex(0, 0, (vex >> 2) & 1, 0), /*need_write_permission*/0);
                }
                emit_write_xmm_register(context, reg, host(REGISTER_XMM0), vex);
            }break;
            
            case 0x17f:{ // movdqa
                crash_assert(legacy_prefix_flags == MANDATORY_PREFIX_F3 || legacy_prefix_flags == MANDATORY_PREFIX_66, emit_jit_result);
                
                // VEX.128.66.0F.WIG 7F /r VMOVDQA xmm2/m128, xmm1 AVX Move aligned packed integer values from xmm1 to xmm2/mem.
                // VEX.256.66.0F.WIG 7F /r VMOVDQA ymm2/m256, ymm1 AVX Move aligned packed integer values from ymm1 to ymm2/mem.
                // VEX.128.F3.0F.WIG 7F /r VMOVDQU xmm2/m128, xmm1 AVX Move unaligned packed integer values from xmm1 to xmm2/m128.
                // VEX.256.F3.0F.WIG 7F /r VMOVDQU ymm2/m256, ymm1 AVX Move unaligned packed integer values from ymm1 to ymm2/m256.
                
                if(mod == MOD_REG){
                    emit_read_xmm_register(context, host(REGISTER_XMM1), reg, vex);
                    emit_write_xmm_register(context, regm, host(REGISTER_XMM1), vex);
                }else{
                    emit_write_guest_register(context, host(REGISTER_A), reg, (vex & VEXL) ? 32 : 16, 0);
                }
            }break;
            
            
            case 0x10d: case 0x118: case 0x119: case 0x11a: case 0x11b: case 0x11c: case 0x11d: case 0x11e: case 0x11f:{
                // nop
            }break;
            
            case 0x120:{ // mov regm, creg
                crash_assert(mod == MOD_REG && (operand_size == 4 || operand_size == 8), emit_jit_result);
                
                u32 offset = 0;
                switch(reg.encoding){
                    case 0: offset = offset_in_type(struct registers, cr0); break;
                    case 2: offset = offset_in_type(struct registers, cr2); break;
                    case 3: offset = offset_in_type(struct registers, cr3); break;
                    case 4: offset = offset_in_type(struct registers, cr4); break;
                    case 8: offset = offset_in_type(struct registers, cr8); break;
                    crash_invalid_default_case("Unhandled control register in 'mov regm, creg'.", emit_jit_result);
                }
                
                // mov rcx, [registers + offset]
                emit(0x48, 0x8b, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset);
                
                emit_write_gpr(context, regm, host(REGISTER_C), 8, 0);
            }break;
            
            case 0x121:{ // mov regm, dreg
                crash_assert(mod == MOD_REG && (operand_size == 4 || operand_size == 8), emit_jit_result);
                
                u32 offset = 0;
                switch(reg.encoding){
                    case 0: offset = offset_in_type(struct registers, dr0); break;
                    case 1: offset = offset_in_type(struct registers, dr1); break;
                    case 2: offset = offset_in_type(struct registers, dr2); break;
                    case 3: offset = offset_in_type(struct registers, dr3); break;
                    case 6: offset = offset_in_type(struct registers, dr6); break;
                    case 7: offset = offset_in_type(struct registers, dr7); break;
                    crash_invalid_default_case("Unhandled control register in 'mov regm, dreg'.", emit_jit_result);
                }
                
                // mov rcx, [registers + offset]
                emit(0x48, 0x8b, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset);
                
                emit_write_gpr(context, regm, host(REGISTER_C), 8, 0);
            }break;
            
            case 0x122:{ // mov creg, regm
                crash_assert(mod == MOD_REG && (operand_size == 4 || operand_size == 8), emit_jit_result);
                
                emit_read_gpr(context, host(ARG_REG_2), regm, 8, 0);
                
                if(reg.encoding == 8){
                    
                    // mov [registers + cr8], rdx
                    emit_inst(0x89, regm32(8, ARG_REG_2, NONVOL_registers)); emit32(offset_in_type(struct registers, cr8));
                    
                    should_check_for_interrupts = 1;
                }else if(reg.encoding == 2){
                    // mov [registers + cr2], rdx
                    emit_inst(0x89, regm32(8, ARG_REG_2, NONVOL_registers)); emit32(offset_in_type(struct registers, cr2));
                }else{
                    
                    void *helper = 0;
                    switch(reg.encoding){
                        case 0: helper = helper_write_to_cr0; break;
                        case 3: helper = helper_write_to_cr3; break;
                        case 4: helper = helper_write_to_cr4; break;
                        crash_invalid_default_case("Unhandled control register in 'mov creg, regm'.", emit_jit_result);
                    }
                    
                    // call helper(context, value)
                    emit_inst(0x8B, reg(8, ARG_REG_1, NONVOL_context));
                    emit_call_to_helper(context, helper, HELPER_cares_about_rip | HELPER_might_change_rip | HELPER_might_crash);
                    
                    // @cleanup: Right now we always leave the jit here, as we have just called
                    //           'invalidate_translate_lookaside_buffers' and potentially the whole
                    //           address space might have changed.
                    //           
                    //    add nonvol_rip, imm8
                    emit(0x48 | REXB, 0x83, make_modrm(MOD_REG, REG_OPCODE_add, NONVOL_rip), (u8)instruction_size); 
                    is_unconditional_jump = 1;
                }
            }break;
            
            case 0x123:{ // mov dreg, regm
                crash_assert(mod == MOD_REG && (operand_size == 4 || operand_size == 8), emit_jit_result);
                
                emit_read_gpr(context, host(REGISTER_C), regm, 8, 0);
                
                u32 offset = 0;
                switch(reg.encoding){
                    case 0: offset = offset_in_type(struct registers, dr0); break;
                    case 1: offset = offset_in_type(struct registers, dr1); break;
                    case 2: offset = offset_in_type(struct registers, dr2); break;
                    case 3: offset = offset_in_type(struct registers, dr3); break;
                    case 6: offset = offset_in_type(struct registers, dr6); break;
                    case 7: offset = offset_in_type(struct registers, dr7); break;
                    crash_invalid_default_case("Unhandled control register in 'mov regm, dreg'.", emit_jit_result);
                }
                
                // mov [registers + offset], rcx
                emit(0x48, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset);
            }break;
            
            
            case 0x12e: case 0x12f:{
                crash_assert(!(vex & VEXL) && (legacy_prefix_flags == 0 || legacy_prefix_flags == MANDATORY_PREFIX_66), emit_jit_result);
                //       0F    2E  UCOMISS xmm    xmm/m32 sse1        ....z.pc    ....z.pc            Unordered Compare Scalar Single-FP Values and Set EFLAGS
                // 66    0F    2E  UCOMISD xmm    xmm/m64 sse2        ....z.pc    ....z.pc            Unordered Compare Scalar Double-FP Values and Set EFLAGS
                //       0F    2F  COMISS  xmm    xmm/m32 sse1        ....z.pc    ....z.pc            Compare Scalar Ordered Single-FP Values and Set EFLAGS
                // 66    0F    2F  COMISD  xmm    xmm/m64 sse2        ....z.pc    ....z.pc            Compare Scalar Ordered Double-FP Values and Set EFLAGS
                
                if(mod == MOD_REG){
                    emit_read_xmm_register(context, host(REGISTER_XMM0), regm, vex);
                }else{
                    enum legacy_prefix flag = (legacy_prefix_flags == MANDATORY_PREFIX_66) ? /*movsd*/MANDATORY_PREFIX_F2 : /*movss*/MANDATORY_PREFIX_F3; 
                    emit_read_into_xmm(context, host(REGISTER_XMM0), host(REGISTER_A), flag, vex, /*need_write_permission*/0);
                }
                
                emit_read_xmm_register(context, host(REGISTER_XMM1), reg, vex);
                
                if(vex){
                    emit(0xc5, make_vex(0, 0, 0, vex & 3), opcode, make_modrm(MOD_REG, REGISTER_XMM1, REGISTER_XMM0));
                }else{
                    emit_simd_prefix(context, legacy_prefix_flags);
                    emit(0x0F, opcode, make_modrm(MOD_REG, REGISTER_XMM1, REGISTER_XMM0));
                }
                emit_destructively_update_flags(context, host(REGISTER_D));
            }break;
            
            
            case 0x130:{ // wrmsr
                emit_inst(0x8B, reg(8, ARG_REG_1, NONVOL_context));
                emit_inst(0x8B, reg(8, ARG_REG_2, NONVOL_registers));
                emit_call_to_helper(context, helper_wrmsr, HELPER_cares_about_rip | HELPER_might_change_rip | HELPER_might_crash);
                should_check_for_interrupts = 1;
            }break;
            
            case 0x132:{ // rdmsr
                emit_inst(0x8B, reg(8, ARG_REG_1, NONVOL_context));
                emit_inst(0x8B, reg(8, ARG_REG_2, NONVOL_registers));
                emit_call_to_helper(context, helper_rdmsr, HELPER_cares_about_rip | HELPER_might_change_rip | HELPER_might_crash);
            }break;
            
            case 0x131:{ // RDTSC
                //
                // "Reads the current value of the processors time-stamp counter (a 64-bit MSR) into the EDX:EAX registers."
                //
                
                // Increment 'ia32_tsc'
                //     mov rdx, qword [registers + .ia32_tsc]
                //     add rdx, RDTSC_INCREMENT
                //     mov qword [registers + .ia32_tsc], rdx
                //     
                // Load eax:edx with the resulting tsc.
                //     mov eax, edx
                //     shr rdx, 32
                emit(0x48, 0x8b, make_modrm(MOD_REGM_OFF32, REGISTER_D, NONVOL_registers)); emit32(offset_in_type(struct registers, ia32_tsc));
                emit(0x48, 0x81, make_modrm(MOD_REG, REG_OPCODE_add, REGISTER_D)); emit32(RDTSC_INCREMENT);
                emit(0x48, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_D, NONVOL_registers)); emit32(offset_in_type(struct registers, ia32_tsc));
                emit(0x8b, make_modrm(MOD_REG, REGISTER_A, REGISTER_D));
                emit(0x48, 0xC1, make_modrm(MOD_REG, 5, REGISTER_D), 32);
                
                // Write to the guest registers:
                emit_write_gpr(context, guest(REGISTER_A), host(REGISTER_A), 4, 0);
                emit_write_gpr(context, guest(REGISTER_D), host(REGISTER_D), 4, 0);
            }break;
            
            case 0x1a2:{ // cpuid
                
                // helper_cpuid(context, registers):
                //     mov arg1, context
                //     mov arg2, registers
                //     mov rax, helper_cpuid
                //     call rax
                emit_inst(0x8B, reg(8, ARG_REG_1, NONVOL_context));
                emit_inst(0x8B, reg(8, ARG_REG_2, NONVOL_registers));
                emit(0x48, 0xB8); emit64((u64)helper_cpuid);
                emit(0xff, make_modrm(MOD_REG, /*call*/2, REGISTER_A));
                
            }break;
            
            case 0x140: // CMOVO   r16/32/64 r/m16/32/64 - Conditional Move - overflow (OF=1)
            case 0x141: // CMOVNO  r16/32/64 r/m16/32/64 - Conditional Move - not overflow (OF=0)
            case 0x142: // CMOVC   r16/32/64 r/m16/32/64 - Conditional Move - below/not above or equal/carry (CF=1)
            case 0x143: // CMOVNC  r16/32/64 r/m16/32/64 - Conditional Move - not below/above or equal/not carry (CF=0)
            case 0x144: // CMOVZ   r16/32/64 r/m16/32/64 - Conditional Move - zero/equal (ZF=1)
            case 0x145: // CMOVNZ  r16/32/64 r/m16/32/64 - Conditional Move - not zero/not equal (ZF=0)
            case 0x146: // CMOVBE  r16/32/64 r/m16/32/64 - Conditional Move - below or equal/not above (CF=1 OR ZF=1)
            case 0x147: // CMOVNBE r16/32/64 r/m16/32/64 - Conditional Move - not below or equal/above (CF=0 AND ZF=0)
            case 0x148: // CMOVS   r16/32/64 r/m16/32/64 - Conditional Move - sign (SF=1)
            case 0x149: // CMOVNS  r16/32/64 r/m16/32/64 - Conditional Move - not sign (SF=0)
            case 0x14A: // CMOVP   r16/32/64 r/m16/32/64 - Conditional Move - parity/parity even (PF=1)
            case 0x14B: // CMOVNP  r16/32/64 r/m16/32/64 - Conditional Move - not parity/parity odd (PF=0)
            case 0x14C: // CMOVL   r16/32/64 r/m16/32/64 - Conditional Move - less/not greater (SF!=OF)
            case 0x14D: // CMOVNL  r16/32/64 r/m16/32/64 - Conditional Move - not less/greater or equal (SF=OF)
            case 0x14E: // CMOVLE  r16/32/64 r/m16/32/64 - Conditional Move - less or equal/not greater ((ZF=1) OR (SF!=OF))
            case 0x14F: // CMOVNLE r16/32/64 r/m16/32/64 - Conditional Move - not less nor equal/greater ((ZF=0) AND (SF=OF))
            {
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_C), regm, operand_size, rex);
                }else{
                    emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), operand_size, /*need_write_permission*/0);
                }
                
                emit_read_gpr(context, host(REGISTER_A), reg, 8, rex);
                
                emit_load_flags(context);
                
                // cmovcc rax, rcx
                if(operand_size == 2) emit(0x66);
                if(operand_size == 8) emit(0x48);
                emit(0x0f, opcode, make_modrm(MOD_REG, REGISTER_A, REGISTER_C));
                
                emit_write_gpr(context, reg, host(REGISTER_A), operand_size, rex);
            }break;
            
            case 0x190:  // seto   regm8
            case 0x191:  // setno  regm8
            case 0x192:  // setc   regm8
            case 0x193:  // setnc  regm8
            case 0x194:  // setz   regm8
            case 0x195:  // setnz  regm8
            case 0x196:  // setbe  regm8
            case 0x197:  // setnbe regm8
            case 0x198:  // sets   regm8
            case 0x199:  // setns  regm8
            case 0x19a:  // setp   regm8
            case 0x19b:  // setnp  regm8
            case 0x19c:  // setl   regm8
            case 0x19d:  // setnl  regm8
            case 0x19e:  // setle  regm8
            case 0x19f:{ // setnle regm8
                crash_assert(reg.encoding == 0, emit_jit_result); // These are all /0 for some reason.
                
                if(mod == MOD_REG){
                    emit_load_flags(context);
                    
                    // setcc byte ptr [registers + .regm]
                    emit(0x0f, opcode, make_modrm(MOD_REGM_OFF8, 0, NONVOL_registers), reg_offset(regm, 1, rex));
                }else{
                    // lea rdx, [context + .jit_scratch]
                    emit(0x48, 0x8D, make_modrm(MOD_REGM_OFF32, REGISTER_D, NONVOL_context)); emit32(offset_in_type(struct context, jit_scratch));
                    
                    emit_load_flags(context);
                    // setcc [rdx]
                    emit(0x0f, opcode, make_modrm(MOD_REGM, 0, REGISTER_D));
                    
                    emit_write_pointer(context, host(REGISTER_A), host(REGISTER_D), 1);
                }
            }break;
            
            case 0x1ac:  // SHRD regm, reg, imm8
            case 0x1a4:{ // SHLD regm, reg, imm8
                
                //
                // @note: If the shift is greater then the 'operand_size * 8' its undefined behavior.
                //        Because of the shift mask this can only happen if 'operand_size == 2',
                //        we prevent this here to get clean logs!
                if(operand_size == 2) imm8 &= 15;
                if(!imm8) break; // Otherwise it would change the flags.
                
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_A), regm,  operand_size, rex);
                }else{
                    // mov flex, rax ; address
                    emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), operand_size, /*need_write_permission*/1);
                }
                emit_read_gpr(context, host(REGISTER_C), reg,  operand_size, rex);
                
                if(operand_size == 2) emit(0x66);
                if(operand_size == 8) emit(0x48);
                emit(0x0f, opcode, make_modrm(MOD_REG, REGISTER_C, REGISTER_A), imm8);
                
                if(mod == MOD_REG){
                    emit_write_gpr(context, regm, host(REGISTER_A),  operand_size, rex);
                }else{
                    emit_write_host_register(context, host(NONVOL_flex), host(REGISTER_A), operand_size);
                }
            }break;
            
            case 0x1a3:  // bt  regm, reg
            case 0x1ab:  // bts regm, reg
            case 0x1b3:  // btr regm, reg
            case 0x1bb:{ // btc regm, reg
                
                if(mod == MOD_REG){
                    // Load the regm, because it has to do a modulo operation.
                    
                    emit_read_gpr(context, host(REGISTER_C), reg,  operand_size, rex);
                    emit_read_gpr(context, host(REGISTER_A), regm, operand_size, rex);
                    
                    emit_load_flags(context);
                    
                    // bt* rax, rcx
                    if(operand_size == 2) emit(0x66);
                    if(operand_size == 8) emit(0x48);
                    emit(0x0f, opcode, make_modrm(MOD_REG, REGISTER_C, REGISTER_A));
                    emit_destructively_update_flags(context, host(REGISTER_D));
                    
                    if(opcode != /*bt*/0xa3){
                        emit_write_gpr(context, regm, host(REGISTER_A), operand_size, rex);
                    }
                }else{
                    //
                    // "If the bit base operand specifies a memory location, the operand represents the address
                    //  of the byte in memory that contains the bit base (bit 0 of the specified byte)
                    //  of the bit string."
                    //
                    
                    // "When accessing a bit in memory, the processor may access 4 bytes starting from the memory 
                    //  address for a 32-bit operand size, using by the following relationship:
                    //    
                    //    Effective Address + (4 * (BitOffset / 32))."
                    // 
                    // Similarly, for 16-bit and 64-bit operands it accesses 2/8 bytes at
                    //   
                    //   16-bit: Effective Address + (2 * (BitOffset/16))
                    //   64-bit: Effective Address + (8 * (BitOffset/64)).
                    // 
                    
                    u32 bit_size_index;
                    _BitScanForward((unsigned long32 *)&bit_size_index, (operand_size * 8));
                    
                    u32 byte_size_index;
                    _BitScanForward((unsigned long32 *)&byte_size_index, operand_size);
                    
                    // 
                    // Compute the access base in rax.
                    //    mov rcx, [registers + .reg] ; BitOffset
                    //    shr rcx, log2(bit-size)
                    //    lea rax, [log2(bit-size) * rcx + rax]
                    // 
                    emit_read_gpr(context, host(REGISTER_C), reg, operand_size, rex);
                    emit(0x48, 0xC1, make_modrm(MOD_REG, 5, REGISTER_C), (u8)bit_size_index);
                    emit(0x48, 0x8D, make_modrm(MOD_REGM, REGISTER_A, REGISTER_SP), make_sib(byte_size_index, REGISTER_C, REGISTER_A));
                    
                    // Save the address in flex, because we might write later.
                    //      mov flex, rax
                    emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                    
                    // Read a byte from the dest, into rax.
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), operand_size, /*need_write_permission*/opcode != /*bt*/0xa3);
                    
                    // Calculate the bit in rdx. (@cleanup: We reload 'reg' here. maybe there is a better way?).
                    //    mov ecx, [registers + .reg]
                    //    and ecx, (bit_size-1)
                    //    mov edx, 1
                    //    shl edx, cl
                    emit_read_gpr(context, host(REGISTER_C), reg, 4, 0);
                    emit(0x83, make_modrm(MOD_REG, REG_OPCODE_and, REGISTER_C), (operand_size * 8)-1);
                    emit(0xB8 + REGISTER_D, 0x01, 0x00, 0x00, 0x00);
                    if(operand_size == 8) emit(0x48);
                    emit(0xD3, make_modrm(MOD_REG, 4, REGISTER_D));
                    
                    //
                    // At this point:
                    //     rax  = the value we read, need this to do a write.
                    //     rcx  = the bit index, we need this to compute CF.
                    //     rdx  = the bit mask, we need this to compute the value we write back.
                    //     flex = the guest_address we want to write to in the end.
                    //
                    
                    // We use r8 to hold the address (as that what 'emit_write_host_register' prefers)
                    // and use flex to calculate the bit-value.
                    //     mov r8, flex
                    emit_inst(0x8b, reg(8, REGISTER_R8, NONVOL_flex));
                    
                    // 
                    // Calculate the value of CF in 'flex'.
                    // 
                    //    mov flex, edx ; bit mask
                    //    and flex, eax ; value
                    //    shr flex, cl  ; bit index
                    
                    
                    emit_inst(0x8b, reg(operand_size, NONVOL_flex, REGISTER_D));
                    emit_inst(0x23, reg(operand_size, NONVOL_flex, REGISTER_A));
                    emit_inst(0xD3, reg(operand_size, /*shr*/5, NONVOL_flex));
                    
                    //
                    // Compute the value we should store back, in eax, edx contains the bitmask.
                    //
                    if(opcode == 0xab){ // bts
                        // or eax, edx
                        if(operand_size == 8) emit(0x48); 
                        emit(0x0b, make_modrm(MOD_REG, REGISTER_A, REGISTER_D));
                    }
                    
                    if(opcode == 0xb3){ // btr
                        // not edx
                        if(operand_size == 8) emit(0x48); 
                        emit(0xf7, make_modrm(MOD_REG, 2, REGISTER_D));
                        // and eax, edx
                        if(operand_size == 8) emit(0x48); 
                        emit(0x23, make_modrm(MOD_REG, REGISTER_A, REGISTER_D));
                    }
                    
                    if(opcode == 0xbb){ // btc
                        // xor eax, edx
                        if(operand_size == 8) emit(0x48); 
                        emit(0x33, make_modrm(MOD_REG, REGISTER_A, REGISTER_D));
                    }
                    
                    if(opcode != /*bt*/0xa3){
                        emit_write_host_register(context, host(REGISTER_R8), host(REGISTER_A), operand_size);
                    }
                    
                    //
                    // After all this, flex contains the value of CF we want to assign.
                    //
                    
                    // and byte ptr [registers + .eflags], ~CF
                    emit(0x80, make_modrm(MOD_REGM_OFF32, REG_OPCODE_and, NONVOL_registers));
                    emit32(offset_in_type(struct registers, rflags));
                    emit((u8)~FLAG_CF);
                    
                    // or dword ptr [registers + .eflags], flex
                    emit_inst(0x09, regm32(4, NONVOL_flex, NONVOL_registers)); emit32(offset_in_type(struct registers, rflags));
                }
            }break;
            
            case 0x1ae:{
                switch(reg.encoding){
                    case 0:{ // FXSAVE
                        if(mod == MOD_REG){
                            //
                            // RDFSBASE
                            //
                            
                            // mov ecx, size word [registers + .fs_base]
                            if(operand_size == 8) emit(0x48);
                            emit(0x8B, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, fs_base));
                            
                            emit_write_gpr(context, reg, host(REGISTER_C), operand_size, rex);
                        }else{
                            
                            // call the helper routine:
                            //     mov arg1, context
                            //     mov arg2, registers
                            //     mov arg3, rax ; guest_address
                            //     call fxsave_helper
                            emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                            emit_inst(0x8b, reg(8, ARG_REG_2, NONVOL_registers));
                            emit_inst(0x8b, reg(8, ARG_REG_3, REGISTER_A));
                            
                            emit_call_to_helper(context, fxsave_helper, HELPER_might_crash);
                        }
                    }break;
                    case 1:{
                        if(mod == MOD_REG){
                            //
                            // RDGSBASE
                            //
                            
                            // mov ecx, size word [registers + .gs_base]
                            if(operand_size == 8) emit(0x48);
                            emit(0x8B, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, gs_base));
                            
                            emit_write_gpr(context, reg, host(REGISTER_C), operand_size, rex);
                        }else{
                            // 
                            // FXRSTOR [mem]
                            // 
                            
                            // call the helper routine:
                            //     mov arg1, context
                            //     mov arg2, registers
                            //     mov arg3, rax ; guest_address
                            //     mov arg4, (operand_size == 8)
                            //     call fxrstor_helper
                            emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                            emit_inst(0x8b, reg(8, ARG_REG_2, NONVOL_registers));
                            emit_inst(0x8b, reg(8, ARG_REG_3, REGISTER_A));
                            emit_inst(0xc7, reg(8, /*mov*/0, ARG_REG_4)); emit32(operand_size == 8);
                            emit_call_to_helper(context, fxrstor_helper, HELPER_might_crash);
                            
                            // fldcw [registers + .fpucw]
                            emit(0xd9, make_modrm(MOD_REGM_OFF32, /*FLDCW*/5, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_control_word));
                        }
                    }break;
                    
                    case 2:{
                        if(mod == MOD_REG){
                            //
                            // WRFSBASE
                            //
                            emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), operand_size, /*need_write_permission*/0);
                            
                            // mov dword [registers + .fs_base], ecx
                            if(operand_size == 8) emit(0x48);
                            emit(0x89, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, fs_base));
                        }else{
                            //
                            // LDMXCSR
                            //
                            emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), operand_size, /*need_write_permission*/0);
                            
                            // mov dword [registers + .mxcsr], ecx
                            emit(0x89, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, mxcsr));
                            
#if JIT_EMULATE_MXCSR
                            // ldmxcsr [registers + .mxcsr]
                            emit(0x0f, 0xae, make_modrm(MOD_REGM_OFF32, /*ldmxcsr*/2, NONVOL_registers)); emit32(offset_in_type(struct registers, mxcsr));
#endif
                        }
                    }break;
                    case 3:{
                        if(mod == MOD_REG){
                            //
                            // WRGSBASE
                            //
                            emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), operand_size, /*need_write_permission*/0);
                            
                            // mov dword [registers + .gs_base], ecx
                            if(operand_size == 8) emit(0x48);
                            emit(0x89, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, gs_base));
                        }else{
                            //
                            // STMXCSR
                            //
                            
#if JIT_EMULATE_MXCSR
                            // stmxcsr [registers + .mxcsr]
                            emit(0x0f, 0xae, make_modrm(MOD_REGM_OFF32, /*ldmxcsr*/3, NONVOL_registers)); emit32(offset_in_type(struct registers, mxcsr));
#endif
                            
                            // mov ecx, dword [registers + .mxcsr]
                            emit(0x8b, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_registers)); emit32(offset_in_type(struct registers, mxcsr));
                            
                            emit_write_host_register(context, host(REGISTER_A), host(REGISTER_C), operand_size);
                        }
                    }break;
                    
                    // 4 = xsave
                    
                    case 5:{// XRSTOR / LFENCE
                        if(mod != MOD_REG){
                            // @cleanup: why do they use both xrstor and xrstors?
                            // call the helper routine:
                            //     mov arg1, context
                            //     mov arg2, registers
                            //     mov arg3, rax ; guest_address
                            //     call xrstors_helper
                            emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                            emit_inst(0x8b, reg(8, ARG_REG_2, NONVOL_registers));
                            emit_inst(0x8b, reg(8, ARG_REG_3, REGISTER_A));
                            emit_call_to_helper(context, xrstors_helper, HELPER_might_crash);
                        }
                    }break;
                    
                    
                    case 6:{ // MFENCE
                        if(mod != MOD_REG){
                            set_crash_information(context, CRASH_unimplemented_instruction, 0);
                        }
                    }break;
                    
                    case 7:{ // CLFLUSH (mod != MOD_REG) / SFENCE (mod == MOD_REG)
                        // @cleanup: CLFLUSH can #PF
                    }break;
                    crash_invalid_default_case("0f ae", emit_jit_result);
                    
                }
            }break;
            
            case 0x1af:{ // imul reg, regm
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_C), regm, operand_size, rex);
                }else{
                    emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), operand_size, /*need_write_permission*/0);
                }
                emit_read_gpr(context, host(REGISTER_A), reg, operand_size, rex);
                
                // imul rax, rcx
                if(operand_size == 2) emit(0x66);
                if(operand_size == 8) emit(0x48);
                emit(0x0F, opcode, make_modrm(MOD_REG, REGISTER_A, REGISTER_C));
                emit_destructively_update_flags(context, host(REGISTER_D));
                
                emit_write_gpr(context, reg, host(REGISTER_A), operand_size, rex);
            }break;
            
            case 0x1b0:  // cmpxchg regm8, al,  reg8
            case 0x1b1:{ // cmpxchg regm,  rax, reg
                
                if(opcode == 0xb0) operand_size = 1;
                
                // "Compares the value in the AL, AX, EAX, or RAX register with the first operand (destination operand).
                //  If the two values are equal, the second operand (source operand) is loaded into the destination operand.
                //  Otherwise, the destination operand is loaded into the AL, AX, EAX or RAX register.
                //  RAX register is available only in 64-bit mode."
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_D), regm, operand_size, rex);
                }else{
                    // Save the address in flex, because we might write later.
                    //      mov flex, rax
                    emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                    
                    emit_read_into_gpr(context, host(REGISTER_D), host(REGISTER_A), operand_size, /*need_write_permission*/1);
                }
                
                emit_read_gpr(context, host(REGISTER_A), guest(REGISTER_A), operand_size, rex);
                emit_read_gpr(context, host(REGISTER_C), reg,               operand_size, rex);
                
                // cmpxchg rdx, rax, rcx
                if(operand_size == 2) emit(0x66);
                if(operand_size == 8) emit(0x48);
                emit(0x0f, opcode, make_modrm(MOD_REG, REGISTER_C, REGISTER_D));
                
                // Save the flags and the 'destination' in the case that it failed.
                emit_destructively_update_flags(context, host(REGISTER_R9));
                emit_write_gpr(context, guest(REGISTER_A), host(REGISTER_A), operand_size, rex);
                
                if(mod == MOD_REG){
                    emit_write_gpr(context, regm, host(REGISTER_D), operand_size, rex);
                }else{
                    // @cleanup: we could get rid of this mov rax, rdx
                    emit(0x48, 0x8b, make_modrm(MOD_REG, REGISTER_A, REGISTER_D));
                    emit_write_host_register(context, host(NONVOL_flex), host(REGISTER_A), operand_size);
                }
            }break;
            
            case 0x1be:  // movsx reg, regm8
            case 0x1bf:  // movsx reg, regm16
            case 0x1b6:  // movzx reg, regm8
            case 0x1b7:{ // movzx reg, regm16
                u8 size = 1 + (opcode & 1);
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_A), regm, size, rex);
                }else{
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), size, /*need_write_permission*/0);
                }
                
                // The read was zero-extended, so if we should sign extend, do!
                if(opcode == 0xbe || opcode == 0xbf){
                    if(operand_size == 2) emit(0x66);
                    if(operand_size == 8) emit(0x48);
                    emit(0x0f, opcode, make_modrm(MOD_REG, REGISTER_A, REGISTER_A));
                }
                
                emit_write_gpr(context, reg, host(REGISTER_A), operand_size, rex);
            }break;
            
            case 0x1b8:{ // popcnt reg, regm
                crash_assert(legacy_prefix_flags == MANDATORY_PREFIX_F3, emit_jit_result);
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_A), regm, operand_size, rex);
                }else{
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), operand_size, /*need_write_permission*/0);
                }
                emit_read_gpr(context, host(REGISTER_C), reg, operand_size, rex);
                
                emit(0xf3);
                if(operand_size == 2) emit(0x66);
                if(operand_size == 8) emit(0x48);
                emit(0x0f, 0xb8, make_modrm(MOD_REG, REGISTER_C, REGISTER_A));
                
                emit_write_gpr(context, reg, host(REGISTER_C), operand_size, rex);
            }break;
            
            case 0x1ba:{ // bt* regm, imm8
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_A), regm, operand_size, rex);
                }else{
                    // Save the address in flex, because we might write later.
                    //      mov flex, rax
                    emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                    emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), operand_size, /*need_write_permission*/(reg.encoding != 4));
                }
                
                emit_load_flags(context);
                // bt* rax, imm8
                if(operand_size == 2) emit(0x66);
                if(operand_size == 8) emit(0x48);
                emit(0x0f, opcode, make_modrm(MOD_REG, reg.encoding, REGISTER_A), imm8);
                emit_destructively_update_flags(context, host(REGISTER_D));
                
                if(reg.encoding != 4){
                    if(mod == MOD_REG){
                        emit_write_gpr(context, regm, host(REGISTER_A), operand_size, rex);
                    }else{
                        emit_write_host_register(context, host(NONVOL_flex), host(REGISTER_A), operand_size);
                    }
                }
            }break;
            
            case 0x1bc:  // bsf/tzcnt reg, regm
            case 0x1bd:{ // bsr/lzcnt reg, regm
                crash_assert(legacy_prefix_flags == 0 || legacy_prefix_flags == MANDATORY_PREFIX_66 || legacy_prefix_flags == MANDATORY_PREFIX_F3, emit_jit_result);
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_C), regm, operand_size, rex);
                }else{
                    emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), operand_size, /*need_write_permission*/0);
                }
                
                // op rax, rcx
                if(legacy_prefix_flags & MANDATORY_PREFIX_F3) emit(0xF3);
                if(operand_size == 2) emit(0x66);
                if(operand_size == 8) emit(0x48);
                emit(0x0F, opcode, make_modrm(MOD_REG, REGISTER_A, REGISTER_C));
                
                u8 *end_jump = null;
                if(legacy_prefix_flags == 0){
                    emit(0x74); end_jump = emit_get_current(context); emit(0);
                }
                
                // @note: Only write if it is not undefined.
                emit_write_gpr(context, reg, host(REGISTER_A), operand_size, rex);
                
                if(legacy_prefix_flags == 0){
                    *end_jump = (u8)(emit_get_current(context) - (end_jump + 1));
                }
                
                emit_destructively_update_flags(context, host(REGISTER_D));
            }break;
            
            case 0x1c0:  // xadd regm8, reg8
            case 0x1c1:{ // xadd regm, reg
                if(opcode == 0xc0) operand_size = 1;
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_C), regm, operand_size, rex);
                }else{
                    // Save the address in flex, because we might write later.
                    //      mov flex, rax
                    emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                    emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), operand_size, /*need_write_permission*/1);
                }
                
                emit_read_gpr(context, host(REGISTER_A), reg, operand_size, rex);
                
                // xadd rcx, rax
                if(operand_size == 2) emit(0x66);
                if(operand_size == 8) emit(0x48);
                emit(0x0f, opcode, make_modrm(MOD_REG, REGISTER_A, REGISTER_C));
                emit_destructively_update_flags(context, host(REGISTER_D));
                
                if(mod == MOD_REG){
                    emit_write_gpr(context, regm, host(REGISTER_C), operand_size, rex);
                }else{
                    // Use an xchg to save the value we have to store in 'reg'.
                    //     xchg flex, rax
                    if(NONVOL_flex >= 8) emit(0x48 | REXB, 0x90 + (NONVOL_flex & 7));
                    else emit(0x48, 0x90 + NONVOL_flex);
                    
                    // First try to write.
                    emit_write_host_register(context, host(REGISTER_A), host(REGISTER_C), operand_size);
                    
                    // If the write succeeds, also write the register.
                    emit_write_gpr(context, reg, host(NONVOL_flex), operand_size, rex);
                }
            }break;
            
            case 0x1c7:{
                switch(reg.encoding){
                    case 1:{ // cmpxchg8b/cmpxchg16b
                        crash_assert(mod != MOD_REG && operand_size == 8, emit_jit_result);
                        
                        // @cleanup: Maybe the easier solution would have been to read into the temp buffer and then just to cmpxchg16b.
                        
                        
                        // "The CF, PF, AF, SF, and OF flags are unaffected."
                        // "Compare RDX:RAX with m128. If equal, set ZF and load RCX:RBX into m128. Else, clear ZF and load m128 into RDX:RAX"
                        
                        // Save the address in flex.
                        //      mov flex, rax
                        emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                        
                        // Load the low qword into rax.
                        emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), 8, /*need_write_permission*/1);
                        
                        // Compare the low qword with rax.
                        //     cmp rax, [registers + .rax]
                        //     jnz failure
                        emit(0x48, 0x3b, make_modrm(MOD_REGM, REGISTER_A, NONVOL_registers));
                        emit(0x75);
                        u8 *patch_failure_byte1 = emit_get_current(context); emit(0);
                        
                        // Add 8 to flex, to get to the high qword.
                        //     add flex, 8
                        emit_inst(0x83, reg(8, REG_OPCODE_add, NONVOL_flex), 0x08);
                        
                        // Load the high qword into rax.
                        emit_read_into_gpr(context, host(REGISTER_A), host(NONVOL_flex), 8, /*need_write_permission*/1);
                        
                        // Compare the high qword with rdx.
                        //      cmp rax, [registers + .rdx]
                        //      jnz failure
                        emit(0x48, 0x3b, make_modrm(MOD_REGM_OFF8, REGISTER_A, NONVOL_registers), REGISTER_D * 8);
                        emit(0x75);
                        u8 *patch_failure_byte2 = emit_get_current(context); emit(0);
                        
                        //
                        // We have verified that [rdx:rax] == m128, write [rcx:rbx] to it.
                        //
                        emit_write_guest_register(context, host(NONVOL_flex), guest(REGISTER_C), 8, 0);
                        
                        // Sub 8 to flex, to get to the low qword.
                        //      sub flex, 8
                        emit_inst(0x83, reg(8, REG_OPCODE_sub, NONVOL_flex), 0x08);
                        
                        emit_write_guest_register(context, host(NONVOL_flex), guest(REGISTER_B), 8, 0);
                        
                        // Set the zero flag.
                        emit(0x83, make_modrm(MOD_REGM_OFF32, REG_OPCODE_or, NONVOL_registers));  emit32(offset_in_type(struct registers, rflags)); emit(FLAG_ZF);
                        
                        // jmp end
                        emit(0xEB);
                        u8 *success_end_patch = emit_get_current(context); emit(0);
                        
                        // failure:
                        u8 *failure_byte2 = emit_get_current(context);
                        *patch_failure_byte2 = (u8)(failure_byte2 - (patch_failure_byte2 + 1));
                        
                        // If we failed on the second byte the 'flex' was incremented, undo this.
                        //     sub flex, 8
                        emit_inst(0x83, reg(8, REG_OPCODE_sub, NONVOL_flex), 0x08);
                        
                        u8 *failure_byte1 = emit_get_current(context);
                        *patch_failure_byte1 = (u8)(failure_byte1 - (patch_failure_byte1 + 1));
                        
                        //
                        // The operation almost never failes, so we just re-read the values here.
                        // "clear ZF and load m128 into RDX:RAX".
                        //
                        
                        // Clear the zero flag.
                        emit(0x83, make_modrm(MOD_REGM_OFF32, REG_OPCODE_and, NONVOL_registers));  emit32(offset_in_type(struct registers, rflags)); emit((u8)~FLAG_ZF);
                        
                        // Load the low qword into rax.
                        emit_read_into_gpr(context, host(REGISTER_A), host(NONVOL_flex), 8, /*need_write_permission*/0);
                        emit_write_gpr(context, guest(REGISTER_A), host(REGISTER_A), 8, 0);
                        
                        // Add 8 to flex, to get to the high qword.
                        //     add flex, 8
                        emit_inst(0x83, reg(8, REG_OPCODE_add, NONVOL_flex), 0x08);
                        
                        // Load the low qword into rax.
                        emit_read_into_gpr(context, host(REGISTER_A), host(NONVOL_flex), 8, /*need_write_permission*/0);
                        emit_write_gpr(context, guest(REGISTER_D), host(REGISTER_A), 8, 0);
                        
                        // end:
                        u8 *end = emit_get_current(context);
                        *success_end_patch = (u8)(end - (success_end_patch + 1));
                    }break;
                    
                    case 3:{ // xrstors
                        // call the helper routine:
                        //     mov arg1, context
                        //     mov arg2, registers
                        //     mov arg3,  rax ; guest_address
                        //     call xrstors_helper
                        emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                        emit_inst(0x8b, reg(8, ARG_REG_2, NONVOL_registers));
                        emit_inst(0x8b, reg(8, ARG_REG_3, REGISTER_A));
                        emit_call_to_helper(context, xrstors_helper, HELPER_might_crash);
                        
                        // fldcw [registers + .fpucw]
                        emit(0xd9, make_modrm(MOD_REGM_OFF32, /*FLDCW*/5, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_control_word));
                    }break;
                    
                    case 4: case 5:{ // xsaves/xsavec
                        // call the helper routine:
                        //     mov arg1, context
                        //     mov arg2, registers
                        //     mov arg3, rax ; guest_address
                        //     call xsaves_helper
                        emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                        emit_inst(0x8b, reg(8, ARG_REG_2, NONVOL_registers));
                        emit_inst(0x8b, reg(8, ARG_REG_3, REGISTER_A));
                        emit_call_to_helper(context, xsaves_helper, HELPER_might_crash);
                        
                        // fldcw [registers + .fpucw]
                        emit(0xd9, make_modrm(MOD_REGM_OFF32, /*FLDCW*/5, NONVOL_registers)); emit32(offset_in_type(struct registers, fpu_control_word));
                    }break;
                    
                    case 0x6: case 0x7:{ // rdrand/rdseed
                        crash_assert(mod == MOD_REG, emit_jit_result);
                        
                        // mov arg1, context
                        // mov arg2, registers
                        // mov arg3, operand_size
                        // mov arg4  regm
                        emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                        emit_inst(0x8b, reg(8, ARG_REG_2, NONVOL_registers));
                        emit_inst(0xC7, reg(8, 0, ARG_REG_3)); emit32(operand_size);
                        emit_inst(0xC7, reg(8, 0, ARG_REG_4)); emit32(regm.encoding);
                        
                        emit_call_to_helper(context, rdrand_helper, HELPER_simple_call);
                    }break;
                    crash_invalid_default_case("0f c7", emit_jit_result);
                }
            }break;
            
            case 0x1c8: case 0x1c9: case 0x1ca: case 0x1cb: case 0x1cc: case 0x1cd: case 0x1ce: case 0x1cf:{ // bswap + reg
                struct guest_register bswap_reg = guest((opcode - 0xc8) | ((rex & REXB) ? 8 : 0));
                
                emit_read_gpr(context, host(REGISTER_A), bswap_reg, operand_size, rex);
                
                // bswap rax
                if(operand_size == 2) emit(0x66);
                if(operand_size == 8) emit(0x48);
                emit(0x0f, 0xc8);
                
                emit_write_gpr(context, bswap_reg, host(REGISTER_A), operand_size, rex);
            }break;
            
            case 0x177:{ 
                crash_assert(vex, emit_jit_result);
                
                if(vex & VEXL){
                    // 
                    // vzeroall
                    // 
                    
                    // vxorps YMM0, YMM0, YMM0
                    emit(0xc5, make_vex(0, REGISTER_XMM0, 1, 1), 0x57, make_modrm(MOD_REG, REGISTER_XMM0, REGISTER_XMM0));
                    
                    // lea rax, [registers + .xmm0_high]
                    emit(0x48, 0x8d, make_modrm(MOD_REGM_OFF32, REGISTER_A, NONVOL_registers)); emit32(offset_in_type(struct registers, simd));
                    
                    for(u32 reg_index = 0; reg_index < 16; reg_index++){
                        // vmovups [rax], ymm0
                        emit(0xc5, make_vex(0, 0, 1, 1), 0x11, make_modrm(MOD_REGM, REGISTER_XMM0, REGISTER_A));
                        
                        // add rax, 32
                        emit(0x48, 0x83, 0xC0, 0x20);
                    }
                }else{
                    // 
                    // vzeroupper
                    // 
                    
                    // xorps xmm0, xmm0
                    emit(0x0F, 0x57, 0xC0);
                    
                    // lea rax, [registers + .xmm0_high]
                    emit(0x48, 0x8d, make_modrm(MOD_REGM_OFF32, REGISTER_A, NONVOL_registers)); emit32(offset_in_type(struct registers, simd) + 0x10);
                    
                    for(u32 reg_index = 0; reg_index < 16; reg_index++){
                        // movups [rax], xmm0
                        emit(0x0F, 0x11, 0x00);
                        
                        // add rax, 32
                        emit(0x48, 0x83, 0xC0, 0x20);
                    }
                }
            }break;
            
            // 
            // @sigh: @cleanup: 
            // There are sadly movq xmm, qword [mem], instruction with REX.W in the windows kernel.
            // From what I can tell it makes no sense to put REX.W in there. (maybe alignment?)
            // But it tricks my decoder, which does not match because of REX.W missmatch and then 
            // matches even though the 0xf3 prefix is present...
            // Because of this we have to implement the instruction manually.
            // 
            case 0x17e:{ // movd / movq
                crash_assert(legacy_prefix_flags == MANDATORY_PREFIX_66 || legacy_prefix_flags == MANDATORY_PREFIX_F3, emit_jit_result);
                
                if(legacy_prefix_flags == MANDATORY_PREFIX_66){
                    if(operand_size == 2) operand_size = 4;
                    // 66 0F 7E /r VMOVD r32/m32, xmm1 AVX    Move doubleword from xmm1 register to r/m32.
                    // 66 0F 7E /r VMOVQ r64/m64, xmm1 AVX    Move quadword from xmm1 register to r/m64.
                    
                    emit_read_xmm_register(context, host(REGISTER_XMM0), reg, vex);
                    
                    // movd/movq size ptr rax, xmm/mm
                    if(vex){
                        crash_assert(!(vex & VEXL), emit_jit_result);
                        if(operand_size == 8){
                            emit(0xc4, make_two_byte_vex(0, 0, 0, 1, 1, 0, 0, vex & 3), 0x7e, make_modrm(MOD_REG, REGISTER_XMM0, REGISTER_C));
                        }else{
                            emit(0xc5, make_vex(0, 0, 0, vex & 3), 0x7e, make_modrm(MOD_REG, REGISTER_XMM0, REGISTER_C));
                        }
                    }else{
                        emit(0x66);
                        if(operand_size == 8) emit(0x48);
                        emit(0x0f, 0x7e, make_modrm(MOD_REG, REGISTER_XMM0, REGISTER_C));
                    }
                    
                    if(mod == MOD_REG){
                        emit_write_gpr(context, regm, host(REGISTER_C), operand_size, 0);
                    }else{
                        emit_write_host_register(context, host(REGISTER_A), host(REGISTER_C), operand_size);
                    }
                }else if(legacy_prefix_flags == MANDATORY_PREFIX_F3){
                    crash_assert(!vex, emit_jit_result);
                    // F3 0F 7E /r MOVQ xmm1, xmm2/m64 SSE2 Move quadword from xmm2/mem64 to xmm1.
                    //
                    // @note: I dont get how this is xmm2/m64?
                    //        I am going to cheese it for now.
                    
                    if(mod == MOD_REG){
                        emit_read_xmm_register(context, host(REGISTER_XMM0), regm, vex);
                        
                        // movq xmm0, xmm0 (no idear what this does...?)
                        emit(0xf3, 0x0f, opcode, make_modrm(MOD_REG, REGISTER_XMM0, REGISTER_XMM0));
                    }else{
                        emit_read_into_gpr(context, host(REGISTER_A), host(REGISTER_A), 8, /*need_write_permission*/0);
                        
                        // mov qword [context + .jit_scratch], rax
                        emit(0x48, 0x89, make_modrm(MOD_REGM_OFF32, REGISTER_A, NONVOL_context)); emit32(offset_in_type(struct context, jit_scratch));
                        
                        // movq xmm0, qword [context + .jit_scratch]
                        emit(0xf3, 0x0f, opcode, make_modrm(MOD_REGM_OFF32, REGISTER_XMM0, NONVOL_context)); emit32(offset_in_type(struct context, jit_scratch));
                    }
                    emit_write_xmm_register(context, reg, host(REGISTER_XMM0), vex);
                    
                }else invalid_code_path();
            }break;
            
            case 0x282:{ // INVPCID r32, m128
                // helper_invlpg(context, address):
                //     mov  arg1, context
                //     mov  arg2, address(rax)
                //     call helper_invlpg
                emit_inst(0x8B, reg(8, ARG_REG_1, NONVOL_context));
                emit_inst(0x8B, reg(8, ARG_REG_2, REGISTER_A));
                emit_call_to_helper(context, helper_invlpg, HELPER_simple_call);
            }break;
            
            // @note: this uses flags / edx, so we currently have to implemented manually.
            case 0x2f6:{
                crash_assert(!(vex & VEXL), emit_jit_result);
                
                // 66       0F 38    F6 /r ADCX r32,        r/m32 ADX  Unsigned addition of r32 with CF, r/m32 to r32, writes CF.
                // 66 REX.w 0F 38    F6 /r ADCX r64,        r/m64 ADX  Unsigned addition of r64 with CF, r/m64 to r64, writes CF.
                // F3       0F 38    F6 /r ADOX r32,        r/m32 ADX  Unsigned addition of r32 with OF, r/m32 to r32, writes OF.
                // F3 REX.w 0F 38    F6 /r ADOX r64,        r/m64 ADX  Unsigned addition of r64 with OF, r/m64 to r64, writes OF.
                // VEX.LZ.F2.0F38.W0 F6 /r MULX r32a, r32b, r/m32 BMI2 Unsigned multiply of r/m32 with EDX without affecting arithmetic flags.
                // VEX.LZ.F2.0F38.W1 F6 /r MULX r64a, r64b, r/m64 BMI2 Unsigned multiply of r/m64 with RDX without affecting arithmetic flags.
                
                if(operand_size == 2) operand_size = 4;
                
                if(mod == MOD_REG){
                    emit_read_gpr(context, host(REGISTER_C), regm, operand_size, rex);
                }else{
                    emit_read_into_gpr(context, host(REGISTER_C), host(REGISTER_A), operand_size, /*need_write_permission*/0);
                }
                
                emit_read_gpr(context, host(REGISTER_A), reg, operand_size, rex);
                
                
                if(vex){
                    // MULX
                    emit_read_gpr(context, host(REGISTER_D), guest(REGISTER_D), operand_size, rex);
                }else{
                    // ADCX, ADOX
                    emit_load_flags(context);
                }
                
                if(vex){
                    // op rax, rcx
                    emit_read_gpr(context, host(REGISTER_R8), vex_reg, operand_size, 0);
                    
                    emit(0xc4, make_two_byte_vex(0, 0, 0, multibyte_mode, (operand_size == 8), REGISTER_R8, 0, vex & 3), opcode, make_modrm(MOD_REG, REGISTER_A, REGISTER_C));
                    
                    emit_write_gpr(context, vex_reg, host(REGISTER_R8), operand_size, 0);
                }else{
                    // op rax, rcx
                    emit_simd_prefix(context, legacy_prefix_flags);
                    if(operand_size == 8) emit(0x48);
                    emit(0x0f, 0x38, opcode, make_modrm(MOD_REG, REGISTER_A, REGISTER_C));
                }
                
                if(!vex){
                    // ADCX, ADOX
                    emit_destructively_update_flags(context, host(REGISTER_D));
                }
                
                emit_write_gpr(context, reg, host(REGISTER_A), operand_size, rex);
            }break;
            
            case 0x34a:{
                crash_assert(vex && legacy_prefix_flags == MANDATORY_PREFIX_66, emit_jit_result);
                // 66 4A /r /is4 VBLENDVPS xmm1, xmm2, xmm3/m128, xmm4    RVMR    V/V    AVX    Conditionally copy single-precision floating-point values from xmm2 or xmm3/m128 to xmm1, based on mask bits in the specified mask operand, xmm4.
                // 66 4A /r /is4 VBLENDVPS ymm1, ymm2, ymm3/m256, ymm4    RVMR    V/V    AVX    Conditionally copy single-precision floating-point values from ymm2 or ymm3/m256 to ymm1, based on mask bits in the specified mask register, ymm4.
                struct guest_register imm_reg = guest(((u8)imm8 >> 4));
                
                if(mod == MOD_REG){
                    emit_read_xmm_register(context, host(REGISTER_XMM2), regm, vex);
                }else{
                    emit_read_into_xmm(context, host(REGISTER_XMM2), host(REGISTER_A), legacy_prefix_flags, vex, /*need_write_permission*/0);
                }
                
                emit_read_xmm_register(context, host(REGISTER_XMM1), vex_reg, vex);
                emit_read_xmm_register(context, host(REGISTER_XMM0), reg, vex);
                emit_read_xmm_register(context, host(REGISTER_XMM3), imm_reg, vex);
                
                emit(0xc4, make_two_byte_vex(0, 0, 0, multibyte_mode, 0, REGISTER_XMM1, (vex >> 2) & 1, vex & 3), opcode, make_modrm(MOD_REG, REGISTER_XMM0, REGISTER_XMM2), (u8)REGISTER_XMM3);
                
                emit_write_xmm_register(context, reg, host(REGISTER_XMM0), vex);
            }break;
            
            case 0x363:{ // PCMPISTRI rcx, xmm1, xmm2/m128, imm8
                crash_assert(!(vex & VEXL) && legacy_prefix_flags == MANDATORY_PREFIX_66, emit_jit_result);
                
                if(mod == MOD_REG){
                    emit_read_xmm_register(context, host(REGISTER_XMM1), regm, vex);
                }else{
                    emit_read_into_xmm(context, host(REGISTER_XMM1), host(REGISTER_A), legacy_prefix_flags, vex, /*need_write_permission*/0);
                }
                
                emit_read_xmm_register(context, host(REGISTER_XMM0), reg, vex);
                
                if(vex){
                    // op xmm0, xmm1, imm8
                    emit(0xc4, make_two_byte_vex(0, 0, 0, multibyte_mode, 0, 0, (vex >> 2) & 1, vex & 3), opcode, make_modrm(MOD_REG, REGISTER_XMM0, REGISTER_XMM1), imm8);
                }else{
                    // op xmm0, xmm1, imm8
                    emit(0x66, 0x0f, 0x3A, opcode, make_modrm(MOD_REG, REGISTER_XMM0, REGISTER_XMM1), imm8);
                }
                emit_destructively_update_flags(context, host(REGISTER_A));
                
                // the result is in RCX
                emit_write_gpr(context, guest(REGISTER_C), host(REGISTER_C), 4, 0);
            }break;
            
            default:{
                
#define PRINT_DEFAULT_CASE_INFORMATION 0
                
#if PRINT_DEFAULT_CASE_INFORMATION
                print("default case: ");
                print_disassembly_for_buffer(context, instruction_rip, instruction, 16);
                print("\n");
                u8 *default_case_start = emit_get_current(context);
#endif
                
                
                // 
                // In the default case, we use the 'instruction_table.h' to compile jit code.
                // Here, we only handle _simple_ instructions, i.e. no side effects, no special
                // registers, etc.
                // 
                struct instruction_table_entry *instructions = normal_instructions;
                smm amount_of_instructions = array_count(normal_instructions);
                u16 *instruction_table = normal_instruction_table;
                
                if(vex){
                    instructions = vex_instructions;
                    amount_of_instructions = array_count(vex_instructions);
                    instruction_table = vex_instruction_table;
                }
                
                try_again_because_there_might_have_been_an_unnecessary_rexw:;
                
                u16 instruction_index = instruction_table[augmented_opcode];
                if(instruction_index == 0xffff){
                    set_crash_information(context, CRASH_internal_error, (u64)"Instruction has invalid index in instruction_table.");
                    goto jit_default_case_possibly_print_instruction;
                }
                
                int instruction_has_modrm = !instruction_has_no_modrm[augmented_opcode];
                
                int unhandled_instruction = 0;
                for(; instruction_index < amount_of_instructions; instruction_index++){
                    
                    struct instruction_table_entry entry = instructions[instruction_index];
                    if((u32)entry.extended_opcode != augmented_opcode){
                        unhandled_instruction = 1;
                        break;
                    }
                    
                    //
                    // In the table we *first* have the prefixed instructions, then the one without a prefix.
                    //
                    if(entry.legacy_prefix_f2 && !(legacy_prefix_flags & MANDATORY_PREFIX_F2)) continue;
                    if(entry.legacy_prefix_f3 && !(legacy_prefix_flags & MANDATORY_PREFIX_F3)) continue;
                    if(entry.legacy_prefix_66 && !(legacy_prefix_flags & MANDATORY_PREFIX_66)) continue;
                    
                    if(entry.rex_W != ((rex & REXW) != 0)) continue;
                    
                    if(entry.regm_only && mod == MOD_REG) continue;
                    if(entry.vex_L != ((vex & VEXL) != 0)) continue; // @cleanup: evex needs 2 bits for vex_L.
                    
                    if(instruction_has_modrm){
                        if(entry.modrm_opcode != -1 && entry.modrm_opcode != modrm) continue;
                        if((entry.reg_opcode < 8) && entry.reg_opcode != (reg.encoding & 7)) continue;
                    }
                    
                    //
                    // We have found our instruction!
                    // We will handle it below to reduce scoping!
                    //
                    break;
                }
                
                if(unhandled_instruction){
                    
                    if(rex & REXW){ // @cleanup: we should maybe handle this in the table, maybe not...?
                        rex &= ~REXW;
                        goto try_again_because_there_might_have_been_an_unnecessary_rexw;
                    }
                    
                    set_crash_information(context, CRASH_internal_error, (u64)"Unable to find instruction in instruction table in emit_jit_for_instruction.");
                    goto jit_default_case_possibly_print_instruction;
                }
                
                // 
                // We have found the instruction.
                // 
                struct instruction_table_entry inst = instructions[instruction_index];
                
                if(instruction_has_modrm){
                    // 
                    // If we have a memory operand, and it is flagged as 'OPERAND_FLAG_read',
                    // we have to load that *first*, as we will use volatile registers to store 
                    // the other operands, i.e:
                    // 
                    //     'emit_read_into_temp_buffer_and_return_pointer_in_rax'
                    //     <load other registers>
                    //     op other, registers, [rax]
                    //     <store other registers>
                    // 
                    // If we have a memory operand, and it is flagged as 'OPERAND_FLAG_write',
                    // we will just write to it in the end, i.e:
                    // 
                    //     lea NONVOL_flex, [rsp + temp_buffer]
                    //     <load other registers>
                    //     op [flex], other, registers
                    //     <store other registers>
                    //     emit_write_pointer(guest=rax, host=flex)
                    // 
                    // If we have a memory operand, and it is flagged as both 'OPERAND_FLAG_read'
                    // and 'OPERAND_FLAG_write', we have to save the guest address into the 'NONVOL_flex'
                    // and do a combination of the two:
                    // 
                    //     mov NONVOL_flex, rax
                    //     'emit_read_into_temp_buffer_and_return_pointer_in_rax'
                    //     <load other registers>
                    //     op [rax], other, registers
                    //     <store other registers>
                    //     emit_write_pointer(guest=flex, host=rax)
                    // 
                    
                    enum register_encoding volatile_gprs[4] = {
                        REGISTER_C,
                        REGISTER_D,
                        REGISTER_R8,
                        REGISTER_R9,
                    };
                    int volatile_gpr_index = 0;
                    
                    enum register_encoding volatile_xmms[4] = {
                        // @note: do not use XMM0, as it is sometimes used as an implicit arguement.
                        REGISTER_XMM1,
                        REGISTER_XMM2,
                        REGISTER_XMM3,
                        REGISTER_XMM4,
                    };
                    int volatile_xmm_index = 0;
                    
                    int memory_operand_size  = -1;
                    int memory_operand_index = -1;
                    enum register_encoding host_regm   = INVALID_REGISTER;
                    enum register_encoding address_reg = REGISTER_A;
                    
                    if(mod != MOD_REG){
                        
                        for(u32 operand_index = 0; operand_index < inst.amount_of_operands; operand_index++){
                            enum operand_kind  kind  = inst.operands[operand_index].kind;
                            enum operand_flags flags = inst.operands[operand_index].flags;
                            
                            switch((int)kind){
                                case OPERAND_regm8:  memory_operand_size = 1; break;
                                case OPERAND_regm16: memory_operand_size = 2; break;
                                case OPERAND_regm32: memory_operand_size = 4; break;
                                case OPERAND_regm64: memory_operand_size = 8; break;
                                
                                case OPERAND_regm8_zero_extended:  memory_operand_size = 1; break;
                                case OPERAND_regm16_zero_extended: memory_operand_size = 2; break;
                                
                                case OPERAND_xmmm8:   memory_operand_size =  1; break;
                                case OPERAND_xmmm16:  memory_operand_size =  2; break;
                                case OPERAND_xmmm32:  memory_operand_size =  4; break;
                                case OPERAND_xmmm64:  memory_operand_size =  8; break;
                                case OPERAND_xmmm128: memory_operand_size = 16; break;
                                case OPERAND_ymmm256: memory_operand_size = 32; break;
                                
                                case OPERAND_m8:   memory_operand_size =  1; break;
                                case OPERAND_m16:  memory_operand_size =  2; break;
                                case OPERAND_m32:  memory_operand_size =  4; break;
                                case OPERAND_m64:  memory_operand_size =  8; break;
                                case OPERAND_m128: memory_operand_size = 16; break;
                                case OPERAND_m256: memory_operand_size = 32; break;
                                
                            }
                            
                            if(memory_operand_size != -1){
                                memory_operand_index = operand_index;
                                
                                if(flags & OPERAND_FLAG_read){
                                    
                                    if(flags & OPERAND_FLAG_write){
                                        // mov flex, rax ; address
                                        emit_inst(0x8b, reg(8, NONVOL_flex, REGISTER_A));
                                        address_reg = NONVOL_flex;
                                    }
                                    
                                    emit_read_into_temp_buffer_and_return_pointer_in_rax(context, host(REGISTER_A), (u8)memory_operand_size, (flags & OPERAND_FLAG_write) != 0);
                                    host_regm = REGISTER_A;
                                }else{
                                    // lea rcx, [context + .jit_scratch]
                                    emit(0x48, 0x8D, make_modrm(MOD_REGM_OFF32, REGISTER_C, NONVOL_context)); emit32(offset_in_type(struct context, jit_scratch));
                                    volatile_gpr_index = 1;
                                    
                                    host_regm = REGISTER_C;
                                }
                                
                                break;
                            }
                        }
                        
                        if(memory_operand_index == -1){
                            // 
                            // MOD indicates we have a memory operand, but we could not find it.
                            // 
                            set_crash_information(context, CRASH_internal_error, (u64)"Instruction has mod != MOD_REG but no memory operand inside emit_jit_for_instruction.");
                            goto jit_default_case_possibly_print_instruction;
                        }
                    } 
                    
                    // 
                    // Load all non-memory operands marked 'OPERAND_FLAG_read' into registers.
                    // 
                    
                    enum register_encoding host_reg     = INVALID_REGISTER;
                    enum register_encoding host_vex_reg = 0; // often times this is reserved and must be 0b1111, but it gets inverted by the vex macro.
                    
                    for(int operand_index = 0; operand_index < inst.amount_of_operands; operand_index++){
                        
                        // 
                        // @note: The memory operand is handled separately.
                        //        If there is no memory operand the value is -1.
                        //        Which will never get hit.
                        if(operand_index == memory_operand_index) continue;
                        
                        enum operand_kind  kind  = inst.operands[operand_index].kind;
                        enum operand_flags flags = inst.operands[operand_index].flags;
                        
                        
                        switch(kind){
                            case OPERAND_reg8:{
                                host_reg = volatile_gprs[volatile_gpr_index++];
                                if(flags & OPERAND_FLAG_read) emit_read_gpr(context, host(host_reg), reg, 1, rex);
                            }break;
                            
                            case OPERAND_reg16:{
                                host_reg = volatile_gprs[volatile_gpr_index++];
                                if(flags & OPERAND_FLAG_read) emit_read_gpr(context, host(host_reg), reg, 2, rex);
                            }break;
                            case OPERAND_reg32:{
                                host_reg = volatile_gprs[volatile_gpr_index++];
                                if(flags & OPERAND_FLAG_read) emit_read_gpr(context, host(host_reg), reg, 4, rex);
                            }break;
                            case OPERAND_reg64:{
                                host_reg = volatile_gprs[volatile_gpr_index++];
                                if(flags & OPERAND_FLAG_read) emit_read_gpr(context, host(host_reg), reg, 8, rex);
                            }break;
                            
                            case OPERAND_xmm:
                            case OPERAND_ymm:{
                                host_reg = volatile_xmms[volatile_xmm_index++];
                                if(flags & OPERAND_FLAG_read) emit_read_xmm_register(context, host(host_reg), reg, vex);
                            }break;
                            
                            
                            case OPERAND_vex_reg32:{
                                host_vex_reg = volatile_gprs[volatile_gpr_index++];
                                if(flags & OPERAND_FLAG_read) emit_read_gpr(context, host(host_vex_reg), vex_reg, 4, rex);
                            }break;
                            case OPERAND_vex_reg64:{
                                host_vex_reg = volatile_gprs[volatile_gpr_index++];
                                if(flags & OPERAND_FLAG_read) emit_read_gpr(context, host(host_vex_reg), vex_reg, 8, rex);
                            }break;
                            
                            case OPERAND_vex_xmm:
                            case OPERAND_vex_ymm:{
                                host_vex_reg = volatile_xmms[volatile_xmm_index++];
                                if(flags & OPERAND_FLAG_read) emit_read_xmm_register(context, host(host_vex_reg), vex_reg, vex);
                            }break;
                            
                            case OPERAND_regm8_zero_extended:
                            case OPERAND_regm8:{
                                host_regm = volatile_gprs[volatile_gpr_index++];
                                if(flags & OPERAND_FLAG_read) emit_read_gpr(context, host(host_regm), regm, 1, rex);
                            }break;
                            
                            case OPERAND_regm16_zero_extended:
                            case OPERAND_regm16:{
                                host_regm = volatile_gprs[volatile_gpr_index++];
                                if(flags & OPERAND_FLAG_read) emit_read_gpr(context, host(host_regm), regm, 2, rex);
                            }break;
                            case OPERAND_regm32:{
                                host_regm = volatile_gprs[volatile_gpr_index++];
                                if(flags & OPERAND_FLAG_read) emit_read_gpr(context, host(host_regm), regm, 4, rex);
                            }break;
                            case OPERAND_regm64:{
                                host_regm = volatile_gprs[volatile_gpr_index++];
                                if(flags & OPERAND_FLAG_read) emit_read_gpr(context, host(host_regm), regm, 8, rex);
                            }break;
                            
                            case OPERAND_xmmm8:
                            case OPERAND_xmmm16:
                            case OPERAND_xmmm32:
                            case OPERAND_xmmm64:
                            case OPERAND_xmmm128:
                            case OPERAND_ymmm256:{
                                host_regm = volatile_xmms[volatile_xmm_index++];
                                if(flags & OPERAND_FLAG_read) emit_read_xmm_register(context, host(host_regm), regm, vex);
                            }break;
                            
                            case OPERAND_xmm0:{
                                crash_assert(!(flags & OPERAND_FLAG_write), emit_jit_result);
                                emit_read_xmm_register(context, host(REGISTER_XMM0), guest(REGISTER_XMM0), vex);
                            }break;
                            
                            case OPERAND_imm8:{
                                // do nothing.
                            }break;
                            
                            default:{
                                set_crash_information(context, CRASH_internal_error, (u64)"Unhandled operand kind in default case of emit_jit_for_instruction.");
                            }break;
                        }
                        
                        assert(volatile_xmm_index <= (int)array_count(volatile_xmms));
                        assert(volatile_gpr_index <= (int)array_count(volatile_gprs));
                    }
                    
                    // 
                    // Emit the instruction.
                    // 
                    if(vex){
                        if(multibyte_mode != 1 || (rex & REXW)){
                            emit(0xc4, make_two_byte_vex((host_reg >= 8), 0, (host_regm >= 8), multibyte_mode, (rex & REXW) != 0, host_vex_reg, (vex & VEXL) != 0, (vex & 3)));
                        }else{
                            emit(0xc5, make_vex((host_reg >= 8), host_vex_reg, (vex & VEXL) != 0, (vex & 3)));
                        }
                        
                        emit(opcode);
                    }else{
                        emit_simd_prefix(context, legacy_prefix_flags);
                        
                        int rex_to_emit = (rex & REXW) | ((host_reg >= 8) ? REXR : 0) | ((host_regm >= 8) ? REXB : 0);
                        if(rex_to_emit) emit((u8)(0x40 | rex_to_emit));
                        
                        if(multibyte_mode == 1) emit(0x0f);
                        if(multibyte_mode == 2) emit(0x0f, 0x38);
                        if(multibyte_mode == 3) emit(0x0f, 0x3a);
                        emit(opcode);
                    }
                    
                    if(inst.reg_opcode < 8){
                        crash_assert(host_reg == INVALID_REGISTER, emit_jit_result);
                        host_reg = inst.reg_opcode;
                    }
                    
                    crash_assert(host_reg  != INVALID_REGISTER, emit_jit_result);
                    crash_assert(host_regm != INVALID_REGISTER, emit_jit_result);
                    
                    // 
                    // We set up the 'host_regm' to be correct for both memory operands and 
                    // register operands.
                    // 
                    
                    emit(make_modrm((mod != MOD_REG) ? MOD_REGM : MOD_REG, host_reg, host_regm));
                    
                    if(immediate_size){
                        emit_bytes(context, (u8 *)&immediate, immediate_size);   
                    }
                    
                    // 
                    // Write out all the registers marked 'OPERAND_FLAG_write'.
                    // 
                    
                    for(int operand_index = 0; operand_index < inst.amount_of_operands; operand_index++){
                        
                        // 
                        // @note: The memory operand is handled separately.
                        //        If there is no memory operand the value is -1.
                        //        Which will never get hit.
                        if(operand_index == memory_operand_index) continue;
                        
                        enum operand_kind  kind  = inst.operands[operand_index].kind;
                        enum operand_flags flags = inst.operands[operand_index].flags;
                        if(!(flags & OPERAND_FLAG_write)) continue;
                        
                        switch(kind){
                            case OPERAND_reg8:{
                                emit_write_gpr(context, reg, host(host_reg), 1, rex);
                            }break;
                            
                            case OPERAND_reg16:{
                                emit_write_gpr(context, reg, host(host_reg), 2, rex);
                            }break;
                            case OPERAND_reg32:{
                                emit_write_gpr(context, reg, host(host_reg), 4, rex);
                            }break;
                            case OPERAND_reg64:{
                                emit_write_gpr(context, reg, host(host_reg), 8, rex);
                            }break;
                            
                            case OPERAND_xmm:
                            case OPERAND_ymm:{
                                emit_write_xmm_register(context, reg, host(host_reg), vex);
                            }break;
                            
                            case OPERAND_vex_reg32:{
                                emit_write_gpr(context, vex_reg, host(host_vex_reg), 4, rex);
                            }break;
                            case OPERAND_vex_reg64:{
                                emit_write_gpr(context, vex_reg, host(host_vex_reg), 8, rex);
                            }break;
                            
                            case OPERAND_vex_xmm:
                            case OPERAND_vex_ymm:{
                                emit_write_xmm_register(context, vex_reg, host(host_vex_reg), vex);
                            }break;
                            
                            case OPERAND_regm8_zero_extended:
                            case OPERAND_regm8:{
                                emit_write_gpr(context, regm, host(host_regm), 1, rex);
                            }break;
                            
                            case OPERAND_regm16_zero_extended:
                            case OPERAND_regm16:{
                                emit_write_gpr(context, regm, host(host_regm), 2, rex);
                            }break;
                            case OPERAND_regm32:{
                                emit_write_gpr(context, regm, host(host_regm), 4, rex);
                            }break;
                            case OPERAND_regm64:{
                                emit_write_gpr(context, regm, host(host_regm), 8, rex);
                            }break;
                            
                            case OPERAND_xmmm8:
                            case OPERAND_xmmm16:
                            case OPERAND_xmmm32:
                            case OPERAND_xmmm64:
                            case OPERAND_xmmm128:
                            case OPERAND_ymmm256:{
                                emit_write_xmm_register(context, regm, host(host_regm), vex);
                            }break;
                            
                            default:{
                                set_crash_information(context, CRASH_internal_error, (u64)"Unhandled operand kind in default case of emit_jit_for_instruction.");
                            }break;
                        }
                        
                        assert(volatile_xmm_index <= (int)array_count(volatile_xmms));
                        assert(volatile_gpr_index <= (int)array_count(volatile_gprs));
                    }
                    
                    
                    if((mod != MOD_REG) && (inst.operands[memory_operand_index].flags & OPERAND_FLAG_write)){
                        // 
                        // Write out the memory operand. Its host memory address is contained in 'host_regm'.
                        // The guest address is contained in the 'address_reg'.
                        // 
                        emit_write_pointer(context, host(address_reg), host(host_regm), (u8)memory_operand_size);
                    }
                }else{
                    set_crash_information(context, CRASH_internal_error, (u64)"Instruction has no modrm.");
                }
                
                jit_default_case_possibly_print_instruction:;
                
                if(globals.debugger_mode && context->crash){
                    print("\n\n");
                    print("%p: JIT default case crash: ", instruction_rip);
                    print_disassembly_for_buffer(context, 0, instruction, 16);
                    print(" (raw: ");
                    for(u32 index = 0; index < instruction_size; index++){
                        print("%.2x ", (u8)instruction[index]);
                    }
                    print(")\n");
                    print("\n");
                    
                    handle_debugger(context);
                }
                
#if PRINT_DEFAULT_CASE_INFORMATION
                u8 *end = emit_get_current(context);
                print("Generated jit:\n");
                for(u8 *at = default_case_start; at < end; ){
                    print("    ");
                    smm size = end - beginning_of_the_jit;
                    at += print_disassembly_for_buffer(context, (u64)at, at, (u32)size);
                    print("\n");
                }
#endif
            }break;
        }
        
        if(jump_patch){
            
            // 
            // We ended in a conditional jump. Conditional jumps are always rip-relative.
            // We are in the branch taken case, rip has already been adjusted.
            // 
            
            assert(conditional_branch_rip);
            
            if((instruction_rip & ~0xfff) == (conditional_branch_rip & ~0xfff)){
                emit_patchable_jit_exit_for_jump_within_page(context, instruction_rip, BRANCH_taken);
            }else{
                emit_patchable_jit_exit(context, instruction_rip, BRANCH_taken);
            }
            
            u8 *end = emit_get_current(context);
            u8 *start = jump_patch + 1;
            assert((s8)(end - start) == end - start);
            *jump_patch = (s8)(end - start);
            
            // 
            // We are in the branch not taken case, add the rip.
            // 
            //    add nonvol_rip, imm8
            emit(0x48 | REXB, 0x83, make_modrm(MOD_REG, REG_OPCODE_add, NONVOL_rip), (u8)instruction_size);
            
            if((instruction_rip & ~0xfff) == ((instruction_rip + instruction_size) & ~0xfff)){
                emit_patchable_jit_exit_for_jump_within_page(context, instruction_rip, BRANCH_not_taken);
            }else{
                emit_patchable_jit_exit(context, instruction_rip, BRANCH_not_taken);
            }
            
            is_terminating_instruction = 1;
        }else{
            
            // 
            // @cleanup: Currently, we only do these post-instruction things if the instruction is not in conditional jump.
            //           Technically, the sti instruction might cause us to have to `check_for_interrupts` after a conditional branch.
            // 
            
            if(should_check_for_interrupts){
                
                // Call check for interrupts and exit the jit if one was delivered.
                //     mov arg1, context
                //     mov arg2, registers
                //     call check_for_interrupts
                
                emit_inst(0x8b, reg(8, ARG_REG_1, NONVOL_context));
                emit_inst(0x8b, reg(8, ARG_REG_2, NONVOL_registers));
                emit_call_to_helper(context, check_for_interrupts, HELPER_cares_about_rip | HELPER_might_change_rip | HELPER_do_not_print);
            }
            
            if(context->jit_skip_one_breakpoint && instruction_rip == initial_rip){
                // Reset the 'jit_skip_one_breakpoint' only after the first instruction of the first block has been executed.
                // Future blocks will not go into this code path, as we will first execute this and hence the value will be reset.
                // 
                //      mov [context + .jit_skip_one_breakpoint], 0
                //      
                emit(0xC7, make_modrm(MOD_REGM_OFF32, 0, NONVOL_context)); emit32(offset_in_type(struct context, jit_skip_one_breakpoint)); emit32(0);
            }
            
            if(instruction_byte == /*sti*/0xfb){
                // 
                // If the instructions was STI, we should check after the _next_ instruction, 
                // not after the current one, because of the _interrupt shadow_.
                // This also means the next instruction needs to be part of this jit-block.
                // 
                should_check_for_interrupts = 1;
                assert(globals.single_stepping || is_terminating_instruction == 0);
                is_terminating_instruction = 0;
            }
            
            if(is_unconditional_jump){
                is_terminating_instruction = 1;
                
                emit_patchable_jit_exit(context, 0, BRANCH_unconditional);
            }else{
                //
                // Update the rip, and jump to the next instruction.
                //
                //    add nonvol_rip, imm8
                emit(0x48 | REXB, 0x83, make_modrm(MOD_REG, REG_OPCODE_add, NONVOL_rip), (u8)instruction_size);
            }
        }
        
        instruction_rip += instruction_size;
        
        if(false){
            // 
            // For debugging purposes, put the instruction we emit code for
            // in a disabled block just after the code we emit.
            // 
            emit(0xeb, (u8)instruction_size); 
            emit_bytes(context, instruction, instruction_size);
        }
    }
    
    if(!is_terminating_instruction || globals.single_stepping){
        emit_patchable_jit_exit(context, 0, BRANCH_unconditional);
    }
    
#if VTUNE_JIT_PROFILING
    if(globals.fuzzing){
        char buffer[0x100];
        snprintf(buffer, sizeof(buffer), "block@%p\n", initial_rip);
        iJIT_Method_Load jit = {0};
        jit.method_id = iJIT_GetNewMethodID();
        jit.method_name = buffer;
        jit.method_load_address = beginning_of_the_jit;
        jit.method_size = (u32)(emit_get_current(context) - (u8 *)jit.method_load_address);
        iJIT_NotifyEvent(iJVM_EVENT_TYPE_METHOD_LOAD_FINISHED, (void*)&jit);
    }
#endif
    
    emit_jit_result.jit_code = beginning_of_the_jit;
    emit_jit_result.block_start_rip = initial_rip;
    emit_jit_result.block_end_rip   = instruction_rip;
    return emit_jit_result;
}

void handle_instruction_cache_miss(struct context *context, struct instruction_cache_entry *instruction_cache_entry, u64 instruction_rip, u64 physical_rip){
    
    if((context->jit_block_table.amount_of_entries + 1) > (context->jit_block_table.maximal_size_minus_one >> 1)){
        u64 new_capacity = (context->jit_block_table.maximal_size_minus_one + 1) << 1;
        struct jit_block *new_entries = push_data(&context->permanent_arena, struct jit_block, new_capacity);
        
        for(u64 old_table_index = 0; old_table_index <= context->jit_block_table.maximal_size_minus_one; old_table_index++){
            struct jit_block *old_jit_block = context->jit_block_table.entries + old_table_index;
            if(!old_jit_block->jit_code) continue;
            
            u64 hash = old_jit_block->physical_rip;
            xor_shift(&hash);
            
            for(u64 new_table_index = 0; new_table_index < new_capacity; new_table_index++){
                struct jit_block *new_jit_block = new_entries + ((hash + new_table_index) & (new_capacity - 1));
                if(new_jit_block->jit_code) continue;
                
                *new_jit_block = *old_jit_block;
                break;
            }
        }
        
        context->jit_block_table.maximal_size_minus_one = new_capacity - 1;
        context->jit_block_table.entries = new_entries;
    }
    
    u64 index = 0;
    u64 hash = physical_rip;
    xor_shift(&hash);
    
    for(u64 table_index = 0; table_index <= context->jit_block_table.maximal_size_minus_one; table_index++){
        index = (hash + table_index) & context->jit_block_table.maximal_size_minus_one;
        
        struct jit_block *jit_block = &context->jit_block_table.entries[index];
        
        // break if we could not find any entry with the correct 
        if(!jit_block->jit_code) break;
        
        if(jit_block->physical_rip == physical_rip){
            instruction_cache_entry->instruction_jit = jit_block->jit_code;
            instruction_cache_entry->physical_rip = jit_block->physical_rip;
            return;
        }
    }
    
    struct emit_jit_result emit_jit_result = emit_jit(context, instruction_rip);
    if(!emit_jit_result.jit_code){
        assert(context->crash);
        return;
    }
    
    struct jit_block *jit_block = &context->jit_block_table.entries[index];
    context->jit_block_table.amount_of_entries += 1;
    
    assert(jit_block->jit_code == null);
    
    _bittestandset((void *)context->physical_memory_executed, (u32)(physical_rip/0x1000)); // set the bit to indicate we have executed this page.
    clear_specific_physical_address_from_write_tlb(context, physical_rip >> 12);
    
    jit_block->jit_code     = emit_jit_result.jit_code;
    jit_block->physical_rip = physical_rip;
    
    instruction_cache_entry->instruction_jit = emit_jit_result.jit_code;
    instruction_cache_entry->physical_rip    = physical_rip;
    
    if((emit_jit_result.block_start_rip & ~0xfff) != ((emit_jit_result.block_end_rip-1) & ~0xfff)){
        // :AccessedBitsForInstructionBlockRip
        // Make sure to pass 'PERMISSION_none' when looking up the 'second_page',
        // to avoid setting accessed bits unnecessarily.
        u64 physical_second_page = translate_rip_to_physical(context, (instruction_rip + 0x1000) & ~0xfff, PERMISSION_none);
        _bittestandset((void *)context->physical_memory_executed, (u32)(physical_second_page/0x1000)); // set the bit to indicate we have executed this page.
        clear_specific_physical_address_from_write_tlb(context, physical_second_page >> 12);
    }
    
    
    if(0){
        for(u64 address = instruction_rip; address < emit_jit_result.block_end_rip; ){
            u8 instruction[16];
            prefetch_instruction(context, address, instruction, sizeof(instruction));
            
            print("%p: ", address);
            u32 instruction_size = print_disassembly_for_buffer(0, instruction_rip, instruction, 16);
            
            print("   (raw: ");
            for(u32 i = 0; i < instruction_size; i++){
                print("%2.2x ", instruction[i]);
            }
            print(")\n");
            
            address += instruction_size;
        }
        
        u8 *end = emit_get_current(context);
        
        print("Generated jit:\n");
        for(u8 *at = emit_jit_result.jit_code; at < end; ){
            print("    ");
            smm size = end - emit_jit_result.jit_code;
            at += print_disassembly_for_buffer(0, instruction_rip, at, (u32)size);
            print("\n");
        }
        
        print("%p\n", physical_rip);
    }
}

struct crash_information jit_execute_until_exception(struct context *context){
    
    context->crash         = CRASH_none;
    context->crash_address = 0;
    
    struct registers *registers = &context->registers;
    
    u64 last_page_index = (registers->rip >> 12);
    u64 physical_rip = translate_rip_to_physical(context, registers->rip, PERMISSION_execute);
    u8 *patchable_jit_exit_address = null;
    
    // If we get into the loop and should be single stepping, get into the debugger here.
    if(globals.print_trace){
        print_registers(context, globals.trace_file);
    }else if(globals.single_stepping){
        handle_debugger(context); 
        initialize_jit(context); // :reset_jit_after_handle_debugger
    }
    
    do{
        
        // @cleanup: If we flushed the address space and the rip is now on the same virtual address
        //           pointing to a different physical address, this will not do the correct thing.
        // @note: In the future, we might want to get rid of caching 'last_page_index', 
        //        once we patch page-internal jumps, because then we would expect this condition 
        //        to be usually false.
        if(last_page_index != (registers->rip >> 12)){
            u64 last_rip = registers->rip;
            last_page_index = (last_rip >> 12);
            
            // :AccessedBitsForInstructionBlockRip
            // Here we do want to pass 'PERMISSION_execute' otherwise we would not ever set the 
            // accessed bits for the executed page. In theory, this probably sets the accessed
            // bits a _bit_ too late, but I don't think that'll ever matter.
            physical_rip = translate_rip_to_physical(context, registers->rip, PERMISSION_execute);
            if(physical_rip == (u64)-1){
                
                // 
                // We have hit an invalid 'registers->rip', this usually means a page fault,
                // but it could be an invalid address, we put a hook on.
                // For the latter case, we look up the hook here and execute it.
                // 
                
                struct hook *hook = lookup_hook(registers->rip);
                
                if(hook){
                    hook->hook(context, registers);
                    
                    if(context->crash) break;
                    if(registers->rip != last_rip) continue;
                    
                }else{
                    set_crash_information(context, CRASH_execute, registers->rip);
                    break;
                }
            }
        }else{
            physical_rip = (physical_rip & ~0xfff) | (registers->rip & 0xfff);
        }
        
        //
        // Lookup the instruction in the 'instruction_cache', this is just a fast, linear lookup by the physical rip.
        //
        static_assert((array_count(context->instruction_cache) & (array_count(context->instruction_cache) - 1)) == 0); // Needs to be a power of two, so we can user '&' instead of %.
        struct instruction_cache_entry *instruction_cache_entry = &context->instruction_cache[physical_rip & (array_count(context->instruction_cache) - 1)];
        
        if(instruction_cache_entry->physical_rip != physical_rip){
            
            //
            // We do not have this instruction in our cache, this could means we have to decode the instructions
            // and possibly generate new jit-snippets.
            //
            
            context->skip_setting_permission_bits += 1;
            handle_instruction_cache_miss(context, instruction_cache_entry, registers->rip, physical_rip);
            context->skip_setting_permission_bits -= 1;
            
            //
            // If we crashed, this means there were invalid/unimplemented instructions or a page fault occurred.
            //
            if(context->crash) break;
        }
        
        assert(context->skip_setting_permission_bits == 0);
        
#if !DISABLE_TAILCALL_OPTIMIZTIONS
        if(!globals.print_trace && patchable_jit_exit_address){
            if(*patchable_jit_exit_address == 0x48){
                struct patchable_jit_exit *patchable_jit_exit = (void *)patchable_jit_exit_address;
                
                // Patch up the last entry, because we now know where it is supposed to jump.
                patchable_jit_exit->saved_physical = physical_rip;
                
                u8 *jump_to   = instruction_cache_entry->instruction_jit;
                u8 *jump_from = (u8 *)(patchable_jit_exit + 1);
                
                patchable_jit_exit->success = (s32)(jump_to - jump_from);
            }else{
                assert(*patchable_jit_exit_address == 0xe9);
                
                struct patchable_jit_exit_for_jump_within_page *patchable_jit_exit = (void *)patchable_jit_exit_address;
                
                u8 *jump_to   = instruction_cache_entry->instruction_jit;
                u8 *jump_from = (u8 *)(patchable_jit_exit + 1);
                
                patchable_jit_exit->rel32 = (s32)(jump_to - jump_from);
            }
        }
#endif
        
        //
        // Enter the jit.
        // 
        patchable_jit_exit_address = (*context->jit_entry)(context, registers, instruction_cache_entry);
        
        if(globals.debugger_mode){
            
            int should_reset = 1;
            
            if(context->crash == CRASH_enter_debugger){
                // We hit some kind of breakpoint.
                handle_debugger(context);
                context->crash = CRASH_none;
            }else if(snapshot_mode_should_break_in_debugger){
                // If the user CTRL-C'ed break in the debugger.
                handle_debugger(context);
                snapshot_mode_should_break_in_debugger = 0;
            }else if(globals.print_trace){
                // If we are single stepping because of 'print_trace',
                // print the registers, but do not break in the debugger.
                print_registers(context, globals.trace_file);
                should_reset = 0;
            }else if(globals.single_stepping){
                // We are single stepping (this could also mean we just hit a breakpoint).
                handle_debugger(context);
            }else{
                should_reset = 0;
            }
            
            // :reset_jit_after_handle_debugger
            // 
            // Whenever we entered the debugger, reset the jit.
            // This makes sure that the jit is always up to date with the breakpoints.
            // We could somehow reset less, but I think the complexity is not worth the
            // speed improvement.
            if(should_reset){
                initialize_jit(context);
                patchable_jit_exit_address = 0;
            }
        }
        
        if(context->crash == CRASH_reset_jit){
            
            if(CRASH_ON_SELF_MODIFYING_CODE_DURING_FUZZING && globals.fuzzing){
                set_crash_information(context, CRASH_internal_error, (u64)"Would be resetting the jit.");
                break;
            }
            
            initialize_jit(context);
            context->crash = CRASH_none;
            patchable_jit_exit_address = 0;
        }
        
#if 0
        {   // Some dumb stats, this only works if there is only one thread.
            static u64 start_timeout, last_timeout;
            static double start_time;
            static double last_time;
            if(last_timeout == 0){
                start_timeout = last_timeout = context->fuzz_case_timeout;
                start_time    = last_time    = os_get_time_in_seconds();
            }
            
            u64 instructions_executed = context->fuzz_case_timeout - last_timeout;
            if(instructions_executed > 400ull * 1000 * 1000){
                last_timeout = context->fuzz_case_timeout;
                
                double time = os_get_time_in_seconds();
                
                if(time - last_time > 1){
                    last_time = time;
                    print("mips = %f\n", (start_timeout - last_timeout) / ((time - start_time) * 1000000.0));
                }
            }
        }
#endif
        
        //
        // Once we returned from the jit, there are two possibilities,
        //     1) we ended in an instruction miss. Therefore, we have to redo the loop, now with a new and improved 'rip' value.
        //     2) we ended in a crash. Thus 'context->crash' is set and we exit from this loop.
    } while(context->crash == CRASH_none);
    
    struct crash_information ret = {
        .crash_type    = context->crash,
        .crash_address = context->crash_address,
    };
    
    return ret;
}

struct crash_information start_execution_jit(struct context *context){
    
    if(context->registers.rip == 0 || address_is_non_canonical(context->registers.rip)){
        // @note: We return an internal error here instead of asserting, 
        //        as that will give the user a .crash-file, which they can reproduce 
        //        and diagnos the issue. We only spam in 'debugger_mode', not sure if that is the right choice.
        set_crash_information(context, CRASH_internal_error, (u64)"Invalid initial rip.");
        if(globals.debugger_mode) print("[" __FUNCTION__ "] Invalid initial rip %p.\n", context->registers.rip);
        return context->crash_information;
    }
    
    // For simplicity, if we are not fuzzing, we don't care about the performance of entering the jit,
    // so we make sure the jit is up-to-date by resetting it here.
    if(!globals.fuzzing) initialize_jit(context);
    
    struct crash_information result;
    
    while(true){
        
        result = jit_execute_until_exception(context);
        
        if(result.crash_type >= CRASH_exception_count) break;
        
        if(result.crash_type == CRASH_execute && result.crash_address == DEFAULT_RETURN_RIP){
            //
            // We succeeded to execute what we wanted!
            // 
            result.crash_type = CRASH_none;
            context->crash    = CRASH_none;
            context->registers.rsp -= 8; // Avoid rsp wandering off because of the return.
            return result;
        }
        
        if(PRINT_EXECUTION_EVENTS || PRINT_INTERRUPT_EVENTS){
            u64 pid = 0;
            char *image_name = get_image_name(context, (char[16]){0}, &pid);
            
            print("\n\n**** EXCEPTION (%s %p '%.16s' %p) ****\n", crash_type_string[result.crash_type], result.crash_address, image_name, pid);
            print_stack_trace(context);
            
            print_registers(context, stdout);
        }
        
        u64 previous_rip = context->registers.rip;
        
        if(result.crash_type == CRASH_non_canonical){
            deliver_exception_or_interrupt(context, /*#GP*/0xd, /*have_error_code*/1, /*error_code*/0);
        }else if(result.crash_type == CRASH_divide){
            deliver_exception_or_interrupt(context, /*#DE*/0, /*have_error_code*/0, /*error_code*/0);
        }else{
            
            // Page fault!
            
            //
            // Certain Interrupts (such as this one) also have a status:
            //
            
            //  31              15                             4               0
            // +---+--  --+---+-----+---+--  --+---+----+----+---+---+---+---+---+
            // |   Reserved   | SGX |   Reserved   | SS | PK | I | R | U | W | P |
            // +---+--  --+---+-----+---+--  --+---+----+----+---+---+---+---+---+
            // P - Present           - The Page was present in the page table.
            // W - Write             - The Page fault was caused by a write access.
            // U - User              - When set, the page fault was caused while CPL = 3.
            // R - Reserved Write    - The Page table has reserved bits set.
            // I - Instruction Fetch - The Page fault was caused by an instruction fetch.
            // PK, SS, SGX           - Unsupported.
            
            u64 pte = 0;
            translate_page_number_to_physical(context, result.crash_address >> 12, 0, &pte);
            
            u32 error_code = 0;
            
            if(pte & PAGE_TABLE_present)           error_code |= /*Present*/(1 << 0);
            if(result.crash_type == CRASH_write)   error_code |= /*Write*/  (1 << 1);
            if(context->registers.cs.selector & 3) error_code |= /*User*/   (1 << 2);
            if(result.crash_type == CRASH_execute) error_code |= /*Fetch*/  (1 << 4);
            
            context->registers.cr2 = result.crash_address;
            deliver_exception_or_interrupt(context, /*#PF*/0xe, /*have_error_code*/1, error_code);
        }
        
        if(previous_rip == context->registers.rip){
            // @note: this should probably never happen.
            set_crash_information(context, CRASH_internal_error, (u64)"Double Crash.");
            break;
        }
    }
    
    if(result.crash_type == CRASH_bugcheck){
        //
        // @note: 'hook_bugcheck' does already pop the return address into 'registers.rip'.
        //
        struct registers registers = context->registers;
        
        if((u32)registers.rcx == /*KMODE_EXCEPTION_NOT_HANDLED*/0x1E && (u32)registers.rdx == /*STATUS_ACCESS_VIOLATION*/0xC0000005){
            
            //
            // ExceptionRecord = ExceptionPointers->ExceptionRecord;
            // KeBugCheckEx(BugCheckCode,
            //             (longlong)ExceptionRecord->ExceptionCode,
            //             (ULONG_PTR)ExceptionRecord->ExceptionAddress,
            //             (ULONG_PTR)ExceptionRecord,
            //             (ULONG_PTR)ExceptionPointers->ContextRecord);
            //
            
            // EXCEPTION_ACCESS_VIOLATION - ExceptionInformation
            //   "The first element of the array contains a read-write flag that indicates the type of operation
            //    that caused the access violation. If this value is zero, the thread attempted to read the inaccessible data.
            //    If this value is 1, the thread attempted to write to an inaccessible address.
            //    If this value is 8, the thread causes a user-mode data execution prevention (DEP) violation."
            u64 flags   = guest_read(u64, registers.r9 + 0x20);
            u64 address = guest_read(u64, registers.r9 + 0x28);
            
            enum crash_type crash_type = CRASH_read;
            if(flags & 1) crash_type = CRASH_write;
            if(flags & 8) crash_type = CRASH_execute;
            result.crash_type = crash_type;
            result.crash_address = address;
            
        }else if((u32)registers.rcx == /*PAGE_FAULT_IN_NONPAGED_AREA*/0x50){
            
            result.crash_address = registers.rdx;
            
            u32 access_type = (u32)registers.r8;
            
            enum crash_type crash_type = CRASH_bugcheck;
            if(access_type == 0)  crash_type = CRASH_read;
            if(access_type == 2)  crash_type = CRASH_write;
            if(access_type == 10) crash_type = CRASH_execute;
            
            result.crash_type = crash_type;
        }
    }
    
    if(result.crash_type == CRASH_unhandled_exception){
        // We are at ntdll!RtlUserThreadStart$filt$0, with rcx = _EXCEPTION_POINTERS;
        
        u64 ExceptionRecord = guest_read(u64, context->registers.rcx + 0);
        // u64 ContextRecord   = guest_read(u64, registers.rcx + 8);
        u32 ExceptionCode = guest_read(u32, ExceptionRecord + 0);
        
        if(ExceptionCode == /*STATUS_ACCESS_VIOLATION*/0xC0000005){
            
            // EXCEPTION_ACCESS_VIOLATION - ExceptionInformation
            //   "The first element of the array contains a read-write flag that indicates the type of operation
            //    that caused the access violation. If this value is zero, the thread attempted to read the inaccessible data.
            //    If this value is 1, the thread attempted to write to an inaccessible address.
            //    If this value is 8, the thread causes a user-mode data execution prevention (DEP) violation."
            u64 flags   = guest_read(u64, ExceptionRecord + 0x20);
            u64 address = guest_read(u64, ExceptionRecord + 0x28);
            
            enum crash_type crash_type = CRASH_read;
            if(flags & 1) crash_type = CRASH_write;
            if(flags & 8) crash_type = CRASH_execute;
            result.crash_type = crash_type;
            result.crash_address = address;
        }
    }
    
    if(result.crash_type == CRASH_read && result.crash_address < 0x1000){
        result.crash_type = CRASH_read_null;
    }
    
    if(result.crash_type == CRASH_write && result.crash_address < 0x1000){
        result.crash_type = CRASH_write_null;
    }
    
    int should_print_stack_trace = 0;
    
#if ENTER_DEBUGGER_MODE_ON_CRASHES_PRE_FUZZING
    if(!globals.fuzzing && result.crash_type){
        should_print_stack_trace = 1;
    }
#endif
    
    if(should_print_stack_trace || (globals.debugger_mode && result.crash_type && result.crash_type != CRASH_timeout)){
        print_crash_information(context, &result);
        
        handle_debugger(context);
    }
    
    return result;
}

#undef guest
#undef host

