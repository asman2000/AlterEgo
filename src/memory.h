#ifndef ALTEREGO_MEMORY_H
#define ALTEREGO_MEMORY_H

#include "types.h"

/*--------------------------------------------------------------------------*/

ULONG MemoryAllocateAll(void);
void MemoryReleaseAll(void);

void MemoryInitialize(void);

/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_MEMORY_H */
