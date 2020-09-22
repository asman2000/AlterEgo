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

MemoryDetails m;

MemoryDetails* MemoryGetDetails(void)
{
	m.screen.address = MemoryGetChip(SCREEN_SIZE);
	m.screen.bpl = 4;
	m.screen.brow = 40;
	m.screen.height = 256;

	m.copper.address = MemoryGetChip(COPPER_SIZE);

	m.sprites.fake =  MemoryGetChip(SPRITES_SIZE);
	m.sprites.hero = m.sprites.fake + 8;
	m.sprites.ego = m.sprites.hero + 18 * 4;
	m.sprites.enemies = m.sprites.ego + 18 * 4;

	m.sprites.data = MemoryGetAny(GFX_SPRITES_SIZE);


	m.assets.packed = MemoryGetAny(ASSETS_SIZE);
	ULONG stack = MemoryGetAny(DECOMPRESS_STACK_SIZE);
	m.assets.decrunchStack = stack + DECOMPRESS_STACK_SIZE;

	// credits
	m.palette = MemoryGetAny(PALETTE_SIZE);
	m.creditsText = MemoryGetAny(CREDITS_TEXTS_SIZE);
	m.smallFont = MemoryGetAny(FONTS8_SIZE);

	//game
	m.game.level = MemoryGetAny(LEVEL_SIZE);
	m.game.tiles = MemoryGetAny(TILES_SIZE);

	return &m;
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
