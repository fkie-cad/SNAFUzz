
//_____________________________________________________________________________________________________________________
// Basic Utilities

#define extract_bits(packed, lsb, msb) (((packed) >> (lsb)) & ((1U << ((msb) - (lsb) + 1)) - 1))

// Exiting the program.
no_return void os_panic(u32 exit_code){
    os_debug_break();
    _exit(exit_code);
}


#if 0
#include <stddef.h>

#define STB_SPRINTF_IMPLEMENTATION
#include "stb_sprintf.h"

// A flushing print.
int print(char *format, ...){
    
    va_list va;
    va_start(va, format);
    
    // Just here for consistent printing between windows and linux for now.
    char buffer[0x400];
    int ret = stbsp_vsnprintf(buffer, sizeof(buffer), format, va);
    
    fputs(buffer, stdout);
    
    va_end(va);
    fflush(0);
    return ret;
}


int fprint(FILE *file, char *format, ...){
    
    va_list va;
    va_start(va, format);
    
    // Just here for consistent printing between windows and linux for now.
    char buffer[0x400];
    int ret = stbsp_vsnprintf(buffer, sizeof(buffer), format, va);
    
    fputs(buffer, file);
    
    va_end(va);
    
    return ret;
}

#else

// A flushing print.
int print(char *format, ...){
    va_list va;
    va_start(va, format);
    int ret = vprintf(format, va);
    va_end(va);
    fflush(0);
    return ret;
}

#define fprint fprintf
#endif

// A malloc which exits on error.
static void *save_malloc(size_t size, char *file, int line){
    void *ret = malloc(size);
    if(!ret){
        print("Out of memory error at %s(%d): Could not allocate memory.\n", file, line);
        os_panic(1);
    }
    memset(ret, 0, size);
    return ret;
}
#define malloc(size) save_malloc(size, __FILE__, __LINE__)

