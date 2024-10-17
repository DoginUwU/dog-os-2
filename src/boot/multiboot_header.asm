[bits 32]

MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x00

section .text
align 4
multiboot_header:
		dd MAGIC_NUMBER
		dd FLAGS
		dd - (MAGIC_NUMBER + FLAGS)
