gdt_start: 
	; GDT starts with zeros 8 bytes
	dd 0x0 ; null descriptor
	dd 0x0 ; null descriptor

; GDT segment: base = 0x0, length = 0xfffff
gdt_code:
	dw 0xffff ; limit
	dw 0x0 ; base 0-15
	db 0x0 ; base 16-23
	db 10011010b ; access https://wiki.osdev.org/Global_Descriptor_Table
	db 11001111b ; flags
	db 0x0

gdt_data:
	dw 0xffff ; limit
	dw 0x0 ; base 0-15
	db 0x0 ; base 16-23
	db 10010010b ; access https://wiki.osdev.org/Global_Descriptor_Table
	db 11001111b ; flags
	db 0x0

gdt_end:

gdt_descriptor:
	dw gdt_end - gdt_start - 1 ; size of GDT, always one less of true size
	dd gdt_start ; base address of GDT

; constants
CODE_SEQ equ gdt_code - gdt_start
DATA_SEQ equ gdt_data - gdt_start
