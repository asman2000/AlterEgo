#include "map.h"

#include "gfxtile.h"

#define MAP_WIDTH (40)
#define MAP_HEIGHT (32)

/*--------------------------------------------------------------------------*/

void MapDraw(UBYTE* map)
{
	ULONG scrOffset = 0;

	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			GfxTileDrawOne(scrOffset, *map++);
			scrOffset += 1;
		}

		//TODO change it
		scrOffset += 40*4*8-40;
	}
}

/*--------------------------------------------------------------------------*/
