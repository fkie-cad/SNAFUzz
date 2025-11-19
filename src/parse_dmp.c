// 
// This file consists of essentially only one function ('parse_dmp').
// It attempt to recreate a workable state off the full kernel DMP,
// which was created from WinDbg by using the '.dump /f <file-path>' 
// command.
// The format of these DMP files is not ideal but workable for what we are
// trying to accomplish. It contains:
// 
//     1) Most of the physical memory state (excluding firmware state).
//     2) A _CONTEXT structure containing most of the general purpose register state
//        and some of the control registers. Most important being the 'cr3' or 
//        'DirectoryTableBase'.
//     3) Some special adresses, like the 'PsLoadedModuleList' and the 'KdDebuggerDataBlock'.
//     
// Because we have the cr3, the physical memory, and the module list, we can parse kernel
// structures to figure out more of the control registers like the GDT, IDT, apic base, ...
// Sadly, some registers remain guess-work (using symbols or hardcoded values observed in the debugger).
// 
// For snapshot mode, we also recreate the VMBUS state by walking and calling 
// vmbkmcl.sys structures and functions.
// 
//                                                         - Pascal Beyer 21.03.2024
// 


// @cleanup: Where should this live?
void stub_out_efi_runtime_services(struct context *context){
    //
    // Stub out Efi Runtime services.
    //
    
    if(guest_read(u8, get_symbol(context, string("nt!HalFirmwareTypeEfi")))){
        //
        // Get The FirmwareInformationBlock, which is a copy of the '_FIRMWARE_INFORMATION_BLOCK' contained in the 'KeLoaderBlock' (_LOADER_PARAMETER_BLOCK).
        // @cleanup: For now I am gonna assume the symbol does not change...
        //
        // u64 HalFirmwareInformationBlock = get_symbol(context, string("nt!HalFirmwareInformationBlock"));
        //
        // @cleanup: This would be a good option but only points to the '_VIRTUAL_EFI_RUNTIME_SERVICES' and there is no guarantee that it is mapped in....
        
        
        //
        // @note: I don't think this is documented...
        //
        u64 HalEfiRuntimeServicesBlock = get_symbol(context, string("nt!HalEfiRuntimeServicesBlock"));
        
        u64 GetTime                  = guest_read(u64, HalEfiRuntimeServicesBlock + 0x00);
        u64 SetTime                  = guest_read(u64, HalEfiRuntimeServicesBlock + 0x08);
        u64 ResetSystem              = guest_read(u64, HalEfiRuntimeServicesBlock + 0x10);
        u64 GetVariable              = guest_read(u64, HalEfiRuntimeServicesBlock + 0x18);
        u64 GetNextVariableName      = guest_read(u64, HalEfiRuntimeServicesBlock + 0x20);
        u64 SetVariable              = guest_read(u64, HalEfiRuntimeServicesBlock + 0x28);
        u64 UpdateCapsule            = guest_read(u64, HalEfiRuntimeServicesBlock + 0x30);
        u64 QueryCapsuleCapabilities = guest_read(u64, HalEfiRuntimeServicesBlock + 0x38);
        u64 QueryVariableInfo        = guest_read(u64, HalEfiRuntimeServicesBlock + 0x40);
        
        // Code:
        //     mov rax, 0x8000000000000003
        //     ret
        static u8 code[] = {
            0x48, 0xb8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
            0xc3
        };
        
        guest_force_write(context, code, GetTime, sizeof(code));
        guest_force_write(context, code, SetTime, sizeof(code));
        guest_force_write(context, code, ResetSystem, sizeof(code));
        guest_force_write(context, code, GetVariable, sizeof(code));
        guest_force_write(context, code, GetNextVariableName, sizeof(code));
        guest_force_write(context, code, SetVariable, sizeof(code));
        guest_force_write(context, code, UpdateCapsule, sizeof(code));
        guest_force_write(context, code, QueryCapsuleCapabilities, sizeof(code));
        guest_force_write(context, code, QueryVariableInfo, sizeof(code));
    }
}

