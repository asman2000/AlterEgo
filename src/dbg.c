#include "dbg.h"

#include "smallfont.h"

#ifdef GAME_DEBUG


/*--------------------------------------------------------------------------*/

static char msgDec[10] = {0, 0, 0, 0, 0};

static void ubyteToDec(UBYTE n)
{
	msgDec[0] = 0;

	while (n >= 100)
	{
		n -= 100;
		msgDec[0]++;
	}

	msgDec[1] = 0;

	while (n >= 10)
	{
		n -= 10;
		msgDec[1]++;
	}

	msgDec[2] = n;
}


void DbgUbyte(ULONG scrOffset, UBYTE n)
{
	ubyteToDec(n);

	SmallFontDrawDigit(scrOffset, '0' + msgDec[0]);
	SmallFontDrawDigit(scrOffset + 1, '0' + msgDec[1]);
	SmallFontDrawDigit(scrOffset + 2, '0' + msgDec[2]);
}


static void uwordToDec(UWORD n)
{
	msgDec[0] = 0;

	while (n >= 10000)
	{
		n -= 10000;
		msgDec[0]++;
	}

	msgDec[1] = 0;

	while (n >= 1000)
	{
		n -= 1000;
		msgDec[1]++;
	}

	msgDec[2] = 0;

	while (n >= 100)
	{
		n -= 100;
		msgDec[2]++;
	}

	msgDec[3] = 0;

	while (n >= 10)
	{
		n -= 10;
		msgDec[3]++;
	}

	msgDec[4] = n;

}

void DbgUword(ULONG scrOffset, UWORD n)
{
	uwordToDec(n);

	SmallFontDrawDigit(scrOffset, '0' + msgDec[0]);
	SmallFontDrawDigit(scrOffset + 1, '0' + msgDec[1]);
	SmallFontDrawDigit(scrOffset + 2, '0' + msgDec[2]);
	SmallFontDrawDigit(scrOffset + 3, '0' + msgDec[3]);
	SmallFontDrawDigit(scrOffset + 4, '0' + msgDec[4]);
}

static void ulongToDec(ULONG n)
{
	ULONG tab[] = {
		1000000000,
		100000000,
		10000000,
		1000000,
		100000,
		10000,
		1000,
		100,
		10,
	};

	int index = 0;

	for (int i = 0; i < ARRAY_SIZE(tab); ++i)
	{
		msgDec[index] = 0;

		while (n >= tab[i])
		{
			n -= tab[i];
			msgDec[index]++;
		}

		index++;
	}

	msgDec[index] = n;
}

void DbgUlong(ULONG scrOffset, ULONG n)
{
	ulongToDec(n);

	SmallFontDrawDigit(scrOffset, '0' + msgDec[0]);
	SmallFontDrawDigit(scrOffset + 1, '0' + msgDec[1]);
	SmallFontDrawDigit(scrOffset + 2, '0' + msgDec[2]);
	SmallFontDrawDigit(scrOffset + 3, '0' + msgDec[3]);
	SmallFontDrawDigit(scrOffset + 4, '0' + msgDec[4]);
	SmallFontDrawDigit(scrOffset + 5, '0' + msgDec[5]);
	SmallFontDrawDigit(scrOffset + 6, '0' + msgDec[6]);
	SmallFontDrawDigit(scrOffset + 7, '0' + msgDec[7]);
	SmallFontDrawDigit(scrOffset + 8, '0' + msgDec[8]);
	SmallFontDrawDigit(scrOffset + 9, '0' + msgDec[9]);
}

/*--------------------------------------------------------------------------*/
#endif /* GAME_DEBUG */
/*--------------------------------------------------------------------------*/
