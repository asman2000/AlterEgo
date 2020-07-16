#ifndef ALETEREGO_MEMORY_H
#define ALETEREGO_MEMORY_H

#include "types.h"

/*--------------------------------------------------------------------------*/

ULONG MemoryAllocateAll(void);
void MemoryReleaseAll(void);

ULONG MemoryAnyGet(ULONG size);
void MemoryAnyReset(void);
void MemoryAnySetTo(ULONG origin);

ULONG MemoryChipGet(ULONG size);
void MemoryChipReset(void);
void MemoryChipSetTo(ULONG origin);


/*--------------------------------------------------------------------------*/

#endif /* ALETEREGO_MEMORY_H */
