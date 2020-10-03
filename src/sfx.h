#ifndef ALTEREGO_SFX_H
#define ALTEREGO_SFX_H
/*--------------------------------------------------------------------------*/

#include "types.h"

void SfxInit(void);
void SfxPlay(UWORD number);

enum SfxNames
{
	SFX_START			=0,
	SFX_MENU			=1,
	SFX_EXCHANGE			=2,
	SFX_ITEM1			=3,
	SFX_ITEM2			=4,
	SFX_HIT				=5,
	SFX_FALLING			=6,
	SFX_DROP			=7,
	SFX_NO_EXCHANGE			=8,
	SFX_OUT_OF_EXCHANGES 		=9,
	SFX_BRIDGE			=10,
	SFX_WALK1			=11,
	SFX_WALK2			=12,
	SFX_LADDER			=13,
	SFX_LEVEL_CLEAR			=14,

	SND_AMOUNT
};

/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_SFX_H */
