#ifndef ALTEREGO_MUSIC_H
#define ALTEREGO_MUSIC_H
/*--------------------------------------------------------------------------*/

#include "types.h"

ULONG MusicInit(void);
void MusicKill(void);

void MusicSetUp(void);
void MusicDestroy(void);

void MusicStart(void);
void MusicStop(void);
/*--------------------------------------------------------------------------*/
#endif /* ALTEREGO_MUSIC_H */
