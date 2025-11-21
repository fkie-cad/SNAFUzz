
#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 768

extern double os_get_time_in_seconds(void);
extern void cancel_virtual_processor(void);

static int Running;
extern unsigned frame_buffer[1024 * 768];

HACKY_EXTERN volatile int events_processed;
HACKY_EXTERN volatile int events_initiated;

HACKY_EXTERN volatile int snapshot_mode_should_break_in_debugger;
HACKY_EXTERN volatile int snapshot_mode_currently_in_debugger;

HACKY_EXTERN struct hacky_event{
    enum hacky_event_kind{
        HACKY_EVENT_key_none,
        
        HACKY_EVENT_key_event,
        HACKY_EVENT_mouse_event,
        HACKY_EVENT_mouse_move,
    } kind;
    union{
        unsigned short keycode;
        struct{
            char button;
            char wheel;
            unsigned short mouse_x;
            unsigned short mouse_y;
        };
    };
} event_buffer[0x100];


HACKY_EXTERN volatile int drag_and_drops_processed;
HACKY_EXTERN volatile int drag_and_drops_initiated;

HACKY_EXTERN struct hacky_drag_and_drop_files{
    char file_path[/*MAX_PATH*/260];
} drag_and_drop_files[0x10];

