#include "microunit.h"
#include "../src/error.c"

/*--------------------------------------------------------------------------*/

void testFindErrorMsg0(void)
{
	const char* result = FindErrorMsg(RT_FAILED_OPEN_DOS);
	muAssert(result == unknownError, "bad result");
}

/*--------------------------------------------------------------------------*/

void testFindErrorMsg1(void)
{
	const char* result = FindErrorMsg(0xffffffff);
	muAssert(result == unknownError, "bad result");
}

/*--------------------------------------------------------------------------*/

void testFindErrorMsg2(void)
{
	const char* result = FindErrorMsg(RT_OK);
	muAssert(result == unknownError, "bad result");
}

/*--------------------------------------------------------------------------*/
