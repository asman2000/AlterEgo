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
UWORD worldLevels[] =
{
	ASSET_WORLD0_0,
	ASSET_WORLD0_1,
	ASSET_WORLD0_2,
	ASSET_WORLD0_3,
	ASSET_WORLD0_4,

	ASSET_WORLD1_0,
	ASSET_WORLD1_1,
	ASSET_WORLD1_2,
	ASSET_WORLD1_3,
	ASSET_WORLD1_4,

	ASSET_WORLD2_0,
	ASSET_WORLD2_1,
	ASSET_WORLD2_2,
	ASSET_WORLD2_3,
	ASSET_WORLD2_4,

	ASSET_WORLD3_0,
	ASSET_WORLD3_1,
	ASSET_WORLD3_2,
	ASSET_WORLD3_3,
	ASSET_WORLD3_4,

	ASSET_WORLD4_0,
	ASSET_WORLD4_1,
	ASSET_WORLD4_2,
	ASSET_WORLD4_3,
	ASSET_WORLD4_4,
};

void AssetsMap(const MemoryDetails* m, UWORD levelNumber)
{
	AssetsGet(m, m->game.level, worldLevels[levelNumber]);	
}

/*--------------------------------------------------------------------------*/

UBYTE worldColors[] = 
{ 
	ASSET_WORLD0_COLORS,
	ASSET_WORLD1_COLORS,
	ASSET_WORLD2_COLORS,
	ASSET_WORLD3_COLORS,
	ASSET_WORLD4_COLORS,
};


void AssetsGameWorldPalette(const MemoryDetails* m, UBYTE worldNumber)
{
	AssetsGet(m, m->palette, worldColors[worldNumber]);
}

/*--------------------------------------------------------------------------*/

void AssetsGameTiles(const MemoryDetails* m)
{
	AssetsGet(m, m->game.tiles, ASSET_TILES);
}

/*--------------------------------------------------------------------------*/

void AssetsGameSprites(const MemoryDetails* m)
{
	AssetsGet(m, m->sprites.data, ASSET_SPRITES);
}

/*--------------------------------------------------------------------------*/

void AssetsGameOver(const MemoryDetails* m)
{
	AssetsGet(m, m->smallFont, ASSET_FONTS8);
}

/*--------------------------------------------------------------------------*/

void AssetsTitle(const MemoryDetails* m)
{
	AssetsGet(m, m->smallFont, ASSET_FONTS8);
}

/*--------------------------------------------------------------------------*/
