#include "map.h"

#include "assets.h"
#include "enemy.h"
#include "gfxtile.h"
#include "hero.h"
#include "item.h"

#define MAP_WIDTH (40)
#define MAP_HEIGHT (32)


UWORD mapItemsToCollect;


/*--------------------------------------------------------------------------*/

UWORD MapProcess(UWORD levelNumber)
{
	Lvl* level = (Lvl*)mem->gameLevel;

	AssetsMap(levelNumber);

	mapItemsToCollect = 0;
	EnemyInitCnt();
	ItemInit();
	HeroInit();
	HeroSetSwaps(level->swaps);
	HeroSetSyncType(level->syncType);

	UBYTE* map = level->colMap;

	const ULONG yOffset = 8 * mem->screenBpl * mem->screenBrow;

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
				EnemyAdd(x * 8, y * 8, tile);
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

	return mapItemsToCollect;
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

	Lvl* level = (Lvl*)mem->gameLevel;

	return level->colMap[(posY * 40) + posX];
}

/*--------------------------------------------------------------------------*/

void MapClearTile(UWORD x, UWORD y)
{
	UWORD posX = x >> 3;
	UWORD posY = y >> 3;

	Lvl* level = (Lvl*)mem->gameLevel;

	level->colMap[(posY * 40) + posX] = TILE_EMPTY;
}

/*--------------------------------------------------------------------------*/
