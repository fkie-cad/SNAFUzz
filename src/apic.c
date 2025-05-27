
// The Advanced Programmable Interrupt Controller or APIC.
//
// The APIC has two parts:
//     1) A local APIC for each core.
//     2) A I/O APIC for each peripheral bus.
// The local APIC receives interrupts from the I/O APIC.
//
// Each local APIC consists of a set of APIC registers. The APIC registers are memory mapped.
// Local Apics can receive interrupts from
//     1) I/O Devices
//     2) Inter Processor Interrupts (IPIs)
//     3) APIC timer generated interrupts
//     4) Performance monitoring counter interrupts
//     5) Thermal Sensor interrupts
//     6) APIC internal error interrupts
// A processor can generate IPIs by writing to the interrupt command register (ICR) in its local APIC.
//
// There are two extensions to the APIC:
//     1) xAPIC
//     2) x2APIC
// But neither really matter for our situation I think.
// The x2APIC makes some APIC registers accessible through model specific registers.
//                                                                           - Pascal Beyer 14.03.2023

// 
// We are currently assuming there is only one processor.
// We are also assuming this processor only ever sends fixed, edge-triggered interrupts to itself.
// We are also assuming the guest uses 'cr8' instead of the task priority register.
// 

// Main Reference:
//     Intel Architecture Developer Manual Chapter 10

struct serialized_local_apic{
    /* 000 */u32 reserved_00[4];
    /* 010 */u32 reserved_10[4];
    
    /* 020 */u32 id_register[4];
    /* 030 */u32 version_register[4];
    
    /* 040 */u32 reserved_40[4];
    /* 050 */u32 reserved_50[4];
    /* 060 */u32 reserved_60[4];
    /* 070 */u32 reserved_70[4];
    
    /* 080 */u32 task_priority_register[4];
    /* 090 */u32 arbitration_priority_register[4];
    /* 0a0 */u32 processor_priority_register[4];
    /* 0b0 */u32 end_of_interrupt_register[4];
    
    /* 0c0 */u32 remote_read_register[4];
    /* 0d0 */u32 local_destination_register[4];
    /* 0e0 */u32 destination_format_register[4];
    /* 0f0 */u32 spurious_interrupt_vector_register[4];
    
    /* 100 */u32 in_service_register[8][4];
    /* 180 */u32 trigger_mode_register[8][4];
    /* 200 */u32 interrupt_request_register[8][4];
    
    /* 280 */u32 error_status_register[4];
    
    /* 290 */u32 reserved_290[4];
    /* 2a0 */u32 reserved_2a0[4];
    /* 2b0 */u32 reserved_2b0[4];
    /* 2c0 */u32 reserved_2c0[4];
    /* 2d0 */u32 reserved_2d0[4];
    /* 2e0 */u32 reserved_2e0[4];
    
    /* 2f0 */u32 local_vector_table_corrected_machine_check_interrupt_register[4];
    /* 300 */u32 interrupt_command_register_0_31[4];
    /* 310 */u32 interrupt_command_register_32_63[4];
    /* 320 */u32 local_vector_table_timer_register[4];
    /* 330 */u32 local_vector_table_thermal_sensor_register[4];
    /* 340 */u32 local_vector_table_performance_monitoring_counters_register[4];
    /* 350 */u32 local_vector_table_lint0_register[4];
    /* 360 */u32 local_vector_table_lint1_register[4];
    /* 370 */u32 local_vector_table_error_register[4];
    /* 380 */u32 timer_initial_count_register[4];
    /* 390 */u32 timer_current_count_register[4];
    
    /* 3a0 */u32 reserved_3a0[4];
    /* 3b0 */u32 reserved_3b0[4];
    /* 3c0 */u32 reserved_3c0[4];
    /* 3d0 */u32 reserved_3d0[4];
    
    /* 3e0 */u32 timer_divide_configuration_register[4];
    
    /* 3f0 */u32 reserved_3f0[4];
    
    u8 padding[0x1000 - 0x400];
};

static_assert(sizeof(struct serialized_local_apic) == 0x1000);

int apic__get_highest_set_bit(u32 apic_register[8]){
    
    for(int vector_number = 255; vector_number >= 0; vector_number--){
        if(apic_register[vector_number / 32] & (1u << (vector_number % 32))){
            return vector_number;
        }
    }
    return -1;
}

