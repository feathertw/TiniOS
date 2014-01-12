SECTIONS
{

	. = 0x0;
	.text :
	{
		obj/boot.o(.text)
		*(.text)
	}

	.rel : 
	{ 
	
	}

	. = 0x01000000;
	.data :
	{
		*(.rodata*)
		*(.data)
	}
	.bss :
	{
		*(.bss)
	}
}
