#include "lpc21xx.h"


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
