#ifndef ALTEREGO_SMALLFONTS_H
#define ALTEREGO_SMALLFONTS_H

#include "types.h"

/*--------------------------------------------------------------------------*/

void SmallFontInit(void);

void SmallFontDrawString(ULONG screenOffset, const char* str, UBYTE amount);

void SmallFontDrawDigit(ULONG screenOffset, const char digit);


/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_SMALLFONTS_H */
