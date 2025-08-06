
// 
// Hooks are callbacks which are executed once a certain rip is reached.
//
// If a hook changes the value of the guest rip, the hooked instruction is never executed.
// Otherwise, after the hook the execution continues as normal.
// The hook can also cause a crash (for example by using set_crash_information).
// 
// Good examples of hooks are for example the 'hook_allocate_*' and 'hook_free',
// which are used to apply extra permissions to allocations (i.e implement heap tracking).
// Another good example is the 'hook_bugcheck' which catches and reports bugchecks
// and 'hook_print_stack_trace', which prints a stack trace and then simply continues executing.
//
// To register an hook use the 'register_hook' function. There currently is no way to remove an hook.
// 
//                                                                                - Pascal Beyer 29.02.2024

//_____________________________________________________________________________________________________________________
// Hook API

typedef void hook_callback(struct context *context, struct registers *registers);

#define register_hook(context, rip, hook) register_hook_((context), (rip), (hook), #hook)
static void register_hook_(struct context *context, u64 rip, hook_callback *hook, char *hook_string){
    
    if(globals.fuzzing && !globals.debugger_mode){
        print("Error: Cannot add a hook (%s) after starting to fuzz.\n", hook_string);
        return;
    }
    
    if(!rip){
        print("Warning: Hook %s has rip at NULL. Ignored!\n", hook_string);
        print("         (press enter to continue.)\n");
        getchar();
        return;
    }
    
#if 0
    // 
    // For now we allow putting hooks on arbitrary addresses.
    // We need to allow non-paged-in memory, and I want to be able to use arbitrary (non-canonical) 
    // addresses as escapes from time to time.
    // 
    
    if(address_is_non_canonical(rip)){
        // Allow hooks on non-canonicall addresses.
    }else{
        u64 user_cr3 = patch_in_kernel_cr3(context); // Ensure we can put hooks on kernel addresses.
        u8 *translated = translate_address(context, rip, PERMISSION_execute);
        context->registers.cr3 = user_cr3;
        
        if(!translated){
            print("Warning: Hook %s has a canonical rip, but does not point to executable memory.\n", hook_string);
            print("         (press enter to continue.)\n");
            getchar();
            return; // @cleanup: Allow this?
        }
    }
#endif
    
    print("Adding hook '%s' to ", hook_string); print_symbol(context, rip); print("\n");
    
    u64 x = rip;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    
    for(u64 i = 0; i < array_count(globals.hook_table); i++){
        int index = (x + i) & (array_count(globals.hook_table) - 1);
        if(globals.hook_table[index].rip == 0 || globals.hook_table[index].rip == (u64)-1){
            globals.hook_table[index].hook = hook;
            globals.hook_table[index].rip  = rip;
            
            return;
        }else if(globals.hook_table[index].rip == rip){
            print("Error: Same address hook twice. (Hook %s)\n", hook_string);
            print("       Hooked-Symbol: "); print_symbol(context, rip); print("\n");
            os_panic(1);
        }
    }
    print("Error: Hook table full. Currently maximally %d hooks. Change 'HOOK_TABLE_SIZE' in options.c (must be a power of two).\n", array_count(globals.hook_table));
    os_panic(1);
}

static struct hook *lookup_hook(u64 rip){
    
    u64 x = rip;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    
    for(u64 i = 0; i < array_count(globals.hook_table); i++){
        int index = (x + i) & (array_count(globals.hook_table) - 1);
        if(globals.hook_table[index].rip == 0) return null;
        
        if(globals.hook_table[index].rip == rip){
            return &globals.hook_table[index];
        }
    }
    
    print("[" __FUNCTION__ "] Internal error: Hook table full.\n");
    os_panic(1);
}

