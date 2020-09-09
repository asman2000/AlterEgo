#ifndef ALTEREGO_MEMORYCHIP_H
#define ALTEREGO_MEMORYCHIP_H

#include "types.h"

/*--------------------------------------------------------------------------*/

ULONG MemoryChipAllocate(ULONG size);

void MemoryChipFree(ULONG memory, ULONG size);


/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_MEMORYCHIP_H */
