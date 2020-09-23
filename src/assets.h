#ifndef ALTEREGO_ASSETS_H
#define ALTEREGO_ASSETS_H

#include "types.h"

typedef enum 
{
	ASSET_COPPER,
	ASSET_FONTS8,
	ASSET_SPRITES,
	ASSET_CREDITS_COLORS,
	ASSET_CREDITS_TXT,

	ASSET_SFX,

	ASSET_TILES,
	ASSET_WORLD0_COLORS,
	ASSET_WORLD0_0,
	ASSET_WORLD0_1,
	ASSET_WORLD0_2,
	ASSET_WORLD0_3,
	ASSET_WORLD0_4,

	ASSET_WORLD1_COLORS,
	ASSET_WORLD1_0,
	ASSET_WORLD1_1,
	ASSET_WORLD1_2,
	ASSET_WORLD1_3,
	ASSET_WORLD1_4,

	ASSET_WORLD2_COLORS,
	ASSET_WORLD2_0,
	ASSET_WORLD2_1,
	ASSET_WORLD2_2,
	ASSET_WORLD2_3,
	ASSET_WORLD2_4,

	ASSET_WORLD3_COLORS,
	ASSET_WORLD3_0,
	ASSET_WORLD3_1,
	ASSET_WORLD3_2,
	ASSET_WORLD3_3,
	ASSET_WORLD3_4,

	ASSET_WORLD4_COLORS,
	ASSET_WORLD4_0,
	ASSET_WORLD4_1,
	ASSET_WORLD4_2,
	ASSET_WORLD4_3,
	ASSET_WORLD4_4,

	ASSET_MOD_CLEAR,
	ASSET_MOD_CONGRATS,
	ASSET_MOD_GAMEOVER,
	ASSET_MOD_MENU,
	ASSET_MOD_WORLD0,
	ASSET_MOD_WORLD1,
	ASSET_MOD_WORLD2,
	ASSET_MOD_WORLD3,
	ASSET_MOD_WORLD4,

	OFFSET_AMOUNT
} AssetsOffset;

/*--------------------------------------------------------------------------*/

ULONG AssetsLoad(const MemoryDetails* memory, const char* name);

void AssetsScreen(const MemoryDetails* m);

void AssetsCredits(const MemoryDetails* m);

void AssetsMap(const MemoryDetails* m, UWORD levelNumber);

void AssetsGameWorldPalette(const MemoryDetails* m, UBYTE worldNumber);
void AssetsGameWorldMusic(const MemoryDetails* m, UBYTE worldNumber);

void AssetsGameTiles(const MemoryDetails* m);
void AssetsGameSprites(const MemoryDetails* m);

void AssetsTitle(const MemoryDetails* m);

void AssetsGameOver(const MemoryDetails* m);
/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_ASSETS_H */
