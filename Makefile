ARCH		= x86_64

prefix		= $(ARCH)-w64-mingw32-
CC 			= $(prefix)gcc

CFLAGS 		= --std=c99 -shared -nostdlib -mno-red-zone -fno-stack-protector -Wall -e EfiMain

FORMAT		= efi-app-$(ARCH)

all: qemu

%.efi: %.dll
	objcopy --target=$(FORMAT) $< $@

%.dll: %.c
	$(CC) $(CFLAGS) $< -o $@

qemu: main.efi OVMF/OVMF.fd image/EFI/BOOT/BOOTX64.EFI
	qemu-system-x86_64 -nographic -L OVMF/ -bios OVMF/OVMF.fd -hda fat:image

image/EFI/BOOT/BOOTX64.EFI:
	mkdir -p image/EFI/BOOT
	ln -sf ../../../main.efi image/EFI/BOOT/BOOTX64.EFI

OVMF/OVMF.fd:
	mkdir OVMF
	wget -nc http://downloads.sourceforge.net/project/edk2/OVMF/OVMF-X64-r15214.zip
	unzip OVMF-X64-r15214.zip OVMF.fd -d OVMF

clean:
	rm -f main.efi
