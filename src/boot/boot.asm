[bits 32]
section .text
	align 4

[global _start]
[extern kernel_main]

_start:
		cli
		mov esp, stack_space
		call kernel_main
		jmp $

HaltKernel:
	cli
	hlt
	jmp HaltKernel

section .bss
resb 8192

stack_space:
