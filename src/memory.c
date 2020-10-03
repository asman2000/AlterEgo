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

MemoryDetails* m;

MemoryDetails* MemoryGetDetails(void)
{
	m = (MemoryDetails*)MemoryGetAny(sizeof(MemoryDetails));

	m->screen.address = MemoryGetChip(SCREEN_SIZE);
	m->screen.bpl = 4;
	m->screen.brow = 40;
	m->screen.height = 256;

	m->copper.address = MemoryGetChip(COPPER_SIZE);

	m->sprites.fake =  MemoryGetChip(SPRITES_SIZE);
	m->sprites.hero = m->sprites.fake + 8;
	m->sprites.ego = m->sprites.hero + 18 * 4;
	m->sprites.enemies = m->sprites.ego + 18 * 4;

	m->music = MemoryGetChip(MUSIC_SIZE);

	m->sfx = MemoryGetChip(SFX_SIZE);

	m->sprites.data = MemoryGetAny(GFX_SPRITES_SIZE);


	m->assets.packed = MemoryGetAny(ASSETS_SIZE);
	ULONG stack = MemoryGetAny(DECOMPRESS_STACK_SIZE);
	m->assets.decrunchStack = stack + DECOMPRESS_STACK_SIZE;

	// credits
	m->palette = MemoryGetAny(PALETTE_SIZE);
	m->creditsText = MemoryGetAny(CREDITS_TEXTS_SIZE);
	m->smallFont = MemoryGetAny(FONTS8_SIZE);

	//game
	m->game.level = MemoryGetAny(LEVEL_SIZE);
	m->game.tiles = MemoryGetAny(TILES_SIZE);

	return m;
}

/*--------------------------------------------------------------------------*/

void MemoryInitialize(void)
{
	ULONG any = memoryAny;
	Memories* mem = (Memories*)memoryAny;
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

ULONG MemoryGetChip(ULONG size)
{
	ULONG result = chipCurrent;
	chipCurrent += size;

	return result;
}

/*--------------------------------------------------------------------------*/

ULONG MemoryGetAny(ULONG size)
{
	ULONG result = anyCurrent;
	anyCurrent += size;

	return result;
}

/*--------------------------------------------------------------------------*/
