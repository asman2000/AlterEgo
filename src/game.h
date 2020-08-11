#ifndef ALTEREGO_GAME_H
#define ALTEREGO_GAME_H

#include "types.h"

typedef struct
{
	UBYTE worldNumber;
	UBYTE levelNumber;
	UWORD itemsToCollect;
} GameInfo;

/*--------------------------------------------------------------------------*/
void GameInit(void);

void Game(struct State* gameState);

/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_GAME_H */
