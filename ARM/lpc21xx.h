#ifndef LPC21XX_H
#define LPC21XX_H

//taka funkcja ma nizszy priorytet niz zwykla funkcja o tej samej nazwie
#define _weak __attribute__ ((weak))	

//ten atrybut pozwala kompilatorowi w poprawny sposob zbudowac procedure przerwania
//poprawne wartosci to: IRQ, FIQ, SWI, ABORT, UNDEF.
#define _interrupt(type) __attribute__ ((interrupt ("type")))

/* DEFINE DO FUNKCJI INICJACYJNYCH */
#define PLLCFG_P_1_bm 	0x00
#define PLLCFG_P_2_bm 	0x20
#define PLLCFG_P_4_bm 	0x40
#define PLLCFG_P_8_bm 	0x60

/* FUNKCJE STAŁE DLA ARM7TDMI-S */
_weak _interrupt(UNDEF) void Int_UndefinedInstruction(void);
_weak _interrupt(SWI) void Int_SoftwareInterrupt(void);
_weak _interrupt(ABORT) void Int_ProgramAbort(void);
_weak _interrupt(ABORT) void Int_DataAbort(void);
_weak _interrupt(FIQ) void Int_FIQ(void);

/* PROTOTYPY FUNKCJI */
void InitPLL(unsigned char ucMultiplier, unsigned char ucDividerMask);
void InitMAM(unsigned char ucPrefetchCycles);

/* WATCHDOG */
#define WATCHDOG_BASE	0xE0000000
#define WDMOD 			(*((volatile unsigned char *) 	(WATCHDOG_BASE + 0x00)))
#define WDTC			(*((volatile unsigned long *) 	(WATCHDOG_BASE + 0x04)))
#define WDFEED			(*((volatile unsigned char *) 	(WATCHDOG_BASE + 0x08)))
#define WDTV 			(*((volatile unsigned long *) 	(WATCHDOG_BASE + 0x0C)))

/* TIMER0 */
#define TIMER0_BASE		0xE0004000
#define T0IR 			(*((volatile unsigned char *) 	(TIMER0_BASE + 0x00)))
#define T0TCR 			(*((volatile unsigned char *) 	(TIMER0_BASE + 0x04)))
#define T0TC 			(*((volatile unsigned long *) 	(TIMER0_BASE + 0x08)))
#define T0PR 			(*((volatile unsigned long *) 	(TIMER0_BASE + 0x0C)))
#define T0PC 			(*((volatile unsigned long *) 	(TIMER0_BASE + 0x10)))
#define T0MCR 			(*((volatile unsigned short *) 	(TIMER0_BASE + 0x14)))
#define T0MR0 			(*((volatile unsigned long *) 	(TIMER0_BASE + 0x18)))
#define T0MR1 			(*((volatile unsigned long *) 	(TIMER0_BASE + 0x1C)))
#define T0MR2 			(*((volatile unsigned long *) 	(TIMER0_BASE + 0x20)))
#define T0MR3 			(*((volatile unsigned long *) 	(TIMER0_BASE + 0x24)))
#define T0CCR 			(*((volatile unsigned short *) 	(TIMER0_BASE + 0x28)))
#define T0CR0 			(*((volatile unsigned long *) 	(TIMER0_BASE + 0x2C)))
#define T0CR1 			(*((volatile unsigned long *) 	(TIMER0_BASE + 0x30)))
#define T0CR2 			(*((volatile unsigned long *) 	(TIMER0_BASE + 0x34)))
#define T0EMR 			(*((volatile unsigned short *) 	(TIMER0_BASE + 0x3C)))

