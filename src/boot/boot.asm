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
	;mov ecx, (initial_page_dir - 0xC0000000)
	;mov cr3, ecx ; page directory loc
	;
	;mov ecx, cr4
	;or ecx, 0x10
	;mov cr4, ecx
	;
	;mov ecx, cr0
	;or ecx, 0x80000000 ; enable 32-bit paging
	;mov cr0, ecx

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
;global initial_page_dir

;initial_page_dir:
;	dd 10000011b
;	times 768-1 dd 0
;
;	dd (0 << 22) | 10000011b
;	dd (1 << 22) | 10000011b
;	dd (2 << 22) | 10000011b
;	dd (3 << 22) | 10000011b
;	times 256-4 dd 0
