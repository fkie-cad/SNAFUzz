// 
// This is a drag and drop service, that you can run inside of the vm,
// to allow dragging and dropping of files to the guest desktop.
// It uses a hacky special CPUID `CPUID_drag_and_drop`.
// To build this service simply use `cl drag_and_drop.c` and then to 
// auto start it, move the executable into the guests auto start folder
// 
//    C:\Users\<User Name>\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup
//    
// This only allows host to client copying of files.
// To get this executable into the guest either use an .iso (produced for example by oscdimg),
// or use drag and drop supported by Hyper-V "extended session".
// 
//                                                        - Pascal Beyer 04.04.2025
// 


#include <windows.h>
#include <intrin.h>
#include <shlobj.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment(lib, "Shell32")
#pragma comment(lib, "User32")

typedef unsigned char    u8;
typedef unsigned short   u16;
typedef unsigned int     u32;
typedef unsigned __int64 u64;

#define print(...) (printf(__VA_ARGS__), fflush(0))


#include "src/uefi_bios.h"


#define ID_TRAY_EXIT      1001
NOTIFYICONDATA nid;

void TrayMessage(PSTR Title, PSTR Format, ...){
    
    va_list va;
    va_start(va, Format);
    
    CHAR Info[0x100];
    _vsnprintf(Info, sizeof(Info)/sizeof(*Info), Format, va);
    
    va_end(va);
    
    strcpy_s(nid.szInfo, sizeof(nid.szInfo), Info);
    strcpy_s(nid.szInfoTitle, sizeof(nid.szInfoTitle), Title);
    Shell_NotifyIcon(NIM_MODIFY, &nid);
}

__declspec(noinline) void cause_vmexit(u32 code, void *rdx){
    (void)rdx;
    int cpuinfo[4]; // ignored for now.
    __cpuid(cpuinfo, code);
}

int DragAndDropThread(void *unused){
    
    SIZE_T MinimumWorkingSetSize;
    SIZE_T MaximumWorkingSetSize;
    BOOL GetProcessWorkingSetSizeSuccess = GetProcessWorkingSetSize(GetCurrentProcess(), &MinimumWorkingSetSize, &MaximumWorkingSetSize);
    if(!GetProcessWorkingSetSizeSuccess){
        print("Failed to get Working set size.\n");
    }
    
    while(1){
        struct cpuid_drag_and_drop_input_buffer input_buffer = {0};
        
        cause_vmexit(CPUID_drag_and_drop, &input_buffer);
        
        if(input_buffer.file_name_size == 0){
            // No pending file.
            Sleep(1000);
            continue;
        }
        
        u64 allocation_size = input_buffer.file_name_size + 1 + input_buffer.file_size;
        char *data = VirtualAlloc(0, allocation_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        
        input_buffer.file_name = data;
        data[input_buffer.file_name_size] = 0;
        input_buffer.file_data = data + input_buffer.file_name_size + 1;
        
        
        BOOL VirtualLockSuccess = VirtualLock(data, allocation_size);
        while(!VirtualLockSuccess){
            MinimumWorkingSetSize *= 2;
            MaximumWorkingSetSize *= 2;
            
            BOOL SetProcessWorkingSetSizeSuccess = SetProcessWorkingSetSize(GetCurrentProcess(), MinimumWorkingSetSize, MaximumWorkingSetSize);
            if(!SetProcessWorkingSetSizeSuccess){
                TrayMessage("Drag And Drop Error", "Failed to set WorkingSetSize to %llx\n", MaximumWorkingSetSize);
                exit(1);
            }
            
            VirtualLockSuccess = VirtualLock(data, allocation_size);
        }
        
        cause_vmexit(CPUID_drag_and_drop, &input_buffer);
        
        BOOL VirtualUnLockSuccess = VirtualUnlock(data, allocation_size);
        if(!VirtualUnLockSuccess){
            print("VirtualUnLock failed %u\n", GetLastError());
        }
        
        PWSTR path = NULL;
        if(!SUCCEEDED(SHGetKnownFolderPath(&FOLDERID_Desktop, 0, NULL, &path))){
            TrayMessage("Drag And Drop Error", "Failed to get Desktop path.\n");
            VirtualFree(data, 0, MEM_RELEASE);
            continue;
        }
        
        char file_path_buffer[MAX_PATH];
        snprintf(file_path_buffer, sizeof(file_path_buffer), "%ws\\%.*s", path, (int)input_buffer.file_name_size, input_buffer.file_name);
        
        FILE *file = fopen(file_path_buffer, "wb");
        if(!file){
            TrayMessage("Drag And Drop Error", "Failed to open file %s\n", file_path_buffer);
            VirtualFree(data, 0, MEM_RELEASE);
            continue;
        }
        
        fwrite(input_buffer.file_data, input_buffer.file_size, 1, file);
        fclose(file);
        
        TrayMessage("Drag And Drop", "%s\n", file_path_buffer);
        
        VirtualFree(data, 0, MEM_RELEASE);
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    
    switch(uMsg){
        case WM_APP + 1:{
            if(lParam == WM_RBUTTONDOWN){
                POINT pt;
                GetCursorPos(&pt);
                
                HMENU hMenu = CreatePopupMenu();
                InsertMenu(hMenu, 0, MF_BYPOSITION | MF_STRING, ID_TRAY_EXIT, "Exit");
                
                SetForegroundWindow(hwnd);
                TrackPopupMenu(hMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0, hwnd, NULL);
                DestroyMenu(hMenu);
            }
        }break;
        
        case WM_COMMAND:{
            int id = LOWORD(wParam);
            
            if(id == ID_TRAY_EXIT){
                Shell_NotifyIcon(NIM_DELETE, &nid);
                PostQuitMessage(0);
            }
        }break;
        
        case WM_DESTROY:{ // @cleanup: Not sure if this is ever called...
            PostQuitMessage(0);
        }break;
        
        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    
    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[]  = "VM Drag and Drop Window Class";
    
    WNDCLASS wc = {};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    
    RegisterClass(&wc);
    
    HWND hwnd = CreateWindowEx(
            0,
            CLASS_NAME,
            "Drag and Drop",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            NULL,
            NULL,
            hInstance,
            NULL
            );
    
    if(hwnd == NULL) return 0;
    
    
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO | NIF_REALTIME;
    nid.uTimeout = 1000;
    nid.uCallbackMessage = WM_APP + 1;
    nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    nid.dwInfoFlags = NIIF_INFO | NIIF_NOSOUND;
    strcpy_s(nid.szTip, sizeof(nid.szTip), "Drag and Drop");
    strcpy_s(nid.szInfo, sizeof(nid.szInfo), "You can now Drag and Drop files to the desktop.");
    strcpy_s(nid.szInfoTitle, sizeof(nid.szInfoTitle), "Started App:");
    Shell_NotifyIcon(NIM_ADD, &nid);
    
    CreateThread(NULL, 0, DragAndDropThread, NULL, 0, NULL);
    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int) msg.wParam;
}

