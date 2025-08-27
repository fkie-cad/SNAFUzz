// 
// This `user_snapshot` utility contains a small "debugger",
// i.e. a program that uses the Windows Debugger Api's, 
// that has the following command line:
// 
//     user_snapshot.exe <breakpoint offset> -- <target commandline>
//     
// To build the user_snapshot.exe simply use `cl user_snapshot.c`.
// The `user_snapshot.exe` is then supposed to be run inside of the guest.
// 
// `user_snapshot.exe` starts up a process with the target commandline
// and sets a breakpoint on the main executable plus the breakpoint offset.
// It does so using a software breakpoint and then runs the process.
// 
// The builtin debugger of snafuzz ignores software breakpoints, 
// therefore once the breakpoint is hit, this `user_snapshot.exe` utility
// will get notified.
// 
// It will then lock the entire guest virtual address space of the process
// and cause a hardware breakpoint, that snafuzz recognizes and breaks 
// in its builtin debugger.
// 
// From here, you can use the builtin debugger, to take a snapshot of the
// target.
// 
// If your target is simple enough that you simply have an `input_buffer`
// and an `input_size`, that need to get mutated, the snapshot can then 
// potentially be used with the `default_target.c`. 
// For user space applications, the `default_target.c` has the following command line:
// 
//     snafuzz.exe fuzz.snapshot -- -buffer <input_buffer> -size <input_size> [-corpus <directory>] [-no_loop]
// 
// If you need something more sophisticated for your target,
// also see the target-specific code in `HeaderParser.c`.
// There I describe how to fuzz a user-space application in more detail.
// 
//                                            - Pascal Beyer 27.08.2025

// 
// In the future, this should probably be _more_ of a real debugger, 
// so potentially use the DbgHelp API's to be able to resolve an address
// like `headerParser!parseHeader` instead of having to pass an offset.
// The problem with this is that the guest does not have internet and thus
// cannot download the PDB's. Hmm...
// 
// Also maybe it should start per default on the main function 
// or the entry point somehow.
// 

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#include <windows.h>
#include <psapi.h>

#pragma comment(lib, "ntdll.lib")

NTSYSAPI NTSTATUS NTAPI NtLockVirtualMemory(
        IN HANDLE               ProcessHandle,
        IN PVOID                *BaseAddress,
        IN OUT PSIZE_T           NumberOfBytesToLock,
        IN ULONG                LockOption );


void print(char *format, ...){
    va_list va;
    va_start(va, format);
    int ret = vprintf(format, va);
    va_end(va);
    fflush(0);
}

