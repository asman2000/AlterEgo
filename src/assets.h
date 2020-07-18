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

	ASSET_SFX00,
	ASSET_SFX01,
	ASSET_SFX02,
	ASSET_SFX03,
	ASSET_SFX04,
	ASSET_SFX05,
	ASSET_SFX06,
	ASSET_SFX07,
	ASSET_SFX08,
	ASSET_SFX09,
	ASSET_SFX10,
	ASSET_SFX11,
	ASSET_SFX12,
	ASSET_SFX13,
	ASSET_SFX14,

	OFFSET_AMOUNT
} AssetsOffset;

/*--------------------------------------------------------------------------*/

ULONG AssetsLoad(const char* name);

ULONG AssetsPackedGet(AssetsOffset number);

void AssetsGet(ULONG address, AssetsOffset number);

/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_ASSETS_H */
