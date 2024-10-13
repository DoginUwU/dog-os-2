bootloader:
	i686-linux-gnu-gcc -ffreestanding -c src/kernel/kernel.c -o dist/kernel.o
	nasm src/bootloader/kernel_entry.asm -f elf -o dist/kernel_entry.o
	i686-linux-gnu-ld -o dist/kernel.bin -Ttext 0x1000 dist/kernel_entry.o dist/kernel.o --oformat binary
	nasm -f bin src/bootloader/boot.asm -o dist/boot.bin
	cat dist/boot.bin dist/kernel.bin > dist/os.bin
	rm dist/boot.bin dist/kernel.bin

run:
	make podman
	qemu-system-x86_64 -fda dist/os.bin

clean:
	rm -f dist/boot.bin

podman:
	podman run --rm docker.io/dockcross/linux-i686 > ./dist/dockcross-linux-i686
	chmod +x ./dist/dockcross-linux-i686
	./dist/dockcross-linux-i686 make bootloader
