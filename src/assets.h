#ifndef ALTEREGO_ASSETS_H
#define ALTEREGO_ASSETS_H

#include "types.h"

typedef enum 
{
	ASSET_COPPER,
	ASSET_FONTS8,
	ASSET_SPRITES,

	OFFSET_AMOUNT
} AssetsOffset;

/*--------------------------------------------------------------------------*/

ULONG AssetsLoad(const char* name);

ULONG AssetsPackedGet(AssetsOffset number);

void AssetsGet(ULONG address, AssetsOffset number);

/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_ASSETS_H */
