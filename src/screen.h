#ifndef ALTEREGO_SCREEN_H
#define ALTEREGO_SCREEN_H

/*--------------------------------------------------------------------------*/

#include "types.h"

typedef struct
{
	UWORD bpl;
	UWORD brow;
	UWORD height;
	ULONG address;

} ScreenInfo;

void ScreenInit(void);

void ScreenClear(ScreenInfo* screen);
void ScreenWaitForFrame(void);
void ScreenOff(void);
void ScreenOn(void);
void ScreenStart(void);

void ScreenWaitForVerticallBlank(void);


void ScreenBlackColors(void);
void ScreenSetPalette(const UWORD* palette, ULONG size);
void ScreenFadeIn(const UWORD* palette, UWORD size);
void ScreenFadeOut(const UWORD* palette, UWORD size);


/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_SCREEN_H */
