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
	stack = adr + DECOMPRESS_STACK_SIZE;

	ULONG i = DECOMPRESS_STACK_SIZE / 4;
	ULONG* src = (ULONG*)adr;
	do
	{
		*src++ = 0;

	} while (--i, 0 != i);
}

/*--------------------------------------------------------------------------*/
