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

	} while (--i, 0 != i);
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

	} while (amount--, amount > 0);
}

/*--------------------------------------------------------------------------*/

void CopperUpdateSprite(ULONG sprite, int n)
{
	UWORD* cp = (UWORD*)copper + 19;
	cp += n * 4;

	*cp = (sprite >> 16);
	cp += 2;
	*cp = sprite & 0xffff;
}

/*--------------------------------------------------------------------------*/
