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
} Sprite;

void SpriteInit(void);

ULONG SpriteGetFalse(void);

void SpriteDraw(Sprite* sprite);



/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_SPRITE_H */