void *os_reserve_memory(u64 size){
#if _WIN32
    return VirtualAlloc(null, size, /*MEM_RESERVE*/0x2000, /*PAGE_READWRITE*/0x4);
#else
    return mmap(null, size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif
}

int os_commit_memory(void *base, u64 commit_size, int executable){
#if _WIN32
    int perms = executable ? /*PAGE_EXECUTE_READWRITE*/0x40 : /*PAGE_READWRITE*/0x4;
    u8 *memory = VirtualAlloc(base, commit_size, /*MEM_COMMIT*/0x00001000, perms);
    return memory == base;
#else
    int perms = executable ? PROT_READ | PROT_WRITE | PROT_EXEC : PROT_READ | PROT_WRITE;
    int failiure = mprotect(base, commit_size, perms);
    return failiure == 0;
#endif
}

void *os_allocate_memory(u64 size){
#if _WIN32
    return VirtualAlloc(null, size, /*MEM_RESERVE|MEM_COMMIT*/0x3000, /*PAGE_READWRITE*/4);
#else
    return mmap(null, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif
}

#if !_WIN32
#define SEC_IN_NS (1000ull * 1000 * 1000)

void QueryPerformanceCounter(u64 *lpCounter){
    struct timespec time; clock_gettime(CLOCK_MONOTONIC, &time);
    u64 nano_seconds = time.tv_nsec + time.tv_sec * SEC_IN_NS;
    *lpCounter = nano_seconds;
}

void QueryPerformanceFrequency(u64 *lpFrequency){
    *lpFrequency = SEC_IN_NS;
}

#endif

// Getting a timer.
double os_get_time_in_seconds(void){
    u64 frequency, counter;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&counter);
    return (double)counter / (double)frequency;
}

void sleep_miliseconds(u32 miliseconds){
#ifdef _WIN32
    Sleep(miliseconds);
#else
    usleep(1000ull * miliseconds);
#endif
}

// Dumping memory.
void print_byte_range(void *_bytes, u64 size, u64 offset){
    u8 *bytes = _bytes;
    
    for(u64 i = 0; i < size; i += 16){
        print("0x%.8llx: ", i + offset);
        for(u64 j = 0; j < 16; j++){
            if(j == 8) print("- ");
            
            u64 index = i + j;
            if(index < size){
                print("%.2x ", (unsigned char)bytes[index]);
            }else{
                print("   ");
            }
        }
        
        print("    ");
        
        for(u64 j = 0; j < 16; j++){
            u64 index = i + j;
            if(index < size){
                unsigned char byte = (unsigned char)bytes[index];
                
                if(32 <= byte && byte <= 126){
                    print("%c", byte);
                }else{
                    print(".");
                }
            }else{
                print("   ");
            }
        }
        print("\n");
    }
}


//_____________________________________________________________________________________________________________________
// File Utilities

struct file{
    union{
        u8 *memory;
        u8 *data;
    };
    u64 size;
};

#if _WIN32
#define ftell64 _ftelli64
#else 
#define ftell64 ftell
#endif

struct file load_file(char *file_name){
    struct file ret = {0};
    
    FILE *handle = fopen(file_name, "rb");
    
    if(!handle) return ret;
    
    fseek(handle, 0, SEEK_END);
    
    size_t size = ftell64(handle);

    if(size == -1) return ret; // @note: '-1' might be the worst error value....
    
    fseek(handle, 0, SEEK_SET);
    
    u8 *memory = malloc(size + 1);
    memory[size] = 0;
    
    fread(memory, 1, size, handle);
    
    fclose(handle);
    
    ret.memory = memory;
    ret.size   = size;
    
    
    return ret;
}


#if _WIN32

int download_file(char *file_path, char *url){
    
    int Result = URLDownloadToFileA(NULL, url, file_path, 0, NULL);
    
    if(Result != /*S_OK*/0){
        print("Error: Failed to download '%s' from '%s' with result 0x%x.\n", file_path, url, Result);
    }
    
    return  Result == /*S_OK*/0;
}

#else

int download_file(char *filename, char *url) {
    CURL *curl = curl_easy_init();
    if(!curl) return 0;
    
    FILE *fp = fopen(filename, "wb");
    if(!fp){
        curl_easy_cleanup(curl);
        return 0;
    }
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    CURLcode res = curl_easy_perform(curl);
    
    curl_easy_cleanup(curl);
    fclose(fp);
    return res == CURLE_OK;
}

#endif


struct file memory_map_file(char *file_name, HANDLE *optional_out_file_handle, int copy_on_write){
    
#if _WIN32
    
    struct file ret = {0};
    
    HANDLE FileHandle = CreateFileA(file_name, /*GENERIC_READ*/0x80000000L, /*FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE*/7, null, /*OPEN_EXISTING*/3, /*FILE_ATTRIBUTE_NORMAL*/0x80, null);
    
    if(FileHandle.Unused == (u64)-1){
        print("Error: Could not open '%s' error %d\n", file_name, GetLastError());
        return ret;
    }
    
    u64 FileSize = 0;
    if(!GetFileSizeEx(FileHandle, &FileSize)){
        print("Error: Could not determine the file size of '%s'\n", file_name);
        CloseHandle(FileHandle);
        return ret;
    }
    
    // HANDLE CreateFileMappingA(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCSTR lpName);
    //     'hfile'                   - a handle to the underlying file.
    //     'lpFIleMappingAttributes' - some security thing, as always we can just specify NULL.
    //     'flProtect'               - this determines the permissions, which a caller of 'MapViewOfFile' is allowed to use.
    //     'dwMaximumSizeHigh/dwMaximumSizeLow' - If both of these are 0, the size gets initialized to the size of the 'hFile'.
    //     'lpName'                  - a name for the 'FileMapping'. We don't need this.
    HANDLE FileMapping = CreateFileMappingA(FileHandle, NULL, /*PAGE_READONLY*/2, 0, 0, NULL);
    if(!FileMapping.Unused){
        print("Error: Could not 'CreateFileMappingA' for %s. GetLastError %d.\n", file_name, GetLastError());
        CloseHandle(FileHandle);
        return ret;
    }
    
    u32 desired_access = copy_on_write ? /*FILE_MAP_COPY*/1 : /*FILE_MAP_READ*/4;
    
    // LPVOID MapViewOfFileEx(HANDLE hFileMappingObject, DWORD  dwDesiredAccess, DWORD  dwFileOffsetHigh, DWORD  dwFileOffsetLow, SIZE_T dwNumberOfBytesToMap, LPVOID lpBaseAddress);
    //     'hFileMappingObject'   - A handle to the file mapping object above.
    //     'dwDesiredAccess'      - The access permissions of the mapping. For some reasons these use different constants then the usual 'PAGE_READ_WRITE'.
    //     'dwFileOffset'         - The offset in the File of where to map. 
    //     'dwNumberOfBytesToMap' - How many bytes we want to map. If this is 0 map to the end.
    //     'lpBaseAddress'        - an optional base address, for us this is the 'Base'. This can be NULL to let the kernel decide
    u8 *MapAddress = MapViewOfFileEx(FileMapping, desired_access, 0, 0, 0, NULL);
    if(MapAddress == NULL){
        print("Error: 'MapViewOfFileEx' failed for file '%s' last error %d\n", file_name, GetLastError());
        CloseHandle(FileMapping);
        CloseHandle(FileHandle);
        return ret;
    }
    
    ret.memory = MapAddress;
    ret.size   = FileSize;
    
    // @cleanup: Should we close the file handle here?
    if(optional_out_file_handle) *optional_out_file_handle = FileHandle;
    
    return ret;
    
#else
    struct file ret = {0};
    
    int file_descriptor = open(file_name, O_RDONLY);
    if(file_descriptor == -1){
        perror("open");
        return ret;
    }
    
    // 
    // Determine the size of the file.
    // 
    struct stat stat_buffer;
    if(fstat(file_descriptor, &stat_buffer) == -1){
        perror("fstat");
        close(file_descriptor);
        return ret;
    }
    
    u64 size = stat_buffer.st_size;
    
    int prot = PROT_READ | (copy_on_write ? PROT_WRITE : 0);
    
    // void *mmap(void *address, size_t length, int prot, int flags, int fd, off_t offset);
    //     'address' - NULL means the kernel chooses.
    //     'length'  - Length of the file in this case, not sure what happens when it changed size.
    //     'prot'    - Because we use a private mapping, PROT_READ means read only, PROT_READ | PROT_WRITE means Copy on Write.
    //     'flags'   - MAP_PRIVATE means copy-on-wirte mapping.
    //     'offset'  - We don't want an offset.
    u8 *mapped = mmap(NULL, size, prot, MAP_PRIVATE, file_descriptor, 0);
    if(mapped == MAP_FAILED){
        perror("mmap");
        close(file_descriptor);
        return ret;
    }
    
    if(optional_out_file_handle) *optional_out_file_handle = (HANDLE){file_descriptor};
    
    ret.data = mapped;
    ret.size = size;
    return ret;
#endif
    
}

//_____________________________________________________________________________________________________________________
// Memory arena - A linear allocator.

struct memory_arena{
    u8 *base;
    u8 *current;
    smm committed;
    smm reserved;
};

void initialize_arena(struct memory_arena *arena){
    
    u64 reserved = 0x1000000000;
    u8 *rw_memory = os_reserve_memory(reserved);

    if(!rw_memory){
        print("Error: Could not reserve memory for arena.\n");
        os_panic(1);
    }
    
    arena->committed = 0;
    arena->reserved = reserved;
    arena->current  = rw_memory;
    arena->base     = rw_memory;
}

void *arena_allocate_struct(struct memory_arena *arena, smm size, smm alignment){
    smm alignment_mask   = alignment - 1;
    smm alignment_needed = alignment - ((smm)arena->current & alignment_mask);
    if(alignment_needed != alignment){
        arena->current += alignment_needed;
    }
    
    while((s64)(arena->current - arena->base + size) > arena->committed){
        u8 *new_base = arena->base + arena->committed;
        u64 commit_size = 0x1000000;
        
        int success = os_commit_memory(new_base, commit_size, /*executable*/false);
        
        if(!success){
            print("Out of memory error: Could not commit during 'arena_allocate_struct'.\n");
            invalid_code_path();
        }
        
        arena->committed += commit_size;
    }
    
    u8 *ret = arena->current;
    memset(ret, 0, size);
    arena->current += size;
    return ret;
}

#define push_struct(arena, type) (type *)arena_allocate_struct(arena, sizeof((type){0}), _Alignof(type))
#define push_data(arena, type, size) (type *)arena_allocate_struct(arena, (size) * sizeof((type){0}), _Alignof(type))

//_____________________________________________________________________________________________________________________
// String utilities

struct string{
    char *data;
    smm size;
};
#define string(a) (struct string){ .data = (a), .size = (sizeof(a) - 1) }
#define const_string(a) { .data = (a), .size = (sizeof(a) - 1) }

int string_match(struct string lhs, struct string rhs){
    if(lhs.size != rhs.size) return 0;
    int are_equal = strncmp((char *)lhs.data, (char *)rhs.data, lhs.size) == 0;
    return are_equal;
}

int character_is_whitespace(char c){
    return (c == ' ' || c == '\t' || c == '\n');
}

void string_skip_whitespace(struct string *string){
    while(string->size && character_is_whitespace(string->data[0])){
        string->size -= 1;
        string->data += 1;
    }
}

struct string string_eat_nonwhitespace(struct string *string){
    struct string ret = *string;
    
    while(string->size && !character_is_whitespace(string->data[0])){
        string->data += 1;
        string->size -= 1;
    }
    
    ret.size = string->data - ret.data;
    return ret;
}


struct string string_eat_line(struct string *string){
    struct string ret = *string;
    
    while(string->size && string->data[0] != '\n'){
        string->data += 1;
        string->size -= 1;
    }
    
    ret.size = string->data - ret.data + (string->size != 0);
    return ret;
}


struct string string_strip_file_path(struct string file_path){
    struct string file_name = file_path;
    for(smm index = file_path.size - 1; index >= 0; index--){
        if(file_path.data[index] == '/' || file_path.data[index] == '\\'){
            file_name.data = file_path.data + (index + 1);
            file_name.size = file_path.size - (index + 1);
            break;
        }
    }
    return file_name;
}

struct string string_strip_file_extension(struct string file_name){
    struct string ret = file_name;
    for(smm index = file_name.size - 1; index > 0; index--){
        if(file_name.data[index] == '.'){
            ret.size = index;
            break;
        }
    }
    return ret;
}

u32 string_hash(struct string string){
    u32 hash = 1337;
    
    for(u32 index = 0; index < string.size; index++){
        // 33 * hash + character
        hash = ((hash << 5) + hash) + string.data[index];
    }
    
    return hash;
}

char *push_cstring_from_string(struct memory_arena *arena, struct string string){
    char *ret = memcpy(push_data(arena, char, string.size + 1), string.data, string.size);
    ret[string.size] = 0;
    return ret;
}

u64 parse_number(struct string string, int *error){
    
    //
    //    -> hex
    // 0x -> hex
    // 0n -> decimal
    // 0b -> binary
    // 0o -> octal
    //
    
    int base = 0;
    
    if(string.size >= 2 && string.data[0] == '0'){
        if(string.data[1] == 'x') { base = 16; }
        if(string.data[1] == 'n') { base = 10; }
        if(string.data[1] == 'b') { base =  2; }
        if(string.data[1] == 'o') { base =  8; }
    }
    
    if(base){
        string.size -= 2;
        string.data += 2;
    }else{
        base = 0x10;
    }
    
    u64 ret = 0;
    for(smm index = 0; index < string.size; index++){
        
        char character = string.data[index];
        
        // we assume we are done parsing the string on whitespace...
        if(character == ' ' || character == '\n') break;
        
        // skip common separating characters
        if(character == '`' || character == '_') continue;
        
        if(base == 16){
            ret *= 16;
            if('a' <= character && character <= 'f'){
                ret += character - 'a' + 10;
            }else if('A' <= character && character <= 'F'){
                ret += character - 'A' + 10;
            }else if('0' <= character && character <= '9'){
                ret += character - '0';
            }else{
                *error = 1;
                return 0;
            }
        }else{
            ret *= base;
            if('0' <= character && character <= '0' + base){
                ret += character - '0';
            }else{
                *error = 1;
                return 0;
            }
        }
    }
    return ret;
}

#if _WIN32
#define stricmp _stricmp
#define strnicmp _strnicmp
#else   
#define stricmp strcasecmp
#define strnicmp strncasecmp
#endif

int cstring_ends_with_case_insensitive(char *haystack, char *needle){
    size_t haystack_size = strlen(haystack);
    size_t   needle_size = strlen(needle);
    if(haystack_size < needle_size) return 0;
    
    char *end = haystack + (haystack_size - needle_size);

    return stricmp(end, needle) == 0;
}

//_____________________________________________________________________________________________________________________
// Theading Utilities

#define atomic_load(type, value) *((volatile type *)(&value))

#if _WIN32

#define atomic_postincrement(value)         (_InterlockedIncrement64(&(value)) - 1)
#define atomic_preincrement(value)        _InterlockedIncrement64(&(value))
#define atomic_increment(value)            _InterlockedIncrement64(&(value))
#define atomic_exchange_add(addend, value) _InterlockedExchangeAdd64(&(addend), (value))

#define atomic_compare_exchange_pointer(dest, value, compare) _InterlockedCompareExchangePointer((void **)(dest), (value), (compare));

// @cleanup: maybe make this generic.
#define atomic_compare_exchange(dest, value, compare) _InterlockedCompareExchange((dest), (value), (compare))

#define long32 long

#else

// 
// Linux
// 

#define atomic_postincrement(value)         (__sync_fetch_and_add(&(value), 1) - 1)
#define atomic_preincrement(value)        __sync_fetch_and_add(&(value), 1)
#define atomic_increment(value)            __sync_fetch_and_add(&(value), 1)
#define atomic_exchange_add(addend, value) __sync_fetch_and_add(&(addend), (value))

#define atomic_compare_exchange_pointer(dest, compare, value) __sync_val_compare_and_swap((void **)(dest), (void *)(value), (void *)(compare));
#define atomic_compare_exchange(dest, compare, value) __sync_val_compare_and_swap((dest), (value), (compare))

#define long32 int

#endif

// Ticket locks are used, whenever we get a new crash so the inputs are in order.
struct ticket_spinlock{
    s64 tickets_given_out;
    s64 ticket_in_work;
};

static void ticket_spinlock_lock(struct ticket_spinlock *mutex){
    s64 my_ticket = atomic_postincrement(mutex->tickets_given_out);
    while(atomic_load(s64, mutex->ticket_in_work) != my_ticket){
        _mm_pause();
    }
}

static void ticket_spinlock_unlock(struct ticket_spinlock *mutex){
    atomic_postincrement(mutex->ticket_in_work);
}


#if _WIN32
#define byteswap_u64 _byteswap_uint64
#define byteswap_u32 _byteswap_ulong
#define byteswap_u16 _byteswap_ushort
#else
#define byteswap_u64 __builtin_bswap64
#define byteswap_u32 __builtin_bswap32
#define byteswap_u16 __builtin_bswap16

#define _bittestandset __atomic_test_and_set
#define __popcnt64 __builtin_popcountll

static inline int _BitScanForward64(unsigned *Index, unsigned long Mask) {
    if (Mask == 0) return 0;
    __asm__ volatile ("bsf %1, %0"
            : "=r" (*Index)
            : "rm" (Mask)
            : "cc");
    return 1;
}

static inline int _BitScanForward(unsigned *Index, unsigned Mask) {
    if (Mask == 0) return 0;
    __asm__ volatile ("bsf %1, %0"
            : "=r" (*Index)
            : "rm" (Mask)
            : "cc");
    return 1;
}

static inline int _bittest(const long *Base, long Bit) {
    unsigned char result;
    __asm__ volatile ("bt %2, %1\n\t"
            "setc %0"
            : "=r" (result)
            : "m" (*Base), "r" (Bit)
            : "cc");
    return result;
}

static inline void __movsb(unsigned char *dst, const unsigned char *src, size_t count) {
    __asm__ volatile ("rep movsb"
            : "+D" (dst), "+S" (src), "+c" (count)
            :
            : "memory");
}

static inline void __movsw(unsigned short *dst, const unsigned short *src, size_t count) {
    __asm__ volatile ("rep movsw"
            : "+D" (dst), "+S" (src), "+c" (count)
            :
            : "memory");
}

static inline void __movsd(unsigned *dst, const unsigned *src, size_t count) {
    __asm__ volatile ("rep movsd"
            : "+D" (dst), "+S" (src), "+c" (count)
            :
            : "memory");
}

static inline void __movsq(unsigned long long *dst, const unsigned long long *src, size_t count) {
    __asm__ volatile ("rep movsq"
            : "+D" (dst), "+S" (src), "+c" (count)
            :
            : "memory");
}

static inline void __stosb(unsigned char *dst, unsigned char value, size_t count) {
    __asm__ volatile ("rep stosb"
            : "+D" (dst), "+c" (count)
            : "a" (value)
            : "memory");
}

static inline void __stosw(unsigned short *dst, unsigned short value, size_t count) {
    __asm__ volatile ("rep stosw"
            : "+D" (dst), "+c" (count)
            : "a" (value)
            : "memory");
}

static inline void __stosd(unsigned *dst, unsigned value, size_t count) {
    __asm__ volatile ("rep stosl"
            : "+D" (dst), "+c" (count)
            : "a" (value)
            : "memory");
}

static inline void __stosq(unsigned long long *dst, unsigned long long value, size_t count) {
    __asm__ volatile ("rep stosq"
            : "+D" (dst), "+c" (count)
            : "a" (value)
            : "memory");
}

static inline unsigned long long _umul128(unsigned long long a, unsigned long long b, unsigned long long *high) {
    unsigned long long low;
    __asm__ volatile ("mulq %3"
            : "=a" (low), "=d" (*high)
            : "a" (a), "r" (b)
            : "cc");
    return low;
}

static inline unsigned long long _udiv128(unsigned long long high, unsigned long long low, unsigned long long divisor, unsigned long long *remainder) {
    unsigned long long quotient;
    __asm__ volatile ("divq %4"
            : "=a" (quotient), "=d" (*remainder)
            : "d" (high), "a" (low), "r" (divisor)
            : "cc");
    return quotient;
}

static inline void __cpuid(int CPUInfo[4], int InfoType) {
    __asm__ volatile ("cpuid"
            : "=a" (CPUInfo[0]), "=b" (CPUInfo[1]), "=c" (CPUInfo[2]), "=d" (CPUInfo[3])
            : "a" (InfoType)
            : "cc");
}

static inline char _InterlockedCompareExchange128(
        volatile long long *Destination,
        long long ExchangeHigh, 
        long long ExchangeLow, 
        long long *Comparand
        ) {
    char success;
    
    __asm__ volatile ("lock cmpxchg16b %0"
            : "+m" (*Destination), "+a" (Comparand[0]), "+d" (Comparand[1]), "=c" (success)
            : "b" (ExchangeLow), "c" (ExchangeHigh)
            : "memory");
    
    return success;
}

#endif

//_____________________________________________________________________________________________________________________
// Misc Utilities

inline u64 xor_shift(u64 *number){
    u64 x = *number;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    *number = x;
    return x;
}

struct unicode_string{
    u16 length;
    u16 maximum_length;
    u32 _padding;
    u64 buffer;
};

struct guid{
    u32 Data1;
    u16 Data2;
    u16 Data3;
    u8  Data4[8];
};

#define PRINT_GUID_FORMAT "{%.8x-%.4x-%.4x-%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x}"
#define PRINT_GUID_MEMBERS(guid) (guid).Data1, (guid).Data2, (guid).Data3, (guid).Data4[0], (guid).Data4[1], (guid).Data4[2], (guid).Data4[3], (guid).Data4[4], (guid).Data4[5], (guid).Data4[6], (guid).Data4[7]

int g_always_answer_yes;

int yes_no_stop_point(char *message, int force){
    
    if(!force && g_always_answer_yes) return 1;
    
    while(true){
        print("%s (Y/N)\n", message);
        int yn = getchar();
        while(getchar() != '\n');
        if((yn|32) == 'n') return 0;
        if((yn|32) == 'y') return 1;
    }
    
    invalid_code_path();
}


typedef union align_type(16){
    u32 _u32[4];
    u8 _u8[16];
} m128;

// based loosly of wikipedia
static m128 hash_md5(u8 *data, smm initial_length){
    
    // Prepare the message:
    
    // message layout:
    // | original layout | (1 << 7) | pad zeroes | length of the message (64 bit) |
    // message bit-length has to be divisible by 512, or the message byte length  has to be divisible by 64
    smm length = (initial_length + 1 + 8 + 63) & ~63ull;
    
    u8 *msg = malloc(length);
    if(!msg){
        print("could not malloc for md5\n");
        _exit(1);
    }
    
    memcpy(msg, data, initial_length);
    memset(msg + initial_length, 0, length - initial_length);
    
    msg[initial_length] = (1 << 7); // only the top bit set
    
    smm bit_length = 8 * initial_length;
    memcpy(msg + length - 8, &bit_length, 8); // copy in the length
    
    // constant stuff:
    static const u32 shifts[] = {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    };
    
    // Use binary integer part of the sines of integers (in radians) as constants
    static const u32 sines[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
    };
    
    u32 hash_0 = 0x67452301;
    u32 hash_1 = 0xefcdab89;
    u32 hash_2 = 0x98badcfe;
    u32 hash_3 = 0x10325476;
    
    // go through in blocks of 512 bits or 64 bytes
    for(smm block_it = 0; block_it < length; block_it += 64){
        u8 *block = (msg + block_it);
        u32 *words = (u32 *)block;
        
        u32 block_hash_0 = hash_0;
        u32 block_hash_1 = hash_1;
        u32 block_hash_2 = hash_2;
        u32 block_hash_3 = hash_3;
        
        for(u32 i = 0; i < 64; i++){
            u32 mix;
            u32 word_index;
            
            if(i < 16){
                mix = block_hash_3 ^ (block_hash_1 & (block_hash_2 ^ block_hash_3));
                word_index = i;
            }else if(i < 32){
                mix = block_hash_2 ^ (block_hash_3 & (block_hash_1 ^ block_hash_2));
                word_index = (5 * i + 1) & 15;
            }else if(i < 48){
                mix = block_hash_1 ^ block_hash_2 ^ block_hash_3;
                word_index = (3 * i + 5) & 15;
            }else{
                mix = block_hash_2 ^ (block_hash_1 | (~block_hash_3));
                word_index = (7 * i) & 15;
            }
            
            u32 temp_hash = block_hash_3;
            block_hash_3 = block_hash_2;
            block_hash_2 = block_hash_1;
            
            u32 to_rotate = (block_hash_0 + mix + sines[i] + words[word_index]);
            u32 rotate_by = shifts[i];
            block_hash_1 = block_hash_1 + ((to_rotate << rotate_by) | (to_rotate >> (32 - rotate_by)));
            
            block_hash_0 = temp_hash;
        }
        
        hash_0 += block_hash_0;
        hash_1 += block_hash_1;
        hash_2 += block_hash_2;
        hash_3 += block_hash_3;
    }
    
    free(msg);
    
    m128 ret;
    ret._u32[0] = hash_0;
    ret._u32[1] = hash_1;
    ret._u32[2] = hash_2;
    ret._u32[3] = hash_3;
    return ret;
}

