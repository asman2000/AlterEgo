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

void ScreenClear();
void ScreenOff(void);
void ScreenOn(void);
void ScreenStart(void);
void ScreenSetUp(void);

void ScreenWaitForVerticallBlank(void);

ScreenInfo* ScreenGet(void);

void ScreenBlackColors(void);
void ScreenSetPalette(const UWORD* palette, ULONG size);
void ScreenFadeIn(const UWORD* palette, UWORD size);
void ScreenFadeOut(const UWORD* palette, UWORD size);


/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_SCREEN_H */
