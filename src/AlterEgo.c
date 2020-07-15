#include "alterego.h"

#include "error.h"
#include "memory.h"
#include "io.h"
#include "decompress.h"

/*--------------------------------------------------------------------------*/

static ULONG AlterEgoInit(void)
{
	IoFlush();

	ULONG result = MemoryAllocateAll();

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
