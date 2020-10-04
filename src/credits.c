#include "credits.h"

#include "assets.h"
#include "colors.h"
#include "input.h"
#include "screen.h"
#include "smallfont.h"
#include "title.h"


/*--------------------------------------------------------------------------*/

static void CreditsDrawTexts(void)
{
	ULONG scr = 0;
	UBYTE* txt = (UBYTE*)mem->creditsText;

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

		SmallFontDrawString(scr + offset, txt, size);
		txt += size;
	}
}

/*--------------------------------------------------------------------------*/

void CreditsMain(void)
{
	UWORD wait = 300;

	ColorsFadeIn(16);

	do
	{
		ScreenWaitForVerticallBlank();

		if (InputJoystickRedButton())
		{
			InputJoystickReleaseRedButton();
			break;
		}

		if (InputMouseLeftButton())
		{
			mem->mainState.exitToOs = TRUE;
			break;
		}


	} while (--wait, 0 != wait);

	ColorsFadeOut(16);
	ScreenOff();

	mem->mainState.run = Title;
}

/*--------------------------------------------------------------------------*/

void Credits(void)
{
	AssetsCredits();

	ScreenClear();
	CreditsDrawTexts();

	ScreenOn();

	mem->mainState.run = CreditsMain;
}

/*--------------------------------------------------------------------------*/
