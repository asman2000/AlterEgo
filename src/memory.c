#include "memory.h"

#include <proto/exec.h>

#include "sizes.h"

static ULONG memoryChip = NULL;
static ULONG memoryAny = NULL;

static ULONG memoryAnyCurrent;
static ULONG memoryChipCurrent;
/*--------------------------------------------------------------------------*/

ULONG MemoryAllocateAll(void)
{
	memoryChip = (ULONG)AllocMem(MEMORY_CHIP_SIZE, MEMF_CHIP);

	if (NULL == memoryChip)
	{
		return RT_NOT_ENOUGH_CHIP_MEM;
	}

	memoryAny = (ULONG)AllocMem(MEMORY_OTHER_SIZE, MEMF_ANY);

	if (NULL == memoryAny)
	{
		return RT_NOT_ENOUGH_ANY_MEM;
	}

	memoryChipCurrent = memoryChip;
	memoryAnyCurrent = memoryAny;

	return RT_OK;
}

/*--------------------------------------------------------------------------*/

void MemoryReleaseAll(void)
{
	if (NULL != memoryAny)
	{
		FreeMem((APTR)memoryAny, MEMORY_OTHER_SIZE);
	}

	if (NULL != memoryChip)
	{
		FreeMem((APTR)memoryChip, MEMORY_CHIP_SIZE);
	}
}

/*--------------------------------------------------------------------------*/

ULONG MemoryGetAny(ULONG size)
{
	ULONG result = memoryAnyCurrent;
	memoryAnyCurrent -= size;

	return result;
}

/*--------------------------------------------------------------------------*/

ULONG MemoryGetChip(ULONG size)
{
	ULONG result = memoryChipCurrent;
	memoryChipCurrent -= size;

	return result;
}

/*--------------------------------------------------------------------------*/
