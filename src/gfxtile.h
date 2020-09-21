#ifndef ALTEREGO_GFXTILE_H
#define ALTEREGO_GFXTILE_H

#include "types.h"

/*--------------------------------------------------------------------------*/

void GfxTileInit(void);

void GfxTileDrawOne(ULONG scrOffset, UBYTE tileNumber, const MemoryDetails* m);

/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_GFXTILE_H */
