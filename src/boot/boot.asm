bits 32

PAGE_ALIGN equ 1 << 0
MEM_INFO equ 1 << 1
USE_GFX equ 0

MAGIC_NUMBER equ 0x1BADB002
FLAGS equ PAGE_ALIGN | MEM_INFO | USE_GFX
CHECKSUM equ -(MAGIC_NUMBER + FLAGS)

section .boot
align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM
	dd 0, 0, 0, 0, 0

	dd 0   ; Graphic mode
	dd 800 ; Width
	dd 600 ; Height
	dd 32  ; Depth

global _start

_start:
	jmp higher_half

section .text
extern kernel_main
higher_half:
	mov esp, stack_top
	push ebx
	push eax
	xor ebp, ebp
	call kernel_main

halt:
	cli
	hlt
	jmp halt

section .data
align 4096

section .bss
align 16
stack_bottom:
	resb 16384 * 8
stack_top:

