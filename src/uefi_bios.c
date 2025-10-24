// 
// A (mostly stubbed-out) UEFI implementation, which can boot (some versions) of Windows 11.
// Windows does not need much from UEFI, here is ~what we give it:
//    * Read and write the disk image.
//    * Read and write UEFI-variables.
//    * Allocate and free physical pages.
//    * Provide ACPI / SMBIOS stubs.
//    * Provide the GOP-framebuffer.
//    * Glue code (EFI-protocol stuff).
// 


typedef _Bool boolean;

typedef unsigned char    u8;
typedef unsigned short   u16;
typedef unsigned int     u32;
typedef unsigned __int64 u64;

typedef signed char    s8;
typedef signed short   s16;
typedef signed int     s32;
typedef signed __int64 s64;

int _fltused;

#include <stdarg.h>
#include <stdint.h>

#include <intrin.h>


#ifdef __clang__

unsigned long __readcr8(void){
    u64 val;
    __asm__ volatile("mov %%cr8, %0" : "=r"(val));
    return (unsigned long)val;
}

void __writecr8(unsigned int val){
    u64 _val = val;
    __asm__ volatile("mov %0, %%cr8" :: "r"(_val));
}

void __sidt(void *idtr_ptr) {
    struct __attribute__((packed)) idtr {
        uint16_t limit;
        uint64_t base;
    } *idtr = idtr_ptr;
    
    __asm__ volatile("sidt %0" : "=m"(*idtr));
}

void __writemsr(unsigned long msr, u64 value) {
    uint32_t low = value & 0xFFFFFFFF;
    uint32_t high = value >> 32;
    __asm__ volatile("wrmsr"
            :
            : "c"(msr), "a"(low), "d"(high));
}

void *memset(void *mem, int val, size_t amount){
    u8 *it = mem;
    for(size_t i = 0; i < amount; i++){
        *it++ = (u8)val;
    }
    return mem;
}

void *memcpy(void *dest, const void *source, size_t amount){
    u8 *it  = dest;
    const u8 *it2 = source;
    for(size_t i = 0; i < amount; i++){
        *it++ = *it2++;
    }
    
    return dest;
}

#endif

struct efi_handle{ void *value; };
struct efi_event{ void *value; };

struct efi_guid{
    u32 data1;
    u16 data2;
    u16 data3;
    u8  data4[8];
};

#define PRINT_EFI_GUID_FORMAT "{%.8x-%.4x-%.4x-%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x}"
#define PRINT_EFI_GUID_MEMBERS(guid) (guid).data1, (guid).data2, (guid).data3, (guid).data4[0], (guid).data4[1], (guid).data4[2], (guid).data4[3], (guid).data4[4], (guid).data4[5], (guid).data4[6], (guid).data4[7]

int guid_match(struct efi_guid *guid_1, struct efi_guid *guid_2){
    if(guid_1->data1 != guid_2->data1) return 0;
    if(guid_1->data2 != guid_2->data2) return 0;
    if(guid_1->data3 != guid_2->data3) return 0;
    if(*(u64 *)guid_1->data4 != *(u64 *)guid_2->data4) return 0;
    return 1;
}

typedef s64 efi_status;

#define EFI_BUFFER_TOO_SMALL  0x8000000000000005
#define EFI_UNSUPPORTED       0x8000000000000003
#define EFI_INVALID_PARAMETER 0x8000000000000002
#define EFI_NOT_FOUND         0x800000000000000e
#define EFI_SUCCESS 0


#define null ((void *)0)
#define array_count(a) (sizeof(a)/sizeof(*(a)))

//_____________________________________________________________________________________________________________________
// Bios escapes.
#include "uefi_bios.h"

#define ENABLE_BIOS_LOGGING 0

#if ENABLE_BIOS_LOGGING
#define STB_SPRINTF_DECORATE(name) name
#define STB_SPRINTF_IMPLEMENTATION

// If you want to enable bios logging, you have to download 'stb_sprintf.h'.
//     https://github.com/nothings/stb/blob/master/stb_sprintf.h

#include "stb_sprintf.h"
#endif

__declspec(noinline) void cause_vmexit(u64 code, u64 arg1, u64 arg2, u64 arg3){
    __readmsr(code);
}

void bios_print_string(char *string, size_t size){
    if(ENABLE_BIOS_LOGGING) cause_vmexit(BIOS_log, (u64)string, size, 0);
}

void bios_crash(void){
    cause_vmexit(BIOS_crash, 0, 0, 0);
}

void bios_break(void){
    cause_vmexit(BIOS_break, 0, 0, 0);
}

void bios_disk_read(u64 lba, u64 buffer_size, void *buffer){
    cause_vmexit(BIOS_disk_read, lba, buffer_size, (u64)buffer);
}

void bios_disk_write(u64 lba, u64 buffer_size, void *buffer){
    cause_vmexit(BIOS_disk_write, lba, buffer_size, (u64)buffer);
}

#if ENABLE_BIOS_LOGGING

void bios_log(char *format, ...){
    u8 buffer[0x1000];
    
    va_list va;
    va_start(va, format);
    int length = vsnprintf(buffer, sizeof(buffer), format, va);
    va_end(va);
    
    bios_print_string(buffer, length);
}

#define log bios_log

#else

#define log(...)

#endif

//_____________________________________________________________________________________________________________________
// EFI text input output protocols

struct efi_input_key{
    u16 scan_code;
    s16 unicode_char;
};

struct efi_simple_text_input_protocol{
    efi_status (*reset)(struct efi_simple_text_input_protocol *, boolean extended_verification);
    efi_status (*read_key_stroke)(struct efi_simple_text_input_protocol *, struct efi_input_key *out_key_data);
    
    struct efi_event wait_for_key;
};

efi_status efi_simple_text_input__reset(void){ 
    log("stubbed efi_simple_text_input_ex__reset");
    return 0; 
}
efi_status efi_simple_text_input__read_key_stroke(void){ log("unimplemented efi_simple_text_input_ex__read_key_stroke\n"); bios_crash(); return 0; }

struct efi_simple_text_input_protocol g_efi_simple_text_input_protocol = {
    .reset = (void *)efi_simple_text_input__reset,
    .read_key_stroke = (void *)efi_simple_text_input__read_key_stroke,
};

struct efi_simple_text_input_ex_protocol{
    void *reset;
    void *read_key_stroke;
    
    struct efi_event wait_for_key;
    
    void *set_state;
    void *register_key_notify;
    void *unregister_key_notify;
};

efi_status efi_simple_text_input_ex__reset(void){ log("unimplemented efi_simple_text_input_ex__reset\n"); bios_crash(); return 0; }
efi_status efi_simple_text_input_ex__read_key_stroke(void){ log("unimplemented efi_simple_text_input_ex__read_key_stroke\n"); bios_crash(); return 0; }
efi_status efi_simple_text_input_ex__set_state(void){ 
    log("stubbed efi_simple_text_input_ex__set_state"); 
    return 0; 
}
efi_status efi_simple_text_input_ex__register_key_notify(void){ log("unimplemented efi_simple_text_input_ex__register_key_notify\n"); bios_crash(); return 0; }
efi_status efi_simple_text_input_ex__unregister_key_notify(void){ log("unimplemented efi_simple_text_input_ex__unregister_key_notify\n"); bios_crash(); return 0; }


#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID {0xdd9e7534, 0x7762, 0x4698, {0x8c, 0x14, 0xf5, 0x85, 0x17, 0xa6, 0x25, 0xaa}}
struct efi_simple_text_input_ex_protocol g_simple_text_input_ex_protocol = {
    .reset                 = efi_simple_text_input_ex__reset,
    .read_key_stroke       = efi_simple_text_input_ex__read_key_stroke,
    .set_state             = efi_simple_text_input_ex__set_state,
    .register_key_notify   = efi_simple_text_input_ex__register_key_notify,
    .unregister_key_notify = efi_simple_text_input_ex__unregister_key_notify,
};

struct efi_simple_text_output_protocol{
    efi_status (*reset)(struct efi_simple_text_output_protocol *, boolean extended_verification);
    efi_status (*output_string)(struct efi_simple_text_output_protocol *, s16 *);
    efi_status (*test_string)(struct efi_simple_text_output_protocol *, s16 *);
    efi_status (*query_mode)(struct efi_simple_text_output_protocol *, size_t mode_number, size_t *out_columns, size_t *out_rows);
    efi_status (*set_mode)(struct efi_simple_text_output_protocol *, size_t mode_number);
    efi_status (*set_attribute)(struct efi_simple_text_output_protocol *, size_t attribute);
    efi_status (*clear_screen)(struct efi_simple_text_output_protocol *);
    efi_status (*set_cursor_position)(struct efi_simple_text_output_protocol *, size_t column, size_t row);
    efi_status (*enable_cursor)(struct efi_simple_text_output_protocol *, boolean);
    
    struct efi_simple_text_output_mode{
        s32 max_mode;
        s32 mode;
        s32 attributes;
        s32 cursor_column;
        s32 cursor_row;
        _Bool cursor_visible;
    } *mode;
};

efi_status efi_simple_text_output__reset(struct efi_simple_text_output_protocol *protocol, boolean extended_verification){
    log("unhandled efi_simple_text_output__reset"); bios_crash(); return 0;
}
efi_status efi_simple_text_output__output_string(struct efi_simple_text_output_protocol *protocol, s16 *string){
    log("unhandled efi_simple_text_output__output_string"); bios_crash(); return 0;
}
efi_status efi_simple_text_output__test_string(struct efi_simple_text_output_protocol *protocol, s16 *string){
    log("unhandled efi_simple_text_output__test_string"); bios_crash(); return 0;
}

efi_status efi_simple_text_output__query_mode(struct efi_simple_text_output_protocol *protocol, size_t mode_number, size_t *out_columns, size_t *out_rows){
    
    log("protocol %p mode number %lld", protocol, mode_number);
    
    *out_columns = 0x50;
    *out_rows = 0x19;
    
    return 0;
}

efi_status efi_simple_text_output__set_mode(struct efi_simple_text_output_protocol *protocol, size_t mode_number){
    log("unhandled efi_simple_text_output__set_mode"); bios_crash(); return 0;
}
efi_status efi_simple_text_output__set_attribute(struct efi_simple_text_output_protocol *protocol, size_t attribute){
    log("unhandled efi_simple_text_output__set_attribute"); bios_crash(); return 0;
}
efi_status efi_simple_text_output__clear_screen(struct efi_simple_text_output_protocol *protocol){
    log("unhandled efi_simple_text_output__clear_screen"); bios_crash(); return 0;
}
efi_status efi_simple_text_output__set_cursor_position(struct efi_simple_text_output_protocol *protocol, size_t column, size_t row){
    log("unhandled efi_simple_text_output__set_cursor_position"); bios_crash(); return 0;
}
efi_status efi_simple_text_output__enable_cursor(struct efi_simple_text_output_protocol *protocol, boolean enable_cursor){
    log("unhandled efi_simple_text_output__enable_cursor"); bios_crash(); return 0;
}

struct efi_simple_text_output_mode g_simple_text_output_mode = {
    .max_mode = 4,
    .mode = 0,
    .attributes = 7,
    .cursor_column = 1,
    .cursor_row = 24,
    .cursor_visible = 0,
};

struct efi_simple_text_output_protocol g_efi_simple_text_output_protocol = {
    .reset               = efi_simple_text_output__reset,
    .output_string       = efi_simple_text_output__output_string,
    .test_string         = efi_simple_text_output__test_string,
    .query_mode          = efi_simple_text_output__query_mode,
    .set_mode            = efi_simple_text_output__set_mode,
    .set_attribute       = efi_simple_text_output__set_attribute,
    .clear_screen        = efi_simple_text_output__clear_screen,
    .set_cursor_position = efi_simple_text_output__set_cursor_position,
    .enable_cursor       = efi_simple_text_output__enable_cursor,
    .mode                = &g_simple_text_output_mode,
};

//_____________________________________________________________________________________________________________________
// Efi block io protocol

#define EFI_BLOCK_IO_PROTOCOL_GUID {0x964e5b21,0x6459,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

struct efi_block_io_protocol{
    u64 revision;
    struct efi_block_io_media *media;
    void *reset;
    void *read_blocks;
    void *write_blocks;
    void *flush_blocks;
};

struct efi_block_io_media{
    u32 media_id;
    u8  removable_media;
    u8  media_present;
    u8  logical_partition;
    u8  read_only;
    u8  write_caching;
    u32 block_size;
    u32 io_align;
    u64 last_block;
    u64 lowest_aligned_lba;
    u32 logical_blocks_per_physical_block;
    u32 optimal_transfer_length_granularity;
};

extern struct efi_block_io_protocol g_partition_io_protocol;

u64 g_efi_system_partition_starting_lba;

