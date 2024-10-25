ENTRY(_start)

SECTIONS {
	. = 0x00100000;
	kernel_phyiscal_start = .;

	.boot ALIGN(4K): {
		*(.boot)
	}

	. += 0xC0000000;

	.text ALIGN(4K): AT(ADDR(.text) - 0xC0000000) {
		_kernel_code_start = .;
		*(.text)
		_kernel_code_end = .;
	}

	.rodata ALIGN(4K): AT(ADDR(.rodata) - 0xC0000000) {
		*(.rodata)
	}

	.data ALIGN(4K): AT(ADDR(.data) - 0xC0000000) {
		*(.data)
	}

	.bss ALIGN(4K): AT(ADDR(.bss) - 0xC0000000) {
		*(COMMON)
		*(.bss)
	}

	.kernel_stack ALIGN(4K): AT(ADDR(.kernel_stack) - 0xC0000000) {
			_kernel_stack_start = .;
			. += 8K;   
			_kernel_stack_end = .;
	}

	. = 0x00000000;

	.user_code ALIGN(4k): {
		_user_code_start = .;
		*(.user_text)
		_user_code_end = .;
	}

	.user_stack ALIGN(4K): {
		_user_stack_start = .;
		*(.user_stack)
		_user_stack_end = .;
	}

	kernel_virtual_end = .;
	kernel_physical_end = . + 0xC0000000;
}
