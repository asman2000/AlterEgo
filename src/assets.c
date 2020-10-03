#include "assets.h"

#include "decompress.h"
#include "io.h"
#include "sizes.h"

void AssetsGet(ULONG address, AssetsOffset number);

/*--------------------------------------------------------------------------*/

ULONG AssetsLoad(const char* name)
{
	ULONG result = IoFileLoad(name, mem->assetsPackedData, ASSETS_SIZE);
	IoFlush();

	return result;
}

/*--------------------------------------------------------------------------*/

void AssetsGet(ULONG address, AssetsOffset number)
{
	const ULONG* offsets = (const ULONG*)mem->assetsPackedData;
	ULONG src = mem->assetsPackedData + offsets[number];

	Decompress(src, address, mem->assetsDecrunchStack);
}

/*--------------------------------------------------------------------------*/

void AssetsScreen(void)
{
	AssetsGet(mem->copperAddress, ASSET_COPPER);
}

/*--------------------------------------------------------------------------*/

void AssetsCredits(void)
{
	AssetsGet(mem->palette, ASSET_CREDITS_COLORS);
	AssetsGet(mem->creditsText, ASSET_CREDITS_TXT);
	AssetsGet(mem->smallFont, ASSET_FONTS8);
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

void AssetsMap(UWORD levelNumber)
{
	AssetsGet(mem->gameLevel, worldLevels[levelNumber]);	
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


void AssetsGameWorldPalette(UBYTE worldNumber)
{
	AssetsGet(mem->palette, worldColors[worldNumber]);
}

UBYTE worldMusic[] = 
{ 
	ASSET_MOD_WORLD0,
	ASSET_MOD_WORLD1,
	ASSET_MOD_WORLD2,
	ASSET_MOD_WORLD3,
	ASSET_MOD_WORLD4
};

void AssetsGameWorldMusic(UBYTE worldNumber)
{
	AssetsGet(mem->musicAddress, worldMusic[worldNumber]);
}

void AssetsGameLevelClear(void)
{
	AssetsGet(mem->musicAddress, ASSET_MOD_CLEAR);
}

/*--------------------------------------------------------------------------*/

void AssetsGameTiles(void)
{
	AssetsGet(mem->gameTiles, ASSET_TILES);
}

/*--------------------------------------------------------------------------*/

void AssetsGameSprites(void)
{
	AssetsGet(mem->spritesData, ASSET_SPRITES);
}

/*--------------------------------------------------------------------------*/

void AssetsGameOver(void)
{
	AssetsGet(mem->smallFont, ASSET_FONTS8);
	AssetsGet(mem->musicAddress, ASSET_MOD_GAMEOVER);
}

/*--------------------------------------------------------------------------*/

void AssetsTitle(void)
{
	AssetsGet(mem->smallFont, ASSET_FONTS8);
	AssetsGet(mem->musicAddress, ASSET_MOD_MENU);
}

/*--------------------------------------------------------------------------*/

void AssetsWellDone(void)
{
	AssetsGet(mem->smallFont, ASSET_FONTS8);
	AssetsGet(mem->musicAddress, ASSET_MOD_CONGRATS);
}

/*--------------------------------------------------------------------------*/

void AssetsSfx(void)
{
	AssetsGet(mem->sfxAddress, ASSET_SFX);
}

/*--------------------------------------------------------------------------*/
