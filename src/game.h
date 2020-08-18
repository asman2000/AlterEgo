#ifndef ALTEREGO_GAME_H
#define ALTEREGO_GAME_H

#include "types.h"

#define GAME_STATE_FAIL 1
#define GAME_STATE_NOTHING 0

typedef struct
{
	UBYTE worldNumber;
	UBYTE levelNumber;
	UWORD itemsToCollect;
	UWORD livesNumber;

	UBYTE state;
} GameInfo;

/*--------------------------------------------------------------------------*/
void GameInit(void);

void Game(struct State* gameState);

/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_GAME_H */
