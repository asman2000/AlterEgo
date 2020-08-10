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


/*--------------------------------------------------------------------------*/

void ItemInit(void)
{
	current = &items[0];
	ScreenCopyInformation(&screen);
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

}

/*--------------------------------------------------------------------------*/
