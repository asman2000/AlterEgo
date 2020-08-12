#ifndef ALTEREGO_HERO_H
#define ALTEREGO_HERO_H
/*--------------------------------------------------------------------------*/

#include "types.h"
#include "sprite.h"
#include "game.h"

typedef enum 
{
	HERO_ONE,
	HERO_TWO
} HeroNumber;

struct Hero
{
	Sprite man;
	Sprite ego;

	UWORD dir;
	UWORD steps;


	UBYTE state;
	UBYTE previousState;
	UBYTE unused;
	UBYTE idleCounter;

	UBYTE swaps;
	UBYTE syncType;
};


void HeroHandleInput(UBYTE joy, GameInfo* game);

void HeroSetUp(HeroNumber number);
void HeroInit(void);
void HeroShow(void);


void HeroSetPosition(UWORD x, UWORD y);
void HeroSetSyncType(UBYTE sync);
void HeroSetSwaps(UBYTE swaps);


/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_HERO_H */
