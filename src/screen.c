#include "screen.h"

#include "assets.h"
#include "colors.h"
#include "copper.h"

#include <hardware/custom.h>
#include <hardware/dmabits.h>

extern struct Custom* custom;

void ScreenSetUp();
/*--------------------------------------------------------------------------*/

void ScreenInit(void)
{
	AssetsScreen();

	UWORD* copper = (UWORD*)mem->copperAddress + 1;
	ULONG screen = mem->screenAddress;
	UWORD bpl = mem->screenBpl;
	UWORD brow = mem->screenBrow;

	do
	{
		CopperUpdateAddress((ULONG)copper, screen);
		copper += 4;
		screen += brow;

	} while (--bpl, 0 != bpl);


	ScreenSetUp();
	ColorsSetAllToBlack();
	ScreenWaitForVerticallBlank();
	CopperStart();
}

/*--------------------------------------------------------------------------*/

void ScreenClear(void)
{
	ULONG* scr = (ULONG*)mem->screenAddress;
	ULONG i = (mem->screenHeight * mem->screenBpl * mem->screenBrow) / 4;

	do
	{
		*scr++ = 0x0;
	} while (--i, i > 0);
}

/*--------------------------------------------------------------------------*/

void ScreenOff(void)
{
	ScreenWaitForVerticallBlank();
	custom->dmacon = DMAF_RASTER;
}

/*--------------------------------------------------------------------------*/

void ScreenOn(void)
{
	ScreenWaitForVerticallBlank();
	custom->dmacon = DMAF_SETCLR | DMAF_RASTER;
}

/*--------------------------------------------------------------------------*/

void ScreenWaitForVerticallBlank(void)
{
	volatile ULONG* vposr = (ULONG*)0xdff004;

	do { ; } while(303<<8 != (*vposr & 0x1ff00));
	do { ; } while(303<<8 == (*vposr & 0x1ff00));
}

/*--------------------------------------------------------------------------*/

void ScreenSetUp()
{
	//TODO add AGA check
	custom->fmode = 0;
	custom->bplcon3 = 0x0c00;

	custom->diwstrt = 0x2c81;
	custom->diwstop = 0x2cc1;
	custom->ddfstrt = 0x0038;
	custom->ddfstop = 0x00d0;

	custom->bplcon0 = mem->screenBpl * 0x1000 + 0x200;
	custom->bplcon1 = 0;
	custom->bplcon2 = 0x24;
	
	const UWORD modulo = (mem->screenBpl - 1) * mem->screenBrow;
	custom->bpl1mod = modulo;
	custom->bpl2mod = modulo;
}

/*--------------------------------------------------------------------------*/
