#ifndef ALTEREGO_IO_H
#define ALTEREGO_IO_H

#include "types.h"

/*--------------------------------------------------------------------------*/

void IoFlush(void);

ULONG IoFileLoad(const char* name, ULONG buffer, ULONG length);

/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_IO_H */
