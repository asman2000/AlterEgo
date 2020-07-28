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

void MapInit(void);
void MapProcess(UWORD levelNumber);
void MapDraw(UBYTE* map);

/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_MAP_H */