int parse_dmp(struct context *context, char *file_name){
    
    print("Loading .dmp '%s'\n", file_name);
    
#if _WIN32
    HANDLE FileHandle = CreateFileA(file_name, /*GENERIC_READ*/0x80000000L, /*FILE_SHARE_READ | FILE_SHARE_WRITE*/3, null, /*OPEN_EXISTING*/3, /*FILE_ATTRIBUTE_NORMAL*/0x80, null);
    if(FileHandle.Unused == (u64)-1){
        print("Error: Specified Dump (.dmp) file '%s' does not exist!\n", file_name);
        return 0;
    }
    
    u64 FileSize = 0;{
        int Success = GetFileSizeEx(FileHandle, &FileSize);
        if(!Success){
            print("Error: Could not 'GetFileSizeEx' for '%s'.\n", file_name);
            return 0;
        }
    }
#else
    
    int file_descriptor = open(file_name, O_RDONLY);
    if(file_descriptor == -1){
        perror("open");
        return 0;
    }
    
    // 
    // Determine the size of the file.
    // 
    struct stat stat_buffer;
    if(fstat(file_descriptor, &stat_buffer) == -1){
        perror("fstat");
        close(file_descriptor);
        return 0;
    }
    u64 FileSize = stat_buffer.st_size;
    
#endif
    
    //
    // Parse the _DMP_HEADER.
    //
    struct _DMP_HEADER64{
        u64 Signature;
        u32 MajorVersion;
        u32 MinorVersion;
        u64 DirectoryTableBase;
        u64 PfnDataBase;
        u64 PsLoadedModuleList;
        u64 PsActiveProcessHead;
        u32 MachineImageType;
        u32 NumberOfProcessors;
        u32 BugCheckCode;
        u32 _padding;
        u64 BugCheckParameter1;
        u64 BugCheckParameter2;
        u64 BugCheckParameter3;
        u64 BugCheckParameter4;
        char VersionUser[32];
        u64 KdDebuggerDataBlock;
        union{
            char PhysicalMemoryBlockBuffer[700];
            struct _PHYSICAL_MEMORY_DESCRIPTOR64{
                u32 NumberOfRuns;
                u32 __padding;
                u64 NumberOfPages;
                struct _PHYSICAL_MEMORY_RUN64{
                    u64 BasePage;
                    u64 PageCount;
                } Runs[1];
            } PhysicalMemoryBlock;
        };
        
        union{
            char ContextRecord[3000];
            struct _CONTEXT{ // This is apparently not aligned.
                u64 P1Home;
                u64 P2Home;
                u64 P3Home;
                u64 P4Home;
                u64 P5Home;
                u64 P6Home;
                
                u32 ContextFlags;
                u32 MxCsr;
                
                u16 SegCs;
                u16 SegDs;
                u16 SegEs;
                u16 SegFs;
                u16 SegGs;
                u16 SegSs;
                
                u32 EFlags;
                
                u64 Dr0;
                u64 Dr1;
                u64 Dr2;
                u64 Dr3;
                u64 Dr6;
                u64 Dr7;
                
                union{
                    struct{
                        u64 Rax;
                        u64 Rcx;
                        u64 Rdx;
                        u64 Rbx;
                        u64 Rsp;
                        u64 Rbp;
                        u64 Rsi;
                        u64 Rdi;
                        u64 R8;
                        u64 R9;
                        u64 R10;
                        u64 R11;
                        u64 R12;
                        u64 R13;
                        u64 R14;
                        u64 R15;
                    };
                    u64 Gpr[16];
                };
                u64 Rip;
                
                struct _XMM_SAVE_AREA32{
                    u16 ControlWord;
                    u16 StatusWord;
                    
                    u8  TagWord;
                    u8  Reserved1;
                    u16 ErrorOpcode;
                    
                    u32 ErrorOffset;
                    u16 ErrorSelector;
                    u16 Reserved2;
                    
                    u32 DataOffset;
                    u16 DataSelector;
                    u16 Reserved3;
                    
                    u32 MxCsr;
                    u32 MxCsr_Mask;
                } FltSave;
                
                u128 FpST[8];
                
                u128 Xmm0;
                u128 Xmm1;
                u128 Xmm2;
                u128 Xmm3;
                u128 Xmm4;
                u128 Xmm5;
                u128 Xmm6;
                u128 Xmm7;
                u128 Xmm8;
                u128 Xmm9;
                u128 Xmm10;
                u128 Xmm11;
                u128 Xmm12;
                u128 Xmm13;
                u128 Xmm14;
                u128 Xmm15;
                
                
                //
                // @note: Though there is some stuff after this, it seems none of it is useful.
                //        It does not appear that YMM registers are saved.
                
            } Context;
        };
        struct _EXCEPTION_RECORD64{
            u32 ExceptionCode;
            u32 ExceptionFlags;
            u64 ExceptionRecord;
            u64 ExceptionAddress;
            u32 NumberParameters;
            u32 _unused;
            u64 ExceptionInformation[15];
        } ExceptionRecord;
        u32 DumpType;
        u32 __padding2;
        s64 RequiredDumpSpace;
        s64 SystemTime;
        char Comment[128];
        s64 SystemUpTime;
        u32 MiniDumpFields;
        u32 SecondaryDataState;
        u32 ProductType;
        u32 SuiteMask;
        u32 WriterStatus;
        u8 _unused2;
        u8 KdSecondaryVersion;
        u8 _unused[2];
        u32 Attributes;
        u32 BootId;
    } DmpHeader;
    
    {
        //
        // Validate that we can obtain a valid 'DmpHeader'.
        //
        
#if _WIN32
        u32 BytesRead;
        int Success = ReadFile(FileHandle, &DmpHeader, sizeof(DmpHeader), &BytesRead, NULL);
#else
        ssize_t BytesRead = read(file_descriptor, &DmpHeader, sizeof(DmpHeader));
        int Success = BytesRead >= 0;
#endif
        if(!Success || BytesRead != sizeof(DmpHeader)){
            print("Error: Dmp too small for DMP_HEADER64!\n");
            return 0;
        }
        
        if(DmpHeader.Signature != 0x3436554445474150){
            print("Error: Invalid DMP_HEADER64 signature: %.8s.\n", &DmpHeader.Signature);
            return 0;
        }
        
        if(DmpHeader.NumberOfProcessors != 1){
            print("Warning: The .dmp file is from a machine which has more than one processor.\n"
                  "         Only the \"current\" processor will execute any instructions.\n");
        }
    }
    
#if _WIN32
    int SetFilePointerSuccess = SetFilePointerEx(FileHandle, 0x2000, NULL, /*FILE_BEGIN*/0);
    if(!SetFilePointerSuccess){
        print("Error: Could not 'SetFilePointerEx' to 0x2000 (GetLastError %d).\n", GetLastError());
        return 0;
    }
#else
    off_t lseek_result = lseek(file_descriptor, 0x2000, SEEK_SET);
    if(lseek_result == (lseek_result)-1){
        perror("Could not 'lseek' to 0x2000.");
        return 0;
    }
#endif
    
    struct _PHYSICAL_MEMORY_DESCRIPTOR64 *PhysicalMemoryDescriptor;
    
    if(DmpHeader.DumpType == /*Full Dump*/1){
        PhysicalMemoryDescriptor = &DmpHeader.PhysicalMemoryBlock;
    }else if(DmpHeader.DumpType == /*New Full Dump ?*/10){
        struct _RDMP_HEADER{
            u32 NotSure; // 0x40
            u8  Signature[8];
            u32 Padding;
            u64 MemoryDescriptorsSize;
            u64 HeaderSize;
        } RdmpHeader;
        
#if _WIN32
        u32 BytesRead;
        int Success = ReadFile(FileHandle, &RdmpHeader, sizeof(RdmpHeader), &BytesRead, NULL);
#else
        ssize_t BytesRead = read(file_descriptor, &RdmpHeader, sizeof(RdmpHeader));
        int Success = BytesRead >= 0;
#endif
        
        if(!Success || BytesRead != sizeof(RdmpHeader)){
            print("Error: Dmp too small for RDMP_HEADER!\n");
            return 0;
        }
        
        if(RdmpHeader.MemoryDescriptorsSize < sizeof(DmpHeader.PhysicalMemoryBlockBuffer)){
            PhysicalMemoryDescriptor = (void *)&DmpHeader.PhysicalMemoryBlockBuffer;
        }else{
            PhysicalMemoryDescriptor = malloc(RdmpHeader.MemoryDescriptorsSize);
        }
        
#if _WIN32
        Success = ReadFile(FileHandle, PhysicalMemoryDescriptor, (u32)RdmpHeader.MemoryDescriptorsSize, &BytesRead, NULL);
#else
        BytesRead = read(file_descriptor, PhysicalMemoryDescriptor, RdmpHeader.MemoryDescriptorsSize);
        Success = BytesRead >= 0;
#endif
        if(!Success || BytesRead != RdmpHeader.MemoryDescriptorsSize){
            print("Parse DMP error: Failed to read Memory descriptor list!\n");
            return 0;
        }
        
    }else{
        print("Error: Unhandled .dmp type %d.\n", DmpHeader.DumpType);
        return 0;
    }
    
    if(PhysicalMemoryDescriptor->NumberOfRuns == 0){
        print("Error: DMP file does not specify any Physical memory?\n");
        return 0;
    }
    
    //
    // Calculate the guest "physical memory" size needed.
    //
    u64 PhysicalMemorySize = 0;
    u64 PagesInDmp = 0;
    
    for(u32 PhysicalMemoryRunIndex = 0; PhysicalMemoryRunIndex < PhysicalMemoryDescriptor->NumberOfRuns; PhysicalMemoryRunIndex++){
        struct _PHYSICAL_MEMORY_RUN64 *PhysicalMemoryRun = PhysicalMemoryDescriptor->Runs + PhysicalMemoryRunIndex;
        
        if((PhysicalMemoryRun->BasePage > (0x1000ull << 32)) || (PhysicalMemoryRun->PageCount > (0x1000ull << 32))){
            print("Error: Physical Memory Run in DMP file specify memory run, which exceeds bounds.");
        }
        
        u64 RunStart = PhysicalMemoryRun->BasePage  * 0x1000;
        u64 RunSize  = PhysicalMemoryRun->PageCount * 0x1000;
        u64 RunEnd   = RunStart + RunSize;
        
        if(RunEnd > PhysicalMemorySize) PhysicalMemorySize = RunEnd;
        
        PagesInDmp += PhysicalMemoryRun->PageCount;
        
        if(PRINT_STARTUP_EVENTS) print("Range Present: start: %p end: %p size: %p\n", RunStart, RunEnd, RunSize);
    }
    
    if(PagesInDmp * 0x1000 > FileSize - 0x2000){
        print("Error: Dmp file is to small to contain all the Pages specified by the Physical Memory runs.\n");
        return 0;
    }
    
    //
    // Reserve memory for the guest "physical memory".
    //
    u8 *PhysicalMemory = os_allocate_memory(PhysicalMemorySize);
    if(!PhysicalMemory){
        print("Error: Could not reserve memory for guest \"physical memory\".\n");
        return 0;
    }
    
    globals.snapshot.physical_memory_size = PhysicalMemorySize;
    globals.snapshot.physical_memory      = PhysicalMemory;
    
    //
    // We would really like to just memory map sections of the dump file to the physical memory layout.
    // Sadly, windows only supports memory mapping files, if both the mapped address and the file offset
    // is 64k aligned.
    //
    // Therefore, we are just loading it eagerly.
    //
    
    for(u32 PhysicalMemoryRunIndex = 0; PhysicalMemoryRunIndex < PhysicalMemoryDescriptor->NumberOfRuns; PhysicalMemoryRunIndex++){
        struct _PHYSICAL_MEMORY_RUN64 *PhysicalMemoryRun = PhysicalMemoryDescriptor->Runs + PhysicalMemoryRunIndex;
        
        // 
        // @note: I don't know if there is a documented way to read more than 4GiB
        //        from a file at a time. Hence here is a stupid loop which reads in chunks.
        // 
        
        u64 SizeToRead = PhysicalMemoryRun->PageCount * 0x1000;
        
        for(u64 SizeRead = 0; SizeRead < SizeToRead;){
            
            u8 *Destination = PhysicalMemory + (PhysicalMemoryRun->BasePage * 0x1000) + SizeRead;
            
            u32 Size = 1ull * 1024ull * 1024ull * 1024ull;
            
            if((u64)Size > SizeToRead - SizeRead){
                Size = (u32)(SizeToRead - SizeRead);
            }
            
#if _WIN32
            u32 BytesRead;
            int ReadFileSuccess = ReadFile(FileHandle, Destination, Size, &BytesRead, null);
#else
            ssize_t BytesRead = read(file_descriptor, Destination, Size);
            int ReadFileSuccess = BytesRead >= 0;
#endif
            
            if(!ReadFileSuccess || BytesRead != Size){
                print("Error: Dmp file too small for physical memory ranges.\n");
                return 0;
            }
            
            SizeRead += Size;
        }
    }
    
    //
    // Initialize the context for the main thread. From here on we are able to look up virtual addresses.
    //
    u64 page_bitmap_size = globals.snapshot.physical_memory_size/(0x1000 * 8);
    context->registers.cr3            = DmpHeader.DirectoryTableBase;
    context->physical_memory          = globals.snapshot.physical_memory;
    context->physical_memory_size     = globals.snapshot.physical_memory_size;
    context->physical_memory_copied   = os_allocate_memory(page_bitmap_size);
    context->physical_memory_executed = os_allocate_memory(page_bitmap_size);
    memset(context->physical_memory_copied, 0xff, page_bitmap_size);
    
    //
    // Read the 'KdDebuggerDataBlock'.
    //
    
    struct _DBGKD_DEBUG_DATA_HEADER64{
        u64 Flink;
        u64 Blink;
        u32 OwnerTag;
        u32 Size;
    } DebugDataHeader;
    
    int read_debug_data_header_success = guest_read_size(context, &DebugDataHeader, DmpHeader.KdDebuggerDataBlock, sizeof(DebugDataHeader), PERMISSION_none);
    if(!read_debug_data_header_success){
        print("Error: Could not read 'KdDebuggerDataBlock' header.\n");
        return 0;
    }
    
    struct _KDDEBUGGER_DATA64{
        struct _DBGKD_DEBUG_DATA_HEADER64 Header;
        u64 KernBase;
        u64 BreakpointWithStatus;
        u64 SavedContext;
        u16 ThCallbackStack;
        u16 NextCallback;
        u16 FramePointer;
        u16 _bitfield;
        u64 KiCallUserMode;
        u64 KeUserCallbackDispatcher;
        u64 PsLoadedModuleList;
        u64 PsActiveProcessHead;
        u64 PspCidTable;
        u64 ExpSystemResourcesList;
        u64 ExpPagedPoolDescriptor;
        u64 ExpNumberOfPagedPools;
        u64 KeTimeIncrement;
        u64 KeBugCheckCallbackListHead;
        u64 KiBugcheckData;
        u64 IopErrorLogListHead;
        u64 ObpRootDirectoryObject;
        u64 ObpTypeObjectType;
        u64 MmSystemCacheStart;
        u64 MmSystemCacheEnd;
        u64 MmSystemCacheWs;
        u64 MmPfnDatabase;
        u64 MmSystemPtesStart;
        u64 MmSystemPtesEnd;
        u64 MmSubsectionBase;
        u64 MmNumberOfPagingFiles;
        u64 MmLowestPhysicalPage;
        u64 MmHighestPhysicalPage;
        u64 MmNumberOfPhysicalPages;
        u64 MmMaximumNonPagedPoolInBytes;
        u64 MmNonPagedSystemStart;
        u64 MmNonPagedPoolStart;
        u64 MmNonPagedPoolEnd;
        u64 MmPagedPoolStart;
        u64 MmPagedPoolEnd;
        u64 MmPagedPoolInformation;
        u64 MmPageSize;
        u64 MmSizeOfPagedPoolInBytes;
        u64 MmTotalCommitLimit;
        u64 MmTotalCommittedPages;
        u64 MmSharedCommit;
        u64 MmDriverCommit;
        u64 MmProcessCommit;
        u64 MmPagedPoolCommit;
        u64 MmExtendedCommit;
        u64 MmZeroedPageListHead;
        u64 MmFreePageListHead;
        u64 MmStandbyPageListHead;
        u64 MmModifiedPageListHead;
        u64 MmModifiedNoWritePageListHead;
        u64 MmAvailablePages;
        u64 MmResidentAvailablePages;
        u64 PoolTrackTable;
        u64 NonPagedPoolDescriptor;
        u64 MmHighestUserAddress;
        u64 MmSystemRangeStart;
        u64 MmUserProbeAddress;
        u64 KdPrintCircularBuffer;
        u64 KdPrintCircularBufferEnd;
        u64 KdPrintWritePointer;
        u64 KdPrintRolloverCount;
        u64 MmLoadedUserImageList;
        u64 NtBuildLab;
        u64 KiNormalSystemCall;
        u64 KiProcessorBlock;
        u64 MmUnloadedDrivers;
        u64 MmLastUnloadedDriver;
        u64 MmTriageActionTaken;
        u64 MmSpecialPoolTag;
        u64 KernelVerifier;
        u64 MmVerifierData;
        u64 MmAllocatedNonPagedPool;
        u64 MmPeakCommitment;
        u64 MmTotalCommitLimitMaximum;
        u64 CmNtCSDVersion;
        u64 MmPhysicalMemoryBlock;
        u64 MmSessionBase;
        u64 MmSessionSize;
        u64 MmSystemParentTablePage;
        u64 MmVirtualTranslationBase;
        u16 OffsetKThreadNextProcessor;
        u16 OffsetKThreadTeb;
        u16 OffsetKThreadKernelStack;
        u16 OffsetKThreadInitialStack;
        u16 OffsetKThreadApcProcess;
        u16 OffsetKThreadState;
        u16 OffsetKThreadBStore;
        u16 OffsetKThreadBStoreLimit;
        u16 SizeEProcess;
        u16 OffsetEprocessPeb;
        u16 OffsetEprocessParentCID;
        u16 OffsetEprocessDirectoryTableBase;
        u16 SizePrcb;
        u16 OffsetPrcbDpcRoutine;
        u16 OffsetPrcbCurrentThread;
        u16 OffsetPrcbMhz;
        u16 OffsetPrcbCpuType;
        u16 OffsetPrcbVendorString;
        u16 OffsetPrcbProcStateContext;
        u16 OffsetPrcbNumber;
        u16 SizeEThread;
        u8 L1tfHighPhysicalBitIndex;
        u8 L1tfSwizzleBitIndex;
        u32 Padding0;
        u64 KdPrintCircularBufferPtr;
        u64 KdPrintBufferSize;
        u64 KeLoaderBlock;
        u16 SizePcr;
        u16 OffsetPcrSelfPcr;
        u16 OffsetPcrCurrentPrcb;
        u16 OffsetPcrContainedPrcb;
        u16 OffsetPcrInitialBStore;
        u16 OffsetPcrBStoreLimit;
        u16 OffsetPcrInitialStack;
        u16 OffsetPcrStackLimit;
        u16 OffsetPrcbPcrPage;
        u16 OffsetPrcbProcStateSpecialReg;
        u16 GdtR0Code;
        u16 GdtR0Data;
        u16 GdtR0Pcr;
        u16 GdtR3Code;
        u16 GdtR3Data;
        u16 GdtR3Teb;
        u16 GdtLdt;
        u16 GdtTss;
        u16 Gdt64R3CmCode;
        u16 Gdt64R3CmTeb;
        u64 IopNumTriageDumpDataBlocks;
        u64 IopTriageDumpDataBlocks;
        u64 VfCrashDataBlock;
        u64 MmBadPagesDetected;
        u64 MmZeroedPageSingleBitErrorsDetected;
        u64 EtwpDebuggerData;
        u16 OffsetPrcbContext;
        u16 OffsetPrcbMaxBreakpoints;
        u16 OffsetPrcbMaxWatchpoints;
        u16 __padding;
        u32 OffsetKThreadStackLimit;
        u32 OffsetKThreadStackBase;
        u32 OffsetKThreadQueueListEntry;
        u32 OffsetEThreadIrpList;
        u16 OffsetPrcbIdleThread;
        u16 OffsetPrcbNormalDpcState;
        u16 OffsetPrcbDpcStack;
        u16 OffsetPrcbIsrStack;
        u16 SizeKDPC_STACK_FRAME;
        u16 OffsetKPriQueueThreadListHead;
        u16 OffsetKThreadWaitReason;
        u16 Padding1;
        u64 PteBase;
        u64 RetpolineStubFunctionTable;
        u32 RetpolineStubFunctionTableSize;
        u32 RetpolineStubOffset;
        u32 RetpolineStubSize;
        u16 OffsetEProcessMmHotPatchContext;
        u16 __padding2;
    } KdData;
    
    if(DebugDataHeader.Size < sizeof(KdData)){
        print("Error: '_KDDEBUGGER_DATA64' is smaller than expected.\n");
        return 0;
    }
    
    int read_kd_data_success = guest_read_size(context, &KdData, DmpHeader.KdDebuggerDataBlock, sizeof(KdData), PERMISSION_none);
    if(!read_kd_data_success){
        print("Error: Could not read KdDebuggerDataBlock data.\n");
        return 0;
    }
    
    load_modules_from_list(context, DmpHeader.PsLoadedModuleList);
    
    {
        // 
        // Now that the modules are loaded, we can use symbols. 
        // Check manually here, that we can indeed load the symbols for 'nt', 
        // as we definitely need those and sometimes the microsoft symbol servers 
        // are not yet up to date. In this case we want to print a good error message.
        // 
        struct loaded_module *nt = get_loaded_module(string("nt"));
        if(!nt){
            print("Corrupt .DMP: The PsLoadedModuleList inside the .DMP file does not contain a module called 'ntoskrnl.exe'.\n");
            return 0;
        }
        
        if(!nt->tried_to_load_pdb) loaded_module_try_to_load_pdb(context, nt);
        if(!nt->pdb_context){
            print("Error: Could not load the .PDB for 'ntoskrnl.exe' this could mean you updated to early\n");
            print("       and the Microsoft symbol server is not yet up to date.\n");
            return 0;
        }
    }
    
    u64 kprcb = 0, kpcr = 0, thread = 0, process = 0, process_cr3 = 0;
    
    for(u32 processor_index = 0; processor_index < DmpHeader.NumberOfProcessors; processor_index++){
        kprcb = guest_read(u64, KdData.KiProcessorBlock + 8 * processor_index);
        kpcr = kprcb - KdData.OffsetPcrContainedPrcb;
        
        thread      = guest_read(u64, kprcb   + get_member_offset(context, string("nt!_KPRCB.CurrentThread")));
        process     = guest_read(u64, thread  + get_member_offset(context, string("nt!_KTHREAD.ApcState.Process")));
        process_cr3 = guest_read(u64, process + get_member_offset(context, string("nt!_KPROCESS.DirectoryTableBase")));
        
        if(process_cr3 == DmpHeader.DirectoryTableBase) break;
    }
    
    if(process_cr3 != DmpHeader.DirectoryTableBase){
        print("Error: Could not find the active processor by scanning `nt!KiProcessorBlock`\n");
        print("       for a processor running the process with `cr3 = DmpHeader.DirectoryTableBase`.\n");
        return 0;
    }
    
    //
    // Read the '_KSPECIAL_REGISTERS'.
    //
    struct _KSPECIAL_REGISTERS{
        u64 Cr0;
        u64 Cr2;
        u64 Cr3;
        u64 Cr4;
        u64 KernelDr0;
        u64 KernelDr1;
        u64 KernelDr2;
        u64 KernelDr3;
        u64 KernelDr6;
        u64 KernelDr7;
        struct {u16 Pad[3]; u16 Limit; u64 Base;} Gdtr;
        struct {u16 Pad[3]; u16 Limit; u64 Base;} Idtr;
        u16 Tr;
        u16 Ldtr;
        u32 MxCsr;
        u64 DebugControl;
        u64 LastBranchToRip;
        u64 LastBranchFromRip;
        u64 LastExceptionToRip;
        u64 LastExceptionFromRip;
        u64 Cr8;
        u64 MsrGsBase; // @note: Sadly, these MSR seem to be not filled in :(
        u64 MsrGsSwap;
        u64 MsrStar;
        u64 MsrLStar;
        u64 MsrCStar;
        u64 MsrSyscallMask;
        u64 Xcr0;
        u64 MsrFsBase;
        u64 SpecialPadding0;
    } special_registers;
    
    int read_special_registers_success = guest_read_size(context, &special_registers, kprcb + get_member_offset(context, string("nt!_KPRCB.ProcessorState.SpecialRegisters")), sizeof(special_registers), PERMISSION_none);
    if(!read_special_registers_success){
        print("Error: Could not read `nt!_KPRCB.ProcessorState.SpecialRegisters`.\n");
        return 0;
    }
    
    u64 rdtsc    = guest_read(u64, kprcb + get_member_offset(context, string("nt!_KPRCB.StartCycles")));
    u64 gdt_base = guest_read(u64, kpcr + get_member_offset(context, string("nt!_KPCR.GdtBase"))); // Global Descriptor Table.
    u64 idt_base = guest_read(u64, kpcr + get_member_offset(context, string("nt!_KPCR.IdtBase"))); // Interrupt Descriptor Table.
    u64 UserTib  = guest_read(u64, kpcr + get_member_offset(context, string("nt!_KPCR.Used_Self")));
    
    u64 ia32_lstar = get_symbol(context, string("nt!KiSystemCall64"));
    u64 ia32_cstar = get_symbol(context, string("nt!KiSystemCall32")); // @note: Currently unused.
    
    if(guest_read(u32, get_symbol(context, string("nt!KiKvaShadow"))) & 1){
        // 
        // KVAS is enabled, use the shadow variants.
        // 
        ia32_lstar = get_symbol(context, string("nt!KiSystemCall64Shadow"));
        ia32_cstar = get_symbol(context, string("nt!KiSystemCall32Shadow"));
    }
    
    u64 ia32_apic_base = guest_read(u64, get_symbol(context, string("nt!HalpLocalApicPhysical"))) | /*Enabled + Boot Strap Processor*/0x900;
    
    if(context->crash){
        print("Error: Failed to read critical kernel structures while parsing DMP.\n");
        return 0;
    }
    
    int are_in_kernel = (s64)DmpHeader.Context.Rip < 0;
    if(!are_in_kernel){
        // @cleanup: Why is this not set? what am I not understanding?
        DmpHeader.Context.SegCs |= 3;
    }
    
    u64 gs_base = !are_in_kernel ? UserTib : kpcr;
    u64 gs_swap = !are_in_kernel ? kpcr : UserTib;
    
    //
    // Parse the GDT to find information about the segments.
    //
    
    struct segment cs = parse_segment_from_global_descriptor_table(context, gdt_base, DmpHeader.Context.SegCs);
    struct segment ds = parse_segment_from_global_descriptor_table(context, gdt_base, DmpHeader.Context.SegDs);
    struct segment es = parse_segment_from_global_descriptor_table(context, gdt_base, DmpHeader.Context.SegEs);
    struct segment ss = parse_segment_from_global_descriptor_table(context, gdt_base, DmpHeader.Context.SegSs);
    
    struct segment fs = parse_segment_from_global_descriptor_table(context, gdt_base, DmpHeader.Context.SegFs);
    struct segment gs = parse_segment_from_global_descriptor_table(context, gdt_base, DmpHeader.Context.SegGs);
    
    struct segment ldt = parse_segment_from_global_descriptor_table(context, gdt_base, KdData.GdtLdt);
    struct segment tr  = parse_segment_from_global_descriptor_table(context, gdt_base, KdData.GdtTss);
    
    if(context->crash) return 0;// We should have printed an error in 'parse_segment_from_global_descriptor_table'.
    
    // 
    // Fix up the gs base, it is usually stored in a MSR and not the descriptor.
    // 
    gs.base = gs_base;
    
    struct registers initial_register_state = {
        .rip = DmpHeader.Context.Rip,
        .rax = DmpHeader.Context.Rax,
        .rcx = DmpHeader.Context.Rcx,
        .rdx = DmpHeader.Context.Rdx,
        .rbx = DmpHeader.Context.Rbx,
        .rsp = DmpHeader.Context.Rsp,
        .rbp = DmpHeader.Context.Rbp,
        .rsi = DmpHeader.Context.Rsi,
        .rdi = DmpHeader.Context.Rdi,
        .r8  = DmpHeader.Context.R8,
        .r9  = DmpHeader.Context.R9,
        .r10 = DmpHeader.Context.R10,
        .r11 = DmpHeader.Context.R11,
        .r12 = DmpHeader.Context.R12,
        .r13 = DmpHeader.Context.R13,
        .r14 = DmpHeader.Context.R14,
        .r15 = DmpHeader.Context.R15,
        
        
#if _WIN32
        .simd[0].xmmi  = {.m128i_u64[0] = DmpHeader.Context.Xmm0.low,  .m128i_u64[1] = DmpHeader.Context.Xmm0.high},
        .simd[1].xmmi  = {.m128i_u64[0] = DmpHeader.Context.Xmm1.low,  .m128i_u64[1] = DmpHeader.Context.Xmm1.high},
        .simd[2].xmmi  = {.m128i_u64[0] = DmpHeader.Context.Xmm2.low,  .m128i_u64[1] = DmpHeader.Context.Xmm2.high},
        .simd[3].xmmi  = {.m128i_u64[0] = DmpHeader.Context.Xmm3.low,  .m128i_u64[1] = DmpHeader.Context.Xmm3.high},
        .simd[4].xmmi  = {.m128i_u64[0] = DmpHeader.Context.Xmm4.low,  .m128i_u64[1] = DmpHeader.Context.Xmm4.high},
        .simd[5].xmmi  = {.m128i_u64[0] = DmpHeader.Context.Xmm5.low,  .m128i_u64[1] = DmpHeader.Context.Xmm5.high},
        .simd[6].xmmi  = {.m128i_u64[0] = DmpHeader.Context.Xmm6.low,  .m128i_u64[1] = DmpHeader.Context.Xmm6.high},
        .simd[7].xmmi  = {.m128i_u64[0] = DmpHeader.Context.Xmm7.low,  .m128i_u64[1] = DmpHeader.Context.Xmm7.high},
        .simd[8].xmmi  = {.m128i_u64[0] = DmpHeader.Context.Xmm8.low,  .m128i_u64[1] = DmpHeader.Context.Xmm8.high},
        .simd[9].xmmi  = {.m128i_u64[0] = DmpHeader.Context.Xmm9.low,  .m128i_u64[1] = DmpHeader.Context.Xmm9.high},
        .simd[10].xmmi = {.m128i_u64[0] = DmpHeader.Context.Xmm10.low, .m128i_u64[1] = DmpHeader.Context.Xmm10.high},
        .simd[11].xmmi = {.m128i_u64[0] = DmpHeader.Context.Xmm11.low, .m128i_u64[1] = DmpHeader.Context.Xmm11.high},
        .simd[12].xmmi = {.m128i_u64[0] = DmpHeader.Context.Xmm12.low, .m128i_u64[1] = DmpHeader.Context.Xmm12.high},
        .simd[13].xmmi = {.m128i_u64[0] = DmpHeader.Context.Xmm13.low, .m128i_u64[1] = DmpHeader.Context.Xmm13.high},
        .simd[14].xmmi = {.m128i_u64[0] = DmpHeader.Context.Xmm14.low, .m128i_u64[1] = DmpHeader.Context.Xmm14.high},
        .simd[15].xmmi = {.m128i_u64[0] = DmpHeader.Context.Xmm15.low, .m128i_u64[1] = DmpHeader.Context.Xmm15.high},
#else
        .simd[0].xmmi  = {DmpHeader.Context.Xmm0.low,  DmpHeader.Context.Xmm0.high},
        .simd[1].xmmi  = {DmpHeader.Context.Xmm1.low,  DmpHeader.Context.Xmm1.high},
        .simd[2].xmmi  = {DmpHeader.Context.Xmm2.low,  DmpHeader.Context.Xmm2.high},
        .simd[3].xmmi  = {DmpHeader.Context.Xmm3.low,  DmpHeader.Context.Xmm3.high},
        .simd[4].xmmi  = {DmpHeader.Context.Xmm4.low,  DmpHeader.Context.Xmm4.high},
        .simd[5].xmmi  = {DmpHeader.Context.Xmm5.low,  DmpHeader.Context.Xmm5.high},
        .simd[6].xmmi  = {DmpHeader.Context.Xmm6.low,  DmpHeader.Context.Xmm6.high},
        .simd[7].xmmi  = {DmpHeader.Context.Xmm7.low,  DmpHeader.Context.Xmm7.high},
        .simd[8].xmmi  = {DmpHeader.Context.Xmm8.low,  DmpHeader.Context.Xmm8.high},
        .simd[9].xmmi  = {DmpHeader.Context.Xmm9.low,  DmpHeader.Context.Xmm9.high},
        .simd[10].xmmi = {DmpHeader.Context.Xmm10.low, DmpHeader.Context.Xmm10.high},
        .simd[11].xmmi = {DmpHeader.Context.Xmm11.low, DmpHeader.Context.Xmm11.high},
        .simd[12].xmmi = {DmpHeader.Context.Xmm12.low, DmpHeader.Context.Xmm12.high},
        .simd[13].xmmi = {DmpHeader.Context.Xmm13.low, DmpHeader.Context.Xmm13.high},
        .simd[14].xmmi = {DmpHeader.Context.Xmm14.low, DmpHeader.Context.Xmm14.high},
        .simd[15].xmmi = {DmpHeader.Context.Xmm15.low, DmpHeader.Context.Xmm15.high},
#endif
        
        .cs = cs,
        .ds = ds,
        .es = es,
        .ss = ss,
        
        .tr  = tr,
        .ldt = ldt,
        
        .fs = fs,
        .gs = gs,
        
        .gs_base  = gs_base,
        .gs_swap  = gs_swap,
        
        .idt_base  = idt_base,
        .idt_limit = special_registers.Idtr.Limit,
        
        .gdt_base  = gdt_base,
        .gdt_limit = special_registers.Gdtr.Limit,
        
        .xinuse = 6, // @cleanup:
        
        .mxcsr      = DmpHeader.Context.MxCsr,
        // .mxcsr_mask = DmpHeader.Context.FltSave.MxCsr_Mask,
        .mxcsr_mask = 0xffff, // @cleanup: understand this! Somehow the hypervisor accepts 0xfffff802, which appears to be the value specified in the DMP_HEADER, but then it sets it to 0xffff.
        
        // @note: I have about zero clue what any x87 stuff does.
        .fpu_control_word   = DmpHeader.Context.FltSave.ControlWord,
        .fpu_status_word    = DmpHeader.Context.FltSave.StatusWord,
        .fpu_tag_word = DmpHeader.Context.FltSave.TagWord,
        
        .ia32_tsc = rdtsc,
        .ia32_tsc_aux = 0, // processor 0
        
        .rflags = DmpHeader.Context.EFlags,
        
        // See comment in registers, this is dumped from KD: (80050031)
        // These are  PG             AM             WP             NE            ET            PE
        // .cr0 = ((1ull << 31) | (1ull << 18) | (1ull << 16) | (1ull << 5) | (1ull << 4) | (1ull << 0)),
        .cr0 = special_registers.Cr0,
        
        // @cleanup: Use 'nt!_KPROCESS.UserDirectoryTableBase' if we are in user space?
        .cr3 = DmpHeader.DirectoryTableBase,
        
        // See comment in registers, this is dumped from KD: (1106a0)
        // These are SMEP         FSGSBASE      OSXMMEXCPT      OSFXSR          PGE          PAE
        // .cr4 = ((1ull << 20) | (1ull << 16) | (1ull << 10) | (1ull << 9) | (1ull << 7) | (1ull << 5)),
        .cr4 = special_registers.Cr4,
        
        // .xcr0 = 7, // x87 | SSE | AVX
        .xcr0 = special_registers.Xcr0,
        
        .dr0 = DmpHeader.Context.Dr0,
        .dr1 = DmpHeader.Context.Dr1,
        .dr2 = DmpHeader.Context.Dr2,
        .dr3 = DmpHeader.Context.Dr3,
        .dr6 = DmpHeader.Context.Dr6,
        .dr7 = DmpHeader.Context.Dr7,
        
        .ia32_efer = 0xd01, // msr[c0000080] = 00000000`00000d01 (System Call Extension (1) | Long Mode Enable (8) | Long Mode Active (10) | (No-Execute Enable (11))
        .ia32_pat  = 0x0007010600070106, // Page Attribute Table - msr[277] = 00070106`00070106 (?)
        
        .ia32_star = 0x0023001000000000, // msr[c0000081] = 00230010`00000000
        .ia32_lstar = ia32_lstar,
        .ia32_cstar = ia32_cstar,
        .ia32_fmask = 0x4700, // msr[c0000084] = 00000000`00004700 (FLAG_TF | FLAG_IF | FLAG_DF | FLAG_NT)
        
        .ia32_spec_ctrl = 1,
        
        // @cleanup: I don't think we support a relocated Apic...
        .ia32_apic_base = ia32_apic_base,
        
        .local_apic = {
            .highest_pending_interrupt    = -1,
            .highest_interrupt_in_service = -1,
        },
        
        .hv_x64_msr_sint2 = 0x20033,
        .hv_x64_msr_sint3 = 0xd1,
        
        .hv_x64_msr_stimer0_config = 0x3000b, // synthetic interrupt vector = 3, 0xb = auto enable | periodic | enabled.
        .hv_x64_msr_stimer0_count  = 0x2625A,
    };
    
    {
        //
        // The 'SintMessagePage' and the 'SintEventFlags' are Pages that enable
        // communication through 'Synthetic interrupts' (sint) between the host and the guest.
        // We need these for the VMBUS to work.
        //
        
        u64 WinHvGetSintMessage    = get_symbol(context, string("winhv!WinHvGetSintMessage"));
        u64 WinHvGetSintEventFlags = get_symbol(context, string("winhv!WinHvGetSintEventFlags"));
        
        if(WinHvGetSintMessage && WinHvGetSintEventFlags){
            //
            // Get the 'sint message page' and the 'sint event flags page' these are used to assist communication when using
            // Synthetic interrupts to pass messages to the guest.
            //
            struct registers registers = initial_register_state;
            registers.gs_base = ((s64)registers.rip > 0) ? registers.gs_swap : registers.gs_base;
            
            //
            // Allocate some space on the stack.
            // 0x20 for homing space, 0x8 for the return address. and then 0x18 for random stuff.
            //
            registers.rsp -= 0x40;
            
            //
            // Make sure rsp is aligned properly for just having _called_ a function.
            //
            if((registers.rsp & 0xf) == 0) registers.rsp -= 8;
            assert((registers.rsp & 0xf) == 8);
            
            guest_write(u64, registers.rsp, DEFAULT_RETURN_RIP);
            
            registers.rip = WinHvGetSintMessage;
            registers.rcx = 0;
            
            context->registers = registers;
            struct crash_information execution_result = start_execution_jit(context);
            assert(execution_result.crash_type == CRASH_none);
            if(PRINT_STARTUP_EVENTS) print("sint_message_page %p\n", context->registers.rax);
            
            u64 pte = 0;
            initial_register_state.hv_x64_msr_simp = translate_page_number_to_physical(context, (context->registers.rax >> 12), PERMISSION_write, &pte) | 1;
            
            registers.rip = WinHvGetSintEventFlags;
            registers.rcx = 0;
            
            context->registers = registers;
            execution_result = start_execution_jit(context);
            assert(execution_result.crash_type == CRASH_none);
            
            if(PRINT_STARTUP_EVENTS) print("sint_event_flags_page %p\n", context->registers.rax);
            
            pte = 0;
            initial_register_state.hv_x64_msr_siefp = translate_page_number_to_physical(context, (context->registers.rax >> 12), PERMISSION_write, &pte) | 1;
        }
    }
    
    {
        u64 HvlpReferenceTscPage = guest_read(u64, get_symbol(context, string("nt!HvlpReferenceTscPage")));
        
        u64 pte = 0;
        initial_register_state.hv_x64_msr_reference_tsc_page = translate_page_number_to_physical(context, (HvlpReferenceTscPage >> 12), PERMISSION_write, &pte);
        if(pte & PAGE_TABLE_present) initial_register_state.hv_x64_msr_reference_tsc_page |= 1;
    }
    
    
    //
    // Save the registers so that the threads can read them!
    // This gives the threads the ability to have a valid cr3, and access to the user_buffers.
    //
    
    globals.snapshot.registers = initial_register_state;
    
    do{
        // 
        // Attempt to load the vmbus information.
        // This is somewhat volatile, as there are no symbols to get reliable results.
        // 
        
        u64 KmclChannelList = get_symbol(context, string("vmbkmcl!KmclChannelList"));
        if(!KmclChannelList){
            print("Warning: Could not find 'vmbkmcl!KmclChannelList'. This means vmbus devices will not work.\n");
            break;
        }
        
        u64 VmBusChannelListEntry = guest_read(u64, KmclChannelList);
        
        u64 VmbusChannelListEntryOffset = 0;
        u64 VmbusChannelInstanceTypeIdOffset = 0;
        
        {
            // 
            // Figure out the offset of the 'ListEntry' inside the 'VmbChannel' 
            // by scanning backwards on the first entry until we find the pool tag.
            // 
            
            u32 ChannelPoolTag = 0x636d6b56; // "Vkmc"
            
            if(VmBusChannelListEntry == KmclChannelList){
                print("Warning: 'vmbkmcl!KmclChannelList' is empty. This means vmbus devices will likely not work.\n");
                break;
            }
            
            if(VmBusChannelListEntry & 0xf){ // @paranoid.
                print("Warning: 'vmbkmcl!KmclChannelList' is corrupted. This means vmbus devices will not work.\n");
                break;
            }
            
            u64 VmbusChannel = 0;
            
            for(u64 Scan = VmBusChannelListEntry; !context->crash; Scan -= 0x10){
                if(guest_read(u32, Scan + 4) == ChannelPoolTag && guest_read(u64, Scan + 0x10) == Scan + 0x10){
                    VmbusChannel = Scan + 0x10;
                    break;
                }
            }
            
            if(!VmbusChannel){
                print("Warning: Could not determine the offset of 'ListEntry' in the 'VmbusChannel'. This means vmbus devices will not work.\n");
                break;
            }
            
            VmbusChannelListEntryOffset = VmBusChannelListEntry - VmbusChannel;
            
            
            // 
            // Call 'VmbChannelGetInterfaceInstance' to figure out the offset of the 'InterfaceId'.
            // 
            
            struct registers registers = initial_register_state;
            registers.gs_base = ((s64)registers.rip > 0) ? registers.gs_swap : registers.gs_base;
            
            registers.rsp -= 0x80;
            if((registers.rsp & 0xf) == 0) registers.rsp -= 8;
            assert((registers.rsp & 0xf) == 8);
            guest_write(u64, registers.rsp, DEFAULT_RETURN_RIP);
            
            registers.rip = get_symbol(context, string("vmbkmcl!VmbChannelGetInterfaceInstance"));
            registers.rcx = VmbusChannel;
            registers.rdx = initial_register_state.rsp - 0x20;
            
            context->registers = registers;
            struct crash_information execution_result = start_execution_jit(context);
            assert(execution_result.crash_type == CRASH_none);
            
            struct guid guid = guest_read(struct guid, initial_register_state.rsp - 0x20);
            
            for(u64 Scan = VmbusChannel; !context->crash; Scan += 4){
                if(memcmp(&guest_read(struct guid, Scan), &guid, sizeof(guid)) == 0){
                    VmbusChannelInstanceTypeIdOffset = Scan - VmbusChannel - 0x10;
                    break;
                }
            }
            
            if(!VmbusChannelInstanceTypeIdOffset){
                print("Warning: Could not determine the offset of 'InterfaceTypeId' in the 'VmbusChannel'. This means vmbus devices will not work.\n");
                break;
            }
        }
        
        // @note: This is really ad-hoc, but whatever.
        //        We need these to determine the channel id, as it does not seem to be stored anywhere.
        u64 XpartPncFlags = get_symbol(context, string("vmbus!XPartPncFlags"));
        u64 XPartPncHighestFlagUsed = guest_read(u16, get_symbol(context, string("vmbus!XPartPncHighestFlagUsed")));
        
        u32 gpadl_id = 1;
        
        for(; !context->crash && (VmBusChannelListEntry != KmclChannelList); VmBusChannelListEntry = guest_read(u64, VmBusChannelListEntry)){
            
            u64 VmbusChannel = VmBusChannelListEntry - VmbusChannelListEntryOffset;
            
            struct guid InterfaceTypeId = guest_read(struct guid, VmbusChannel + VmbusChannelInstanceTypeIdOffset);
            
            enum vmbus_device_kind device_kind = vmbus_interface_type_id_to_device_type(InterfaceTypeId);
            
            #if 0
            print("InterfaceTypeId {%.8x-%.4x-%.4x-%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x}\n",
                    InterfaceTypeId.Data1, InterfaceTypeId.Data2, InterfaceTypeId.Data3, 
                    InterfaceTypeId.Data4[0], InterfaceTypeId.Data4[1], InterfaceTypeId.Data4[2], InterfaceTypeId.Data4[3],
                    InterfaceTypeId.Data4[4], InterfaceTypeId.Data4[5], InterfaceTypeId.Data4[6], InterfaceTypeId.Data4[7]);
            #endif
            
            u32 ChannelId = 0xffffffff;
            for(u32 FlagIndex = 0; FlagIndex <= XPartPncHighestFlagUsed; FlagIndex++){
                u64 XpartPnc = guest_read(u64, XpartPncFlags + 8 * FlagIndex) & ~1;
                if(!XpartPnc) continue;
                
                u64 CallbackAndChannel = guest_read(u64, XpartPnc + 0x18);
                if(!CallbackAndChannel) continue;
                
                u64 XpartChannel = guest_read(u64, CallbackAndChannel + 8);
                if(VmbusChannel == XpartChannel){
                    ChannelId = FlagIndex;
                    break;
                }
            }
            
            if(!ChannelId){
                print("Warning: Could not determine the ChannelId for VmbusChannel at %p.\n", VmbusChannel);
                continue;
            }
            
            // 
            // Call 'VmbChannelGetRingBuffer' to find the send/read ring buffer pages.
            // 
            
            struct registers registers = initial_register_state;
            registers.gs_base = ((s64)registers.rip > 0) ? registers.gs_swap : registers.gs_base;
            
            registers.rsp -= 0x80;
            if((registers.rsp & 0xf) == 0) registers.rsp -= 8;
            assert((registers.rsp & 0xf) == 8);
            guest_write(u64, registers.rsp, DEFAULT_RETURN_RIP);
            
            registers.rip = get_symbol(context, string("vmbkmcl!VmbChannelGetRingBuffer"));
            registers.rcx = VmbusChannel;
            registers.rdx = initial_register_state.rsp - 0x20;
            registers.r8  = initial_register_state.rsp - 0x10;
            registers.r9  = initial_register_state.rsp - 0x18;
            guest_write(u64, registers.rsp + 0x28, initial_register_state.rsp - 0xc);
            
            context->registers = registers;
            struct crash_information execution_result = start_execution_jit(context);
            assert(execution_result.crash_type == CRASH_none);
            
            struct{
                u64 buffer1; // This is the one we write to.
                u64 buffer2; // This is the one we read from.
                u32 size1;
                u32 size2;
            } ring_buffer = {0};
            
            guest_read_size(context, &ring_buffer, initial_register_state.rsp - 0x20, sizeof(ring_buffer), PERMISSION_none);
            
            u32 total_amount_of_pages = ring_buffer.size1 + ring_buffer.size2;
            
            struct gpadl *gpadl = (void *)push_data(&context->permanent_arena, u8, sizeof(struct gpadl) + total_amount_of_pages * sizeof(u64));
            gpadl->gpadl_id = gpadl_id++;
            gpadl->channel_id = ChannelId;
            gpadl->amount_of_pages = total_amount_of_pages;
            
            u64 page_index = 0;
            for(u64 index = 0; index < ring_buffer.size2; index++){
                u64 pte = 0;
                gpadl->pages[page_index++] = translate_page_number_to_physical(context, ring_buffer.buffer2/0x1000 + index, PERMISSION_read, &pte) / 0x1000;
            }
            
            for(u64 index = 0; index < ring_buffer.size1; index++){
                u64 pte = 0;
                gpadl->pages[page_index++] = translate_page_number_to_physical(context, ring_buffer.buffer1/0x1000 + index, PERMISSION_read, &pte) / 0x1000;
            }
            
            gpadl->next           = context->vmbus.gpadls;
            context->vmbus.gpadls = gpadl;
            
            // 
            // @note: Let's pray this is enough to make everything sort of work :)
            // 
            
            struct vmbus_channel *channel = push_struct(&context->permanent_arena, struct vmbus_channel);
            channel->device_kind   = device_kind;
            channel->gpadl_id      = gpadl->gpadl_id;
            channel->channel_id    = ChannelId;
            channel->connection_id = ChannelId | 0x2000;
            channel->read_ring_buffer_pages = ring_buffer.size2;
            
            vmbus_channel_initialize_ringbuffers(channel, gpadl);
            
            channel->next = context->vmbus.channels;
            context->vmbus.channels = channel;
            
            if(channel->device_kind == VMBUS_DEVICE_mouse)    context->vmbus.mouse = channel;
            if(channel->device_kind == VMBUS_DEVICE_keyboard) context->vmbus.keyboard = channel;
        }
        
    } while(false);
    
    stub_out_efi_runtime_services(context);
    
    {
        // Patch some kernel debugger symbols I guess.
        guest_write(u32, get_symbol(context, string("nt!KdpDebugRoutineSelect")), 0);
        guest_write(u32, get_symbol(context, string("nt!KdDebuggerEnabled")), 0);
        guest_write(u32, get_symbol(context, string("nt!KdDebuggerNotPresent")), 1);
        guest_write(u32, get_symbol(context, string("nt!KdPitchDebugger")), 0);
    }
    
    return 1;
}
