@echo off

:: Build script, essentially does `cl src\uefi_bios.c`, `cl src\hacky_display.c src\main.c`.
:: Optionally, this build script allows passing a target file as the first argument:
::     build.bat hevd.c
::     build.bat C:\path\to\hevd.c
:: If the target is not specified, the `src\default_target.c` is used.

set optimization= /Od

set target_source= 
IF %1.==. GOTO No1
:: Allow full paths by checking whether the second character is a ':'. There is probably a better option.
set target_source=%1
IF %target_source:~1,1%==: (set target_source= /DTARGET_SOURCE=%target_source%) ELSE (set target_source=/DTARGET_SOURCE=../%target_source%)
:No1

del build\*.pdb >NUL 2>&1
del build\*.obj >NUL 2>&1
del build\*.ilk >NUL 2>&1

:: disable a bunch of security things as otherwise it will insert externals like '__chkstk'.
cl /nologo /GS- /Gs9999999 src/uefi_bios.c /Z7 /INCREMENTAL:no /Fo:build\bios.obj /Fe:build\bios.exe /link /nodefaultlib /subsystem:console /ignore:4281 /base:0x100000 /entry:entry /DEBUGTYPE:CV,PDATA
if not %errorlevel% == 0 goto :end

:: Build the hacky_display.c, this is in it's own compilation unit, as it includes windows.h and I don't want to polute my namespace.
cl /nologo /c src/hacky_display.c /Z7 /INCREMENTAL:no /Fo: build\hacky_display.obj 
if not %errorlevel% == 0 goto :end

set warning_options_to_reconsider= -wd4477 -wd4127 -wd4702 -wd4883
set padding_warnings= -wd4324 -wd4820
set warning_options= -Wall -wd4210 -wd4200 -wd4201 -wd4152 -wd4061 -wd4710 -wd4711 -wd4062 -wd4464 -wd5045 -wd5274 %padding_warnings% %warning_options_to_reconsider% 

:: /GS- prevents security cookies which introduce 'length changing prefixes', which vtune complains about. Maybe it's not a big deal though ~3%.

cl /nologo /std:c11 /GS- /diagnostics:column /c  %warning_options% %target_source% %optimization% /Z7 src/main.c /Fo:build\snafuzz.obj
if not %errorlevel% == 0 goto :end

link /nologo /INCREMENTAL:no /DEBUG build\snafuzz.obj build\hacky_display.obj kernel32.lib ntdll.lib /PDB:build\snafuzz.pdb /OUT:snafuzz.exe 

:end
