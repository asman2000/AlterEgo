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

static void GameOverLoop(void)
{
	custom->color[1] = 0x555;
	custom->color[2] = 0x888;
	custom->color[3] = 0xaaa;

	SmallFontDrawString(0, "GAME OVER", 9);
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
	MusicStop();
}

/*--------------------------------------------------------------------------*/

void GameOver(void)
{
	AssetsGameOver();

	ScreenOn();

	mem->mainState.run = GameOverLoop;
}

/*--------------------------------------------------------------------------*/