efi_status efi_block_io__reset(void){ log("unimplemented efi_block_io__reset"); bios_crash(); return 0; }
efi_status efi_block_io__read_blocks(struct efi_block_io_protocol *protocol, u32 media_id, u64 lba, u64 buffer_size, void *buffer){ 
    
    // If it is trying to read from the partition instead of the whole disk, add the offset of the partition.
    if(protocol == &g_partition_io_protocol) lba += g_efi_system_partition_starting_lba;
    
    log("efi_block_io__read_blocks protocol: %p media_id: %x lba: 0x%llx, buffer_size: 0x%llx address %p", protocol, media_id, lba, buffer_size, buffer);
    
    bios_disk_read(lba, buffer_size, buffer);
    
#if 0
    for(u32 buffer_offset = 0; buffer_offset + 16 <= buffer_size; buffer_offset += 16){
        u8 *at = (u8 *)buffer + buffer_offset;
        
        log("%.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x - %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x",
                at[0], at[1], at[2], at[3], at[4], at[5], at[6], at[7], 
                at[8], at[9], at[10], at[11], at[12], at[13], at[14], at[15]);
        
    }
#endif
    
    return 0;
}

efi_status efi_block_io__write_blocks(struct efi_block_io_protocol *protocol, u32 media_id, u64 lba, u64 buffer_size, void *buffer){ 
    
    // If it is trying to read from the partition instead of the whole disk, add the offset of the partition.
    if(protocol == &g_partition_io_protocol) lba += g_efi_system_partition_starting_lba;
    
    bios_disk_write(lba, buffer_size, buffer);
    
#if 0
    for(u32 buffer_offset = 0; buffer_offset + 16 <= buffer_size; buffer_offset += 16){
        u8 *at = (u8 *)buffer + buffer_offset;
        
#define c(a) ((a > 32 && a < 127) ? a : '.')
        log("%.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x - %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
                at[0], at[1], at[2], at[3], at[4], at[5], at[6], at[7], 
                at[8], at[9], at[10], at[11], at[12], at[13], at[14], at[15], 
                c(at[0]), c(at[1]), c(at[2]), c(at[3]), c(at[4]), c(at[5]), c(at[6]), c(at[7]), 
                c(at[8]), c(at[9]), c(at[10]), c(at[11]), c(at[12]), c(at[13]), c(at[14]), c(at[15]));
        
        #undef c
    }
#endif
    
    return 0;
}

efi_status efi_block_io__flush_blocks(void){ log("unimplemented efi_block_io__flush_blocks"); bios_crash(); return 0; }

struct efi_block_io_media g_logical_block_media = {
    .media_id = 1,
    .media_present = 1,
    .block_size = 0x200,
    .io_align = 0x2,
    .last_block = 0x31fff, // @note: Filled in in 'entry'.
};

struct efi_block_io_protocol g_logical_block_io_protocol = {
    .revision = 0x20031,
    .media = &g_logical_block_media,
    .reset = efi_block_io__reset,
    .read_blocks = efi_block_io__read_blocks,
    .write_blocks = efi_block_io__write_blocks,
    .flush_blocks = efi_block_io__flush_blocks,
};

struct efi_block_io_media g_partition_media = {
    .media_id = 1,
    .media_present = 1,
    .logical_partition = 1,
    .block_size = 0x200,
    .last_block = 0x31fff, // @note: Filled in in 'entry'.
};

struct efi_block_io_protocol g_partition_io_protocol = {
    .revision = 0x20031,
    .media = &g_partition_media,
    .reset = efi_block_io__reset,
    .read_blocks = efi_block_io__read_blocks,
    .write_blocks = efi_block_io__write_blocks,
    .flush_blocks = efi_block_io__flush_blocks,
};

//_____________________________________________________________________________________________________________________
// Efi device path

#define EFI_DEVICE_PATH_PROTOCOL_GUID {0x09576e91,0x6d3f,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

#define EFI_VMBUS_CHANNEL_DEVICE_PATH_GUID {0x9b17e5a2, 0x0891, 0x42dd, {0xb6, 0x53, 0x80, 0xb5, 0xc2, 0x28, 0x09, 0xba}}


#define HV_SCSI_GUID {0xba6163d9, 0x04a1, 0x4d29, {0xb6, 0x05, 0x72, 0xe2, 0xff, 0xb1, 0xdc, 0x7f}}

static struct {
    struct {
        u8 type;
        u8 subtype;
        u16 length;
        u32 _HID;
        u32 _UID;
        u32 _CID;
        char _HIDSTR_UIDSTR_CIDSTR[0x8];
    } vmbus_node;
    
    struct {
        u8 type;
        u8 subtype;
        u16 length;
        struct efi_guid vendor_guid;
        struct efi_guid device_type_guid; // @note: Kinda guessing these names.
        struct efi_guid device_id_guid;   // @note: Kinda guessing these names.
    } vendor_node;
    
    struct{
        u8 type;
        u8 subtype;
        u16 length;
        
        u16 target_id;
        u16 logical_unit_number;
    } scsi_node;
    
    struct{
        u8 type;
        u8 subtype;
        u16 length;
    } device_path_terminator;
    
} g_vmbus_scsi_device_path_protocol = {
    .vmbus_node = {
        .type = 2, // ACPI Device Path
        .subtype = 2, // Expanded ACPI Device Path
        .length = sizeof(g_vmbus_scsi_device_path_protocol.vmbus_node),
        ._HIDSTR_UIDSTR_CIDSTR = "VMBus",
    },
    
    .vendor_node = {
        .type = 1,
        .subtype = 4,
        .length = sizeof(g_vmbus_scsi_device_path_protocol.vendor_node),
        .vendor_guid = EFI_VMBUS_CHANNEL_DEVICE_PATH_GUID,
        .device_type_guid = HV_SCSI_GUID,
        .device_id_guid = {0xa17ff36e, 0x90d5, 0x4e0f, {0x80, 0xa1, 0xf9, 0x86, 0x41, 0x1c, 0x4d, 0x0f}},
    },
    
    .scsi_node = {
        .type = 3,
        .subtype = 2,
        .length = sizeof(g_vmbus_scsi_device_path_protocol.scsi_node),
        .target_id = 0,
        .logical_unit_number = 0,
    },
    .device_path_terminator = {
        .type = 0x7f,
        .subtype = 0xff,
        .length = sizeof(g_vmbus_scsi_device_path_protocol.device_path_terminator),
    },
};


static struct {
    struct {
        u8 type;
        u8 subtype;
        u16 length;
        u32 _HID;
        u32 _UID;
        u32 _CID;
        char _HIDSTR_UIDSTR_CIDSTR[0x8];
    } vmbus_node;
    
    struct {
        u8 type;
        u8 subtype;
        u16 length;
        struct efi_guid vendor_guid;
        struct efi_guid device_type_guid; // @note: Kinda guessing these names.
        struct efi_guid device_id_guid;   // @note: Kinda guessing these names.
    } vendor_node;
    
    struct{
        u8 type;
        u8 subtype;
        u16 length;
        
        u16 target_id;
        u16 logical_unit_number;
    } scsi_node;
    
    struct{
        u8 type;
        u8 subtype;
        u16 length;
        
        u32 partition_number;
        u32 partition_start_low;
        u32 partition_start_high;
        u32 partition_size_low;
        u32 partition_size_high;
        
        u8 partition_signature[16];
        u8 partition_format;
        u8 signature_type;
    } media_node;
    
    struct{
        u8 type;
        u8 subtype;
        u16 length;
    } device_path_terminator;
    
} g_vmbus_partition_device_path_protocol = {
    .vmbus_node = {
        .type = 2, // ACPI Device Path
        .subtype = 2, // Expanded ACPI Device Path
        .length = sizeof(g_vmbus_partition_device_path_protocol.vmbus_node),
        ._HIDSTR_UIDSTR_CIDSTR = "VMBus",
    },
    
    .vendor_node = {
        .type = 1,
        .subtype = 4,
        .length = sizeof(g_vmbus_partition_device_path_protocol.vendor_node),
        .vendor_guid = EFI_VMBUS_CHANNEL_DEVICE_PATH_GUID,
        .device_type_guid = HV_SCSI_GUID,
        .device_id_guid = {0xa17ff36e, 0x90d5, 0x4e0f, {0x80, 0xa1, 0xf9, 0x86, 0x41, 0x1c, 0x4d, 0x0f}},
    },
    
    .scsi_node = {
        .type = 3,
        .subtype = 2,
        .length = sizeof(g_vmbus_partition_device_path_protocol.scsi_node),
        .target_id = 0,
        .logical_unit_number = 0,
    },
    
    .media_node = {
        .type = 4, // media device path
        .subtype = 1, // hard drive
        .length = sizeof(g_vmbus_partition_device_path_protocol.media_node),
        
        .partition_number = 1,
        .partition_start_low = 22,
        .partition_size_low = 0x31fbd,
        
        .partition_format = 2,
        .signature_type   = 2,
    },
    
    .device_path_terminator = {
        .type = 0x7f,
        .subtype = 0xff, 
        .length = sizeof(g_vmbus_partition_device_path_protocol.device_path_terminator),
    },
};

// 
// Mouse: VMBUS\{cfa8b69e-5b4a-4cc0-b98b-8ba1a1f3f95a}\{58f75a6d-d949-4320-99e1-a2a2576d581c}
// 

#define HV_MOUSE_GUID {0xcfa8b69e, 0x5b4a, 0x4cc0, {0xb9, 0x8b, 0x8b, 0xa1, 0xa1, 0xf3, 0xf9, 0x5a}}

static struct {
    struct {
        u8 type;
        u8 subtype;
        u16 length;
        u32 _HID;
        u32 _UID;
        u32 _CID;
        char _HIDSTR_UIDSTR_CIDSTR[0x8];
    } vmbus_node;
    
    struct {
        u8 type;
        u8 subtype;
        u16 length;
        struct efi_guid vendor_guid;
        struct efi_guid device_type_guid; // @note: Kinda guessing these names.
        struct efi_guid device_id_guid;   // @note: Kinda guessing these names.
    } vendor_node;
    
    struct{
        u8 type;
        u8 subtype;
        u16 length;
    } device_path_terminator;
    
} g_vmbus_mouse_device_path_protocol = {
    .vmbus_node = {
        .type = 2, // ACPI Device Path
        .subtype = 2, // Expanded ACPI Device Path
        .length = sizeof(g_vmbus_mouse_device_path_protocol.vmbus_node),
        ._HIDSTR_UIDSTR_CIDSTR = "VMBus",
    },
    
    .vendor_node = {
        .type = 1,
        .subtype = 4,
        .length = sizeof(g_vmbus_mouse_device_path_protocol.vendor_node),
        .vendor_guid = EFI_VMBUS_CHANNEL_DEVICE_PATH_GUID,
        .device_type_guid = HV_MOUSE_GUID,
        .device_id_guid = {0x58f75a6d, 0xd949, 0x4320, {0x99, 0xe1, 0xa2, 0xa2, 0x57, 0x6d, 0x58, 0x1c}},
    },
    
    .device_path_terminator = {
        .type = 0x7f,
        .subtype = 0xff, 
        .length = sizeof(g_vmbus_mouse_device_path_protocol.device_path_terminator),
    },
};


// 
// Sythetic Video: VMBUS\{DA0A7802-E377-4aac-8E77-0558EB1073F8}\{5620e0c7-8062-4dce-aeb7520c7ef76171}
// 

#define HV_SYNVID_GUID {0xda0a7802, 0xe377, 0x4aac, {0x8e, 0x77, 0x05, 0x58, 0xeb, 0x10, 0x73, 0xf8}}

static struct {
    struct {
        u8 type;
        u8 subtype;
        u16 length;
        u32 _HID;
        u32 _UID;
        u32 _CID;
        char _HIDSTR_UIDSTR_CIDSTR[0x8];
    } vmbus_node;
    
    struct {
        u8 type;
        u8 subtype;
        u16 length;
        struct efi_guid vendor_guid;
        struct efi_guid device_type_guid; // @note: Kinda guessing these names.
        struct efi_guid device_id_guid;   // @note: Kinda guessing these names.
    } vendor_node;
    
    struct{
        u8 type;
        u8 subtype;
        u16 length;
    } device_path_terminator;
    
} g_vmbus_synvid_device_path_protocol = {
    .vmbus_node = {
        .type = 2, // ACPI Device Path
        .subtype = 2, // Expanded ACPI Device Path
        .length = sizeof(g_vmbus_synvid_device_path_protocol.vmbus_node),
        ._HIDSTR_UIDSTR_CIDSTR = "VMBus",
    },
    
    .vendor_node = {
        .type = 1,
        .subtype = 4,
        .length = sizeof(g_vmbus_synvid_device_path_protocol.vendor_node),
        .vendor_guid = EFI_VMBUS_CHANNEL_DEVICE_PATH_GUID,
        .device_type_guid = HV_SYNVID_GUID,
        .device_id_guid = {0x5620e0c7, 0x8062, 0x4dce, {0xae, 0xb7, 0x52, 0x0c, 0x7e, 0xf7, 0x61, 0x71}},
    },
    
    .device_path_terminator = {
        .type = 0x7f,
        .subtype = 0xff, 
        .length = sizeof(g_vmbus_synvid_device_path_protocol.device_path_terminator),
    },
};

