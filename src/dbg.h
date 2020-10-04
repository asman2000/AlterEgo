#ifndef ALTEREGO_DBG_H
#define ALTEREGO_DBG_H

/*--------------------------------------------------------------------------*/

#include "types.h"

#ifdef GAME_DEBUG



void DbgScreenUbyte(ULONG scrOffset, UBYTE n);
void DbgScreenUword(ULONG scrOffset, UWORD n);
#else

#define DbgScreenUbyte(s, n)
#define DbgScreenUword(s, n)

#endif /* GAME_DEBUG */

/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_DBG_H */
