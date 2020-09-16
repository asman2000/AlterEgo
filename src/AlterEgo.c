#include "alterego.h"

#include "assets.h"
#include "credits.h"
#include "memory.h"
#include "os.h"


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

			while (TRUE)
			{
				state.run(&state);

				if (TRUE == state.exitToOs)
				{
					break;
				}
			}

			OsRestore();
		}
	}

	MemoryReleaseAll();
}

/*--------------------------------------------------------------------------*/
