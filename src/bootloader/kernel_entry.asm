[bits 32]
[extern main] ; main is defined in C

section .text
global _start

_start:
	call main
	jmp $
