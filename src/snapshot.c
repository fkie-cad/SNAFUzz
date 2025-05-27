// 
// The snapshot file format.
// 
// Overview:
//     header (magic, version)
//     directory [start, end]
//     
//     [0] disk state
//     [1] vmbus state
//     [2] registers
//     [3] physical memory
// 
// Snapshots are written from the debugger using the 'snapshot <file-name>' command
// and can be loaded as a parameter. The snapshot file and in particular the 
// guest physical memory is memory mapped to speed up startup times.
// 

static char snapshot_magic[32]   = "arstneio-snapshot";
static char snapshot_version[32] = __DATE__ " " __TIME__;

int load_snapshot(struct context *context, char *file_name){
    
    struct file file = memory_map_file(file_name, null, /*copy_on_write*/1);
    if(!file.memory) return 0; // Error was reported inside 'memory_map_file'.
    
    struct {
        u64 start_offset;
        u64 end_offset;
    } directory[4] = {0};
    
    if(file.size < sizeof(snapshot_magic) + sizeof(snapshot_version) + sizeof(directory)){
        print("File '%s' is too small to be a snapshot file.\n", file_name);
        return 0;
    }
    
    if(memcmp(file.memory, snapshot_magic, sizeof(snapshot_magic)) != 0){
        print("File '%s' is not a snapshot file.\n", file_name);
        return 0;
    }
    
    if(memcmp(file.memory + sizeof(snapshot_magic), snapshot_version, sizeof(snapshot_version)) != 0){
        print("File '%s' was created with a different version of the fuzzer.\n", file_name);
        print("    Current version: %.32s.\n", snapshot_version);
        print("    File version: %.32s.\n", file.memory + sizeof(snapshot_magic));
        print("\n");
        
        int should_load = yes_no_stop_point("Load anyway?", /*force*/0);
        if(!should_load) return 0;
    }
    
    memcpy(directory, file.memory + sizeof(snapshot_magic) + sizeof(snapshot_version), sizeof(directory));
    
    {
        int corrupt = -1;
        
        for(u32 index = 0; index < array_count(directory); index++){
            if(directory[index].start_offset > file.size) corrupt = index;
            if(directory[index].end_offset   > file.size) corrupt = index;
            if(directory[index].start_offset > directory[index].end_offset) corrupt = index;
        }
        
        if(corrupt != -1){
            print("Error: Snapshot file '%s' has a corrupted directory entry at index %d.\n", file_name, corrupt);
            return 0;
        }
    }
    
    {   // 
        // Load the temporary write nodes.
        // 
        u64 *disk_section_start = (u64 *)(file.memory + directory[0].start_offset);
        
        // @cleanup: checks.
        u64 amount_of_write_nodes  = disk_section_start[0];
        u64 file_modification_time = disk_section_start[1];
        u64 full_file_path_size    = disk_section_start[2];
        u8 *full_file_path_data    = (u8 *)&disk_section_start[3]; // Needs to be zero terminated...
        
        if(full_file_path_size){
            int skip_file_modification_time_check = false;
            
            if(!globals.vhdx_info.mapped_address){
                // 
                // We have not loaded the 'vhdx' yet, load it from this information.
                // 
                int parse_vhdx_success = parse_vhdx((char *)full_file_path_data);
                
                if(!parse_vhdx_success){
                    int should_continue = yes_no_stop_point("Continue anyway?", /*force*/0);
                    if(!should_continue) return 0;
                }
                
                // if(!parse_vhdx_success) return 0;
            }else{
                
                if(!string_match((struct string){.data = (char *)full_file_path_data, .size = full_file_path_size}, globals.vhdx_info.full_file_path)){
                    print("Snapshot '%s' specifies a different disk than was loaded.\n", file_name);
                    print("    Snapshot-disk: '%.*s'.\n", full_file_path_size, full_file_path_data);
                    print("    Loaded-disk:   '%.*s'.\n", globals.vhdx_info.full_file_path.size, globals.vhdx_info.full_file_path.data);
                    print("\n");
                    
                    int should_continue = yes_no_stop_point("Continue?", /*force*/0);
                    if(!should_continue) return 0;
                    
                    skip_file_modification_time_check = true;
                }
            }
            
            if(!skip_file_modification_time_check && (file_modification_time != globals.vhdx_info.file_modification_time)){
                print("Disk Image '%.*s' changed since snapshot was taken.\n", full_file_path_size, full_file_path_data);
                int should_continue = yes_no_stop_point("Continue?", /*force*/0);
                if(!should_continue) return 0;
            }
        }
        
        u64 *write_nodes     = (u64 *)(full_file_path_data + ((full_file_path_size + /*zero-terminator*/1 + 7) & ~7));
        u64 *write_nodes_end = write_nodes + 2 * amount_of_write_nodes;
        
        u8 *blocks_at = file.memory + ((((u8 *)write_nodes_end - file.memory) + 0x1ff) & ~0x1ff);
        
        for(u64 index = 0; index < amount_of_write_nodes; index++){
            u64 logical_block_address     = write_nodes[2 * index + 0];
            u64 transfer_length_in_blocks = write_nodes[2 * index + 1];
            vhdx_push_temporary_write_node(context, &context->permanent_arena, blocks_at, logical_block_address, transfer_length_in_blocks);
            
            blocks_at += 0x200 * transfer_length_in_blocks;
        }
    }
    
    {   // 
        // Load the 'vmbus' section.
        // 
        
        u64 *vmbus_section_start = (u64 *)(file.memory + directory[1].start_offset);
        
        // Clear the old state.
        context->vmbus.channels = null;
        context->vmbus.gpadls   = null;
        
        u64 amount_of_channels = vmbus_section_start[0];
        u64 amount_of_gpadls   = vmbus_section_start[1];
        u64 monitor_page1      = vmbus_section_start[2];
        u64 monitor_page2      = vmbus_section_start[3];
        u64 channel_offer_at   = vmbus_section_start[4];
        
        context->vmbus.monitor_page1 = monitor_page1;
        context->vmbus.monitor_page2 = monitor_page2;
        context->vmbus.channel_offer_at = (u32)channel_offer_at;
        
        u32 *at = (u32 *)(vmbus_section_start + 5);
        
        // @hmm: We reverse the order here, does that matter?
        
        for(u64 index = 0; index < amount_of_channels; index++){
            struct vmbus_channel *channel = push_struct(&context->permanent_arena, struct vmbus_channel);
            
            channel->next = context->vmbus.channels;
            context->vmbus.channels = channel;
            
            channel->device_kind   = *at++;
            channel->channel_id    = *at++;
            channel->connection_id = *at++;
            channel->monitor_id    = (u8)*at++;
            channel->gpadl_id      = *at++;
            channel->read_ring_buffer_pages = *at++;
        }
        
        u64 *pages_at = (u64 *)(at + 3 * amount_of_gpadls + (amount_of_gpadls & 1));
        for(u64 index = 0; index < amount_of_gpadls; index++){
            
            u32 channel_id = *at++;
            u32 gpadl_id   = *at++;
            u32 amount_of_pages   = *at++;
            
            struct gpadl *gpadl = (void *)push_data(&context->permanent_arena, u8, sizeof(struct gpadl) + amount_of_pages * sizeof(u64));
            gpadl->channel_id      = channel_id;
            gpadl->gpadl_id        = gpadl_id;
            gpadl->amount_of_pages = amount_of_pages;
            
            memcpy(gpadl->pages, pages_at, amount_of_pages * sizeof(gpadl->pages[0]));
            pages_at += amount_of_pages;
            
            gpadl->next = context->vmbus.gpadls;
            context->vmbus.gpadls = gpadl;
        }
        
        assert((void *)pages_at == (void *)(file.memory + directory[1].end_offset));
        
        // 
        // Initialize the 'read_buffer' and 'send_buffer' for each channel.
        // 
        
        for(struct vmbus_channel *channel = context->vmbus.channels; channel; channel = channel->next){
            struct gpadl *gpadl = context->vmbus.gpadls;
            
            // Search for the corresponding gpadl.
            for(; gpadl; gpadl = gpadl->next){
                if(gpadl->gpadl_id == channel->gpadl_id) break;
            }
            
            if(!gpadl){
                print("Warning: Snapshot file '%s' contains a VMBUS channel which does not have a corresponding GPADL.\n", file_name);
                continue;
            }
            
            vmbus_channel_initialize_ringbuffers(channel, gpadl);
            
            // 
            // @note: Only initialize these pointers if there is a gpadl,
            //        otherwise we might try to send inputs before there is a gpadl and that might crash.
            //        If there is no gpadl, this was likely a snapshot prior to the guest opening the channel.
            // 
            if(channel->device_kind == VMBUS_DEVICE_mouse)    context->vmbus.mouse = channel;
            if(channel->device_kind == VMBUS_DEVICE_keyboard) context->vmbus.keyboard = channel;
        }
    }
    
    {   // 
        // Load the registers.
        // 
        struct registers *registers_section_start = (struct registers *)(file.memory + directory[2].start_offset);
        globals.snapshot.registers = context->registers = *registers_section_start;
        
    }
    
    {   // 
        // Load the physical memory.
        // 
        u8 *memory_section_start = file.memory + directory[3].start_offset;
        globals.snapshot.physical_memory = memory_section_start;
        globals.snapshot.physical_memory_size = directory[3].end_offset - directory[3].start_offset;
        
        u64 page_bitmap_size = globals.snapshot.physical_memory_size/(0x1000 * 8);
        context->physical_memory = globals.snapshot.physical_memory;
        context->physical_memory_size = globals.snapshot.physical_memory_size;
        context->physical_memory_copied   = os_allocate_memory(page_bitmap_size);
        context->physical_memory_executed = os_allocate_memory(page_bitmap_size);
        memset(context->physical_memory_copied, 0xff, page_bitmap_size);
    }
    
    print("Successfully loaded '%s'.\n", file_name);
    return 1;
}


