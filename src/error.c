#include "error.h"
#include "string.h"

#include <proto/dos.h>

typedef struct 
{
	const ULONG code;
	const char* msg;
} Error;

static Error Errors[] =
{
	{RT_FAILED_OPEN_GFX, "Cannot open graphics.library"},
	{RT_NOT_ENOUGH_CHIP_MEM, "Not enough CHIP memory"},
	{RT_NOT_ENOUGH_ANY_MEM, "Not enough any memory"},
	{RT_FAILED_LOAD_DATA, "Cannot open/read data.bin"},
};

static const char* unknownError = "Unknown error";
/*--------------------------------------------------------------------------*/

static const char* FindErrorMsg(ULONG code)
{
	ULONG i = ARRAY_SIZE(Errors);

	Error const * error = Errors;

	do
	{
		if (code == error->code)
		{
			return error->msg;
		}

		error++;
		--i;

	} while (0 != i);

	return unknownError;
}

/*--------------------------------------------------------------------------*/

void ErrorShow(ULONG errorCode)
{
	if (RT_OK == errorCode || RT_FAILED_OPEN_DOS == errorCode)
	{
		return;
	}

	const BPTR out = Output();

	if (0 != out)
	{
		const char* msg = FindErrorMsg(errorCode);

		Write(out, (const APTR)msg, (LONG)strlen(msg) );
		Write(out, (const APTR)"\n", 1);
	}
}

/*--------------------------------------------------------------------------*/
