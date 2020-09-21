#include "input.h"

#include <hardware/custom.h>

extern struct Custom* custom;

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

void InputJoystickReleaseRedButton(void)
{
	while (InputJoystickRedButton())
	{
		;
	}
}

/*--------------------------------------------------------------------------*/

UBYTE InputJoystickGetState(void)
{
	UWORD joy = custom->joy1dat;
	UBYTE result = 0;

	result += (joy >> 1 ^ joy) & 0x0100 ? JOY_UP : 0;
	result += (joy >> 1 ^ joy) & 0x0001 ? JOY_DOWN : 0;

	result += joy & 0x0200 ? JOY_LEFT : 0;
	result += joy & 0x0002 ? JOY_RIGHT : 0;

	result += InputJoystickRedButton() ? JOY_BUTTON_RED : 0;

	return result;
}

/*--------------------------------------------------------------------------*/
