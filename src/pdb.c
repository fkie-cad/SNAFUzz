
// 
// A parser implementation of the PDB (Program Database) symbol file format.
//
// Usage example:
//     struct file pdb_file = load_file("path\\to\\my.pdb");
//     struct pdb_context *pdb_context = load_pdb(pdb_file);
//     
//     if(!pdb_context){
//         // Handle error....
//     }
//     
//     free(pdb_file.data); // Can free the .pdb, it was copied.
//     
//     // Given a symbol name we can search for the relative virtual address.
//     u64 rva = pdb_get_rva_for_symbol(pdb_context, string("main"));
//     
//     // Given a relative virtual address, we can search for the symbol name.
//     // The relative virtual address needs to be an exact match.
//     struct string main = pdb_get_symbol_name(pdb_context, rva);
// 
//     // We can do symbolized dump to stdout.
//     // If you pass 'have_address = 2', it will use 'guest_read' (and context) to dump memory contents.
//     // Otherwise, it will just print the type.
//     pdb_dump_type(context, pdb_context, string("type_name"), string("optional.member"), 0x13371337, /*have_address*/1);
//
//     // We can also figure out the offset of a member in a structure.
//     u64 member_offset = pdb_get_member_offset(pdb_context, , string("type_name"), string("optional.member"));
//
// Importantly, this parser should never hard error. If something does not parse correctly so be it.
// Errors usually print some cryptic string and then return some dummy value.
// 
// We use this PDB parser for three things:
// 
//    1) The debugger (and also symbolized stack traces and so on).
//    2) To have ntoskrnl-version independent snapshot/DMP loading. Things like the '_KPRCB' change with the kernel version.
//    3) We use the .pdata and .xdata section from the .pdb. Crash uniqueness uses a stack trace hash.
//
// This PDB parser copies/linearizes all the streams inside the PDB, then finds and iterates the TPI and symbol record stream,
// to build one 'pdb_hash_table' for types, one 'pdb_hash_table' for symbols, one 'pdb_hash_table' for constants,
// one array for 'type index' to 'type record' and one array for 'rva' to 'symbol record' (see also 'struct pdb_context').
// 
// If you care about the internals of PDBs, maybe check out my PDB-Documentation repository:
//     https://github.com/PascalBeyer/PDB-Documentation
// 
//                                                                          - Pascal Beyer 13.02.2023
//                                                                                         16.02.2024

struct pdb_stream{
    u8 *base;
    u64 size;
    u64 current_offset;
};

void *pdb_read_type_(struct pdb_stream *stream, void *buffer, u64 size){
    assert(stream->current_offset + size <= stream->size);
    memcpy(buffer, stream->base + stream->current_offset, size);
    stream->current_offset += size;
    return buffer;
}
#define pdb_read_type(stream, type) (*(type *)pdb_read_type_((stream), &(type){0}, sizeof(type)))


void *pdb_read_type__failable_(struct pdb_stream *stream, void *buffer, u64 size, int *error){
    if(stream->current_offset + size > stream->size){
        stream->current_offset = stream->size;
        *error = 1;
        return buffer;
    }
    
    memcpy(buffer, stream->base + stream->current_offset, size);
    stream->current_offset += size;
    return buffer;
}
#define pdb_read_type__failable(stream, type, error) (*(type *)pdb_read_type__failable_((stream), &(type){0}, sizeof(type), error))

struct pdb_stream pdb_substream(struct pdb_stream *stream, u64 size){
    assert(stream->current_offset + size <= stream->size);
    
    struct pdb_stream substream = {
        .base = stream->base + stream->current_offset,
        .size = size,
        .current_offset = 0,
    };
    
    stream->current_offset += size;
    
    return substream;
}

struct codeview_record_header{
    u16 length;
    u16 kind;
};

struct pdb_hash_table_entry{
    struct string string;
    struct codeview_record_header *record;
    u64    rva_value_or_type_index;
};

struct pdb_hash_table{
    struct pdb_hash_table_entry *entries;
    u64 count;
    u64 capacity;
};

struct pdb_sorted_array_entry{
    u32 rva;
    u32 kind;
    struct string name;
    struct codeview_record_header *record;
};

struct pdb_sorted_array{
    struct pdb_sorted_array_entry *entries;
    u64 count;
    u64 capacity;
};

void pdb_sorted_array_add(struct pdb_sorted_array *array, u32 rva, u32 kind, struct codeview_record_header *record, struct string name){
    
    if(array->count == array->capacity){
        array->capacity = !array->capacity ? 0x10 : 2 * array->capacity;
        
        struct pdb_sorted_array_entry *new_entries = malloc(array->capacity * sizeof(*new_entries));
        memcpy(new_entries, array->entries, array->count * sizeof(*array->entries));
        
        free(array->entries);
        array->entries = new_entries;
    }
    
    struct pdb_sorted_array_entry *new_entry = &array->entries[array->count++];
    new_entry->rva    = rva;
    new_entry->kind   = kind;
    new_entry->record = record;
    new_entry->name   = name;
}

int compare_pdb_sorted_array_entries(const void *a, const void *b){
    const struct pdb_sorted_array_entry *entry_a = a;
    const struct pdb_sorted_array_entry *entry_b = b;
    
    if(entry_a->rva != entry_b->rva) return entry_a->rva - entry_b->rva;
    
    if(entry_a->name.size != entry_b->name.size) return (int)(entry_a->name.size - entry_b->name.size);
    
    return strncmp(entry_a->name.data, entry_b->name.data, entry_a->name.size);
}

void pdb_sorted_array_sort(struct pdb_sorted_array *array){
    qsort(array->entries, array->count, sizeof(*array->entries), compare_pdb_sorted_array_entries);
}

struct pdb_sorted_array_entry *pdb_sorted_array_get(struct pdb_sorted_array *array, u32 rva){
    
    if(!array->count) return null;
    if(rva < array->entries[0].rva) return null;
    
    s64 min = 0;
    s64 max = array->count - 1;
    
    while(max - min >= 0){
        s64 at = (max + min) / 2;
        u32 entry_rva = array->entries[at].rva;
        
        if(entry_rva == rva){
            return &array->entries[at];
        }
        
        if(entry_rva < rva){
            min = at + 1;
        }else{
            max = at - 1; 
        }
    }
    
    // 
    // When we get here, we have 
    //     'max - min < 0' <=> 'max < min'
    // Because of how the loop works, in the end:
    //     'array->entries[max]' is the entry right before 'rva'
    //     'array->entries[min]' is the entry right after 'rva'
    // Because we checked at the start, that 'rva >= array->entries[0].rva',
    // we can safely return 'array->entries[max]'.
    // 
    
    return &array->entries[max];
}

struct pdb_context{
    u8 *pdb_base;
    
    u32 page_size;
    u32 amount_of_pages;
    
    struct pdb_stream directory_stream;
    struct pdb_stream *streams;
    
    struct pdb_hash_table type_table;
    struct pdb_hash_table publics_table;
    struct pdb_hash_table symbol_table;
    struct pdb_hash_table constant_table;
    
    struct pdb_sorted_array publics_array;
    struct pdb_sorted_array symbols_array;
    
    u64 amount_of_sections;
    struct pdb_image_section_header *section_headers;
    
    u32 minimal_type_index;
    u32 amount_of_type_indices;
    u32 *type_index_to_tpi_offset_map;
    
    s16 pdata_dump_stream_index;
    s16 xdata_dump_stream_index;
    int have_unwind_information;
};

struct pdb_image_section_header{
    u8  name[8];
    u32 virtual_size;
    u32 virtual_address;
    u32 size_of_raw_data;
    u32 pointer_to_raw_data;
    u32 pointer_to_relocations;
    u32 pointer_to_linenumbers;
    u16 number_of_relocations;
    u16 number_of_linenumbers;
    u32 characteristics;
};

struct pdb_section_contribution{
    s16 section_id;
    u16 padding1;
    s32 offset;
    s32 size;
    u32 characteristics;
    s16 module_index;
    u16 padding2;
    u32 data_crc;
    u32 reloc_crc;
};

struct pdb_module_information{
    u32 next_module;
    struct pdb_section_contribution first_section_contribution;
    u16 flags;
    u16 module_symbol_stream;
    u32 byte_size_of_symbol_information;
    u32 byte_size_of_c11_line_information;
    u32 byte_size_of_c13_line_information;
    u16 amount_of_source_files;
    u16 padding;
    u32 ignored;
    u32 offset_in_module_name;
    u32 offset_in_obj_file_name;
    char module_and_object_file_names[1];
};

u64 pdb_read_numeric_leaf_as_u64(struct pdb_stream *stream, int *error){
    
    if(stream->current_offset + sizeof(u16) > stream->size){
        *error = 1;
        return 0;
    }
    
    u16 numeric_leaf = pdb_read_type(stream, u16);
    
    //
    // If the top bit is not set it is a _simple_ numeric leaf
    //
    if(!(numeric_leaf & 0x8000)) return numeric_leaf;
    
    //
    // Otherwise, figure out the type.
    //
    switch(numeric_leaf){
        case /*LF_CHAR*/0x8000:{
            if(stream->current_offset + sizeof(char) > stream->size){
                *error = 1;
                return 0;
            }
            return pdb_read_type(stream, char);
        }break;
        
        case /*LF_SHORT*/0x8001:{
            if(stream->current_offset + sizeof(short) > stream->size){
                *error = 1;
                return 0;
            }
            return pdb_read_type(stream, short);
        }break;
        
        case /*LF_USHORT*/0x8002:{
            if(stream->current_offset + sizeof(unsigned short) > stream->size){
                *error = 1;
                return 0;
            }
            return pdb_read_type(stream, unsigned short);
        }break;
        
        case /*LF_LONG*/0x8003:{
            if(stream->current_offset + sizeof(s32) > stream->size){
                *error = 1;
                return 0;
            }
            return pdb_read_type(stream, s32);
        }break;
        
        case /*LF_LONG*/0x8004:{
            if(stream->current_offset + sizeof(u32) > stream->size){
                *error = 1;
                return 0;
            }
            return pdb_read_type(stream, u32);
        }break;
        
        case /*LF_QUADWORD*/0x8009:{
            if(stream->current_offset + sizeof(s64) > stream->size){
                *error = 1;
                return 0;
            }
            return pdb_read_type(stream, s64);
        }break;
        
        case /*LF_UQUADWORD*/0x800a:{
            if(stream->current_offset + sizeof(u64) > stream->size){
                *error = 1;
                return 0;
            }
            return pdb_read_type(stream, u64);
        }break;
        
        default:{
            // We don't handle any other numeric leaf.
            *error = 1;
            return 0;
        }break;
    }
}

