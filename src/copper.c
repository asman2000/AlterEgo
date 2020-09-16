#include "copper.h"


#include <hardware/custom.h>
#include <hardware/dmabits.h>

extern struct Custom* custom;

/*--------------------------------------------------------------------------*/

void CopperStart(ULONG copperAddress)
{
	custom->cop1lc = copperAddress;
	custom->copjmp1 = 1;
}

/*--------------------------------------------------------------------------*/

// void CopperUpdateScreen(ULONG copperAddress, ULONG screenAddress, UWORD bpl, UWORD brow)
// {
// 	do
// 	{
// 		CopperUpdateAddress(copperAddress, screenAddress);
// 		copperAddress += 2;
// 		screenAddress += brow;

// 	} while (--bpl, 0 != bpl);
// }

/*--------------------------------------------------------------------------*/

void CopperUpdateAddress(ULONG copperAddress, ULONG address)
{
	UWORD* copper = (UWORD*)copperAddress;

	*copper = (address >> 16);
	copper += 2;
	*copper = address & 0xffff;
}

/*--------------------------------------------------------------------------*/
