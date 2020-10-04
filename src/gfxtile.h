#ifndef ALTEREGO_GFXTILE_H
#define ALTEREGO_GFXTILE_H

#include "types.h"

#define TILE_NUM_PLAYER		0x20
#define TILE_NUM_ENEMY_R	0x21
#define TILE_NUM_ENEMY_L	0x22
#define TILE_NUM_ENEMY_U	0x23
#define TILE_NUM_ENEMY_D	0x24
#define TILE_NUM_ITEM_1		0x17
#define TILE_NUM_ITEM_2		0x18

/*--------------------------------------------------------------------------*/

void GfxTileDrawOne(ULONG scrOffset, UBYTE tileNumber);

/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_GFXTILE_H */
