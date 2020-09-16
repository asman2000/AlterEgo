#ifndef ALTEREGO_COPPER_H
#define ALTEREGO_COPPER_H

#include "types.h"

/*--------------------------------------------------------------------------*/


void CopperStart(ULONG copperAddress);

//void CopperUpdateScreen(ULONG copperAddress, ULONG screenAddress, UWORD bpl, UWORD brow);
void CopperUpdateAddress(ULONG copperAddress, ULONG address);
/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_COPPER_H */
