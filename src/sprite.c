#include "sprite.h"

#include "assets.h"
#include "memory.h"
#include "sizes.h"
#include "copper.h"

static ULONG spriteGfxData;
static ULONG spriteFake;

static ULONG spriteHero;
static ULONG spriteEgo;
/*--------------------------------------------------------------------------*/

void SpriteInit(void)
{
	spriteGfxData = MemoryAnyGet(GFX_SPRITES_SIZE);
	AssetsGet(spriteGfxData, ASSET_SPRITES);

	spriteFake = MemoryChipGet(SPRITES_SIZE);

	ULONG i = SPRITES_SIZE / 4;
	ULONG* data = (ULONG*)spriteFake;
	do
	{
		*data++ = 0;

	} while (--i, 0 != i);

	spriteHero = spriteFake + 8;
	spriteEgo = spriteHero + 18 * 4;
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
	*ctl = (s << 8) + (x & 1) + (y >> 6 & 4) + (s >> 7 & 2);

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

void SpriteDrawHero(Sprite* sprite)
{
	UWORD frame = sprite->frame + sprite->frameOffset;
	sprite->src = spriteGfxData + frame * 16 * 4;
	sprite->dst = spriteHero;
	SpriteDraw(sprite);

	CopperUpdateSprite(spriteHero, 4);
}

/*--------------------------------------------------------------------------*/

void SpriteDrawEgo(Sprite* sprite)
{
	UWORD frame = sprite->frame + sprite->frameOffset;
	sprite->src = spriteGfxData + frame * 16 * 4;
	sprite->dst = spriteEgo;
	SpriteDraw(sprite);

	CopperUpdateSprite(spriteEgo, 5);
}

/*--------------------------------------------------------------------------*/
