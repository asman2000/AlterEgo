#include "screen.h"

//#include "colors.h"
//#include "copper.h"
//#include "memory.h"
//#include "sprite.h"

//#include "sizes.h"

#include <hardware/custom.h>
#include <hardware/dmabits.h>



extern struct Custom* custom;


// /*--------------------------------------------------------------------------*/

// void ScreenInit(void)
// {
// 	screen.address = MemoryChipGet(SCREEN_SIZE);
// 	ScreenClear();
// 	ScreenStart();
// }

// /*--------------------------------------------------------------------------*/

// void ScreenCopyInformation(ScreenInfo* scr)
// {
// 	scr->address = screen.address;
// 	scr->bpl = screen.bpl;
// 	scr->brow = screen.brow;
// 	scr->height = screen.height;
// }

// /*--------------------------------------------------------------------------*/

void ScreenClear(ScreenDetails* screen)
{
	ULONG* scr = (ULONG*)screen->address;
	ULONG i = (screen->height * screen->bpl * screen->brow) / 4;

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

// void ScreenStart()
// {
// 	CopperInit();
// 	SpriteInit();
// 	CopperSetScreen(&screen);
// 	CopperSetFalseSprites(SpriteGetFalse());

// 	ColorsSetAllToBlack();
// 	ScreenSetUp();

// 	ScreenWaitForVerticallBlank();
// 	CopperStart();

// 	custom->dmacon = DMAF_SETCLR|DMAF_MASTER|DMAF_RASTER|DMAF_COPPER|DMAF_SPRITE;
// }

/*--------------------------------------------------------------------------*/

void ScreenWaitForVerticallBlank(void)
{
	volatile ULONG* vposr = (ULONG*)0xdff004;

	do { ; } while(303<<8 != (*vposr & 0x1ff00));
	do { ; } while(303<<8 == (*vposr & 0x1ff00));
}

/*--------------------------------------------------------------------------*/

void ScreenSetUp(ScreenDetails* screen)
{
	//TODO add AGA check
	custom->fmode = 0;
	custom->bplcon3 = 0x0c00;

	custom->diwstrt = 0x2c81;
	custom->diwstop = 0x2cc1;
	custom->ddfstrt = 0x0038;
	custom->ddfstop = 0x00d0;

	custom->bplcon0 = screen->bpl * 0x1000 + 0x200;
	custom->bplcon1 = 0;
	custom->bplcon2 = 0x24;
	
	const UWORD modulo = (screen->bpl - 1) * screen->brow;
	custom->bpl1mod = modulo;
	custom->bpl2mod = modulo;
}

/*--------------------------------------------------------------------------*/
