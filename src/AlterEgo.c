#include "alterego.h"

#include "assets.h"
#include "credits.h"
#include "game.h"
#include "error.h"
#include "memory.h"
#include "music.h"
#include "os.h"
#include "screen.h"


struct MainState state;
/*--------------------------------------------------------------------------*/

void AlterEgo(void)
{

	ULONG result = MemoryAllocateAll();

	if (RT_OK == result)
	{
		state.exitToOs = FALSE;
		state.memory = MemoryGetDetails();
		state.run = Credits;

		result = AssetsLoad(state.memory, "data.bin");

		if (RT_OK == result)
		{
			OsStore();
			ScreenInit(state.memory);
			MusicSetUp();


			while (TRUE)
			{
				state.run(&state);

				if (TRUE == state.exitToOs)
				{
					break;
				}
			}

			MusicDestroy();
			OsRestore();
		}
	}

	ErrorShow(result);

	MemoryReleaseAll();
}

/*--------------------------------------------------------------------------*/