struct string pdb_read_zero_terminated_string(struct pdb_stream *stream){
    struct string ret = {0};
    
    u64 size_remaining = (stream->size - stream->current_offset);
    char *name = (char *)(stream->base + stream->current_offset);
    size_t name_length = strnlen(name, size_remaining);
    
    if(name_length == size_remaining) return ret;
    
    ret.data = name;
    ret.size = name_length;
    
    stream->current_offset += name_length + 1;
    
    return ret;
}


// @note: Return (u32)-1 on error.
u32 pdb_section_offset_to_rva(struct pdb_context *context, u16 section_id, u32 offset_in_section){
    
    u32 section_index = section_id - 1;
    if(section_index >= context->amount_of_sections) return (u32)-1;
    
    struct pdb_image_section_header *section_header = &context->section_headers[section_index];
    
    if(offset_in_section > section_header->virtual_size) return (u32)-1;
    
    return section_header->virtual_address + offset_in_section;
}

struct pdb_hash_table pdb_hash_table_initialize(void){
    struct pdb_hash_table table = {
        .entries  = malloc(0x100 * sizeof(*table.entries)),
        .capacity = 0x100,
    };
    return table;
}

void pdb_hash_table_insert(struct pdb_hash_table *table, struct codeview_record_header *record, struct string string, u64 rva_value_or_type_index){
    
    if(2 * (table->count + 1) > table->capacity){
        //
        // Grow the hash table.
        //
        struct pdb_hash_table old_table = *table;
        
        u64 new_capacity = table->capacity * 2;
        if(!new_capacity) new_capacity = 0x1000;
        
        struct pdb_hash_table_entry *new_entries = malloc(new_capacity * sizeof(*table->entries));
        
        table->capacity = new_capacity;
        table->entries  = new_entries;
        table->count    = 0;
        
        for(u64 index = 0; index < old_table.capacity; index++){
            struct pdb_hash_table_entry entry = old_table.entries[index];
            
            if(entry.record){
                pdb_hash_table_insert(table, entry.record, entry.string, entry.rva_value_or_type_index);
            }
        }
        
        free(old_table.entries);
    }
    
    u32 hash = string_hash(string);
    
    for(u32 hash_index = 0; hash_index < table->capacity; hash_index++){
        u32 index = (hash + hash_index) % table->capacity;
        
        struct pdb_hash_table_entry *entry = &table->entries[index];
        if(entry->record){
            //
            // @note: Prefer _later_ entries.
            //
            
            if(!string_match(entry->string, string)){    
                continue;
            }
        }
        
        entry->record = record;
        entry->string = string;
        entry->rva_value_or_type_index = rva_value_or_type_index;
        table->count++;
        
        return;
    }
    
    return;
}

struct pdb_hash_table_entry *pdb_hash_table_get(struct pdb_hash_table *table, struct string string){
    if(!table->capacity) return null;
    
    u32 hash = string_hash(string);
    
    for(u32 hash_index = 0; hash_index < table->capacity; hash_index++){
        u32 index = (hash + hash_index) % table->capacity;
        
        struct pdb_hash_table_entry *entry = &table->entries[index];
        if(!entry->record) return null;
        if(!string_match(string, entry->string)) continue;
        
        return entry;
    }
    
    return null;
}

struct pdb_context *load_pdb(struct file pdb_file){
    if(!pdb_file.size){
        // This happens for stubs we emitted.
        // If we cannot load the file once, even though we tried, there is a zero-sized file in there.
        return null;
    }
    
    u8 *pdb_base = pdb_file.memory;
    
    struct{
        u8 signature[32];
        u32 page_size;
        u32 free_page_map;
        u32 amount_of_pages;
        u32 directory_stream_size;
        u32 reserved;
        u32 page_number_of_directory_stream_page_number_list;
    } *pdb_header = (void *)pdb_base;
    
    //
    // Make sure the file is a pdb.
    //
    if(pdb_file.size < sizeof(*pdb_header)) return null;
    if(memcmp(pdb_header->signature, "Microsoft C/C++ MSF 7.00\r\n\032DS\0\0\0", 32) != 0) return null;
    
    //
    // Validate all members that we care about.
    //
    
    u32 page_size       = pdb_header->page_size;
    u32 amount_of_pages = pdb_header->amount_of_pages;
    
    if(!page_size || (page_size & (page_size - 1))) return null;
    if(amount_of_pages * page_size > pdb_file.size) return null; // Allow bigger I guess?
    
    //
    // Check the directory stream page number list and make sure it fits into one page.
    //
    u32 amount_of_directory_stream_pages = ((pdb_header->directory_stream_size + page_size - 1) / page_size);
    
    if(pdb_header->page_number_of_directory_stream_page_number_list >= amount_of_pages) return null;
    if(amount_of_directory_stream_pages * sizeof(u32) > page_size) return null;
    
    
    struct pdb_stream directory_stream = {0};
    {
        u8 *directory_stream_data = malloc(amount_of_directory_stream_pages * page_size);
        u64 directory_stream_size = pdb_header->directory_stream_size;
        
        //
        // Make sure the directory stream pages are valid.
        //
        u32 *directory_stream_pages = (u32 *)(pdb_base + pdb_header->page_number_of_directory_stream_page_number_list * page_size);
        
        for(u32 directory_stream_page_index = 0; directory_stream_page_index < amount_of_directory_stream_pages; directory_stream_page_index++){
            if(directory_stream_pages[directory_stream_page_index] >= amount_of_pages) goto error;
            
            u8 *dest   = directory_stream_data + page_size * directory_stream_page_index;
            u8 *source = pdb_base              + page_size * directory_stream_pages[directory_stream_page_index];
            
            memcpy(dest, source, page_size);
        }
        
        directory_stream = (struct pdb_stream){
            .base = directory_stream_data,
            .size = directory_stream_size,
        };
    }
    
    //
    // Set up a context, which allows us call stream reading functions.
    //
    struct pdb_context *pdb_context = malloc(sizeof(*pdb_context));
    pdb_context->pdb_base         = pdb_base;
    pdb_context->page_size        = page_size;
    pdb_context->amount_of_pages  = amount_of_pages;
    pdb_context->directory_stream = directory_stream;
    
    //
    // directory_steam:
    //    u32 amount_of_streams;
    //    u32 stream_sizes[amount_of_streams];
    //    u32 stream_one_pages[];
    //    u32 stream_two_pages[];
    //    ...
    //
    
    if(directory_stream.size < 4) goto error;
    
    u32 amount_of_streams = pdb_read_type(&directory_stream, u32);
    
    // @note: Allow missing ipi. Other fixed streams need to be present.
    if(amount_of_streams < 4) goto error;
    
    if(directory_stream.current_offset + amount_of_streams * sizeof(u32) > directory_stream.size) goto error;
    
    //
    // Linearize all the streams for convenience, after this point we could free the PDB.
    //
    
    struct pdb_stream stream_sizes = pdb_substream(&directory_stream, amount_of_streams * sizeof(u32));
    struct pdb_stream *streams = malloc(amount_of_streams * sizeof(struct pdb_stream));
    
    pdb_context->streams = streams;
    
    for(u32 stream_index = 0; stream_index < amount_of_streams; stream_index++){
        u32 stream_size = pdb_read_type(&stream_sizes, u32);
        
        // Skip the stream if it was _deleted_.
        if(stream_size == 0xffffffff) continue;
        
        u32 amount_of_pages_in_stream = (stream_size + page_size - 1) / page_size;
        
        streams[stream_index] = (struct pdb_stream){
            .base = malloc(page_size * amount_of_pages_in_stream),
            .size = stream_size,
        };
        
        if(directory_stream.current_offset + amount_of_pages_in_stream * sizeof(u32) > directory_stream.size) goto error;
        
        for(u32 page_index = 0; page_index < amount_of_pages_in_stream; page_index++){
            u32 stream_page = pdb_read_type(&directory_stream, u32);
            
            if(stream_page >= amount_of_pages) goto error;
            
            u8 *dest   = streams[stream_index].base + page_index * page_size;
            u8 *source = pdb_base + stream_page * page_size;
            
            memcpy(dest, source, page_size);
        }
    }
    
    //
    // The first 5 streams are fixed:
    //
    // 0 - Old directory stream
    //        We ignore this stream.
    // 1 - PDB Stream
    //        This stream contains information to match the .pdb against the .exe.
    //        It also contains information about the .pdb including information where
    //        we can locate the global '/names' string table, which is interesting for
    //        line information.
    // 2 - TPI Stream
    //        This stream contains all the type information.
    // 3 - DBI Stream
    //        This stream contains information about the debug information contained in the .pdb.
    //        This includes stream indices for the 'symbol record stream' as well as the
    //        'module symbol stream' for each module (compilation unit).
    // 4 - IPI Stream
    //        This stream contains id information. Some of which seems tangentially interesting
    //        like the sections. But I am not sure we care about it.
    //
    
    // @note: For now we ignore the PDB Stream, we don't care about line information
    //        and for now we don't match against a .exe.
    
    pdb_context->type_table    = pdb_hash_table_initialize();
    pdb_context->symbol_table  = pdb_hash_table_initialize();
    pdb_context->publics_table = pdb_hash_table_initialize();
    
