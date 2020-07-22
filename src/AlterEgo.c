#include "alterego.h"

#include "assets.h"
#include "error.h"
#include "hero.h"
#include "input.h"
#include "memory.h"
#include "os.h"
#include "screen.h"
#include "credits.h"
#include "game.h"


/*--------------------------------------------------------------------------*/

static ULONG AlterEgoInit(void)
{
	ULONG result = MemoryAllocateAll();

	if (RT_OK == result)
	{
		result = AssetsLoad("data.bin");

		if (RT_OK == result)
		{
			OsStore();
			ScreenInit();
			MemoryAnySetToCurrent();
			MemoryChipSetToCurrent();
		}
	}

	return result;
}

/*--------------------------------------------------------------------------*/

static void AlterEgoKill(void)
{
	MemoryReleaseAll();
}

/*--------------------------------------------------------------------------*/

static struct State state;
static struct State* gameState = &state;

static void AlterEgoLoop(void)
{

	//gameState->run = Credits;
	gameState->run = Game;
	gameState->exitToOs = FALSE;

	//HeroDraw();

	while (TRUE)
	{
		gameState->run(gameState);

		if (TRUE == gameState->exitToOs)
		{
			break;
		}

		//temprorary
		if (InputMouseLeftButton())
		{
			break;
		}
	}
}

/*--------------------------------------------------------------------------*/

void AlterEgo(void)
{
	ULONG result = AlterEgoInit();

	if (RT_OK == result)
	{
		AlterEgoLoop();

		OsRestore();
	}
	else
	{
		ErrorShow(result);
	}
	
	AlterEgoKill();
}

/*--------------------------------------------------------------------------*/
