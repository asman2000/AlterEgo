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

	UWORD steps;

	UBYTE state;
	UBYTE input;

	UBYTE swaps;
	UBYTE syncType;
};

typedef enum
{
	HERO_STATE_IDLE,
	HERO_STATE_WALK,
	HERO_STATE_LADDER,
	HERO_STATE_LADDER_IDLE,
	HERO_STATE_FALL,
	HERO_STATE_EXCHANGE

} HeroStates;


void HeroHandleInput(Match* game, const MemoryDetails* m);

void HeroSetUp(HeroNumber number);
void HeroInit(void);
void HeroShow(const MemoryDetails* m);


void HeroSetPosition(UWORD x, UWORD y);
void HeroSetSyncType(UBYTE sync);
void HeroSetSwaps(UBYTE swaps);

struct Hero* HeroGet(void);

/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_HERO_H */
