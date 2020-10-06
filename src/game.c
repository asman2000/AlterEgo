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
#include "music.h"
#include "screen.h"
#include "sizes.h"
#include "smallfont.h"
#include "sprite.h"
#include "sfx.h"
#include "welldone.h"


Match currentMatch;

#define LEVEL_MAX_NUMBER 5
#define WORLD_MAX_NUMBER 5

static ULONG mapsData;



void GameNextLevel(void);
void GameLevelFail(void);
static void GameLoop(void);

/*--------------------------------------------------------------------------*/

void GameInit(void)
{
	currentMatch.levelNumber = 1;
	currentMatch.worldNumber = 4;
	currentMatch.itemsToCollect = 0;
	currentMatch.state = GAME_STATE_NOTHING;
	currentMatch.livesNumber = 1;


	AssetsGameTiles();
	AssetsGameSprites();

	HeroSetUp(HERO_ONE);

	ScreenOff();
	ScreenClear();
	ColorsSetAllToBlack();
}

/*--------------------------------------------------------------------------*/

static void GameLoop(void)
{
	AssetsGameWorldPalette(currentMatch.worldNumber);
	AssetsGameWorldMusic(currentMatch.worldNumber);
	
	UBYTE number = currentMatch.levelNumber + currentMatch.worldNumber * 5;

	currentMatch.itemsToCollect = MapProcess(number);
	EnemyInit();

	HeroShow();

	ScreenOn();
	ColorsFadeIn(mem->palette, 32);

	UBYTE frame_cnt = 0;

	MusicStart();

	//game logic
	while (TRUE)
	{
		ScreenWaitForVerticallBlank();
		mem->frameCounter++;
		
		frame_cnt++;

		ItemDraw();

		EnemyDraw();

		HeroHandleInput(&currentMatch);

		if (GAME_STATE_NOTHING == currentMatch.state)
		{
			struct Hero* hero = HeroGet();
			currentMatch.state = EnemyProcess(hero, frame_cnt);
		}

		if (InputMouseLeftButton())
		{
			mem->mainState.exitToOs = TRUE;
			break;
		}

		if (0 == currentMatch.itemsToCollect)
		{
			mem->mainState.run = GameNextLevel;
			return;
		}

		if (GAME_STATE_FAIL == currentMatch.state)
		{
			SfxPlay(SFX_HIT);
			mem->mainState.run = GameLevelFail;
			break;
		}
	}

	MusicStop();

	ColorsFadeOut(mem->palette, 32);
	ScreenOff();
	ScreenClear();
	ColorsSetAllToBlack();
}

/*--------------------------------------------------------------------------*/

void Game(void)
{
	GameInit();
	GameLoop();
}

/*--------------------------------------------------------------------------*/

void GameFailed(void)
{
	mem->mainState.run = GameOver;
}

/*--------------------------------------------------------------------------*/

void GameLevelFail(void)
{
	currentMatch.livesNumber--;

	if (0 == currentMatch.livesNumber)
	{
		mem->mainState.run = GameFailed;
		return;
	}

	mem->mainState.run = GameLoop;
}

/*--------------------------------------------------------------------------*/

void GameNextLevel(void)
{
	mem->mainState.run = GameLoop;
	
	MusicStop();

	AssetsGameLevelClear();

	MusicStart();

	UWORD counter = 200;

	do
	{
		ScreenWaitForVerticallBlank();

	}
	while (--counter, 0 != counter);


	currentMatch.levelNumber++;

	if (LEVEL_MAX_NUMBER == currentMatch.levelNumber)
	{
		currentMatch.levelNumber = 0;
		currentMatch.worldNumber++;

		if (WORLD_MAX_NUMBER == currentMatch.worldNumber)
		{
			mem->mainState.run = Welldone;
		}
	}
}

/*--------------------------------------------------------------------------*/
