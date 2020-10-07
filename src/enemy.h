#ifndef ALTEREGO_ENEMY_H
#define ALTEREGO_ENEMY_H
/*--------------------------------------------------------------------------*/

#include "types.h"
#include "hero.h"

void EnemyInit(void);
UBYTE EnemyProcess(struct Hero* player);
void EnemyAdd(UWORD x, UWORD y, UWORD dir);
void EnemyDraw(void);
void EnemyInitCnt(void);


extern void EnemyClearSpritesBuffer(void);






/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_ENEMY_H */