    {
        //
        // Parse the TPI Stream into a map of type indices to entries in the TPI.
        //
        
        struct pdb_stream tpi_stream = streams[2];
        
        struct tpi_stream_header{
            u32 version;            // always 20040203
            u32 header_size;        // sizeof(tpi_header_size)
            u32 minimal_type_index; // always 0x1000
            u32 maximal_type_index; // -> maximal_type_index - minimal_type_index = amount
            u32 amount_of_bytes_of_type_record_data_following_the_header;
            
            u16 hash_stream_index;
            s16 hash_aux_stream_index; // unknown, can be -1
            
            u32 hash_key_size;         // usually 4 bytes
            u32 number_of_hash_buckets;
            
            // The length and offset of a buffer of hash values within the TPI hash stream (tpi->hash_stream_index)
            // This buffer should be of size (maximal_type_index - minimal_type_index) * hash_key_size
            s32 hash_value_buffer_offset;
            u32 hash_value_buffer_length; // = (maximal_type_index - minimal_type_index) * hash_key_size
            
            // The length and offset of a buffer of (type_index, offset of the type in the type record data)
            // again in the TPI hash stream (pairs of u32's)
            s32 index_offset_buffer_offset;
            u32 index_offset_buffer_length;
            
            // A serialized hash table in the TPI hash stream.
            s32 incremental_linking_hash_table_offset;
            u32 incremental_linking_hash_table_length;
        } tpi;
        
        if(tpi_stream.size < sizeof(tpi)) goto error;
        
        tpi = pdb_read_type(&tpi_stream, struct tpi_stream_header);
        
        //
        // @note: We only care about the type information and manually build a map,
        //        instead of using the 'index_offset_buffer' or the 'hash_stream'.
        //
        if(tpi.minimal_type_index > tpi.maximal_type_index) goto error;
        
        u32 amount_of_type_indices = tpi.maximal_type_index - tpi.minimal_type_index;
        
        // @cleanup: Maybe make this more lenient, but technically the first 0x1000 type indices are reserved.
        //           some of which are basic types an whatnot.
        if(tpi.minimal_type_index < 0x1000) goto error;
        
        u32 *type_index_to_tpi_offset_map = malloc(amount_of_type_indices * sizeof(u32));
        
        u32 type_index_at = tpi.minimal_type_index;
        
        // Make sure at least the header of the next type index fits.
        while(tpi_stream.current_offset + 2 * sizeof(u16) <= tpi_stream.size){
            
            //
            // Make sure we don't overrun the map, but allow there to be more symbols,
            // to allow for somewhat invalid pdbs.
            //
            if(type_index_at == tpi.maximal_type_index) break;
            
            u32 type_offset = (u32)tpi_stream.current_offset;
            
            u32 type_index = type_index_at++;
            
            //
            // Register the type record in the 'type_index_to_tpi_offset_map'.
            //
            type_index_to_tpi_offset_map[type_index - tpi.minimal_type_index] = type_offset;
            
            //
            // Read the record length and skip it.
            //
            u16 length = pdb_read_type(&tpi_stream, u16);
            
            struct pdb_stream type_stream = pdb_substream(&tpi_stream, length);
            if(length < 2) continue;
            
            //
            // Parse the type, if it is named add it to the hash table.
            //
            u16 kind = pdb_read_type(&type_stream, u16);
            
            int error = 0;
            switch(kind){
                
                //
                // @note: Only check the types we support and which are named.
                //
                case 0x1506:  // LF_UNION
                case 0x1609:  // LF_STRUCTURE_EX
                case 0x1505:{ // LF_STRUCTURE
                    
                    // LF_UNION
                    //     u16 number_of_elements;
                    //     u16 properties;
                    //     u32 field_list_type_index;
                    
                    // LF_STRUCTURE_EX
                    //     u32 properties;
                    //     u32 field_list_type_index;
                    //     u32 derived;
                    //     u32 vshape;
                    
                    // LF_STRUCTURE
                    //     u16 number_of_elements;
                    //     u16 properties;
                    //     u32 field_list_type_index;
                    //     u32 derived;
                    //     u32 vshape;
                    
                    //
                    // All of them are followed by a numeric leaf for the size of the structure/union and its name.
                    //
                    
                    u32 properties_and_number_of_elements = pdb_read_type__failable(&type_stream, u32, &error);
                    u32 field_list_type_index             = pdb_read_type__failable(&type_stream, u32, &error);
                    
                    u32 properties = (kind == /*LF_STRUCTURE_EX*/0x1609) ? properties_and_number_of_elements : (properties_and_number_of_elements >> 16);
                    
                    type_stream.current_offset += (kind == /*LF_UNION*/0x1506) ? 0 : 8;
                    
                    /*u64 size = */pdb_read_numeric_leaf_as_u64(&type_stream, &error);
                    
                    if((properties & /* forward ref */(1 << 7)) || error) break;
                    
                    struct string name = pdb_read_zero_terminated_string(&type_stream);
                    if(!name.data) break;
                    
                    //
                    // Register the type in the hash table.
                    //
                    pdb_hash_table_insert(&pdb_context->type_table, (struct codeview_record_header *)(tpi_stream.base + type_offset), name, field_list_type_index);
                }break;
            }
        }
        
        if(type_index_at < amount_of_type_indices){
            //
            // If there were less type indices then specified, just take the ones we know about.
            //
            amount_of_type_indices = type_index_at;
        }
        
        pdb_context->minimal_type_index           = tpi.minimal_type_index;
        pdb_context->amount_of_type_indices       = amount_of_type_indices;
        pdb_context->type_index_to_tpi_offset_map = type_index_to_tpi_offset_map;
    }
    
