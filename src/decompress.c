#include "decompress.h"

static ULONG stack;

extern void ShrinklerDecompress(
	__reg("a0") ULONG src, __reg("a1") ULONG dst,
	__reg("a4") ULONG stack);

/*--------------------------------------------------------------------------*/

void Decompress(ULONG src, ULONG dst)
{
	ShrinklerDecompress(src, dst, stack);
}

/*--------------------------------------------------------------------------*/

void DecompressSetStack(ULONG adr)
{
	stack = adr + 3072;
}

/*--------------------------------------------------------------------------*/