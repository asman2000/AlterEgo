#ifndef ALTEREGO_MEMORY_H
#define ALTEREGO_MEMORY_H

#include "types.h"

/*--------------------------------------------------------------------------*/

ULONG MemoryAllocateAll(void);
void MemoryReleaseAll(void);

MemoryDetails* MemoryGetDetails(void);

/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_MEMORY_H */
