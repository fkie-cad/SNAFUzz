
//
// Hacky Display to show the 'frame_buffer'.
//
// This creates a windows which has a client size of 1024 x 768,
// and continuously renders the 'frame_buffer' into it at 60fps.
// It also forwards keyboard and mouse events into some globals
// which can then be used by the hypervisor to implement mouse 
// and keyboard events (see 'hacky_display_input_handling').
// 
// Furthermore, timer events are communicated through
// 'next_timer_interrupt_time_or_zero' and invoked by calling
// 'cancel_virtual_processor'.
// 
// Finally, a CTRL-C handler is registered to allow the user
// to break in the debugger at will. This is communicated 
// through 'snapshot_mode_should_break_in_debugger'.
// 
//                                  - Pascal Beyer 16.02.2024
//


#define HACKY_EXTERN
#include "hacky_display.h"


#define false 0
#define true  1
#define array_count(a) (sizeof(a)/sizeof(*(a)))


#if _WIN32

#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <windows.h>
#include <shellapi.h>

// #include "options.c"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "shell32.lib")

static int left_mouse_down;
static int right_mouse_down;
static int mouse_z_delta;

static void hacky_mouse_event(enum hacky_event_kind kind, LPARAM LParam){
    
    // "The low-order word specifies the x-coordinate of the cursor.
    //  The coordinate is relative to the upper-left corner of the client area."
    short x = (short)(LParam >>  0);
    
    // "The high-order word specifies the y-coordinate of the cursor. 
    //  The coordinate is relative to the upper-left corner of the client area."
    short y = (short)(LParam >> 16);
    
    //
    // Map from [0, 1023] x [0, 767] to [0, 0x7fff] x [0, 0x7fff].
    //
    double x_zero_to_one = (double)x / (double)(WINDOW_WIDTH  - 1);
    double y_zero_to_one = (double)y / (double)(WINDOW_HEIGHT - 1);
    
    short mouse_x = (short)(x_zero_to_one * 0x7fff);
    short mouse_y = (short)(y_zero_to_one * 0x7fff);
    
    if(kind == HACKY_EVENT_mouse_move && events_processed != events_initiated){
        
        // 
        // Attempt to "merge" mouse_move events.
        // 
        int index = (events_initiated-1) % array_count(event_buffer);
        
        if(event_buffer[index].kind == HACKY_EVENT_mouse_move){
            event_buffer[index].mouse_x = mouse_x;
            event_buffer[index].mouse_y = mouse_y;
            
            // After patching, check that we have not processed the event in the middle.
            if(events_processed != events_initiated) return;
        }
    }
    
    int index = events_initiated % array_count(event_buffer);
    
    event_buffer[index].kind = kind;
    event_buffer[index].button = left_mouse_down | (right_mouse_down << 1);
    event_buffer[index].mouse_x = mouse_x;
    event_buffer[index].mouse_y = mouse_y;
    event_buffer[index].wheel = mouse_z_delta;
    
    mouse_z_delta = 0;
    
    events_initiated += 1;
}

