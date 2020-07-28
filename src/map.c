#include "map.h"

#include "assets.h"
#include "gfxtile.h"
#include "memory.h"
#include "screen.h"
#include "sizes.h"

#define MAP_WIDTH (40)
#define MAP_HEIGHT (32)

static Lvl* level;

static ScreenInfo screen;

UWORD worldLevels[] =
{
	ASSET_WORLD0_0,
	ASSET_WORLD0_1,
	ASSET_WORLD0_2,
	ASSET_WORLD0_3,
	ASSET_WORLD0_4,

	ASSET_WORLD1_0,
	ASSET_WORLD1_1,
	ASSET_WORLD1_2,
	ASSET_WORLD1_3,
	ASSET_WORLD1_4,

	ASSET_WORLD2_0,
	ASSET_WORLD2_1,
	ASSET_WORLD2_2,
	ASSET_WORLD2_3,
	ASSET_WORLD2_4,

	ASSET_WORLD3_0,
	ASSET_WORLD3_1,
	ASSET_WORLD3_2,
	ASSET_WORLD3_3,
	ASSET_WORLD3_4,

	ASSET_WORLD4_0,
	ASSET_WORLD4_1,
	ASSET_WORLD4_2,
	ASSET_WORLD4_3,
	ASSET_WORLD4_4,
};

/*--------------------------------------------------------------------------*/

void MapInit(void)
{
	level = (Lvl*)MemoryAnyGet(LEVEL_SIZE);

	ScreenCopyInformation(&screen);
}

/*--------------------------------------------------------------------------*/
void MapProcess(UWORD levelNumber)
{
	AssetsGet((ULONG)level, worldLevels[levelNumber]);
	
	MapDraw(level->gfxMap);
}
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
