#include "smallfont.h"

#include "assets.h"
#include "screen.h"



static void SmallFontDrawOne(const MemoryDetails* m, UBYTE* scr, UBYTE fntNumber);

/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/

void SmallFontDrawString(const MemoryDetails* m, ULONG screenOffset, const char* str, UBYTE amount)
{
	UBYTE* scr = (UBYTE*)(m->screen.address + screenOffset);

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

		SmallFontDrawOne(m, scr++, fnt);

	} while (--amount, 0 != amount);
}

/*--------------------------------------------------------------------------*/

static void SmallFontDrawOne(const MemoryDetails* m, UBYTE* scr, UBYTE fntNumber)
{
	ULONG i = 8;
	UBYTE* fonts = (UBYTE*)m->smallFont;
	fonts += fntNumber * 16;

	do
	{
		*scr = *fonts++;
		scr += m->screen.brow;
		*scr = *fonts++;
		scr += m->screen.brow * 3;
		
	} while (--i, 0 != i);
}

/*--------------------------------------------------------------------------*/

void SmallFontDrawDigit(const MemoryDetails* m, ULONG screenOffset, const char digit)
{
	UBYTE font = digit - '0' + 28 + 1;
	UBYTE* scr = (UBYTE*)(m->screen.address + screenOffset);

	SmallFontDrawOne(m, scr, font);
}

/*--------------------------------------------------------------------------*/
