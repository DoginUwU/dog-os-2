ENTRY(_start)

SECTIONS {
	. = 1M;

	kernel_virtual_start = .;

	.boot : ALIGN(4K) {
		*(.boot)
	}

	.text : ALIGN(4K) {
		*(.text)
	}

	.rodata : ALIGN(4K) {
		*(.rodata)
	}

	.data : ALIGN(4K) {
		*(.data)
	}

	.bss : ALIGN(4K) {
		*(COMMON)
		*(.bss)
	}

	kernel_virtual_end = .;
}
