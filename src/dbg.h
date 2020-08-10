#ifndef ALTEREGO_DBG_H
#define ALTEREGO_DBG_H

/*--------------------------------------------------------------------------*/

#include "types.h"

#ifdef GAME_DEBUG

void DbgUbyte(ULONG scrOffset, UBYTE n);
void DbgUword(ULONG scrOffset, UWORD n);
void DbgUlong(ULONG scrOffset, ULONG n);
#else

void DbgUbyte(ULONG scrOffset, UBYTE n )
void DbgUword(ULONG scrOffset, UWORD n)
void DbgUlong(ULONG scrOffset, ULONG n)

#endif /* GAME_DEBUG */


/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_DBG_H */