/* TIMER1 */
#define TIMER1_BASE		0xE0008000
#define T1IR 			(*((volatile unsigned char *) 	(TIMER1_BASE + 0x00)))
#define T1TCR 			(*((volatile unsigned char *) 	(TIMER1_BASE + 0x04)))
#define T1TC 			(*((volatile unsigned long *) 	(TIMER1_BASE + 0x08)))
#define T1PR 			(*((volatile unsigned long *) 	(TIMER1_BASE + 0x0C)))
#define T1PC 			(*((volatile unsigned long *) 	(TIMER1_BASE + 0x10)))
#define T1MCR 			(*((volatile unsigned short *) 	(TIMER1_BASE + 0x14)))
#define T1MR0 			(*((volatile unsigned long *) 	(TIMER1_BASE + 0x18)))
#define T1MR1 			(*((volatile unsigned long *) 	(TIMER1_BASE + 0x1C)))
#define T1MR2 			(*((volatile unsigned long *) 	(TIMER1_BASE + 0x20)))
#define T1MR3 			(*((volatile unsigned long *) 	(TIMER1_BASE + 0x24)))
#define T1CCR 			(*((volatile unsigned short *) 	(TIMER1_BASE + 0x28)))
#define T1CR0 			(*((volatile unsigned long *) 	(TIMER1_BASE + 0x2C)))
#define T1CR1 			(*((volatile unsigned long *) 	(TIMER1_BASE + 0x30)))
#define T1CR2 			(*((volatile unsigned long *) 	(TIMER1_BASE + 0x34)))
#define T1CR3 			(*((volatile unsigned long *) 	(TIMER1_BASE + 0x38)))
#define T1EMR 			(*((volatile unsigned short *) 	(TIMER1_BASE + 0x3C)))

/* UART0 */
#define UART0_BASE		0xE000C000
#define U0RBR			(*((volatile unsigned char *) 	(UART0_BASE + 0x00)))
#define U0THR			(*((volatile unsigned char *) 	(UART0_BASE + 0x00)))
#define U0DLL			(*((volatile unsigned char *) 	(UART0_BASE + 0x00)))
#define U0IER			(*((volatile unsigned char *) 	(UART0_BASE + 0x04)))
#define U0DLM			(*((volatile unsigned char *) 	(UART0_BASE + 0x04)))
#define U0IIR			(*((volatile unsigned char *) 	(UART0_BASE + 0x08)))
#define U0FCR			(*((volatile unsigned char *) 	(UART0_BASE + 0x08)))
#define U0LCR			(*((volatile unsigned char *) 	(UART0_BASE + 0x0C)))
#define U0LSR			(*((volatile unsigned char *) 	(UART0_BASE + 0x14)))
#define U0SCR			(*((volatile unsigned char *) 	(UART0_BASE + 0x1C)))

/* UART1 */
#define UART1_BASE		0xE0010000
#define U1RBR			(*((volatile unsigned char *) 	(UART1_BASE + 0x00)))
#define U1THR			(*((volatile unsigned char *) 	(UART1_BASE + 0x00)))
#define U1DLL			(*((volatile unsigned char *) 	(UART1_BASE + 0x00)))
#define U1IER			(*((volatile unsigned char *) 	(UART1_BASE + 0x04)))
#define U1DLM			(*((volatile unsigned char *) 	(UART1_BASE + 0x04)))
#define U1IIR			(*((volatile unsigned char *) 	(UART1_BASE + 0x08)))
#define U1FCR			(*((volatile unsigned char *) 	(UART1_BASE + 0x08)))
#define U1LCR			(*((volatile unsigned char *) 	(UART1_BASE + 0x0C)))
#define U1MCR			(*((volatile unsigned char *) 	(UART1_BASE + 0x10)))
#define U1LSR			(*((volatile unsigned char *) 	(UART1_BASE + 0x14)))
#define U1SCR			(*((volatile unsigned char *) 	(UART1_BASE + 0x1C)))
#define U1MSR			(*((volatile unsigned char *) 	(UART1_BASE + 0x18)))

/* PWM */
#define PWM_BASE		0xE0014000
#define PWMIR			(*((volatile unsigned short *) 	(PWM_BASE + 0x00)))
#define PWMTCR			(*((volatile unsigned char *) 	(PWM_BASE + 0x04)))
#define PWMTC			(*((volatile unsigned long *) 	(PWM_BASE + 0x08)))
#define PWMPR			(*((volatile unsigned long *) 	(PWM_BASE + 0x0C)))
#define PWMPC			(*((volatile unsigned long *) 	(PWM_BASE + 0x10)))
#define PWMIMCR			(*((volatile unsigned long *) 	(PWM_BASE + 0x14)))
#define PWMMR0			(*((volatile unsigned long *) 	(PWM_BASE + 0x18)))
#define PWMMR1			(*((volatile unsigned long *) 	(PWM_BASE + 0x1C)))
#define PWMMR2			(*((volatile unsigned long *) 	(PWM_BASE + 0x20)))
#define PWMMR3			(*((volatile unsigned long *) 	(PWM_BASE + 0x24)))
#define PWMMR4			(*((volatile unsigned long *) 	(PWM_BASE + 0x40)))
#define PWMMR5			(*((volatile unsigned long *) 	(PWM_BASE + 0x44)))
#define PWMMR6			(*((volatile unsigned long *) 	(PWM_BASE + 0x48)))
#define PWMPCR			(*((volatile unsigned short *) 	(PWM_BASE + 0x4C)))
#define PWMLER			(*((volatile unsigned char *) 	(PWM_BASE + 0x50)))

