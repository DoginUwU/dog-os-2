[org 0x7c00]
KERNEL_OFFSET equ 0x1000

start:
	mov [BOOT_DRIVE], dl ; Save the boot drive
	mov bp, 0x9000 ; Set the stack pointer
	mov sp, bp ; Init empty stack

	mov bx, MSG_REAL_MODE
	call print
	call print_nl

	call load_kernel
	call switch_to_pm ; Switch to protected mode
	jmp $

%include "src/bootloader/print.asm"
%include "src/bootloader/print_hex.asm"
%include "src/bootloader/disk.asm"
%include "src/bootloader/gdt.asm"
%include "src/bootloader/32bit_print.asm"
%include "src/bootloader/32bit_switch.asm"

[bits 16]
load_kernel:
	mov bx, MSG_LOAD_KERNEL
	call print
	call print_nl

	mov bx, KERNEL_OFFSET; Read kernel from disk
	mov dh, 16; Sectors to load
	mov dl, [BOOT_DRIVE] ; Boot drive
	call disk_load
	ret

[bits 32]
BEGIN_PM:
	call KERNEL_OFFSET ; Call the kernel
	jmp $

BOOT_DRIVE db 0
MSG_REAL_MODE db 'DogOS Bootloader 16 bits', 0
MSG_PROTECTED_MODE db 'DogOS Bootloader 32 bits', 0
MSG_LOAD_KERNEL db 'Loading kernel...', 0

times 510-($-$$) db 0
dw 0xaa55
