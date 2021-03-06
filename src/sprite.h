#ifndef ALTEREGO_SPRITE_H
#define ALTEREGO_SPRITE_H
/*--------------------------------------------------------------------------*/

#include "types.h"

typedef struct
{
	UWORD x;
	UWORD y;
	ULONG src;
	ULONG dst;
	UWORD frame;
	UWORD frameOffset;

	UWORD dx;
	UWORD dy;
} Sprite;

void SpriteDraw(Sprite* sprite);
void SpriteDrawHero(Sprite* sprite);
void SpriteDrawEgo(Sprite* sprite);

void SpritesOn(void);
void SpritesOff(void);

/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_SPRITE_H */