#define EFI_VMBUS_PROTOCOL_GUID {0x59e6efc9, 0x9695, 0x470a, {0x9d, 0x87, 0x02, 0x61, 0xd8, 0x45, 0x1d, 0xd8}}

struct efi_vmbus_protocol{
    void *vmbus_1;
    void *vmbus_2;
    void *vmbus_3;
    void *vmbus_4;
    void *vmbus_5;
    void *vmbus_6;
    u32 enabled;
};

efi_status efi_vmbus_1(void){ log("unimplemented efi_vmbus_1"); bios_crash(); return 0; }
efi_status efi_vmbus_2(void){ log("unimplemented efi_vmbus_2"); bios_crash(); return 0; }
efi_status efi_vmbus_3(void){ log("unimplemented efi_vmbus_3"); bios_crash(); return 0; }
efi_status efi_vmbus_4(void){ log("unimplemented efi_vmbus_4"); bios_crash(); return 0; }
efi_status efi_vmbus_5(void){ log("unimplemented efi_vmbus_5"); bios_crash(); return 0; }
efi_status efi_vmbus_6(void){ log("unimplemented efi_vmbus_6"); bios_crash(); return 0; }


struct efi_vmbus_protocol g_vmbus_mouse_protocol = {
    .vmbus_1 = efi_vmbus_1,
    .vmbus_2 = efi_vmbus_2,
    .vmbus_3 = efi_vmbus_3,
    .vmbus_4 = efi_vmbus_4,
    .vmbus_5 = efi_vmbus_5,
    .vmbus_6 = efi_vmbus_6,
    .enabled = 1,
};

struct efi_vmbus_protocol g_vmbus_synvid_protocol = {
    .vmbus_1 = efi_vmbus_1,
    .vmbus_2 = efi_vmbus_2,
    .vmbus_3 = efi_vmbus_3,
    .vmbus_4 = efi_vmbus_4,
    .vmbus_5 = efi_vmbus_5,
    .vmbus_6 = efi_vmbus_6,
    .enabled = 1,
};


//_____________________________________________________________________________________________________________________
// Efi Graphics

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID {0x9042a9de,0x23dc,0x4a38,{0x96,0xfb,0x7a,0xde,0xd0,0x80,0x51,0x6a}}

struct efi_graphics_output_protocol{
    void *query_mode;
    void *set_mode;
    void *blt;
    struct efi_graphics_output_protocol_mode *mode;
};

efi_status efi_graphics_output__query_mode(void){log("unimplemented efi_graphics_output__query_mode"); bios_crash(); return 0;}
efi_status efi_graphics_output__set_mode(void){log("unimplemented efi_graphics_output__set_mode"); bios_crash(); return 0;}
efi_status efi_graphics_output__blt(void){log("unimplemented efi_graphics_output__blt"); bios_crash(); return 0;}

struct efi_graphics_output_protocol_mode{
    u32 max_mode;
    u32 mode;
    struct efi_graphics_output_mode_information *info;
    u64 size_of_info;
    u64 frame_buffer_base;
    u64 frame_buffer_size;
};

struct efi_graphics_output_mode_information{
    u32 version;
    u32 horizontal_resolution;
    u32 vertical_resolution;
    int pixel_format;
    struct efi_pixel_bitmask{
        u32 red_mask;
        u32 green_mask;
        u32 blue_mask;
        u32 reserved_mask;
    } pixel_information;
    u32 pixels_per_scanline;
};

struct efi_graphics_output_mode_information g_efi_graphics_output_mode_information = {
    .horizontal_resolution = 0x400,
    .vertical_resolution   = 0x300,
    .pixel_format          = /*BlueGreenRedReserved8BitPerColor*/1,
    .pixels_per_scanline   = 0x400,
};

struct efi_graphics_output_protocol_mode g_efi_graphics_output_protocol_mode = {
    .max_mode   = 1,
    .info       = &g_efi_graphics_output_mode_information,
    .size_of_info = sizeof(g_efi_graphics_output_mode_information),
    .frame_buffer_base = 0xf8000000,
    .frame_buffer_size =   0x800000,
};

struct efi_graphics_output_protocol g_efi_graphics_output_protocol = {
    .query_mode = efi_graphics_output__query_mode,
    .set_mode   = efi_graphics_output__set_mode,
    .blt        = efi_graphics_output__blt,
    .mode = &g_efi_graphics_output_protocol_mode,
};


//_____________________________________________________________________________________________________________________
// EFI tables

struct efi_table_header{
    u64 signature;
    u32 revision;
    u32 header_size;
    u32 crc32;
    u32 reserved;
};

struct efi_boot_services{
    struct efi_table_header header;
    
    u64 (*raise_tpl)(u64 new_tpl);
    void *restore_tpl;
    
    void *allocate_pages;
    void *free_pages;
    void *get_memory_map;
    void *allocate_pool;
    void *free_pool;
    
    void *create_event;
    void *set_timer;
    efi_status (*wait_for_event)(size_t number_of_events, struct efi_event *event, size_t *index);
    void *signal_event;
    void *close_event;
    void *check_event;
    
    void *install_protocol_interface;
    void *reinstall_protocol_interface;
    void *uninstall_protocol_interface;
    efi_status (*handle_protocol)(struct efi_handle handle, struct efi_guid *protocol_guid, void **out_interface);
    void *reserved;
    void *register_protocol_notify;
    void *locate_handle;
    void *locate_device_path;
    void *install_configuration_table;
    
    void *load_image;
    void *start_image;
    void *exit;
    void *unload_image;
    void *exit_boot_services;
    
    void *get_next_monotonic_count;
    void *stall;
    void *set_watchdog_timer;
    
    void *connect_controller;
    void *disconnect_controller;
    
    void *open_protocol;
    void *close_protocol;
    void *open_protocol_information;
    
    void *protocols_per_handle;
    void *locate_handle_buffer;
    void *locate_protocol;
    void *install_multiple_protocol_interfaces;
    void *uninstall_multiple_protocol_interfaces;
    
    void *calculate_crc32;
    void *copy_mem;
    void *set_mem;
    
    void *create_event_ex;
};

struct efi_system_table{
    struct efi_table_header header;
    
    s16 *FirmwareVendor;
    u32 FirmwareRevision;
    
    struct efi_handle console_in_handle;
    struct efi_simple_text_input_protocol *console_in;
    
    struct efi_handle console_out_handle;
    struct efi_simple_text_output_protocol *console_out;
    
    
    struct efi_handle console_error_handle;
    struct efi_simple_text_output_protocol *standard_error;
    
    struct efi_runtime_services *runtime_services;
    struct efi_boot_services    *boot_services;
    
    struct{
        size_t size;
        struct efi_configuration_table_entry{
            struct efi_guid guid;
            void *table;
        }*data;
    } configuration_table;
};

struct efi_runtime_services{
    struct efi_table_header header;
    
    void *get_time;
    void *set_time;
    void *get_wakeup_time;
    void *set_wakeup_time;
    
    void *set_virtual_address_map;
    void *convert_pointer;
    
    void *get_variable;
    void *get_next_variable;
    void *set_variable;
    
    void *get_next_high_mono_count;
    void *reset_system;
    
    void *update_capsule;
    void *query_capsule_capabilities;
    
    void *query_variable_info;
};

struct efi_boot_services g_boot_services;
struct efi_runtime_services g_runtime_services;
struct efi_system_table  g_system_table;

//_____________________________________________________________________________________________________________________
// Efi Loaded Image

#define EFI_LOADED_IMAGE_PROTOCOL_GUID {0x5B1B31A1,0x9562,0x11d2,{0x8E,0x3F,0x00,0xA0,0xC9,0x69,0x72,0x3B}}

struct efi_loaded_image_protocol{
    u32 revision;
    struct efi_handle parent_handle;
    struct efi_system_table *system_table;
    struct efi_handle device_handle;
    void *file_path;
    void *reserved;
    u32 load_options_size;
    void *load_options;
    
    void *image_base;
    u64 image_size;
    enum efi_memory_type image_code_type;
    enum efi_memory_type image_data_type;
    void *unload;
};

//_____________________________________________________________________________________________________________________
// Efi Boot Services

u64 efi_raise_tpl(u64 new_tpl){ 
    u64 old_tpl = __readcr8();
    __writecr8(new_tpl);
    return old_tpl;
}

void efi_restore_tpl(u64 old_tpl){ 
    __writecr8(old_tpl); 
}

struct {
    struct efi_memory_descriptor{
        enum efi_memory_type{
            
            // Not usable
            EfiReservedMemoryType = 0,
            
            // UEFI application
            EfiLoaderCode         = 1,
            EfiLoaderData         = 2,
            
            // UEFI Boot Service Driver
            EfiBootServiceCode    = 3,
            EfiBootServiceData    = 4,
            
            // UEFI Runtime Service Driver
            EfiRuntimeServiceCode = 5,
            EfiRuntimeServiceData = 6,
            
            // Free memory
            EfiConventionalMemory = 7,
            
            // Firmware Memory (Hold ACPI tables)
            EfiACPIReclaimMemory = 9,
            EfiACPIMemoryNVS     = 10,
        } memory_type;
        
        u64 physical_start;
        u64 virtual_start;
        u64 number_of_pages;
        u64 attributes;
    } data[0x100];
    u64 size;
} g_efi_memory_map;


