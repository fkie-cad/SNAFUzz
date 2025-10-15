
#include <stddef.h>
#include <intrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char    u8;
typedef unsigned short   u16;
typedef unsigned int     u32;
typedef unsigned __int64 u64;

#define print(...) (printf(__VA_ARGS__), fflush(0))

#include "src/uefi_bios.h"

__declspec(noinline) void cause_vmexit(u32 code, void *rdx){
    (void)rdx;
    int cpuinfo[4]; // ignored for now.
    __cpuid(cpuinfo, code);
}

int wmain(int argc, wchar_t *argv[]){
    
    if(argc != 2){
        print("Usage: %ws <file>\n", argv[0]);
        return 0;
    }
    
    FILE *file = _wfopen(argv[1], L"rb");
    if(!file){
        print("Error: Could not open '%ws'\n", argv[1]);
        return 1;
    }
    
    fseek(file, 0, SEEK_END);
    size_t file_size = _ftelli64(file);
    fseek(file, 0, SEEK_SET);
    
    u8 *data = malloc(file_size);
    fread(data, 1, file_size, file);
    fclose(file);
    
    wchar_t *file_name = wcsrchr(argv[1], L'\\');
    if(!file_name) file_name = argv[1];
    size_t length = wcslen(file_name);
    
    char *mb_file_name = malloc(4 * length + 1);
    size_t mb_file_name_length = wcstombs(mb_file_name, file_name, 4 * length + 1);
    
    
    // 
    // Copy out the file.
    // 
    struct cpuid_drag_and_drop_input_buffer output_buffer = {
        .file_name = mb_file_name,
        .file_name_size = mb_file_name_length,
        .file_data = data,
        .file_size = file_size,
    };
    
    cause_vmexit(CPUID_copy_out, &output_buffer);
    return 0;
}
