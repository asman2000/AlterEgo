#include "error.h"
#include "string.h"

#include <proto/dos.h>

typedef struct 
{
        ULONG code;
        const char* msg;
} Error;

Error Errors[] =
{
        {RT_FAILED_OPEN_GFX, "Cannot oper graphics.library"},
        {RT_NOT_ENOUGH_CHIP_MEM, "Not enough CHIP memory"},
        {RT_NOT_ENOUGH_ANY_MEM, "Not enough any memory"},
};

/*--------------------------------------------------------------------------*/

static const char* FindErrorMsg(ULONG code)
{
        ULONG i = ARRAY_SIZE(Errors);

        Error* error = Errors;

        do
        {
                if (code == error->code)
                {
                        return error->msg;
                }

                error++;
                --i;

        } while (0 != i);

        return "Unknown error";
}

/*--------------------------------------------------------------------------*/

void ErrorShow(ULONG errorCode)
{
        if (RT_OK == errorCode || RT_FAILED_OPEN_DOS == errorCode)
        {
                return;
        }

        BPTR out = Output();

        if (0 != out)
        {
                const char* msg = FindErrorMsg(errorCode);

                Write(out, (const APTR)msg, (LONG)strlen(msg) );
                Write(out, (const APTR)"\n", 1);
        }
}

/*--------------------------------------------------------------------------*/
