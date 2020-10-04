#include "sprite.h"

#include "input.h"

#include "copper.h"

#include <hardware/custom.h>
#include <hardware/dmabits.h>

extern struct Custom* custom;

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
	sprite->src = mem->spritesData+ frame * 16 * 4;
	sprite->dst = mem->spriteHeroAddress;
	SpriteDraw(sprite);

	ULONG copperSprite = mem->copperAddress + 9 * 4 + 2 + 5 * 8;
	CopperUpdateAddress(copperSprite, mem->spriteHeroAddress);
}

/*--------------------------------------------------------------------------*/

void SpriteDrawEgo(Sprite* sprite)
{
	UWORD frame = sprite->frame + sprite->frameOffset;
	sprite->src = mem->spritesData + frame * 16 * 4;
	sprite->dst = mem->spriteEgoAddress;
	SpriteDraw(sprite);

	ULONG copperSprite = mem->copperAddress + 9 * 4 + 2 + 4 * 8;
	CopperUpdateAddress(copperSprite, mem->spriteEgoAddress);
}

/*--------------------------------------------------------------------------*/

void SpritesOn(void)
{
	custom->dmacon = DMAF_SETCLR | DMAF_SPRITE;

}

/*--------------------------------------------------------------------------*/

void SpritesOff(void)
{
	custom->dmacon = DMAF_SPRITE;
}

/*--------------------------------------------------------------------------*/
