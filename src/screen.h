#ifndef ALTEREGO_SCREEN_H
#define ALTEREGO_SCREEN_H

/*--------------------------------------------------------------------------*/

#include "types.h"


void ScreenSetUp(ScreenDetails* screen);

void ScreenInit(void);

void ScreenClear(ScreenDetails* screen);
void ScreenOff(void);
void ScreenOn(void);
// void ScreenStart(void);


void ScreenWaitForVerticallBlank(void);

/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_SCREEN_H */
