#include "copper.h"


#include <hardware/custom.h>
#include <hardware/dmabits.h>

extern struct Custom* custom;

/*--------------------------------------------------------------------------*/

void CopperStart(ULONG copperAddress)
{
	custom->cop1lc = copperAddress;
	custom->copjmp1 = 1;
	custom->dmacon = DMAF_SETCLR|DMAF_MASTER|DMAF_COPPER;
}

/*--------------------------------------------------------------------------*/

void CopperUpdateAddress(ULONG copperAddress, ULONG address)
{
	UWORD* copper = (UWORD*)copperAddress;

	*copper = (address >> 16);
	copper += 2;
	*copper = address & 0xffff;
}

/*--------------------------------------------------------------------------*/
