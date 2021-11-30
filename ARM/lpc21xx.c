#include "lpc21xx.h"


#define PLOCK_bit		(1<<10)
#define PLLCFG_M(M)		((M-1)&(0x1F))
#define PLL_MAGIC1		0xAA
#define PLL_MAGIC2		0x55
#define PLLE_bit		(1<<0)	//enable
#define PLLC_bit		(1<<1)	//connect

#define MAM_DISABLE_bm		0x00
#define MAM_PART_ENABLE_bm	0x01
#define MAM_ENABLE_bm		0x02
#define MAM_TIMING_bm(cyc)	(cyc&0x07)


_weak _interrupt(UNDEF) void Int_UndefinedInstruction(void)
{
	while(1)
	{
	}
}

_weak _interrupt(SWI) void Int_SoftwareInterrupt(void)
{
	while(1)
	{
	}
}

_weak _interrupt(ABORT) void Int_ProgramAbort(void)
{
	while(1)
	{
	}
}

_weak _interrupt(ABORT) void Int_DataAbort(void)
{
	while(1)
	{
	}
}

_weak _interrupt(FIQ) void Int_FIQ(void)
{
	while(1)
	{
	}
}

void InitPLL(unsigned char ucMultiplier, unsigned char ucDividerMask)
{
	PLLCFG = (PLLCFG_M(ucMultiplier) | ucDividerMask);	          
    PLLFEED = PLL_MAGIC1;					//magic pozwala na zapisanie rejestrow pll
    PLLFEED = PLL_MAGIC2;
	
    PLLCON = PLLE_bit;                		//wlacz pll
    PLLFEED = PLL_MAGIC1;
    PLLFEED = PLL_MAGIC2;
	
    while(!(PLLSTAT & PLOCK_bit)){}			//czekaj na lock
	
    PLLCON = (PLLE_bit | PLLC_bit);			//zamien zegar na pll
    PLLFEED = PLL_MAGIC1;
    PLLFEED = PLL_MAGIC2;
}

void InitMAM(unsigned char ucPrefetchCycles)
{
	MAMCR = MAM_ENABLE_bm;						//wlacz prefetch
    MAMTIM = MAM_TIMING_bm(ucPrefetchCycles);	//ustawia ilosc cycli fetchu
}