/* I2C */
#define I2C_BASE		0xE001C000
#define I2CONSET		(*((volatile unsigned char *) 	(I2C_BASE + 0x00)))
#define I2STAT			(*((volatile unsigned char *) 	(I2C_BASE + 0x04)))
#define I2DAT			(*((volatile unsigned char *) 	(I2C_BASE + 0x08)))
#define I2ADR			(*((volatile unsigned char *) 	(I2C_BASE + 0x0C)))
#define I2SCLH			(*((volatile unsigned short *) 	(I2C_BASE + 0x10)))
#define I2SCLL			(*((volatile unsigned short *) 	(I2C_BASE + 0x14)))
#define I2CONCLR		(*((volatile unsigned char *) 	(I2C_BASE + 0x18)))

/* SPI0 */
#define SPI0_BASE		0xE0020000
#define S0SPCR			(*((volatile unsigned char *) 	(SPI0_BASE + 0x00)))
#define S0SPSR			(*((volatile unsigned char *) 	(SPI0_BASE + 0x04)))
#define S0SPDR			(*((volatile unsigned char *) 	(SPI0_BASE + 0x08)))
#define S0SPCCR			(*((volatile unsigned char *) 	(SPI0_BASE + 0x0C)))
#define S0SPINT			(*((volatile unsigned char *) 	(SPI0_BASE + 0x1C)))

/* SPI1 */
#define SPI1_BASE		0xE0030004
#define S1SPCR			(*((volatile unsigned char *) 	(SPI1_BASE + 0x00)))
#define S1SPSR			(*((volatile unsigned char *) 	(SPI1_BASE + 0x04)))
#define S1SPDR			(*((volatile unsigned char *) 	(SPI1_BASE + 0x08)))
#define S1SPCCR			(*((volatile unsigned char *) 	(SPI1_BASE + 0x0C)))
#define S1SPINT			(*((volatile unsigned char *) 	(SPI1_BASE + 0x1C)))

/* RTC */ 
#define RTC_BASE		0xE0024000
#define ILR				(*((volatile unsigned char *) 	(RTC_BASE + 0x00)))
#define CTC				(*((volatile unsigned short *) 	(RTC_BASE + 0x04)))
#define CCR				(*((volatile unsigned char *) 	(RTC_BASE + 0x08)))
#define CIIR			(*((volatile unsigned char *) 	(RTC_BASE + 0x0C)))
#define AMR				(*((volatile unsigned char *) 	(RTC_BASE + 0x10)))
#define CTIME0			(*((volatile unsigned long *) 	(RTC_BASE + 0x14)))
#define CTIME1			(*((volatile unsigned long *) 	(RTC_BASE + 0x18)))
#define CTIME2			(*((volatile unsigned long *) 	(RTC_BASE + 0x1C)))
#define SEC				(*((volatile unsigned char *) 	(RTC_BASE + 0x20)))
#define MIN				(*((volatile unsigned char *) 	(RTC_BASE + 0x24)))
#define HOUR			(*((volatile unsigned char *) 	(RTC_BASE + 0x28)))
#define DOM				(*((volatile unsigned char *) 	(RTC_BASE + 0x2C)))
#define DOW				(*((volatile unsigned char *) 	(RTC_BASE + 0x30)))
#define DOY				(*((volatile unsigned short *) 	(RTC_BASE + 0x34)))
#define MONTH			(*((volatile unsigned char *) 	(RTC_BASE + 0x38)))
#define YEAR			(*((volatile unsigned short *) 	(RTC_BASE + 0x3C)))
#define ALSEC			(*((volatile unsigned char *) 	(RTC_BASE + 0x60)))
#define ALMIN			(*((volatile unsigned char *) 	(RTC_BASE + 0x64)))
#define ALHOUR			(*((volatile unsigned char *) 	(RTC_BASE + 0x68)))
#define ALDOM			(*((volatile unsigned char *) 	(RTC_BASE + 0x6C)))
#define ALDOW			(*((volatile unsigned char *) 	(RTC_BASE + 0x70)))
#define ALDOY			(*((volatile unsigned short *) 	(RTC_BASE + 0x74)))
#define ALMON			(*((volatile unsigned char *) 	(RTC_BASE + 0x78)))
#define ALYEAR			(*((volatile unsigned short *) 	(RTC_BASE + 0x7C)))
#define PREINT			(*((volatile unsigned short *) 	(RTC_BASE + 0x80)))
#define PREFRAC			(*((volatile unsigned short *) 	(RTC_BASE + 0x84)))

