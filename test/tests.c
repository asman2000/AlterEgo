#include <stdio.h>
#include "microunit.h"
#include "errorTest.h"
#include "decompressTest.h"

int testsRun = 0;
int testsFailed = 0;

int main(void)
{
	// error tests
	muRun(testFindErrorMsg0);
	muRun(testFindErrorMsg1);
	muRun(testFindErrorMsg2);

	// decompress tests
	muRun(testDecompress);

	printf("total: %d, ", testsRun);
	printf("passed: %d, ", testsRun-testsFailed);
	printf("failed: %d\n", testsFailed);

	return 0;
}
