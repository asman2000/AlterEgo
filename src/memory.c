#include "memory.h"

#include <proto/exec.h>


#include "sizes.h"

static ULONG memoryChip;
static ULONG memoryAny;


static ULONG chipCurrent;
static ULONG anyCurrent;

static void MemoryRelease(ULONG memory, ULONG size);

ULONG MemoryGetChip(ULONG size);
ULONG MemoryGetAny(ULONG size);

/*--------------------------------------------------------------------------*/

ULONG MemoryAllocateAll(void)
{
	memoryChip = (ULONG)AllocMem(MEMORY_CHIP_SIZE, MEMF_CHIP);

	if (0 == memoryChip)
	{
		return RT_NOT_ENOUGH_CHIP_MEM;
	}

	memoryAny = (ULONG)AllocMem(MEMORY_OTHER_SIZE, MEMF_ANY);

	if (0 == memoryAny)
	{
		return RT_NOT_ENOUGH_ANY_MEM;
	}

	chipCurrent = memoryChip;
	anyCurrent = memoryAny;

	return RT_OK;
}

/*--------------------------------------------------------------------------*/

void MemoryReleaseAll(void)
{
	MemoryRelease(memoryAny, MEMORY_OTHER_SIZE);
	MemoryRelease(memoryChip, MEMORY_CHIP_SIZE);
}

/*--------------------------------------------------------------------------*/

static void MemoryRelease(ULONG memory, ULONG size)
{
	if (0 != memory)
	{
		FreeMem((APTR)memory, size);
	}
}

/*--------------------------------------------------------------------------*/

Memories* mem;

void MemoryInitialize(void)
{
	ULONG any = memoryAny;
	mem = (Memories*)memoryAny;
	any += sizeof(Memories);


	mem->spritesData = any;
	any += GFX_SPRITES_SIZE;

	mem->assetsPackedData = any;
	any += ASSETS_SIZE;

	mem->assetsDecrunchStack = any;
	any += DECOMPRESS_STACK_SIZE;

	// credits
	mem->palette = any;
	any +=  PALETTE_SIZE;
	
	mem->creditsText = any;
	any +=CREDITS_TEXTS_SIZE;

	mem->smallFont = any;
	any += FONTS8_SIZE;

	//game
	mem->gameLevel = any;
	any += LEVEL_SIZE;

	mem->gameTiles = any;
	any += TILES_SIZE;

	//correct assets stack to bottom of memory;
	mem->assetsDecrunchStack += DECOMPRESS_STACK_SIZE;


	// -- chip --

	ULONG chip = memoryChip;

	mem->screenAddress = chip;
	chip += SCREEN_SIZE;
	mem->copperAddress = chip;
	chip += COPPER_SIZE;
	mem->spriteFakeAddress = chip;
	chip += 8;
	mem->spriteHeroAddress = chip;
	chip += 18*4;
	mem->spriteEgoAddress = chip;
	chip += 18*4;
	mem->spriteEnemyAddress = chip;
	chip += 18*4*8;
	mem->musicAddress = chip;
	chip += MUSIC_SIZE;
	mem->sfxAddress = chip;
	chip += SFX_SIZE;

	mem->screenBpl = 4;
	mem->screenBrow = 40;
	mem->screenHeight = 256;
}

/*--------------------------------------------------------------------------*/
