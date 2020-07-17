#ifndef ALTEREGO_COPPER_H
#define ALTEREGO_COPPER_H

#include "types.h"

#include "screen.h"
/*--------------------------------------------------------------------------*/

void CopperInit(void);
void CopperStart();

void CopperSetScreen(ScreenInfo* screen);
void CopperSetFalseSprites(const ULONG falseSprite);

/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_COPPER_H */
