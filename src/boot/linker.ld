ENTRY(_start)

SECTIONS {
	. = 0x00100000;

	.multiboot ALIGN(4K): {
		*(.multiboot)
	}

	.note.gnu.build-id ALIGN(4K): {
		*(.note.gnu.build-id)
	}

	.boot ALIGN(4K): {
		*(.boot)
	}

	/*. += 0xC0000000;*/

	.text ALIGN(4K): /* AT(ADDR(.text) - 0xC0000000) */ {
		*(.text)
	}

	.rodata ALIGN(4K): {
		*(.rodata)
	}

	.data ALIGN(4K): {
		*(.data)
	}

	.bss ALIGN(4K): {
		*(COMMON)
		*(.bss)
	}

	_kernel_end = .;
}
