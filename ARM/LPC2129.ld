STACK_SIZE = 0x400;

/* Memory definitons LPC2129 */
MEMORY
{
	ROM (rx) : ORIGIN = 0x00000000, LENGTH = 0x0003E000
	RAM (rw) : ORIGIN = 0x40000000, LENGTH = 0x00004000
}

/* Section Definitions */
SECTIONS
{
	.init :
	{
		KEEP(*(.init))				/* isr vectors and  init */
	}
	. = ALIGN(4);

	.text :
	{
		*(.text)                   /* code */
		*(.rodata)                 /* constants */
		*(.rodata*)
		*(.glue_7)
		*(.glue_7t)
	} > ROM
	. = ALIGN(4);

	_etext = . ;

	/* initialzed data */
	.data :
	{
		_data = .;
		*(.data)
	} > RAM AT> ROM
	. = ALIGN(4);

	_edata = . ;

	/* uninitialized data */
	.bss (NOLOAD) :
	{
		_bss_start = . ;
		*(.bss)
		*(COMMON)
	} > RAM
	. = ALIGN(4);

	_bss_end = . ;

	/* left space for stack */
	.stack (NOLOAD) :
	{
        . = ALIGN(4);
		. += STACK_SIZE;
		_stack = . ;
	} > RAM

	_end = . ;
}
