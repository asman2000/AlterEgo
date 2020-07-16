#include "os.h"


#include <proto/exec.h>
#include <proto/graphics.h>
#include <graphics/gfxbase.h>

#include <hardware/custom.h>

struct Custom* custom;
extern struct GfxBase* GfxBase;

static struct View* oldView;
static UWORD osIntena;
static UWORD osDma;

static void OsViewLoad(struct View* view);

void OsOwnBlitter(void);
void OsDisownBlitter(void);

void OsStoreHardwareRegs(void);
void OsRestoreHardwareRegs(void);


/*--------------------------------------------------------------------------*/

static void StopDmaAndInts(void)
{
	custom->dmacon = 0x7fff;
	custom->intena = 0x7fff;
	custom->intreq = 0x7fff;
}

/*--------------------------------------------------------------------------*/

void OsStore(void)
{
	//stop multitasking
	Forbid();

	//save old view
	oldView = GfxBase->ActiView;

	OsOwnBlitter();

	//reset display
	OsViewLoad(0);

	custom = ((struct Custom*)0xdff000);
	OsStoreHardwareRegs();

	StopDmaAndInts();
}

/*--------------------------------------------------------------------------*/

void OsRestore(void)
{
	StopDmaAndInts();

	OsRestoreHardwareRegs();

	OsDisownBlitter();

	//restore display
	OsViewLoad(oldView);

	//restore system clist
	custom->cop1lc = (ULONG)GfxBase->copinit;

	//multitasking on
	Permit();
}

/*----------------------------------------------------------------------------*/

static void OsViewLoad(struct View* view)
{
	LoadView(view);
	WaitTOF();
	WaitTOF();
}

/*----------------------------------------------------------------------------*/

void OsOwnBlitter(void)
{
	OwnBlitter();
	WaitBlit();
}

/*----------------------------------------------------------------------------*/

void OsDisownBlitter(void)
{
	WaitBlit();
	DisownBlitter();
}

/*--------------------------------------------------------------------------*/

void OsStoreHardwareRegs(void)
{
	osIntena = custom->intenar;
	osDma = custom->dmaconr;
}

/*--------------------------------------------------------------------------*/

void OsRestoreHardwareRegs(void)
{
	custom->intena = osIntena | 0xC000;
	custom->dmacon = osDma | 0x8000;
}

/*--------------------------------------------------------------------------*/
