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


static struct State state;

/*--------------------------------------------------------------------------*/

static ULONG AlterEgoInit(void)
{
	ULONG result = MemoryAllocateAll();

	if (RT_OK == result)
	{
		state.memory =  MemoryDetailsInit();
		state.exitToOs = FALSE;
		state.run = Credits;

		result = AssetsLoad("data.bin");

		if (RT_OK == result)
		{
			OsStore();
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

static void AlterEgoLoop(void)
{
	struct State* gameState = &state;

	while (TRUE)
	{
		gameState->run(gameState);

		if (TRUE == gameState->exitToOs)
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
