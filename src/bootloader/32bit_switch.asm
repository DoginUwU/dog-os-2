[bits 16]
switch_to_pm:
	cli ; Disable interrupts
	lgdt [gdt_descriptor] ; Load the GDT
	mov eax, cr0 ; Load the control register 0
	or eax, 0x1 ; Set 32 bit mode
	mov cr0, eax ; Save the control register 0
	jmp CODE_SEG:init_pm ; Jump to the code segment

[bits 32]
init_pm:
	mov ax, DATA_SEG ; Load the data segment
	mov ds, ax ; Set the data segment
	mov ss, ax ; Set the stack segment
	mov es, ax ; Set the extra segment
	mov fs, ax ; Set the fs segment
	mov gs, ax ; Set the gs segment

	mov ebp, 0x90000 ; Update the stack pointer
	mov esp, ebp ; Set the stack pointer

	call BEGIN_PM ; Call the main function
