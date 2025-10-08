
//
// A parser implementation of the VHDX (Virtual hard disk) file format.
//
// This is a very, very ad-hoc implementation. It only allows reading and no differencing.
// The only two functions are 'parse_vhdx' which memory maps the specified VHDX and writes some globals,
// and 'vhdx_read_sectors' which reads a run of sectors after the VHDX has been memory mapped.
// 
//                                                                            - Pascal Beyer 13.02.2023
// 
// Update:
// 
// We now also have a very simple 'temporary_write' implementation in this file.
// The idea is to just keep a list of all writes performed in 'context->temporary_write_nodes'.
// Whenever a read occurs, we then 'vhdx_apply_temporary_writes'.
// When fuzzing, we also apply the temporary write nodes of the main thread 
// (globals.main_thread_context->temporary_write_nodes).
// This allows us to reset the disk writes to the snapshot by simply clearing
// 'context->temporary_write_nodes'.
// 
//                                                                            - Pascal Beyer 29.02.2024

int parse_vhdx(char *file_name){
    
    print("Loading .vhdx '%s'\n", file_name);
    
    HANDLE file_handle = {0};
    
    struct file file = memory_map_file(file_name, &file_handle, /*copy_on_write*/0);
    if(!file.memory) return 0;
    
    // 
    // 0x00000 | File Id.
    // 0x10000 | Header 1 
    // 0x20000 | Header 2 
    // 0x30000 | Region Table 
    // 0x40000 | Reserved  (to 1MB)
    //
    u8 *file_end = file.memory + file.size;
    
    u8 * MapAddress = file.memory;
    char *FileIdHeader = (char *)MapAddress;
    
    if((file.size < sizeof("vhdxfile") - 1) || (strncmp("vhdxfile", FileIdHeader, sizeof("vhdxfile") - 1) != 0)){
        print("["__FUNCTION__"] Error: Invalid signature for disk '%s'.\n", file_name);
        return 0;
    }
    
    //
    // We ignore both 'Header 1' and 'Header 2' for now.
    //
    
    struct{
        u32 signature;
        u32 checksum;
        u32 entry_count;
        u32 reserved;
        
        struct {
            struct guid guid;
            u64 file_offset;
            u32 length;
            u32 data_bits;
        } region_entry_table[1];
        
    } *region_header = (void *)(MapAddress + 0x30000);
    
    if((u8 *)(region_header + 1) > file_end || (u8 *)(region_header->region_entry_table + region_header->entry_count) > file_end){
        print("["__FUNCTION__"] Error: Corrupt file '%s'.\n", file_name);
        return 0;
    }
    
    // Block Allocation Table.
    u64 bat_table_offset = 0, metadata_offset = 0;
    u64 bat_table_size   = 0, metadata_size   = 0;
    
    for(u32 entry_index = 0; entry_index < region_header->entry_count; entry_index++){
        struct guid guid = region_header->region_entry_table[entry_index].guid;
        
        u64 FileOffset = region_header->region_entry_table[entry_index].file_offset;
        u64 Length     = region_header->region_entry_table[entry_index].length;
        
        static struct guid bat_guid = {0x2dc27766, 0xf623, 0x4200, 0x9d, 0x64, 0x11, 0x5e, 0x9b, 0xfd, 0x4a, 0x08};
        if(memcmp(&bat_guid, &guid, sizeof(guid)) == 0){
            bat_table_offset = FileOffset;
            bat_table_size   = Length;
        }
        
        static struct guid metadata_guid = {0x8b7ca206, 0x4790, 0x4b9a, 0xb8, 0xfe, 0x57, 0x5f, 0x05, 0x0f, 0x88, 0x6e};
        if(memcmp(&metadata_guid, &guid, sizeof(guid)) == 0){
            metadata_offset = FileOffset;
            metadata_size   = Length;
        }
    }
    
    if(!metadata_offset || !bat_table_offset){
        print("["__FUNCTION__"] Error: Could not find all necessary objects in disk '%s'.\n", file_name);
        return 0;
    }
    
    if(metadata_offset > file.size || bat_table_offset > file.size){
        print("["__FUNCTION__"] Error: Corrupt file '%s'.\n", file_name);
        return 0;
    }
    
    struct{
        u64 signature;
        u16 reserved;
        u16 entry_count;
        u32 reserved2[5];
        struct {
            struct guid guid;
            u32 offset;
            u32 length;
            u32 data_bits;
            u32 reserved;
        } entries[1];
    } *metadata_table = (void *)(MapAddress + metadata_offset);
    
    if((u8 *)(metadata_table + 1) > file_end || (u8 *)(metadata_table->entries + metadata_table->entry_count) > file_end){
        print("["__FUNCTION__"] Error: Corrupt file '%s'.\n", file_name);
        return 0;
    }
    
    u32 block_size = 0;
    u64 virtual_disk_size = 0;
    u32 logical_sector_size = 0;
    u32 physical_sector_size = 0;
    
    for(u32 metadata_table_index = 0; metadata_table_index < metadata_table->entry_count; metadata_table_index++){
        struct guid guid = metadata_table->entries[metadata_table_index].guid;
        
        u64 offset = metadata_table->entries[metadata_table_index].offset + metadata_offset;
        
        if(offset > file.size || offset + 8 > file.size){
            print("["__FUNCTION__"] Error: Corrupt file '%s'.\n", file_name);
            return 0;
        }
        
        char *MetadataBuffer = (char *)(MapAddress + offset);
        
        static struct guid file_param = {0xcaa16737, 0xfa36, 0x4d43, 0xb3, 0xb6, 0x33, 0xf0, 0xaa, 0x44, 0xe7, 0x6b};
        if(memcmp(&file_param, &guid, sizeof(guid)) == 0){
            block_size = *(u32 *)(MetadataBuffer +  0);
        }
        
        static struct guid virtual_size = {0x2fa54224, 0xcd1b, 0x4876, 0xb2, 0x11, 0x5d, 0xbe, 0xd8, 0x3b, 0xf4, 0xb8};
        if(memcmp(&virtual_size, &guid, sizeof(guid)) == 0){
            virtual_disk_size = *(u64 *)MetadataBuffer;
        }
        
        static struct guid logical_sector = {0x8141bf1d, 0xa96f, 0x4709, 0xba, 0x47, 0xf2, 0x33, 0xa8, 0xfa, 0xab, 0x5f};
        if(memcmp(&logical_sector, &guid, sizeof(guid)) == 0){
            logical_sector_size = *(u32 *)MetadataBuffer;
        }
        
        static struct guid phys_sector = {0xcda348c7, 0x445d, 0x4471, 0x9c, 0xc9, 0xe9, 0x88, 0x52, 0x51, 0xc5, 0x56};
        if(memcmp(&phys_sector, &guid, sizeof(guid)) == 0){
            physical_sector_size = *(u32 *)MetadataBuffer;
        }
        
        // static struct guid page83 = {0xbeca12ab, 0xb2e6, 0x4523, 0x93, 0xef, 0xc3, 0x09, 0xe0, 0x00, 0xc7, 0x46};
        // if(memcmp(&page83, &guid, sizeof(guid)) == 0){}
    }
    
    if(!logical_sector_size){
        print("[" __FUNCTION__ "] Error: Could not read the Logical Sector Size.\n");
        return 0;
    }
    
    if(!block_size){
        print("[" __FUNCTION__ "] Error: Could not read the block size.\n");
        return 0;
    }
    
    u64 ChunkRatio = (((u64)logical_sector_size) << 23) / block_size;
    u64 SectorsPerBlock = block_size / logical_sector_size;
    
    u64 amount_of_data_blocks = (u32)((virtual_disk_size + block_size - 1)/block_size);
    
    u64 TotalBlockAllocationTableEntries = amount_of_data_blocks + (amount_of_data_blocks - 1)/ChunkRatio;
    u64 *BlockAllocationTable = (u64 *)(MapAddress + bat_table_offset);
    
    if((u8 *)BlockAllocationTable > file_end || (u8 *)(BlockAllocationTable + TotalBlockAllocationTableEntries) > file_end){
        print("["__FUNCTION__"] Error: Corrupt file '%s'.\n", file_name);
        return 0;
    }
    
    globals.vhdx_info.virtual_disk_size           = virtual_disk_size;
    globals.vhdx_info.block_allocation_table      = BlockAllocationTable;
    globals.vhdx_info.amount_of_bat_table_entries = TotalBlockAllocationTableEntries;
    globals.vhdx_info.mapped_address              = MapAddress;
    globals.vhdx_info.sectors_per_block           = SectorsPerBlock;
    globals.vhdx_info.sector_size_in_bytes        = logical_sector_size;
    globals.vhdx_info.chunk_ratio                 = ChunkRatio;
    
    
#if _WIN32
    
    // Get the file modification time of the vhdx.
    if(!GetFileTime(file_handle, null, null, &globals.vhdx_info.file_modification_time)){
        globals.vhdx_info.file_modification_time = 0;
    }
    
    // Get the full path of the vhdx.
    u8 PathBuffer[/*MAX_PATH*/260];
    u32 PathLength = GetFinalPathNameByHandleA(file_handle, PathBuffer, sizeof(PathBuffer), /*VOLUME_NAME_DOS*/0);
#else
    // Get the file modification time of the vhdx.
    struct stat stat_buffer;
    fstat((int)file_handle.Unused, &stat_buffer);
    globals.vhdx_info.file_modification_time = stat_buffer.st_mtime;
    
    // Get the full path of the vhdx. (A little linux terribleness included)
    char PathBuffer[PATH_MAX];
    snprintf(PathBuffer, sizeof(PathBuffer), "/proc/self/fd/%d", (int)file_handle.Unused);
    ssize_t PathLength = readlink(PathBuffer, PathBuffer, sizeof(PathBuffer));
#endif
    
    if(PathLength <= 0 || PathLength > sizeof(PathBuffer)){
        print("Warning: Failed to get the full path for disk '%s'.\n", file_name);
        print("         This means that, when taking a snapshot, the disk-path will not be saved.\n");
    }else{
        globals.vhdx_info.full_file_path.data = memcpy(malloc(PathLength + 1), PathBuffer, PathLength + 1);
        globals.vhdx_info.full_file_path.size = PathLength;
    }
    
    return 1;
}

