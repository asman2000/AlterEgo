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
	UBYTE idleCounter;
};


void HeroHandleInput(UBYTE joy);

void HeroSetUp(HeroNumber number);
void HeroInit(void);

void HeroSetPosition(UWORD x, UWORD y);

/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_HERO_H */