LRESULT CALLBACK WindowCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam){
    LRESULT Result = 0;
    
    switch(Message){
        case WM_DESTROY:
        case WM_CLOSE:{
            Running = false;
        }break;
        
        case WM_LBUTTONDOWN:{
            hacky_mouse_event(HACKY_EVENT_mouse_move, LParam);
            left_mouse_down = 1;
            hacky_mouse_event(HACKY_EVENT_mouse_event, LParam);
        }break;
        
        case WM_LBUTTONUP:{
            hacky_mouse_event(HACKY_EVENT_mouse_move, LParam);
            left_mouse_down = 0;
            hacky_mouse_event(HACKY_EVENT_mouse_event, LParam);
        }break;
        
        case WM_RBUTTONDOWN:{
            hacky_mouse_event(HACKY_EVENT_mouse_move, LParam);
            right_mouse_down = 1;
            hacky_mouse_event(HACKY_EVENT_mouse_event, LParam);
        }break;
        
        case WM_RBUTTONUP:{
            hacky_mouse_event(HACKY_EVENT_mouse_move, LParam);
            right_mouse_down = 0;
            hacky_mouse_event(HACKY_EVENT_mouse_event, LParam);
        }break;
        
        case WM_MOUSEWHEEL:{
            hacky_mouse_event(HACKY_EVENT_mouse_move, LParam);
            mouse_z_delta = GET_WHEEL_DELTA_WPARAM(WParam) / WHEEL_DELTA;
            hacky_mouse_event(HACKY_EVENT_mouse_event, LParam);
        }break;
        
        case WM_MOUSEMOVE:{
            hacky_mouse_event(HACKY_EVENT_mouse_move, LParam);
        }break;
        
        case WM_SYSKEYUP:
        case WM_KEYUP:
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:{
            
            //
            // @note: PS/2 Scan Code map for US QWERTY keyboard. (Scan Code Set 1)
            //        https://wiki.osdev.org/PS/2_Keyboard
            //
            static unsigned short scan_code_map[] = {
                [VK_ESCAPE] = 0x01, //  escape pressed
                ['1'] = 0x02, //  1 pressed
                ['2'] = 0x03, //  2 pressed
                ['3'] = 0x04, // 3 pressed
                ['4'] = 0x05, // 4 pressed
                ['5'] = 0x06, // 5 pressed
                ['6'] = 0x07, // 6 pressed
                
                ['7'] = 0x08, // 7 pressed
                ['8'] = 0x09, // 8 pressed
                ['9'] = 0x0A, // 9 pressed
                ['0'] = 0x0B, // 0 (zero) pressed
                
                [VK_OEM_MINUS] = 0x0C, // - pressed
                [VK_OEM_PLUS] = 0x0D, // = pressed
                [VK_BACK] = 0x0E, // backspace pressed
                [VK_TAB]  = 0x0F, // tab pressed
                        
                ['Q'] = 0x10, // Q pressed
                ['W'] = 0x11, // W pressed
                ['E'] = 0x12, // E pressed
                ['R'] = 0x13, // R pressed
                        
                ['T'] = 0x14, // T pressed
                ['Y'] = 0x15, // Y pressed
                ['U'] = 0x16, // U pressed
                ['I'] = 0x17, // I pressed
                        
                ['O'] = 0x18, // O pressed
                ['P'] = 0x19, // P pressed
                [VK_OEM_4] = 0x1A, // [ pressed
                [VK_OEM_6] = 0x1B, // ] pressed
                        
                [VK_RETURN] = 0x1C, // enter pressed
                [VK_LCONTROL] = 0x1D, // left control pressed
                [VK_CONTROL] = 0x1D, // left control pressed
                ['A'] = 0x1E, // A pressed
                ['S'] = 0x1F, // S pressed
                        
                ['D'] = 0x20, // D pressed
                ['F'] = 0x21, // F pressed
                ['G'] = 0x22, // G pressed
                ['H'] = 0x23, // H pressed
                        
                ['J'] = 0x24, // J pressed
                ['K'] = 0x25, // K pressed
                ['L'] = 0x26, // L pressed
                [VK_OEM_1] = 0x27, //  ; pressed
                
                [VK_OEM_7] = 0x28, // ' (single quote) pressed
                // 0x29, // ` (back tick) pressed
                [VK_LSHIFT] = 0x2A, // left shift pressed
                [VK_SHIFT] = 0x2A, // left shift pressed
                [VK_OEM_5] = 0x2B, // \ pressed
                
                ['Z'] = 0x2C, // Z pressed
                ['X'] = 0x2D, // X pressed
                ['C'] = 0x2E, // C pressed
                ['V'] = 0x2F, // V pressed
                
                ['B'] = 0x30, // B pressed
                ['N'] = 0x31, // N pressed
                ['M'] = 0x32, // M pressed
                [VK_OEM_COMMA] = 0x33, // , pressed
                
                [VK_OEM_PERIOD] = 0x34, // . pressed
                [VK_OEM_2] = 0x35, // / pressed
                [VK_RSHIFT] = 0x36, // right shift pressed
                // 0x37, // (keypad) * pressed
                
                // 0x38, // left alt pressed
                [VK_SPACE] = 0x39, // space pressed
                [VK_CAPITAL] = 0x3A, // CapsLock pressed
                [VK_F1] = 0x3B, // F1 pressed
                
                [VK_F2] = 0x3C, // F2 pressed
                [VK_F3] = 0x3D, // F3 pressed
                [VK_F4] = 0x3E, // F4 pressed
                [VK_F5] = 0x3F, // F5 pressed
                
                [VK_F6] = 0x40, // F6 pressed
                [VK_F7] = 0x41, // F7 pressed
                [VK_F8] = 0x42, // F8 pressed
                [VK_F9] = 0x43, // F9 pressed
                
                [VK_F10] = 0x44, // F10 pressed
                
                [VK_F11] = 0x57, //  F11 pressed
                
                // @note: These have the IS_E0 bit set (4 << 8).
                [VK_UP]     = 0x0448, // cursor up pressed
                [VK_PRIOR]  = 0x0449, // page up pressed
                [VK_LEFT]   = 0x044B, // cursor left pressed
                [VK_RIGHT]  = 0x044D, // cursor right pressed
                [VK_END]    = 0x044F, // end pressed
                [VK_DOWN]   = 0x0450, // cursor down pressed
                [VK_NEXT]   = 0x0451, // page down pressed
                [VK_INSERT] = 0x0452, // insert pressed
                [VK_DELETE] = 0x0453, // delete pressed
                
            };
            
            unsigned short scan_code = WParam < sizeof(scan_code_map) ? scan_code_map[WParam] : 0;
            
            if(scan_code != 0){
                int index = events_initiated;
                
                // Transition state.
                if(LParam & 1u << 31) scan_code |= (/* IS_BREAK */2 << 8);
                
                event_buffer[index % array_count(event_buffer)] = (struct hacky_event){
                    .kind = HACKY_EVENT_key_event,
                    .keycode = scan_code,
                };
                events_initiated++;
            }
        }break;
        
        case WM_DROPFILES:{
            HDROP drop =  (HDROP)WParam;
            
            //
            // Using 'DragQueryFileA' with 'file_index == 0xFFFFFFFF' it returns the amount of files dropped.
            //
            UINT amount_of_file_paths = DragQueryFileA(drop, 0xFFFFFFFF, NULL, 0);
            
            for(UINT file_index = 0; file_index < amount_of_file_paths; file_index++){
                //
                // Using 'DragQueryFileA' with returns the file path.
                //
                
                if(drag_and_drops_initiated + 1 < drag_and_drops_processed + array_count(drag_and_drop_files)){
                    int index = drag_and_drops_initiated++ % array_count(drag_and_drop_files);
                    DragQueryFileA(drop, file_index, drag_and_drop_files[index].file_path, sizeof(drag_and_drop_files[index].file_path));
                }
            }
            
            DragFinish(drop);
        }break;
        
        case WM_PAINT:{
            PAINTSTRUCT Paint;
            BeginPaint(Window, &Paint);
            EndPaint(Window, &Paint);
        }break;
        
        default:{
            Result = DefWindowProc(Window, Message, WParam, LParam);
        }break;
    }
    return Result;
}

