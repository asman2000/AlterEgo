#include "sfx.h"

#include "memory.h"

/*--------------------------------------------------------------------------*/

	//"00-start.sfx"
	//"01-menu.sfx"
	//"02-exchange.sfx"
	//"03-item1.sfx"
	//"04-item2.sfx"
	//"05-hit.sfx"
	//"06-falling.sfx"
	//"07-drop.sfx"
	//"08-no-exchange.sfx"
	//"09-out-of-exchanges.sfx"
	//"10-bridge.sfx"
	//"11-walk1.sfx"
	//"12-walk2.sfx"
	//"13-ladder.sfx"
	//"14-level-clear.sfx"

UWORD sfxSizes[15] = 
{
	6980,
	4143,
	14162,
	3322,
	1465,
	379,
	7500,
	1934,
	2977,
	6988,
	5000,
	2221,
	505,
	2659,
	7500
};

/*---------------------------------------------------------------------------*/

typedef struct
{
	APTR address;	// sample start address (CHIP) 
	UWORD length;	// sample length in words
	UWORD period;	// hardware replay period for sample
	UWORD volume;	// volume 0..64, is unaffected by the song's master volume
	BYTE channel;   // 0..3 selected replay channel, -1 selects best channel
	UBYTE priority; // unsigned priority, must be non-zero
} Sfx;

Sfx Samples[15];

extern void mt_playfx(__reg("a6") ULONG custom, __reg("a0") ULONG Sfx);

/*---------------------------------------------------------------------------*/

void SfxInit(const MemoryDetails* m)
{
	ULONG adr = m->sfx;

	for (int i = 0; i < 15; ++i)
	{
		UWORD size = sfxSizes[i];

		Samples[i].address = (APTR)adr;
		adr += size;

		Samples[i].length = size / 2;
		Samples[i].period = 324;
		Samples[i].volume = 64;
		Samples[i].channel = -1;
		Samples[i].priority = 1;
	}
}

/*---------------------------------------------------------------------------*/

void SfxPlay(UWORD number)
{
	mt_playfx(0xdff000, (ULONG) &Samples[number]);
}

/*---------------------------------------------------------------------------*/
