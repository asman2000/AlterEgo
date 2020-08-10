#include "item.h"

#include "gfxtile.h"
#include "map.h"
#include "screen.h"


typedef struct
{
	ULONG scrOffset;
	UBYTE tileNumber;
	UBYTE adjust;

} AnimItem;

static AnimItem items[21];

static AnimItem* current;

static ScreenInfo screen;

static UBYTE counter;
/*--------------------------------------------------------------------------*/

void ItemInit(void)
{
	current = &items[0];
	ScreenCopyInformation(&screen);
	counter = 0;
}


/*--------------------------------------------------------------------------*/

void ItemAdd(ULONG scrOffset, UBYTE tileNumber)
{
	current->scrOffset = scrOffset;
	current->tileNumber = tileNumber;
	current++;
}

/*--------------------------------------------------------------------------*/

void ItemDraw(void)
{
	ItemAnimate();

	AnimItem* item = &items[0];

	while (item != current)
	{
		GfxTileDrawOne(item->scrOffset, item->tileNumber);

		item++;
	}
}

/*--------------------------------------------------------------------------*/

void ItemTake(UWORD x, UWORD y)
{
	const ULONG scrOffset = x + y * screen.bpl * screen.brow;

	AnimItem* item = &items[0];

	while (item != current)
	{
		if (item->scrOffset == scrOffset)
		{
			item->tileNumber = TILE_EMPTY;
			break;
		}

		item++;
	}
}

/*--------------------------------------------------------------------------*/

void ItemAnimate(void)
{
	UBYTE j = ((counter++ >> 1) & 7);

	AnimItem* item = &items[0];

	while (item != current)
	{
		if (TILE_EMPTY != item->tileNumber)
		{
			item->tileNumber =(item->tileNumber & ~7) | j;
		}

		j = (j + 1) & 7;

		item++;
	}
}

/*--------------------------------------------------------------------------*/
