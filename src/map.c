#include "map.h"

#include "assets.h"
#include "gfxtile.h"
#include "hero.h"
#include "item.h"

#define MAP_WIDTH (40)
#define MAP_HEIGHT (32)


UWORD mapItemsToCollect;


/*--------------------------------------------------------------------------*/

UWORD MapProcess(UWORD levelNumber, const MemoryDetails* m)
{
	Lvl* level = (Lvl*)m->game.level;

	AssetsMap(m, levelNumber);

	mapItemsToCollect = 0;
	ItemInit();
	HeroInit();
	HeroSetSwaps(level->swaps);
	HeroSetSyncType(level->syncType);

	UBYTE* map = level->colMap;

	const ULONG yOffset = 8 * m->screen.bpl * m->screen.brow;

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
	
	MapDraw(level->gfxMap, m);

	return mapItemsToCollect;
}

/*--------------------------------------------------------------------------*/

void MapDraw(UBYTE* map, const MemoryDetails* m)
{
	ULONG scrOffset = 0;

	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			GfxTileDrawOne(scrOffset, *map++, m);
			scrOffset += 1;
		}

		//TODO change it
		scrOffset += 40*4*8-40;
	}
}

/*--------------------------------------------------------------------------*/

UBYTE MapCheck(UWORD x, UWORD y, const MemoryDetails* m)
{
	UWORD posX = x >> 3;
	UWORD posY = y >> 3;

	Lvl* level = (Lvl*)m->game.level;

	return level->colMap[(posY * 40) + posX];
}

/*--------------------------------------------------------------------------*/

void MapClearTile(UWORD x, UWORD y, const MemoryDetails* m)
{
	UWORD posX = x >> 3;
	UWORD posY = y >> 3;

	Lvl* level = (Lvl*)m->game.level;

	level->colMap[(posY * 40) + posX] = TILE_EMPTY;
}

/*--------------------------------------------------------------------------*/
