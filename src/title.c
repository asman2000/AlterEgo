#include "title.h"

#include "assets.h"
#include "input.h"
#include "game.h"
#include "screen.h"
#include "smallfont.h"

#include <hardware/custom.h>

extern struct Custom* custom;

/*--------------------------------------------------------------------------*/

void TitleLoop(struct MainState* state)
{
	ScreenWaitForVerticallBlank();

	custom->color[1] = 0x555;
	custom->color[2] = 0x888;
	custom->color[3] = 0xaaa;

	while (TRUE)
	{
		if (TRUE == InputMouseLeftButton())
		{
			state->exitToOs = TRUE;
			break;
		}

		if (TRUE == InputJoystickRedButton())
		{
			InputJoystickReleaseRedButton();
			state->run = Game;
			break;
		}
	}

	ScreenOff();
}

/*--------------------------------------------------------------------------*/

void Title(struct MainState* state)
{
	AssetsTitle(state->memory);
	ScreenClear(&state->memory->screen);
	SmallFontDrawString(state->memory, 0, "TITLE", 5);

	ScreenOn();

	state->run = TitleLoop;	
}

/*--------------------------------------------------------------------------*/
