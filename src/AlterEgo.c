#include "alterego.h"

#include "error.h"
#include "libs.h"
#include "memory.h"
#include "io.h"

/*--------------------------------------------------------------------------*/

static ULONG AlterEgoInit(void)
{
	ULONG result = LibsOpen();

	if (RT_OK != result)
	{
		return result;
	}

	IoFlush();

	result = MemoryAllocateAll();

	return result;
}

/*--------------------------------------------------------------------------*/

static void AlterEgoKill(void)
{
	MemoryReleaseAll();

	LibsClose();
}

/*--------------------------------------------------------------------------*/

static void AlterEgoLoop(void)
{


}

/*--------------------------------------------------------------------------*/

void AlterEgo(void)
{
	ULONG result = AlterEgoInit();

	if (RT_OK == result)
	{
		AlterEgoLoop();
	}
	else
	{
		ErrorShow(result);
	}
	
	AlterEgoKill();
}

/*--------------------------------------------------------------------------*/
