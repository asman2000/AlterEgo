#include "dbg.h"

#ifdef GAME_DEBUG

#include "smallfont.h"


/*--------------------------------------------------------------------------*/

static const char digits[] =
{ '0', '1', '2', '3', '4', '5', '6', '7',
  '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

static char msgUbyte[2] = { 0, 0 };

static void ubyteToAscii(UBYTE n)
{
	msgUbyte[0] = digits[(n >> 4) & 15];
	msgUbyte[1] = digits[n & 15];
}

void DbgScreenUbyte(ULONG scrOffset, UBYTE n)
{
	ubyteToAscii(n);

	SmallFontDrawString(scrOffset, msgUbyte, 2);
}

static char msgUword[4] = { 0, 0, 0, 0 };

static void uwordToAscii(UWORD n)
{
	msgUword[0] = digits[(n >> 12) & 15];
	msgUword[1] = digits[(n >> 8) & 15];
	msgUword[2] = digits[(n >> 4) & 15];
	msgUword[3] = digits[n & 15];
}

void DbgScreenUword(ULONG scrOffset, UWORD n)
{
	uwordToAscii(n);

	SmallFontDrawString(scrOffset, msgUword, 4);

}


/*--------------------------------------------------------------------------*/
#endif /* GAME_DEBUG */
/*--------------------------------------------------------------------------*/
