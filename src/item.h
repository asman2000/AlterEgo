#ifndef ALTEREGO_ITEM_H
#define ALTEREGO_ITEM_H

#include "types.h"

/*--------------------------------------------------------------------------*/

void ItemInit(void);
void ItemAdd(ULONG scrOffset, UBYTE tileNumber);
void ItemAnimate(void);
void ItemDraw(const MemoryDetails* m);
void ItemTake(UWORD x, UWORD y, const MemoryDetails* m);

/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_ITEM_H */
