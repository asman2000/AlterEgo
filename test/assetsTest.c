#include "microunit.h"

#include "../src/assets.h"
#include "../src/memory.h"

/*--------------------------------------------------------------------------*/

static ULONG loadAssets(void)
{
	ULONG result = MemoryAllocateAll();

	if (RT_OK == result)
	{
		result = AssetsLoad("exe/data.bin");

		if (RT_OK == result)
		{
			return RT_OK;
		}
		else
		{
			muFail("Cannot load assets");
		}
	}
	else
	{
		muFail("can't alloc memory");
	}
}


/*--------------------------------------------------------------------------*/

void testAssets(void)
{
	ULONG result = MemoryAllocateAll();

	if (RT_OK == result)
	{
		result = AssetsLoad("exe/data.bin");

		if (RT_OK == result)
		{
			ULONG offset = AssetsPackedGet(ASSET_FONTS8);

			muAssert(offset != 0, "wrong offset address");
		}
		else
		{
			muFail("Cannot load assets");
		}
	}
	else
	{
		muFail("can't alloc memory");
	}


	MemoryReleaseAll();
}

/*--------------------------------------------------------------------------*/

void testAssetFonts8(void)
{
	ULONG result = MemoryAllocateAll();

	if (RT_OK == result)
	{
		result = AssetsLoad("exe/data.bin");

		if (RT_OK == result)
		{
			ULONG* offset = (ULONG*)AssetsPackedGet(ASSET_FONTS8);

			muAssert(*offset == 0xff61e80b, "wrong content");
		}
		else
		{
			muFail("Cannot load assets");
		}

	}
	else
	{
		muFail("can't alloc memory");
	}


	MemoryReleaseAll();
}

/*--------------------------------------------------------------------------*/

void testAssetCopper(void)
{
	ULONG result = MemoryAllocateAll();

	if (RT_OK == result)
	{
		result = AssetsLoad("exe/data.bin");

		if (RT_OK == result)
		{
			ULONG* offset = (ULONG*)AssetsPackedGet(ASSET_COPPER);

			muAssert(*offset == 0xff8fffc2, "wrong content");
		}
		else
		{
			muFail("Cannot load assets");
		}

	}
	else
	{
		muFail("can't alloc memory");
	}


	MemoryReleaseAll();
}

/*--------------------------------------------------------------------------*/

void testAssetWorld0Colors(void)
{
	ULONG result = loadAssets();

	if (RT_OK == result)
	{
		ULONG *offset = (ULONG *)AssetsPackedGet(ASSET_WORLD0_COLORS);

		muAssert(*offset == 0xffffff35, "wrong content");
	}

	MemoryReleaseAll();
}
