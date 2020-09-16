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


void ScreenClear();
void ScreenOff(void);
void ScreenOn(void);
void ScreenStart(void);
void ScreenSetUp(void);

void ScreenWaitForVerticallBlank(void);

void ScreenCopyInformation(ScreenInfo* screen);

/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_SCREEN_H */
