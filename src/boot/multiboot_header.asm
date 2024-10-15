[extern kernel_main]

PAGE_ALIGN    equ 1<<0
MEM_INFO      equ 1<<1
FLAGS         equ PAGE_ALIGN | MEM_INFO
MAGIC         equ 0x1BADB002
CHECKSUM      equ -(MAGIC + FLAGS)

[bits 32]

section .multiboot
	align 4
	multiboot:
		dd MAGIC
		dd FLAGS
		dd CHECKSUM

section .text
global _start
_start:
	push ebx
	cli
	;call kernel_main
	jmp $

