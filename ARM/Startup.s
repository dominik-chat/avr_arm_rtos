	.global main                    	// int main(void)
	.global Int_UndefinedInstruction	// przerwanie niezdefiniowanej instrukcji
	.global Int_SoftwareInterrupt		// przerwanie programowe
	.global Int_ProgramAbort			// przerwanie prefetchu instrukcji
	.global Int_DataAbort				// przerwanie prefetchu danych
	.global Int_FIQ						// przerwanie szybkie FIQ

	.global _etext                  // poczatek .data w ROM (koniec text)
	.global _data                   // poczatek .data (RAM)
	.global _edata                  // koniec .data (RAM)
	.global _bss_start             	// poczatek .bss
	.global _bss_end             	// koniec .bss
	.global _stack                  // szczyt stosu
	
// Rozmiary stosow trybow specjalnych
	.set  UND_STACK_SIZE, 0x00000004
	.set  ABT_STACK_SIZE, 0x00000004
	.set  FIQ_STACK_SIZE, 0x00000004
	.set  IRQ_STACK_SIZE, 0X00000080
	.set  SVC_STACK_SIZE, 0x00000004

// Definicje trybow specjalnych
	.set  MODE_USR, 0x10            // User Mode
	.set  MODE_FIQ, 0x11            // FIQ Mode
	.set  MODE_IRQ, 0x12            // IRQ Mode
	.set  MODE_SVC, 0x13            // Supervisor Mode
	.set  MODE_ABT, 0x17            // Abort Mode
	.set  MODE_UND, 0x1B            // Undefined Mode
	.set  MODE_SYS, 0x1F            // System Mode

	.set  I_BIT, 0x80               // Bit wylaczenia przerwania irq
	.set  F_BIT, 0x40               // Bit wylaczenia przerwania fiq

	.section  .init
	.global isr_vectors

isr_vectors:
	ldr		pc, _start				// reset - start
	ldr   	pc, _undf               // undefined - _undf
	ldr   	pc, _swi                // SWI - _swi
	ldr   	pc, _pabt               // program abort - _pabt
	ldr   	pc, _dabt               // data abort - _dabt
	nop                             // reserved
	ldr   	pc, [pc,#-0xFF0]        // IRQ - funkcja z VIC
	ldr   	pc, _fiq                // FIQ - _fiq

_start:	.word start
_undf:  .word Int_UndefinedInstruction	// undefined 
_swi:   .word Int_SoftwareInterrupt		// SWI 
_pabt:  .word Int_ProgramAbort			// program abort
_dabt:  .word Int_DataAbort				// data abort
_irq:   .word _loop						// IRQ glownie wypelniacz, bo i tak czyta z VIC
_fiq:   .word Int_FIQ					// FIQ 

start:
//ustawienie stosow wszystkich trybow procesora
    ldr   r0, =_stack
	msr   CPSR_c, #MODE_UND|I_BIT|F_BIT // Undefined Instruction Mode
	mov   sp, r0
	sub   r0, r0, #UND_STACK_SIZE
	msr   CPSR_c, #MODE_ABT|I_BIT|F_BIT // Abort Mode
	mov   sp, r0
	sub   r0, r0, #ABT_STACK_SIZE
	msr   CPSR_c, #MODE_FIQ|I_BIT|F_BIT // FIQ Mode
	mov   sp, r0
	sub   r0, r0, #FIQ_STACK_SIZE
	msr   CPSR_c, #MODE_IRQ|I_BIT|F_BIT // IRQ Mode
	mov   sp, r0
	sub   r0, r0, #IRQ_STACK_SIZE
	msr   CPSR_c, #MODE_SVC|I_BIT|F_BIT // Supervisor Mode
	mov   sp, r0
	sub   r0, r0, #SVC_STACK_SIZE
	msr   CPSR_c, #MODE_SYS|I_BIT|F_BIT // System Mode
	mov   sp, r0

//kopiowanie zainicjalizowanego data flash -> ram
	ldr   r1, =_etext                // Poczatek danych (wartosc ROM)
	ldr   r2, =_data                 // Poczatek danych (RAM)
	ldr   r3, =_edata                // Koniec danych (RAM)
1:	cmp   r2, r3                     // Jak rozne to znaczy ze sa dane
	ldrlo r0, [r1],#4                // kopiowanie
	strlo r0, [r2],#4
	blo   1b           

// Wyczysc bss
	mov   r0, #0                     
	ldr   r1, =_bss_start           	// Poczatek .bss
	ldr   r2, =_bss_end           	// Koniec .bss
2:	cmp   r1, r2                     // Jak rozne to czysc
	strlo r0, [r1],#4                
	blo   2b                        
	
// Wywolanie main
	mov   r0, #0                     // bez argumentu
	mov   r1, r0
	mov   r2, r0
	mov   fp, r0                     // null frame pointer
	ldr   lr, =main
	bx    lr                       // skocz to main()

_loop:
	b	_loop
	