BOOL ControlHandlerRoutine(DWORD dwCtrlType){
    
    if(dwCtrlType != CTRL_C_EVENT) return FALSE;
    
    // 
    // First Ctrl-C breaks, second one terminates the application.
    // 
    if(snapshot_mode_currently_in_debugger) return FALSE;
    snapshot_mode_should_break_in_debugger = 1;
    
    return TRUE;
}

unsigned initialize_hacky_display(void *unused){
    (void)unused;
    
    SetConsoleCtrlHandler(ControlHandlerRoutine, TRUE);
    
    LONG Width  = WINDOW_WIDTH;
    LONG Height = WINDOW_HEIGHT;
    
    BITMAPINFO BitmapInfo = {
        .bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader),
        .bmiHeader.biWidth = Width,
        .bmiHeader.biHeight = -Height,
        .bmiHeader.biPlanes = 1,
        .bmiHeader.biBitCount = 32,
        .bmiHeader.biCompression = BI_RGB,
    };
    
    HINSTANCE Instance = GetModuleHandle(NULL);
    
    WNDCLASS WindowClass = {
        .lpfnWndProc = WindowCallback,
        .hInstance   = Instance,
        .lpszClassName = "WindowClass",
    };
    
    if(!RegisterClassA(&WindowClass)){
        printf("[initialize_hacky_display] Could not RegisterClassA.\n");
        return 0;
    }
    
    RECT WindowRect = {
        .right  = Width,
        .bottom = Height,
    };
    
    if(!AdjustWindowRectEx(&WindowRect, WS_OVERLAPPEDWINDOW, 0, 0)){
        printf("[initialize_hacky_display] Could not AdjustWindowRectEx.\n");
        return 0;
    }
    
    HWND WindowHandle =
            CreateWindowExA(0, WindowClass.lpszClassName,
            "Hacky Display",
            WS_OVERLAPPEDWINDOW|WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            WindowRect.right  - WindowRect.left,
            WindowRect.bottom - WindowRect.top,
            0, 0, Instance, 0);
    
    
    if(!WindowHandle){
        printf("[initialize_hacky_display] Could not CreateWindowExA.\n");
        return 0;
    }
    
    //
    // Enable dropped files.
    //
    DragAcceptFiles(WindowHandle, 1);
    
    Running = true;
    
    HDC DeviceContext = GetDC(WindowHandle);
    
    while(Running){
        
        MSG Message;
        BOOL MessageResult = PeekMessageA(&Message, WindowHandle, 0, 0, PM_REMOVE);
        
        while(MessageResult > 0){
            TranslateMessage(&Message);
            DispatchMessageA(&Message);
            
            MessageResult = PeekMessageA(&Message, WindowHandle, 0, 0, PM_REMOVE);
        }
        
        StretchDIBits(DeviceContext,
                0, 0, Width, Height,
                0, 0, Width, Height,
                frame_buffer,
                &BitmapInfo,
                DIB_RGB_COLORS, SRCCOPY);
        
        // Cancel the hypervisor, so that it can check whether or not it should issue a timer interrupt
        // or input event.
        cancel_virtual_processor();
        
        Sleep(16);
    }
    
    // Exit the program if the user closes the window.
    _exit(1);
    
    return 0;
}


