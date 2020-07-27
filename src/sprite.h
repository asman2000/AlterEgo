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
} Sprite;

void SpriteInit(void);

ULONG SpriteGetFalse(void);

void SpriteDraw(Sprite* sprite);

void SpriteDrawHero(Sprite* sprite);



/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_SPRITE_H */