u8 *vhdx_read_sectors(struct memory_arena *arena, u64 TotalSectorsToRead, u64 Sector){
    u64 TotalBytesToRead = TotalSectorsToRead * globals.vhdx_info.sector_size_in_bytes;
    u8 *ret = push_data(arena, u8, TotalBytesToRead);
    if(!ret) return null;
    
    for(u64 SectorsTransfered = 0; SectorsTransfered < TotalSectorsToRead; ){
        
        //
        // The 'LogicalBlockAddress' is in sectors, so convert it to 'blocks'.
        //
        u64 BlockIndex = Sector / globals.vhdx_info.sectors_per_block;
        
        //
        // Calculate the offset in sectors in the block (by subtracting the block base).
        //
        u64 BlockOffsetInSectors = Sector - BlockIndex * globals.vhdx_info.sectors_per_block;
        
        // @cleanup: Understand why I have to do this.
        BlockIndex += BlockIndex / globals.vhdx_info.chunk_ratio;
        
        //
        // Calculate how many sectors are left in the block.
        //
        u64 SizeLeftInBlockInSectors = globals.vhdx_info.sectors_per_block - BlockOffsetInSectors;
        
        //
        // Bound the sectors to read.
        //
        u64 SectorsLeftToRead = TotalSectorsToRead - SectorsTransfered;
        u64 SectorsToRead =  (SectorsLeftToRead > SizeLeftInBlockInSectors) ? SizeLeftInBlockInSectors : SectorsLeftToRead;
        u64 BytesToRead   = SectorsToRead * globals.vhdx_info.sector_size_in_bytes;
        
        //
        // Get the block offset and state from the 'BlockAllocationTable'.
        //
        assert(BlockIndex < globals.vhdx_info.amount_of_bat_table_entries);
        u64 BlockAllocationTableEntry = globals.vhdx_info.block_allocation_table[BlockIndex];
        
        u32 EntryState  = (BlockAllocationTableEntry & 7);
        u64 EntryOffset = (BlockAllocationTableEntry & ~0xfffff);
        
        u64 WriteOffset = SectorsTransfered * globals.vhdx_info.sector_size_in_bytes;
        
        if(EntryState == /*PAYLOAD_BLOCK_FULLY_PRESENT*/6){
            u64 FilePosition = EntryOffset + BlockOffsetInSectors * globals.vhdx_info.sector_size_in_bytes;
            memcpy(ret + WriteOffset, globals.vhdx_info.mapped_address + FilePosition, BytesToRead);
        }else{
            memset(ret + WriteOffset, 0, BytesToRead);
        }
        
        SectorsTransfered += SectorsToRead;
        Sector += SectorsToRead;
    }
    return ret;
}


