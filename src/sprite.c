#include "sprite.h"

#include "assets.h"
#include "hero.h"
#include "memory.h"
#include "sizes.h"
#include "copper.h"

static ULONG spriteGfxData;
static ULONG spriteFake;

static ULONG spriteHero;
/*--------------------------------------------------------------------------*/

void SpriteInit(void)
{
	spriteGfxData = MemoryAnyGet(GFX_SPRITES_SIZE);
	AssetsGet(spriteGfxData, ASSET_SPRITES);

	spriteFake = MemoryChipGet(SPRITES_SIZE);

	ULONG* fake =(ULONG*)(spriteFake);
	*fake++ = 0;
	*fake++ = 0;

	spriteHero = spriteFake + 8;
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
static Sprite spr;

void SpriteDrawHero(UWORD x, UWORD y)
{
	spr.x = x;
	spr.y = y;
	spr.src = spriteGfxData;
	spr.dst = spriteHero;
	SpriteDraw(&spr);

	CopperUpdatSprite(spriteHero, 0);
}

/*--------------------------------------------------------------------------*/