/* GPIO */
#define IO_BASE			0xE0028000
#define IO0PIN			(*((volatile unsigned long *) 	(IO_BASE + 0x00)))
#define IO0SET			(*((volatile unsigned long *) 	(IO_BASE + 0x04)))
#define IO0DIR			(*((volatile unsigned long *) 	(IO_BASE + 0x08)))
#define IO0CLR			(*((volatile unsigned long *) 	(IO_BASE + 0x0C)))
#define IO1PIN			(*((volatile unsigned long *) 	(IO_BASE + 0x10)))
#define IO1SET			(*((volatile unsigned long *) 	(IO_BASE + 0x14)))
#define IO1DIR			(*((volatile unsigned long *) 	(IO_BASE + 0x18)))
#define IO1CLR			(*((volatile unsigned long *) 	(IO_BASE + 0x1C)))
#define IO2PIN			(*((volatile unsigned long *) 	(IO_BASE + 0x20)))
#define IO2SET			(*((volatile unsigned long *) 	(IO_BASE + 0x24)))
#define IO2DIR			(*((volatile unsigned long *) 	(IO_BASE + 0x28)))
#define IO2CLR			(*((volatile unsigned long *) 	(IO_BASE + 0x2C)))
#define IO3PIN			(*((volatile unsigned long *) 	(IO_BASE + 0x30)))
#define IO3SET			(*((volatile unsigned long *) 	(IO_BASE + 0x34)))
#define IO3DIR			(*((volatile unsigned long *) 	(IO_BASE + 0x38)))
#define IO3CLR			(*((volatile unsigned long *) 	(IO_BASE + 0x3C)))

/* PIN CONNECT BLOCK */
#define PCBLOCK_BASE	0xE002C000
#define PINSEL0			(*((volatile unsigned long *) 	(PCBLOCK_BASE + 0x00)))
#define PINSEL1			(*((volatile unsigned long *) 	(PCBLOCK_BASE + 0x04)))
#define PINSEL2			(*((volatile unsigned long *) 	(PCBLOCK_BASE + 0x14)))

/* ADC */
#define ADC_BASE		0xE0034000
#define ADCR			(*((volatile unsigned long *) 	(ADC_BASE + 0x00)))
#define ADDR			(*((volatile unsigned long *) 	(ADC_BASE + 0x04)))

/* CAN */
#define CAN_FILTER_BASE	0xE003C000
#define CAN_BASE		0xE0040000
#define CAN_RAM_PTR		((volatile unsigned long *)		(0xE0038000))
#define AFMR			(*((volatile unsigned char *) 	(CAN_FILTER_BASE + 0x00)))
#define SFF_sa			(*((volatile unsigned short *) 	(CAN_FILTER_BASE + 0x04)))
#define SFF_GRP_sa		(*((volatile unsigned short *) 	(CAN_FILTER_BASE + 0x08)))
#define EFF_sa			(*((volatile unsigned short *) 	(CAN_FILTER_BASE + 0x0C)))
#define EFF_GRP_sa		(*((volatile unsigned short *) 	(CAN_FILTER_BASE + 0x10)))
#define ENDofTable		(*((volatile unsigned short *) 	(CAN_FILTER_BASE + 0x14)))
#define LUTerrAd		(*((volatile unsigned short *) 	(CAN_FILTER_BASE + 0x18)))
#define LUTerr			(*((volatile unsigned char *) 	(CAN_FILTER_BASE + 0x1C)))
#define CANTxSR			(*((volatile unsigned long *) 	(CAN_BASE + 0x00)))
#define CANRxSR			(*((volatile unsigned long *) 	(CAN_BASE + 0x04)))
#define CANMSR			(*((volatile unsigned long *) 	(CAN_BASE + 0x08)))

