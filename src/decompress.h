#ifndef ALTEREGO_DECOMPRESS_H
#define ALTEREGO_DECOMPRESS_H

#include "types.h"

#define DECOMPRESS_STACK_SIZE (1024*5)
/*--------------------------------------------------------------------------*/

void Decompress(ULONG src, ULONG dst);

void DecompressSetStack(ULONG adr);
/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_DECOMPRESS_H */
