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

typedef struct _CopperDetails
{
	ULONG address;
} CopperDetails;

typedef struct _ScreenDetails
{
	UWORD bpl;
	UWORD brow;
	UWORD height;
	ULONG address;
} ScreenDetails;

typedef struct _SpritesDetails
{
	ULONG fake;
	ULONG hero;
	ULONG ego;
	ULONG enemies;
	ULONG data;
} SpritesDetails;

typedef struct _AssetsDetails
{
	ULONG packed;
	ULONG decrunchStack;
} AssetsDetails;

typedef struct _GameDetails
{
	ULONG level;
	ULONG tiles;

} GameDetails;

typedef struct _MemoryDetails
{
	CopperDetails copper;
	ScreenDetails screen;
	SpritesDetails sprites;

	ULONG palette;
	ULONG creditsText;
	ULONG smallFont;

	AssetsDetails assets;

	GameDetails game;

} MemoryDetails;


struct MainState;
typedef void (*StateFunction)(struct MainState*);

struct MainState
{
	StateFunction run;

	MemoryDetails* memory;

	UBYTE exitToOs;
};

#define GAME_STATE_FAIL 1
#define GAME_STATE_NOTHING 0

/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_TYPES_H */
