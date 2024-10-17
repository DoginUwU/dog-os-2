CC = gcc
LD = ld
NASM = nasm
CFLAGS = -Isrc/include -g -ffreestanding -Wall -Wextra -fno-exceptions -m32 -nodefaultlibs -fno-builtin -fno-stack-protector

SRC_DIR = src
DIST_DIR = dist

C_SOURCES = $(shell find ${SRC_DIR} -name '*.c')
C_HEADERS = $(shell find ${SRC_DIR} -name '*.h')

OBJ = $(patsubst ${SRC_DIR}/%.c, ${DIST_DIR}/%.o, ${C_SOURCES}) ${DIST_DIR}/boot/interrupt.o ${DIST_DIR}/boot/gdt.o
# OBJ =
DIST_DIRS = $(sort $(dir ${OBJ} ${DIST_DIR}/boot/boot.bin ${DIST_DIR}/boot/kernel.bin))

create-image-with-grub: ${DIST_DIR}/boot/kernel.bin
	apt install -y grub-pc-bin grub-common xorriso
	grub-file --is-x86-multiboot ${DIST_DIR}/boot/kernel.bin
	mkdir -p ${DIST_DIR}/iso/boot/grub
	cp ${DIST_DIR}/boot/kernel.bin ${DIST_DIR}/iso/boot/kernel.bin
	cp ${SRC_DIR}/boot/grub.cfg ${DIST_DIR}/iso/boot/grub/grub.cfg
	grub-mkrescue -o ${DIST_DIR}/dog-os.iso ${DIST_DIR}/iso

compile_commands.json:
	apt install -y bear
	bear -- make -f docker/Makefile -B

$(DIST_DIRS):
	mkdir -p $@

${DIST_DIR}/boot/kernel.bin: ${DIST_DIR}/boot/multiboot_header.o ${DIST_DIR}/boot/boot.o ${OBJ} | $(DIST_DIRS)
	${LD} -m elf_i386 -n -T ${SRC_DIR}/boot/linker.ld $^ -o $@

${DIST_DIR}/%.o: ${SRC_DIR}/%.c ${C_HEADERS} | $(DIST_DIRS)
	${CC} ${CFLAGS} -c $< -o $@

${DIST_DIR}/%.o: ${SRC_DIR}/%.asm | $(DIST_DIRS)
		${NASM} -f elf32 $< -o $@

