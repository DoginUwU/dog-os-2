bootloader:
	nasm -f bin src/bootloader/boot.asm -o dist/boot.bin
	qemu-system-x86_64 dist/boot.bin
