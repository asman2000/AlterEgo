#include "gameover.h"

#include "game.h"
#include "input.h"
#include "screen.h"
#include "smallfont.h"

#include <hardware/custom.h>


extern struct Custom* custom;

/*--------------------------------------------------------------------------*/

static void GameOverInit(void)
{
	SmallFontInit();
}

/*--------------------------------------------------------------------------*/

static void GameOverLoop(struct State* gameState)
{
	custom->color[1] = 0x555;
	custom->color[2] = 0x888;
	custom->color[3] = 0xaaa;

	SmallFontDrawString(0, "GAME OVER", 9);

	while (TRUE)
	{
		if (TRUE == InputJoystickRedButton())
		{
			gameState->run = Game;
			break;
		}
	}

}

/*--------------------------------------------------------------------------*/
void GameOver(struct State* gameState)
{
	GameOverInit();

	ScreenOn();

	GameOverLoop(gameState);
}

/*--------------------------------------------------------------------------*/
