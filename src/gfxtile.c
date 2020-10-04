#include "gfxtile.h"

/*--------------------------------------------------------------------------*/

void GfxTileDrawOne(ULONG scrOffset, UBYTE tileNumber)
{
	UBYTE* scr = (UBYTE*)(mem->screenAddress + scrOffset);
	UBYTE* tiles = (UBYTE*)mem->gameTiles + tileNumber * 32;

	ULONG i = 8;

	do
	{
		*scr = *tiles++;
		scr += mem->screenBrow;

		*scr = *tiles++;
		scr += mem->screenBrow;

		*scr = *tiles++;
		scr += mem->screenBrow;

		*scr = *tiles++;
		scr += mem->screenBrow;

	} while (--i, 0 != i);
}

/*--------------------------------------------------------------------------*/
