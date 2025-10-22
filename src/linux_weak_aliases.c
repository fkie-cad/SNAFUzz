// 
// This is just a hacky compilation unit because I could not figure out how to have
// weak aliases (for overwritable default definitions) on linux without adding another
// compilation unit.
// 

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;
typedef long long s64;

struct context;

struct input{
    u8 *data;
    s64 size;
};

struct input target_get_input__default(struct context *context, u64 *seed);
void target_reset__default(struct context *context);
int target_read_guest_input_buffer__default(struct context *context, u64 virtual_address, u8 *buffer, u64 size);


struct input target_get_input__default_weak(struct context *context, u64 *seed){
    return target_get_input__default(context, seed);
}
void target_reset__default_weak(struct context *context){
    target_reset__default(context);
}
int target_read_guest_input_buffer__default_weak(struct context *context, u64 virtual_address, u8 *buffer, u64 size){
    return target_read_guest_input_buffer__default(context, virtual_address, buffer, size);
}

struct input target_get_input(struct context *context, u64 *seed) __attribute__((weak, alias("target_get_input__default_weak")));
void target_reset(struct context *context) __attribute__((weak, alias("target_reset__default_weak")));
int target_read_guest_input_buffer(struct context *context, u64 virtual_address, u8 *buffer, u64 size) __attribute__((weak, alias("target_read_guest_input_buffer__default_weak")));
