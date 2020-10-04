#ifndef ALTEREGO_TYPES_H
#define ALTEREGO_TYPES_H

/*--------------------------------------------------------------------------*/

#define GAME_DEBUG 1


#ifdef _WINDOWS
#define __reg(string)
#endif

#include <exec/types.h>

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

enum Returns
{
	RT_OK = 0,
	RT_FAILED_OPEN_DOS,
	RT_FAILED_OPEN_GFX,
	RT_NOT_ENOUGH_CHIP_MEM,
	RT_NOT_ENOUGH_ANY_MEM,
	RT_FAILED_LOAD_DATA,
};

struct GlobalMainState;
typedef void (*Fnc)(void);

struct GlobalMainState
{
	Fnc run;
	UBYTE exitToOs;
};

#define GAME_STATE_FAIL 1
#define GAME_STATE_NOTHING 0

/*--------------------------------------------------------------------------*/

typedef struct _Memories
{
	//any
	ULONG spritesData;
	ULONG assetsPackedData;
	ULONG assetsDecrunchStack;
	ULONG palette;
	ULONG creditsText;
	ULONG smallFont;
	ULONG gameLevel;
	ULONG gameTiles;

	// chip
	ULONG screenAddress;
	ULONG copperAddress;
	ULONG spriteFakeAddress;
	ULONG spriteHeroAddress;
	ULONG spriteEgoAddress;
	ULONG spriteEnemyAddress;
	ULONG musicAddress;
	ULONG sfxAddress;

	//variables
	UWORD screenBpl;
	UWORD screenBrow;
	UWORD screenHeight;

	struct GlobalMainState mainState;
} Memories;

extern Memories* mem;
/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_TYPES_H */
