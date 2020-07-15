#include "microunit.h"
#include "../src/decompress.h"

#include <proto/exec.h>
#include <proto/dos.h>


/*--------------------------------------------------------------------------*/

void testDecompress(void)
{
	ULONG mem = (ULONG)AllocMem(3072+288+656, MEMF_ANY);

	if (0 == mem)
	{
		return;
	}

	ULONG stack = mem;
	ULONG src = mem + 3072;
	ULONG dst = src + 288;

	BPTR file = Open("assets/raw-packed/fonts8x8x2.shr", MODE_OLDFILE);

	if (0 != file)
	{
		Read(file, (APTR)src, 288);
		Close(file);
	
	}
	
	DecompressSetStack(stack);
	Decompress(src, dst);

	ULONG *value = (ULONG *)dst;

	muAssert(*value == 0, "wrong depacked ulong");

	FreeMem((APTR)mem, 3072+288+656);
}

/*--------------------------------------------------------------------------*/
