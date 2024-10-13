[bits 32]

; constants - https://wiki.osdev.org/Printing_To_Screen
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_string_pm:
	pusha
	mov edx, VIDEO_MEMORY ; Set the video memory address to edx

print_string_pm_loop:
	mov al, [ebx] ; Load the current character to al
	mov ah, WHITE_ON_BLACK ; Set the color to white on black

	cmp al, 0 ; Compare if end of string
	je print_string_pm_end ; If equal, end the loop

	mov [edx], ax ; Write the character to the video memory
	add ebx, 1 ; Move to the next character
	add edx, 2 ; Move to the next cell

	jmp print_string_pm_loop ; Loop

print_string_pm_end:
	popa
	ret
