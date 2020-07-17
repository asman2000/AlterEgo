#include "screen.h"

#include "copper.h"
#include "memory.h"
#include "sprite.h"

#include <hardware/custom.h>
#include <hardware/dmabits.h>

#define SCREEN_SIZE (40960)

extern struct Custom* custom;

static ScreenInfo screen =
{
	4,40,256,0
};


UWORD ScreenFadeColor(UWORD color, UWORD step);

/*--------------------------------------------------------------------------*/

void ScreenInit(void)
{
	screen.address = MemoryChipGet(SCREEN_SIZE);
	ScreenClear(&screen);
}


/*--------------------------------------------------------------------------*/

void ScreenClear(ScreenInfo* screen)
{
	ULONG* scr = (ULONG*)screen->address;
	ULONG i = (screen->height * screen->bpl * screen->brow) / 4;

	do
	{
		*scr++ = 0xffffffff;
		--i;
	} while (i > 0);
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

void ScreenStart()
{
	CopperInit();
	SpriteInit();
	CopperSetScreen(&screen);
	CopperSetFalseSprites(SpriteGetFalse());

	ScreenBlackColors();

	ScreenWaitForVerticallBlank();
	CopperStart();

	custom->dmacon = DMAF_SETCLR|DMAF_MASTER|DMAF_RASTER|DMAF_COPPER|DMAF_SPRITE;
}

/*--------------------------------------------------------------------------*/

void ScreenBlackColors(void)
{
	ULONG i = 32;
	UWORD* col = custom->color;

	do
	{
		*col++ = 0x0000;
		--i;
	} while (i > 0);
}

/*--------------------------------------------------------------------------*/

void ScreenSetPalette(const UWORD* palette, ULONG size)
{
	ULONG i = size;
	UWORD* col = custom->color;

	do
	{
		*col++ = *palette++;
		--i;
	} while (i > 0);
}

/*--------------------------------------------------------------------------*/

void ScreenFadeIn(const UWORD* palette, UWORD size)
{
	ULONG i = 0;

	while (i < 17)
	{
		UWORD k = size;
		const UWORD* plt = palette;
		UWORD* col = custom->color;
		ScreenWaitForVerticallBlank();

		do
		{
			*col++ = ScreenFadeColor(*plt++, i);
			--k;
		} while (k > 0);

		++i;
	}

}

/*--------------------------------------------------------------------------*/

void ScreenFadeOut(const UWORD* palette, UWORD size)
{
	ULONG i = 16;

	while (i > 0)
	{
		ULONG k = size;
		const UWORD* plt = palette;
		UWORD* col = custom->color;
		ScreenWaitForVerticallBlank();
		do
		{
			*col++ = ScreenFadeColor(*plt++, i);
			--k;
		} while (k > 0);
		--i;
	}
}

/*--------------------------------------------------------------------------*/

UWORD ScreenFadeColor(UWORD color, UWORD step)
{
	UWORD result = ((color & 0x000f) * step) >> 4;
	result |= ((((color >> 4) & 0x000f) * step) >> 4) << 4;
	result |= ((((color >> 8) & 0x000f) * step) >> 4) << 8;
 
	return result;
}

/*--------------------------------------------------------------------------*/

void ScreenWaitForVerticallBlank(void)
{
	volatile ULONG* vposr = (ULONG*)0xdff004;

	do { ; } while(303<<8 != (*vposr & 0x1ff00));
	do { ; } while(303<<8 == (*vposr & 0x1ff00));
}

/*--------------------------------------------------------------------------*/
