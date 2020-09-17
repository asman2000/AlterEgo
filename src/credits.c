#include "credits.h"

#include "assets.h"
#include "colors.h"
#include "input.h"
#include "screen.h"
#include "smallfont.h"
#include "title.h"


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

/*--------------------------------------------------------------------------*/

void CreditsMain(struct MainState* state)
{
	UWORD wait = 300;

	ColorsFadeIn(state->memory->palette, 16);

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

	ColorsFadeOut(state->memory->palette, 16);
	ScreenOff();

	state->run = Title;
}

/*--------------------------------------------------------------------------*/

void Credits(struct MainState* state)
{
	AssetsCredits(state->memory);

	ScreenClear(&state->memory->screen);
	CreditsDrawTexts(state->memory);

	ScreenOn();

	state->run = CreditsMain;
}

/*--------------------------------------------------------------------------*/
