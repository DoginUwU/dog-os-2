[GLOBAL _start]
[extern kernel_main]

section .multiboot
align 4
    dd 0x1BADB002            ; magic number
    dd 0x00                  ; flags
    dd -(0x1BADB002 + 0x00)  ; checksum

section .text
global _start
_start:
		push ebx
		cli
    call kernel_main
		jmp $
;
;section .bss
;align 4
;		resb 8192
;
;section .data
;align 4
;		kernel_stack_bottom:
;		resb 8192
;		kernel_stack_top:
;		resb 0

