#include <stdio.h>

#include <proto/exec.h>
#include "microunit.h"

#include "decompressTest.h"
#include "assetsTest.h"


int testsRun = 0;
int testsFailed = 0;

struct GfxBase* GfxBase;
static const char* gfxName = "graphics.library";

int main(void)
{
	GfxBase = (struct GfxBase*)OldOpenLibrary(gfxName);
	//assets tests
	muRun(testAssets);
	muRun(testAssetFonts8);
	muRun(testAssetCopper);
	muRun(testAssetWorld0Colors);

	// decompress tests
	muRun(testDecompress);

	printf("total: %d, ", testsRun);
	printf("passed: %d, ", testsRun-testsFailed);
	printf("failed: %d\n", testsFailed);

	return 0;
}
