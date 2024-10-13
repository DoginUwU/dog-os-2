start:
	mov ah, 0x0e ; https://en.wikipedia.org/wiki/BIOS_interrupt_call
	mov al, 'H'
	int 0x10 ; call 10h - BIOS video service
	mov al, 'e'
	int 0x10
	mov al, 'l'
	int 0x10
	int 0x10
	mov al, 'o'
	int 0x10

times 510-($-$$) db 0

dw 0xaa55
