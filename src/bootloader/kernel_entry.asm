[bits 32]
[extern kernel_main] ; main is defined in C

section .text
global _start

_start:
	call kernel_main
	jmp $
