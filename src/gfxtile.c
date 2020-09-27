#include "gfxtile.h"

/*--------------------------------------------------------------------------*/

void GfxTileDrawOne(ULONG scrOffset, UBYTE tileNumber, const MemoryDetails* m)
{
	UBYTE* scr = (UBYTE*)(m->screen.address + scrOffset);
	UBYTE* tiles = (UBYTE*)m->game.tiles + tileNumber * 32;

	ULONG i = 8;

	do
	{
		*scr = *tiles++;
		scr += m->screen.brow;

		*scr = *tiles++;
		scr += m->screen.brow;

		*scr = *tiles++;
		scr += m->screen.brow;

		*scr = *tiles++;
		scr += m->screen.brow;
	} while (--i, 0 != i);
}

/*--------------------------------------------------------------------------*/