// allocation_type:
// 0 - AllocateAnyPages
//     The address is ignored on input.
//     
// 1 - AllocateMaxAddress
//     The returned allocation has to be less then the specified address.
// 
// 2 - AllocateAddress
//     The requested pages have to be exactly at the specified address.
//     
efi_status efi_allocate_pages(int allocation_type, enum efi_memory_type memory_type, u64 number_of_pages, u64 *in_out_physical_address){
    
    if(g_system_table.boot_services == null){
        log("efi_allocate_pages after efi_exit_boot_services\n");
        bios_crash();
    }
    
    log("type: %d memory_type: %d [%p, %p)", allocation_type, memory_type, *in_out_physical_address, *in_out_physical_address + number_of_pages * 0x1000);

    u64 requested_physical_address = *in_out_physical_address;
    
    // 
    // @note: This routine specifies physical addresses, but the memory map is liniear, so that does not matter.
    //        @cleanup: actually look at the mapping and how this is all intended to work...
    // 
    
    switch(allocation_type){
        case /*AllocateAnyPages*/0:{
            
            struct efi_memory_descriptor *descriptor = null;
            
            // @note: lets ignore the first allocation so we don't allocate 0.
            for(u32 index = 1; index < g_efi_memory_map.size; index++){
                descriptor = &g_efi_memory_map.data[index];
                
                // 
                // Find the range which fits the range.
                // 
                if(descriptor->memory_type == EfiConventionalMemory && descriptor->number_of_pages >= number_of_pages){
                    break;
                }
            }
            
            if(!descriptor){
                log("efi_allocate_pages could not find a range which fit the size.");
                bios_crash();
            }
            
            u64 descriptor_index = (descriptor - g_efi_memory_map.data);
            
            if(g_efi_memory_map.size + 1 > array_count(g_efi_memory_map.data)){
                log("efi_allocate_pages ran out of entries for allocation_type 0.");
                bios_crash();
            }
            
            // 
            // move all latter entries up, including the descriptor.
            // 
            for(u64 index = g_efi_memory_map.size - 1; index >= descriptor_index; index--){
                g_efi_memory_map.data[index + 1] = g_efi_memory_map.data[index];
            }
            g_efi_memory_map.size += 1;
            
            *in_out_physical_address = descriptor->physical_start;
            
#define efi_memory_type_to_attributes(memory_type) (0xf | ((memory_type == EfiRuntimeServiceCode || memory_type == EfiRuntimeServiceData) ? 0x8000000000000000 : 0))
            
            descriptor->memory_type = memory_type;
            descriptor->number_of_pages = number_of_pages;
            descriptor->attributes = efi_memory_type_to_attributes(memory_type);
            
            descriptor += 1;
            descriptor->number_of_pages -= number_of_pages;
            descriptor->physical_start  += number_of_pages * 0x1000;
            
        }break;
        
        case /*AllocateAddress*/2:{
            struct efi_memory_descriptor *descriptor = null;
            
            for(u32 index = 0; index < g_efi_memory_map.size; index++){
                descriptor = &g_efi_memory_map.data[index];
                
                // 
                // Find the range which contains the 'requested_physical_address'
                // 
                if(descriptor->physical_start <= requested_physical_address && requested_physical_address < descriptor->physical_start + descriptor->number_of_pages * 0x1000){
                    break;
                }
            }
            
            if(!descriptor){
                log("efi_allocate_pages could not find descriptor.");
                return -1; // @cleanup: error code.
            }
            
            u64 page_offset_in_descriptor = (requested_physical_address - descriptor->physical_start)/0x1000;
            
            if(descriptor->number_of_pages - page_offset_in_descriptor < number_of_pages){
                
                for(u32 index = 0; index < g_efi_memory_map.size; index++){
                    struct efi_memory_descriptor *d = &g_efi_memory_map.data[index];
                    log("%d memory_type %d [%p -> %p)", index, d->memory_type, d->physical_start, d->physical_start + d->number_of_pages * 0x1000);
                }
                
                
                log("efi_allocate_pages descriptor too small.");    
                return -1;
            }
            
            if(descriptor->memory_type == memory_type){
                log("efi_allocate_pages correct memory type already.");
                return 0;
            }
            
            if(descriptor->memory_type != EfiConventionalMemory && memory_type != EfiConventionalMemory){
                log("allocating non-free memory.");
                return EFI_NOT_FOUND;
            }
            
            // 
            // Cases for the splitting: 
            // 
            //   [----parent range----]
            //      [child range]
            //      
            //   [----parent range----]
            //   [child range]
            //   
            //   [----parent range----]
            //            [child range]
            //
            //   [----parent range----]
            //   [----child range ----]
            // 
            
            if(page_offset_in_descriptor == 0 && descriptor->number_of_pages == number_of_pages){
                log("efi_allocate_pages correct size already.");
                
                descriptor->memory_type = memory_type;
                descriptor->attributes  = efi_memory_type_to_attributes(memory_type);
                break;
            }
            
            int new_ranges_needed = (page_offset_in_descriptor != 0) + (page_offset_in_descriptor + number_of_pages != descriptor->number_of_pages);
            
            if(g_efi_memory_map.size + new_ranges_needed > array_count(g_efi_memory_map.data)){
                log("efi_allocate_pages ran out of entries.");
                bios_crash();
            }
            g_efi_memory_map.size += new_ranges_needed;
            
            u64 descriptor_index = (descriptor - g_efi_memory_map.data);
            
            // 
            // move all latter entries up.
            // 
            for(u64 index = g_efi_memory_map.size - 1; index > descriptor_index; index--){
                g_efi_memory_map.data[index + new_ranges_needed] = g_efi_memory_map.data[index];
            }
            
            if(page_offset_in_descriptor != 0){
                // move the original range up by one.
                
                struct efi_memory_descriptor *prefix = &g_efi_memory_map.data[descriptor_index];
                
                g_efi_memory_map.data[descriptor_index + 1] = g_efi_memory_map.data[descriptor_index];
                descriptor_index += 1;
                descriptor += 1;
                
                prefix->number_of_pages = page_offset_in_descriptor; // everything else stays the same
                
                // advance the descriptor by the consumed pages.
                descriptor->number_of_pages -= page_offset_in_descriptor;
                descriptor->physical_start  += page_offset_in_descriptor * 0x1000;
            }
            
            if(descriptor->number_of_pages != number_of_pages){
                struct efi_memory_descriptor *postfix = &g_efi_memory_map.data[descriptor_index + 1];
                *postfix = *descriptor;
                
                postfix->number_of_pages -= number_of_pages;
                postfix->physical_start  += number_of_pages * 0x1000;
                
                descriptor->number_of_pages = number_of_pages;
            }
            
            descriptor->memory_type = memory_type;
            descriptor->attributes  = efi_memory_type_to_attributes(memory_type);
        }break;
        
        default:{
            log("efi_allocate_pages allocation_type %d memory_type %d number of pages %llu physical_address %p", allocation_type, memory_type, number_of_pages, *in_out_physical_address);
            
            bios_crash();
        }break;
    }
    
    // 
    // Merge adjacent ranges of the same type.
    // This whole function is piggy and slow, but who cares for now.
    // 
    
    u64 out_descriptor_index = 0;
    for(u64 descriptor_index = 1; descriptor_index < g_efi_memory_map.size; descriptor_index++){
        struct efi_memory_descriptor *out = &g_efi_memory_map.data[out_descriptor_index];
        struct efi_memory_descriptor *descriptor = &g_efi_memory_map.data[descriptor_index];
        
        // log("%d (%d) %d (%d)", out_descriptor_index, out->memory_type, descriptor_index, descriptor->memory_type);
        
        if(out->memory_type == descriptor->memory_type){
            out->number_of_pages += descriptor->number_of_pages;
        }else{
            out_descriptor_index += 1;
            if(out_descriptor_index != descriptor_index) *(out + 1) = *descriptor;
        }
    }
    g_efi_memory_map.size = out_descriptor_index + 1;
    
#if 1
    for(u64 descriptor_index = 0; descriptor_index < g_efi_memory_map.size - 1; descriptor_index++){
        struct efi_memory_descriptor *d1 = &g_efi_memory_map.data[descriptor_index];
        struct efi_memory_descriptor *d2 = &g_efi_memory_map.data[descriptor_index + 1];
        
        if(d1->physical_start + d1->number_of_pages * 0x1000 != d2->physical_start){
            log("Corrupt memory ranges. %p + %p != %p", d1->physical_start, d1->number_of_pages * 0x1000, d2->physical_start);
            bios_crash();
        }
    }
#endif
    
    return 0;
}

efi_status efi_free_pages(u64 physical_address, u64 number_of_pages){
    
    // "Allocate" the range as 'free'.
    return efi_allocate_pages(/**/2, EfiConventionalMemory, number_of_pages, &physical_address);
}

efi_status efi_get_memory_map(u64 *in_out_memory_map_size, struct efi_memory_descriptor *memory_map, u64 *map_key, u64 *descriptor_size, u32 *descriptor_version){
    
    // 
    // The memory map generally contains the following types of entries:
    //    1) EfiReservedMemoryType = 0
    //       The memory is unusable.
    //    2) EfiLoaderCode/EfiLoaderData = 1, 2
    //       The memory was allocated by the efi application (see efi_allocate_pages above).
    //    3) EfiBootServiceCode/EfiBootServiceData = 3, 4
    //       The memory was allocated by an efi boot service driver.
    //    4) EfiRuntimeServiceCode/EfiRuntimeServiceData = 5, 6
    //       The memory was allocated by an efi runtime service driver.
    //    5) EfiConventionalMemory = 7
    //       The memory is currently not allocated.
    //    6) EfiACPIReclaimMemory/EfiACPIMemoryNVS = 9, 10
    //       The memory is allocated by the firmware (for ACPI tables).
    // 
    
    if(map_key)            *map_key = 0x1337;
    if(descriptor_size)    *descriptor_size = sizeof(struct efi_memory_descriptor);
    if(descriptor_version) *descriptor_version = 1;
    
    int success = 0;
    if(*in_out_memory_map_size >= sizeof(struct efi_memory_descriptor) * g_efi_memory_map.size){
        __movsb((u8 *)memory_map, (u8 *)g_efi_memory_map.data, g_efi_memory_map.size * sizeof(struct efi_memory_descriptor));
        success = 1;
    }
    
    *in_out_memory_map_size = sizeof(struct efi_memory_descriptor) * g_efi_memory_map.size;
    return success ? 0 : EFI_BUFFER_TOO_SMALL;
}

efi_status efi_allocate_pool(void){ log("unimplemented allocate_pool"); bios_crash(); return 0; }
efi_status efi_free_pool(void){ log("unimplemented free_pool"); bios_crash(); return 0; }
efi_status efi_create_event(void){ log("unimplemented create_event"); bios_crash(); return 0; }
efi_status efi_set_timer(void){ log("unimplemented set_timer"); bios_crash(); return 0; }
efi_status efi_wait_for_event(void){ log("unimplemented wait_for_event"); bios_crash(); return 0; }
efi_status efi_signal_event(void){ log("unimplemented signal_event"); bios_crash(); return 0; }
efi_status efi_close_event(void){ log("unimplemented close_event"); bios_crash(); return 0; }
efi_status efi_check_event(void){ log("unimplemented check_event"); bios_crash(); return 0; }
efi_status efi_install_protocol_interface(void){ log("unimplemented install_protocol_interface"); bios_crash(); return 0; }
efi_status efi_reinstall_protocol_interface(void){ log("unimplemented reinstall_protocol_interface"); bios_crash(); return 0; }
efi_status efi_uninstall_protocol_interface(void){ log("unimplemented uninstall_protocol_interface"); bios_crash(); return 0; }

efi_status efi_reserved(void){ log("unimplemented reserved"); bios_crash(); return 0; }
efi_status efi_register_protocol_notify(void){ log("unimplemented register_protocol_notify"); bios_crash(); return 0; }

efi_status efi_locate_handle(u32 search_type, struct efi_guid *protocol_guid, void *search_key, u64 *in_out_buffer_size, struct efi_handle *buffer){
    log("efi_locate_handle search_type %d, protocol_guid %p, search_key %p, buffer_size 0x%llx, buffer %p", search_type, protocol_guid, search_key, *in_out_buffer_size, buffer);
    u64 buffer_size = *in_out_buffer_size;
    
    
    if(search_type == /*ByProtocol*/2){
        log("   -> guid {%.8x-%.4x-%.4x-%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x}",
                protocol_guid->data1, protocol_guid->data2, protocol_guid->data3, 
                protocol_guid->data4[0], protocol_guid->data4[1], protocol_guid->data4[2], protocol_guid->data4[3],
                protocol_guid->data4[4], protocol_guid->data4[5], protocol_guid->data4[6], protocol_guid->data4[7]);
        
        // https://learn.microsoft.com/en-us/windows-hardware/test/hlk/testref/trusted-execution-environment-efi-protocol
        // 
#define EFI_TCG2_PROTOCOL_GUID {0x607f766c, 0x7455, 0x42be, 0x93, 0x0b, 0xe4, 0xd7, 0x6d, 0xb2, 0x72, 0x0f}
#define EFI_TCG_PROTOCOL_GUID  {0xf541796d, 0xa62e, 0x4954, 0xa7, 0x75, 0x95, 0x84, 0xf6, 0x1b, 0x9c, 0xdd}
        if(guid_match(protocol_guid, &(struct efi_guid)EFI_TCG2_PROTOCOL_GUID) || guid_match(protocol_guid, &(struct efi_guid)EFI_TCG_PROTOCOL_GUID)){
            return EFI_NOT_FOUND;
        }
        
#define MS_RESET_REASON_PROTOCOL_GUID {0x6147e8b4, 0xf382, 0x4982, {0x93, 0x8e, 0x2e, 0xca, 0x5e, 0x52, 0xf6, 0x5b}}
        if(guid_match(protocol_guid, &(struct efi_guid)MS_RESET_REASON_PROTOCOL_GUID)){
            return EFI_NOT_FOUND;
        }
        
#define EFI_BOOT_MODE_MGMT_PROTOCOL_GUID {0xbe464946, 0x9787, 0x4feb, {0xbd, 0x71, 0x14, 0xc1, 0xc5, 0x2d, 0x69, 0xd1}}
        if(guid_match(protocol_guid, &(struct efi_guid)EFI_BOOT_MODE_MGMT_PROTOCOL_GUID)){
            return EFI_NOT_FOUND;
        }
        
#define EFI_RNG_PROTOCOL_GUID {0x3152bca5, 0xeade, 0x433d, {0x86, 0x2e, 0xc0, 0x1c, 0xdc, 0x29, 0x1f, 0x44}}
        if(guid_match(protocol_guid, &(struct efi_guid)EFI_RNG_PROTOCOL_GUID)){
            return EFI_NOT_FOUND;
        }
#define EFI_ADAPTER_INFORMATION_PROTOCOL_GUID {0xE5DD1403, 0xD622, 0xC24E, {0x84, 0x88, 0xC7, 0x1B, 0x17, 0xF5, 0xE8, 0x02 }}
        if(guid_match(protocol_guid, &(struct efi_guid)EFI_ADAPTER_INFORMATION_PROTOCOL_GUID)){
            return EFI_NOT_FOUND;
        }
        
#define MS_DEBUGGING_DEVICE {0x2da15ac7, 0x4909, 0x4c4c, {0xb8, 0xc3, 0xa7, 0x42, 0x19, 0x5e, 0xa4, 0x6e}}
        if(guid_match(protocol_guid, &(struct efi_guid)MS_DEBUGGING_DEVICE)){
            return EFI_NOT_FOUND;
        }
        
        if(guid_match(protocol_guid, &(struct efi_guid)EFI_VMBUS_PROTOCOL_GUID)){
            *in_out_buffer_size = 0x10;
            if(buffer_size < 0x10) return EFI_BUFFER_TOO_SMALL;
            
            buffer[0] = (struct efi_handle){&g_vmbus_mouse_protocol};
            buffer[1] = (struct efi_handle){&g_vmbus_synvid_protocol};
            return 0;
        }
        
        if(guid_match(protocol_guid, &(struct efi_guid)EFI_BLOCK_IO_PROTOCOL_GUID)){
            *in_out_buffer_size = 0x10;
            if(buffer_size < 0x10) return EFI_BUFFER_TOO_SMALL;
            
            buffer[0].value = (void *)0xb101;
            buffer[1].value = (void *)0xb102;
            return 0;
        }
        
        if(guid_match(protocol_guid, &(struct efi_guid)EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID)){
            *in_out_buffer_size = 8;
            if(buffer_size < 8) return EFI_BUFFER_TOO_SMALL;
            
            buffer[0].value = &g_efi_graphics_output_protocol;
            return 0;
        }
        
    }
    
    bios_crash();
    return 0;
}

