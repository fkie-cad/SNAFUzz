
int parse_raw_disk(char *file_name, HANDLE *file_handle){
    globals.disk_info.virtual_disk_kind = VIRTUAL_DISK_raw;
    globals.disk_info.sector_size_in_bytes = 512;
    globals.disk_info.mapped_address = (void *)1; // Kinda weird, but this needs to be set.
    
    *file_handle = CreateFileA(file_name, /*GENERIC_READ*/0x80000000L, /*FILE_SHARE_READ | FILE_SHARE_WRITE*/3, null, /*OPEN_EXISTING*/3, /*FILE_ATTRIBUTE_NORMAL*/0x80, null);
    
    if(file_handle->Unused == (u64)-1){
        print("Unable to CreateFileA(\"%s\"), GetLastError() = %u\n", file_name, GetLastError());
        return 0;
    }
    
    return 1;
}


u8 *raw_disk_read_sectors(struct memory_arena *arena, u64 total_sectors_to_read, u64 sector){
    u64 TotalBytesToRead = total_sectors_to_read * globals.disk_info.sector_size_in_bytes;
    u8 *ret = push_data(arena, u8, TotalBytesToRead);
    
    u64 Start = sector * globals.disk_info.sector_size_in_bytes;
    
    u64 NewFilePointer = 0;
    int SetFilePointerExSuccess = SetFilePointerEx(globals.disk_info.file_handle, Start, &NewFilePointer, /*FILE_BEGIN*/0);
    
    if(!SetFilePointerExSuccess || NewFilePointer != Start){
        print("Error: SetFilePointerEx failed for '%.*s' and 0x%llx.\n", globals.disk_info.full_file_path.size, globals.disk_info.full_file_path.data, Start);
        _exit(1); // ?
    }
    
    assert(TotalBytesToRead < 0xffffffff); // ?
    
    u32 BytesRead = 0;
    int ReadFileSuccess = ReadFile(globals.disk_info.file_handle, ret, (u32)TotalBytesToRead, &BytesRead, NULL);
    if(!ReadFileSuccess || BytesRead != TotalBytesToRead){
        print("Error: ReadFile failed for '%.*s' and 0x%llx and size 0x%llx. GetLastError %u\n", globals.disk_info.full_file_path.size, globals.disk_info.full_file_path.data, Start, TotalBytesToRead, GetLastError());
        _exit(1); // ?
    }
    
    return ret;
}
