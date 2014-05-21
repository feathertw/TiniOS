MEMORY
{
	FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x00040000
	RAM (rwx) :  ORIGIN = 0x01000000, LENGTH = 0x00040000
}
SECTIONS
{

	.text :
	{
		_stext = . ;
		*(vectors)
		*(.text)
		_etext = . ;
	} > FLASH

	.rel : 
	{ 
	
	} > FLASH

	.data : AT(_etext)
	{
		_sdata = . ;
		*(.rodata*)
		*(.data)
		_edata = . ;
	} > RAM
	data_size = _edata - _sdata ;

	.bss :
	{
		_sbss = . ;
		*(.bss)
		_ebss = . ;
	} > RAM
	bss_size = _ebss - _sbss ;
}
