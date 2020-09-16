#ifndef ALTEREGO_MEMORY_H
#define ALTEREGO_MEMORY_H

#include "types.h"

/*--------------------------------------------------------------------------*/

ULONG MemoryAllocateAll(void);
void MemoryReleaseAll(void);


struct MemoryDetails* MemoryDetailsInit(void);


ULONG MemoryAnyGet(ULONG size);
void MemoryAnyReset(void);
void MemoryAnySetTo(ULONG origin);
void MemoryAnySetToCurrent(void);

ULONG MemoryChipGet(ULONG size);
void MemoryChipReset(void);
void MemoryChipSetTo(ULONG origin);
void MemoryChipSetToCurrent(void);


/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_MEMORY_H */
