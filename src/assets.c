#include "assets.h"

#include "io.h"
#include "memory.h"

#define ASSETS_SIZE (344)

static ULONG assetsAddress;
static ULONG* offsets;

/*--------------------------------------------------------------------------*/

ULONG AssetsLoad(const char* name)
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

	offsets = (ULONG*)assetsAddress;

	return RT_OK;
}

/*--------------------------------------------------------------------------*/

ULONG AssetsGet(AssetsOffset number)
{
	return assetsAddress + offsets[number];
}

/*--------------------------------------------------------------------------*/
