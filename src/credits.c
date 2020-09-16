#include "credits.h"

#include "assets.h"
#include "colors.h"
#include "input.h"
#include "memory.h"
#include "screen.h"
#include "sizes.h"
#include "smallfont.h"



static UWORD* palette;

static ULONG texts;

static void CreditsDrawTexts(void);

/*--------------------------------------------------------------------------*/

void CreditsMemoryInit(void)
{
	// screen
	// copper
	// sprites (at least fake one)

	// palette
	// texts
	// small fonts
}


/*--------------------------------------------------------------------------*/
static void CreditsInit(void)
{
	MemoryAnyReset();

	palette = (UWORD*) MemoryAnyGet(CREDITS_COLORS_SIZE);
	AssetsGet((ULONG)palette, ASSET_CREDITS_COLORS);
	
	texts = MemoryAnyGet(CREDITS_TEXTS_SIZE);
	AssetsGet(texts, ASSET_CREDITS_TXT);

	SmallFontInit();

	
	ColorsSetAllToBlack();
	ScreenClear();

	CreditsDrawTexts();
	ScreenOn();
}

/*--------------------------------------------------------------------------*/
static void CreditsDrawTexts(void)
{
	ULONG scr = 0;
	UBYTE* txt = (UBYTE*)texts;

	while (TRUE)
	{
		UBYTE size;
		UWORD offset = *((UWORD*)txt);

		if (0xffff == offset)
		{
			break;
		}

		txt +=2;
		size = *txt++;

		SmallFontDrawString(scr + offset, txt, size);
		txt += size;
	}
}

/*--------------------------------------------------------------------------*/

static void CreditsMain(struct State* gameState)
{
	UWORD wait = 300;

	ColorsFadeIn(palette, 16);

	do
	{
		ScreenWaitForVerticallBlank();

		if (InputJoystickRedButton())
		{
			break;
		}

		

		if (InputMouseLeftButton())
		{
			gameState->exitToOs = TRUE;
			break;
		}


	} while (--wait, 0 != wait);

	ColorsFadeOut(palette, 16);
	ScreenOff();

	//gameState->run = Title;
}

/*--------------------------------------------------------------------------*/

void Credits(struct State* gameState)
{
	CreditsInit();
	CreditsMain(gameState);
}

/*--------------------------------------------------------------------------*/
