#ifndef ALTEREGO_DBG_H
#define ALTEREGO_DBG_H

/*--------------------------------------------------------------------------*/

#include "types.h"

#ifdef GAME_DEBUG



void DbgScreenUbyte(const MemoryDetails *m, ULONG scrOffset, UBYTE n);
void DbgScreenUword(const MemoryDetails *m, ULONG scrOffset, UWORD n);
#else

#define DbgScreenUbyte(m, s, n)
#define DbgScreenUword(m, s, n)

#endif /* GAME_DEBUG */

/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_DBG_H */
