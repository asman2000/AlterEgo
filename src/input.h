#ifndef ALTEREGO_INPUT_H
#define ALTEREGO_INPUT_H
/*--------------------------------------------------------------------------*/

#include "types.h"

#define JOY_BUTTON_RED	0x01
#define JOY_UP		0x02
#define JOY_DOWN 	0x04
#define JOY_LEFT 	0x08
#define JOY_RIGHT	0x10

UBYTE InputMouseLeftButton(void);
UBYTE InputJoystickRedButton(void);

UBYTE InputJoystickGetState(void);
/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_INPUT_H */
