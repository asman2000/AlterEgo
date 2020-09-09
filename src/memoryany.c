#include "memoryany.h"

#include <proto/exec.h>

/*--------------------------------------------------------------------------*/

ULONG MemoryAnyAllocate(ULONG size)
{
	return (ULONG)AllocMem(size, MEMF_ANY);
}

/*--------------------------------------------------------------------------*/

void MemoryAnyFree(ULONG memory, ULONG size)
{
	if (0 != memory)
	{
		FreeMem((APTR)memory, size);
	}
}

/*--------------------------------------------------------------------------*/
