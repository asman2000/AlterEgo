#include "smallfont.h"

#include "assets.h"
#include "screen.h"



static void SmallFontDrawOne(UBYTE* scr, UBYTE fntNumber);

/*--------------------------------------------------------------------------*/

void SmallFontDrawString(ULONG screenOffset, const char* str, UBYTE amount)
{
	UBYTE* scr = (UBYTE*)(mem->screenAddress + screenOffset);

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
	UBYTE* fonts = (UBYTE*)mem->smallFont;
	fonts += fntNumber * 16;

	do
	{
		*scr = *fonts++;
		scr += mem->screenBrow;
		*scr = *fonts++;
		scr += mem->screenBrow * 3;
		
	} while (--i, 0 != i);
}

/*--------------------------------------------------------------------------*/

void SmallFontDrawDigit(ULONG screenOffset, const char digit)
{
	UBYTE font = digit - '0' + 28 + 1;
	UBYTE* scr = (UBYTE*)(mem->screenAddress + screenOffset);

	SmallFontDrawOne(scr, font);
}

/*--------------------------------------------------------------------------*/
