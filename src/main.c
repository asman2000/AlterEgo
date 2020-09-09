#include "alterego.h"
#include "libs.h"

/*--------------------------------------------------------------------------*/

int main(void)
{
	ULONG result = LibsOpen();

	if (RT_OK == result)
	{
		AlterEgo();
	}

	LibsClose();

	return 0;
}

/*--------------------------------------------------------------------------*/