    {
        //
        // Parse the DBI Stream.
        //
        // We care about the 'symbol record stream', which contains "public" symbols like:
        //     'S_PUB32', 'S_(L|G)PROCREF', 'S_DATAREF', 'S_(L|G)DATA32', S_UDT
        //
        // The 'module symbol streams' which contain "private" symbols like:
        //     'S_(G|L)PROC32', 'DEBUG_S_LINES' and 'S_(L|G)PROCREF', 'S_UDT', 'S_(L|G)DATA32' which created conflicts.
        // We only consider those which are referenced by the 'symbol record stream'.
        //
        // And the section header dump stream, which contains a copy of the section table
        // contained in the executable. This helps us map from [section:offset] addressing
        // to rva addressing.
        //
        
        struct pdb_stream dbi_stream = streams[3];
        
        struct dbi_stream_header{
            u32 version_signature;                         // always -1
            u32 version;                                   // always 19990903
            u32 amount_of_times_the_pdb_has_been_written;  // same as in pdb_stream
            u16 index_of_the_global_symbol_stream;
            u16 toolchain_version;
            u16 index_of_the_public_symbol_stream;
            u16 version_number_of_mspdb;
            u16 index_of_the_symbol_record_stream;
            u16 PdbDllRbld;
            u32 module_info_substream_byte_size;           // substream 0
            u32 section_contribution_substream_byte_size;  // substream 1
            u32 section_map_substream_byte_size;           // substream 2
            u32 source_info_substream_byte_size;           // substream 3
            u32 type_server_map_substream_byte_size;       // substream 4
            u32 offset_of_the_MFC_type_server_in_the_type_server_map_substream;
            u32 optional_debug_header_substream_byte_size; // substream 6
            u32 edit_and_continue_substream_byte_size;     // substream 5
            
            u16 flags;
            u16 machine;
            u32 padding;
        } dbi;
        
        if(dbi_stream.size < sizeof(dbi)) goto error;
        
        dbi = pdb_read_type(&dbi_stream, struct dbi_stream_header);
        
        u64 size = sizeof(dbi) +
                (u64)dbi.module_info_substream_byte_size          +
                (u64)dbi.section_contribution_substream_byte_size +
                (u64)dbi.section_map_substream_byte_size          +
                (u64)dbi.source_info_substream_byte_size          +
                (u64)dbi.type_server_map_substream_byte_size      +
                (u64)dbi.edit_and_continue_substream_byte_size    +
                (u64)dbi.optional_debug_header_substream_byte_size;
        
        
        u64 amount_of_sections = 0;
        struct pdb_image_section_header *section_headers = null;
        
        if(size <= dbi_stream.size){
            //
            // Parse out the _optional debug header substream_ to figure out the module indices.
            //
            u64 offset = size - dbi.optional_debug_header_substream_byte_size;
            
            struct pdb_stream debug_headers = {
                .base = dbi_stream.base + offset,
                .size = dbi.optional_debug_header_substream_byte_size,
            };
            
            // [0] s16 FPO       data
            // [1] s16 Exception data
            // [2] s16 Fixup     data
            // [3] s16 Omap
            // [4] s16 Omap
            // [5] s16 Section Header Dump Stream
            // [6] s16 clr_token_to_clr_record_id_map_stream_index
            // [7] s16 xdata_dump_stream_index
            // [8] s16 pdata_dump_stream_index
            
            if(dbi.optional_debug_header_substream_byte_size >= 6 * sizeof(s16)){
                s16 section_header_dump_stream = *(s16 *)(debug_headers.base + 5 * sizeof(s16));
                
                if(section_header_dump_stream != -1 && (u16)section_header_dump_stream < amount_of_streams){
                    struct pdb_stream section_header_stream = streams[section_header_dump_stream];
                    
                    section_headers    = (struct pdb_image_section_header *)section_header_stream.base;
                    amount_of_sections = section_header_stream.size / sizeof(struct pdb_image_section_header);
                }
            }
            
            if(dbi.optional_debug_header_substream_byte_size >= 9 * sizeof(s16)){
                s16 pdata_dump_stream = *(s16 *)(debug_headers.base + 8 * sizeof(s16));
                s16 xdata_dump_stream = *(s16 *)(debug_headers.base + 7 * sizeof(s16));
                
                int pdata_is_valid = pdata_dump_stream != -1 && (u16)pdata_dump_stream < amount_of_streams;
                int xdata_is_valid = xdata_dump_stream != -1 && (u16)xdata_dump_stream < amount_of_streams;
                
                if(pdata_is_valid && xdata_is_valid){
                    struct pdb_stream pdata = streams[pdata_dump_stream];
                    struct pdb_stream xdata = streams[xdata_dump_stream];
                    
                    // 
                    // Both the .pdata and the .xdata dump streams begin with a header, 
                    // telling us where the sections are located, followed by a copy of said sections.
                    // 
                    
                    if(xdata.size > 0x20 && pdata.size > 0x20){
                        pdb_context->have_unwind_information = 1;
                        
                        pdb_context->pdata_dump_stream_index = pdata_dump_stream;
                        pdb_context->xdata_dump_stream_index = xdata_dump_stream;
                    }
                }
            }
        }
        
        //
        // @cleanup: Maybe if we did not get a section header stream we should read it from the .exe
        //
        pdb_context->amount_of_sections = amount_of_sections;
        pdb_context->section_headers   = section_headers;
        
        u32 amount_of_modules = 0;
        struct pdb_module_information **module_informations = null;
        
        if(sizeof(dbi) + (u64)dbi.module_info_substream_byte_size <= dbi_stream.size){
            
            struct pdb_stream module_information_substream = pdb_substream(&dbi_stream, dbi.module_info_substream_byte_size);
            
            //
            // Parse the module information substream, this consists of variable sized 'pdb_module_information' structures.
            //
            
            char *module_information_end = (char *)(module_information_substream.base + module_information_substream.size);
            
            while(module_information_substream.current_offset + sizeof(struct pdb_module_information) < module_information_substream.size){
                struct pdb_module_information *module_information = (void *)(module_information_substream.base + module_information_substream.current_offset);
                
                char *module_name = module_information->module_and_object_file_names;
                size_t module_name_length = strnlen(module_name, module_information_end - module_name);
                
                // Catch 'strnlen' error: should be less then the buffer size given.
                if(module_name + module_name_length == module_information_end) break;
                
                char *object_name = module_name + module_name_length + 1;
                size_t object_name_length = strnlen(object_name, module_information_end - object_name);
                
                // Catch 'strnlen' error: should be less then the buffer size given.
                if(object_name + object_name_length == module_information_end) break;
                
                size_t module_information_size = (u8 *)(object_name + object_name_length + 1) - (u8 *)module_information;
                module_information_substream.current_offset += (module_information_size + 3) & ~3;
                
                amount_of_modules += 1;
            }
            
            module_informations = malloc(amount_of_modules * sizeof(*module_informations));
            
            //
            // We have validated that the first 'amount_of_modules' are just fine.
            // Use this to make a tighter loop!
            //
            struct pdb_module_information *module_information_at = (void *)module_information_substream.base;
            for(u32 module_index = 0; module_index < amount_of_modules; module_index++){
                module_informations[module_index] = module_information_at;
                
                size_t module_name_size = strlen(module_information_at->module_and_object_file_names);
                size_t object_name_size = strlen(module_information_at->module_and_object_file_names + module_name_size + 1);
                
                size_t aligned_sizes = ((module_name_size + 1) + (object_name_size + 1) + 3) & ~3;
                
                module_information_at = (void *)(module_information_at->module_and_object_file_names + aligned_sizes);
            }
        }
        
        if(dbi.index_of_the_symbol_record_stream < amount_of_streams){
            //
            // Parse the symbol record stream to get maps:
            //     relative virtual address -> symbol
            //     symbol name -> relative virtual address
            //
            
            struct pdb_stream symbol_record_stream = streams[dbi.index_of_the_symbol_record_stream];
            
            while(symbol_record_stream.current_offset + 2 * sizeof(u16) <= symbol_record_stream.size){
                
                u32 symbol_offset = (u32)symbol_record_stream.current_offset;
                
                struct codeview_record_header *symbol = (void *)(symbol_record_stream.base + symbol_offset);
                
                u16 length = pdb_read_type(&symbol_record_stream, u16);
                
                struct pdb_stream symbol_stream = pdb_substream(&symbol_record_stream, length);
                if(length < 2) continue;
                
                int error = 0;
                u16 kind = pdb_read_type(&symbol_stream, u16);
                
                switch(kind){
                    
                    case /*S_PUB32*/0x110e:{
                        /*u32 flags         = */pdb_read_type__failable(&symbol_stream, u32, &error);
                        u32 offset_in_section = pdb_read_type__failable(&symbol_stream, u32, &error);
                        u16 section_id        = pdb_read_type__failable(&symbol_stream, u16, &error);
                        
                        if(error) break;
                        
                        struct string name = pdb_read_zero_terminated_string(&symbol_stream);
                        if(!name.data) break;
                        
                        u32 rva = pdb_section_offset_to_rva(pdb_context, section_id, offset_in_section);
                        if(rva == (u32)-1) break;
                        
                        if(name.data[0] == '?'){
                            // 
                            // Basic C++ name syntax:
                            //     ?function@class@otherclass@@XYZ
                            // Strip everything after @@ and the ?, becoming:
                            //     function@class@otherclass
                            // Which is equivalent to:
                            //     otherclass::class::function
                            // 
                            
                            smm amount_of_delimiters = 0;
                            
                            for(smm index = 0; index < name.size-1; index++){
                                if(name.data[index] == '@' && name.data[index+1] == '@'){
                                    name.size = index;
                                    break;
                                }
                                
                                if(name.data[index] == '@') amount_of_delimiters += 1;
                            }
                            
                            if(!amount_of_delimiters){
                                // Strip the '?'.
                                name.data += 1;
                                name.size -= 1;
                            }
                        }
                        
                        pdb_hash_table_insert(&pdb_context->publics_table, symbol, name, rva);
                        pdb_sorted_array_add(&pdb_context->publics_array, rva, symbol->kind, symbol, name);
                    }break;
                    
                    case /*S_ANNOTATIONREF*/0x1128:{
                        // @note: ignore these
                    }break;
                    
                    case /*S_LPROCREF*/0x1127:
                    case /*S_PROCREF*/ 0x1125:{
                        /*u32 name_check_sum                 = */pdb_read_type__failable(&symbol_stream, u32, &error);
                        u32 offset_in_module_symbol_stream = pdb_read_type__failable(&symbol_stream, u32, &error);
                        u16 module_id                      = pdb_read_type__failable(&symbol_stream, u16, &error);
                        
                        if(error) break;
                        
                        struct string name = pdb_read_zero_terminated_string(&symbol_stream);
                        if(!name.data) break;
                        
                        //
                        // Get the GPROC32 or LPROC32, while validating all the information.
                        //
                        u32 module_index = module_id - 1;
                        if(module_index >= amount_of_modules) break;
                        
                        struct pdb_module_information *module = module_informations[module_index];
                        
                        if(module->module_symbol_stream >= amount_of_streams) break;
                        
                        struct pdb_stream module_symbol_stream = streams[module->module_symbol_stream];
                        
                        if((u64)offset_in_module_symbol_stream + 2 * sizeof(u16) > module_symbol_stream.size) break;
                        
                        symbol = (void *)(module_symbol_stream.base + offset_in_module_symbol_stream);
                        
                        module_symbol_stream.current_offset = offset_in_module_symbol_stream + 2 * sizeof(u16);
                        module_symbol_stream.size          -= offset_in_module_symbol_stream + 2 * sizeof(u16);
                        
                        if(symbol->kind != /*S_LPROC32*/0x110f && symbol->kind != /*S_GPROC32*/0x1110) break;
                        if(module_symbol_stream.size < symbol->length) break;
                        
                        struct codeview_proc32{
                            u32 pointer_to_parent;
                            u32 pointer_to_end;
                            u32 pointer_to_next_symbol;
                            u32 procedure_length;
                            u32 debug_start_offset;
                            u32 debug_end_offset;
                            u32 type_index;
                            u32 offset_in_section;
                            u16 section_id;
                            u8  procedure_flags;
                            char name[];
                        } *proc32 = (void *)(symbol + 1);
                        
                        if(symbol->length < sizeof(*proc32) + /*-1 because in struct +1 because 0-terminated*/name.size) break;
                        if(strncmp(proc32->name, name.data, name.size) != 0) break;
                        
                        u32 rva = pdb_section_offset_to_rva(pdb_context, proc32->section_id, proc32->offset_in_section);
                        if(rva == (u32)-1) break;
                        
                        pdb_hash_table_insert(&pdb_context->symbol_table, symbol, name, rva);
                        pdb_sorted_array_add(&pdb_context->symbols_array, rva, symbol->kind, symbol, name);
                    }break;
                    
                    case /*S_UDT*/0x1108:{
                        
                        // @cleanup: I think these are typedefs.
                        
#if 0
                        u32 type_index = pdb_read_type__failable(&symbol_stream, u32, &error);
                        
                        if(error) break;
                        
                        u64 size_remaining = symbol_stream.size - symbol_stream.current_offset;
                        char *name = (char *)(symbol_stream.base + symbol_stream.current_offset);
                        size_t name_length = strnlen(name, size_remaining);
                        
                        if(name_length == size_remaining) break;
                        
                        print("[S_UDT] %.*s\n", name_length, name);
#endif
                    }break;
                    
                    case /*S_CONSTANT*/0x1107:{
                        /*u32 type_index = */pdb_read_type__failable(&symbol_stream, u32, &error);
                        u64 value = pdb_read_numeric_leaf_as_u64(&symbol_stream, &error);
                        
                        if(error) break;
                        
                        struct string name = pdb_read_zero_terminated_string(&symbol_stream);
                        if(!name.data) break;
                        
                        pdb_hash_table_insert(&pdb_context->constant_table, symbol, name, value);
                    }break;
                    
                    case /*S_GDATA32*/0x110d:
                    case /*S_LDATA32*/0x110c:{
                        /*u32 type_index        = */pdb_read_type__failable(&symbol_stream, u32, &error);
                        u32 offset_in_section = pdb_read_type__failable(&symbol_stream, u32, &error);
                        u16 section_id        = pdb_read_type__failable(&symbol_stream, u16, &error);
                        
                        if(error) break;
                        
                        struct string name = pdb_read_zero_terminated_string(&symbol_stream);
                        if(!name.data) break;
                        
                        u32 rva = pdb_section_offset_to_rva(pdb_context, section_id, offset_in_section);
                        if(rva == (u32)-1) break;
                        
                        pdb_hash_table_insert(&pdb_context->symbol_table, symbol, name, rva);
                        
                        pdb_sorted_array_add(&pdb_context->symbols_array, rva, symbol->kind, symbol, name);
                    }break;
                    
#if 0
                    case /*S_LTHREAD32*/0x1112:
                    case /*S_GTHREAD32*/0x1113:{
                    }break;
#endif
                    
                    default:{
                        print("[PDB] Unhandled symbol kind 0x%x\n", kind);
                    }break;
                    
                }
            }
            
            pdb_sorted_array_sort(&pdb_context->publics_array);
            pdb_sorted_array_sort(&pdb_context->symbols_array);
        }
    }
    
