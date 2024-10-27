CC = i686-unknown-linux-gnu-gcc
LD = i686-unknown-linux-gnu-ld
QEMU = qemu-system-x86_64
NASM = nasm
CFLAGS = -Isrc/include -g -ffreestanding -Wall -Wextra -fno-exceptions -m32 -nodefaultlibs -fno-builtin -fno-stack-protector

SRC_DIR = src
BOOT_DIR = boot/arch
DIST_DIR = dist

C_SOURCES = $(shell find $(SRC_DIR) -name '*.c')
C_HEADERS = $(shell find $(SRC_DIR) -name '*.h')

OBJ = $(patsubst $(SRC_DIR)/%.c, $(DIST_DIR)/%.o, $(C_SOURCES)) $(DIST_DIR)/$(BOOT_DIR)/boot.o

qemu:
	make grub
	$(QEMU) -cdrom $(DIST_DIR)/dog-os.iso

qemu-debug:
	make grub
	$(QEMU) -s -S -cdrom $(DIST_DIR)/dog-os.iso &
	sleep 1
	gdb -ex "target remote localhost:1234" -ex "symbol-file $(DIST_DIR)/kernel.bin"

grub: $(DIST_DIR)/kernel.bin
	grub-file --is-x86-multiboot2 $(DIST_DIR)/kernel.bin
	mkdir -p $(DIST_DIR)/iso/boot/grub
	cp $(DIST_DIR)/kernel.bin $(DIST_DIR)/iso/boot/kernel.bin
	cp $(SRC_DIR)/$(BOOT_DIR)/grub.cfg $(DIST_DIR)/iso/boot/grub/grub.cfg
	grub-mkrescue -o $(DIST_DIR)/dog-os.iso $(DIST_DIR)/iso

bear:
	bear -- make grub -B

$(MKDIR_DIST):
	mkdir -p $@

$(DIST_DIR)/kernel.bin: $(OBJ) | $(MKDIR_DIST)
	$(LD) -m elf_i386 -n -T $(SRC_DIR)/$(BOOT_DIR)/linker.ld $^ -o $@

$(DIST_DIR)/%.o: $(SRC_DIR)/%.c $(C_HEADERS) | $(MKDIR_DIST)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIST_DIR)/%.o: $(SRC_DIR)/%.asm | $(MKDIR_DIST)
		$(NASM) -f elf32 $< -o $@