void write_snapshot(struct context *context, char *file_name){
    
    if(!cstring_ends_with_case_insensitive(file_name, ".snapshot")){
        size_t file_name_size = strlen(file_name);
        char *buffer = malloc(file_name_size + sizeof(".snapshot"));
        memcpy(buffer, file_name, file_name_size);
        memcpy(buffer + file_name_size, ".snapshot", sizeof(".snapshot"));
        file_name = buffer;
    }
    
    FILE *file = fopen(file_name, "wb");
    if(!file){
        print("Error: Could not open '%s' file.\n", file_name);
        return;
    }
    
    // 
    // Calculate the size for the 'temporary_write_nodes'.
    // 
    u64 amount_of_write_nodes = 0;
    u64 total_blocks = 0;
    
    for(struct vhdx_temporary_write_node *node = context->temporary_write_nodes.first; node; node = node->next){
        amount_of_write_nodes += 1;
        total_blocks += node->transfer_length_in_blocks;
    }
    
    // disk write headers:
    //     u64 amount_of_write_nodes;
    //     u64 file_modification_time;
    //     u64 file_path_size;
    //     u8  file_path[(file_path_size + 7) & ~7];
    //     
    // temporary_write_nodes:
    //     u64 logical_block_address;
    //     u64 transfer_length_in_blocks;
    //     
    // <blocks>
    
    struct string full_file_path = globals.vhdx_info.full_file_path;
    u8 aligned_path_size = ((full_file_path.size + /*zero-terminator*/1 + 7) & ~7);
    
    u64 temporary_write_nodes_header_size = 3 * sizeof(u64) + aligned_path_size + 2 * sizeof(u64) * amount_of_write_nodes;
    u64 temporary_write_nodes_size = ((temporary_write_nodes_header_size + 0x1ff) & ~0x1ff) + 0x200 * total_blocks;
    
    // 
    // Calculate the size for the 'vmbus'.
    // 
    u64 amount_of_gpadls   = 0;
    u64 amount_of_channels = 0;
    u64 amount_of_gpadl_pages = 0;
    
    for(struct vmbus_channel *channel = context->vmbus.channels; channel; channel = channel->next){
        amount_of_channels += 1;
    }
    
    for(struct gpadl *gpadl = context->vmbus.gpadls; gpadl; gpadl = gpadl->next){
        amount_of_gpadls += 1;
        amount_of_gpadl_pages += gpadl->amount_of_pages;
    }
    
    // 
    // vmbus data header:
    //     u64 amount_of_channel;
    //     u64 amount_of_gpadl;
    //     u64 monitor_page1;
    //     u64 monitor_page2;
    //     u64 channel_offer_at;
    // 
    // channels:
    //     u32 device_kind;
    //     u32 channel_id;
    //     u32 connection_id;
    //     u32 monitor_id;
    //     u32 gpadl_id;
    //     u32 read_ring_buffer_pages;
    // 
    // gpadl:
    //     u32 channel_id;
    //     u32 gpadl_id;
    //     u32 amount_of_pages;
    // 
    // <gpadl_pages>
    //     
    
    u64 vmbus_size = 
            /*header*/5 * sizeof(u64) + 
            /*channels*/amount_of_channels * 6 * sizeof(u32) + 
            /*gpadls*/amount_of_gpadls * 3 * sizeof(u32) + 
            /*alignment*/(amount_of_gpadls & 1) * sizeof(u32) + 
            /*gpadl_pages*/amount_of_gpadl_pages * sizeof(u64);
    
    u64 registers_size = sizeof(struct registers);
    
    u64 physical_memory_size = globals.snapshot.physical_memory_size;
    
    // directory:
    //     u64 start_offset;
    //     u64 end_offset;
    
    struct {
        u64 start_offset;
        u64 end_offset;
    } directory[4] = {0};
    
    u64 current_offset = (64 + sizeof(directory) + 0x1ff) & ~0x1ff;
    
    // Temporary write nodes.
    directory[0].start_offset = current_offset;
    current_offset += temporary_write_nodes_size;
    directory[0].end_offset = current_offset;
    
    // vmbus.
    directory[1].start_offset = current_offset;
    current_offset += vmbus_size;
    directory[1].end_offset = current_offset;
    
    // registers.
    directory[2].start_offset = current_offset;
    current_offset += registers_size;
    directory[2].end_offset = current_offset;
    
    current_offset = (current_offset + 0xfff) & ~0xfff;
    
    // physical memories.
    directory[3].start_offset = current_offset;
    current_offset += physical_memory_size;
    directory[3].end_offset = current_offset;
    
    static u8 zero_buffer[0x1000];
    
    fwrite(snapshot_magic,   1, sizeof(snapshot_magic),   file);
    fwrite(snapshot_version, 1, sizeof(snapshot_version), file);
    
    fwrite(directory, sizeof(directory), 1, file);
    fwrite(zero_buffer, directory[0].start_offset - (64 + sizeof(directory)), 1, file);
    
    assert((u64)ftell64(file) == directory[0].start_offset);
    
    // 
    // Write the 'temporary_write_nodes'.
    // 
    fwrite(&amount_of_write_nodes, sizeof(u64), 1, file);
    fwrite(&globals.vhdx_info.file_modification_time, sizeof(u64), 1, file);
    fwrite(&full_file_path.size, sizeof(u64), 1, file);
    fwrite(full_file_path.data, full_file_path.size, 1, file);
    fwrite(zero_buffer, aligned_path_size - full_file_path.size, 1, file);
    
    for(struct vhdx_temporary_write_node *node = context->temporary_write_nodes.first; node; node = node->next){
        struct{
            u64 logical_block_address;
            u64 transfer_length_in_blocks;
        } write_nodes = {
            .logical_block_address     = node->logical_block_address,
            .transfer_length_in_blocks = node->transfer_length_in_blocks,
        };
        fwrite(&write_nodes, sizeof(write_nodes), 1, file);
    }
    
    u64 temporary_write_nodes_aligned_header_size = (temporary_write_nodes_header_size + 0x1ff) & ~0x1ff;
    fwrite(zero_buffer, temporary_write_nodes_aligned_header_size - temporary_write_nodes_header_size, 1, file);
    
    for(struct vhdx_temporary_write_node *node = context->temporary_write_nodes.first; node; node = node->next){
        fwrite(node->buffer, 0x200, node->transfer_length_in_blocks, file);
    }
    
    assert((u64)ftell64(file) == directory[0].end_offset);
    assert((u64)ftell64(file) == directory[1].start_offset);
    
    // 
    // Write the 'vmbus' section.
    // 
    struct{
        u64 amount_of_channels;
        u64 amount_of_gpadls;
        u64 monitor_page1;
        u64 monitor_page2;
        u64 channel_offer_at;
    } vmbus_header = {
        .amount_of_channels = amount_of_channels,
        .amount_of_gpadls   = amount_of_gpadls,
        .monitor_page1 = context->vmbus.monitor_page1,
        .monitor_page2 = context->vmbus.monitor_page2,
        .channel_offer_at = context->vmbus.channel_offer_at,
    };
    fwrite(&vmbus_header, sizeof(vmbus_header), 1, file);
    
    for(struct vmbus_channel *channel = context->vmbus.channels; channel; channel = channel->next){
        
        struct{
            u32 device_kind;
            u32 channel_id;
            u32 connection_id;
            u32 monitor_id;
            u32 gpadl_id;
            u32 read_ring_buffer_pages;
        } channel_info = {
            .device_kind = channel->device_kind,
            .channel_id  = channel->channel_id,
            .connection_id  = channel->connection_id,
            .monitor_id  = channel->monitor_id,
            .gpadl_id  = channel->gpadl_id,
            .read_ring_buffer_pages = channel->read_ring_buffer_pages,
        };
        
        fwrite(&channel_info, sizeof(channel_info), 1, file);
    }
    
    for(struct gpadl *gpadl = context->vmbus.gpadls; gpadl; gpadl = gpadl->next){
        struct{
            u32 channel_id;
            u32 gpadl_id;
            u32 amount_of_pages;
        } gpadl_info = {
            .channel_id = gpadl->channel_id,
            .gpadl_id   = gpadl->gpadl_id,
            .amount_of_pages = gpadl->amount_of_pages,
        };
        
        fwrite(&gpadl_info, sizeof(gpadl_info), 1, file);
    }
    
    if(amount_of_gpadls & 1) fwrite(zero_buffer, sizeof(u32), 1, file);
    
    for(struct gpadl *gpadl = context->vmbus.gpadls; gpadl; gpadl = gpadl->next){
        fwrite(gpadl->pages, sizeof(u64), gpadl->amount_of_pages, file);
    }
    
    assert((u64)ftell64(file) == directory[1].end_offset);
    assert((u64)ftell64(file) == directory[2].start_offset);
    
    
    {
        u64 dr0 = context->registers.dr0;
        u64 dr1 = context->registers.dr1;
        u64 dr2 = context->registers.dr2;
        u64 dr3 = context->registers.dr3;
        u64 dr6 = context->registers.dr3;
        u64 dr7 = context->registers.dr7;
        
        // 
        // @Note: Remove all the breakpoints from the snapshot.
        // 
        
        context->registers.dr0 = 0;
        context->registers.dr1 = 0;
        context->registers.dr2 = 0;
        context->registers.dr3 = 0;
        context->registers.dr3 = 0;
        context->registers.dr7 = 0;
        
        fwrite(&context->registers, sizeof(context->registers), 1, file);
        
        context->registers.dr0 = dr0;
        context->registers.dr1 = dr1;
        context->registers.dr2 = dr2;
        context->registers.dr3 = dr3;
        context->registers.dr3 = dr6;
        context->registers.dr7 = dr7;
    }
    
    assert((u64)ftell64(file) == directory[2].end_offset);
    
    fwrite(zero_buffer, 1, directory[3].start_offset - directory[2].end_offset, file);
    
    assert((u64)ftell64(file) == directory[3].start_offset);
    
    fwrite(context->physical_memory, 1, context->physical_memory_size, file);
    
    assert((u64)ftell64(file) == directory[3].end_offset);
    
    fclose(file);
    
    print("Success fully written snapshot '%s'.\n", file_name);
}