    return pdb_context;
    
    error:;
    //
    // @cleanup: Deallocate stuff maybe needs some rearranging.
    //
    print("Error while parsing pdb.");
    return null;
}

struct string pdb_get_symbol_name(struct pdb_context *context, u32 rva, u32 *offset){
    struct string name = {0};
    *offset = 0;
    
    struct pdb_sorted_array_entry *symbol_entry = pdb_sorted_array_get(&context->symbols_array, rva);
    if(symbol_entry && symbol_entry->rva == rva) return symbol_entry->name;
    
    struct pdb_sorted_array_entry *publics_entry = pdb_sorted_array_get(&context->publics_array, rva);
    if(publics_entry && publics_entry->rva == rva) return publics_entry->name;
    
    if(symbol_entry && publics_entry){
        u32 symbol_offset = rva - symbol_entry->rva;
        u32 public_offset = rva - publics_entry->rva;
        
        if(symbol_offset < public_offset){
            *offset = symbol_offset;
            return symbol_entry->name;
        }else{
            *offset = public_offset;
            return publics_entry->name;
        }
    }
    
    if(symbol_entry){
        *offset = rva - symbol_entry->rva;
        return symbol_entry->name;
    }
    
    if(publics_entry){
        *offset = rva - publics_entry->rva;
        return publics_entry->name;
    }
    
    return name;
}

// @note: Returns (u64)-1 on failure.
u64 pdb_get_rva_for_symbol(struct pdb_context *context, struct string symbol_name){
    
    struct pdb_hash_table_entry *symbol_entry = pdb_hash_table_get(&context->symbol_table, symbol_name);
    if(symbol_entry) return symbol_entry->rva_value_or_type_index;
    
    struct pdb_hash_table_entry *publics_entry = pdb_hash_table_get(&context->publics_table, symbol_name);
    if(publics_entry) return publics_entry->rva_value_or_type_index;
    
    return (u64)-1;
}

u64 pdb_get_constant_for_symbol(struct pdb_context *context, struct string symbol_name, int *error){
    
    struct pdb_hash_table_entry *constant = pdb_hash_table_get(&context->constant_table, symbol_name);
    if(!constant){
        *error = 1;
        return 0;
    }
    
    return constant->rva_value_or_type_index;
}

struct codeview_record_header *pdb_get_record_for_type_index(struct pdb_context *context, u32 type_index){
    
    static struct codeview_record_header basic_type = {0};
    if(type_index < 0x1000) return &basic_type;
    
    u32 index_in_map = type_index - context->minimal_type_index;
    if(index_in_map >= context->amount_of_type_indices) return null;
    
    return (void *)(context->streams[2].base + context->type_index_to_tpi_offset_map[index_in_map]);
}


// returns the size of the type
static u64 pdb_sizeof_type(struct pdb_context *pdb_context, u32 type_index){
    
    if(type_index < 0x1000){
        
        //
        // Handle "basic" type indices.
        //
        
        switch(type_index){
            case    0: return 0;
            case  0x3: return 0;
            
            case 0x10: return 1;
            
            case 0x11: return 2;
            
            case 0x12: return 4;
            
            case 0x13: return 8;
            
            case 0x20: return 1;
            case 0x21: return 2;
            case 0x22: return 4;
            case 0x23: return 8;
            
            case 0x68: return 1;
            case 0x69: return 2;
            
            case 0x70: return 1;
            
            case 0x71: return 2;
            
            case 0x72: return 2;
            case 0x73: return 2;
            case 0x74: return 4;
            case 0x75: return 4;
            case 0x76: return 8;
            case 0x77: return 8;
            
            case 0x40: return 4;
            case 0x41: return 8;
            
            
            case 0x620: return 8;
            case 0x670: return 8;
            case 0x671: return 8;
            
            case 0x668: return 8;
            case 0x669: return 8;
            
            case 0x603: return 8;
            
            default: print("Unhandled type index 0x%x", type_index); return 0;
        }
        
        return 0;
    }
    
    struct codeview_record_header *record = pdb_get_record_for_type_index(pdb_context, type_index);
    if(!record){
        print("ERROR_INVALID_TYPE_INDEX\n");
        return 0;
    }
    
    if(record->kind == /*LF_POINTER*/0x1002) return 8;
    
    
    while(record->kind == /*LF_MODIFIER*/0x1001){
        
        type_index = *(u32 *)(record + 1);
        
        if(type_index < 0x1000) break;
        
        record = pdb_get_record_for_type_index(pdb_context, type_index);
        if(!record){
            print("ERROR_INVALID_TYPE_INDEX 0x%x\n", type_index);
            return 0;
        }
    }
    
    if(type_index < 0x1000) return pdb_sizeof_type(pdb_context, type_index);
    
    struct pdb_stream type_stream = {
        .base = (void *)(record + 1),
        .size = record->length - 2,
    };
    
    int error = 0;
    
    switch(record->kind){
        
        case /*LF_ARRAY*/0x1503:{
            
            pdb_read_type__failable(&type_stream, u32, &error);
            pdb_read_type__failable(&type_stream, u32, &error);
            
            return pdb_read_numeric_leaf_as_u64(&type_stream, &error);
        }break;
        
        //
        // @copy_and_paste from 'load_pdb'.
        //
        case 0x1506:  // LF_UNION
        case 0x1609:  // LF_STRUCTURE_EX
        case 0x1505:{ // LF_STRUCTURE
            
            // LF_UNION
            //     u16 number_of_elements;
            //     u16 properties;
            //     u32 field_list_type_index;
            
            // LF_STRUCTURE_EX
            //     u32 properties;
            //     u32 field_list_type_index;
            //     u32 derived;
            //     u32 vshape;
            
            // LF_STRUCTURE
            //     u16 number_of_elements;
            //     u16 properties;
            //     u32 field_list_type_index;
            //     u32 derived;
            //     u32 vshape;
            
            //
            // All of them are followed by a numeric leaf for the size of the structure/union and its name.
            //
            
            u32 properties_and_number_of_elements = pdb_read_type__failable(&type_stream, u32, &error);
            u32 properties = (record->kind == /*LF_STRUCTURE_EX*/0x1609) ? properties_and_number_of_elements : (properties_and_number_of_elements >> 16);
            type_stream.current_offset += (record->kind == /*LF_UNION*/0x1506) ? 4 : 12;
            
            u64 struct_size = pdb_read_numeric_leaf_as_u64(&type_stream, &error);
            struct string name = pdb_read_zero_terminated_string(&type_stream);
            
            if(properties & /* forward ref */(1 << 7)){
                // If this is a forward ref, the struct size is 0.
                // Hence we get the correct struct size by looking up the entry.
                struct pdb_hash_table_entry *table_entry = pdb_hash_table_get(&pdb_context->type_table, name);
                if(table_entry){
                    
                    struct codeview_record_header *real_record = table_entry->record;
                    
                    type_stream = (struct pdb_stream){
                        .base = (void *)(real_record + 1),
                        .size = real_record->length - 2,
                    };
                    
                    type_stream.current_offset += (record->kind == /*LF_UNION*/0x1506) ? 8 : 16;
                    
                    struct_size = pdb_read_numeric_leaf_as_u64(&type_stream, &error);
                }
            }
            
            return struct_size;
        }break;
        
        case 0x1205:{ // LF_BITFIELD
            u32 underlying_type = pdb_read_type__failable(&type_stream, u32, &error);
            
            return pdb_sizeof_type(pdb_context, underlying_type);
        }break;
        
        case 0x1507:{ // LF_ENUM
            u16 count = pdb_read_type__failable(&type_stream, u16, &error);
            u16 properties = pdb_read_type__failable(&type_stream, u16, &error);
            (void)count;
            (void)properties;
            
            
            u32 underlying_type_index = pdb_read_type__failable(&type_stream, u32, &error);
            
            return pdb_sizeof_type(pdb_context, underlying_type_index);
        }break;
        
        
        default: print("UNHANDLED_TYPE_0x%x", record->kind); break;
        
    }
    
    return 0;
}


