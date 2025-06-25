// 
// Hypervisor implementation based on the kvm APIs.
// 
// WARNING: Because I personally work on Windows the experience using kvm in snapshot mode to debug might be a lot worse.
// 
// This is the linux implementation for Snapshot Mode. In snapshot mode, we use a hypervisor to give the user reasonable preformance,
// when setting up their snapshots.
// 
// Because of limitations in the API, the kvm-based hypervisor works differantly from the hyperv based one.
// Instead of implementing the hyper-v features (such as timers) it uses the KVM internal implementation of them.
// In some sense this is nice, because in this way they are probably faster and more accurate, but on the other hand,
// they possibly behave differantly then on Windows or in the JIT.
// 
// 


#include <sys/ioctl.h>
#include <linux/kvm.h>

pthread_t g_kvm_thread;
int g_vm_fd;

#define GSI_VMBUS 22

void hypervisor_pend_interrupt(struct context *context, struct registers *registers, u32 vector_number){
    struct kvm_irq_level event = {
        .irq = GSI_VMBUS,
        .level = 1,
    };
    
    if(ioctl(g_vm_fd, KVM_IRQ_LINE, &event) < 0){
        perror("KVM_IRQ_LINE 1");
    }
}


void kvmb_user_signal(int sig){}

void start_execution_hypervisor(struct context *context){
    
    
    {   // 
        // Block all signals.
        // 
        sigset_t set;
        // sigfillset(&set);
        // sigaddset(&set, SIGUSR1);
        sigaddset(&set, SIGINT);
        pthread_sigmask(SIG_BLOCK, &set, NULL);
        
        g_kvm_thread = pthread_self();
        signal(SIGUSR1, kvmb_user_signal);
    }
    
    struct registers *registers = &context->registers;
    
    {   // @cleanup: maybe all of this stuff should be on the outside.
        
        // @note: We fix up the descriptors here as the jit does not care about anything but the selector.
        registers->cs = parse_segment_from_global_descriptor_table(context, registers->gdt_base, registers->cs.selector);
        registers->ss = parse_segment_from_global_descriptor_table(context, registers->gdt_base, registers->ss.selector);
        registers->ds = parse_segment_from_global_descriptor_table(context, registers->gdt_base, registers->ds.selector);
        registers->es = parse_segment_from_global_descriptor_table(context, registers->gdt_base, registers->es.selector);
        
        registers->fs = parse_segment_from_global_descriptor_table(context, registers->gdt_base, registers->fs.selector);
        registers->gs = parse_segment_from_global_descriptor_table(context, registers->gdt_base, registers->gs.selector);
        registers->gs.base = registers->gs_base;
        registers->fs.base = registers->fs_base;
        
        registers->dr7 |= (1 << 13); // General Detect Enable. Causes a debug Exception on any attempt at accessing dr0-dr7.
        registers->dr6 &= ~(1 << 13); // Clear the Debug register Access detected bit.
        registers->dr6 &= ~0xf; // Clear the "Condition Detected" bits.
        
        context->use_hypervisor = 1;
        
        // Setting this value makes sure we won't use the translation look aside buffers.
        // This in turn means, we don't have to invalidate them each time we exit the hypervisor.
        context->skip_setting_permission_bits = 1;
        
    }
    
    
    // 
    // Open /dev/kvm 
    // 
    
    int kvm_fd = open("/dev/kvm", O_RDWR | O_CLOEXEC);
    if(kvm_fd < 0){
        perror("open /dev/kvm");
        exit(1);
    }
    
    if(ioctl(kvm_fd, KVM_GET_API_VERSION, 0) != KVM_API_VERSION){
        perror("KVM_GET_API_VERSION");
        exit(1);
    }
    
    int vm_fd = ioctl(kvm_fd, KVM_CREATE_VM, 0);
    if(vm_fd < 0){
        perror("KVM_CREATE_VM");
        exit(1);
    }
    
    g_vm_fd = vm_fd;
    
    if(ioctl(vm_fd, KVM_CREATE_IRQCHIP, 0) < 0){
        perror("KVM_CREATE_IRQCHIP");
        exit(1);
    }

    struct kvm_enable_cap cap_x86_user_space_msr = {
        .cap  = KVM_CAP_X86_USER_SPACE_MSR,
        .args = KVM_MSR_EXIT_REASON_UNKNOWN | KVM_MSR_EXIT_REASON_FILTER | KVM_MSR_EXIT_REASON_INVAL,
    };
    
    if(ioctl(vm_fd, KVM_ENABLE_CAP, &cap_x86_user_space_msr) < 0){
        perror("KVM_ENABLE_CAP(KVM_CAP_X86_USER_SPACE_MSR)");
        exit(1);
    }
    
    
    {   //
        // Set up guest physical memory.
        // 
        
        u8 *base = globals.snapshot.physical_memory;
        u64 size = globals.snapshot.physical_memory_size;
        
        // 
        // 1) guest
        // 2) preboot frame_buffer
        // 3) guest
        // 4) io-apic hole
        // 5) guest
        // 6) local apic hole
        // 7) guest
        // 8) postboot framebuffer
        // 
        
        int slot = 0;
        
        struct kvm_userspace_memory_region guest_physical_memory_region_low = {
            .slot = slot++,
            .flags = 0,
            .guest_phys_addr = 0,
            .userspace_addr = (u64)base,
            .memory_size = 0xF8000000,
        };
        
        if(ioctl(vm_fd, KVM_SET_USER_MEMORY_REGION, &guest_physical_memory_region_low) < 0){
            perror("KVM_SET_USER_MEMORY_REGION low");
            exit(1);
        }
        
        struct kvm_userspace_memory_region preboot_frame_buffer_memory_region = {
            .slot = slot++,
            .flags = 0,
            .guest_phys_addr = 0xF8000000,
            .userspace_addr = (u64)frame_buffer,
            .memory_size = sizeof(frame_buffer),
        };
        
        if(ioctl(vm_fd, KVM_SET_USER_MEMORY_REGION, &preboot_frame_buffer_memory_region) < 0){
            perror("KVM_SET_USER_MEMORY_REGION preboot");
            exit(1);
        }
        
        
        struct kvm_userspace_memory_region guest_physical_memory_region_mid = {
            .slot = slot++,
            .flags = 0,
            .guest_phys_addr = 0xF8000000 + sizeof(frame_buffer),
            .userspace_addr = (u64)(base + 0xF8000000 + sizeof(frame_buffer)),
            .memory_size = 0xfec00000 - (0xF8000000 + sizeof(frame_buffer)),
        };
        
        if(ioctl(vm_fd, KVM_SET_USER_MEMORY_REGION, &guest_physical_memory_region_mid) < 0){
            perror("KVM_SET_USER_MEMORY_REGION mid");
            exit(1);
        }
        
        /* I/O-Apic hole */
        
        struct kvm_userspace_memory_region guest_physical_memory_region_high = {
            .slot = slot++,
            .flags = 0,
            .guest_phys_addr = 0xfec01000,
            .userspace_addr = (u64)(base + 0xfec01000),
            .memory_size = 0xfee00000 - 0xfec01000,
        };
        
        if(ioctl(vm_fd, KVM_SET_USER_MEMORY_REGION, &guest_physical_memory_region_high) < 0){
            perror("KVM_SET_USER_MEMORY_REGION high");
            exit(1);
        }
        
        /* local apic hole*/
        
        struct kvm_userspace_memory_region guest_physical_memory_region_high_high = {
            .slot = slot++,
            .flags = 0,
            .guest_phys_addr = 0xfee01000,
            .userspace_addr = (u64)(base + 0xfee01000),
            .memory_size = size - 0xfee01000,
        };
        
        if(ioctl(vm_fd, KVM_SET_USER_MEMORY_REGION, &guest_physical_memory_region_high_high) < 0){
            perror("KVM_SET_USER_MEMORY_REGION high high");
            exit(1);
        }
        
        struct kvm_userspace_memory_region postboot_frame_buffer_memory_region = {
            .slot = slot++,
            .flags = 0,
            .guest_phys_addr = 0xFFF800000,
            .userspace_addr = (u64)frame_buffer,
            .memory_size = sizeof(frame_buffer),
        };
        
        if(ioctl(vm_fd, KVM_SET_USER_MEMORY_REGION, &postboot_frame_buffer_memory_region) < 0){
            perror("KVM_SET_USER_MEMORY_REGION postboot");
            exit(1);
        }
        
        
        // @cleanup: monitor pages?
        
    }
    
    // 
    // Set up the VCPU. Here is seems you need to mmap its kvm_run structure 
    // of the vcpu_fd.
    // 
    
    int vcpu_fd = ioctl(vm_fd, KVM_CREATE_VCPU, /*Virtual Processor Index*/0);
    if(vcpu_fd < 0){
        perror("KVM_CREATE_VCPU");
        exit(1);
    }
    
    int vcpu_mmap_size = ioctl(kvm_fd, KVM_GET_VCPU_MMAP_SIZE, 0);
    if(vcpu_mmap_size < 0){
        perror("KVM_GET_VCPU_MMAP_SIZE");
        exit(1);
    }
    
    // "Application code obtains a pointer to the kvm_run structure by mmap()ing a vcpu fd. 
    //  From that point, application code can control execution by changing fields in kvm_run 
    //  prior to calling the KVM_RUN ioctl, and obtain information about the reason KVM_RUN 
    //  returned by looking up structure members."
    struct kvm_run *kvm_run = mmap(NULL, vcpu_mmap_size, PROT_READ | PROT_WRITE, MAP_SHARED, vcpu_fd, 0);
    if(kvm_run == MAP_FAILED){
        perror("mmap kvm_run");
        exit(1);
    }
    
    // 
    // Fill the kvm_run structure with the initial values.
    // 
    
    kvm_run->kvm_valid_regs = KVM_SYNC_X86_REGS | KVM_SYNC_X86_SREGS | KVM_SYNC_X86_EVENTS;
    
    if(ioctl(vcpu_fd, KVM_GET_REGS, &kvm_run->s.regs.regs) < 0){
        perror("KVM_GET_REGS");
        exit(1);
    }
    
    if(ioctl(vcpu_fd, KVM_GET_SREGS, &kvm_run->s.regs.sregs) < 0){
        perror("KVM_GET_SREGS");
        exit(1);
    }
    
    if(ioctl(vcpu_fd, KVM_GET_VCPU_EVENTS, &kvm_run->s.regs.events) < 0){
        perror("KVM_GET_VCPU_EVENTS");
        exit(1);
    }
    
    
    {   // 
        // Set up CPUID's. It seems there is no exit for unhandled CPUID.
        // It simply returns all zeros, if the cpuid is not handled.
        // 
        
        static struct{
            u32 function;
            s32 index;
        } set_cpuid_entries[] = {
            {0, -1},
            {1, -1},
            {2, -1},
            {6, -1},
            {7,  0},
            {0xd, 0},
            {0xd, 1},
            {0xd, 2},
            
            {0x80000000, -1},
            {0x80000001, -1},
            {0x80000002, -1},
            {0x80000003, -1},
            {0x80000004, -1},
            {0x80000005, -1},
            {0x80000006, -1},
            {0x80000007, -1},
            {0x80000008, -1},
            
            {0x40000000, -1},
            {0x40000001, -1},
            {0x40000002, -1},
            {0x40000003, -1},
            {0x40000004, -1},
            {0x40000005, -1},
            {0x40000006, -1},
        };
        
        u8 buffer[sizeof(struct kvm_cpuid2) + array_count(set_cpuid_entries) * sizeof(struct kvm_cpuid_entry2)] = {0};
        
        struct kvm_cpuid2 *cpuid_info = (struct kvm_cpuid2 *)buffer;
        cpuid_info->nent = array_count(set_cpuid_entries);
        
        u64 rax = registers->rax;
        u64 rbx = registers->rbx;
        u64 rcx = registers->rcx;
        u64 rdx = registers->rdx;
        
        for(smm index = 0; index < array_count(set_cpuid_entries); index++){
            
            u32 function = set_cpuid_entries[index].function;
            s32 fn_index = set_cpuid_entries[index].index;
            
            struct kvm_cpuid_entry2 *entry = &cpuid_info->entries[index];
            entry->function = function;
            entry->index = (fn_index != -1) ? fn_index : 0;
            entry->flags = (fn_index != -1) ? KVM_CPUID_FLAG_SIGNIFCANT_INDEX : 0;
            
            registers->rax = function;
            registers->rcx = fn_index;
            
            helper_cpuid(context, registers);
            
            entry->eax = (u32)registers->rax;
            entry->ebx = (u32)registers->rbx;
            entry->ecx = (u32)registers->rcx;
            entry->edx = (u32)registers->rdx;
        }
        
        registers->rax = rax;
        registers->rbx = rbx;
        registers->rcx = rcx;
        registers->rdx = rdx;
        
        if(ioctl(vcpu_fd, KVM_SET_CPUID2, cpuid_info) < 0){
            perror("KVM_SET_CPUID2");
            exit(1);
        }
    }
    

    
    {   //
        // Filter the HV_X64_MSR_EOM hyper-v msr.
        // 
        
        // :AEOI_on_linux
        // 
        // It was really difficult to get any info about `HV_X64_MSR_EOM`.
        // The below only works if the vector is an aeoi (auto-eoi) sint.
        // I am not sure why. Otherwise, one can maybe get this information
        // through the `KVM_IRQFD_FLAG_RESAMPLE` flag of `KVM_IRQFD`.
        // This fd seems to be signaled both, on EOI and on EOM. 
        // Hence, we could do some message counting to figure out when an eom 
        // is expected and then call `vmbus_offer_channel`. 
        // But since it works now using aeois I guess i am happy for now.
        // 
        
        u8 bitmap[0x100/8];
        memset(bitmap, 0xff, sizeof(bitmap));
        
        bitmap[(HV_X64_MSR_EOM - 0x40000000)/8] &= ~(1u << ((HV_X64_MSR_EOM - 0x40000000)%8));

        struct kvm_msr_filter msr_filter = {
            .flags = KVM_MSR_FILTER_DEFAULT_ALLOW,
            .ranges = {
                [0] = {
                    .flags = KVM_MSR_FILTER_READ | KVM_MSR_FILTER_WRITE,
                    .nmsrs = 0x100,
                    .base = 0x40000000,
                    .bitmap = bitmap,
                },
            },
        };
        
        if(ioctl(vm_fd, KVM_X86_SET_MSR_FILTER, &msr_filter) < 0){
            perror("KVM_X86_SET_MSR_FILTER");
            exit(1);
        }
    }
    
    struct kvm_enable_cap cap_hyperv_synic = {
        .cap  = KVM_CAP_HYPERV_SYNIC,
        .args = 0,
    };
    
    if(ioctl(vcpu_fd, KVM_ENABLE_CAP, &cap_hyperv_synic) < 0){
        perror("KVM_ENABLE_CAP(KVM_CAP_HYPERV_SYNIC)");
        exit(1);
    }
    
    {
        // 
        // Ummm...
        // Maybe we need to set up a gsi (Global System Interrupt) route for the sint?
        // 
        
        struct{
            __u32 nmsrs;
            __u32 pad;
            
            struct kvm_msr_entry entry;
        } msrs = {
            .nmsrs = 1,
            .entry = {
                .index = /*HV_X64_MSR_VP_INDEX */0x40000002,
            },
        };
        int msrs_gotten = ioctl(vcpu_fd, KVM_GET_MSRS, &msrs);
        if(msrs_gotten != msrs.nmsrs){
            print("msrs_gotten %d\n", msrs_gotten);
            perror("KVM_GET_MSRS");
            exit(1);
        }
        
        // 
        // It seems the only way to really handle vmbus sint's in kvm is through an async event.
        // We have introduce a GSI (Global System Interrupt) to be able to send the event.
        // 
        
        struct{
            struct kvm_irq_routing irq_routing;
            struct kvm_irq_routing_entry irq_routing_entry;
        } irq_routing = {
            .irq_routing = {
                .nr = 1,
                .flags = 0,
            },
            .irq_routing_entry = {
                .gsi = GSI_VMBUS,
                .type = KVM_IRQ_ROUTING_HV_SINT,
                .flags = 0,
                .u.hv_sint.vcpu = msrs.entry.data,
                .u.hv_sint.sint = 2,
            },
        };
        
        if(ioctl(vm_fd, KVM_SET_GSI_ROUTING, &irq_routing) < 0){
            perror("KVM_SET_GSI_ROUTING");
            exit(1);
        }
    }
    
    struct kvm_enable_cap cap_hyperv_direct_tlb_flush = {
        .cap  = KVM_CAP_HYPERV_DIRECT_TLBFLUSH,
        .args = 0,
    };
    
    if(ioctl(vcpu_fd, KVM_ENABLE_CAP, &cap_hyperv_direct_tlb_flush) < 0){
        perror("KVM_ENABLE_CAP(KVM_CAP_HYPERV_DIRECT_TLBFLUSH)");
        exit(1);
    }
    
    {   //
        // Synchronize the local apic state.
        // 
        
        // "The data format and layout are the same as documented in the architecture manual."
        struct serialized_local_apic local_apic;
        if(ioctl(vcpu_fd, KVM_GET_LAPIC, &local_apic) < 0){
            perror("KVM_GET_LAPIC");
            exit(1);
        }
        
        local_apic.task_priority_register[0] = registers->local_apic.task_priority_register;
        local_apic.arbitration_priority_register[0] = registers->local_apic.arbitration_priority_register;
        local_apic.processor_priority_register[0] = registers->local_apic.processor_priority_register;
        local_apic.local_destination_register[0] = registers->local_apic.local_destination_register;
        local_apic.destination_format_register[0] = registers->local_apic.destination_format_register;
        local_apic.spurious_interrupt_vector_register[0] = registers->local_apic.spurious_interrupt_vector_register;
        
        for(u32 index = 0; index < 8; index++){
            local_apic.in_service_register[index][0] = registers->local_apic.in_service_register[index];
            local_apic.trigger_mode_register[index][0] = registers->local_apic.trigger_mode_register[index];
            local_apic.interrupt_request_register[index][0] = registers->local_apic.interrupt_request_register[index];
        }
        
        local_apic.error_status_register[0] = registers->local_apic.error_status_register;
        
        local_apic.local_vector_table_corrected_machine_check_interrupt_register[0] = registers->local_apic.local_vector_table.corrected_machine_check_interrupt_register;
        local_apic.local_vector_table_timer_register[0] = registers->local_apic.local_vector_table.timer_register;
        local_apic.local_vector_table_thermal_sensor_register[0] = registers->local_apic.local_vector_table.thermal_sensor_register;
        local_apic.local_vector_table_performance_monitoring_counters_register[0] = registers->local_apic.local_vector_table.performance_monitoring_counters_register;
        local_apic.local_vector_table_lint0_register[0] = registers->local_apic.local_vector_table.lint0_register;
        local_apic.local_vector_table_lint1_register[0] = registers->local_apic.local_vector_table.lint1_register;
        local_apic.local_vector_table_error_register[0] = registers->local_apic.local_vector_table.error_register;
        local_apic.timer_divide_configuration_register[0] = registers->local_apic.timer_divide_configuration_register;
        
        if(ioctl(vcpu_fd, KVM_SET_LAPIC, &local_apic) < 0){
            perror("KVM_SET_LAPIC");
            exit(1);
        }
    }
    
    if(globals.single_stepping){
        // If we are starting by 'single stepping', it means we want to enter the debugger on the first instruction.
        // Hence, we put a breakpoint on the instruction we are currently at.
        hypervisor_set_breakpoint(context, registers, BREAKPOINT_execute, BREAKPOINT_FLAG_oneshot, registers->rip, 1);
    }
    
    int first_time = 1;
    
    union{
        struct xsave_area xsave_area;
        struct kvm_xsave kvm_xsave;
    } xsave = {0};
    
    while(1){
        
        // 
        // Set general purpose registers.
        // 
        
        kvm_run->s.regs.regs.rax = registers->rax;
        kvm_run->s.regs.regs.rbx = registers->rbx;
        kvm_run->s.regs.regs.rcx = registers->rcx;
        kvm_run->s.regs.regs.rdx = registers->rdx;
        kvm_run->s.regs.regs.rsi = registers->rsi;
        kvm_run->s.regs.regs.rdi = registers->rdi;
        kvm_run->s.regs.regs.rsp = registers->rsp;
        kvm_run->s.regs.regs.rbp = registers->rbp;
        kvm_run->s.regs.regs.r8  = registers->r8;
        kvm_run->s.regs.regs.r9  = registers->r9;
        kvm_run->s.regs.regs.r10 = registers->r10;
        kvm_run->s.regs.regs.r11 = registers->r11;
        kvm_run->s.regs.regs.r12 = registers->r12;
        kvm_run->s.regs.regs.r13 = registers->r13;
        kvm_run->s.regs.regs.r14 = registers->r14;
        kvm_run->s.regs.regs.r15 = registers->r15;
        
        kvm_run->s.regs.regs.rip = registers->rip;
        kvm_run->s.regs.regs.rflags = registers->rflags;
        
        kvm_run->kvm_dirty_regs |= KVM_SYNC_X86_REGS;
        
        if(first_time){
            
            // 
            // Set special registers.
            // 
            
            kvm_run->s.regs.sregs.cr0 = registers->cr0;
            kvm_run->s.regs.sregs.cr2 = registers->cr2;
            kvm_run->s.regs.sregs.cr3 = registers->cr3;
            kvm_run->s.regs.sregs.cr4 = registers->cr4;
            kvm_run->s.regs.sregs.cr8 = registers->cr8;
            
            kvm_run->s.regs.sregs.cs.base     = registers->cs.base;
            kvm_run->s.regs.sregs.cs.limit    = registers->cs.limit;
            kvm_run->s.regs.sregs.cs.selector = registers->cs.selector;
            kvm_run->s.regs.sregs.cs.type     = registers->cs.segment_type;
            kvm_run->s.regs.sregs.cs.present  = registers->cs.present;
            kvm_run->s.regs.sregs.cs.dpl      = registers->cs.privilege_level;
            kvm_run->s.regs.sregs.cs.db       = registers->cs.default_big;
            kvm_run->s.regs.sregs.cs.s        = registers->cs.is_non_system;
            kvm_run->s.regs.sregs.cs.l        = registers->cs.long_mode;
            kvm_run->s.regs.sregs.cs.g        = registers->cs.granularity;
            kvm_run->s.regs.sregs.cs.avl      = registers->cs.available;
            
            kvm_run->s.regs.sregs.ds.base     = registers->ds.base;
            kvm_run->s.regs.sregs.ds.limit    = registers->ds.limit;
            kvm_run->s.regs.sregs.ds.selector = registers->ds.selector;
            kvm_run->s.regs.sregs.ds.type     = registers->ds.segment_type;
            kvm_run->s.regs.sregs.ds.present  = registers->ds.present;
            kvm_run->s.regs.sregs.ds.dpl      = registers->ds.privilege_level;
            kvm_run->s.regs.sregs.ds.db       = registers->ds.default_big;
            kvm_run->s.regs.sregs.ds.s        = registers->ds.is_non_system;
            kvm_run->s.regs.sregs.ds.l        = registers->ds.long_mode;
            kvm_run->s.regs.sregs.ds.g        = registers->ds.granularity;
            kvm_run->s.regs.sregs.ds.avl      = registers->ds.available;
            
            kvm_run->s.regs.sregs.es.base     = registers->es.base;
            kvm_run->s.regs.sregs.es.limit    = registers->es.limit;
            kvm_run->s.regs.sregs.es.selector = registers->es.selector;
            kvm_run->s.regs.sregs.es.type     = registers->es.segment_type;
            kvm_run->s.regs.sregs.es.present  = registers->es.present;
            kvm_run->s.regs.sregs.es.dpl      = registers->es.privilege_level;
            kvm_run->s.regs.sregs.es.db       = registers->es.default_big;
            kvm_run->s.regs.sregs.es.s        = registers->es.is_non_system;
            kvm_run->s.regs.sregs.es.l        = registers->es.long_mode;
            kvm_run->s.regs.sregs.es.g        = registers->es.granularity;
            kvm_run->s.regs.sregs.es.avl      = registers->es.available;
            
            kvm_run->s.regs.sregs.ss.base     = registers->ss.base;
            kvm_run->s.regs.sregs.ss.limit    = registers->ss.limit;
            kvm_run->s.regs.sregs.ss.selector = registers->ss.selector;
            kvm_run->s.regs.sregs.ss.type     = registers->ss.segment_type;
            kvm_run->s.regs.sregs.ss.present  = registers->ss.present;
            kvm_run->s.regs.sregs.ss.dpl      = registers->ss.privilege_level;
            kvm_run->s.regs.sregs.ss.db       = registers->ss.default_big;
            kvm_run->s.regs.sregs.ss.s        = registers->ss.is_non_system;
            kvm_run->s.regs.sregs.ss.l        = registers->ss.long_mode;
            kvm_run->s.regs.sregs.ss.g        = registers->ss.granularity;
            kvm_run->s.regs.sregs.ss.avl      = registers->ss.available;
            
            kvm_run->s.regs.sregs.tr.base     = registers->tr.base;
            kvm_run->s.regs.sregs.tr.limit    = registers->tr.limit;
            kvm_run->s.regs.sregs.tr.selector = registers->tr.selector;
            kvm_run->s.regs.sregs.tr.type     = registers->tr.segment_type;
            kvm_run->s.regs.sregs.tr.present  = registers->tr.present;
            kvm_run->s.regs.sregs.tr.dpl      = registers->tr.privilege_level;
            kvm_run->s.regs.sregs.tr.db       = registers->tr.default_big;
            kvm_run->s.regs.sregs.tr.s        = registers->tr.is_non_system;
            kvm_run->s.regs.sregs.tr.l        = registers->tr.long_mode;
            kvm_run->s.regs.sregs.tr.g        = registers->tr.granularity;
            kvm_run->s.regs.sregs.tr.avl      = registers->tr.available;
            
            kvm_run->s.regs.sregs.ldt.base     = registers->ldt.base;
            kvm_run->s.regs.sregs.ldt.limit    = registers->ldt.limit;
            kvm_run->s.regs.sregs.ldt.selector = registers->ldt.selector;
            kvm_run->s.regs.sregs.ldt.type     = registers->ldt.segment_type;
            kvm_run->s.regs.sregs.ldt.present  = registers->ldt.present;
            kvm_run->s.regs.sregs.ldt.dpl      = registers->ldt.privilege_level;
            kvm_run->s.regs.sregs.ldt.db       = registers->ldt.default_big;
            kvm_run->s.regs.sregs.ldt.s        = registers->ldt.is_non_system;
            kvm_run->s.regs.sregs.ldt.l        = registers->ldt.long_mode;
            kvm_run->s.regs.sregs.ldt.g        = registers->ldt.granularity;
            kvm_run->s.regs.sregs.ldt.avl      = registers->ldt.available;
            
            kvm_run->s.regs.sregs.gs.base     = registers->gs.base;
            kvm_run->s.regs.sregs.gs.limit    = registers->gs.limit;
            kvm_run->s.regs.sregs.gs.selector = registers->gs.selector;
            kvm_run->s.regs.sregs.gs.type     = registers->gs.segment_type;
            kvm_run->s.regs.sregs.gs.present  = registers->gs.present;
            kvm_run->s.regs.sregs.gs.dpl      = registers->gs.privilege_level;
            kvm_run->s.regs.sregs.gs.db       = registers->gs.default_big;
            kvm_run->s.regs.sregs.gs.s        = registers->gs.is_non_system;
            kvm_run->s.regs.sregs.gs.l        = registers->gs.long_mode;
            kvm_run->s.regs.sregs.gs.g        = registers->gs.granularity;
            kvm_run->s.regs.sregs.gs.avl      = registers->gs.available;
            
            kvm_run->s.regs.sregs.fs.base     = registers->fs.base;
            kvm_run->s.regs.sregs.fs.limit    = registers->fs.limit;
            kvm_run->s.regs.sregs.fs.selector = registers->fs.selector;
            kvm_run->s.regs.sregs.fs.type     = registers->fs.segment_type;
            kvm_run->s.regs.sregs.fs.present  = registers->fs.present;
            kvm_run->s.regs.sregs.fs.dpl      = registers->fs.privilege_level;
            kvm_run->s.regs.sregs.fs.db       = registers->fs.default_big;
            kvm_run->s.regs.sregs.fs.s        = registers->fs.is_non_system;
            kvm_run->s.regs.sregs.fs.l        = registers->fs.long_mode;
            kvm_run->s.regs.sregs.fs.g        = registers->fs.granularity;
            kvm_run->s.regs.sregs.fs.avl      = registers->fs.available;
            
            kvm_run->s.regs.sregs.gdt.base = registers->gdt_base;
            kvm_run->s.regs.sregs.gdt.limit = registers->gdt_limit;
            
            kvm_run->s.regs.sregs.idt.base = registers->idt_base;
            kvm_run->s.regs.sregs.idt.limit = registers->idt_limit;
            
            kvm_run->s.regs.sregs.efer = registers->ia32_efer;
            kvm_run->s.regs.sregs.apic_base = registers->ia32_apic_base;
            
            kvm_run->kvm_dirty_regs |= KVM_SYNC_X86_SREGS;
            
            // 
            // Load the floating point registers
            // 
            xsave.xsave_area = xsave_area_from_registers(registers);
            
            
            if(ioctl(vcpu_fd, KVM_SET_XSAVE, &xsave.kvm_xsave) < 0){
                perror("KVM_SET_XSAVE");
                exit(1);
            }
            
            
#if 0
            {
                struct kvm_fpu fpu = {
                    .fcw = registers->fpu_control_word,
                    .fsw = registers->fpu_status_word,
                    .ftwx = registers->fpu_tag_word,
                    .last_opcode = registers->fpu_opcode,
                    .last_ip = registers->fpu_instruction_pointer,
                    .last_dp = registers->fpu_data_pointer,
                    .mxcsr = registers->mxcsr,
                };
                memcpy(fpu.fpr, registers->fpu_st, 16 * 8);
                memcpy(fpu.xmm, registers->xmm, 16 * 8);
                
                if(ioctl(vcpu_fd, KVM_SET_FPU, &fpu) < 0){
                    perror("KVM_SET_FPU");
                    exit(1);
                }
            }
#endif
            
            {   // 
                // Load cr0.
                // 
                struct kvm_xcrs xcrs = {
                    .nr_xcrs = 1,
                    .flags = 0,
                    .xcrs[0] = {.xcr = 0, .value = registers->xcr0 },
                };
                
                if(ioctl(vcpu_fd, KVM_SET_XCRS, &xcrs) < 0){
                    perror("KVM_SET_XCRS");
                    exit(1);
                }
            }
            
            first_time = 0;
        }
            
        {   // 
            // Load the debug registers.
            // 
            
            struct kvm_guest_debug dreg = {
                .control = KVM_GUESTDBG_ENABLE | KVM_GUESTDBG_USE_HW_BP, /* | KVM_GUESTDBG_SINGLESTEP*/
                .arch = {
                    .debugreg[0] = registers->dr0,
                    .debugreg[1] = registers->dr1,
                    .debugreg[2] = registers->dr2,
                    .debugreg[3] = registers->dr3,
                    .debugreg[6] = registers->dr6,
                    .debugreg[7] = registers->dr7,
                },
            };
            
            if(globals.single_stepping) dreg.control |= KVM_GUESTDBG_SINGLESTEP;
            
            if(ioctl(vcpu_fd, KVM_SET_GUEST_DEBUG, &dreg) < 0){
                perror("KVM_SET_GUEST_DEBUG");
                exit(1);
            }
        }
        
        {   // 
            // Load some Model Specific Registers.
            // 
            
            struct{
                __u32 nmsrs;
                __u32 pad;
                
                struct kvm_msr_entry entries[16 + 16];
            } msrs = {
                .nmsrs = 12 + 16,
                .entries = {
                    { .index = IA32_KERNEL_GS_BASE, .data = registers->gs_swap},
                    { .index = IA32_TSC, .data = registers->ia32_tsc},
                    { .index = 0xc0000103, .data = registers->ia32_tsc_aux},
                    { .index = 0xc0000082, .data = registers->ia32_lstar},
                    { .index = 0xc0000083, .data = registers->ia32_cstar},
                    { .index = 0xc0000081, .data = registers->ia32_star},
                    { .index = 0xc0000084, .data = registers->ia32_fmask},
                    { .index = 0xc0000080, .data = registers->ia32_efer},
                    { .index = 0x00000048, .data = registers->ia32_spec_ctrl},
                    { .index = 0x00000277, .data = registers->ia32_pat},
                    { .index = 0x000001a0, .data = registers->ia32_misc_enable},
                    { .index = 0x0000001b, .data = registers->ia32_apic_base},
                    // { .index = IA32_MTRR_CAP,       .data = registers->ia32_mtrr_cap},
                    // { .index = IA32_MTRR_DEF_TYPE,  .data = registers->ia32_mtrr_def_type},
                    // { .index = IA32_MTRR_PHYS_BASE, .data = registers->ia32_mtrr_phys_base},
                    // { .index = IA32_MTRR_PHYS_MASK, .data = registers->ia32_mtrr_phys_mask},
                    
                    { .index = HV_X64_MSR_SINT0, .data = registers->hv_x64_msr_sint[0]},
                    { .index = HV_X64_MSR_SINT1, .data = registers->hv_x64_msr_sint[1]},
                    { .index = HV_X64_MSR_SINT2, .data = registers->hv_x64_msr_sint[2]},
                    { .index = HV_X64_MSR_SINT3, .data = registers->hv_x64_msr_sint[3]},
                    { .index = HV_X64_MSR_SINT4, .data = registers->hv_x64_msr_sint[4]},
                    { .index = HV_X64_MSR_SINT5, .data = registers->hv_x64_msr_sint[5]},
                    { .index = HV_X64_MSR_SINT6, .data = registers->hv_x64_msr_sint[6]},
                    { .index = HV_X64_MSR_SINT7, .data = registers->hv_x64_msr_sint[7]},
                    { .index = HV_X64_MSR_SINT8, .data = registers->hv_x64_msr_sint[8]},
                    { .index = HV_X64_MSR_SINT9, .data = registers->hv_x64_msr_sint[9]},
                    { .index = HV_X64_MSR_SINT10, .data = registers->hv_x64_msr_sint[10]},
                    { .index = HV_X64_MSR_SINT11, .data = registers->hv_x64_msr_sint[11]},
                    { .index = HV_X64_MSR_SINT12, .data = registers->hv_x64_msr_sint[12]},
                    { .index = HV_X64_MSR_SINT13, .data = registers->hv_x64_msr_sint[13]},
                    { .index = HV_X64_MSR_SINT14, .data = registers->hv_x64_msr_sint[14]},
                    { .index = HV_X64_MSR_SINT15, .data = registers->hv_x64_msr_sint[15]},
                    
                },
            };
            
            int msrs_set = ioctl(vcpu_fd, KVM_SET_MSRS, &msrs);
            if(msrs_set != msrs.nmsrs){
                print("msrs_set %d\n", msrs_set);
                perror("KVM_SET_MSRS");
                exit(1);
            }
        }
        
        ioctl(vcpu_fd, KVM_RUN, 0);
        
        {   // 
            // Load some Model Specific Registers.
            // 
            
            struct{
                __u32 nmsrs;
                __u32 pad;
                
                struct kvm_msr_entry entries[16 + 16];
            } msrs = {
                .nmsrs = 12 + 16,
                .entries = {
                    { .index = IA32_KERNEL_GS_BASE },
                    { .index = IA32_TSC },
                    { .index = 0xc0000103 },
                    { .index = 0xc0000082 },
                    { .index = 0xc0000083 },
                    { .index = 0xc0000081 },
                    { .index = 0xc0000084 },
                    { .index = 0xc0000080 },
                    { .index = 0x00000048 },
                    { .index = 0x00000277 },
                    { .index = 0x000001a0 },
                    { .index = 0x0000001b },
                    // { .index = IA32_MTRR_CAP },
                    // { .index = IA32_MTRR_DEF_TYPE },
                    // { .index = IA32_MTRR_PHYS_BASE },
                    // { .index = IA32_MTRR_PHYS_MASK },
                    
                    
                    { .index = HV_X64_MSR_SINT0 },
                    { .index = HV_X64_MSR_SINT1 },
                    { .index = HV_X64_MSR_SINT2 },
                    { .index = HV_X64_MSR_SINT3 },
                    { .index = HV_X64_MSR_SINT4 },
                    { .index = HV_X64_MSR_SINT5 },
                    { .index = HV_X64_MSR_SINT6 },
                    { .index = HV_X64_MSR_SINT7 },
                    { .index = HV_X64_MSR_SINT8 },
                    { .index = HV_X64_MSR_SINT9 },
                    { .index = HV_X64_MSR_SINT10 },
                    { .index = HV_X64_MSR_SINT11 },
                    { .index = HV_X64_MSR_SINT12 },
                    { .index = HV_X64_MSR_SINT13 },
                    { .index = HV_X64_MSR_SINT14 },
                    { .index = HV_X64_MSR_SINT15 },
                    
                },
            };
            
            int msrs_gotten = ioctl(vcpu_fd, KVM_GET_MSRS, &msrs);
            if(msrs_gotten != msrs.nmsrs){
                print("msrs_gotten %d\n", msrs_gotten);
                perror("KVM_GET_MSRS");
                exit(1);
            }
            
            u32 index = 0;
            registers->gs_swap          = msrs.entries[index++].data;
            registers->ia32_tsc         = msrs.entries[index++].data;
            registers->ia32_tsc_aux     = msrs.entries[index++].data;
            registers->ia32_lstar       = msrs.entries[index++].data;
            registers->ia32_cstar       = msrs.entries[index++].data;
            registers->ia32_star        = msrs.entries[index++].data;
            registers->ia32_fmask       = msrs.entries[index++].data;
            registers->ia32_efer        = msrs.entries[index++].data;
            registers->ia32_spec_ctrl   = msrs.entries[index++].data;
            registers->ia32_pat         = msrs.entries[index++].data;
            registers->ia32_misc_enable = msrs.entries[index++].data;
            registers->ia32_apic_base   = msrs.entries[index++].data;
            
            registers->hv_x64_msr_sint[0] = msrs.entries[index++].data;
            registers->hv_x64_msr_sint[1] = msrs.entries[index++].data;
            registers->hv_x64_msr_sint[2] = msrs.entries[index++].data;
            registers->hv_x64_msr_sint[3] = msrs.entries[index++].data;
            registers->hv_x64_msr_sint[4] = msrs.entries[index++].data;
            registers->hv_x64_msr_sint[5] = msrs.entries[index++].data;
            registers->hv_x64_msr_sint[6] = msrs.entries[index++].data;
            registers->hv_x64_msr_sint[7] = msrs.entries[index++].data;
            registers->hv_x64_msr_sint[8] = msrs.entries[index++].data;
            registers->hv_x64_msr_sint[9] = msrs.entries[index++].data;
            registers->hv_x64_msr_sint[10] = msrs.entries[index++].data;
            registers->hv_x64_msr_sint[11] = msrs.entries[index++].data;
            registers->hv_x64_msr_sint[12] = msrs.entries[index++].data;
            registers->hv_x64_msr_sint[13] = msrs.entries[index++].data;
            registers->hv_x64_msr_sint[14] = msrs.entries[index++].data;
            registers->hv_x64_msr_sint[15] = msrs.entries[index++].data;
        }
        
        {   // 
            // Copy the kvm register state into our register state.
            // 
            
            registers->rax = kvm_run->s.regs.regs.rax;
            registers->rbx = kvm_run->s.regs.regs.rbx;
            registers->rcx = kvm_run->s.regs.regs.rcx;
            registers->rdx = kvm_run->s.regs.regs.rdx;
            registers->rsi = kvm_run->s.regs.regs.rsi;
            registers->rdi = kvm_run->s.regs.regs.rdi;
            registers->rsp = kvm_run->s.regs.regs.rsp;
            registers->rbp = kvm_run->s.regs.regs.rbp;
            registers->r8 = kvm_run->s.regs.regs.r8;
            registers->r9 = kvm_run->s.regs.regs.r9;
            registers->r10 = kvm_run->s.regs.regs.r10;
            registers->r11 = kvm_run->s.regs.regs.r11;
            registers->r12 = kvm_run->s.regs.regs.r12;
            registers->r13 = kvm_run->s.regs.regs.r13;
            registers->r14 = kvm_run->s.regs.regs.r14;
            registers->r15 = kvm_run->s.regs.regs.r15;
            
            registers->rip = kvm_run->s.regs.regs.rip;
            registers->rflags = kvm_run->s.regs.regs.rflags;
            
            
            registers->cr0 = kvm_run->s.regs.sregs.cr0;
            registers->cr2 = kvm_run->s.regs.sregs.cr2;
            registers->cr3 = kvm_run->s.regs.sregs.cr3;
            registers->cr4 = kvm_run->s.regs.sregs.cr4;
            registers->cr8 = kvm_run->s.regs.sregs.cr8;
            
            registers->cs.base = kvm_run->s.regs.sregs.cs.base;
            registers->cs.limit = kvm_run->s.regs.sregs.cs.limit;
            registers->cs.selector = kvm_run->s.regs.sregs.cs.selector;
            registers->cs.segment_type = kvm_run->s.regs.sregs.cs.type;
            registers->cs.present = kvm_run->s.regs.sregs.cs.present ;
            registers->cs.privilege_level = kvm_run->s.regs.sregs.cs.dpl;
            registers->cs.default_big = kvm_run->s.regs.sregs.cs.db;
            registers->cs.is_non_system = kvm_run->s.regs.sregs.cs.s;
            registers->cs.long_mode = kvm_run->s.regs.sregs.cs.l;
            registers->cs.granularity = kvm_run->s.regs.sregs.cs.g;
            registers->cs.available = kvm_run->s.regs.sregs.cs.avl;
            
            registers->ds.base = kvm_run->s.regs.sregs.ds.base;
            registers->ds.limit = kvm_run->s.regs.sregs.ds.limit;
            registers->ds.selector = kvm_run->s.regs.sregs.ds.selector;
            registers->ds.segment_type = kvm_run->s.regs.sregs.ds.type;
            registers->ds.present = kvm_run->s.regs.sregs.ds.present ;
            registers->ds.privilege_level = kvm_run->s.regs.sregs.ds.dpl;
            registers->ds.default_big = kvm_run->s.regs.sregs.ds.db;
            registers->ds.is_non_system = kvm_run->s.regs.sregs.ds.s;
            registers->ds.long_mode = kvm_run->s.regs.sregs.ds.l;
            registers->ds.granularity = kvm_run->s.regs.sregs.ds.g;
            registers->ds.available = kvm_run->s.regs.sregs.ds.avl;
            
            registers->es.base = kvm_run->s.regs.sregs.es.base;
            registers->es.limit = kvm_run->s.regs.sregs.es.limit;
            registers->es.selector = kvm_run->s.regs.sregs.es.selector;
            registers->es.segment_type = kvm_run->s.regs.sregs.es.type;
            registers->es.present = kvm_run->s.regs.sregs.es.present ;
            registers->es.privilege_level = kvm_run->s.regs.sregs.es.dpl;
            registers->es.default_big = kvm_run->s.regs.sregs.es.db;
            registers->es.is_non_system = kvm_run->s.regs.sregs.es.s;
            registers->es.long_mode = kvm_run->s.regs.sregs.es.l;
            registers->es.granularity = kvm_run->s.regs.sregs.es.g;
            registers->es.available = kvm_run->s.regs.sregs.es.avl;
            
            registers->ss.base = kvm_run->s.regs.sregs.ss.base;
            registers->ss.limit = kvm_run->s.regs.sregs.ss.limit;
            registers->ss.selector = kvm_run->s.regs.sregs.ss.selector;
            registers->ss.segment_type = kvm_run->s.regs.sregs.ss.type;
            registers->ss.present = kvm_run->s.regs.sregs.ss.present ;
            registers->ss.privilege_level = kvm_run->s.regs.sregs.ss.dpl;
            registers->ss.default_big = kvm_run->s.regs.sregs.ss.db;
            registers->ss.is_non_system = kvm_run->s.regs.sregs.ss.s;
            registers->ss.long_mode = kvm_run->s.regs.sregs.ss.l;
            registers->ss.granularity = kvm_run->s.regs.sregs.ss.g;
            registers->ss.available = kvm_run->s.regs.sregs.ss.avl;
            
            registers->tr.base = kvm_run->s.regs.sregs.tr.base;
            registers->tr.limit = kvm_run->s.regs.sregs.tr.limit;
            registers->tr.selector = kvm_run->s.regs.sregs.tr.selector;
            registers->tr.segment_type = kvm_run->s.regs.sregs.tr.type;
            registers->tr.present = kvm_run->s.regs.sregs.tr.present ;
            registers->tr.privilege_level = kvm_run->s.regs.sregs.tr.dpl;
            registers->tr.default_big = kvm_run->s.regs.sregs.tr.db;
            registers->tr.is_non_system = kvm_run->s.regs.sregs.tr.s;
            registers->tr.long_mode = kvm_run->s.regs.sregs.tr.l;
            registers->tr.granularity = kvm_run->s.regs.sregs.tr.g;
            registers->tr.available = kvm_run->s.regs.sregs.tr.avl;
            
            registers->ldt.base = kvm_run->s.regs.sregs.ldt.base;
            registers->ldt.limit = kvm_run->s.regs.sregs.ldt.limit;
            registers->ldt.selector = kvm_run->s.regs.sregs.ldt.selector;
            registers->ldt.segment_type = kvm_run->s.regs.sregs.ldt.type;
            registers->ldt.present = kvm_run->s.regs.sregs.ldt.present ;
            registers->ldt.privilege_level = kvm_run->s.regs.sregs.ldt.dpl;
            registers->ldt.default_big = kvm_run->s.regs.sregs.ldt.db;
            registers->ldt.is_non_system = kvm_run->s.regs.sregs.ldt.s;
            registers->ldt.long_mode = kvm_run->s.regs.sregs.ldt.l;
            registers->ldt.granularity = kvm_run->s.regs.sregs.ldt.g;
            registers->ldt.available = kvm_run->s.regs.sregs.ldt.avl;
            
            registers->gs.base = kvm_run->s.regs.sregs.gs.base;
            registers->gs.limit = kvm_run->s.regs.sregs.gs.limit;
            registers->gs.selector = kvm_run->s.regs.sregs.gs.selector;
            registers->gs.segment_type = kvm_run->s.regs.sregs.gs.type;
            registers->gs.present = kvm_run->s.regs.sregs.gs.present ;
            registers->gs.privilege_level = kvm_run->s.regs.sregs.gs.dpl;
            registers->gs.default_big = kvm_run->s.regs.sregs.gs.db;
            registers->gs.is_non_system = kvm_run->s.regs.sregs.gs.s;
            registers->gs.long_mode = kvm_run->s.regs.sregs.gs.l;
            registers->gs.granularity = kvm_run->s.regs.sregs.gs.g;
            registers->gs.available = kvm_run->s.regs.sregs.gs.avl;
            
            registers->fs.base = kvm_run->s.regs.sregs.fs.base;
            registers->fs.limit = kvm_run->s.regs.sregs.fs.limit;
            registers->fs.selector = kvm_run->s.regs.sregs.fs.selector;
            registers->fs.segment_type = kvm_run->s.regs.sregs.fs.type;
            registers->fs.present = kvm_run->s.regs.sregs.fs.present ;
            registers->fs.privilege_level = kvm_run->s.regs.sregs.fs.dpl;
            registers->fs.default_big = kvm_run->s.regs.sregs.fs.db;
            registers->fs.is_non_system = kvm_run->s.regs.sregs.fs.s;
            registers->fs.long_mode = kvm_run->s.regs.sregs.fs.l;
            registers->fs.granularity = kvm_run->s.regs.sregs.fs.g;
            registers->fs.available = kvm_run->s.regs.sregs.fs.avl;
            
            registers->gdt_base = kvm_run->s.regs.sregs.gdt.base;
            registers->gdt_limit = kvm_run->s.regs.sregs.gdt.limit;
            
            registers->idt_base = kvm_run->s.regs.sregs.idt.base;
            registers->idt_limit = kvm_run->s.regs.sregs.idt.limit;
            
            registers->ia32_efer = kvm_run->s.regs.sregs.efer;
            registers->ia32_apic_base = kvm_run->s.regs.sregs.apic_base;
            
            {   // 
                // Load the floating point registers
                // 
                
                if(ioctl(vcpu_fd, KVM_GET_XSAVE, &xsave.kvm_xsave) < 0){
                    perror("KVM_GET_XSAVE");
                    exit(1);
                }
                
                if(xsave.xsave_area.mxcsr == 0){
                    xsave.xsave_area.mxcsr = registers->mxcsr; // @cleanup:
                }
                
                load_xsave_registers(registers, xsave.xsave_area);
                

                struct kvm_fpu fpu;
                if(ioctl(vcpu_fd, KVM_GET_FPU, &fpu) < 0){
                    perror("KVM_SET_FPU");
                    exit(1);
                }
                
                registers->fpu_control_word = fpu.fcw;
                registers->fpu_status_word = fpu.fsw;
                registers->fpu_tag_word = fpu.ftwx;
                registers->fpu_opcode = fpu.last_opcode;
                registers->fpu_instruction_pointer = fpu.last_ip;
                registers->fpu_data_pointer = fpu.last_dp;
                registers->mxcsr = fpu.mxcsr;
                
                // print("fpu.mxcsr 0x%x\n", fpu.mxcsr);
            }
            
            {
                // 
                // Synchronize the local apic state.
                // This does not really work, as linux does not want to tell me the 'isr' and so on.
                // (From what I can tell at least).
                // 
                struct serialized_local_apic local_apic;
                if(ioctl(vcpu_fd, KVM_GET_LAPIC, &local_apic) < 0){
                    perror("KVM_GET_LAPIC");
                    exit(1);
                }
                
                registers->local_apic.task_priority_register        = local_apic.task_priority_register[0];
                registers->local_apic.arbitration_priority_register = local_apic.arbitration_priority_register[0];
                registers->local_apic.processor_priority_register   = local_apic.processor_priority_register[0];
                registers->local_apic.local_destination_register    = local_apic.local_destination_register[0];
                registers->local_apic.destination_format_register   = local_apic.destination_format_register[0];
                registers->local_apic.spurious_interrupt_vector_register = local_apic.spurious_interrupt_vector_register[0];
                
                for(u32 index = 0; index < 8; index++){
                    registers->local_apic.in_service_register[index] = local_apic.in_service_register[index][0];
                    registers->local_apic.trigger_mode_register[index] = local_apic.trigger_mode_register[index][0];
                    registers->local_apic.interrupt_request_register[index] = local_apic.interrupt_request_register[index][0];
                }
                
                registers->local_apic.error_status_register = local_apic.error_status_register[0];
                
                registers->local_apic.local_vector_table.corrected_machine_check_interrupt_register = local_apic.local_vector_table_corrected_machine_check_interrupt_register[0];
                registers->local_apic.local_vector_table.timer_register = local_apic.local_vector_table_timer_register[0];
                registers->local_apic.local_vector_table.thermal_sensor_register = local_apic.local_vector_table_thermal_sensor_register[0];
                registers->local_apic.local_vector_table.performance_monitoring_counters_register = local_apic.local_vector_table_performance_monitoring_counters_register[0];
                registers->local_apic.local_vector_table.lint0_register = local_apic.local_vector_table_lint0_register[0];
                registers->local_apic.local_vector_table.lint1_register = local_apic.local_vector_table_lint1_register[0];
                registers->local_apic.local_vector_table.error_register = local_apic.local_vector_table_error_register[0];
                registers->local_apic.timer_divide_configuration_register = local_apic.timer_divide_configuration_register[0];
                
                registers->local_apic.highest_pending_interrupt = apic__get_highest_set_bit(registers->local_apic.interrupt_request_register);
                registers->local_apic.highest_interrupt_in_service = apic__get_highest_set_bit(registers->local_apic.in_service_register);
            }
        }
        
        if(snapshot_mode_should_break_in_debugger){
            handle_debugger(context);
            snapshot_mode_should_break_in_debugger = 0;
        }
        
        switch(kvm_run->exit_reason){
            
            case KVM_EXIT_DEBUG:{
                
                registers->dr6 = kvm_run->debug.arch.dr6;
                registers->dr7 = kvm_run->debug.arch.dr7;
                
                // Clear one shot breakpoint at the current rip, for example from 'f' or 'n'.
                hypervisor_clear_oneshot_breakpoint(registers, registers->rip);
                
                // If I understand correctly, the dr7 "GD - General Detect Enable" bit is reset on every debug exception.
                // Hence, we have to reset it here.
                registers->dr7 |= (1 << 13);
                
                if(registers->dr6 & (1 << 13)){
                    // Debug register access detected.
                    // This happens when patchguard tries to make sure the debug registers are not set.
                    // Somewhere inside the exception handler of `KiBalanceSetManagerDeferredRoutine`.
                    
                    // Clear the Status bit.
                    registers->dr6 &= ~(1 << 13);
                    
                    u8 *address = translate_address(context, registers->rip, PERMISSION_none); // @cleanup: Cross page instructions
                    struct instruction_information instruction = decode_instruction(address);
                    
                    int handled = 0;
                    if(instruction.augmented_opcode == /*mov regm, dreg*/0x121){
                        if(instruction.mod == MOD_REG){
                            handled = 1;
                            registers->gpr[instruction.regm] = 0; // Reading a debug register will always give 0.
                        }
                    }else if(instruction.augmented_opcode == /*mov dreg, regm*/0x123){
                        handled = 1;
                        
                        // 
                        // For user mode snapshotting, we use the debug registers to cause a breakpoint in the debugger.
                        // Hence, we must allow setting breakpoints here, but not allow removing breakpoints.
                        // 
                        
                        if(instruction.mod == MOD_REG){
                            // 
                            // Allow the very specific case of setting a local breakpoint using dr0.
                            // This is what the `user_snapshot.exe` does.
                            // 
                            if(instruction.reg == 0){
                                // Save of the value we would have written to dr0, so we can write it below.
                                context->potentially_usermode_snapshotting_breakpoint = registers->gpr[instruction.regm];
                            }
                            
                            if(instruction.reg == 7 && registers->gpr[instruction.regm] == 1){
                                // Set the breakpoint the guest has requested as a oneshot breakpoint.
                                hypervisor_set_breakpoint(context, registers, BREAKPOINT_execute, BREAKPOINT_FLAG_oneshot, context->potentially_usermode_snapshotting_breakpoint, 1);
                            }
                        }
                    }
                    
                    if(handled){
                        registers->rip += instruction.instruction_size;
                        
                        if(!globals.single_stepping) continue;
                    }else{
                        print("WARNING: Unhandled Debug Register access!\n");
                    }
                }
                
                // if(Exception->InstructionBytes[0] == /*int1*/0xf1){
                //     // If we hit a natural 0xf1, we want to stop, but then be able to continue.
                //     registers->rip += 1;
                // }
                
                if(globals.print_trace){
                    static u64 static_last_rip;
                    if(static_last_rip != registers->rip) print_registers(context, globals.trace_file);
                    
                    static_last_rip = registers->rip;
                    
                    u64 next_rip = get_address_of_next_instruction(context, registers);
                    
                    int is_terminating_breakpoint = 0;
                    is_terminating_breakpoint |= (registers->dr7 & 2) && registers->dr0 == next_rip;
                    is_terminating_breakpoint |= (registers->dr7 & 8) && registers->dr1 == next_rip;
                    is_terminating_breakpoint |= (registers->dr7 & 0x20) && registers->dr2 == next_rip;
                    is_terminating_breakpoint |= (registers->dr7 & 0x80) && registers->dr3 == next_rip;
                    if(is_terminating_breakpoint){
                        globals.print_trace = false;
                    }
                }else{
                    handle_debugger(context);
                }
                
                
                registers->dr6 &= ~0xf; // Clear the "Condition Detected" bits.
                
                // 
                // Set the resume flag, so we don't immediately break again.
                // 
                registers->RF = 1;
            }break;
            
            case KVM_EXIT_X86_RDMSR:{
                u32 msr_number = kvm_run->msr.index;
                if(msr_number == BIOS_break){
                    print("Bios Breakpoint\n");
                    handle_debugger(context);
                }else if(msr_number == BIOS_crash){
                    print("Bios crash\n");
                    handle_debugger(context);
                    exit(1);
                }else{
                    helper_rdmsr(context, registers);
                    
                    u64 value = (registers->rdx << 32) | registers->rax;
                    
                    kvm_run->msr.data = value;
                }
            }break;
            
            case KVM_EXIT_X86_WRMSR:{
                u32 msr_number = kvm_run->msr.index;
                u64 msr_input_value = kvm_run->msr.data;
                
                if(msr_number == HV_X64_MSR_EOM){
                    vmbus_offer_channel(context); // :AEOI_on_linux
                }else{
                    helper_wrmsr(context, registers);
                }
                
            }break;
            
            case KVM_EXIT_IO:{ 
                // kvm_run->io.direction;
                // kvm_run->io.size;
                // kvm_run->io.port;
                // kvm_run->io.count;
                // kvm_run->io.data_offset;
                
                u8 *data = (u8 *)kvm_run + kvm_run->io.data_offset;
                u8  size = kvm_run->io.size;
                u16 port = kvm_run->io.port;
                
                assert(kvm_run->io.count == 1);
                
                if(kvm_run->io.direction == KVM_EXIT_IO_IN){
                    read_from_port_helper(context, registers, port, size);
                    memcpy(data, &registers->rax, size);
                }else if(kvm_run->io.direction == KVM_EXIT_IO_OUT){
                    assert(size <= 4);
                    u32 value = 0;
                    memcpy(&value, data, size);
                    write_to_port_helper(context, registers, port, value);
                }else invalid_code_path();
            }break;
            
            case KVM_EXIT_MMIO:{
                u64 physical_address = kvm_run->mmio.phys_addr;
                u8 *data   = kvm_run->mmio.data;
                u32 length = kvm_run->mmio.len;
                u8 is_write = kvm_run->mmio.is_write;
                
                if((physical_address & ~0xfff) == /*IO APIC base*/0xfec00000){
                    u32 offset = physical_address & 0xfff;
                    if(is_write){
                        io_apic_write(context, offset, data, length);
                    }else{
                        u32 value;
                        io_apic_read(context, offset, data, length); // This does not work for whatever reason.
                    }
                }else if((physical_address & ~0xfff) == /*Local Apic base*/0xfee00000){ // @cleanup: ia32_apic_base?
                    u32 offset = physical_address & 0xfff;
                    if(is_write){
                        local_apic_write(context, offset, data, length);
                    }else{
                        local_apic_read(context, offset, data, length);
                    }
                }else{
                    print("KVM_EXIT_MMIO\n");
                    handle_debugger(context);
                }
                
                if(!is_write){
                    // 
                    // For whatever reason just setting data does not seem to work. I feel like it should.
                    // 
                    
                    u8 *address = translate_address(context, registers->rip, PERMISSION_none); // @cleanup: Cross page instructions
                    struct instruction_information instruction = decode_instruction(address);
                    
                    registers->gpr[instruction.reg] = *(u32 *)data;
                }
            }break;
            
            
            case KVM_EXIT_INTR:{
                // This is only caused by `cancel_virtual_processor`.
                // Which happens on Ctrl-C and when an input is pending.
                
                int did_something = hacky_display_input_handling(context);
                if(did_something) break; // For now, only ever initiate one event in an update.
            }break;
            
            case KVM_EXIT_HYPERV:{
                u32 type = kvm_run->hyperv.type;
                switch(type){
                    case KVM_EXIT_HYPERV_SYNIC:{
                        // @note: We ignore HV_X64_MSR_SCONTROL.
                        u32 msr = kvm_run->hyperv.u.synic.msr;
                        if(msr == HV_X64_MSR_SIMP)  registers->hv_x64_msr_simp  = kvm_run->hyperv.u.synic.msg_page;
                        if(msr == HV_X64_MSR_SIEFP) registers->hv_x64_msr_siefp = kvm_run->hyperv.u.synic.evt_page;
                    }break;
                    case KVM_EXIT_HYPERV_HCALL:{
                        u16 code = kvm_run->hyperv.u.hcall.input & 0xffff;
                        int fast = (kvm_run->hyperv.u.hcall.input >> 16) & 1;
                        u64 in_param  = kvm_run->hyperv.u.hcall.params[0];
                        u64 out_param = kvm_run->hyperv.u.hcall.params[1];
                        
                        kvm_run->hyperv.u.hcall.result = 0;
                        
                        switch(code){
                            
                            case /*HvCallPostMessage*/0x5c:{
                                
                                crash_assert(!fast);
                                
                                u8 *input_buffer = get_physical_memory_for_read(context, in_param);
                                
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
                                crash_assert(fast);
                                
                                u32 connection_id = (u32)in_param;
                                
                                if(0x2000 <= connection_id && connection_id < 0x3000){
                                    // 
                                    // VMBUS connection
                                    // 
                                    
                                    vmbus_handle_event(context, connection_id);
                                }else{
                                    set_crash_information(context, CRASH_internal_error, (u64)"Unhandled connection id in HvCallSignalEvent.");
                                }
                            }break;
                            
                            default:{
                                print("KVM_EXIT_HYPERV_HCALL 0x%x\n", code);
                                handle_debugger(context);
                            }break;
                        }
                    }break;
                    invalid_default_case();
                }
            }break;
            
            case KVM_EXIT_HLT:{
                
                // :timer_interrupts
                u64 time_reference_counter = calculate_time_reference_counter(context, registers);
                double time_to_sleep = (double)((s64)context->next_timer_interrupt_time_or_zero - (s64)time_reference_counter) * 100.0 / 1.0e+9;
                if(time_to_sleep > 0){
                    s64 time_to_sleep_micros = (s64)(1000000.0 * time_to_sleep);
                    if(time_to_sleep_micros > 16000) time_to_sleep_micros = 16000;
                    usleep((useconds_t)time_to_sleep_micros);
                }
                
                pend_timer_interrupt(context, registers, context->next_timer_interrupt_time_or_zero);
                
                if(!(registers->hv_x64_msr_stimer0_config & /*periodic*/2)){
                    registers->hv_x64_msr_stimer0_count = 0;
                    
                    context->next_timer_interrupt_time_or_zero = 0;
                }else{
                    context->next_timer_interrupt_time_or_zero = time_reference_counter + registers->hv_x64_msr_stimer0_count;
                }
            }break;
            
            case KVM_EXIT_FAIL_ENTRY:{
                __u64 hardware_entry_failure_reason = kvm_run->fail_entry.hardware_entry_failure_reason;
                __u32 cpu = kvm_run->fail_entry.cpu;
                
                print("hardware_entry_failure_reason > 0x%llx\n", hardware_entry_failure_reason);
                print("cpu > %d\n", cpu);
                print("kvm_run->s.regs.events.interrupt.injected = %d\n", kvm_run->s.regs.events.interrupt.injected);
                
                kvm_run->s.regs.events.interrupt.injected = 0;
                kvm_run->kvm_dirty_regs |= KVM_SYNC_X86_EVENTS;
                
                handle_debugger(context);
            }break;
            
            default:{
                print("Unknown reason %d\n", kvm_run->exit_reason);
                handle_debugger(context);
            }break;
        }   
        
        
        if(context->crash){
            // This can happen for example for unhandled ports or msr's.
            // So handle this more gracefully.
            
            print_crash_information(context, &context->crash_information);
            handle_debugger(context);
        }
    }
}

void cancel_virtual_processor(void){
    if(!g_kvm_thread) return;
    
    if(snapshot_mode_should_break_in_debugger || events_processed != events_initiated){
        pthread_kill(g_kvm_thread, SIGUSR1);
    }
}