/* CAN1 */
#define CAN1_BASE		0xE0044000
#define C1MOD			(*((volatile unsigned long *) 	(CAN1_BASE + 0x00)))
#define C1CMR			(*((volatile unsigned long *) 	(CAN1_BASE + 0x04)))
#define C1GSR			(*((volatile unsigned long *) 	(CAN1_BASE + 0x08)))
#define C1ICR			(*((volatile unsigned long *) 	(CAN1_BASE + 0x0C)))
#define C1IER			(*((volatile unsigned long *) 	(CAN1_BASE + 0x10)))
#define C1BTR			(*((volatile unsigned long *) 	(CAN1_BASE + 0x14)))
#define C1EWL			(*((volatile unsigned long *) 	(CAN1_BASE + 0x18)))
#define C1SR			(*((volatile unsigned long *) 	(CAN1_BASE + 0x1C)))
#define C1RFS			(*((volatile unsigned long *) 	(CAN1_BASE + 0x20)))
#define C1RID			(*((volatile unsigned long *) 	(CAN1_BASE + 0x24)))
#define C1RDA			(*((volatile unsigned long *) 	(CAN1_BASE + 0x28)))
#define C1RDB			(*((volatile unsigned long *) 	(CAN1_BASE + 0x2C)))
#define C1TFI1			(*((volatile unsigned long *) 	(CAN1_BASE + 0x30)))
#define C1TID1			(*((volatile unsigned long *) 	(CAN1_BASE + 0x34)))
#define C1TDA1			(*((volatile unsigned long *) 	(CAN1_BASE + 0x38)))
#define C1TDB1			(*((volatile unsigned long *) 	(CAN1_BASE + 0x3C)))
#define C1TFI2			(*((volatile unsigned long *) 	(CAN1_BASE + 0x40)))
#define C1TID2			(*((volatile unsigned long *) 	(CAN1_BASE + 0x44)))
#define C1TDA2			(*((volatile unsigned long *) 	(CAN1_BASE + 0x48)))
#define C1TDB2			(*((volatile unsigned long *) 	(CAN1_BASE + 0x4C)))
#define C1TFI3			(*((volatile unsigned long *) 	(CAN1_BASE + 0x50)))
#define C1TID3			(*((volatile unsigned long *) 	(CAN1_BASE + 0x54)))
#define C1TDA3			(*((volatile unsigned long *) 	(CAN1_BASE + 0x58)))
#define C1TDB3			(*((volatile unsigned long *) 	(CAN1_BASE + 0x5C)))

/* CAN2 */
#define CAN2_BASE		0xE0048000
#define C2MOD			(*((volatile unsigned long *) 	(CAN2_BASE + 0x00)))
#define C2CMR			(*((volatile unsigned long *) 	(CAN2_BASE + 0x04)))
#define C2GSR			(*((volatile unsigned long *) 	(CAN2_BASE + 0x08)))
#define C2ICR			(*((volatile unsigned long *) 	(CAN2_BASE + 0x0C)))
#define C2IER			(*((volatile unsigned long *) 	(CAN2_BASE + 0x10)))
#define C2BTR			(*((volatile unsigned long *) 	(CAN2_BASE + 0x14)))
#define C2EWL			(*((volatile unsigned long *) 	(CAN2_BASE + 0x18)))
#define C2SR			(*((volatile unsigned long *) 	(CAN2_BASE + 0x1C)))
#define C2RFS			(*((volatile unsigned long *) 	(CAN2_BASE + 0x20)))
#define C2RID			(*((volatile unsigned long *) 	(CAN2_BASE + 0x24)))
#define C2RDA			(*((volatile unsigned long *) 	(CAN2_BASE + 0x28)))
#define C2RDB			(*((volatile unsigned long *) 	(CAN2_BASE + 0x2C)))
#define C2TFI1			(*((volatile unsigned long *) 	(CAN2_BASE + 0x30)))
#define C2TID1			(*((volatile unsigned long *) 	(CAN2_BASE + 0x34)))
#define C2TDA1			(*((volatile unsigned long *) 	(CAN2_BASE + 0x38)))
#define C2TDB1			(*((volatile unsigned long *) 	(CAN2_BASE + 0x3C)))
#define C2TFI2			(*((volatile unsigned long *) 	(CAN2_BASE + 0x40)))
#define C2TID2			(*((volatile unsigned long *) 	(CAN2_BASE + 0x44)))
#define C2TDA2			(*((volatile unsigned long *) 	(CAN2_BASE + 0x48)))
#define C2TDB2			(*((volatile unsigned long *) 	(CAN2_BASE + 0x4C)))
#define C2TFI3			(*((volatile unsigned long *) 	(CAN2_BASE + 0x50)))
#define C2TID3			(*((volatile unsigned long *) 	(CAN2_BASE + 0x54)))
#define C2TDA3			(*((volatile unsigned long *) 	(CAN2_BASE + 0x58)))
#define C2TDB3			(*((volatile unsigned long *) 	(CAN2_BASE + 0x5C)))

