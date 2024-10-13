[org 0x7c00]

start:
	mov ah, 0x0e ; https://en.wikipedia.org/wiki/BIOS_interrupt_call
	mov al, [the_secret]
	int 0x10

the_secret:
	db "X"

times 510-($-$$) db 0

dw 0xaa55
