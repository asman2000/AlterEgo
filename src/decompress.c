#include "decompress.h"

#include "sizes.h"

static ULONG stack;

extern void ShrinklerDecompress(
	__reg("a0") ULONG src, __reg("a1") ULONG dst,
	__reg("a4") ULONG stack);

/*--------------------------------------------------------------------------*/

void Decompress(ULONG src, ULONG dst, ULONG stack)
{
	ShrinklerDecompress(src, dst, stack);
}

/*--------------------------------------------------------------------------*/