/* CAN3 */
#define CAN3_BASE		0xE004C000
#define C3MOD			(*((volatile unsigned long *) 	(CAN3_BASE + 0x00)))
#define C3CMR			(*((volatile unsigned long *) 	(CAN3_BASE + 0x04)))
#define C3GSR			(*((volatile unsigned long *) 	(CAN3_BASE + 0x08)))
#define C3ICR			(*((volatile unsigned long *) 	(CAN3_BASE + 0x0C)))
#define C3IER			(*((volatile unsigned long *) 	(CAN3_BASE + 0x10)))
#define C3BTR			(*((volatile unsigned long *) 	(CAN3_BASE + 0x14)))
#define C3EWL			(*((volatile unsigned long *) 	(CAN3_BASE + 0x18)))
#define C3SR			(*((volatile unsigned long *) 	(CAN3_BASE + 0x1C)))
#define C3RFS			(*((volatile unsigned long *) 	(CAN3_BASE + 0x20)))
#define C3RID			(*((volatile unsigned long *) 	(CAN3_BASE + 0x24)))
#define C3RDA			(*((volatile unsigned long *) 	(CAN3_BASE + 0x28)))
#define C3RDB			(*((volatile unsigned long *) 	(CAN3_BASE + 0x2C)))
#define C3TFI1			(*((volatile unsigned long *) 	(CAN3_BASE + 0x30)))
#define C3TID1			(*((volatile unsigned long *) 	(CAN3_BASE + 0x34)))
#define C3TDA1			(*((volatile unsigned long *) 	(CAN3_BASE + 0x38)))
#define C3TDB1			(*((volatile unsigned long *) 	(CAN3_BASE + 0x3C)))
#define C3TFI2			(*((volatile unsigned long *) 	(CAN3_BASE + 0x40)))
#define C3TID2			(*((volatile unsigned long *) 	(CAN3_BASE + 0x44)))
#define C3TDA2			(*((volatile unsigned long *) 	(CAN3_BASE + 0x48)))
#define C3TDB2			(*((volatile unsigned long *) 	(CAN3_BASE + 0x4C)))
#define C3TFI3			(*((volatile unsigned long *) 	(CAN3_BASE + 0x50)))
#define C3TID3			(*((volatile unsigned long *) 	(CAN3_BASE + 0x54)))
#define C3TDA3			(*((volatile unsigned long *) 	(CAN3_BASE + 0x58)))
#define C3TDB3			(*((volatile unsigned long *) 	(CAN3_BASE + 0x5C)))

