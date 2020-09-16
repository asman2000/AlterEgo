#include "credits.h"

#include "assets.h"
#include "colors.h"
#include "input.h"
#include "screen.h"
#include "copper.h"
#include "smallfont.h"
#include "title.h"


#include <hardware/custom.h>
#include <hardware/dmabits.h>


extern struct Custom* custom;

/*--------------------------------------------------------------------------*/

static void CreditsDrawTexts(const MemoryDetails* m)
{
	ULONG scr = 0;
	UBYTE* txt = (UBYTE*)m->creditsText;

	while (TRUE)
	{
		UBYTE size;
		UWORD offset = *((UWORD*)txt);

		if (0xffff == offset)
		{
			break;
		}

		txt +=2;
		size = *txt++;

		SmallFontDrawString(m, scr + offset, txt, size);
		txt += size;
	}
}

// /*--------------------------------------------------------------------------*/

void CreditsMain(struct MainState* state)
{


	UWORD wait = 300;

	ColorsFadeIn((const UWORD*)state->memory->palette, 16);

	do
	{
		ScreenWaitForVerticallBlank();

		if (InputJoystickRedButton())
		{
			break;
		}

		if (InputMouseLeftButton())
		{
			state->exitToOs = TRUE;
			break;
		}


	} while (--wait, 0 != wait);

	ColorsFadeOut((const UWORD*)state->memory->palette, 16);
	ScreenOff();

	state->run = Title;
}

/*--------------------------------------------------------------------------*/

void Credits(struct MainState* state)
{
	AssetsCredits(state->memory);

	//set up credits screen

	UWORD* copper = (UWORD*)state->memory->copper.address + 1;
	ULONG screen = state->memory->screen.address;
	UWORD bpl = state->memory->screen.bpl;
	UWORD brow = state->memory->screen.brow;

	do
	{
		CopperUpdateAddress((ULONG)copper, screen);
		copper += 4;
		screen += brow;

	} while (--bpl, 0 != bpl);


	ScreenSetUp(&state->memory->screen);
	ColorsSetAllToBlack();

	ScreenClear(&state->memory->screen);

	CreditsDrawTexts(state->memory);

	ScreenWaitForVerticallBlank();
	CopperStart(state->memory->copper.address);
	custom->dmacon = DMAF_SETCLR|DMAF_MASTER|DMAF_RASTER|DMAF_COPPER|DMAF_SPRITE;

	state->run = CreditsMain;
}

/*--------------------------------------------------------------------------*/
