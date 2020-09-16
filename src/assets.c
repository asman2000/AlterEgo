#include "assets.h"

#include "decompress.h"
#include "io.h"
#include "sizes.h"

/*--------------------------------------------------------------------------*/

ULONG AssetsLoad(const MemoryDetails* memory, const char* name)
{
	ULONG result = IoFileLoad(name, memory->assets.packed, ASSETS_SIZE);
	IoFlush();

	return result;
}

/*--------------------------------------------------------------------------*/

void AssetsGet(const MemoryDetails* memory, ULONG address, AssetsOffset number)
{
	const ULONG* offsets = (const ULONG*)memory->assets.packed;
	ULONG src = memory->assets.packed + offsets[number];

	Decompress(src, address, memory->assets.decrunchStack);
}

/*--------------------------------------------------------------------------*/

void AssetsCredits(const MemoryDetails* m)
{
	AssetsGet(m, m->copper.address, ASSET_COPPER);
	AssetsGet(m, m->palette, ASSET_CREDITS_COLORS);
	AssetsGet(m, m->creditsText, ASSET_CREDITS_TXT);
	AssetsGet(m, m->smallFont, ASSET_FONTS8);
}

/*--------------------------------------------------------------------------*/
