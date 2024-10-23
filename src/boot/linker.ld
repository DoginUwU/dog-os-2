ENTRY(_start)

SECTIONS {
	. = 0x00100000;
	kernel_phyiscal_start = .;

	.boot ALIGN(4K): {
		*(.boot)
	}

	/*. += 0xC0000000;*/
	kernel_virtual_start = .;

	.text ALIGN(4K): AT(ADDR(.text)) {
		*(.text)
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

	kernel_virtual_end = .;
	kernel_physical_end = .;
}
