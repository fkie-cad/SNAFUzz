// 
// Kernel snapshot helper for the 'default_target.c'. Compile using 'cl kernel_snapshot.c'.
// Set a breakpoint on 'nt!NtSetInformationTransactionManager' 
// and execute 'kernel_snapshot.exe' on the Virtual Machine.
// When the breakpoint hits, take a snapshot.
//                                               - Pascal Beyer 13.08.2024

#include <stdio.h>
#include <windows.h>
#include <winternl.h>

#pragma comment(lib, "ntdll.lib")

// @note: Intentionally wrong signature. The 'default_target.c' will read the arguments.
__declspec(dllimport) void NtSetInformationTransactionManager(void *Page1, void *Page2, void *Page3, void *Page4);

int main(int argc, char *argv[]){
    
    // 
    // Set our priority class to real time.
    // 
    SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
    
    void *PageOne   = VirtualAlloc(NULL, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    void *PageTwo   = VirtualAlloc(NULL, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    void *PageThree = VirtualAlloc(NULL, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    void *PageFour  = VirtualAlloc(NULL, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    // 
    // Make sure the pages are paged in.
    // 
    *(int *)PageOne   = 1;
    *(int *)PageTwo   = 2;
    *(int *)PageThree = 3;
    *(int *)PageFour  = 4;
    
    // 
    // Hand over to the emulator.
    // 
    NtSetInformationTransactionManager(PageOne, PageTwo, PageThree, PageFour);
}

