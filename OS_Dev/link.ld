ENTRY(loader) /*name of label*/

SECTIONS {
	. = 0x00100000; /*1 MB where no conflict with addresses used by GRUB*/

	.text ALIGN (0x1000) : /* Align 4 KB*/
	{
		*(.text)  
	}

	.rodata ALIGN (0x1000) :
	{
		*(.rodata*)  /*read only data*/
	}

	.data ALIGN (0x1000) :
	{
		*(.data)
	}

	.bss ALIGN (0x1000) :
	{
		*(COMMON)
		*(.bss)
	}
}
