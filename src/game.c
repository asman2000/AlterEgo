#include "game.h"

#include "assets.h"
#include "gfxtile.h"
#include "input.h"
#include "map.h"
#include "memory.h"
#include "screen.h"
#include "sizes.h"
#include "smallfont.h"
#include "sprite.h"


static UBYTE worldNumber;
static UBYTE levelNumber;

static ScreenInfo screen;


#define LEVEL_MAX_NUMBER 5
#define WORLD_MAX_NUMBER 5

static ULONG mapsData;
static UWORD* palette;

static Lvl* level;

/*--------------------------------------------------------------------------*/

void GameInit(void)
{
	worldNumber = 0;
	levelNumber = 0;


	MemoryAnyReset();

	palette = (UWORD *)MemoryAnyGet(PALETTE_SIZE);

	GfxTileInit();

	level = (Lvl*)MemoryAnyGet(LEVEL_SIZE);

	ScreenOff();
	ScreenClear();
	ScreenBlackColors();
}

/*--------------------------------------------------------------------------*/

static void GameLoop(struct State* gameState)
{
	AssetsGet((ULONG)palette, ASSET_WORLD0_COLORS);
	AssetsGet((ULONG)level, ASSET_WORLD0_0);

	MapDraw(level->gfxMap);

	ScreenOn();
	ScreenFadeIn(palette, 32);

	//game logic
	while (TRUE)
	{
		ScreenWaitForVerticallBlank();

		SpriteDrawHero(100, 100);

		if (InputMouseLeftButton())
		{
			gameState->exitToOs = TRUE;
			break;
		}
	}

	ScreenFadeOut(palette, 32);
}

/*--------------------------------------------------------------------------*/

void Game(struct State* gameState)
{
	GameInit();
	GameLoop(gameState);
}

/*--------------------------------------------------------------------------*/

void GameFailed(struct State* gameState)
{
	//TODO add gameover
	//gameState->run = GameOver;
}

/*--------------------------------------------------------------------------*/

void GameLevelFail(struct State* gameState)
{
	//TODO
	//player loose life and restart level

	gameState->run = GameLoop;
}

/*--------------------------------------------------------------------------*/

void GameNextLevel(struct State* gameState)
{
	gameState->run = GameLoop;

	levelNumber++;

	if (LEVEL_MAX_NUMBER == levelNumber)
	{
		worldNumber++;

		if (WORLD_MAX_NUMBER == worldNumber)
		{
			//TODO implement GameOutro
			//gameState->run = GameOutro;
		}
	}
}

/*--------------------------------------------------------------------------*/
