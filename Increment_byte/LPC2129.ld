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
		. = ALIGN(4);
		KEEP(*(.init))		/* isr vectors and  init */
		. = ALIGN(4);
	}

	.text :
	{
		. = ALIGN(4);
		*(.text)                   /* code */
		*(.rodata)                 /* constants */
		*(.rodata*)
		*(.glue_7)
		*(.glue_7t)
		. = ALIGN(4);
		_etext = .;
	} > ROM

	/* initialzed data */
	.data :
	{
		. = ALIGN(4);
		_sdata = .;
		*(.data)
		*(.data*)
		. = ALIGN(4);
		_edata = .;
	} > RAM AT> ROM

	/* uninitialized data */
	.bss (NOLOAD) :
	{
		. = ALIGN(4);
		_sbss = .;
		*(.bss)
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
	} > RAM

	/* left space for stack */
	.stack (NOLOAD) :
	{
		. = ALIGN(4);
		. += STACK_SIZE;
		. = ALIGN(4);
		_stack = . ;
	} > RAM
}