void apic_perform_end_of_interrupt(struct registers *registers){
    struct local_apic *local_apic = &registers->local_apic;
    
    // 
    // Clear the highest bit set in the in service register.
    // 
    s32 vector = local_apic->highest_interrupt_in_service;
    
    s32 dword_index = vector / 32;
    s32 bit = (1u << vector % 32);
    
    local_apic->in_service_register[dword_index] &= ~bit;
    
    if(PRINT_INTERRUPT_EVENTS) print("apic_perform_end_of_interrupt %x\n", vector);
    
    local_apic->highest_interrupt_in_service = apic__get_highest_set_bit(local_apic->in_service_register);
}

int apic_interrupt_will_be_send(struct registers *registers, int vector_number){
    
    struct local_apic *local_apic = &registers->local_apic;
    
    // "Clearing the IF flag causes the processor to ignore maskable external interrupts."
    if(!registers->IF) return 0;
    
    // 
    // "Each interrupt vector is an 8-bit value. The interrupt-priority class is the value of bits 7:4 of the interrupt vector.
    //  The lowest interrupt-priority class is 1 and the highest is 15; interrupts with vectors in the range 0-15 (with inter-
    //  rupt-priority class 0) are illegal and are never delivered."
    // 
    int interrupt_priority = vector_number >> 4;
    
    // "CR8 - Provides read and write access to the Task Priority Register (TPR). It specifies the priority threshold
    //        value that operating systems use to control the priority class of external interrupts allowed to interrupt the
    //        processor. This register is available only in 64-bit mode. However, interrupt filtering continues to apply in
    //        compatibility mode."
    // 
    // "TPR - Operating systems can use the TPR to temporarily block specific (low-priority) interrupts from interrupting a high-priority task. 
    //        This is done by loading TPR with a value in which the task-priority class corresponds to the highest interrupt-priority class 
    //        that is to be blocked. For example:
    //            * Loading the TPR with a task-priority class of 8 (01000B) blocks all interrupts with an interrupt-priority class of
    //              8 or less while allowing all interrupts with an interrupt-priority class of 9 or more to be recognized.
    //            * Loading the TPR with a task-priority class of 0 enables all external interrupts.
    //            * Loading the TPR with a task-priority class of 0FH (01111B) disables all external interrupts."
    //
    if(interrupt_priority <= (int)(registers->cr8 & 0b1111)) return 0;
    
    // 
    // Check if there is an interrupt with higher priority in service.
    // 
    int interrupt_in_service = local_apic->highest_interrupt_in_service;
    if((interrupt_in_service != -1) && interrupt_priority <= (interrupt_in_service >> 4)){
        return 0;
    }
    
    return 1;
}

// returns whether or not we should send the interrupt.
void apic_pend_interrupt(struct registers *registers, int vector_number){
    
    struct local_apic *local_apic = &registers->local_apic;
    
    // 
    // "Local and I/O APICs support 240 vector numbers in the range 16 to 255 as valid interrupts. 
    //  When an interrupt vector in the range of 0 to 15 is sent or received through the local APIC, 
    //  the APIC indicates an illegal vector in its Error Status Register."
    //  
    //  "The Intel64 and IA-32 architecture reserve vectors 16 through 31 for predefined interrupts, 
    //   exceptions and Intel-reserved encodings. However the APIC does not treat vectors in this range as illegal."
    // 
    if(vector_number < 16){
        local_apic->error_status_register |= /* Received Illegal Vector */(1 << 6); // @cleanup: Received or send?
        return;
    }
    
    if(vector_number > local_apic->highest_pending_interrupt) local_apic->highest_pending_interrupt = vector_number;
    
    local_apic->interrupt_request_register[vector_number/32] |= 1u << (vector_number % 32);
}

