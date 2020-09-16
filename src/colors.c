#include "colors.h"

#include "screen.h"

#include <hardware/custom.h>


extern struct Custom* custom;

UWORD ColorsFadeStep(UWORD color, UWORD step);
/*--------------------------------------------------------------------------*/

void ColorsSetAllToBlack(void)
{
	ULONG i = 32;
	UWORD* col = custom->color;

	do
	{
		*col++ = 0x0000;

	} while (--i, i > 0);
}

/*--------------------------------------------------------------------------*/

void ColorsSetPalette(const UWORD* palette, ULONG size)
{
	ULONG i = size;
	UWORD* col = custom->color;

	do
	{
		*col++ = *palette++;

	} while (--i, i > 0);
}

/*--------------------------------------------------------------------------*/

void ColorsFadeIn(ULONG palette, UWORD size)
{
	ULONG i = 0;

	while (i < 17)
	{
		UWORD k = size;
		const UWORD* plt = (const UWORD*)palette;
		UWORD* col = custom->color;
		ScreenWaitForVerticallBlank();

		do
		{
			*col++ = ColorsFadeStep(*plt++, i);

		} while (--k, k > 0);

		++i;
	}
}

/*--------------------------------------------------------------------------*/

void ColorsFadeOut(ULONG palette, UWORD size)
{
	ULONG i = 16;

	while (i > 0)
	{
		ULONG k = size;
		const UWORD* plt = (const UWORD*)palette;
		UWORD* col = custom->color;
		ScreenWaitForVerticallBlank();
		do
		{
			*col++ = ColorsFadeStep(*plt++, i);

		} while (--k, k > 0);

		--i;
	}
}

/*--------------------------------------------------------------------------*/

UWORD ColorsFadeStep(UWORD color, UWORD step)
{
	UWORD result = ((color & 0x000f) * step) >> 4;
	result |= ((((color >> 4) & 0x000f) * step) >> 4) << 4;
	result |= ((((color >> 8) & 0x000f) * step) >> 4) << 8;

	return result;
}

/*--------------------------------------------------------------------------*/
