#include "input.h"

/*--------------------------------------------------------------------------*/

#define CIAADDR (volatile UBYTE*)(0xbfe001)

UBYTE InputMouseLeftButton(void)
{
	return (!(*CIAADDR & 64));
}

/*--------------------------------------------------------------------------*/

UBYTE InputJoystickRedButton(void)
{
	return (!(*CIAADDR & 128));
}

/*--------------------------------------------------------------------------*/
