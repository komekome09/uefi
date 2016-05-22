CC = x86_64-w64-mingw32-gcc
CFLAGS = -std=c99 -shared -nostdlib -mno-red-zone -fno-stack-protector -Wall \
         -e EfiMain -pedantic

all: main.efi

%.efi: %.dll
	objcopy --target=efi-app-x86_64 $< $@

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
