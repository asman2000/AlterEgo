#ifndef ALTEREGO_HERO_H
#define ALTEREGO_HERO_H
/*--------------------------------------------------------------------------*/

#include "types.h"

typedef enum 
{
	HERO_ONE,
	HERO_TWO
} HeroNumber;


void HeroDraw(void);



void HeroInit(HeroNumber number);
void HeroProcess(UBYTE joy);
void HeroMove(void);

/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_HERO_H */
