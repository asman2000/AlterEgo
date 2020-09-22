#include "sprite.h"

#include "input.h"

#include "copper.h"


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

void SpriteDrawHero(Sprite* sprite, const MemoryDetails* memory)
{
	UWORD frame = sprite->frame + sprite->frameOffset;
	sprite->src = memory->sprites.data + frame * 16 * 4;
	sprite->dst = memory->sprites.hero;
	SpriteDraw(sprite);

	ULONG copperSprite = memory->copper.address + 9 * 4 + 2 + 5 * 8;
	CopperUpdateAddress(copperSprite, memory->sprites.hero);
}

/*--------------------------------------------------------------------------*/

void SpriteDrawEgo(Sprite* sprite, const MemoryDetails* memory)
{
	UWORD frame = sprite->frame + sprite->frameOffset;
	sprite->src = memory->sprites.data + frame * 16 * 4;
	sprite->dst = memory->sprites.ego;
	SpriteDraw(sprite);

	ULONG hero = memory->sprites.hero;
	ULONG ego = memory->sprites.ego;

	hero = ego;

	ULONG copperSprite = memory->copper.address + 9 * 4 + 2 + 4 * 8;
	CopperUpdateAddress(copperSprite, memory->sprites.ego);
}

/*--------------------------------------------------------------------------*/
