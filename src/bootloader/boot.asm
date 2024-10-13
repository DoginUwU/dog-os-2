[org 0x7c00]

start:
	mov ah, 0x0e ; https://en.wikipedia.org/wiki/BIOS_interrupt_call

	mov bp, 0x8000 ; base of the stack
	mov sp, bp ; the stack if empty, the top is the base

	push 'A'
	push 'B'
	push 'C'

	mov al, [0x7FFE] ; 0x8000 - 2 - Its only possible acces the stack top
	int 0x10

	pop bx ; C
	mov al, bl ; Move the lower BX to al
	int 0x10

	pop bx ; B
	mov al, bl 
	int 0x10

	pop bx ; A
	mov al, bl
	int 0x10

	mov al, [0x8000] ; garbage
	int 0x10

times 510-($-$$) db 0

dw 0xaa55
