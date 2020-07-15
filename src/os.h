#ifndef ALETEREGO_OS_H
#define ALETEREGO_OS_H

#include "types.h"
/*--------------------------------------------------------------------------*/

void OsStore(void);
void OsRestore(void);

void OsOwnBlitter(void);
void OsDisownBlitter(void);

void OsStoreHardwareRegs(void);
void OsRestoreHardwareRegs(void);


/*--------------------------------------------------------------------------*/

#endif /* ALETEREGO_OS_H */
