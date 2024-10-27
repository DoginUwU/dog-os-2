MULTIBOOT_MAGIC equ 0xE85250D6
MULTIBOOT_ARCH equ 0 ; 0 for i386, 4 for MIPS

section .boot
header_start:
	dd MULTIBOOT_MAGIC
	dd MULTIBOOT_ARCH
	dd header_end - header_start ; header length
	dd 0x100000000 - (MULTIBOOT_MAGIC + MULTIBOOT_ARCH + (header_end - header_start))

	dw 0 ; type
	dw 0 ; flags
	dd 8 ; size
header_end:

bits 32
section .text
global _start
extern kernel_main
_start:
	call kernel_main