#else 

// Linux.

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>


static int left_mouse_down;
static int right_mouse_down;
static int mouse_z_delta;

static void hacky_mouse_event(enum hacky_event_kind kind, int x, int y){
    
    //
    // Map from [0, 1023] x [0, 767] to [0, 0x7fff] x [0, 0x7fff].
    //
    double x_zero_to_one = (double)x / (double)(WINDOW_WIDTH  - 1);
    double y_zero_to_one = (double)y / (double)(WINDOW_HEIGHT - 1);
    
    short mouse_x = (short)(x_zero_to_one * 0x7fff);
    short mouse_y = (short)(y_zero_to_one * 0x7fff);
    
    if(kind == HACKY_EVENT_mouse_move && events_processed != events_initiated){
        
        // 
        // Attempt to "merge" mouse_move events.
        // 
        int index = (events_initiated-1) % array_count(event_buffer);
        
        if(event_buffer[index].kind == HACKY_EVENT_mouse_move){
            event_buffer[index].mouse_x = mouse_x;
            event_buffer[index].mouse_y = mouse_y;
            
            // After patching, check that we have not processed the event in the middle.
            if(events_processed != events_initiated) return;
        }
    }
    
    int index = events_initiated % array_count(event_buffer);
    
    event_buffer[index].kind = kind;
    event_buffer[index].button = left_mouse_down | (right_mouse_down << 1);
    event_buffer[index].mouse_x = mouse_x;
    event_buffer[index].mouse_y = mouse_y;
    event_buffer[index].wheel = mouse_z_delta;
    
    mouse_z_delta = 0;
    
    events_initiated += 1;
}


void sigint_handler(int sig){
    (void)sig;
    
    // 
    // First Ctrl-C breaks, second one terminates the application.
    // 
    if(snapshot_mode_currently_in_debugger){
        exit(1);
        return;
    }
    
    snapshot_mode_should_break_in_debugger = 1;
}

