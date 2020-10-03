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


//struct MainState state;
/*--------------------------------------------------------------------------*/

void AlterEgo(void)
{

	ULONG result = MemoryAllocateAll();

	if (RT_OK == result)
	{
		MemoryInitialize();

		mem->mainState.exitToOs = FALSE;
		mem->mainState.run = Credits;

		//state.exitToOs = FALSE;
		//state.memory = MemoryGetDetails();
		//state.run = Credits;

		//result = AssetsLoad(state.memory, "data.bin");

		if (RT_OK == result)
		{
			OsStore();
			// ScreenInit(state.memory);
			// MusicSetUp();
			// SfxInit(state.memory);
			// AssetsSfx(state.memory);

			while (TRUE)
			{
				mem->mainState.run(&mem->mainState);

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
