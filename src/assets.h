#ifndef ALETEREGO_ASSETS_H
#define ALETEREGO_ASSETS_H

#include "types.h"

typedef enum 
{
	ASSET_FONTS8,

	OFFSET_AMOUNT
} AssetsOffset;

/*--------------------------------------------------------------------------*/

ULONG AssetsLoad(const char* name);

ULONG AssetsGet(AssetsOffset number);

/*--------------------------------------------------------------------------*/

#endif /* ALETEREGO_ASSETS_H */