efi_status efi_locate_device_path(void){ log("unimplemented locate_device_path"); bios_crash(); return 0; }
efi_status efi_install_configuration_table(void){ log("unimplemented install_configuration_table"); bios_crash(); return 0; }
efi_status efi_load_image(void){ log("unimplemented load_image"); bios_crash(); return 0; }
efi_status efi_start_image(void){ log("unimplemented start_image"); bios_crash(); return 0; }
efi_status efi_exit(void){ log("unimplemented exit"); bios_crash(); return 0; }
efi_status efi_unload_image(void){ log("unimplemented unload_image"); bios_crash(); return 0; }

efi_status efi_exit_boot_services(struct efi_handle image_handle, u64 map_key){ 
    
    log("Exiting boot services!\n");
    
    // "On success, several fields of the EFI System Table should be set to NULL."
    g_system_table.console_in_handle.value = 0;
    g_system_table.console_in = null;
    g_system_table.console_out_handle.value = 0;
    g_system_table.console_out = null;
    g_system_table.console_error_handle.value = 0;
    g_system_table.standard_error = null;
    g_system_table.boot_services = null;
    
    g_system_table.runtime_services = &g_runtime_services;
    
    // In theory we have to update the CRC32.
    
    return 0;
}

efi_status efi_get_next_monotonic_count(void){ log("unimplemented get_next_monotonic_count"); bios_crash(); return 0; }

efi_status efi_stall(u64 microseconds){ 
    // 
    // @cleanup: This is quite the hack this is probably used to time 'rdtsc', 
    //           our implementation uses the amount of rdtsc calls to estimate 
    //           the time. Hence, we call __rdtsc() in a loop until it reaches 
    //           the desired microseconds.
    // 
    
    u64 start = __rdtsc();  // 4 GHz = 4 * 10^9 cycles/s -> 4 GHz = 4 * 10^3 cycles / us
    while((__rdtsc() - start) / 4000 < microseconds);
    
    return 0; 
}

efi_status efi_set_watchdog_timer(u64 timeout, u64 watchdogcode, u64 datasize, u16 *data){ 
    // Let's ignore this. We don't want the guest to reset anyway, they probably just disable it anyway.
    log("efi_set_watchdog_timer 0x%llx, 0x%llx, 0x%llx, %p", timeout, watchdogcode, datasize, data);
    return 0;
}

efi_status efi_connect_controller(void){ log("unimplemented connect_controller"); bios_crash(); return 0; }
efi_status efi_disconnect_controller(void){ log("unimplemented disconnect_controller"); bios_crash(); return 0; }


efi_status efi_open_protocol(struct efi_handle handle, struct efi_guid *protocol_guid, void **out_interface, struct efi_handle agent_handle, struct efi_handle controller_handle, u32 attributes){ 
    
    log("entering efi_open_protocol %p {%.8x-%.4x-%.4x-%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x} agent %p, controller %p, attributes 0x%x", handle.value, 
            protocol_guid->data1, protocol_guid->data2, protocol_guid->data3, 
            protocol_guid->data4[0], protocol_guid->data4[1], protocol_guid->data4[2], protocol_guid->data4[3],
            protocol_guid->data4[4], protocol_guid->data4[5], protocol_guid->data4[6], protocol_guid->data4[7], 
            agent_handle.value, controller_handle.value, attributes);
    
    void *protocol = null;
    
    if(guid_match(protocol_guid, &(struct efi_guid)EFI_VMBUS_PROTOCOL_GUID)){
        protocol = handle.value;
    }
    
    if(guid_match(protocol_guid, &(struct efi_guid)EFI_LOADED_IMAGE_PROTOCOL_GUID)){
        protocol = handle.value;
    }
    
    if(guid_match(protocol_guid, &(struct efi_guid)EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID)){
        if(out_interface) protocol = &g_simple_text_input_ex_protocol;
    }
    
    if(guid_match(protocol_guid, &(struct efi_guid)EFI_BLOCK_IO_PROTOCOL_GUID)){
        if(handle.value == (void *)0xb101) protocol = &g_logical_block_io_protocol;
        if(handle.value == (void *)0xb102) protocol = &g_partition_io_protocol;
    }
    
    if(guid_match(protocol_guid, &(struct efi_guid)EFI_DEVICE_PATH_PROTOCOL_GUID)){
        if(handle.value == (void *)0xb101) protocol = &g_vmbus_scsi_device_path_protocol;
        if(handle.value == (void *)0xb102) protocol = &g_vmbus_partition_device_path_protocol;
        if(handle.value == &g_efi_graphics_output_protocol) protocol = &g_vmbus_synvid_device_path_protocol;
        if(handle.value == &g_vmbus_mouse_protocol) protocol = &g_vmbus_mouse_device_path_protocol;
        if(handle.value == &g_vmbus_synvid_protocol) protocol = &g_vmbus_synvid_device_path_protocol;
    }
    
    if(guid_match(protocol_guid, &(struct efi_guid)EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID)){
        if(handle.value == &g_efi_graphics_output_protocol) protocol = &g_efi_graphics_output_protocol;
    }
    
#define EFI_STORAGE_SECURITY_COMMAND_PROTOCOL_GUID {0xc88b0b6d, 0x0dfc, 0x49a7,{0x9c, 0xb4, 0x49, 0x7, 0x4b, 0x4c, 0x3a, 0x78}}
    if(guid_match(protocol_guid, &(struct efi_guid)EFI_STORAGE_SECURITY_COMMAND_PROTOCOL_GUID)){
        return EFI_UNSUPPORTED;
    }
    
#define EFI_EDID_ACTIVE_PROTOCOL_GUID {0xbd8c1056,0x9f36,0x44ec,{0x92,0xa8,0xa6,0x33,0x7f,0x81,0x79,0x86}}
    if(guid_match(protocol_guid, &(struct efi_guid)EFI_EDID_ACTIVE_PROTOCOL_GUID)){
        return EFI_UNSUPPORTED;
    }
    
    if(protocol){
        *out_interface = protocol;
        return 0;
    }
    
    bios_crash();
    return 0;
}


efi_status efi_handle_protocol(struct efi_handle handle, struct efi_guid *protocol_guid, void **out_interface){
    return efi_open_protocol(handle, protocol_guid, out_interface, (struct efi_handle){0}, (struct efi_handle){0}, /*EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL*/1);
}


efi_status efi_close_protocol(struct efi_handle handle, struct efi_guid *guid, struct efi_handle agent, struct efi_handle controller){
    log("stubbed close_protocol %p", handle.value);
    return 0; 
}

efi_status efi_open_protocol_information(void){ log("unimplemented open_protocol_information"); bios_crash(); return 0; }
efi_status efi_protocols_per_handle(void){ log("unimplemented protocols_per_handle"); bios_crash(); return 0; }
efi_status efi_locate_handle_buffer(void){ log("unimplemented locate_handle_buffer"); bios_crash(); return 0; }

efi_status efi_locate_protocol(struct efi_guid *guid, void *registration, void **interface){ 
    
    log("unimplemented locate_protocol " PRINT_EFI_GUID_FORMAT, PRINT_EFI_GUID_MEMBERS(*guid)); 
    
    return EFI_NOT_FOUND; 
}


efi_status efi_install_multiple_protocol_interfaces(void){ log("unimplemented install_multiple_protocol_interfaces"); bios_crash(); return 0; }
efi_status efi_uninstall_multiple_protocol_interfaces(void){ log("unimplemented uninstall_multiple_protocol_interfaces"); bios_crash(); return 0; }
efi_status efi_calculate_crc32(void){ log("unimplemented calculate_crc32"); bios_crash(); return 0; }
efi_status efi_copy_mem(void){ log("unimplemented copy_mem"); bios_crash(); return 0; }
efi_status efi_set_mem(void){ log("unimplemented set_mem"); bios_crash(); return 0; }
efi_status efi_create_event_ex(void){ log("unimplemented efi_create_event_ex"); bios_crash(); return 0; }

//_____________________________________________________________________________________________________________________
// "Boottime" runtime services

struct efi_time{
    u16 year;
    u8 month;
    u8 day;
    u8 hour;
    u8 minute;
    u8 second;
    u8 pad1;
    u32 nanosecond;
    s16 timezone;
    u8 daylight;
    u8 pad2;
};

struct efi_time_capabilities{
    u32 resolution;
    u32 accuracy;
    u8 sets_to_zero;
};

efi_status efi_get_time(struct efi_time *out_time, struct efi_time_capabilities *capabilities){ 
    
    // 
    // @cleanup: How to handle this ? I feel like this should maybe be the modification date of the .vhdx + something based of __rdtsc()
    // 
    out_time->year = 2023;
    out_time->month = 7;
    out_time->day = 12;
    out_time->hour = 17;
    out_time->minute = 50;
    out_time->second = 40;
    out_time->nanosecond = 0;
    out_time->timezone = 0x7ff; // unspecified timezone
    out_time->daylight = 0;
    
    if(capabilities){
        capabilities->resolution = 1;
        capabilities->accuracy = 0x2faf080;
        capabilities->sets_to_zero = 0;
    }
    
    return 0;
}

efi_status efi_set_time(void){ log("unimplemented set_time"); bios_crash(); return 0; }
efi_status efi_get_wakeup_time(void){ log("unimplemented get_wakeup_time"); bios_crash(); return 0; }
efi_status efi_set_wakeup_time(void){ log("unimplemented set_wakeup_time"); bios_crash(); return 0; }

struct efi_variable{
    struct efi_variable *next;
    
    u32 attributes;
    u16 *variable_name;
    u64 data_size;
    u8 data[];
};

u8 efi_variable_buffer[0x10000]; // Clearly nvram.
u64 efi_variable_buffer_at;

struct {
    struct efi_variable *first;
    struct efi_variable *last;
} g_efi_variable_list;

#define sll_push_back(list, node)           \
if((list).first){                           \
    (list).last = (list).last->next = node; \
}else{                                      \
    (list).first = (list).last = node;      \
}

efi_status efi_convert_pointer(u64 debug_disposition, void **address){
    if((debug_disposition & /*EFI_OPTIONAL_PTR*/1) && *address == 0) return 0;
    
    u64 in_address = (u64)*address;
    
    for(u32 index = 0; index < g_efi_memory_map.size; index++){
        struct efi_memory_descriptor *descriptor = &g_efi_memory_map.data[index];
        
        // @cleanup: attributes?
        if(descriptor->physical_start <= in_address && in_address < descriptor->physical_start + descriptor->number_of_pages * 0x1000){
            *address = (void *)(descriptor->virtual_start + (in_address - descriptor->physical_start));
            return 0;
        }
    }
    
    log("efi_convert_pointer could not find %p", in_address);
    bios_crash();
    
    return EFI_NOT_FOUND;
}

