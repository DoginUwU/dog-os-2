CC = i686-linux-gnu-gcc
LD = i686-linux-gnu-ld
NASM = nasm
CFLAGS = -g

SRC_DIR = src
DIST_DIR = dist

C_SOURCES = $(wildcard ${SRC_DIR}/kernel/*.c ${SRC_DIR}/drivers/*.c ${SRC_DIR}/cpu/*.c)
C_HEADERS = $(wildcard ${SRC_DIR}/kernel/*.h ${SRC_DIR}/drivers/*.h ${SRC_DIR}/cpu/*.h)

OBJ = $(patsubst ${SRC_DIR}/%.c, ${DIST_DIR}/%.o, ${C_SOURCES}) ${DIST_DIR}/cpu/interrupt.o

create-image: ${DIST_DIR}/boot.bin ${DIST_DIR}/kernel.bin
	cat $^ > ${DIST_DIR}/os.bin
	rm -f $^

${DIST_DIR}/kernel.bin: ${DIST_DIR}/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

${DIST_DIR}/kernel_entry.o: ${SRC_DIR}/bootloader/kernel_entry.asm
	${NASM} -f elf $< -o $@

# For debbuging
${DIST_DIR}/kernel.elf: ${DIST_DIR}/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^

${DIST_DIR}/%.o: ${SRC_DIR}/%.c ${C_HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

${DIST_DIR}/%.o: ${SRC_DIR}/%.asm
	${NASM} -f elf $< -o $@

${DIST_DIR}/%.bin: ${SRC_DIR}/bootloader/%.asm
	${NASM} -f bin $< -o $@

