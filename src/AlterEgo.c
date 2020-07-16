#include "alterego.h"

#include "error.h"
#include "memory.h"
#include "io.h"
#include "os.h"
#include "input.h"

/*--------------------------------------------------------------------------*/

static ULONG AlterEgoInit(void)
{
	IoFlush();

	ULONG result = MemoryAllocateAll();

	if (RT_OK == result)
	{
		OsStore();
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
