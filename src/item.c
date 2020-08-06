#include "item.h"

#include "gfxtile.h"

typedef struct
{
	ULONG scrOffset;
	UBYTE tileNumber;
	UBYTE adjust;

} AnimItem;

static AnimItem items[21];

static AnimItem* current;

/*--------------------------------------------------------------------------*/

void ItemInit(void)
{
	current = &items[0];
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