// returns the size of the type
static smm pdb_print_type(struct context *context, struct pdb_context *pdb_context, u32 type_index, u64 address, int have_address){
    
    smm size = 0;
    
#define dump_basic_type_or_question_marks(format, basic_type)                      \
{                                                                                  \
    basic_type value;                                                              \
    if(guest_read_size(context, &value, address, sizeof(value), PERMISSION_none)){ \
        print(format, value);                                                      \
    }else{                                                                         \
        print("%.*s", size * 2, "????????????????????????????????");               \
    }                                                                              \
}
    
    if(type_index < 0x1000){
        
        //
        // Handle "basic" type indices.
        //
        
        switch(type_index){
            case    0: print("unknown"); return 0;
            case  0x3: print("void");    return 0;
            
            case 0x10:{
                print("s8");
                if(have_address) dump_basic_type_or_question_marks(" %d", s8);
                size = 1;
            }break;
            
            case 0x11:{
                print("s16");
                if(have_address) dump_basic_type_or_question_marks(" %d", s16);
                size = 2;
            }break;
            
            case 0x12:{
                print("s32");
                if(have_address) dump_basic_type_or_question_marks(" %d", s32);
                size = 4;
            }break;
            
            case 0x13:{
                print("s64");
                if(have_address) dump_basic_type_or_question_marks(" %lld", s64);
                size = 8;
            }break;
            
            case 0x20:{
                print("u8");
                if(have_address) dump_basic_type_or_question_marks(" 0x%x", u8);
                size = 1;
            }break;
            case 0x21:{
                print("u16");
                if(have_address) dump_basic_type_or_question_marks(" 0x%x", u16);
                size = 2;
            }break;
            case 0x22:{
                print("u32");
                if(have_address) dump_basic_type_or_question_marks(" 0x%x", u32);
                size = 4;
            }break;
            case 0x23:{
                print("u64");
                if(have_address) dump_basic_type_or_question_marks(" 0x%llx", u64);
                size = 8;
            }break;
            
            case 0x68:{
                print("s8");
                if(have_address) dump_basic_type_or_question_marks(" %d", s8);
                size = 1;
            }break;
            case 0x69:{
                print("u8");
                if(have_address) dump_basic_type_or_question_marks(" 0x%x", u8);
                size = 2;
            }break;
            
            case 0x70:{
                print("char");
                char c = guest_read(char, address);
                if(have_address) print(" '%c' (%d)", c, c);
                size = 1;
            }break;
            
            case 0x71:{
                print("wchar_t");
                wchar_t c = guest_read(wchar_t, address);
                if(have_address) print(" '%wc' (%d)", c, c);
                size = 2;
            }break;
            
            case 0x72:{
                print("s16");
                if(have_address) dump_basic_type_or_question_marks(" %d", s16);
                size = 2;
            }break;
            case 0x73:{
                print("u16");
                if(have_address) dump_basic_type_or_question_marks(" 0x%x", u16);
                size = 2;
            }break;
            case 0x74:{
                print("s32");
                if(have_address) dump_basic_type_or_question_marks(" %d", s32);
                size = 4;
            }break;
            case 0x75:{
                print("u32");
                if(have_address) dump_basic_type_or_question_marks(" 0x%x", u32);
                size = 4;
            }break;
            case 0x76:{
                print("s64");
                if(have_address) dump_basic_type_or_question_marks(" %lld", s64);
                size = 8;
            }break;
            case 0x77:{
                print("u64");
                if(have_address) dump_basic_type_or_question_marks(" 0x%llx", u64);
                size = 8;
            }break;
            
            case 0x40:{
                print("f32");
                if(have_address) dump_basic_type_or_question_marks(" %f", float);
                size = 4;
            }break;
            case 0x41:{
                print("f64");
                if(have_address) dump_basic_type_or_question_marks(" %f", double);
                size = 8;
            }break;
            
            
            case 0x620:{
                print("unsigned char *");
                if(have_address) dump_basic_type_or_question_marks(" %p", unsigned char *);
                size = 8;
            }break;
            case 0x670:{
                print("char *");
                if(have_address) dump_basic_type_or_question_marks(" %p", char *);
                size = 8;
            }break;
            case 0x671:{
                print("wchar_t *");
                if(have_address) dump_basic_type_or_question_marks(" %p", wchar_t *);
                size = 8;
            }break;
            
            case 0x668:{
                print("s8 *");
                if(have_address) dump_basic_type_or_question_marks(" %p", s8 *);
                size = 8;
            }break;
            case 0x669:{
                print("u8 *");
                if(have_address) dump_basic_type_or_question_marks(" %p", u8 *);
                size = 8;
            }break;
            
            case 0x603:{
                print("void *");
                if(have_address) dump_basic_type_or_question_marks(" %p", void *);
                size = 8;
            }break;
            
            default: print("Unhandled type index 0x%x", type_index); return 0;
        }
        return size;
    }
    
    struct codeview_record_header *record = pdb_get_record_for_type_index(pdb_context, type_index);
    if(!record){
        print("ERROR_INVALID_TYPE_INDEX\n");
        return 0;
    }
    
    
    u64 pointer_depth = 0;
    while(record->kind == /*LF_MODIFIER*/0x1001 || record->kind == /*LF_POINTER*/0x1002){
        
        //
        // Go past LF_MODIFIER and LF_POINTER, while counting pointers, to display later.
        // @cleanup: print modifiers?
        //
        
        pointer_depth += (record->kind == /*LF_POINTER*/0x1002);
        type_index = *(u32 *)(record + 1);
        
        if(type_index < 0x1000) break;
        
        record = pdb_get_record_for_type_index(pdb_context, type_index);
        if(!record){
            print("ERROR_INVALID_TYPE_INDEX 0x%x\n", type_index);
            return 0;
        }
    }
    
    if(type_index < 0x1000){
        
        if(pointer_depth){
            //
            // If we have a pointer to a basic type, print the type, but not the value.
            // Further down we then print a pointer value.
            //
            pdb_print_type(context, pdb_context, type_index, 0, /*have_address*/0);
        }else{
            return pdb_print_type(context, pdb_context, type_index, address, have_address);
        }
    }
    
    struct pdb_stream type_stream = {
        .base = (void *)(record + 1),
        .size = record->length - 2,
    };
    
    int error = 0;
    
    switch(record->kind){
        case /*LF_PROCEDURE*/0x1008: print("function"); break;
        
        case 0x1002: break; // LF_POINTER  (which ended in a type_index < 0x1000), print the type below.
        
        case /*LF_ARRAY*/0x1503:{
            
            u32 element_type = pdb_read_type__failable(&type_stream, u32, &error);
            /*u32 index_type = */pdb_read_type__failable(&type_stream, u32, &error);
            
            u64 array_size = pdb_read_numeric_leaf_as_u64(&type_stream, &error);
            
            if(error){
                print("ERROR_ARRAY_TYPE");
            }else{
                smm element_type_size = pdb_print_type(context, pdb_context, element_type, 0, 0); // Don't print values for sub-types -> have_address = 0.
                
                if(!element_type_size){
                    print(" ERROR_ARRAY_ELEMENT_TYPE");
                }else{
                    print("[%llu]", array_size / element_type_size);
                }
            }
            
            size = array_size;
        }break;
        
        //
        // @copy_and_paste from 'load_pdb'.
        //
        case 0x1506:  // LF_UNION
        case 0x1609:  // LF_STRUCTURE_EX
        case 0x1505:{ // LF_STRUCTURE
            
            // LF_UNION
            //     u16 number_of_elements;
            //     u16 properties;
            //     u32 field_list_type_index;
            
            // LF_STRUCTURE_EX
            //     u32 properties;
            //     u32 field_list_type_index;
            //     u32 derived;
            //     u32 vshape;
            
            // LF_STRUCTURE
            //     u16 number_of_elements;
            //     u16 properties;
            //     u32 field_list_type_index;
            //     u32 derived;
            //     u32 vshape;
            
            //
            // All of them are followed by a numeric leaf for the size of the structure/union and its name.
            //
            
            u32 properties_and_number_of_elements = pdb_read_type__failable(&type_stream, u32, &error);
            u32 properties = (record->kind == /*LF_STRUCTURE_EX*/0x1609) ? properties_and_number_of_elements : (properties_and_number_of_elements >> 16);
            
            type_stream.current_offset += (record->kind == /*LF_UNION*/0x1506) ? 4 : 12;
            
            u64 struct_size = pdb_read_numeric_leaf_as_u64(&type_stream, &error);
            
            struct string name = pdb_read_zero_terminated_string(&type_stream);
            if(!name.data || error){
                print("ERROR_STRUCT_OR_UNION");
                break;
            }
            
            char *type_kind = (record->kind == 0x1506) ? "union" : "struct";
            
            print("%s %.*s", type_kind, name.size, name.data);
            
            if(properties & /* forward ref */(1 << 7)){
                // If this is a forward ref, the struct size is 0.
                // Hence we get the correct struct size by looking up the entry.
                struct pdb_hash_table_entry *table_entry = pdb_hash_table_get(&pdb_context->type_table, name);
                if(table_entry){
                    
                    struct codeview_record_header *real_record = table_entry->record;
                    
                    type_stream = (struct pdb_stream){
                        .base = (void *)(real_record + 1),
                        .size = real_record->length - 2,
                    };
                    
                    type_stream.current_offset += (record->kind == /*LF_UNION*/0x1506) ? 8 : 16;
                    
                    struct_size = pdb_read_numeric_leaf_as_u64(&type_stream, &error);
                }
            }
            
            size = struct_size;
        }break;
        
        case 0x1205:{ // LF_BITFIELD
            u32 underlying_type = pdb_read_type__failable(&type_stream, u32, &error);
            u8 length           = pdb_read_type__failable(&type_stream, u8, &error);
            u8 position         = pdb_read_type__failable(&type_stream, u8, &error);
            
            if(error){
                print("ERROR_BITFIELD_TYPE");
                break;
            }
            
            smm underlying_type_size = pdb_print_type(context, pdb_context, underlying_type, 0, 0); // Don't print values for sub-types -> have_address = 0.
            if(length == 1){
                print(":1 (0x%llx)", 1ull << position);
            }else{
                print(":%d (pos %d)", length, position);
            }
            
            if(have_address && !pointer_depth){
                u64 mask  = ((1ull << length) - 1) << position;
                u64 value = 0;
                if(underlying_type_size <= 8 && guest_read_size(context, &value, address, underlying_type_size, PERMISSION_none)){
                    print(" = 0x%llx", (value & mask) >> position);
                }else{
                    print(" = ?");
                }
            }
            
            size = underlying_type_size;
        }break;
        
        case 0x1507:{ // LF_ENUM
            u16 count = pdb_read_type__failable(&type_stream, u16, &error);
            u16 properties = pdb_read_type__failable(&type_stream, u16, &error);
            (void)count;
            (void)properties;
            
            
            u32 underlying_type_index = pdb_read_type__failable(&type_stream, u32, &error);
            u32 fieldlist_type_index  = pdb_read_type__failable(&type_stream, u32, &error);
            
            struct string name = pdb_read_zero_terminated_string(&type_stream);
            if(!name.data || error){
                print("ERROR_LF_ENUM");
                break;
            }
            
            print("enum %.*s (", name.size, name.data);
            
            smm underlying_type_size = pdb_print_type(context, pdb_context, underlying_type_index, 0, 0); // Don't print values for sub-types -> have_address = 0.
            
            print(")");
            
            if(have_address && !pointer_depth){
                u64 value = 0;
                if(underlying_type_size <= 8 && guest_read_size(context, &value, address, underlying_type_size, PERMISSION_none)){
                    print(" = ");
                    
                    struct codeview_record_header *fieldlist = pdb_get_record_for_type_index(pdb_context, fieldlist_type_index);
                    if(!fieldlist || fieldlist->kind != 0x1203){
                        print("ERROR_LF_ENUM");
                        break;
                    }
                    
                    struct pdb_stream fieldlist_stream = {
                        .base = (void *)(fieldlist + 1),
                        .size = fieldlist->length - 2,
                    };
                    
                    while(fieldlist_stream.current_offset < fieldlist_stream.size){
                        u16 field_kind     = pdb_read_type__failable(&fieldlist_stream, u16, &error);
                        /*u16 attributes = */pdb_read_type__failable(&fieldlist_stream, u16, &error); // C++ stuff
                        
                        u64 member_value  = pdb_read_numeric_leaf_as_u64(&fieldlist_stream, &error);
                        struct string member_name = pdb_read_zero_terminated_string(&fieldlist_stream);
                        
                        if(error || field_kind != /*LF_ENUMERATE*/0x1502 || !member_name.data){
                            break;
                        }
                        
                        // Align the stream to a 4-byte boundary.
                        fieldlist_stream.current_offset = (fieldlist_stream.current_offset + 3) & ~3;
                        
                        if(member_value == value){
                            print("/*%.*s*/", member_name.size, member_name.data);
                        }
                    }
                    
                    print("0x%llx", value);
                }else{
                    print(" = ?");
                }
            }
            
            size = underlying_type_size;
        }break;
        
        
        default: print("UNHANDLED_TYPE_0x%x", record->kind); break;
        
    }
    
    if(pointer_depth){
        print(" ");
        
        for(u64 i = 0; i < pointer_depth; i++) print("*");
        
        if(have_address) dump_basic_type_or_question_marks(" %p", u64);
        
        size = 8;
    }
    
    return size;
}

