#include "copper.h"

#include "assets.h"
#include "decompress.h"
#include "memory.h"
#include "screen.h"

#include "sizes.h"

#include <hardware/custom.h>
#include <hardware/dmabits.h>

extern struct Custom* custom;



ULONG copper;

/*--------------------------------------------------------------------------*/

void CopperInit(void)
{
	copper = MemoryChipGet(COPPER_SIZE);

	AssetsGet(copper, ASSET_COPPER);
}


/*--------------------------------------------------------------------------*/

void CopperStart(void)
{
	custom->cop1lc = copper;
	custom->copjmp1 = 1;
}

/*--------------------------------------------------------------------------*/

void CopperSetScreen(ScreenInfo* screen)
{
	UWORD* cp = (UWORD*)copper + 1;
	ULONG scr = screen->address;
	ULONG i = screen->bpl;

	do
	{
		*cp = scr >> 16;
		cp += 2;
		*cp = scr & 0xffff;
		cp += 2;

		scr += screen->brow;

		--i;
	} while (0 != i);
}

/*--------------------------------------------------------------------------*/

void CopperSetFalseSprites(const ULONG falseSprite)
{
	ULONG amount = 8;
	UWORD* cp = (UWORD*)copper + 19;

	do
	{
		*cp = falseSprite >> 16;
		cp += 2;
		*cp = falseSprite & 0xffff;
		cp += 2;

		amount--;

	} while (amount > 0);
}

/*--------------------------------------------------------------------------*/
