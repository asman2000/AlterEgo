#include "gfxtile.h"

#include "assets.h"
#include "memory.h"
#include "screen.h"
#include "sizes.h"

ULONG tilesData;

static ScreenInfo screen;

/*--------------------------------------------------------------------------*/

void GfxTileInit(void)
{
	tilesData = MemoryAnyGet(TILES_SIZE);
	AssetsGet(tilesData, ASSET_TILES);

	ScreenCopyInformation(&screen);
}


/*--------------------------------------------------------------------------*/

void GfxTileDrawOne(ULONG scrOffset, UBYTE tileNumber)
{
	UBYTE* scr = (UBYTE*)(screen.address + scrOffset);
	UBYTE* tiles = (UBYTE*)tilesData + tileNumber * 32;

	ULONG i = 8;

	do
	{
		*scr = *tiles++;
		scr += screen.brow;

		*scr = *tiles++;
		scr += screen.brow;

		*scr = *tiles++;
		scr += screen.brow;

		*scr = *tiles++;
		scr += screen.brow;
	} while (--i, 0 != i);
}

/*--------------------------------------------------------------------------*/
