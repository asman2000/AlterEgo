#include <stdio.h>

#include <proto/exec.h>
#include "microunit.h"

#include "../src/libs.h"

#include "decompressTest.h"
#include "assetsTest.h"


int testsRun = 0;
int testsFailed = 0;

char* ulongToDec(ULONG n);

int main(void)
{
	LibsOpen();

	//assets tests
	muRun(testAssets);
	muRun(testAssetFonts8);
	muRun(testAssetCopper);
	muRun(testAssetWorld0Colors);

	// decompress tests
	muRun(testDecompress);

	printFnc("total:", ulongToDec(testsRun));
	printFnc("passed:", ulongToDec(testsRun-testsFailed));
	printFnc("failed:", ulongToDec(testsFailed));

	LibsClose();

	return 0;
}

static char msgDec[11];

char* ulongToDec(ULONG n)
{
	ULONG tab[] = {
		1000000000,
		100000000,
		10000000,
		1000000,
		100000,
		10000,
		1000,
		100,
		10,
	};

	int index = 0;

	for (int i = 0; i < 9; ++i)
	{
		msgDec[index] = '0';

		while (n >= tab[i])
		{
			n -= tab[i];
			msgDec[index]++;
		}

		index++;
	}

	msgDec[index++] = '0' + n;
	msgDec[index] = 0;

	char* result = msgDec;

	for (int i = 0; i < 9; ++i)
	{
		if (*result == '0')
		{
			result++;
		}
	}

	return result;
}