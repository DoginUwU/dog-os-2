QEMU = qemu-system-x86_64

DIST_DIR = dist

KERNEL_BIN = $(DIST_DIR)/boot/kernel.bin
OS_ISO = $(DIST_DIR)/dog-os.iso

GENERATE_DATABASE = false

run: podman
	$(QEMU) -cdrom $(OS_ISO)

debug: podman
	$(QEMU) -cdrom $(OS_ISO) -s -S &
	sleep 1
	gdb -ex "target remote localhost:1234" -ex "symbol-file $(KERNEL_BIN)"

podman:
	make clean
	podman run --rm docker.io/dockcross/linux-x86_64-full > $(DIST_DIR)/dockcross-linux-x86_64-full
	chmod +x $(DIST_DIR)/dockcross-linux-x86_64-full
ifeq ($(GENERATE_DATABASE), true)
		$(DIST_DIR)/dockcross-linux-x86_64-full make compile_commands.json -f docker/Makefile
else 
		$(DIST_DIR)/dockcross-linux-x86_64-full make -f docker/Makefile
endif

clean:
	rm -rf $(DIST_DIR)
	mkdir -p $(DIST_DIR)

.PHONY: run debug podman clean
