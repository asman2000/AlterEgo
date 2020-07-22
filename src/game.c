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

void GameNextLevel(struct State* gameState);
static void GameLoop(struct State* gameState);
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

UBYTE worldColors[] = 
{ 
	ASSET_WORLD0_COLORS,
	ASSET_WORLD1_COLORS,
	ASSET_WORLD2_COLORS,
	ASSET_WORLD3_COLORS,
	ASSET_WORLD4_COLORS,
};

UBYTE worldLevels[] =
{
	ASSET_WORLD0_0,
	ASSET_WORLD0_1,
	ASSET_WORLD0_2,
	ASSET_WORLD0_3,
	ASSET_WORLD0_4,

	ASSET_WORLD1_0,
	ASSET_WORLD1_1,
	ASSET_WORLD1_2,
	ASSET_WORLD1_3,
	ASSET_WORLD1_4,

	ASSET_WORLD2_0,
	ASSET_WORLD2_1,
	ASSET_WORLD2_2,
	ASSET_WORLD2_3,
	ASSET_WORLD2_4,

	ASSET_WORLD3_0,
	ASSET_WORLD3_1,
	ASSET_WORLD3_2,
	ASSET_WORLD3_3,
	ASSET_WORLD3_4,

	ASSET_WORLD4_0,
	ASSET_WORLD4_1,
	ASSET_WORLD4_2,
	ASSET_WORLD4_3,
	ASSET_WORLD4_4,
};

static void GameLoop(struct State* gameState)
{

	//AssetsGet((ULONG)palette, ASSET_WORLD0_COLORS);
	AssetsGet((ULONG)palette, worldColors[worldNumber]);
	UBYTE number = levelNumber + worldNumber * 5;
	AssetsGet((ULONG)level, worldLevels[number]);

	MapDraw(level->gfxMap);

	ScreenOn();
	ScreenFadeIn(palette, 32);

	//game logic
	while (TRUE)
	{
		ScreenWaitForVerticallBlank();

		SpriteDrawHero(0, 0);

		if (InputMouseLeftButton())
		{
			gameState->exitToOs = TRUE;
			break;
		}

		if (InputJoystickRedButton())
		{
			gameState->run = GameNextLevel;
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
		levelNumber = 0;
		worldNumber++;

		if (WORLD_MAX_NUMBER == worldNumber)
		{
			//TODO implement GameOutro
			//gameState->run = GameOutro;
		}
	}
}

/*--------------------------------------------------------------------------*/
