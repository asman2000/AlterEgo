#include "gameover.h"

#include "assets.h"
#include "input.h"
#include "music.h"
#include "screen.h"
#include "smallfont.h"
#include "title.h"

#include <hardware/custom.h>


extern struct Custom* custom;

/*--------------------------------------------------------------------------*/

static void GameOverLoop(struct MainState* state)
{
	custom->color[1] = 0x555;
	custom->color[2] = 0x888;
	custom->color[3] = 0xaaa;

	SmallFontDrawString(state->memory, 0, "GAME OVER", 9);
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
void GameOver(struct MainState* state)
{
	AssetsGameOver(state->memory);

	ScreenOn();

	GameOverLoop(state);
}

/*--------------------------------------------------------------------------*/
