CC = i686-linux-gnu-gcc
LD = i686-linux-gnu-ld
NASM = nasm
QEMU = qemu-system-x86_64

SRC_DIR = src
KERNEL_DIR = $(SRC_DIR)/kernel
DRIVERS_DIR = $(SRC_DIR)/drivers
BOOTLOADER_DIR = $(SRC_DIR)/bootloader
DIST_DIR = dist

# Fontes e cabeçalhos
C_SOURCES = $(wildcard $(KERNEL_DIR)/*.c $(DRIVERS_DIR)/*.c)
C_HEADERS = $(wildcard $(KERNEL_DIR)/*.h $(DRIVERS_DIR)/*.h)

# Arquivos objeto
OBJ = $(patsubst %.c, $(DIST_DIR)/%.o, $(notdir $(C_SOURCES)))

KERNEL_ENTRY_OBJ = $(DIST_DIR)/kernel_entry.o
BOOT_BIN = $(DIST_DIR)/boot.bin
KERNEL_BIN = $(DIST_DIR)/kernel.bin
KERNEL_ELF = $(DIST_DIR)/kernel.elf
OS_BIN = $(DIST_DIR)/os.bin

# Regra para compilar os arquivos .c para .o
$(DIST_DIR)/%.o: $(KERNEL_DIR)/%.c $(C_HEADERS)
	$(CC) -ffreestanding -g -c $< -o $@

$(DIST_DIR)/%.o: $(DRIVERS_DIR)/%.c $(C_HEADERS)
	$(CC) -ffreestanding -g -c $< -o $@

# Kernel entry em assembly
$(KERNEL_ENTRY_OBJ): $(BOOTLOADER_DIR)/kernel_entry.asm
	$(NASM) $< -f elf -o $@

# Linkar o kernel
$(KERNEL_BIN): $(KERNEL_ENTRY_OBJ) $(OBJ)
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

# Compilar o bootloader
$(BOOT_BIN): $(BOOTLOADER_DIR)/boot.asm
	$(NASM) -f bin $< -o $@

# Gerar o binário final do OS
$(OS_BIN): $(BOOT_BIN) $(KERNEL_BIN)
	cat $^ > $@

# Gerar o ELF do kernel
$(KERNEL_ELF): $(KERNEL_ENTRY_OBJ) $(OBJ)
	$(LD) -o $@ -Ttext 0x1000 $^

# Target para compilar o bootloader e o kernel
bootloader: $(KERNEL_BIN) $(BOOT_BIN) $(KERNEL_ELF) $(OS_BIN)

# Rodar o OS no QEMU
run: podman
	$(QEMU) -fda $(OS_BIN)

# Rodar em modo debug
debug: podman
	$(QEMU) -fda $(OS_BIN) -s -S &
	sleep 1
	gdb -ex "target remote localhost:1234" -ex "symbol-file $(KERNEL_ELF)"

# Limpar os arquivos compilados
clean:
	rm -f $(DIST_DIR)/*.bin $(DIST_DIR)/*.o $(DIST_DIR)/*.elf

# Usar podman para compilar
podman:
	podman run --rm docker.io/dockcross/linux-i686 > $(DIST_DIR)/dockcross-linux-i686
	chmod +x $(DIST_DIR)/dockcross-linux-i686
	$(DIST_DIR)/dockcross-linux-i686 make bootloader

