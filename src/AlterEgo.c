#include "alterego.h"

#include "assets.h"
#include "error.h"
#include "memory.h"
#include "os.h"
#include "input.h"
#include "copper.h"
#include "screen.h"

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
	//CopperInit();
	//CopperStart();
	ScreenInit();
	ScreenStart();

	while (TRUE)
	{
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
