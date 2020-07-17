#include "assets.h"

#include "decompress.h"
#include "io.h"
#include "memory.h"

#include "sizes.h"


static ULONG assetsAddress;
static ULONG* offsets;

/*--------------------------------------------------------------------------*/

ULONG AssetsLoad(const char* name)
{
	MemoryAnyReset();
	assetsAddress = MemoryAnyGet(ASSETS_SIZE);
	DecompressSetStack(MemoryAnyGet(3072));

	MemoryAnySetTo(assetsAddress + ASSETS_SIZE + 3072);

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

void AssetsGet(ULONG address, AssetsOffset number)
{
	ULONG src = assetsAddress + offsets[number];

	Decompress(src, address);
}

/*--------------------------------------------------------------------------*/

ULONG AssetsPackedGet(AssetsOffset number)
{
	return assetsAddress + offsets[number];
}

/*--------------------------------------------------------------------------*/