/* CAN4 */
#define CAN4_BASE		0xE0050000
#define C4MOD			(*((volatile unsigned long *) 	(CAN4_BASE + 0x00)))
#define C4CMR			(*((volatile unsigned long *) 	(CAN4_BASE + 0x04)))
#define C4GSR			(*((volatile unsigned long *) 	(CAN4_BASE + 0x08)))
#define C4ICR			(*((volatile unsigned long *) 	(CAN4_BASE + 0x0C)))
#define C4IER			(*((volatile unsigned long *) 	(CAN4_BASE + 0x10)))
#define C4BTR			(*((volatile unsigned long *) 	(CAN4_BASE + 0x14)))
#define C4EWL			(*((volatile unsigned long *) 	(CAN4_BASE + 0x18)))
#define C4SR			(*((volatile unsigned long *) 	(CAN4_BASE + 0x1C)))
#define C4RFS			(*((volatile unsigned long *) 	(CAN4_BASE + 0x20)))
#define C4RID			(*((volatile unsigned long *) 	(CAN4_BASE + 0x24)))
#define C4RDA			(*((volatile unsigned long *) 	(CAN4_BASE + 0x28)))
#define C4RDB			(*((volatile unsigned long *) 	(CAN4_BASE + 0x2C)))
#define C4TFI1			(*((volatile unsigned long *) 	(CAN4_BASE + 0x30)))
#define C4TID1			(*((volatile unsigned long *) 	(CAN4_BASE + 0x34)))
#define C4TDA1			(*((volatile unsigned long *) 	(CAN4_BASE + 0x38)))
#define C4TDB1			(*((volatile unsigned long *) 	(CAN4_BASE + 0x3C)))
#define C4TFI2			(*((volatile unsigned long *) 	(CAN4_BASE + 0x40)))
#define C4TID2			(*((volatile unsigned long *) 	(CAN4_BASE + 0x44)))
#define C4TDA2			(*((volatile unsigned long *) 	(CAN4_BASE + 0x48)))
#define C4TDB2			(*((volatile unsigned long *) 	(CAN4_BASE + 0x4C)))
#define C4TFI3			(*((volatile unsigned long *) 	(CAN4_BASE + 0x50)))
#define C4TID3			(*((volatile unsigned long *) 	(CAN4_BASE + 0x54)))
#define C4TDA3			(*((volatile unsigned long *) 	(CAN4_BASE + 0x58)))
#define C4TDB3			(*((volatile unsigned long *) 	(CAN4_BASE + 0x5C)))

/* SYSTEM CONTROL BLOCK */
#define SYS_CTL_BASE	0xE01FC000
#define MAMCR			(*((volatile unsigned char *) 	(SYS_CTL_BASE + 0x00)))
#define MAMTIM			(*((volatile unsigned char *) 	(SYS_CTL_BASE + 0x04)))
#define MEMMAP			(*((volatile unsigned char *) 	(SYS_CTL_BASE + 0x40)))
#define PLLCON			(*((volatile unsigned char *) 	(SYS_CTL_BASE + 0x80)))
#define PLLCFG			(*((volatile unsigned char *) 	(SYS_CTL_BASE + 0x84)))
#define PLLSTAT			(*((volatile unsigned short *) 	(SYS_CTL_BASE + 0x88)))
#define PLLFEED			(*((volatile unsigned char *) 	(SYS_CTL_BASE + 0x8C)))
#define PCON			(*((volatile unsigned char *) 	(SYS_CTL_BASE + 0xC0)))
#define PCONP			(*((volatile unsigned long *) 	(SYS_CTL_BASE + 0xC4)))
#define VPBDIV			(*((volatile unsigned char *) 	(SYS_CTL_BASE + 0x100)))
#define EXTINT			(*((volatile unsigned char *) 	(SYS_CTL_BASE + 0x140)))
#define EXTWAKE			(*((volatile unsigned char *) 	(SYS_CTL_BASE + 0x144)))
#define EXTMODE			(*((volatile unsigned char *) 	(SYS_CTL_BASE + 0x148)))
#define EXTPOLAR		(*((volatile unsigned char *) 	(SYS_CTL_BASE + 0x14C)))

/* EXTERNAL MEMORY CONTROLLER */
#define EMC_BASE		0xFFE00000
#define BCFG0			(*((volatile unsigned long *) 	(EMC_BASE + 0x00)))
#define BCFG1			(*((volatile unsigned long *) 	(EMC_BASE + 0x04)))
#define BCFG2			(*((volatile unsigned long *) 	(EMC_BASE + 0x08)))
#define BCFG3			(*((volatile unsigned long *) 	(EMC_BASE + 0x0C)))

