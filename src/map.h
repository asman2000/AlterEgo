#ifndef ALTEREGO_MAP_H
#define ALTEREGO_MAP_H
/*--------------------------------------------------------------------------*/

#include "types.h"

typedef struct
{
	UBYTE swaps;
	UBYTE syncType;
	UBYTE gfxMap[40*32];
	UBYTE colMap[40*32];
} Lvl;

#define TILE_EMPTY			0x00
#define TILE_WALL			0x01
#define TILE_LADDER			0x02
#define TILE_ITEM1			0x04
#define TILE_ITEM2			0x08
#define TILE_BRIDGE			0x10
#define TILE_WATER			0x40

#define TILE_FLOOR			(TILE_WALL|TILE_LADDER|TILE_BRIDGE)


void MapInit(void);
void MapProcess(UWORD levelNumber);
void MapDraw(UBYTE* map);
UBYTE MapCheck(UWORD x, UWORD y);
/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_MAP_H */
