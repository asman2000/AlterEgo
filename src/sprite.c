#include "sprite.h"

#include "assets.h"
#include "memory.h"
#include "sizes.h"

static ULONG spriteData;
static ULONG spriteFake;

/*--------------------------------------------------------------------------*/

void SpriteInit(void)
{
	spriteData = MemoryChipGet(SPRITES_SIZE + 8);
	spriteFake = spriteData + SPRITES_SIZE;

	AssetsGet(spriteData, ASSET_SPRITES);

	ULONG* fake =(ULONG*)(spriteFake);
	*fake++ = 0;
	*fake++ = 0;
}

/*--------------------------------------------------------------------------*/

ULONG SpriteGetFalse(void)
{
	return spriteFake;
}

/*--------------------------------------------------------------------------*/
void SpriteDraw(Sprite* sprite)
{
	const UWORD startX = 128;
	const UWORD startY = 44;
	const UWORD height = 16;

	UWORD* pos = (UWORD*)sprite->dst;
	UWORD* ctl = (UWORD*)sprite->dst + 1;

	UWORD x = sprite->x + startX;
	UWORD y = sprite->y + startY;
	UWORD s = y + height;

	*pos = (y << 8) + (x >> 1);
	*ctl = (s << 8) + x & 1 + (y >> 6 & 4) + (s >> 7 & 2);

	ULONG* dst = (ULONG*)sprite->dst + 1;
	ULONG* src = (ULONG*)sprite->src;
	
	ULONG i = height;
	do
	{
		*dst++ = *src++;
		--i;
	} while (i != 0);
}

/*--------------------------------------------------------------------------*/
