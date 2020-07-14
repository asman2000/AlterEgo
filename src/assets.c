#include "assets.h"

#include "io.h"
#include "memory.h"

#define ASSETS_SIZE (288)

static ULONG assetsAddress;

static const char* name = "data.bin";

/*--------------------------------------------------------------------------*/

ULONG AssetsLoad(void)
{
	MemoryAnyReset();
	assetsAddress = MemoryAnyGet(ASSETS_SIZE);
	MemoryAnySetTo(assetsAddress + ASSETS_SIZE);

	ULONG result = IoFileLoad(name, assetsAddress, ASSETS_SIZE);
	IoFlush();

	if (result != RT_OK)
	{
		return result;
	}

	return RT_OK;
}

/*--------------------------------------------------------------------------*/