efi_status efi_set_virtual_address_map(u64 memory_map_size, u64 descriptor_size, u32 descriptor_version, struct efi_memory_descriptor *descriptor_base){
    
    log("efi_set_virtual_address_map: memory_map_size 0x%llx, descriptor_size 0x%llx, descriptor_version %d, descriptor_base %p", memory_map_size, descriptor_size, descriptor_version, descriptor_base);
    if(!descriptor_size) descriptor_size = sizeof(struct efi_memory_descriptor);
    
    u64 index = 0;
    for(u64 offset = 0; offset + descriptor_size <= memory_map_size;  offset += descriptor_size){
        struct efi_memory_descriptor *descriptor = (void *)((u8 *)descriptor_base + offset);
        
        log("descriptor[%d]       = {", offset / descriptor_size);
        log("    .memory_type     = %d,", descriptor->memory_type);
        log("    .physical_start  = %p,", descriptor->physical_start);
        log("    .virtual_start   = %p,", descriptor->virtual_start);
        log("    .number_of_pages = %lld,", descriptor->number_of_pages);
        log("    .attributes      = 0x%llx,", descriptor->attributes);
        log("};");
        
        g_efi_memory_map.data[index++] = *descriptor;
    }
    g_efi_memory_map.size = index;
    
    // 
    // Fix up the runtime services.
    // 
    efi_convert_pointer(0, &g_runtime_services.get_time);
    efi_convert_pointer(0, &g_runtime_services.set_time);
    efi_convert_pointer(0, &g_runtime_services.get_wakeup_time);
    efi_convert_pointer(0, &g_runtime_services.set_wakeup_time);
    efi_convert_pointer(0, &g_runtime_services.set_virtual_address_map);
    efi_convert_pointer(0, &g_runtime_services.convert_pointer);
    efi_convert_pointer(0, &g_runtime_services.get_variable);
    efi_convert_pointer(0, &g_runtime_services.set_variable);
    efi_convert_pointer(0, &g_runtime_services.get_next_high_mono_count);
    efi_convert_pointer(0, &g_runtime_services.reset_system);
    efi_convert_pointer(0, &g_runtime_services.update_capsule);
    efi_convert_pointer(0, &g_runtime_services.query_capsule_capabilities);
    efi_convert_pointer(0, &g_runtime_services.query_variable_info);
    
    // 
    // Fix up the system table.
    // 
    efi_convert_pointer(0, &g_system_table.FirmwareVendor);
    efi_convert_pointer(0, &g_system_table.runtime_services);
    
    efi_convert_pointer(0, &g_system_table.configuration_table.data);
    for(size_t index = 0; index < g_system_table.configuration_table.size; index++){
        efi_convert_pointer(0, &g_system_table.configuration_table.data[index].table);
    }
    
    // 
    // Fix up the efi_variable_list.
    // 
    efi_convert_pointer(1, &g_efi_variable_list.first);
    efi_convert_pointer(1, &g_efi_variable_list.last);
    
    for(struct efi_variable *it = g_efi_variable_list.first; it; it = it->next){
        efi_convert_pointer(1, &it->next);
        efi_convert_pointer(1, &it->variable_name);
    }
    
    return 0;
}

u64 wide_string_length(u16 *variable_name){
    u16 *it = variable_name;
    while(*it) it++;
    return it - variable_name;
}

int wide_string_match(u16 *a, u16 *b){
    
    while(*a && *b){
        if(*a != *b) return 0;
        a++, b++;
    }
    
    return (*a == 0) && (*b == 0);
}

efi_status efi_get_variable(u16 *variable_name, struct efi_guid *vendor_guid, u32 *attributes, u64 *in_out_data_size, void *data){ 
    
#if ENABLE_BIOS_LOGGING
    u8 buffer[0x100] = {0};
    for(u16 *it = variable_name; *it; it++){
        buffer[it - variable_name] = (u8)*it;
    }
    
    log("efi_get_variable %s", buffer);
#endif
    
    struct efi_variable *variable = g_efi_variable_list.first;
    
    for(; variable; variable = variable->next){
        if(wide_string_match(variable_name, variable->variable_name)) break;
    }
    
    if(!variable) return EFI_NOT_FOUND;
    
    if(attributes) *attributes = variable->attributes;
    
    u64 data_size = *in_out_data_size;
    *in_out_data_size = variable->data_size;
    if(data_size < variable->data_size) return EFI_BUFFER_TOO_SMALL;
    
    if(data_size) __movsb(data, variable->data, variable->data_size);
    
    return 0; 
}

efi_status efi_get_next_variable(u64 *inout_variable_name_size, u16 *inout_variable_name, struct efi_guid *inout_vendor_guid){ 
    
    struct efi_variable *variable = null;
    if(*inout_variable_name == 0){
        // 
        // Start the search!
        // 
        variable = g_efi_variable_list.first;
    }else{
        for(struct efi_variable *it = g_efi_variable_list.first; it; it = it->next){
            
            if(wide_string_match(it->variable_name, inout_variable_name)){
                variable = it;
                break;
            }
        }
        if(!variable) return EFI_INVALID_PARAMETER;
        variable = variable->next;
    }
    
    if(!variable) return EFI_NOT_FOUND;
    
    u64 size_required = 2 * (wide_string_length(variable->variable_name) + 1);
    if(*inout_variable_name < size_required){
        *inout_variable_name_size = size_required;
        return EFI_BUFFER_TOO_SMALL;
    }
    
    __movsb((u8 *)inout_variable_name, (u8 *)variable->variable_name, size_required);
    return EFI_SUCCESS;
}

efi_status efi_set_variable(u16 *variable_name, struct efi_guid *vendor_guid, u32 attributes, u64 data_size, void *data){
    u32 variable_name_length = (u32)wide_string_length(variable_name);
    if(!variable_name_length) return -1; // @cleanup: error code.
    
    
#if ENABLE_BIOS_LOGGING
    u8 buffer[0x100] = {0};
    for(u16 *it = variable_name; *it; it++){
        buffer[it - variable_name] = (u8)*it;
    }
    
    log("efi_set_variable %s attributes: 0x%x", buffer, attributes);
#endif
    
    if(g_system_table.boot_services == null){
        log("efi_set_variable after exit_boot_services... failling for now."); // @incomplete:
        return -1;
    }
    
    u64 size = sizeof(struct efi_variable) + data_size + (data_size & 1) + 2*(variable_name_length + 1);
    
    if(efi_variable_buffer_at + size > array_count(efi_variable_buffer)){
        log("Ran out of efi_variable space.");
        bios_crash();
    }
    
    u8 *address = efi_variable_buffer + efi_variable_buffer_at;
    
    struct efi_variable *variable = (void *)address;
    variable->next = null;
    variable->attributes = attributes;
    variable->data_size = data_size;
    if(data_size) __movsb(variable->data, data, data_size);
    variable->variable_name = (u16 *)(variable->data + data_size + (data_size & 1));
    __movsw(variable->variable_name, variable_name, variable_name_length + 1);
    
    
    efi_variable_buffer_at += (size + 7) & ~7; // align up to have the next variable start on an 8-byte boundary.
    
    log("variable: %p", address);
    
    if(g_efi_variable_list.first){
        g_efi_variable_list.last = g_efi_variable_list.last->next = variable;
    }else{
        g_efi_variable_list.first = g_efi_variable_list.last = variable;
    }
    
#if ENABLE_BIOS_LOGGING
    log("new variables:");
    for(struct efi_variable *var = g_efi_variable_list.first; var; var = var->next){
        u16 *variable_name = var->variable_name;
        
        u8 buffer[0x100] = {0};
        for(u16 *it = variable_name; *it; it++){
            buffer[it - variable_name] = (u8)*it;
        }
        
        log("   variable %s", buffer);
    }
#endif
    
    return 0;
}

efi_status efi_get_next_high_mono_count(void){ log("unimplemented get_next_high_mono_count"); bios_crash(); return 0; }
efi_status efi_reset_system(void){ log("unimplemented reset_system"); bios_crash(); return 0; }
efi_status efi_update_capsule(void){ log("unimplemented update_capsule"); bios_crash(); return 0; }
efi_status efi_query_capsule_capabilities(void){ log("unimplemented query_capsule_capabilities"); bios_crash(); return 0; }
efi_status efi_query_variable_info(void){ log("unimplemented query_variable_info"); bios_crash(); return 0; }


//_____________________________________________________________________________________________________________________
// Bios initialization.

