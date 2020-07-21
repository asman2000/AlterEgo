#include "smallfont.h"

#include "assets.h"
#include "memory.h"
#include "screen.h"
#include "sizes.h"


static ULONG fontsData;
static ScreenInfo screen;

static void SmallFontDrawOne(UBYTE* screen, UBYTE fnt);

/*--------------------------------------------------------------------------*/

void SmallFontInit(void)
{
	fontsData = MemoryAnyGet(FONTS8_SIZE);
	AssetsGet(fontsData, ASSET_FONTS8);

	ScreenCopyInformation(&screen);
}

/*--------------------------------------------------------------------------*/

void SmallFontDrawString(ULONG screenOffset, const char* str, UBYTE amount)
{
	UBYTE* scr = (UBYTE*)(screen.address + screenOffset);

	do
	{
		UBYTE fnt = *str++;

		if (fnt == ' ')
		{
			fnt = 0;
		}
		else if (fnt >= '0' && fnt <= ';')
		{
			fnt = fnt - '0' + 28 + 1;
		}
		else
		{
			fnt = fnt - 'A' + 1;
		}

		SmallFontDrawOne(scr++, fnt);

	} while (--amount, 0 != amount);
}

/*--------------------------------------------------------------------------*/

static void SmallFontDrawOne(UBYTE* scr, UBYTE fntNumber)
{
	ULONG i = 8;
	UBYTE* fonts = (UBYTE*)fontsData;
	fonts += fntNumber * 16;

	do
	{
		*scr = *fonts++;
		scr += screen.brow;
		*scr = *fonts++;
		scr += screen.brow * 3;

		
	} while (--i, 0 != i);
}

/*--------------------------------------------------------------------------*/
