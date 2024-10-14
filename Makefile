QEMU = qemu-system-x86_64

DIST_DIR = dist

KERNEL_ELF = $(DIST_DIR)/kernel.elf
OS_BIN = $(DIST_DIR)/os.bin

run: podman
	$(QEMU) -fda $(OS_BIN)

debug: podman
	$(QEMU) -fda $(OS_BIN) -s -S &
	sleep 1
	gdb -ex "target remote localhost:1234" -ex "symbol-file $(KERNEL_ELF)"

podman:
	mkdir -p $(DIST_DIR)
	mkdir -p $(DIST_DIR)/kernel
	mkdir -p $(DIST_DIR)/drivers
	mkdir -p $(DIST_DIR)/cpu
	podman run --rm docker.io/dockcross/linux-i686 > $(DIST_DIR)/dockcross-linux-i686
	chmod +x $(DIST_DIR)/dockcross-linux-i686
	$(DIST_DIR)/dockcross-linux-i686 make -f docker/Makefile

clean:
	rm -f $(DIST_DIR)/*.bin $(DIST_DIR)/*.o $(DIST_DIR)/*.elf