void entry(u8 *boot_file_base, u64 page_table_pages, u64 efi_system_partition_starting_lba, u64 disk_last_lba, u64 partition_last_lba){
    
    g_efi_system_partition_starting_lba = efi_system_partition_starting_lba;
    g_partition_media.last_block = partition_last_lba - efi_system_partition_starting_lba;
    g_logical_block_media.last_block = disk_last_lba;
    
    log("Entered bios.");
    
    // 
    // Setup the boot services.
    // 
    g_system_table.boot_services = &g_boot_services;
    g_boot_services.raise_tpl = (void *)efi_raise_tpl;
    g_boot_services.restore_tpl = (void *)efi_restore_tpl;
    g_boot_services.allocate_pages = (void *)efi_allocate_pages;
    g_boot_services.free_pages = (void *)efi_free_pages;
    g_boot_services.get_memory_map = (void *)efi_get_memory_map;
    g_boot_services.allocate_pool = (void *)efi_allocate_pool;
    g_boot_services.free_pool = (void *)efi_free_pool;
    g_boot_services.create_event = (void *)efi_create_event;
    g_boot_services.set_timer = (void *)efi_set_timer;
    g_boot_services.wait_for_event = (void *)efi_wait_for_event;
    g_boot_services.signal_event = (void *)efi_signal_event;
    g_boot_services.close_event = (void *)efi_close_event;
    g_boot_services.check_event = (void *)efi_check_event;
    g_boot_services.install_protocol_interface = (void *)efi_install_protocol_interface;
    g_boot_services.reinstall_protocol_interface = (void *)efi_reinstall_protocol_interface;
    g_boot_services.uninstall_protocol_interface = (void *)efi_uninstall_protocol_interface;
    g_boot_services.handle_protocol = (void *)efi_handle_protocol;
    g_boot_services.reserved = (void *)efi_reserved;
    g_boot_services.register_protocol_notify = (void *)efi_register_protocol_notify;
    g_boot_services.locate_handle = (void *)efi_locate_handle;
    g_boot_services.locate_device_path = (void *)efi_locate_device_path;
    g_boot_services.install_configuration_table = (void *)efi_install_configuration_table;
    g_boot_services.load_image = (void *)efi_load_image;
    g_boot_services.start_image = (void *)efi_start_image;
    g_boot_services.exit = (void *)efi_exit;
    g_boot_services.unload_image = (void *)efi_unload_image;
    g_boot_services.exit_boot_services = (void *)efi_exit_boot_services;
    g_boot_services.get_next_monotonic_count = (void *)efi_get_next_monotonic_count;
    g_boot_services.stall = (void *)efi_stall;
    g_boot_services.set_watchdog_timer = (void *)efi_set_watchdog_timer;
    g_boot_services.connect_controller = (void *)efi_connect_controller;
    g_boot_services.disconnect_controller = (void *)efi_disconnect_controller;
    g_boot_services.open_protocol = (void *)efi_open_protocol;
    g_boot_services.close_protocol = (void *)efi_close_protocol;
    g_boot_services.open_protocol_information = (void *)efi_open_protocol_information;
    g_boot_services.protocols_per_handle = (void *)efi_protocols_per_handle;
    g_boot_services.locate_handle_buffer = (void *)efi_locate_handle_buffer;
    g_boot_services.locate_protocol = (void *)efi_locate_protocol;
    g_boot_services.install_multiple_protocol_interfaces = (void *)efi_install_multiple_protocol_interfaces;
    g_boot_services.uninstall_multiple_protocol_interfaces = (void *)efi_uninstall_multiple_protocol_interfaces;
    g_boot_services.calculate_crc32 = (void *)efi_calculate_crc32;
    g_boot_services.copy_mem = (void *)efi_copy_mem;
    g_boot_services.set_mem = (void *)efi_set_mem;
    g_boot_services.create_event_ex = (void *)efi_create_event_ex;
    
    // 
    // Initialize the efi_memory_map by initializing it to just be one free range.
    // 
    g_efi_memory_map.size = 1;
    g_efi_memory_map.data[0].memory_type = EfiConventionalMemory;
    g_efi_memory_map.data[0].physical_start = 0;
    g_efi_memory_map.data[0].number_of_pages = (4ull * 1024 * 1024 * 1024) / 0x1000;
    g_efi_memory_map.data[0].attributes = 0xf;
    
    
    {
        // 
        // Reserve the memory space of the IDT.
        // 
        
        u8 buffer[10];
        __sidt(buffer);
        
        // :IDT_GDT position
        u64 idt_page = *(u64 *)(buffer + 2);
        efi_allocate_pages(/*AllocateAddress*/2, EfiReservedMemoryType, /*number_of_pages*/1, &idt_page);
        
        u64 gdt_page = *(u64 *)(buffer + 2) - 0x1000;
        efi_allocate_pages(/*AllocateAddress*/2, EfiReservedMemoryType, /*number_of_pages*/1, &gdt_page);
    }
    
    {
        // 
        // Reserve the memory space of the local APIC.
        // 
        u64 local_apic_page = 0xfee00000;
        efi_allocate_pages(/*AllocateAddress*/2, EfiReservedMemoryType, /*number_of_pages*/1, &local_apic_page);
    }
    
    {
        // 
        // Reserve the memory space of the I/O APIC.
        // 
        u64 io_apic_page = 0xfec00000;
        efi_allocate_pages(/*AllocateAddress*/2, EfiReservedMemoryType, /*number_of_pages*/1, &io_apic_page);
    }
    
    {
        // @cleanup: It appears, this is simply not part of the memory map when I check it in hyper-v.
        //           What even is, do we even need? The Gop is below.
        u64 mg2b = 0xf8000000;
        u64 mg2l = 0x08000000;
        efi_allocate_pages(/*AllocateAddress*/2, EfiReservedMemoryType, /*number_of_pages*/(mg2l / 0x1000), &mg2b);
        
        // u64 hmib = 0xfe00ull << 20; // 0xfe0 00 00 00
        // u64 hmil =  0x200ull << 20; //  0x20 00 00 00
        // efi_allocate_pages(/*AllocateAddress*/2, EfiReservedMemoryType, /*number_of_pages*/((hmil + 0xfff) / 0x1000), &hmib);
    }
    
    {
        // 
        // "Allocate" the stack.
        // 
        u64 stack_size = (4 * 1024 * 1024);
        u64 physical_address = (((u64)_AddressOfReturnAddress() + 0xfff) & ~0xfff) - stack_size;
        
        efi_status allocate_stack_status = efi_allocate_pages(/*AllocateAddress*/2, EfiBootServiceData, stack_size/0x1000, &physical_address);
        if(allocate_stack_status < 0) bios_crash();
    }
    
    {
        // 
        // "Allocate" the page tables.
        // 
        u64 physical_address = __readcr3();
        efi_status allocate_page_table_status = efi_allocate_pages(/*AllocateAddress*/2, EfiBootServiceData, page_table_pages, &physical_address);
        if(allocate_page_table_status < 0) bios_crash();
    }
    {
        // __ImageBase is defined by the linker to be at the start of the image.
        extern u8 __ImageBase;
        u8 *base_address = &__ImageBase;
        
        u32 pe_header_offset = *(u32 *)(base_address + 0x3c);
        u32 image_size = *(u32 *)(base_address + pe_header_offset + /*signature*/4 + /*coff file header*/20 + 56);
        
        // 
        // "Allocate" the range this image takes up.
        // We are allocating for 'RuntimeServiceCode' as we will implement both runtime and boot service code in one.
        // 
        u64 physical_address = (u64)base_address; // Linear mapping.
        efi_status allocate_image_status = efi_allocate_pages(/*AllocateAddress*/2, EfiRuntimeServiceCode, image_size/0x1000, &physical_address);
        if(allocate_image_status < 0) bios_crash();
    }
    
    u32 pe_header_offset = *(u32 *)(boot_file_base + 0x3c);
    u32 image_size       = *(u32 *)(boot_file_base + pe_header_offset + 4 + 20 + 56);
    u32 entry_point_rva  = *(u32 *)(boot_file_base + pe_header_offset + 4 + 20 + 16);
    
    u64 physical_address = (u64)boot_file_base;
    efi_status allocate_image_status = efi_allocate_pages(/*AllocateAddress*/2, EfiLoaderCode, image_size/0x1000 + 0x80, &physical_address);
    if(allocate_image_status < 0) bios_crash();
    
    static struct{
        struct{
            u8 type;
            u8 subtype;
            u16 length;
            u16 path[22];
        } path;
        
        struct{
            u8 type;
            u8 subtype;
            u16 length;
        } terminator;
    } path_protocol = {
        .path = {
            .type = 4,
            .subtype = 4,
            .length = sizeof(path_protocol.path),
            .path = L"\\EFI\\BOOT\\BOOTX64.EFI",
        },
        .terminator = {
            .type = 0x7f,
            .subtype = 0xff,
            .length = sizeof(path_protocol.terminator),
        },
    };
    
    static struct efi_loaded_image_protocol loaded_image_protocol = {0};
    loaded_image_protocol.revision = 0x1000;
    loaded_image_protocol.system_table = &g_system_table;
    loaded_image_protocol.device_handle.value = (void *)0xb102;
    loaded_image_protocol.file_path = &path_protocol;
    loaded_image_protocol.image_base = boot_file_base;
    loaded_image_protocol.image_size = image_size;
    
    // 
    // Allocate and initialize the Firmware tables.
    // 
    
    struct acpi_table_header{
        u8 signature[4];
        u32 length;
        u8 revision;
        u8 checksum;
        u8 oem_id[6];
        u8 oem_table_id[8];
        u32 oem_revision;
        u8 creator_id[4];
        u32 creator_revision;
    };
    
#define initialize_acpi_table_header(header, sig, rev, end){        \
    *(header) = (struct acpi_table_header){                         \
        .signature = (sig),                                         \
        .length = (u8 *)(end) - (u8 *)(header),                     \
        .revision = (rev),                                          \
        .checksum = 0,                                              \
        .oem_id = "VRTUAL",                                         \
        .oem_table_id = "MICROSFT",                                 \
        .oem_revision = 1,                                          \
        .creator_id = "MSFT",                                       \
        .creator_revision = 0x05000000,                             \
    };                                                              \
    u8 checksum = 0;                                                \
    for(u8 *it = (u8 *)(header); it < (end); it++) checksum += *it; \
    (header)->checksum = -checksum;                                 \
}
    
    // RSDT - Root System Description Table
    // XSDT - (the same as the RSDT but 64-bit physical addresses)
    // FACP - Fixed ACPI Description Table
    // APIC - Multiple Apic Description Table
    // SRAT - System Resource Affinity Table
    // BGRT - Boot Graphics Reserouce Table
    
    // WAET - Windows ACPI Emulated Devices Table
    // OEM0 - OEM Speicific Table
    // FPDT - Firmware Performance Data Table
    
    u64 madt_physical_address = 0;
    {
        // 
        // MADT - Multiple APIC Description Table.
        // 
        
        efi_status page_allocation_status = efi_allocate_pages(/*AnyAddress*/0, EfiACPIReclaimMemory, /*number_of_pages*/1, &madt_physical_address);
        if(page_allocation_status < 0) bios_crash();
        
        // 
        // These tables sort of suck, they have unaligned members and so on.
        // 
        
        struct{
            struct acpi_table_header header;
            u32 local_apic_address;
            u32 flags;
        } *multiple_apic_description_table = (void *)madt_physical_address;
        multiple_apic_description_table->local_apic_address = 0xfee00000;
        multiple_apic_description_table->flags = 0;
        
        struct {
            u8 entry_type;
            u8 record_length;
            u8 apic_processor_id;
            u8 apic_id;
            u32 flags;
        } *type_0_entry = (void *)(multiple_apic_description_table + 1);
        type_0_entry->entry_type = 0;
        type_0_entry->record_length = sizeof(*type_0_entry);
        type_0_entry->apic_processor_id = 1;
        type_0_entry->apic_id = 0;
        type_0_entry->flags = /*enabled*/1;
        
        struct {
            u8 entry_type;
            u8 record_length;
            u8 io_apic_id;
            u8 reserved;
            
            u32 io_apic_address;
            u32 global_system_interrupt_base;
        } *type_1_entry = (void *)(type_0_entry + 1);
        type_1_entry->entry_type = 1;
        type_1_entry->record_length = sizeof(*type_1_entry);
        type_1_entry->io_apic_id = 1;
        type_1_entry->reserved = 0;
        type_1_entry->io_apic_address = 0xfec00000; 
        type_1_entry->global_system_interrupt_base = 0;
        
        struct {
            u8 entry_type;
            u8 record_length;
            
            u8 bus_source;
            u8 irq_source;
            
            u32 global_system_interrupt;
            u16 flags;
        } *type_2_entry = (void *)(type_1_entry + 1);
        type_2_entry->entry_type = 2;
        type_2_entry->record_length = sizeof(*type_2_entry);
        type_2_entry->bus_source = 0;
        type_2_entry->irq_source = 9;
        type_2_entry->global_system_interrupt = 9;
        type_2_entry->flags = 0xd; // polarity = active high, trigger mode = level triggered
        
        struct {
            u8 entry_type;
            u8 record_length;
        } *type_4_entry = (void *)((u8 *)type_2_entry + (sizeof(*type_2_entry) - 2));
        type_4_entry->entry_type    = 4;
        type_4_entry->record_length = 6;
        u8 *type_4_data = (u8 *)(type_4_entry + 1);
        type_4_data[0] = 1; // ACPI Processor UID
        *(u16 *)(type_4_data + 1) = 0; // flags
        type_4_data[3] = 1; // Local APIC LINT Number
        
        u8 *end = (u8 *)type_4_entry + type_4_entry->record_length;
        initialize_acpi_table_header(&multiple_apic_description_table->header, "APIC", 1, end);
    }
    
    u64 facs_physical_address = 0;
    {
        
        efi_status page_allocation_status = efi_allocate_pages(/*AnyAddress*/0, EfiACPIReclaimMemory, /*number_of_pages*/1, &facs_physical_address);
        if(page_allocation_status < 0) bios_crash();
        
        struct facs{
            u32 signature;
            u32 length;
            u32 hardware_signature;
            u32 firmware_waking_vector;
            u32 global_lock;
            u32 flags;
            u64 x_firmware_waking_vector;
            u8 version;
            u8 reserved[3];
            u32 OSPM_Flags;
            u8 reserved2[24];
        } *facs = (void *)facs_physical_address;
        
        facs->signature = 'SCAF';
        facs->length  = 64;
        facs->version = 1;
    }
    
    u64 dsdt_physical_address = 0;
    {
        
        struct dsdt{
            struct acpi_table_header header;
            u8 aml[];
        } *dsdt = null;
        
        static u8 aml[] = {
            #include "dsdt.inc"
        };
        
        efi_status page_allocation_status = efi_allocate_pages(/*AnyAddress*/0, EfiACPIReclaimMemory, /*number_of_pages*/(sizeof(*dsdt) + sizeof(aml) + 0xfff)/0x1000, &dsdt_physical_address);
        if(page_allocation_status < 0) bios_crash();
        
        dsdt = (void *)dsdt_physical_address;
        
        __movsb(dsdt->aml, aml, sizeof(aml));
        
        dsdt->header = (struct acpi_table_header){
            .signature = "DSDT",
            .length = sizeof(*dsdt) + sizeof(aml),
            .revision = 2,
            .checksum = 0,
            .oem_id = "MSFTVM",
            .oem_table_id = "DSDT01",
            .oem_revision = 1,
            .creator_id = "MSFT",
            .creator_revision = 0x05000000,
        };
        
        u8 checksum = 0;
        for(u8 *it = (u8 *)dsdt; it < (u8 *)dsdt + dsdt->header.length; it++) checksum += *it;
        dsdt->header.checksum = -checksum;
    }
    
    
    u64 fadt_physical_address = 0;
    {
        // 
        // FADT (Fixed ACPI Desription Table) contains information about the various fixed Hardware features.
        // 
        
        struct generic_address_structure{
            u8 address_space_id;
            u8 bit_width;
            u8 bit_offset;
            u8 access_size;
            u32 address_low;
            u32 address_high;
        };
        
        struct fadt{
            struct acpi_table_header header;
            
            u32 facs;
            u32 dsdt;
            
            u8  interrupt_model; // no longer used.
            u8  preferred_power_management_profile;
            u16 sci_interrupt_vector;
            u32 smi_cmd_io_port;
            u8  acpi_on_value;
            u8  acpi_off_value;
            u8  s4bios_req;
            
            u8  pstate_control;
            u32 pm1a_evt_blk_io_port;
            u32 pm1b_evt_blk_io_port;
            u32 pm1a_ctrl_blk_io_port;
            u32 pm1b_ctrl_blk_io_port;
            u32 pm2_ctrl_blk_io_port;
            u32 pm_tmr_blk_io_port;
            u32 gp0_blk_io_port;
            u32 gp1_blk_io_port;
            u8  pm1_evt_length;
            u8  pm1_ctrl_length;
            u8  pm2_ctrl_length;
            u8  pm_tmr_length;
            u8  gp0_blk_length;
            u8  gp1_blk_length;
            u8  gp1_base;
            u8  cstate_control;
            
            u16 lvl2_latency;
            u16 lvl3_latency;
            u16 flush_size;
            u16 flush_stride;
            
            u8  duty_offset;
            u8  duty_width;
            
            u8  day_alarm_index;
            u8  month_alarm_index;
            u8  century_alarm_index;
            
            u8  boot_architecture_flags[2];
            u8  reserved;
            u32 flags;
            
            struct generic_address_structure reset_reg;
            u8  reset_val;
            
            u8  arm_boot_arch[2];
            u8  minor_version_number;
            
            u32 x_firmware_ctrl_low;
            u32 x_firmware_ctrl_high;
            
            u32 x_dsdt_low;
            u32 x_dsdt_high;
            
            struct generic_address_structure x_pm1a_evt_blk;
            struct generic_address_structure x_pm1b_evt_blk;
            struct generic_address_structure x_pm1a_ctrl_blk;
            struct generic_address_structure x_pm1b_ctrl_blk;
            struct generic_address_structure x_pm2_ctrl_blk;
            struct generic_address_structure x_pm_tmr_blk;
            struct generic_address_structure x_gp0_blk;
            struct generic_address_structure x_gp1_blk;
            struct generic_address_structure sleep_control_reg;
            struct generic_address_structure sleep_status_reg;
            u8 hypervisor_vendor_identity[8];
        } *fadt = null;
        
        efi_status page_allocation_status = efi_allocate_pages(/*AnyAddress*/0, EfiACPIReclaimMemory, /*number_of_pages*/(sizeof(*fadt) + 0xfff)/0x1000, &fadt_physical_address);
        if(page_allocation_status < 0) bios_crash();
        
        fadt = (void *)fadt_physical_address;
        
        *fadt = (struct fadt){
            .facs = facs_physical_address,
            .dsdt = dsdt_physical_address,
            .interrupt_model = 1,
            .preferred_power_management_profile = 2,
            .sci_interrupt_vector = 9,
            .pm1_evt_length = 4,
            .pm1_ctrl_length = 2,
            .pm_tmr_length = 4,
            .gp0_blk_length = 4,
            .lvl2_latency = 0x65,
            .lvl3_latency = 0x3e9,
            .day_alarm_index = 0xd,
            .boot_architecture_flags[0] = 4,
            .flags = 0x85b8,
            
            .reset_reg = {
                .address_space_id = 1,
                .bit_width = 8,
                .bit_offset = 0,
                .access_size = 1,
                .address_low = 0x433,
            },
            .reset_val = 1,
            .minor_version_number = 2,
            
            .x_pm1a_evt_blk = {
                .address_space_id = 1,
                .bit_width = 0x20,
                .bit_offset = 0,
                .access_size = 4,
                .address_low = 0x400,
            },
            
            .x_pm1a_ctrl_blk = {
                .address_space_id = 1,
                .bit_width = 0x10,
                .bit_offset = 0,
                .access_size = 2,
                .address_low = 0x404,
            },
            
            .x_pm_tmr_blk = {
                .address_space_id = 1, 
                .bit_width = 0x20, 
                .bit_offset = 0, 
                .access_size = 4, 
                .address_low = 0x408,
            },
            
            .x_gp0_blk = {
                .address_space_id = 1,
                .bit_width = 0x20,
                .bit_offset = 0,
                .access_size = 4,
                .address_low = 0x40c,
            },
            
            .hypervisor_vendor_identity = "MsHyperV", // We could specify our own string here.
        };
        
        initialize_acpi_table_header(&fadt->header, "FACP", 6, (u8 *)(fadt + 1));
    }
    
    u64 rsdt_physical_address = 0;
    {
        // 
        // RSDT - Multiple APIC Description Table.
        efi_status page_allocation_status = efi_allocate_pages(/*AnyAddress*/0, EfiACPIReclaimMemory, /*number_of_pages*/1, &rsdt_physical_address);
        if(page_allocation_status < 0) bios_crash();
        
        struct root_system_descriptor_table{
            struct acpi_table_header header;
            
            u32 madt_physical_address;
            u32 fadt_physical_address;
        } *root_system_descriptor_table = (void *)rsdt_physical_address;
        root_system_descriptor_table->madt_physical_address = (u32)madt_physical_address;
        root_system_descriptor_table->fadt_physical_address = (u32)fadt_physical_address;
        initialize_acpi_table_header(&root_system_descriptor_table->header, "RSDT", 1, (u8 *)(root_system_descriptor_table + 1));
    }
    
    u64 xsdt_physical_address = 0;
    {
        // 
        // XSDT - Multiple APIC Description Table.
        efi_status page_allocation_status = efi_allocate_pages(/*AnyAddress*/0, EfiACPIReclaimMemory, /*number_of_pages*/1, &xsdt_physical_address);
        if(page_allocation_status < 0) bios_crash();
        
        struct acpi_table_header *header = (void *)xsdt_physical_address;
        struct {
            u64 madt_physical_address;
            u64 fadt_physical_address;
        } *addresses = (void *)(header + 1);
        addresses->madt_physical_address = madt_physical_address;
        addresses->fadt_physical_address = fadt_physical_address;
        initialize_acpi_table_header(header, "XSDT", 1, (u8 *)(addresses + 1));
    }
    
    // @cleanup: Can this be in the executable or should I put this also in EfiACPIReclaimMemory?
    static struct root_system_description_pointer{
        u8 signature[8]; // "RSD PTR "
        u8 checksum;
        u8 oem_id[6];    // "VRTUAL"
        u8 revision;     // 2
        u32 root_system_descriptor_table_address;
        
        // fields for revision 2.0
        u32 length;
        u64 extended_root_system_descriptor_table_address;
        u8 extended_checksum;
        u8 reserved[3];
    } root_system_description_pointer = {
        .signature = "RSD PTR ",
        .oem_id    = "VRTUAL",
        .revision  = 2,
        .length = 0x24, // sizeof(struct root_system_description_pointer) - padding
    };
    
    root_system_description_pointer.root_system_descriptor_table_address          = rsdt_physical_address;
    root_system_description_pointer.extended_root_system_descriptor_table_address = xsdt_physical_address;
    
    {
        u8 checksum = 0;
        for(u32 index = 0; index < 0x14; index++){
            checksum += ((u8 *)&root_system_description_pointer)[index];
        }
        root_system_description_pointer.checksum = -checksum;
        
        u8 extended_checksum = 0;
        for(u32 index = 0; index < 0x24; index++){
            extended_checksum += ((u8 *)&root_system_description_pointer)[index];
        }
        root_system_description_pointer.extended_checksum = -extended_checksum;
    }
    
    u64 smbios_physical_address = 0;
    u64 smbios_table_size = 0;
    {
        u64 size = 0x1000;
        efi_status page_allocation_status = efi_allocate_pages(/*AnyAddress*/0, EfiACPIReclaimMemory, /*number_of_pages*/1, &smbios_physical_address);
        if(page_allocation_status < 0) bios_crash();
        
        struct smbios_header{
            u8  Type;
            u8  Length;
            u16 Handle;
        };
        
        u8 *out = (u8 *)smbios_physical_address;
        
        struct system_information{
            struct smbios_header Header;
            u8 Manifacturer;
            u8 ProductName;
            u8 Version;
            u8 SerialNumber;
            union{
                struct{
                    u32 time_low;
                    u16 time_mid;
                    u16 time_hi_and_version;
                    u8  clock_seq_hi_and_reserved;
                    u8  clock_seq_low;
                    u8  Node[6];
                };
                u8 data[16];
            } Uuid;
            u8 WakeUpType;
            u8 SkuNumber;
            u8 Family;
        } system_information = {
            .Header = {.Type = /*System Information*/1, .Length = sizeof(system_information), .Handle = 1},
            .Manifacturer = 0x1,
            .ProductName = 0x2,
            .Version = 0x3,
            .SerialNumber = 0x4,
            
            // 
            // This value is the system UUID/system GUID.
            // This value appers to be uniqe for every (virtual) computer.
            // Windows seems to use this value to cache information about the system to speed up booting.
            // 
            .Uuid = {
                .data = {0x13, 0x37, 0x13, 0x37, 0x13, 0x37, 0x13, 0x37, 0x13, 0x37, 0x13, 0x37, 0x13, 0x37, 0x13, 0x37},
            },
            .WakeUpType = 0x6,
            .SkuNumber = 0x5,
            .Family = 0x6,
        };
        __movsb((u8 *)out, (u8 *)&system_information, sizeof(system_information));
        out += sizeof(system_information)-1;
        
#define out_string(a) do{__movsb((u8 *)out, (u8 *)a, sizeof(a)); out += sizeof(a); } while(0)
        out_string("Microsoft Corporation");
        out_string("Virtual Machine");
        out_string("Hyper-V UEFI Release v4.0");
        out_string("0086-9297-4576-2941-7251-3231-07");
        out_string("None");
        out_string("Virtual Machine");
#undef out_string
        
        smbios_table_size = (u64)out - smbios_physical_address;
    }

    static struct smbios3_table{
        u8 identifier[5];
        u8 checksum;
        u8 length;
        u8 major_version;
        u8 minor_version;
        u8 docrev;
        u8 entry_point_revision;
        u8 reserved;
        u32 max_structure_size;
        void *table_address;
    } smbios3_table = {
        .identifier = "_SM3_",
        .length = sizeof(smbios3_table),
        .major_version = 3,
        .minor_version = 1,
    };
    
    smbios3_table.max_structure_size = smbios_table_size;
    smbios3_table.table_address = (void *)smbios_physical_address;
    
