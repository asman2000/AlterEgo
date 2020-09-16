#include "memory.h"

#include "memorychip.h"
#include "memoryany.h"

#include <proto/exec.h>

#include "sizes.h"

static ULONG memoryChip;
static ULONG memoryAny;


static ULONG memoryAnyCurrent;
static ULONG memoryAnyOrigin;

static ULONG memoryChipCurrent;
static ULONG memoryChipOrigin;

/*--------------------------------------------------------------------------*/

ULONG MemoryAllocateAll(void)
{
	memoryChip = MemoryChipAllocate(MEMORY_CHIP_SIZE);

	if (0 == memoryChip)
	{
		return RT_NOT_ENOUGH_CHIP_MEM;
	}

	memoryAny = MemoryAnyAllocate(MEMORY_OTHER_SIZE);

	if (0 == memoryAny)
	{
		return RT_NOT_ENOUGH_ANY_MEM;
	}

	MemoryChipSetTo(memoryChip);
	MemoryAnySetTo(memoryAny);

	return RT_OK;
}

/*--------------------------------------------------------------------------*/

void MemoryReleaseAll(void)
{
	MemoryAnyFree(memoryAny, MEMORY_OTHER_SIZE);
	MemoryChipFree(memoryChip, MEMORY_CHIP_SIZE);
}

/*--------------------------------------------------------------------------*/

ULONG MemoryAnyGet(ULONG size)
{
	ULONG result = memoryAnyCurrent;
	memoryAnyCurrent += size;

	return result;
}

/*--------------------------------------------------------------------------*/

void MemoryAnyReset(void)
{
	memoryAnyCurrent = memoryAnyOrigin;
}

/*--------------------------------------------------------------------------*/

void MemoryAnySetToCurrent(void)
{
	MemoryAnySetTo(memoryAnyCurrent);
}

/*--------------------------------------------------------------------------*/

void MemoryAnySetTo(ULONG origin)
{
	memoryAnyOrigin = origin;
	MemoryAnyReset();
}

/*--------------------------------------------------------------------------*/

ULONG MemoryChipGet(ULONG size)
{
	ULONG result = memoryChipCurrent;
	memoryChipCurrent += size;

	return result;
}

/*--------------------------------------------------------------------------*/

void MemoryChipReset(void)
{
	memoryChipCurrent = memoryChipOrigin;
}

/*--------------------------------------------------------------------------*/

void MemoryChipSetToCurrent(void)
{
	MemoryChipSetTo(memoryChipCurrent);
}

/*--------------------------------------------------------------------------*/
void MemoryChipSetTo(ULONG origin)
{
	memoryChipOrigin = origin;
	MemoryChipReset();
}

/*--------------------------------------------------------------------------*/

#define DECOMPRESS_STACK_SIZE (1024*5)

struct MemoryDetails memDetails;

struct MemoryDetails* MemoryDetailsInit(void)
{
	//--- C H I P ---

	memDetails.screen.address = MemoryChipGet(SCREEN_SIZE);
	memDetails.screen.bpl = 4;
	memDetails.screen.brow = 40;
	memDetails.screen.height = 256;

	memDetails.copper.address = MemoryChipGet(COPPER_SIZE);

	memDetails.sprites.fake =  MemoryChipGet(SPRITES_SIZE);
	memDetails.sprites.hero = memDetails.sprites.fake + 8;
	memDetails.sprites.ego = memDetails.sprites.hero + 18 * 4;


	//--- A N Y ---

	memDetails.assets.packed = MemoryAnyGet(ASSETS_SIZE);
	memDetails.assets.decrunchStack = MemoryAnyGet(DECOMPRESS_STACK_SIZE);


	return &memDetails;
}

/*--------------------------------------------------------------------------*/
