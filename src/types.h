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

struct CopperDetails
{
	ULONG address;
};

struct ScreenDetails
{
	UWORD bpl;
	UWORD brow;
	UWORD height;
	ULONG address;
};

struct SpritesDetails
{
	ULONG fake;
	ULONG hero;
	ULONG ego;
};

struct AssetsDetails
{
	ULONG packed;
	ULONG decrunchStack;
};


struct MemoryDetails
{
	struct CopperDetails copper;
	struct ScreenDetails screen;
	struct SpritesDetails sprites;

	struct AssetsDetails assets;
};


struct State;
typedef void (*StateFunction)(struct State*);

struct State
{
	StateFunction run;

	struct MemoryDetails* memory;

	UBYTE exitToOs;


};


/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_TYPES_H */