void handle_events(Display *display, Window window) {
    XEvent event;
    while (XPending(display)) {
        XNextEvent(display, &event);
        
        switch(event.type){
            case DestroyNotify:{
                Running = false;
            }break;
            
            
            case MotionNotify:{
                hacky_mouse_event(HACKY_EVENT_mouse_move, event.xmotion.x, event.xmotion.y);
            }break;
            
            
            case ButtonPress:{
                hacky_mouse_event(HACKY_EVENT_mouse_move, event.xbutton.x, event.xbutton.y);
                if(event.xbutton.button == Button1){
                    left_mouse_down = 1;
                }else if(event.xbutton.button == Button2){
                    right_mouse_down = 1;
                }
                hacky_mouse_event(HACKY_EVENT_mouse_event, event.xbutton.x, event.xbutton.y);
            }break;
            
            case ButtonRelease:{
                hacky_mouse_event(HACKY_EVENT_mouse_move, event.xbutton.x, event.xbutton.y);
                if(event.xbutton.button == Button1){
                    left_mouse_down = 0;
                }else if(event.xbutton.button == Button2){
                    right_mouse_down = 0;
                }
                hacky_mouse_event(HACKY_EVENT_mouse_event, event.xbutton.x, event.xbutton.y);
            }break;
            
            
            case KeyPress:
            case KeyRelease:{
                
                // https://codebrowser.dev/kde/include/X11/keysymdef.h.html
                // and https://wiki.osdev.org/PS/2_Keyboard
                
                static unsigned short scan_code_map[] = {
                    [XK_Escape] = 0x01, //  escape pressed
                    [XK_1] = 0x02, //  1 pressed
                    [XK_2] = 0x03, //  2 pressed
                    [XK_3] = 0x04, // 3 pressed
                    [XK_4] = 0x05, // 4 pressed
                    [XK_5] = 0x06, // 5 pressed
                    [XK_6] = 0x07, // 6 pressed
                    
                    [XK_7] = 0x08, // 7 pressed
                    [XK_8] = 0x09, // 8 pressed
                    [XK_9] = 0x0A, // 9 pressed
                    [XK_0] = 0x0B, // 0 (zero) pressed
                    
                    [XK_minus] = 0x0C, // - pressed
                    // [] = 0x0D, // = pressed
                    [XK_BackSpace] = 0x0E, // backspace pressed
                    [XK_Tab]  = 0x0F, // tab pressed
                    
                    [XK_q] = 0x10, // Q pressed
                    [XK_w] = 0x11, // W pressed
                    [XK_e] = 0x12, // E pressed
                    [XK_r] = 0x13, // R pressed
                    
                    [XK_t] = 0x14, // T pressed
                    [XK_y] = 0x15, // Y pressed
                    [XK_u] = 0x16, // U pressed
                    [XK_i] = 0x17, // I pressed
                    
                    [XK_o] = 0x18, // O pressed
                    [XK_p] = 0x19, // P pressed
                    // [VK_OEM_4] = 0x1A, // [ pressed
                    // [VK_OEM_6] = 0x1B, // ] pressed
                    
                    [XK_Return] = 0x1C, // enter pressed
                    [XK_Control_L] = 0x1D, // left control pressed
                    [XK_Control_R] = 0x1D, // left control pressed (?)
                    [XK_a] = 0x1E, // A pressed
                    [XK_s] = 0x1F, // S pressed
                    
                    [XK_d] = 0x20, // D pressed
                    [XK_f] = 0x21, // F pressed
                    [XK_g] = 0x22, // G pressed
                    [XK_h] = 0x23, // H pressed
                    
                    [XK_j] = 0x24, // J pressed
                    [XK_k] = 0x25, // K pressed
                    [XK_l] = 0x26, // L pressed
                    // [VK_OEM_1] = 0x27, //  ; pressed
                    
                    // [VK_OEM_7] = 0x28, // ' (single quote) pressed
                    // 0x29, // ` (back tick) pressed
                    [XK_Shift_L] = 0x2A, // left shift pressed
                    [XK_Shift_R] = 0x2A, // left shift pressed (?)
                    // [VK_OEM_5] = 0x2B, // \ pressed
                    
                    [XK_z] = 0x2C, // Z pressed
                    [XK_x] = 0x2D, // X pressed
                    [XK_c] = 0x2E, // C pressed
                    [XK_v] = 0x2F, // V pressed
                    
                    [XK_b] = 0x30, // B pressed
                    [XK_n] = 0x31, // N pressed
                    [XK_m] = 0x32, // M pressed
                    // [VK_OEM_COMMA] = 0x33, // , pressed
                    
                    // [VK_OEM_PERIOD] = 0x34, // . pressed
                    // [VK_OEM_2] = 0x35, // / pressed
                    // [VK_RSHIFT] = 0x36, // right shift pressed
                    // 0x37, // (keypad) * pressed
                    
                    // 0x38, // left alt pressed
                    [XK_space] = 0x39, // space pressed
                    [XK_Caps_Lock] = 0x3A, // CapsLock pressed
                    
                    [XK_F1] = 0x3B, // F1 pressed
                    
                    [XK_F2] = 0x3C, // F2 pressed
                    [XK_F3] = 0x3D, // F3 pressed
                    [XK_F4] = 0x3E, // F4 pressed
                    [XK_F5] = 0x3F, // F5 pressed
                    
                    [XK_F6] = 0x40, // F6 pressed
                    [XK_F7] = 0x41, // F7 pressed
                    [XK_F8] = 0x42, // F8 pressed
                    [XK_F9] = 0x43, // F9 pressed
                    
                    [XK_F10] = 0x44, // F10 pressed
                    
                    [XK_F11] = 0x57, //  F11 pressed
                    
                    // @note: These have the IS_E0 bit set (4 << 8).
                    [XK_Up]     = 0x0448, // cursor up pressed
                    [XK_Page_Up]  = 0x0449, // page up pressed
                    [XK_Left]   = 0x044B, // cursor left pressed
                    [XK_Right]  = 0x044D, // cursor right pressed
                    [XK_End]    = 0x044F, // end pressed
                    [XK_Down]   = 0x0450, // cursor down pressed
                    [XK_Page_Down]   = 0x0451, // page down pressed
                    [XK_Insert] = 0x0452, // insert pressed
                    [XK_Delete] = 0x0453, // delete pressed
                    
                };
                
                unsigned short keysym = XKeycodeToKeysym(display, event.xkey.keycode, 0);
                unsigned short scan_code = scan_code_map[keysym];
                
                if(scan_code != 0){
                    int index = events_initiated;
                    
                    if(event.type == KeyRelease) scan_code |= (/* IS_BREAK */2 << 8);
                    
                    event_buffer[index % array_count(event_buffer)] = (struct hacky_event){
                        .kind = HACKY_EVENT_key_event,
                        .keycode = scan_code,
                    };
                    events_initiated++;
                }
                
            }break;
        }
    }
}

