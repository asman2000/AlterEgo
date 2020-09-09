#ifndef ALTEREGO_MEMORYANY_H
#define ALTEREGO_MEMORYANY_H

#include "types.h"

/*--------------------------------------------------------------------------*/

ULONG MemoryAnyAllocate(ULONG size);

void MemoryAnyFree(ULONG memory, ULONG size);


/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_MEMORYANY_H */
