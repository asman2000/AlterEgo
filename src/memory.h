#ifndef ALETEREGO_MEMORY_H
#define ALETEREGO_MEMORY_H

#include "types.h"

/*--------------------------------------------------------------------------*/

ULONG MemoryAllocateAll(void);
void MemoryReleaseAll(void);

ULONG MemoryAnyGet(ULONG size);
ULONG MemoryGetChip(ULONG size);

void MemoryAnyReset(void);
void MemoryAnySetTo(ULONG origin);

/*--------------------------------------------------------------------------*/

#endif /* ALETEREGO_MEMORY_H */
