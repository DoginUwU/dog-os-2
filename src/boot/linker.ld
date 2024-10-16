ENTRY(_start)

SECTIONS {
	. = 1M;

	.text : {
		*(.text)
	}

	.rodata : {
		*(.rodata)
	}

	.bss : {
		*(.bss)
	}

	.data : {
		*(.data)
	}
}
