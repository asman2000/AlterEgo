#include "sprite.h"

#include "memory.h"

static ULONG spriteData;

#define SPRITES_SIZE (8)

/*--------------------------------------------------------------------------*/

void SpriteInit(void)
{
	spriteData = MemoryChipGet(SPRITES_SIZE);
}

/*--------------------------------------------------------------------------*/

ULONG SpriteGetFalse(void)
{
	return spriteData;
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
