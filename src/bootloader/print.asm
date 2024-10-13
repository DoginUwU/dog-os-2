print:
	pusha

; while (string[i] != 0) { print string[i]; i++ }

print_start:
	mov al, [bx] ; load the data to al
	cmp al, 0 ; compare if al is 0
	je print_end ; if equal, end the loop

	mov ah, 0x0e ; set the function to print (TTY)
	int 0x10 ; call the interrupt

	inc bx ; increment index
	jmp print_start ; loop

print_end:
	popa
	ret

print_nl:
	pusha

	mov ah, 0x0e ; set the function to print (TTY)
	mov al, 0x0a ; load the newline character
	int 0x10 ; call the interrupt
	mov al, 0x0d ; load the carriage return character
	int 0x10 ; call the interrupt

	popa
	ret