void *initialize_hacky_display(void *unused){
    (void)unused;
    
    signal(SIGINT, sigint_handler);
    
    // Open connection to X server.
    Display *display = XOpenDisplay(NULL);
    if (!display) {
        printf("[initialize_hacky_display] Could not open X display.\n");
        return 0;
    }
    
    int screen = DefaultScreen(display);
    Window root = RootWindow(display, screen);
    
    // Create the window.
    Window window = XCreateSimpleWindow(display, root, 
            0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 
            1, BlackPixel(display, screen), WhitePixel(display, screen));
    
    // Select input events (so we can detect close events).
    XSelectInput(display, window, StructureNotifyMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask);
    
    // Create a graphics context.
    GC gc = XCreateGC(display, window, 0, NULL);
    
    // Show the window.
    XMapWindow(display, window);
    
    // Create an XImage to render framebuffer.
    XImage *image = XCreateImage(display, DefaultVisual(display, screen), DefaultDepth(display, screen), 
            ZPixmap, 0, (char*)frame_buffer, WINDOW_WIDTH, WINDOW_HEIGHT, 32, 0);
    
    // Wait for the MapNotify event (ensures window is displayed)
    XEvent event;
    do {
        XNextEvent(display, &event);
    } while (event.type != MapNotify);
    
    
    Running = true;
    
    while (Running) {
        
        handle_events(display, window);
        
        // Render frame buffer to window.
        XPutImage(display, window, gc, image, 0, 0, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        
        // Cancel the hypervisor, so that it can check whether or not it should issue a timer interrupt
        // or input event.
        cancel_virtual_processor();
        
        usleep(16 * 1000); // Sleep ~16ms to cap at ~60 FPS
    }
    
    XDestroyImage(image);
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
    
    _exit(1);
    
    return 0;
}


#endif
