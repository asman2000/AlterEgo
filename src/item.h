#ifndef ALTEREGO_ITEM_H
#define ALTEREGO_ITEM_H

#include "types.h"

/*--------------------------------------------------------------------------*/

void ItemInit(void);
void ItemAdd(ULONG scrOffset, UBYTE tileNumber);
void ItemAnimate(void);
void ItemDraw(void);
void ItemTake(UWORD x, UWORD y);

/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_ITEM_H */
