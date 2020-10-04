#include "welldone.h"

#include "assets.h"
#include "input.h"
#include "music.h"
#include "screen.h"
#include "smallfont.h"
#include "sprite.h"
#include "title.h"

#include <hardware/custom.h>

extern struct Custom* custom;

/*--------------------------------------------------------------------------*/

void WellDoneLoop(void)
{
	ScreenWaitForVerticallBlank();
	SpritesOff();

	custom->color[1] = 0x555;
	custom->color[2] = 0x888;
	custom->color[3] = 0xaaa;

	MusicStart();

	while (TRUE)
	{
		ScreenWaitForVerticallBlank();

		if (TRUE == InputMouseLeftButton())
		{
			mem->mainState.exitToOs = TRUE;
			break;
		}

		if (TRUE == InputJoystickRedButton())
		{
			InputJoystickReleaseRedButton();
			mem->mainState.run = Title;
			break;
		}
	}

	ScreenOff();
	SpritesOn();

	MusicStop();
}

/*--------------------------------------------------------------------------*/

void Welldone(void)
{
	AssetsWellDone();
	ScreenClear();
	SmallFontDrawString(0, "WELL DONE",  9);

	ScreenOn();

	mem->mainState.run = WellDoneLoop;
}

/*--------------------------------------------------------------------------*/
