#include "game.h"

#include "assets.h"
#include "gameover.h"
#include "gfxtile.h"
#include "hero.h"
#include "input.h"
#include "item.h"
#include "map.h"
#include "memory.h"
#include "screen.h"
#include "sizes.h"
#include "smallfont.h"
#include "sprite.h"


GameInfo currentGame;

static ScreenInfo screen;

#define LEVEL_MAX_NUMBER 5
#define WORLD_MAX_NUMBER 5

static ULONG mapsData;
static UWORD* palette;



void GameNextLevel(struct State* gameState);
void GameLevelFail(struct State* gameState);
static void GameLoop(struct State* gameState);
/*--------------------------------------------------------------------------*/

void GameInit(void)
{
	currentGame.levelNumber = 0;
	currentGame.worldNumber = 0;
	currentGame.itemsToCollect = 0;
	currentGame.state = GAME_STATE_NOTHING;
	currentGame.livesNumber = 1;


	MemoryAnyReset();

	palette = (UWORD *)MemoryAnyGet(PALETTE_SIZE);

	GfxTileInit();

	HeroSetUp(HERO_ONE);
	MapInit();
	

	ScreenOff();
	ScreenClear();
	ScreenBlackColors();
}

/*--------------------------------------------------------------------------*/

UBYTE worldColors[] = 
{ 
	ASSET_WORLD0_COLORS,
	ASSET_WORLD1_COLORS,
	ASSET_WORLD2_COLORS,
	ASSET_WORLD3_COLORS,
	ASSET_WORLD4_COLORS,
};


static void GameLoop(struct State* gameState)
{
	AssetsGet((ULONG)palette, worldColors[currentGame.worldNumber]);
	UBYTE number = currentGame.levelNumber + currentGame.worldNumber * 5;

	
	currentGame.itemsToCollect = MapProcess(number);

	HeroShow();

	ScreenOn();
	ScreenFadeIn(palette, 32);

	//game logic
	while (TRUE)
	{
		ScreenWaitForVerticallBlank();

		ItemDraw();

		UBYTE joy = InputJoystickGetState();

		HeroHandleInput(joy, &currentGame);

		if (InputMouseLeftButton())
		{
			gameState->exitToOs = TRUE;
			break;
		}

		if (0 == currentGame.itemsToCollect)
		{
			gameState->run = GameNextLevel;
			break;
		}

		if (GAME_STATE_FAIL == currentGame.state)
		{
			gameState->run = GameLevelFail;
			break;
		}
	}

	ScreenFadeOut(palette, 32);
	ScreenOff();
	ScreenClear();
	ScreenBlackColors();

}

/*--------------------------------------------------------------------------*/

void Game(struct State* gameState)
{
	//gameState->run = GameInit;
	GameInit();
	GameLoop(gameState);
}

/*--------------------------------------------------------------------------*/

void GameFailed(struct State* gameState)
{
	gameState->run = GameOver;
}

/*--------------------------------------------------------------------------*/

void GameLevelFail(struct State* gameState)
{
	currentGame.livesNumber--;

	if (0 == currentGame.livesNumber)
	{
		gameState->run = GameFailed;
		return;
	}

	gameState->run = GameLoop;
}

/*--------------------------------------------------------------------------*/

void GameNextLevel(struct State* gameState)
{
	gameState->run = GameLoop;

	currentGame.levelNumber++;

	if (LEVEL_MAX_NUMBER == currentGame.levelNumber)
	{
		currentGame.levelNumber = 0;
		currentGame.worldNumber++;

		if (WORLD_MAX_NUMBER == currentGame.worldNumber)
		{
			//TODO implement GameOutro
			//gameState->run = GameOutro;
		}
	}
}

/*--------------------------------------------------------------------------*/
