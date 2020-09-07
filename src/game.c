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


Match currentMatch;

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
	currentMatch.levelNumber = 0;
	currentMatch.worldNumber = 0;
	currentMatch.itemsToCollect = 0;
	currentMatch.state = GAME_STATE_NOTHING;
	currentMatch.livesNumber = 1;


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
	AssetsGet((ULONG)palette, worldColors[currentMatch.worldNumber]);
	UBYTE number = currentMatch.levelNumber + currentMatch.worldNumber * 5;

	
	currentMatch.itemsToCollect = MapProcess(number);

	HeroShow();

	ScreenOn();
	ScreenFadeIn(palette, 32);

	//game logic
	while (TRUE)
	{
		ScreenWaitForVerticallBlank();

		ItemDraw();


		HeroHandleInput(&currentMatch);

		if (InputMouseLeftButton())
		{
			gameState->exitToOs = TRUE;
			break;
		}

		if (0 == currentMatch.itemsToCollect)
		{
			gameState->run = GameNextLevel;
			break;
		}

		if (GAME_STATE_FAIL == currentMatch.state)
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
	currentMatch.livesNumber--;

	if (0 == currentMatch.livesNumber)
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

	currentMatch.levelNumber++;

	if (LEVEL_MAX_NUMBER == currentMatch.levelNumber)
	{
		currentMatch.levelNumber = 0;
		currentMatch.worldNumber++;

		if (WORLD_MAX_NUMBER == currentMatch.worldNumber)
		{
			//TODO implement GameOutro
			//gameState->run = GameOutro;
		}
	}
}

/*--------------------------------------------------------------------------*/