int apic_get_pending_interrupt(struct registers *registers){
    struct local_apic *local_apic = &registers->local_apic;
    
    if(PRINT_INTERRUPT_EVENTS && (local_apic->highest_pending_interrupt != -1)){
        print("apic_maybe_deliver_pending_interrupt (IF %d, registers->cr8 %d, interrupt_in_service %x, interrupt_requested %x)\n", registers->IF, registers->cr8, local_apic->highest_interrupt_in_service, local_apic->highest_pending_interrupt);
    }
    
    // "Clearing the IF flag causes the processor to ignore maskable external interrupts."
    if(!registers->IF) return -1;
    
    // 
    // Get the highest priority pending interrupt.
    // 
    int interrupt_requested = local_apic->highest_pending_interrupt;
    if(interrupt_requested == -1) return -1;
    
    // 
    // Check if it is blocked by the TPR.
    // 
    int priority = interrupt_requested >> 4;
    if(priority <= (int)(registers->cr8 & 0b1111)) return -1; 
    
    // 
    // Check if it is blocked by an in-service interrupt.
    // 
    int interrupt_in_service = local_apic->highest_interrupt_in_service;
    if(interrupt_in_service != -1 && priority <= (interrupt_in_service >> 4)) return -1;
    
    // 
    // Clear the 'requested' bit and set the 'in-service' bit.
    // Then deliver the interrupt.
    // 
    u32 dword_index = interrupt_requested/32;
    u32 bit = 1u << (interrupt_requested % 32);
    
    local_apic->in_service_register       [dword_index] |=  bit;
    local_apic->interrupt_request_register[dword_index] &= ~bit;
    
    local_apic->highest_interrupt_in_service = interrupt_requested;
    local_apic->highest_pending_interrupt    = apic__get_highest_set_bit(local_apic->interrupt_request_register);
    
    if(PRINT_INTERRUPT_EVENTS) print("    -> delivering %x\n", interrupt_requested);
    
    return interrupt_requested;
}

int local_apic_read(struct context *context, u64 offset, void *buffer, smm size){
    
    if(size > 4){
        memset(buffer, 0, size);
        size = 4;
    }
    
    char *name = "";
    u32 value = 0;
    
    switch(offset){
        
        case 0x20:{
            // id register
            value = 0;
            memcpy(buffer, &value, size);
            name = "id";
        }break;
        
        case 0x80:{
            // Task Priority Register
            value = (u32)(context->registers.cr8 & 0xf) << 4;
            memcpy(buffer, &value, size);
            name = "tpr";
        }break;
        
        case 0x200: case 0x210: case 0x220: case 0x230: case 0x240: case 0x250: case 0x260: case 0x270:{
            u64 index = (offset - 0x200)/0x10;
            
            value = context->registers.local_apic.interrupt_request_register[index];
            memcpy(buffer, &value, size);
            name = "irr";
        }break;
        
        case 0x320:{
            value = context->registers.local_apic.local_vector_table.timer_register;
            memcpy(buffer, &value, size);
            name = "timer";
        }break;
        
        case 0x340:{
            value = context->registers.local_apic.local_vector_table.performance_monitoring_counters_register;
            memcpy(buffer, &value, size);
            name = "pmc";
        }break;
        
        case 0x350:{
            // local vector table lint 0 register
            value = context->registers.local_apic.local_vector_table.lint0_register;
            memcpy(buffer, &value, size);
            name = "lint0";
        }break;
        
        case 0x360:{
            // local vector table lint 1 register
            value = context->registers.local_apic.local_vector_table.lint1_register;
            memcpy(buffer, &value, size);
            name = "lint1";
        }break;
        
        case 0x370:{
            // local vector table: error
            value = context->registers.local_apic.local_vector_table.error_register;
            memcpy(buffer, &value, size);
            name = "error";
        }break;
        
        case 0x390:{
            // timer current count register
            value = context->registers.local_apic.timer_current_count_register;
            context->registers.local_apic.timer_current_count_register -= 0x1000;
            memcpy(buffer, &value, size);
            name = "timer current count";
        }break;
        
        default:{
            set_crash_information(context, CRASH_internal_error, (u64)"Read from unknown offset in local APIC.");
            return 0;
        }break;
    }
    
    
    if(PRINT_LOCAL_APIC_EVENTS) print("%p: local_apic_read offset 0x%llx, (%d)\n>>> %s (%x)\n", context->registers.rip, offset, size, name, value);
    
    return 1;
}

