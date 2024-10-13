bootloader:
	nasm -f bin src/bootloader/boot.asm -o dist/boot.bin
	qemu-system-x86_64 -fda dist/boot.bin

clean:
	rm -f dist/boot.bin
