#include "welldone.h"

#include "assets.h"
#include "input.h"
#include "music.h"
#include "screen.h"
#include "smallfont.h"
#include "title.h"

#include <hardware/custom.h>

extern struct Custom* custom;

/*--------------------------------------------------------------------------*/

void WellDoneLoop(struct MainState* state)
{
	ScreenWaitForVerticallBlank();

	custom->color[1] = 0x555;
	custom->color[2] = 0x888;
	custom->color[3] = 0xaaa;

	MusicStart(state->memory);

	while (TRUE)
	{
		ScreenWaitForVerticallBlank();

		if (TRUE == InputMouseLeftButton())
		{
			state->exitToOs = TRUE;
			break;
		}

		if (TRUE == InputJoystickRedButton())
		{
			InputJoystickReleaseRedButton();
			state->run = Title;
			break;
		}
	}

	ScreenOff();

	MusicStop();

}

/*--------------------------------------------------------------------------*/

void Welldone(struct MainState* state)
{
	AssetsTitle(state->memory);
	ScreenClear(&state->memory->screen);
	SmallFontDrawString(state->memory, 0, "WELL DONE",  9);

	ScreenOn();

	state->run = WellDoneLoop;

}


/*--------------------------------------------------------------------------*/
