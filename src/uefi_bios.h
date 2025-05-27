
// 
// Definitions used by both the 'uefi_bios.c' running inside the hypervisor 
// and the supporting code running on the host.
// These are MSR's (Model Specific Register's), which when accesssed (rdmsr),
// do "something" special.
// 

// Cause a crash. This is used for asserts in 'uefi_bios.c'.
#define BIOS_crash      0x1337dead

// Cause the hypervisor to enter the debugger. This is used for debugging.
#define BIOS_break      0x1337aaaa

// Prints something to the host console. This can be used for debugging.
#define BIOS_log        0x1337babe

// Allows for reading/writing of the disk-image, before the vmbus-connection is established.
#define BIOS_disk_read  0x1337cafe
#define BIOS_disk_write 0x1337f00d

struct cpuid_drag_and_drop_input_buffer{
    char *file_name;
    u64 file_name_size;
    char *file_data;
    u64 file_size;
};
#define CPUID_drag_and_drop 0x1337abcd
