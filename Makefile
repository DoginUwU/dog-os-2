bootloader:
	make test
	nasm -f bin src/bootloader/boot.asm -o dist/boot.bin

test:
	# i686-linux-gnu-gcc -ffreestanding -c src/kernel/function.c -o dist/function.o
	# i686-linux-gnu-ld -o dist/function.bin -Ttext 0x0 --oformat binary dist/function.o

run:
	make podman
	qemu-system-x86_64 -fda dist/boot.bin

clean:
	rm -f dist/boot.bin

podman:
	podman run --rm docker.io/dockcross/linux-i686 > ./dist/dockcross-linux-i686
	chmod +x ./dist/dockcross-linux-i686
	./dist/dockcross-linux-i686 make bootloader
