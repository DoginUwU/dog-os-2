[org 0x7c00]

start:
	mov bx, TEST ; Load the data to bx
	call print ; Print the data
	call print_nl ; Print newline

	mov bp, 0x8000 ; Set the stack pointer
	mov sp, bp ; Init empty stack

	mov bx, 0x9000 ; Load the data to 0x9000
	mov dh, 2 ; Load the sector number
	call disk_load

	mov dx, [0x9000] ; Load the data to dx
	call print_hex
	call print_nl

	mov dx, [0x9000 + 512] ; First word from second sector
	call print_hex
	call print_nl

%include "src/bootloader/print.asm"
%include "src/bootloader/print_hex.asm"
%include "src/bootloader/disk.asm"

TEST:
	db 'DogOS Bootloader', 0

times 510-($-$$) db 0
dw 0xaa55

; boot sector = sector 1 cylinder 0 head 0
times 256 dw 0xdada ; sector 2 = 512 bytes
times 256 dw 0xface ; sector 3 = 512 bytes
