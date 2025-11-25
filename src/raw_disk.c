
#if _WIN32
#define RAW_DISK_STRING "\\\\.\\PhysicalDrive"
#else
#define RAW_DISK_STRING "/dev/sd"
#endif

int parse_raw_disk(char *file_name, HANDLE *file_handle){
    globals.disk_info.virtual_disk_kind = VIRTUAL_DISK_raw;
    globals.disk_info.mapped_address = (void *)1; // Kinda weird, but this needs to be set.
    
#if _WIN32
    *file_handle = CreateFileA(file_name, /*GENERIC_READ*/0x80000000L, /*FILE_SHARE_READ | FILE_SHARE_WRITE*/3, null, /*OPEN_EXISTING*/3, /*FILE_ATTRIBUTE_NORMAL*/0x80, null);
    if(file_handle->Unused == (u64)-1){
        print("Unable to CreateFileA(\"%s\"), GetLastError() = %u\n", file_name, GetLastError());
        return 0;
    }
    
    // @incomplete: This currently thinks we are using \\.\PhysicalDrive0 and not img.raw.
    struct{
        u64 Cylinders;
        u32 MediaType;
        u32 TracksPerCylinder;
        u32 SectorsPerTrack;
        u32 BytesPerSector;
        u64 DiskSize;
        u8 Data[0x200];
    } DiskGeometryEx;
    
    int DeviceIoControlSuccess = DeviceIoControl(*file_handle, /*IOCTL_DISK_GET_DRIVE_GEOMETRY_EX*/0x700a0, null, 0, &DiskGeometryEx, sizeof(DiskGeometryEx), null, null);
    if(!DeviceIoControlSuccess){
        print("Unable to IOCTL_DISK_GET_DRIVE_GEOMETRY_EX for disk %s, GetLastError() = %u\n", file_name, GetLastError());
        return 0;
    }
    
    globals.disk_info.sector_size_in_bytes = DiskGeometryEx.BytesPerSector;
    globals.disk_info.virtual_size = DiskGeometryEx.DiskSize;
    
#else
    int file_descriptor = open(file_name, O_RDONLY);
    if(file_descriptor == -1){
        perror("open");
        return 0;
    }
    file_handle->Unused = file_descriptor;
    
    // 
    // Determine the size of the file.
    // 
    struct stat stat_buffer;
    if(fstat(file_descriptor, &stat_buffer) == -1){
        perror("fstat");
        close(file_descriptor);
        return 0;
    }
    
    globals.disk_info.virtual_size = stat_buffer.st_size;
    globals.disk_info.sector_size_in_bytes = 512;
#endif
    
    return 1;
}


u8 *raw_disk_read_sectors(struct memory_arena *arena, u64 total_sectors_to_read, u64 sector){
    u64 TotalBytesToRead = total_sectors_to_read * globals.disk_info.sector_size_in_bytes;
    u8 *ret = push_data(arena, u8, TotalBytesToRead);
    
    u64 Start = sector * globals.disk_info.sector_size_in_bytes;
    
#if _WIN32
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
#else
    if(lseek(globals.disk_info.file_handle.Unused, Start, SEEK_SET) != Start){
        perror("lseek");
        _exit(1); // ?
    }
    
    ssize_t bytes_read = read(globals.disk_info.file_handle.Unused, ret, TotalBytesToRead);
    if(bytes_read != TotalBytesToRead){
        perror("read");
        _exit(1); // ?
    }
#endif
    
    return ret;
}