void pdb_dump_type(struct context *context, struct pdb_context *pdb_context, struct string type_name, struct string member_string, u64 address, int have_address){
    
    struct pdb_hash_table_entry *initial_type = pdb_hash_table_get(&pdb_context->type_table, type_name);
    if(!initial_type){
        print("Type '%.*s' was not found.\n", type_name.size, type_name.data);
        return;
    }
    
    u32 fieldlist_type_index = (u32)initial_type->rva_value_or_type_index;
    struct codeview_record_header *fieldlist = pdb_get_record_for_type_index(pdb_context, fieldlist_type_index);
    
    if(!fieldlist || fieldlist->kind != 0x1203){
        print("Type '%.*s' has invalid fieldlist.\n", type_name.size, type_name.data);
        return;
    }
    
    //
    // Search for the specific member specified by 'member_string'.
    //
    
    u64 root_offset = 0;
    
    while(member_string.size){
        
        if(member_string.data[0] == '.'){
            member_string.data += 1;
            member_string.size -= 1;
        }
        
        struct string member = member_string;
        
        for(smm index = 0; index < member_string.size; index++){
            if(member_string.data[index] == '.' || member_string.data[index] == '['){
                member.size = index;
                member_string.size -= index;
                member_string.data += index;
                break;
            }
        }
        
        if(member.data == member_string.data){
            member_string = (struct string){0};
        }
        
        int found_member = 0, error = 0;
        
        struct pdb_stream fieldlist_stream = {
            .base = (void *)(fieldlist + 1),
            .size = fieldlist->length - 2,
        };
        
        while(fieldlist_stream.current_offset < fieldlist_stream.size){
            u16 field_kind     = pdb_read_type__failable(&fieldlist_stream, u16, &error);
            /*u16 attributes = */pdb_read_type__failable(&fieldlist_stream, u16, &error); // C++ stuff
            u32 member_type_index = pdb_read_type__failable(&fieldlist_stream, u32, &error);
            u64 member_offset  = pdb_read_numeric_leaf_as_u64(&fieldlist_stream, &error);
            struct string member_name = pdb_read_zero_terminated_string(&fieldlist_stream);
            
            if(error || field_kind != /*LF_MEMBER*/0x150d || !member_name.data){
                print("Fieldlist %x is invalid.\n", fieldlist_type_index);
                return;
            }
            
            // Align the stream to a 4-byte boundary.
            fieldlist_stream.current_offset = (fieldlist_stream.current_offset + 3) & ~3;
            
            if(!string_match(member_name, member)) continue;
            
            found_member = 1;
            root_offset += member_offset;
            
            struct codeview_record_header *field_type = pdb_get_record_for_type_index(pdb_context, member_type_index);
            if(!field_type){
                print("Field '%.*s' has invalid type index.\n", member.size, member.data);
                return;
            }
            
            while(field_type->kind == /*LF_MODIFIER*/0x1001){
                u32 type_index = *(u32 *)(field_type + 1);
                field_type = pdb_get_record_for_type_index(pdb_context, type_index);
                if(field_type){
                    print("Field '%.*s' has invalid type index.\n", member.size, member.data);
                    return;
                }
            }
            
            if(field_type->kind == /*LF_ARRAY*/0x1503 && member_string.size){
                
                if(member_string.data[0] != '['){
                    print("member '%.*s'is array expected '['\n", member_string.size, member_string.data);
                    return;
                }
                
                struct pdb_stream array_stream = {
                    .base = (void *)(field_type + 1),
                    .size = field_type->length - 2,
                };
                
                u32 element_type = pdb_read_type__failable(&array_stream, u32, &error);
                /*u32 index_type = */pdb_read_type__failable(&array_stream, u32, &error);
                u64 array_size = pdb_read_numeric_leaf_as_u64(&array_stream, &error);
                
                smm element_type_size = pdb_sizeof_type(pdb_context, element_type);
                
                if(error){
                    print("Failed to read array type 0x%x for member string '%.*s'.\n", member_string.size, member_string.data);
                    return;
                }
                
                member_string.size -= 1;
                member_string.data += 1;
                
                struct string index_string = {
                    .data = member_string.data,
                };
                
                for(smm index = 0; index < member_string.size; index++){
                    if(member_string.data[index] == ']'){
                        index_string.size = index;
                        member_string.size -= index + 1;
                        member_string.data += index + 1;
                        break;
                    }
                }
                
                if(index_string.size == 0){
                    print("failed to parse index for member_string '%.*s'\n", member_string.size + 1, member_string.data - 1);
                    return;
                }
                
                u64 index = parse_number(index_string, &error);
                if(error){
                    print("Failed to parse index string '%.*s'\n", index_string.size, index_string.data);
                    return;
                }
                
                if(!element_type_size){
                    print("Failed to get size for array element type.\n");
                    return;
                }
                
                if(array_size / element_type_size <= index){
                    print("Warning: index 0x%llx is out of bounds of the structure, array has size 0x%llx.\n", index, array_size / element_type_size);
                }
                
                root_offset += index * element_type_size;
                field_type = pdb_get_record_for_type_index(pdb_context, element_type);
                member_type_index = element_type;
            }
            
            
            if(field_type->kind == /*LF_STRUCTURE*/0x1505 || field_type->kind == /*LF_STRUCTURE_EX*/0x1609 || field_type->kind == /*LF_UNION*/0x1506){
                
                struct pdb_stream type_stream = {
                    .base = (void *)(field_type + 1),
                    .size = field_type->length - 2,
                };
                
                u32 properties_and_number_of_elements = pdb_read_type__failable(&type_stream, u32, &error);
                u32 properties = (field_type->kind == /*LF_STRUCTURE_EX*/0x1609) ? properties_and_number_of_elements : (properties_and_number_of_elements >> 16);
                fieldlist_type_index = pdb_read_type__failable(&type_stream, u32, &error);
                
                if(error){
                    print("'%.*s' invalid fieldlist.\n", member.size, member.data);
                    return;
                }
                
                if(properties & /* forward ref */(1 << 7)){
                    //
                    // This is a forward ref. Get the name and use it to look up the real type.
                    //
                    
                    type_stream.current_offset += (field_type->kind == /*LF_UNION*/0x1506) ? 0 : 8;
                    
                    /*u64 size = */pdb_read_numeric_leaf_as_u64(&type_stream, &error);
                    
                    struct string name = pdb_read_zero_terminated_string(&type_stream);
                    
                    struct pdb_hash_table_entry *table_entry = pdb_hash_table_get(&pdb_context->type_table, name);
                    if(!table_entry){
                        print("'%.*s' has undefined struct or union type.\n", member.size, member.data);
                        return;
                    }
                    
                    struct codeview_record_header *real_record = table_entry->record;
                    
                    type_stream = (struct pdb_stream){
                        .base = (void *)(real_record + 1),
                        .size = real_record->length - 2,
                    };
                    
                    pdb_read_type__failable(&type_stream, u32, &error);
                    fieldlist_type_index = pdb_read_type__failable(&type_stream, u32, &error);
                }
                
                fieldlist = pdb_get_record_for_type_index(pdb_context, fieldlist_type_index);
                if(error || !fieldlist || fieldlist->kind != 0x1203){
                    print("'%.*s' invalid fieldlist.\n", member.size, member.data);
                    return;
                }
            }else if(member_string.size){
                print("'%.*s' is not of structure or union type.\n", member.size, member.data);
                return;
            }else{
                //
                // Its not a struct or union, but it does not have to be, as we are at the end of the 'member_string'.
                // Just print the type.
                //
                print("    %p: %.*s ", address + root_offset, member.size, member.data);
                pdb_print_type(context, pdb_context, member_type_index, address + root_offset, have_address);
                print("\n");
                
                return;
            }
            break;
        }
        
        if(!found_member){
            print("'%.*s' is not a valid member.\n", member.size, member.data);
            return;
        }
    }
    
    //
    // Print each member of the fieldlist.
    //
    
    struct pdb_stream fieldlist_stream = {
        .base = (void *)(fieldlist + 1),
        .size = fieldlist->length - 2,
    };
    
    int error = 0;
    
    if(have_address) print("%p:\n", address);
    while(fieldlist_stream.current_offset < fieldlist_stream.size){
        u16 field_kind     = pdb_read_type__failable(&fieldlist_stream, u16, &error);
        /*u16 attributes = */pdb_read_type__failable(&fieldlist_stream, u16, &error); // C++ stuff
        u32 member_type_index = pdb_read_type__failable(&fieldlist_stream, u32, &error);
        u64 member_offset  = pdb_read_numeric_leaf_as_u64(&fieldlist_stream, &error);
        struct string name = pdb_read_zero_terminated_string(&fieldlist_stream);
        
        if(error || field_kind != /*LF_MEMBER*/0x150d || !name.data){
            print("Type 0x%x has invalid fieldlist.\n", fieldlist_type_index);
            return;
        }
        
        // Align the stream to a 4-byte boundary.
        fieldlist_stream.current_offset = (fieldlist_stream.current_offset + 3) & ~3;
        
        print("    %4llx: %-40.*s ", root_offset + member_offset, name.size, name.data);
        pdb_print_type(context, pdb_context, member_type_index, address + root_offset + member_offset, have_address);
        print("\n");
    }
}


