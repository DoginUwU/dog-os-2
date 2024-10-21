bits 32

PAGE_ALIGN equ 1 << 0
MEM_INFO equ 1 << 1
USE_GFX equ 0

MAGIC_NUMBER equ 0x1BADB002
FLAGS equ PAGE_ALIGN | MEM_INFO | USE_GFX
CHECKSUM equ -(MAGIC_NUMBER + FLAGS)

section .multiboot
align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM
	dd 0, 0, 0, 0, 0

	dd 0   ; Graphic mode
	dd 800 ; Width
	dd 600 ; Height
	dd 32  ; Depth

section .bss
align 16
stack_bottom:
	resb 16384 * 8
stack_top:

section .boot
global _start

_start:
	mov ecx, (initial_page_directory - 0xC0000000)
	mov cr3, ecx 

	mov ecx, cr4
	or ecx, 0x10 ; enable physical address extension
	mov cr4, ecx

	mov ecx, cr0
	or ecx, 0x80000000 ; enable 32-bit paging
	mov cr0, ecx

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
	hlt
	jmp halt

section .data
align 4096
global initial_page_directory

initial_page_directory:
	dd 10000011b 		; P | R/W | PS (4mb)
	times 768-1 dd 0
	dd (0 << 22) | 10000011b ; 0 to 4mb
	dd (1 << 22) | 10000011b ; 4 to 8mb
	dd (2 << 22) | 10000011b ; 8 to 12mb
	dd (3 << 22) | 10000011b ; 12 to 16mb
	times 256-4 dd 0
