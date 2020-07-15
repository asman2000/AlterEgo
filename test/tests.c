#include <stdio.h>
#include "microunit.h"

#include "decompressTest.h"
#include "assetsTest.h"


int testsRun = 0;
int testsFailed = 0;

int main(void)
{
	//assets tests
	muRun(testAssets);
	muRun(testAssetFonts8);

	// decompress tests
	muRun(testDecompress);

	printf("total: %d, ", testsRun);
	printf("passed: %d, ", testsRun-testsFailed);
	printf("failed: %d\n", testsFailed);

	return 0;
}