int local_apic_write(struct context *context, u64 offset, void *buffer, smm size){
    
    if(PRINT_LOCAL_APIC_EVENTS) print("%p: local_apic_write offset 0x%llx, value 0%x (%d)\n", context->registers.rip, offset, *(u32 *)buffer, size);
    
    if(size != 4){
        set_crash_information(context, CRASH_internal_error, (u64)"non-4-byte write to local apic.");
        return 0;
    }
    
    u32 value = *(u32 *)buffer;
    
    switch(offset){
        case 0x80:{
            // Task Priority Register
            context->registers.cr8 = (value >> 4) & 0xf;
        }break;
        
        case 0xe0:{
            // destination format register
            u8 cluster_model = value >> 28;
            
            if(PRINT_LOCAL_APIC_EVENTS) print(">>> cluster model %x\n", cluster_model);
        }break;
        
        case 0xd0:{
            u32 logical_apic_id = value >> 24;
            if(PRINT_LOCAL_APIC_EVENTS) print(">>> logical apic id %x\n", logical_apic_id);
        }break;
        
        case 0xf0:{
            // Spurious interrupt vector
            u8 vector = (u8)value;
            u8 apic_software_enable = (value >> 8) & 1;
            u8 focus_processor_checking = (value >> 9) & 1;
            u8 eoi_broadcast_supression = (value >> 12) & 1;
            if(PRINT_LOCAL_APIC_EVENTS) print(">>> spurious interrupt vector 0x%x, APIC software enable %d, Focus Processor Checking %d, EOI-Broadcast Suppression %d\n", vector, apic_software_enable, focus_processor_checking, eoi_broadcast_supression);
        }break;
        
        case 0x320:{
            // local vector table: timer
            u8 vector  = (u8)value;
            u8 pending = (value >> 12) & 1;
            u8 set_to_mask = (value >> 16) & 1;
            u8 mode = (value >> 17) & 3;
            
            if(PRINT_LOCAL_APIC_EVENTS) print(">>> Apic timer vector %x pending %d set to mask %d mode %d\n", vector, pending, set_to_mask, mode);
            
            context->registers.local_apic.local_vector_table.timer_register = value;
            context->registers.local_apic.timer_current_count_register = context->registers.local_apic.timer_initial_count_register;
        }break;
        
        case 0x340:{
            // local vector table: performance monitor
            u8 vector  = (u8)value;
            u8 pending = (value >> 12) & 1;
            u8 set_to_mask = (value >> 16) & 1;
            if(PRINT_LOCAL_APIC_EVENTS) print(">>> apic performance monitor vector %x pending %d set to mask %d\n", vector, pending, set_to_mask);
            
            context->registers.local_apic.local_vector_table.performance_monitoring_counters_register = value;
        }break;
        
        case 0x350:{
            // local vector table: lint0
            u8 vector  = (u8)value;
            u8 pending = (value >> 12) & 1;
            u8 set_to_mask = (value >> 16) & 1;
            if(PRINT_LOCAL_APIC_EVENTS) print(">>> apic lint0 vector %x pending %d set to mask %d\n", vector, pending, set_to_mask);
            
            context->registers.local_apic.local_vector_table.lint0_register = value;
        }break;
        
        case 0x360:{
            // local vector table: lint1
            u8 vector  = (u8)value;
            u8 pending = (value >> 12) & 1;
            u8 set_to_mask = (value >> 16) & 1;
            if(PRINT_LOCAL_APIC_EVENTS) print(">>> apic lint1 vector %x pending %d set to mask %d\n", vector, pending, set_to_mask);
            
            context->registers.local_apic.local_vector_table.lint1_register = value;
        }break;
        
        case 0x370:{
            // local vector table: error
            u8 vector  = (u8)value;
            u8 pending = (value >> 12) & 1;
            u8 set_to_mask = (value >> 16) & 1;
            if(PRINT_LOCAL_APIC_EVENTS) print(">>> apic error vector %x pending %d set to mask %d\n", vector, pending, set_to_mask);
            
            context->registers.local_apic.timer_initial_count_register = value;
        }break;
        
        case 0x380:{
            // timer initial count register
            if(PRINT_LOCAL_APIC_EVENTS) print(">>> timer initial count %x\n", value);
            context->registers.local_apic.timer_initial_count_register = value;
        }break;
        
        case 0x3e0:{
            // timer divide configuration register
            
            static u8 divide_values[] = {
                [0] = 2,
                [1] = 4,
                [2] = 8,
                [3] = 16,
                [4] = 32,
                [5] = 64,
                [6] = 128,
                [7] = 1,
            };
            
            u8 divide_value = divide_values[((value >> 1) & (1 << 2)) | (value & 3)];
            
            if(PRINT_LOCAL_APIC_EVENTS) print(">>> divide value %d\n", divide_value);
        }break;
        
        default:{
            set_crash_information(context, CRASH_internal_error, (u64)"Write to unknown offset in local APIC.");
            return 0;
        }break;
    }
    
    return 1;
}

