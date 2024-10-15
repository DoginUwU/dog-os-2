ENTRY(_start)

SECTIONS {
	. = 1M;

	.text : {
		*(.text)
	}

	.bss : {
		*(.bss)
	}

	.data : {
		*(.data)
	}
}
