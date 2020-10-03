#include "alterego.h"

#include "assets.h"
#include "credits.h"
#include "game.h"
#include "error.h"
#include "memory.h"
#include "music.h"
#include "os.h"
#include "screen.h"
#include "sfx.h"

#include "input.h"

/*--------------------------------------------------------------------------*/

void AETest(void)
{
	if (InputMouseLeftButton())
	{
		mem->mainState.exitToOs = TRUE;
	}
}

void AlterEgo(void)
{

	ULONG result = MemoryAllocateAll();

	if (RT_OK == result)
	{
		MemoryInitialize();

		mem->mainState.exitToOs = FALSE;
		mem->mainState.run = AETest;

		result = AssetsLoad("data.bin");

		if (RT_OK == result)
		{
			OsStore();
			// ScreenInit(state.memory);
			// MusicSetUp();
			// SfxInit(state.memory);
			// AssetsSfx(state.memory);

			while (TRUE)
			{
				mem->mainState.run();

				if (TRUE == mem->mainState.exitToOs)
				{
					break;
				}
			}

			//MusicDestroy();
			OsRestore();
		}
	}

	ErrorShow(result);

	MemoryReleaseAll();
}

/*--------------------------------------------------------------------------*/
