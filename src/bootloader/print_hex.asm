print_hex:
	pusha
	mov cx, 0 ; variable index

print_hex_loop:
	cmp cx, 4 ; compare index with 4
	je print_hex_end ; if equal, end the loop

	mov ax, dx ; load the data to ax
	and ax, 0x000f ; mask the data
	add al, 0x30 ; convert to ascii
	cmp al, 0x39 ; compare if al is greater than 9
	jle print_hex_no_add ; if less or equal, skip
	add al, 0x07 ; add 7 to convert to ascii

print_hex_no_add:
	mov bx, HEX_OUT + 5 ; base + length
	sub bx, cx ; subtract index
	mov [bx], al ; copy the ascii to the output
	ror dx, 4 ; rotate the data to the right

	inc cx ; increment index
	jmp print_hex_loop ; loop

print_hex_end:
	mov bx, HEX_OUT ; load the output
	call print ; print the output

	popa
	ret

HEX_OUT:
	db '0x0000', 0 ; reserve 6 bytes for the output
