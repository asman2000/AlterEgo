#ifndef ALETEREGO_IO_H
#define ALETEREGO_IO_H

#include "types.h"

/*--------------------------------------------------------------------------*/

void IoFlush(void);

ULONG IoFileLoad(const char* name, ULONG buffer, ULONG length);

/*--------------------------------------------------------------------------*/

#endif /* ALETEREGO_IO_H */
