#include "map.h"

#include "assets.h"
#include "gfxtile.h"
#include "hero.h"
#include "item.h"
#include "memory.h"
#include "screen.h"
#include "sizes.h"

#define MAP_WIDTH (40)
#define MAP_HEIGHT (32)

#define TILE_NUM_PLAYER		0x20
#define TILE_NUM_ENEMY_R	0x21
#define TILE_NUM_ENEMY_L	0x22
#define TILE_NUM_ENEMY_U	0x23
#define TILE_NUM_ENEMY_D	0x24
#define TILE_NUM_ITEM_1		0x17
#define TILE_NUM_ITEM_2		0x18

static Lvl* level;

UWORD mapItemsToCollect;

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

	mapItemsToCollect = 0;
	ItemInit();
	HeroSetSwaps(level->swaps);
	HeroSetSyncType(level->syncType);

	UBYTE* map = level->colMap;

	const ULONG yOffset = 8 * screen.bpl * screen.brow;

	for (int y = 0; y < MAP_HEIGHT; ++y)
	{
		for (int x = 0; x < MAP_WIDTH; ++x)
		{
			UBYTE tile = *map;

			switch (tile)
			{
			case TILE_NUM_PLAYER:
				HeroSetPosition(x * 8, y * 8 - 8);
				tile = 0;
				break;
			case TILE_NUM_ENEMY_R:
			case TILE_NUM_ENEMY_L:
			case TILE_NUM_ENEMY_U:
			case TILE_NUM_ENEMY_D:
				//EnemyAdd(x * 8, y * 8, tile);
				tile = 0;
				break;

			case TILE_ITEM1:
				ItemAdd(x + y * yOffset, 0xd0);
				mapItemsToCollect++;
				break;

			case TILE_ITEM2:
				ItemAdd(x + y * yOffset, 0xd8);
				mapItemsToCollect++;
				break;
			}

			*map = tile;
			map++;
		}
	}

	
	MapDraw(level->gfxMap);
	ItemDraw();
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

UBYTE MapCheck(UWORD x, UWORD y)
{
	UWORD posX = x >> 3;
	UWORD posY = y >> 3;

	return level->colMap[(posY * 40) + posX];
}

/*--------------------------------------------------------------------------*/
