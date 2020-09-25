#include "title.h"

#include "assets.h"
#include "game.h"
#include "input.h"
#include "music.h"
#include "screen.h"
#include "smallfont.h"
#include "sprite.h"
#include "sfx.h"

#include <hardware/custom.h>

extern struct Custom* custom;

/*--------------------------------------------------------------------------*/

void TitleLoop(struct MainState* state)
{
	ScreenWaitForVerticallBlank();
	SpritesOff();

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
			MusicStop();
			InputJoystickReleaseRedButton();
			state->run = Game;
			break;
		}
	}

	SfxPlay(SFX_START);
	UWORD wait = 150;

	do
	{
		ScreenWaitForVerticallBlank();


	} while (--wait != 0xffff);



	ScreenOff();
	SpritesOn();

	
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
