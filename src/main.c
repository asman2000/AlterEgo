#include "alterego.h"

#include <proto/exec.h>

struct DosLibrary* DOSBase;
struct GfxBase* GfxBase;

static const char* dosName = "dos.library";
static const char* gfxName = "graphics.library";

/*--------------------------------------------------------------------------*/

static ULONG LibsOpen(void)
{
	DOSBase = (struct DosLibrary*)OldOpenLibrary(dosName);

	if (NULL == DOSBase)
	{
		return RT_FAILED_OPEN_DOS;
	}

	GfxBase = (struct GfxBase*)OldOpenLibrary(gfxName);

	if (NULL == GfxBase)
	{
		return RT_FAILED_OPEN_GFX;
	}


	return RT_OK;
}

/*--------------------------------------------------------------------------*/

static void LibsClose(void)
{
	if (GfxBase)
	{
		CloseLibrary((struct Library*)GfxBase);
	}

	if (DOSBase)
	{
		CloseLibrary((struct Library*)DOSBase);
	}

}

/*--------------------------------------------------------------------------*/


int main(void)
{
	ULONG result = LibsOpen();

	if (RT_OK == result)
	{
		AlterEgo();
	}

	LibsClose();

	return 0;
}

/*--------------------------------------------------------------------------*/
