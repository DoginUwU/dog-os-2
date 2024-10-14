CC = i686-linux-gnu-gcc
LD = i686-linux-gnu-ld
NASM = nasm
CFLAGS = -g -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror

SRC_DIR = src
DIST_DIR = dist

C_SOURCES = $(shell find ${SRC_DIR} -name '*.c')
C_HEADERS = $(shell find ${SRC_DIR} -name '*.h')

OBJ = $(patsubst ${SRC_DIR}/%.c, ${DIST_DIR}/%.o, ${C_SOURCES}) ${DIST_DIR}/cpu/interrupt.o
DIST_DIRS = $(sort $(dir ${OBJ} ${DIST_DIR}/boot.bin ${DIST_DIR}/kernel.bin))

create-image: ${DIST_DIR}/boot.bin ${DIST_DIR}/kernel.bin
	cat $^ > ${DIST_DIR}/os.bin
	rm -f $^

$(DIST_DIRS):
	mkdir -p $@

${DIST_DIR}/kernel.bin: ${DIST_DIR}/kernel_entry.o ${OBJ} | $(DIST_DIRS)
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

${DIST_DIR}/kernel_entry.o: ${SRC_DIR}/bootloader/kernel_entry.asm | $(DIST_DIRS)
	${NASM} -f elf $< -o $@

# For debbuging
${DIST_DIR}/kernel.elf: ${DIST_DIR}/kernel_entry.o ${OBJ} | $(DIST_DIRS)
	${LD} -o $@ -Ttext 0x1000 $^

${DIST_DIR}/%.o: ${SRC_DIR}/%.c ${C_HEADERS} | $(DIST_DIRS)
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

${DIST_DIR}/%.o: ${SRC_DIR}/%.asm | $(DIST_DIRS)
	${NASM} -f elf $< -o $@

${DIST_DIR}/%.bin: ${SRC_DIR}/bootloader/%.asm | $(DIST_DIRS)
	${NASM} -f bin $< -o $@

