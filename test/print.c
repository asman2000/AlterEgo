#include "print.h"

#include <proto/dos.h>


/*--------------------------------------------------------------------------*/

static long strlen(const char* str)
{
	const char *s;

	for (s = str; *s; ++s)
		;

	return (s - str);
}


/*--------------------------------------------------------------------------*/

void printFnc(const char* fnc, const char* msg)
{
	const BPTR out = Output();
	Write(out, fnc, strlen(fnc));
	Write(out, " ", 1);
	Write(out, msg, strlen(msg));
	Write(out, "\n", 1);
}

/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
