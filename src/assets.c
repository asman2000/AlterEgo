#include "assets.h"

#include "decompress.h"
#include "io.h"
#include "sizes.h"

void AssetsGet(const MemoryDetails* m, ULONG address, AssetsOffset number);

/*--------------------------------------------------------------------------*/

ULONG AssetsLoad(const MemoryDetails* memory, const char* name)
{
	ULONG result = IoFileLoad(name, memory->assets.packed, ASSETS_SIZE);
	IoFlush();

	return result;
}

/*--------------------------------------------------------------------------*/

void AssetsGet(const MemoryDetails* m, ULONG address, AssetsOffset number)
{
	const ULONG* offsets = (const ULONG*)m->assets.packed;
	ULONG src = m->assets.packed + offsets[number];

	Decompress(src, address, m->assets.decrunchStack);
}

/*--------------------------------------------------------------------------*/

void AssetsScreen(const MemoryDetails* m)
{
	AssetsGet(m, m->copper.address, ASSET_COPPER);
}

/*--------------------------------------------------------------------------*/
void AssetsCredits(const MemoryDetails* m)
{
	AssetsGet(m, m->palette, ASSET_CREDITS_COLORS);
	AssetsGet(m, m->creditsText, ASSET_CREDITS_TXT);
	AssetsGet(m, m->smallFont, ASSET_FONTS8);
}

/*--------------------------------------------------------------------------*/
