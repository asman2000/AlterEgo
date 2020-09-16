#ifndef ALTEREGO_COLORS_H
#define ALTEREGO_COLORS_H

#include "types.h"

/*--------------------------------------------------------------------------*/

void ColorsSetAllToBlack(void);
void ColorsSetPalette(const UWORD* palette, ULONG size);

void ColorsFadeIn(const UWORD* palette, UWORD size);
void ColorsFadeOut(const UWORD* palette, UWORD size);

/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_COLORS_H */