#if 0
    static u8 SMBIOS[] = {
#include "smbios.inc"
    };
    
    smbios3_table.max_structure_size = 0x4c6;
    smbios3_table.table_address = (void *)SMBIOS;
#endif
    
    {
        u8 checksum = 0;
        for(int i = 0; i < smbios3_table.length; i++){
            checksum += ((u8 *)&smbios3_table)[i];
        }
        smbios3_table.checksum = -checksum;
    }
    
    
#define EFI_ACPI_TABLE_GUID {0x8868e871, 0xe4f1, 0x11d3, {0xbc, 0x22, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81}}
#define SMBIOS3_TABLE_GUID  {0xf2fd1544, 0x9794, 0x4a2c, {0x99, 0x2e, 0xe5, 0xbb, 0xcf, 0x20, 0xe3, 0x94}}
    
    static struct efi_configuration_table_entry configuration_table_entries[] = {
        [0] = { .guid  = EFI_ACPI_TABLE_GUID },
        [1] = { .guid  = SMBIOS3_TABLE_GUID },
    };
    configuration_table_entries[0].table = &root_system_description_pointer;
    configuration_table_entries[1].table = &smbios3_table;
    
    // 
    // Fill out the "boottime" runtime services.
    // 
    struct efi_runtime_services *runtime_services = &g_runtime_services;
    runtime_services->get_time = efi_get_time;
    runtime_services->set_time = efi_set_time;
    runtime_services->get_wakeup_time = efi_get_wakeup_time;
    runtime_services->set_wakeup_time = efi_set_wakeup_time;
    runtime_services->set_virtual_address_map = efi_set_virtual_address_map;
    runtime_services->convert_pointer = efi_convert_pointer;
    runtime_services->get_variable = efi_get_variable;
    runtime_services->get_next_variable = efi_get_next_variable;
    runtime_services->set_variable = efi_set_variable;
    runtime_services->get_next_high_mono_count = efi_get_next_high_mono_count;
    runtime_services->reset_system = efi_reset_system;
    runtime_services->update_capsule = efi_update_capsule;
    runtime_services->query_capsule_capabilities = efi_query_capsule_capabilities;
    runtime_services->query_variable_info = efi_query_variable_info;
    
    
    // 
    // Setup some required EFI-variables.
    // 
    // @note: We don't have to specify any BOOT#### variables, as we assume the default boot case, 
    //        where there is none. Otherwise, we would have to boot a different file...
    // 
    
    static struct efi_variable SetupMode = {
        .attributes = 2,
        .variable_name = L"SetupMode",
        .data_size = 1,
        .data = {1},
    };
    sll_push_back(g_efi_variable_list, &SetupMode);
    
    static struct efi_variable SecureBoot = {
        .attributes = 2,
        .variable_name = L"SecureBoot",
        .data_size = 1,
        .data = {0},
    };
    sll_push_back(g_efi_variable_list, &SecureBoot);
    
    {
        // 
        // Allocate the Hypercall page.
        // 
        u64 hypercall_page = 0;
        efi_status page_allocation_status = efi_allocate_pages(/*AnyAddress*/0, EfiRuntimeServiceCode, /*number_of_pages*/1, &hypercall_page);
        if(page_allocation_status < 0) bios_crash();
        
        log("hypercall page %p", hypercall_page);
        
        __writemsr(/*HV_X64_MSR_HYPERCALL*/0x40000001, hypercall_page | 1);
    }
    
    {
        // 
        // Allocate the GOP buffer.
        // 
        u64 GOP_buffer = g_efi_graphics_output_protocol_mode.frame_buffer_base;
        u64 GOP_pages  = g_efi_graphics_output_protocol_mode.frame_buffer_size / 0x1000;
        efi_status page_allocation_status = efi_allocate_pages(/*AllocateAddress*/2, EfiRuntimeServiceCode, /*number_of_pages*/GOP_pages, &GOP_buffer);
        if(page_allocation_status < 0) bios_crash();
    }
    
    // 
    // Fill out the system table.
    // 
    
    g_system_table.FirmwareVendor = L"Me :)";
    g_system_table.runtime_services = runtime_services;
    g_system_table.console_in  = &g_efi_simple_text_input_protocol;
    g_system_table.console_out = &g_efi_simple_text_output_protocol;
    g_system_table.configuration_table.size = array_count(configuration_table_entries);
    g_system_table.configuration_table.data = configuration_table_entries;
    
    struct efi_handle console_out_handle;
    struct efi_simple_text_output_protocol *console_out;
    
    struct efi_handle efi_handle = { &loaded_image_protocol };
    log("efi_handle %p", efi_handle.value);
    
    efi_status (*efi_main)(struct efi_handle image_handle, struct efi_system_table *system_table) = (void *)(boot_file_base + entry_point_rva);
    efi_main(efi_handle, &g_system_table);
}

