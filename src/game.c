#include "game.h"

#include "assets.h"
#include "colors.h"
#include "enemy.h"
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

#define LEVEL_MAX_NUMBER 5
#define WORLD_MAX_NUMBER 5

static ULONG mapsData;



void GameNextLevel(struct MainState* state);
void GameLevelFail(struct MainState* state);
static void GameLoop(struct MainState* state);

/*--------------------------------------------------------------------------*/

void GameInit(const MemoryDetails* m)
{
	currentMatch.levelNumber = 0;
	currentMatch.worldNumber = 0;
	currentMatch.itemsToCollect = 0;
	currentMatch.state = GAME_STATE_NOTHING;
	currentMatch.livesNumber = 1;


	AssetsGameTiles(m);
	AssetsGameSprites(m);

	HeroSetUp(HERO_ONE);

	ScreenOff();
	ScreenClear(&m->screen);
	ColorsSetAllToBlack();
}

/*--------------------------------------------------------------------------*/

static void GameLoop(struct MainState* state)
{
	AssetsGameWorldPalette(state->memory, currentMatch.worldNumber);
	
	UBYTE number = currentMatch.levelNumber + currentMatch.worldNumber * 5;

	currentMatch.itemsToCollect = MapProcess(number, state->memory);
	EnemyInit();

	HeroShow(state->memory);

	ScreenOn();
	ColorsFadeIn(state->memory->palette, 32);

	//game logic
	while (TRUE)
	{
		ScreenWaitForVerticallBlank();

		ItemDraw(state->memory);

		EnemyDraw(state->memory);

		HeroHandleInput(&currentMatch, state->memory);

		if (InputMouseLeftButton())
		{
			state->exitToOs = TRUE;
			break;
		}

		if (0 == currentMatch.itemsToCollect)
		{
			state->run = GameNextLevel;
			break;
		}

		if (GAME_STATE_FAIL == currentMatch.state)
		{
			state->run = GameLevelFail;
			break;
		}
	}

	ColorsFadeOut(state->memory->palette, 32);
	ScreenOff();
	ScreenClear(&state->memory->screen);
	ColorsSetAllToBlack();
}

/*--------------------------------------------------------------------------*/

void Game(struct MainState* state)
{
	GameInit(state->memory);
	GameLoop(state);
}

/*--------------------------------------------------------------------------*/

void GameFailed(struct MainState* state)
{
	state->run = GameOver;
}

/*--------------------------------------------------------------------------*/

void GameLevelFail(struct MainState* state)
{
	currentMatch.livesNumber--;

	if (0 == currentMatch.livesNumber)
	{
		state->run = GameFailed;
		return;
	}

	state->run = GameLoop;
}

/*--------------------------------------------------------------------------*/

void GameNextLevel(struct MainState* state)
{
	state->run = GameLoop;

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
