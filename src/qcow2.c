

static int parse_qcow2(char *file_name, HANDLE *file_handle){
    
    print("Loading .qcow2 '%s'\n", file_name);
    
    
    struct file file = memory_map_file(file_name, file_handle, /*copy_on_write*/0);
    if(!file.memory) return 0;
    
    // @WARNING: qcow2 is big endian!
    struct qcow2_header{
        u8 magic[4]; // QFI\xfb
        u32 version;
        u64 backing_file_name_offset;
        u32 backing_file_name_size;
        u32 cluster_bits;
        u64 disk_size;
        u32 crypt_method;
        u32 l1_size;
        u64 l1_table_offset;
        u64 refcount_table_offset;
        u32 refcount_table_clusters;
        u32 number_of_snapshots;
        u64 snapshot_offsets;
    } qcow2_header;
    
    if(file.size < sizeof(qcow2_header)){
        print("[" __FUNCTION__ "] Error: File '%s' is too small to be a qcow2 image.\n", file_name);
        return 0;
    }
    
    // Load the header:
    qcow2_header = *(struct qcow2_header *)file.memory;
    qcow2_header.version                  = byteswap_u32(qcow2_header.version);
    qcow2_header.backing_file_name_offset = byteswap_u64(qcow2_header.backing_file_name_offset);
    qcow2_header.backing_file_name_size   = byteswap_u32(qcow2_header.backing_file_name_size);
    qcow2_header.cluster_bits             = byteswap_u32(qcow2_header.cluster_bits);
    qcow2_header.disk_size                = byteswap_u64(qcow2_header.disk_size);
    qcow2_header.crypt_method             = byteswap_u32(qcow2_header.crypt_method);
    qcow2_header.l1_size                  = byteswap_u32(qcow2_header.l1_size);
    qcow2_header.l1_table_offset          = byteswap_u64(qcow2_header.l1_table_offset);
    qcow2_header.refcount_table_offset    = byteswap_u64(qcow2_header.refcount_table_offset);
    qcow2_header.refcount_table_clusters  = byteswap_u32(qcow2_header.refcount_table_clusters);
    qcow2_header.number_of_snapshots      = byteswap_u32(qcow2_header.number_of_snapshots);
    qcow2_header.snapshot_offsets         = byteswap_u64(qcow2_header.snapshot_offsets);
    
    // Validate the header:
    if(memcmp(qcow2_header.magic, "QFI\xfb", 4) != 0){
        print("[" __FUNCTION__ "] Error: File '%s' is not a qcow2 image. (wrong signature %.4s)\n", file_name, qcow2_header.magic);
        return 0;
    }
    
    if(qcow2_header.version != 2 && qcow2_header.version != 3){
        print("[" __FUNCTION__ "] Error: File '%s' has unhandled qcow version %d.\n", file_name, qcow2_header.version);
        return 0;
    }
    
    if(qcow2_header.crypt_method != 0){
        print("[" __FUNCTION__ "] Error: File '%s' is encrypted. Entcryption is not supported.\n", file_name);
        return 0;
    }
    
    if(qcow2_header.cluster_bits > 63){
        print("[" __FUNCTION__ "] Error: File '%s' has too large cluster bit size (exceeds 2^63).\n", file_name);
        return 0;
    }
    
    u64 L1_table_size = sizeof(u64) * qcow2_header.l1_size;
    
    if(qcow2_header.l1_table_offset >= file.size || qcow2_header.l1_table_offset + L1_table_size > file.size){
        print("[" __FUNCTION__ "] Error: File '%s' is corrupt.\n", file_name);
        return 0;
    }
    
    // @cleanup: Ensure that the L1 table is big enough to handle virtual size / cluster_size / L2 entries.
    
    u64 cluster_size = 1ull << qcow2_header.cluster_bits;
    
    globals.qcow2_info.cluster_size = cluster_size;
    globals.qcow2_info.L2_entries = cluster_size / sizeof(u64);
    globals.qcow2_info.L1_table = (u64 *)(file.memory + qcow2_header.l1_table_offset);
    
    globals.disk_info.mapped_address = file.memory;
    globals.disk_info.virtual_size = qcow2_header.disk_size;
    globals.disk_info.virtual_disk_kind = VIRTUAL_DISK_qcow2;
    globals.disk_info.sector_size_in_bytes = 0x200; // @cleanup: not sure, does qcow2 not specify this? On the other hand, why should it?
    
    return 1;
}

static u8 *qcow2_read_sectors(struct memory_arena *arena, u64 total_sectors_to_read, u64 sector){
    // @cleanup: bounds check?
    u64 offset = sector * 0x200;
    u64 length = total_sectors_to_read * 0x200;
    u8 *ret = push_data(arena, u8, length);
    u8 *at = ret;
    
    u64 cluster_size = globals.qcow2_info.cluster_size;
    u64 L2_entries = globals.qcow2_info.L2_entries;
    u64 *L1_table  = globals.qcow2_info.L1_table;
    u8 *mapped_base = globals.disk_info.mapped_address;
    
    while(length){
        u64 cluster_index  = offset / cluster_size;
        u64 offset_in_cluster = offset % cluster_size;
        u64 L2_index = cluster_index % L2_entries;
        u64 L1_index = cluster_index / L2_entries;
        
        u64 L2_table_offset = byteswap_u64(L1_table[L1_index]) & ~(0x8000000000000000); // @cleanup: bounds check.
        if(L2_table_offset == 0){
            // Address not mapped.
        }
        
        u64 *L2_table = (u64 *)(mapped_base + L2_table_offset);
        u64 cluster_offset = byteswap_u64(L2_table[L2_index]) & ~0xc000000000000000; // @cleanup: bounds check.
        
        u8 *source = mapped_base + cluster_offset + offset_in_cluster;  // @cleanup: bounds check.
        
        u64 length_to_copy = (cluster_size - offset_in_cluster < length) ? cluster_size - offset_in_cluster : length;
        
        memcpy(at, source, length_to_copy);
        
        offset += length_to_copy;
        length -= length_to_copy;
        at += length_to_copy;
    }
    
    return ret;
}

