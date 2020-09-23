#include "music.h"

#include "input.h"
#include "memory.h"

extern void mt_install_cia(__reg("a6") ULONG cstm, __reg("a0") ULONG autoVecBase, __reg("d0") UBYTE palFlag);
extern void mt_remove_cia(__reg("a6") ULONG cstm);

extern void mt_init(__reg("a6") ULONG cstm, __reg("a0") ULONG trackerModule, __reg("a1") ULONG Samples, __reg("d0") ULONG InitialSongPos);
extern void mt_end(__reg("a6") ULONG cstm);
extern void mt_mastervol(__reg("d0") ULONG MasterVolume);


extern UBYTE mt_Enable;

/*----------------------------------------------------------------------------*/

void MusicSetUp(void)
{
	mt_install_cia(0xdff000, 0, 1);
}

/*----------------------------------------------------------------------------*/

void MusicDestroy(void)
{
	MusicStop();
	mt_remove_cia(0xdff000);
}

/*----------------------------------------------------------------------------*/

void MusicStart(const MemoryDetails* m)
{
	mt_init(0xdff000, m->music, 0, 0);
	mt_Enable = 1;
	mt_mastervol(64);
}

/*----------------------------------------------------------------------------*/

void MusicStop(void)
{
	mt_Enable = 0;
	mt_end(0xdff000);
}

/*----------------------------------------------------------------------------*/
