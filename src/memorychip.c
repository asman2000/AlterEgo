#include "memorychip.h"

#include <proto/exec.h>

/*--------------------------------------------------------------------------*/

ULONG MemoryChipAllocate(ULONG size)
{
	return (ULONG)AllocMem(size, MEMF_CHIP);
}

/*--------------------------------------------------------------------------*/

void MemoryChipFree(ULONG memory, ULONG size)
{
	if (0 != memory)
	{
		FreeMem((APTR)memory, size);
	}
}

/*--------------------------------------------------------------------------*/