int main(int argc, char *argv[]){
    
    char *CommandLine = GetCommandLineA();
    char *TargetCommandLine = strstr(CommandLine, "-- ") + 3;
    
    if(!TargetCommandLine || argc < 2){
        print("Usage: %s <breakpoint offset> -- <target command line>\n", argv[0]);
        return 0;
    }
    
    DWORD64 Offset = strtoull(argv[1], NULL, 0);
    
    STARTUPINFO TargetStartupInformation = {.cb = sizeof(TargetStartupInformation) };
    PROCESS_INFORMATION TargetProcessInformation;
    BOOL CreateProcessSuccess = CreateProcessA(NULL, TargetCommandLine, NULL, NULL, 0, DEBUG_PROCESS | DEBUG_ONLY_THIS_PROCESS, NULL, NULL, &TargetStartupInformation, &TargetProcessInformation);
    if(!CreateProcessSuccess){
        print("Failed to create the target process. (GetLastError %d)\n", GetLastError());
        return 1;
    }
    
    DEBUG_EVENT InitialDebugEvent;
    BOOL WaitForInitialDebugEventSuccess = WaitForDebugEvent(&InitialDebugEvent, INFINITE);
    if(!WaitForInitialDebugEventSuccess){
        print("Failed to wait for initial debug event. (GetLastError %d)\n", GetLastError());
        return 1;
    }
    
    if(InitialDebugEvent.dwDebugEventCode != CREATE_PROCESS_DEBUG_EVENT){
        print("Unexpected initial debug event.\n");
        return 1;
    }
    
    BOOL SetPriorityClassSuccess = SetPriorityClass(TargetProcessInformation.hProcess, /*REALTIME_PRIORITY_CLASS*/0x00000100);
    if(!SetPriorityClassSuccess){
        print("Warning: Could not 'SetPriorityClass(REALTIME_PRIORITY_CLASS)'. (GetLastError %d)\n", GetLastError());
    }
    
    DWORD64 ImageBase = (DWORD64)InitialDebugEvent.u.CreateProcessInfo.lpBaseOfImage;
    
    // 
    // Set a software breakpoint on the target offset. 
    // The host will not see this as it ignores software breakpoints.
    // 
    
    DWORD64 TargetAddress = ImageBase + Offset;
    
    BYTE OriginalByte;
    SIZE_T ReadProcessMemoryBytesRead;
    BOOL ReadProcessMemorySuccess = ReadProcessMemory(TargetProcessInformation.hProcess, (LPVOID)TargetAddress, &OriginalByte, 1, &ReadProcessMemoryBytesRead);
    if(!ReadProcessMemorySuccess){
        print("Failed to read from offset 0x%llx of the target executable. (GetLastError %d)\n", Offset, GetLastError());
        return 1;
    }
    
    SIZE_T WriteProcessMemoryBytesWrite;
    BOOL WriteProcessMemorySuccess = WriteProcessMemory(TargetProcessInformation.hProcess, (LPVOID)TargetAddress, &(BYTE){0xcc}, 1, &WriteProcessMemoryBytesWrite);
    if(!WriteProcessMemorySuccess){
        print("Failed to write to offset 0x%llx of the target executable. (GetLastError %d)\n", Offset, GetLastError());
        return 1;
    }
    
    struct{
        DWORD ThreadId;
        HANDLE ThreadHandle;
    } ThreadHandleMap[0x100];
    DWORD ThreadHandleMapSize = 1;
    
    ThreadHandleMap[0].ThreadId     = InitialDebugEvent.dwThreadId;
    ThreadHandleMap[0].ThreadHandle = InitialDebugEvent.u.CreateProcessInfo.hThread;
    
    DEBUG_EVENT DebugEvent = InitialDebugEvent;
    
    while(1){
        ContinueDebugEvent(DebugEvent.dwProcessId, DebugEvent.dwThreadId, DBG_CONTINUE);
        WaitForDebugEvent(&DebugEvent, INFINITE);
        
        DWORD64 ExceptionAddress = (DWORD64)DebugEvent.u.Exception.ExceptionRecord.ExceptionAddress;
        
        if(DebugEvent.dwDebugEventCode == CREATE_THREAD_DEBUG_EVENT){
            DWORD Index = ThreadHandleMapSize++;
            ThreadHandleMap[Index].ThreadId     = DebugEvent.dwThreadId;
            ThreadHandleMap[Index].ThreadHandle = DebugEvent.u.CreateThread.hThread;
        }
        
        if(DebugEvent.dwDebugEventCode == 1 && DebugEvent.u.Exception.ExceptionRecord.ExceptionCode == EXCEPTION_BREAKPOINT && ExceptionAddress == TargetAddress){
            
            // 
            // Reset the byte to the original byte.
            // 
            SIZE_T WriteProcessMemoryBytesWrite;
            BOOL WriteProcessMemorySuccess = WriteProcessMemory(TargetProcessInformation.hProcess, (LPVOID)TargetAddress, &OriginalByte, 1, &WriteProcessMemoryBytesWrite);
            if(!WriteProcessMemorySuccess){
                print("Failed to write to offset 0x%llx of the target executable. (GetLastError %d)\n", Offset, GetLastError());
                return 1;
            }
            
            // 
            // Lock the entire address space.
            // @cleanup: In the future, we might only want to lock the images, and not the entire address space.
            // 
            
            MEMORY_BASIC_INFORMATION MemoryBasicInformation = {0};
            
            for(PBYTE Address = 0;; Address += MemoryBasicInformation.RegionSize){
                
                SIZE_T SizeReturned = VirtualQueryEx(TargetProcessInformation.hProcess, Address, &MemoryBasicInformation, sizeof(MemoryBasicInformation));
                if(SizeReturned < sizeof(MemoryBasicInformation)) break;
                
                if(MemoryBasicInformation.State != MEM_COMMIT) continue;
                if(MemoryBasicInformation.Protect & (PAGE_NOACCESS | PAGE_GUARD)) continue;
                
                // https://github.com/0vercl0k/lockmem/blob/master/src/lockmem.cc#L24
                
                for(int Tries = 0; Tries < 10; Tries++){
                    NTSTATUS NtLockVirtualMemoryStatus = NtLockVirtualMemory(TargetProcessInformation.hProcess, &Address, &MemoryBasicInformation.RegionSize, /*MAP_PROCESS*/1);
                 
                    if(NtLockVirtualMemoryStatus != /*STATUS_WORKING_SET_QUOTA*/0xc00000a1) break;
                    
                    SIZE_T MinimumWorkingSetSize = 0;
                    SIZE_T MaximumWorkingSetSize = 0;
                    DWORD Flags;
                    
                    BOOL GetProcessWorkingSetSizeExSuccess = GetProcessWorkingSetSizeEx(TargetProcessInformation.hProcess, &MinimumWorkingSetSize, &MaximumWorkingSetSize, &Flags);
                    if(!GetProcessWorkingSetSizeExSuccess){
                        print("Failed to get working set Quota.\n");
                        return 1;
                    }
                    
                    MinimumWorkingSetSize *= 2;
                    MaximumWorkingSetSize *= 2;
                    Flags = QUOTA_LIMITS_HARDWS_MIN_ENABLE | QUOTA_LIMITS_HARDWS_MAX_DISABLE;
                    
                    BOOL SetProcessWorkingSetSizeExSuccess = SetProcessWorkingSetSizeEx(TargetProcessInformation.hProcess, MinimumWorkingSetSize, MaximumWorkingSetSize, Flags);
                    if(!SetProcessWorkingSetSizeExSuccess){
                        print("Failed to adjust working set Quota.\n");
                        return 1;
                    }
                }
            }
            
            // 
            // Set a breakpoint which will break on the host.
            // 
            
            HANDLE hThread = 0;
            
            for(DWORD Index = 0; Index < ThreadHandleMapSize; Index++){
                
                if(ThreadHandleMap[Index].ThreadId == DebugEvent.dwThreadId){
                    hThread = ThreadHandleMap[Index].ThreadHandle;
                }
            }
            
            CONTEXT ThreadContext = {.ContextFlags = CONTEXT_ALL };
            
            BOOL GetThreadContextSuccesss = GetThreadContext(hThread, &ThreadContext);
            if(!GetThreadContextSuccesss){
                print("Failed to get the initial register state for the process. (GetLastError %d)\n", GetLastError());
                return 1;
            }
            
            ThreadContext.Rip -= 1;
            ThreadContext.Dr0 = TargetAddress;
            ThreadContext.Dr7 |= 1;
            ThreadContext.ContextFlags = CONTEXT_ALL;
            
            BOOL SetThreadContextSuccesss = SetThreadContext(hThread, &ThreadContext);
            if(!SetThreadContextSuccesss){
                print("Failed to get the initial register state for the process. (GetLastError %d)\n", GetLastError());
                return 1;
            }
            
            ContinueDebugEvent(DebugEvent.dwProcessId, DebugEvent.dwThreadId, DBG_CONTINUE);
            
            BOOL DebugActiveProcessStopSuccess = DebugActiveProcessStop(TargetProcessInformation.dwProcessId);
            if(!DebugActiveProcessStopSuccess){
                print("Failed to detach from process.\n");
                return 1;
            }
            
        }
        
        if(DebugEvent.dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT) break;
    }
}
