disk_load:
	pusha
	; Push DX to stack, because it will be used by the disk interrupt
	push dx

	; https://stanislavs.org/helppc/int_13-2.html
	mov ah, 0x02 ; Read sector function
	mov al, dh ; Sector number
	mov cl, 0x02 ; Sector number
	mov ch, 0x00 ; Cylinder number
	mov dh, 0x00 ; Head number
	mov dl, 0x00 ; Drive number (0x00 for floppy)

	int 0x13 ; Call the interrupt
	jc disk_error ; Jump if carry flag is set

	; Pop DX from stack
	pop dx
	cmp al, dh ; Compare the read sector with the requested sector
	jne sectors_error
	popa
	ret

disk_error:
	mov bx, DISK_ERROR
	call print
	call print_nl
	mov dh, ah ; AH = error code, DL = drive number
	call print_hex ; https://stanislavs.org/helppc/int_13-1.html
	call print_nl

sectors_error:
	mov bx, SECTORS_ERROR
	call print

DISK_ERROR:
	db 'Disk error', 0

SECTORS_ERROR:
	db 'Sector error', 0
