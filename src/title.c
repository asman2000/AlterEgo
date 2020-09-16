#include "title.h"

#include "input.h"

/*--------------------------------------------------------------------------*/

void Title(struct MainState* state)
{
	while (TRUE)
	{
		if (InputMouseLeftButton())
		{
			state->exitToOs = TRUE;
			break;
		}
	}
}
/*--------------------------------------------------------------------------*/
