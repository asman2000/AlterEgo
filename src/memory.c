#include "memory.h"

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

	MemoryChipSetTo(memoryChip);
	MemoryAnySetTo(memoryAny);

	return RT_OK;
}

/*--------------------------------------------------------------------------*/

void MemoryReleaseAll(void)
{
	if (0 != memoryAny)
	{
		FreeMem((APTR)memoryAny, MEMORY_OTHER_SIZE);
	}

	if (0 != memoryChip)
	{
		FreeMem((APTR)memoryChip, MEMORY_CHIP_SIZE);
	}
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

void MemoryChipSetTo(ULONG origin)
{
	memoryChipOrigin = origin;
	MemoryChipReset();
}

/*--------------------------------------------------------------------------*/