// @cleanup: This function was copied from the above. It could probably be factored better.
//           Secondly, if this _fails_ the calling code should have to deal with it.
//           Hence, this has to be able to fail.
u64 pdb_get_member_offset(struct pdb_context *pdb_context, struct string type_name, struct string member_string, int *error){
    
    struct pdb_hash_table_entry *initial_type = pdb_hash_table_get(&pdb_context->type_table, type_name);
    if(!initial_type){
        print("Type '%.*s' was not found.\n", type_name.size, type_name.data);
        *error = 1;
        return 0;
    }
    
    u32 fieldlist_type_index = (u32)initial_type->rva_value_or_type_index;
    struct codeview_record_header *fieldlist = pdb_get_record_for_type_index(pdb_context, fieldlist_type_index);
    
    if(!fieldlist || fieldlist->kind != 0x1203){
        print("Type '%.*s' has invalid fieldlist.\n", type_name.size, type_name.data);
        *error = 1;
        return 0;
    }
    
    //
    // Search for the specific member specified by 'member_string'.
    //
    
    u64 root_offset = 0;
    
    while(member_string.size){
        
        if(member_string.data[0] == '.'){
            member_string.data += 1;
            member_string.size -= 1;
        }
        
        struct string member = member_string;
        
        for(smm index = 0; index < member_string.size; index++){
            if(member_string.data[index] == '.' || member_string.data[index] == '['){
                member.size = index;
                member_string.size -= index;
                member_string.data += index;
                break;
            }
        }
        
        if(member.data == member_string.data){
            member_string = (struct string){0};
        }
        
        int found_member = 0;
        
        struct pdb_stream fieldlist_stream = {
            .base = (void *)(fieldlist + 1),
            .size = fieldlist->length - 2,
        };
        
        while(fieldlist_stream.current_offset < fieldlist_stream.size){
            u16 field_kind     = pdb_read_type__failable(&fieldlist_stream, u16, error);
            /*u16 attributes = */pdb_read_type__failable(&fieldlist_stream, u16, error); // C++ stuff
            u32 member_type_index = pdb_read_type__failable(&fieldlist_stream, u32, error);
            u64 member_offset  = pdb_read_numeric_leaf_as_u64(&fieldlist_stream, error);
            struct string member_name = pdb_read_zero_terminated_string(&fieldlist_stream);
            
            if(*error || field_kind != /*LF_MEMBER*/0x150d || !member_name.data){
                print("Fieldlist %x is invalid.\n", fieldlist_type_index);
                *error = 1;
                return 0;
            }
            
            // Align the stream to a 4-byte boundary.
            fieldlist_stream.current_offset = (fieldlist_stream.current_offset + 3) & ~3;
            
            if(!string_match(member_name, member)) continue;
            
            found_member = 1;
            root_offset += member_offset;
            
            if(member_type_index < 0x1000){
                //
                // Its a leaf type, just return the offset.
                //
                if(member_string.size){
                    print("'%.*s' is not of structure or union type.\n", member.size, member.data);
                    *error = 1;
                    return 0;
                }
                return root_offset;
            }
            
            struct codeview_record_header *field_type = pdb_get_record_for_type_index(pdb_context, member_type_index);
            if(!field_type){
                print("field %.*s has invalid type index.\n", member.size, member.data);
                *error = 1;
                return 0;
            }
            
            while(field_type->kind == /*LF_MODIFIER*/0x1001){
                u32 type_index = *(u32 *)(field_type + 1);
                field_type = pdb_get_record_for_type_index(pdb_context, type_index);
                if(field_type){
                    print("Field '%.*s' has invalid type index.\n", member.size, member.data);
                    *error = 1;
                    return 0;
                }
            }
            
            if(field_type->kind == /*LF_ARRAY*/0x1503 && member_string.size){
                
                if(member_string.data[0] != '['){
                    print("member '%.*s'is array expected '['\n", member_string.size, member_string.data);
                    *error = 1;
                    return 0;
                }
                
                struct pdb_stream array_stream = {
                    .base = (void *)(field_type + 1),
                    .size = field_type->length - 2,
                };
                
                u32 element_type = pdb_read_type__failable(&array_stream, u32, error);
                /*u32 index_type = */pdb_read_type__failable(&array_stream, u32, error);
                u64 array_size = pdb_read_numeric_leaf_as_u64(&array_stream, error);
                
                smm element_type_size = pdb_sizeof_type(pdb_context, element_type);
                
                if(*error){
                    print("Failed to read array type 0x%x for member string '%.*s'.\n", member_string.size, member_string.data);
                    return 0;
                }
                
                member_string.size -= 1;
                member_string.data += 1;
                
                struct string index_string = {
                    .data = member_string.data
                        };
                
                for(smm index = 0; index < member_string.size; index++){
                    if(member_string.data[index] == ']'){
                        index_string.size = index;
                        member_string.size -= index + 1;
                        member_string.data += index + 1;
                        break;
                    }
                }
                
                if(index_string.size == 0){
                    print("failed to parse index for member_string '%.*s'\n", member_string.size + 1, member_string.data - 1);
                    *error = 1;
                    return 0;
                }
                
                u64 index = parse_number(index_string, error);
                if(*error){
                    print("Failed to parse index string '%.*s'\n", index_string.size, index_string.data);
                    return 0;
                }
                
                if(!element_type_size){
                    print("Failed to get size for array element type.\n");
                    *error = 1;
                    return 0;
                }
                
                if(array_size / element_type_size <= index){
                    print("Warning: index 0x%llx is out of bounds of the structure, array has size 0x%llx.\n", index, array_size / element_type_size);
                }
                
                root_offset += index * element_type_size;
                field_type = pdb_get_record_for_type_index(pdb_context, element_type);
                member_type_index = element_type;
            }
            
            if(field_type->kind == /*LF_STRUCTURE*/0x1505 || field_type->kind == /*LF_STRUCTURE_EX*/0x1609 || field_type->kind == /*LF_UNION*/0x1506){
                
                struct pdb_stream type_stream = {
                    .base = (void *)(field_type + 1),
                    .size = field_type->length - 2,
                };
                
                u32 properties_and_number_of_elements = pdb_read_type__failable(&type_stream, u32, error);
                u32 properties = (field_type->kind == /*LF_STRUCTURE_EX*/0x1609) ? properties_and_number_of_elements : (properties_and_number_of_elements >> 16);
                fieldlist_type_index = pdb_read_type__failable(&type_stream, u32, error);
                
                if(*error){
                    print("'%.*s' invalid fieldlist.\n", member.size, member.data);
                    return 0;
                }
                
                if(properties & /* forward ref */(1 << 7)){
                    //
                    // This is a forward ref. Get the name and use it to look up the real type.
                    //
                    
                    type_stream.current_offset += (field_type->kind == /*LF_UNION*/0x1506) ? 0 : 8;
                    
                    /*u64 size = */pdb_read_numeric_leaf_as_u64(&type_stream, error);
                    
                    struct string name = pdb_read_zero_terminated_string(&type_stream);
                    
                    struct pdb_hash_table_entry *table_entry = pdb_hash_table_get(&pdb_context->type_table, name);
                    if(!table_entry){
                        print("'%.*s' has undefined struct or union type.\n", member.size, member.data);
                        *error = 1;
                        return 0;
                    }
                    
                    struct codeview_record_header *real_record = table_entry->record;
                    
                    type_stream = (struct pdb_stream){
                        .base = (void *)(real_record + 1),
                        .size = real_record->length - 2,
                    };
                    
                    pdb_read_type__failable(&type_stream, u32, error);
                    fieldlist_type_index = pdb_read_type__failable(&type_stream, u32, error);
                }
                
                fieldlist = pdb_get_record_for_type_index(pdb_context, fieldlist_type_index);
                if(*error || !fieldlist || fieldlist->kind != 0x1203){
                    print("'%.*s' invalid fieldlist.\n", member.size, member.data);
                    *error = 1;
                    return 0;
                }
            }else if(member_string.size){
                print("'%.*s' is not of structure or union type.\n", member.size, member.data);
                *error = 1;
                return 0;
            }else{
                //
                // Its not a struct or union, but it does not have to be, as we are at the end of the 'member_string'.
                // Just return the offset.
                //
                return root_offset;
            }
            break;
        }
        
        if(!found_member){
            print("'%.*s' is not a valid member.\n", member.size, member.data);
            *error = 1;
            return 0;
        }
    }
    
    return root_offset;
}

