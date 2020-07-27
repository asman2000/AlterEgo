#ifndef ALTEREGO_HERO_H
#define ALTEREGO_HERO_H
/*--------------------------------------------------------------------------*/

#include "types.h"
#include "sprite.h"

typedef enum 
{
	HERO_ONE,
	HERO_TWO
} HeroNumber;

struct Hero
{
	Sprite man;

	UWORD dir;
	UWORD steps;


	UBYTE state;
};


void HeroDraw(void);

void HeroHandleInput(UBYTE joy);

void HeroInit(HeroNumber number);
// void HeroProcess(UBYTE joy);
// void HeroMove(void);

/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_HERO_H */
