CC = i686-linux-gnu-gcc
NASM = nasm
CFLAGS = -g -ffreestanding -Wall -Wextra -fno-exceptions -m32 -nodefaultlibs -nostdlib -nostdinc -fno-builtin -fno-stack-protector

SRC_DIR = src
DIST_DIR = dist

C_SOURCES = $(shell find ${SRC_DIR} -name '*.c')
C_HEADERS = $(shell find ${SRC_DIR} -name '*.h')

OBJ = $(patsubst ${SRC_DIR}/%.c, ${DIST_DIR}/%.o, ${C_SOURCES}) ${DIST_DIR}/cpu/interrupt.o
DIST_DIRS = $(sort $(dir ${OBJ} ${DIST_DIR}/boot.bin ${DIST_DIR}/kernel.bin))

create-image-with-grub: ${DIST_DIR}/kernel.bin
	apt install -y grub-pc-bin grub-common xorriso
	grub-file --is-x86-multiboot ${DIST_DIR}/kernel.bin
	mkdir -p ${DIST_DIR}/iso/boot/grub
	cp ${DIST_DIR}/kernel.bin ${DIST_DIR}/iso/boot/kernel.bin
	cp ${SRC_DIR}/grub.cfg ${DIST_DIR}/iso/boot/grub/grub.cfg
	grub-mkrescue -o ${DIST_DIR}/os.iso ${DIST_DIR}/iso

$(DIST_DIRS):
	mkdir -p $@

${DIST_DIR}/kernel.bin: ${DIST_DIR}/kernel_entry.o ${OBJ} | $(DIST_DIRS)
	${CC} -T ${SRC_DIR}/linker.ld $^ -o $@ ${CFLAGS}

${DIST_DIR}/kernel_entry.o: ${SRC_DIR}/grub/multiboot_header.asm | $(DIST_DIRS)
	${NASM} -f elf $< -o $@

# For debbuging
# ${DIST_DIR}/kernel.elf: ${DIST_DIR}/kernel_entry.o ${OBJ} | $(DIST_DIRS)
# 	${CC} -T ${SRC_DIR}/linker.ld $^ -o $@ ${CFLAGS}

${DIST_DIR}/%.o: ${SRC_DIR}/%.c ${C_HEADERS} | $(DIST_DIRS)
	${CC} ${CFLAGS} -c $< -o $@

${DIST_DIR}/%.o: ${SRC_DIR}/%.asm | $(DIST_DIRS)
	${NASM} -f elf $< -o $@

