ENTRY(_start)

SECTIONS {
	. = 0x00100000;
	kernel_phyiscal_start = .;

	.boot ALIGN(4K): {
		*(.boot)
	}

	.text ALIGN(4K): AT(ADDR(.text)) {
		_kernel_code_start = .;
		*(.text)
		_kernel_code_end = .;
	}

	.rodata ALIGN(4K): AT(ADDR(.rodata)) {
		*(.rodata)
	}

	.data ALIGN(4K): AT(ADDR(.data)) {
		*(.data)
	}

	.bss ALIGN(4K): AT(ADDR(.bss)) {
		*(COMMON)
		*(.bss)
	}

	.kernel_stack ALIGN(4K): {
			_kernel_stack_start = .;
			. += 8K;   
			_kernel_stack_end = .;
	}

	.user_code ALIGN(4K): {
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
	kernel_physical_end = .;
}
