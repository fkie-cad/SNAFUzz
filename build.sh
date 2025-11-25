


target_source=""

if [ -n "$1" ]; then
    if [[ "$1" == /* ]]; then
        target_source="$1"
    else
        target_source="../$1"
    fi
    target_source="-DTARGET_SOURCE=$target_source"
fi

clang -ffreestanding -MMD -mno-red-zone -g -std=c11 -target x86_64-unknown-windows -m64 -ferror-limit=1 -w -mavx src/uefi_bios.c -fms-extensions -mno-stack-arg-probe -c -o build/bios.obj
lld -flavor link -subsystem:efi_application -entry:entry -base:0x100000 build/bios.obj -DEBUG -out:build/bios.exe -pdb:build/bios.pdb

clang src/main.c src/hacky_display.c src/linux_weak_aliases.c $target_source -g -Wno-multichar -Wno-format -Wno-bool-operation -Wno-gnu-folding-constant -ferror-limit=1 -mavx  -lcurl -lpthread -lX11 -o snafuzz


