#include <stdio.h>
#include "microunit.h"

#include "../src/error.c"

int testsRun = 0;
int testsFailed = 0;

static void testFindErrorMsg0(void)
{
	const char* result = FindErrorMsg(RT_FAILED_OPEN_DOS);
	muAssert(result == unknownError, "bad result");
}

static void testFindErrorMsg1(void)
{
	const char* result = FindErrorMsg(0xffffffff);
	muAssert(result == unknownError, "bad result");
}

static void testFindErrorMsg2(void)
{
	const char* result = FindErrorMsg(RT_OK);
	muAssert(result == unknownError, "bad result");
}

int main(void)
{
	muRun(testFindErrorMsg0);
	muRun(testFindErrorMsg1);
	muRun(testFindErrorMsg2);

	printf("total: %d, ", testsRun);
	printf("passed: %d, ", testsRun-testsFailed);
	printf("failed: %d\n", testsFailed);

	return 0;
}
