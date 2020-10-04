#ifndef ALTEREGO_GAME_H
#define ALTEREGO_GAME_H

#include "types.h"

typedef struct
{
	UBYTE worldNumber;
	UBYTE levelNumber;
	UWORD itemsToCollect;
	UWORD livesNumber;

	UBYTE state;
	UBYTE unused;
} Match;

/*--------------------------------------------------------------------------*/

void GameInit(void);

void Game(void);

/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_GAME_H */