/* VECTORED INTERRUPT CONTROLLER */
#define VIC_BASE		0xFFFFF000
#define VICIRQStatus	(*((volatile unsigned long *) 	(VIC_BASE + 0x00)))
#define VICFIQStatus	(*((volatile unsigned long *) 	(VIC_BASE + 0x04)))
#define VICRawIntr		(*((volatile unsigned long *) 	(VIC_BASE + 0x08)))
#define VICIntSelect	(*((volatile unsigned long *) 	(VIC_BASE + 0x0C)))
#define VICIntEnable	(*((volatile unsigned long *) 	(VIC_BASE + 0x10)))
#define VICIntEnClear	(*((volatile unsigned long *) 	(VIC_BASE + 0x14)))
#define VICSoftInt		(*((volatile unsigned long *) 	(VIC_BASE + 0x18)))
#define VICSoftIntClear	(*((volatile unsigned long *) 	(VIC_BASE + 0x1C)))
#define VICProtection	(*((volatile unsigned long *) 	(VIC_BASE + 0x20)))
#define VICVectAddr		(*((volatile unsigned long *) 	(VIC_BASE + 0x30)))
#define VICDefVectAddr	(*((volatile unsigned long *) 	(VIC_BASE + 0x34)))
#define VICVectAddr0	(*((volatile unsigned long *) 	(VIC_BASE + 0x100)))
#define VICVectAddr1	(*((volatile unsigned long *) 	(VIC_BASE + 0x104)))
#define VICVectAddr2	(*((volatile unsigned long *) 	(VIC_BASE + 0x108)))
#define VICVectAddr3	(*((volatile unsigned long *) 	(VIC_BASE + 0x10C)))
#define VICVectAddr4	(*((volatile unsigned long *) 	(VIC_BASE + 0x110)))
#define VICVectAddr5	(*((volatile unsigned long *) 	(VIC_BASE + 0x114)))
#define VICVectAddr6	(*((volatile unsigned long *) 	(VIC_BASE + 0x118)))
#define VICVectAddr7	(*((volatile unsigned long *) 	(VIC_BASE + 0x11C)))
#define VICVectAddr8	(*((volatile unsigned long *) 	(VIC_BASE + 0x120)))
#define VICVectAddr9	(*((volatile unsigned long *) 	(VIC_BASE + 0x124)))
#define VICVectAddr10	(*((volatile unsigned long *) 	(VIC_BASE + 0x128)))
#define VICVectAddr11	(*((volatile unsigned long *) 	(VIC_BASE + 0x12C)))
#define VICVectAddr12	(*((volatile unsigned long *) 	(VIC_BASE + 0x130)))
#define VICVectAddr13	(*((volatile unsigned long *) 	(VIC_BASE + 0x134)))
#define VICVectAddr14	(*((volatile unsigned long *) 	(VIC_BASE + 0x138)))
#define VICVectAddr15	(*((volatile unsigned long *) 	(VIC_BASE + 0x13C)))
#define VICVectCntl0	(*((volatile unsigned long *) 	(VIC_BASE + 0x200)))
#define VICVectCntl1	(*((volatile unsigned long *) 	(VIC_BASE + 0x204)))
#define VICVectCntl2	(*((volatile unsigned long *) 	(VIC_BASE + 0x208)))
#define VICVectCntl3	(*((volatile unsigned long *) 	(VIC_BASE + 0x20C)))
#define VICVectCntl4	(*((volatile unsigned long *) 	(VIC_BASE + 0x210)))
#define VICVectCntl5	(*((volatile unsigned long *) 	(VIC_BASE + 0x214)))
#define VICVectCntl6	(*((volatile unsigned long *) 	(VIC_BASE + 0x218)))
#define VICVectCntl7	(*((volatile unsigned long *) 	(VIC_BASE + 0x21C)))
#define VICVectCntl8	(*((volatile unsigned long *) 	(VIC_BASE + 0x220)))
#define VICVectCntl9	(*((volatile unsigned long *) 	(VIC_BASE + 0x224)))
#define VICVectCntl10	(*((volatile unsigned long *) 	(VIC_BASE + 0x228)))
#define VICVectCntl11	(*((volatile unsigned long *) 	(VIC_BASE + 0x22C)))
#define VICVectCntl12	(*((volatile unsigned long *) 	(VIC_BASE + 0x230)))
#define VICVectCntl13	(*((volatile unsigned long *) 	(VIC_BASE + 0x234)))
#define VICVectCntl14	(*((volatile unsigned long *) 	(VIC_BASE + 0x238)))
#define VICVectCntl15	(*((volatile unsigned long *) 	(VIC_BASE + 0x23C)))

#endif