static void *get_or_allocate_tempoary_write_block(struct context *context, u64 logical_block_address){
    u32 page_indices[4] = {
        (logical_block_address >> (39 - 12)) & 0x1ff,
        (logical_block_address >> (30 - 12)) & 0x1ff,
        (logical_block_address >> (21 - 12)) & 0x1ff,
        (logical_block_address >> (12 - 12)) & 0x1ff,
    };
    
    u64 *table = context->temporary_write_table;
    for(u32 page_table_index = 0; page_table_index < array_count(page_indices)-1; page_table_index++){
        u32 page_index = page_indices[page_table_index];
        
        if(!table[page_index]){
            table[page_index] = (u64)push_data(&context->fuzz_run_arena, u64, 0x200);
        }
        
        table = (u64 *)table[page_index];
    }
    
    if(!table[page_indices[3]]){
        table[page_indices[3]] = (u64)push_data(&context->fuzz_run_arena, u8, 0x200);
    }
    table = (u64 *)table[page_indices[3]];
    
    return table;
}


static void *get_tempoary_write_block(struct context *context, u64 logical_block_address){
    u32 page_indices[4] = {
        (logical_block_address >> (39 - 12)) & 0x1ff,
        (logical_block_address >> (30 - 12)) & 0x1ff,
        (logical_block_address >> (21 - 12)) & 0x1ff,
        (logical_block_address >> (12 - 12)) & 0x1ff,
    };
    
    u64 *table = context->temporary_write_table;
    for(u32 page_table_index = 0; page_table_index < array_count(page_indices); page_table_index++){
        u32 page_index = page_indices[page_table_index];
        
        if(!table[page_index]) return null;
        
        table = (u64 *)table[page_index];
    }
    
    return table;
}


static void vhdx_register_temporary_write(struct context *context, u8 *Buffer, u64 LogicalBlockAddress, u64 TransferLengthInBlocks){
    assert(globals.vhdx_info.sector_size_in_bytes == 0x200); // currently we assume this in `get_or_allocate_tempoary_write_block`.
    
    for(u64 BlockIndex = 0; BlockIndex < TransferLengthInBlocks; BlockIndex++){
        u8 *block = get_or_allocate_tempoary_write_block(context, LogicalBlockAddress + BlockIndex);
        memcpy(block, Buffer + globals.vhdx_info.sector_size_in_bytes * BlockIndex, globals.vhdx_info.sector_size_in_bytes);
    }
}

static void vhdx_apply_temporary_writes(struct context *context, u8 *destination, u64 LogicalBlockAddress, u64 TransferLengthInBlocks){
    
    for(u64 BlockIndex = 0; BlockIndex < TransferLengthInBlocks; BlockIndex++){
        u8 *block = get_tempoary_write_block(context, LogicalBlockAddress + BlockIndex);
        if(block){
            memcpy(destination + globals.vhdx_info.sector_size_in_bytes * BlockIndex, block, globals.vhdx_info.sector_size_in_bytes);
        }
    }
}

