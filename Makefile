bootloader:
	nasm -f bin src/bootloader/boot.asm -o dist/boot.bin

run:
	make podman
	qemu-system-x86_64 -fda dist/boot.bin

clean:
	rm -f dist/boot.bin

podman:
	podman run --rm docker.io/dockcross/linux-x86_64-full > ./dist/dockcross-linux-x86_64-full
	chmod +x ./dist/dockcross-linux-x86_64-full
	./dist/dockcross-linux-x86_64-full make bootloader
