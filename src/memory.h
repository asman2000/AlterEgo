#ifndef ALETEREGO_MEMORY_H
#define ALETEREGO_MEMORY_H

#include "types.h"

/*--------------------------------------------------------------------------*/

ULONG MemoryAllocateAll(void);
void MemoryReleaseAll(void);

ULONG MemoryGetAny(ULONG size);
ULONG MemoryGetChip(ULONG size);

/*--------------------------------------------------------------------------*/

#endif /* ALETEREGO_MEMORY_H */
