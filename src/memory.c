#include "memory.h"

#include <proto/exec.h>

#include "types.h"



#define MEMORY_OTHER_SIZE (100*1024)
#define MEMORY_CHIP_SIZE (200*1024)

static ULONG memoryChip = NULL;
static ULONG memoryOther = NULL;

/*--------------------------------------------------------------------------*/

ULONG MemoryAllocateAll(void)
{
        memoryChip = (ULONG)AllocMem(MEMORY_CHIP_SIZE, MEMF_CHIP);

        if (NULL == memoryChip)
        {
                return RT_NOT_ENOUGH_CHIP_MEM;
        }

        memoryOther = (ULONG)AllocMem(MEMORY_OTHER_SIZE, MEMF_ANY);

        if (NULL == memoryOther)
        {
                return RT_NOT_ENOUGH_ANY_MEM;
        }

        return RT_OK;
}

/*--------------------------------------------------------------------------*/

void MemoryReleaseAll(void)
{
        if (NULL != memoryOther)
        {
                FreeMem((APTR)memoryOther, MEMORY_OTHER_SIZE);
        }

        if (NULL != memoryChip)
        {
                FreeMem((APTR)memoryChip, MEMORY_CHIP_SIZE);
        }
}

/*--------------------------------------------------------------------------*/
