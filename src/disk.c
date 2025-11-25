
static int parse_disk(char *file_name){
    
    HANDLE file_handle = {0};
    int success = 0;
    
    enum virtual_disk_kind kind = 0;
    if(cstring_ends_with_case_insensitive(file_name, ".vhdx"))  kind = VIRTUAL_DISK_vhdx;
    if(cstring_ends_with_case_insensitive(file_name, ".qcow2")) kind = VIRTUAL_DISK_qcow2;
    if(strnicmp(file_name, RAW_DISK_STRING, sizeof(RAW_DISK_STRING)-1) == 0)     kind = VIRTUAL_DISK_raw; 
    
    switch(kind){
        case VIRTUAL_DISK_vhdx:  success = parse_vhdx(file_name, &file_handle);  break;
        case VIRTUAL_DISK_qcow2: success = parse_qcow2(file_name, &file_handle); break;
        case VIRTUAL_DISK_raw:   success = parse_raw_disk(file_name, &file_handle); break;
        invalid_default_case();
    }
    
    if(!success) return 0;
    
    globals.disk_info.file_handle = file_handle;
    
#if _WIN32
    
    // Get the file modification time of the disk file.
    if(!GetFileTime(file_handle, null, null, &globals.disk_info.modification_time)){
        globals.disk_info.modification_time = 0;
    }
    
    // Get the full path of the disk file.
    u8 PathBuffer[/*MAX_PATH*/260];
    u32 PathLength = GetFinalPathNameByHandleA(file_handle, PathBuffer, sizeof(PathBuffer), /*VOLUME_NAME_DOS*/0);
#else
    // Get the file modification time of the disk file.
    struct stat stat_buffer;
    fstat((int)file_handle.Unused, &stat_buffer);
    globals.disk_info.modification_time = stat_buffer.st_mtime;
    
    // Get the full path of the disk file. (A little linux terribleness included)
    char PathBuffer[PATH_MAX];
    snprintf(PathBuffer, sizeof(PathBuffer), "/proc/self/fd/%d", (int)file_handle.Unused);
    ssize_t PathLength = readlink(PathBuffer, PathBuffer, sizeof(PathBuffer));
#endif
    
    if(PathLength <= 0 || PathLength > sizeof(PathBuffer)){
        size_t len = strlen(file_name);
        PathLength = (u32)(len > 0x1000 ? 0x1000 : len);
        print("Warning: Failed to get the full path for disk '%s'.\n", file_name);
        
        if(PathLength > sizeof(PathBuffer)){
            print("         Huh? Path length (%llx) exceeds MAX_PATH? Only saving %.259s\n", PathLength, PathBuffer);
            PathLength = 259;
        }
        
        memcpy(PathBuffer, file_name, PathLength);
        PathBuffer[PathLength] = 0;
        
        print("         This means that, when taking a snapshot, relative disk-path '%s' will be saved.\n", file_name);
    }
    
    
    globals.disk_info.full_file_path.data = memcpy(malloc(PathLength + 1), PathBuffer, PathLength + 1);
    globals.disk_info.full_file_path.size = PathLength;
    
    return 1;
}

static u8 *disk_read_sectors(struct memory_arena *arena, u64 total_sectors_to_read, u64 sector){
    switch(globals.disk_info.virtual_disk_kind){
        case VIRTUAL_DISK_vhdx:  return vhdx_read_sectors(arena, total_sectors_to_read, sector);
        case VIRTUAL_DISK_qcow2: return qcow2_read_sectors(arena, total_sectors_to_read, sector);
        case VIRTUAL_DISK_raw:   return raw_disk_read_sectors(arena, total_sectors_to_read, sector);
        invalid_default_case();
    }
}


//_____________________________________________________________________________________________________________________
// Temporary write implementation.

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


static void disk_register_temporary_write(struct context *context, u8 *Buffer, u64 LogicalBlockAddress, u64 TransferLengthInBlocks){
    assert(globals.disk_info.sector_size_in_bytes == 0x200); // currently we assume this in `get_or_allocate_tempoary_write_block`.
    
    for(u64 BlockIndex = 0; BlockIndex < TransferLengthInBlocks; BlockIndex++){
        u8 *block = get_or_allocate_tempoary_write_block(context, LogicalBlockAddress + BlockIndex);
        memcpy(block, Buffer + globals.disk_info.sector_size_in_bytes * BlockIndex, globals.disk_info.sector_size_in_bytes);
    }
}

static void disk_apply_temporary_writes(struct context *context, u8 *destination, u64 LogicalBlockAddress, u64 TransferLengthInBlocks){
    
    for(u64 BlockIndex = 0; BlockIndex < TransferLengthInBlocks; BlockIndex++){
        u8 *block = get_tempoary_write_block(context, LogicalBlockAddress + BlockIndex);
        if(block){
            memcpy(destination + globals.disk_info.sector_size_in_bytes * BlockIndex, block, globals.disk_info.sector_size_in_bytes);
        }
    }
}