// 
// The I/O Apic is used to distribute hardware interrupts.
// They allow for a 'Redirection Table' to map hardware interrupts
// to an interrupt vector (and other configurations such as which processor).
// 
// This Redirection Table is configured by writing the register select
// (offset 0 of the I/O Apic page 0xfec00000) and then writing the value 
// to offset 0x10.
// 
// For our purposes, the I/O Apic is essentially unused, hence we 
// allow reads and writes to it, but there will never be any external
// interrupts to the I/O Apic. 
// The only external interrupts we handle are VMBus interrupts, 
// which don't go through the I/O Apic.
// 
//                                        - Pascal Beyer 16.02.2024
// 
int io_apic_read(struct context *context, u64 offset, void *buffer, smm size){
    
    if(size != 4){
        set_crash_information(context, CRASH_internal_error, (u64)"Non 4-byte read from I/O APIC.");
        return 0;
    }
    
    if(offset == 0x10){
        u32 select = context->registers.io_apic.register_select;
        
        switch(select){
            case /*Apic id*/0:{
                u32 value = 1 << 24;
                memcpy(buffer, &value, size);
                
                if(PRINT_IO_APIC_EVENTS) print("I/O Apic: Reading Apic Id (%x)\n", value);
                
                return 1;
            }break;
            
            case /*version*/1:{
                u8 version = 0x11;
                u8 max_redirection_entry = 0x17;
                u32 value = (max_redirection_entry << 16) | version;
                memcpy(buffer, &value, size);
                
                if(PRINT_IO_APIC_EVENTS) print("I/O Apic: Reading Version (%x = 0x11 version + 0x17 redirection entries)\n", value);
                return 1;
            }break;
        }
        
        u32 redirection_table_entry = (select - 0x10)/2;
        
        if(redirection_table_entry < array_count(context->registers.io_apic.redirection_table)){
            u32 value = 0;
            if(select & 1){
                value = context->registers.io_apic.redirection_table[redirection_table_entry].high;
            }else{
                value = context->registers.io_apic.redirection_table[redirection_table_entry].low;
            }
            
            if(PRINT_IO_APIC_EVENTS) print("I/O Apic: Reading entry %d + %d (select %x) = %x\n", redirection_table_entry, select & 1, select, value);
            
            memcpy(buffer, &value, size);
            
            return 1;
        }
    }
    
    set_crash_information(context, CRASH_internal_error, (u64)"Read from unknown offset in I/O APIC.");
    return 0;
}

int io_apic_write(struct context *context, u64 offset, void *buffer, smm size){
    
    if(size != 4){
        set_crash_information(context, CRASH_internal_error, (u64)"Non 4-byte write to I/O APIC.");
        return 0;
    }
    
    u32 value = *(u32 *)buffer;
    
    if(offset == 0){
        
        if(PRINT_IO_APIC_EVENTS) print("I/O Apic: Writing select to %x\n", value);
        
        context->registers.io_apic.register_select = *(u32 *)buffer;
        return 1;
    }
    
    if(offset == 0x10){
        u32 select = context->registers.io_apic.register_select;
        
        if(select == /*id register*/0 || select == /*version register*/1){
            // @cleanup: Technically writing to the id register allows the software to set the I/O Apic id.
            //           I don't know why the windows kernel writes to the version register though.
            return 1;
        }
        
        u32 redirection_table_entry = (select - 0x10)/2;
        
        if(PRINT_IO_APIC_EVENTS) print("I/O Apic: Writing %x to %x (%d + %d)\n", value, select, redirection_table_entry, select & 1);
        
        if(redirection_table_entry < array_count(context->registers.io_apic.redirection_table)){
            
            if(select & 1){
                context->registers.io_apic.redirection_table[redirection_table_entry].high = value;
            }else{
                context->registers.io_apic.redirection_table[redirection_table_entry].low = value;
            }
            return 1;
        }
        
    }
    
    set_crash_information(context, CRASH_internal_error, (u64)"Write to unknown offset in I/O APIC.");
    return 0;
}

