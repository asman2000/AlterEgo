#include "hero.h"

#include "game.h"
#include "input.h"
#include "item.h"
#include "map.h"
#include "sprite.h"

#include "smallfont.h"
#include "dbg.h"

/*--------------------------------------------------------------------------*/

#define HERO_SPR_IDLE		12
#define HERO_SPR_WALK_LEFT	13
#define HERO_SPR_WALK_RIGHT	17
#define HERO_SPR_LADDER		21
#define HERO_SPR_FALL		23
#define HERO_SPR_ALTER		25


#define HERO_IDLE_COUNTER_MAX	50

static struct Hero heroes[2];

static struct Hero* hero;

typedef enum
{
	HERO_STATE_IDLE,
	HERO_STATE_WALK,
	HERO_STATE_LADDER,
	HERO_STATE_LADDER_IDLE,
	HERO_STATE_FALL,
	HERO_STATE_EXCHANGE

} HeroStates;

void HeroStateSetLadderIdle(void);
void HeroCollectItems(Match* game);
/*--------------------------------------------------------------------------*/

void HeroSetUp(HeroNumber number)
{
	hero = &heroes[0];

	if (HERO_TWO == number)
	{
		hero = &heroes[1];
	}

	//debug
	SmallFontInit();
}

/*--------------------------------------------------------------------------*/

void HeroInit(void)
{
	hero->man.x = 0;
	hero->man.y = 0;
	hero->man.dx = 0;
	hero->man.dy = 0;
	
	//TODO
	hero->man.src = 0;	//spriteGfxData + 12 * 16 * 4;
	hero->man.dst = 0;	//spriteHero;
	hero->man.frame = HERO_SPR_IDLE;
	hero->man.frameOffset = 0;

	hero->ego.x = 8;
	hero->ego.y = 32;
	hero->ego.frame = HERO_SPR_ALTER;
	hero->ego.frameOffset = 0;

	hero->steps = 0;
	hero->state = HERO_STATE_IDLE;
}

/*--------------------------------------------------------------------------*/

static void HeroSyncWithEgo(void)
{
	if (!hero->syncType)
	{
		hero->ego.x = 312 - hero->man.x;
		hero->ego.y = hero->man.y;
	}
	else
	{
		hero->ego.x = hero->man.x;
		hero->ego.y = 224 - hero->man.y;
	}
}

/*--------------------------------------------------------------------------*/

void HeroSetPosition(UWORD x, UWORD y)
{
	hero->man.x = x;
	hero->man.y = y;

	HeroSyncWithEgo();
}

/*--------------------------------------------------------------------------*/

void HeroSetSyncType(UBYTE sync)
{
	hero->syncType = sync;
}

/*--------------------------------------------------------------------------*/

void HeroSetSwaps(UBYTE swaps)
{
	hero->swaps = swaps;
}

/*--------------------------------------------------------------------------*/

static void HeroStateSetIdle(void)
{
	hero->state = HERO_STATE_IDLE;
	hero->steps = HERO_IDLE_COUNTER_MAX;
	hero->man.frameOffset = 0;
}

/*--------------------------------------------------------------------------*/

static void HeroStateSetWalkingLeft(void)
{
	hero->man.dx = 0xffff;
	hero->man.dy = 0;
	hero->state = HERO_STATE_WALK;
	hero->steps = 8;
	hero->man.frame = HERO_SPR_WALK_LEFT;
	hero->man.frameOffset = 0;
}

/*--------------------------------------------------------------------------*/

static void HeroStateSetWalkingRight(void)
{
	hero->man.dx = 0x0001;
	hero->man.dy = 0;
	hero->state = HERO_STATE_WALK;
	hero->steps = 8;
	hero->man.frame = HERO_SPR_WALK_RIGHT;
	hero->man.frameOffset = 0;
}

/*--------------------------------------------------------------------------*/

static void HeroStateSetClimbUp(void)
{
	hero->man.dx = 0;
	hero->man.dy = 0xffff;
	hero->state = HERO_STATE_LADDER;
	hero->steps = 8;
	hero->man.frame = HERO_SPR_LADDER;
	hero->man.frameOffset = 0;
}

/*--------------------------------------------------------------------------*/

static void HeroStateSetClimbDown(void)
{
	hero->man.dx = 0;
	hero->man.dy = 0x0001;
	hero->man.frame = HERO_SPR_LADDER;
	hero->man.frameOffset = 0;
	hero->state = HERO_STATE_LADDER;
	hero->steps = 8;
}

/*--------------------------------------------------------------------------*/

static void HeroStateSetFall(void)
{
	hero->state = HERO_STATE_FALL;
	hero->steps = 8;
	hero->man.dx = 0;
	hero->man.dy = 0x0001;
	hero->man.frame = HERO_SPR_FALL;
	hero->man.frameOffset = 0;
}

/*--------------------------------------------------------------------------*/

static void HeroStateSetExchange(void)
{
	hero->state = HERO_STATE_EXCHANGE;
	hero->man.frame = HERO_SPR_IDLE;
	hero->man.frameOffset = 0;

	hero->man.dx = 0;
	hero->man.dy = 0;
	hero->ego.dx = 0;
	hero->ego.dy = 0;

	if (!hero->syncType)
	{
		UWORD steps = hero->ego.x - hero->man.x;
		UWORD dx = 4;

		if (hero->man.x > hero->ego.x)
		{
			steps = -steps;
			dx = -dx;
		}
		
		hero->steps = steps >> 2;
		hero->man.dx = dx;
		hero->ego.dx = !dx;
	}
	else
	{
		UWORD steps = hero->ego.y - hero->man.y;
		UWORD dy = 4;

		if (hero->man.y > hero->ego.y)
		{
			steps = -steps;
			dy = -dy;
		}
		
		hero->steps = steps >> 2;
		hero->man.dy = dy;
		hero->ego.dy = !dy;

	}

}

/*--------------------------------------------------------------------------*/

static UBYTE HeroIsFall(void)
{
	UBYTE tile = MapCheck(hero->man.x, hero->man.y + 8);
	UBYTE bottom = MapCheck(hero->man.x, hero->man.y + 16);

	if (!(bottom & TILE_FLOOR) && !(tile & TILE_LADDER))
	{
		return TRUE;
	}

	return FALSE;
}

/*--------------------------------------------------------------------------*/

static UBYTE HeroCanLeft(void)
{
	if (MapCheck(hero->man.x - 8, hero->man.y + 8) & TILE_WALL)
	{
		return FALSE;
	}

	return TRUE;
}

/*--------------------------------------------------------------------------*/

static UBYTE HeroCanRight(void)
{
	if (MapCheck(hero->man.x + 8, hero->man.y + 8) & TILE_WALL)
	{
		return FALSE;
	}

	return TRUE;
}

/*--------------------------------------------------------------------------*/

static UBYTE HeroCanUp(void)
{
	UBYTE ladder = MapCheck(hero->man.x, hero->man.y + 8);
	UBYTE above = MapCheck(hero->man.x, hero->man.y);

	if ((ladder & TILE_LADDER) && (above & TILE_LADDER))
	{
		return TRUE;
	}

	return FALSE;
}

/*--------------------------------------------------------------------------*/

static UBYTE HeroCanDown(void)
{
	UBYTE ladder = MapCheck(hero->man.x, hero->man.y + 8);
	UBYTE above = MapCheck(hero->man.x, hero->man.y + 16);

	if ((ladder & TILE_LADDER) || (above & TILE_LADDER))
	{
		if (!(above & (TILE_WALL | TILE_BRIDGE)))
		{
			return TRUE;
		}
	}

	return FALSE;
}

/*--------------------------------------------------------------------------*/

static UBYTE HeroTryExchange(void)
{
	if (0 == hero->swaps)
	{
		//TODO sfx no swaps
		return FALSE;
	}

	UBYTE tile = MapCheck(hero->ego.x, hero->ego.y + 8);

	if (tile & TILE_WALL)
	{
		//TODO sfx can't exchange
		return FALSE;
	}

	//TODO sfx exchange
	//TODO hud or sprite update

	//hero->swaps--;

	return TRUE;
}

/*--------------------------------------------------------------------------*/

static void HeroMoveOneStep(void)
{
	hero->man.x += hero->man.dx;
	hero->man.y += hero->man.dy;
	hero->steps--;

	HeroSyncWithEgo();
}

/*--------------------------------------------------------------------------*/

UBYTE HeroJoyRight(void)
{
	if ((JOY_RIGHT & hero->input) && (TRUE == HeroCanRight()))
	{
		HeroStateSetWalkingRight();
		return TRUE;
	}

	return FALSE;
}

/*--------------------------------------------------------------------------*/

UBYTE HeroJoyLeft(void)
{
	if ((JOY_LEFT & hero->input) && (TRUE == HeroCanLeft()))
	{
		HeroStateSetWalkingLeft();
		return TRUE;
	}

	return FALSE;
}

/*--------------------------------------------------------------------------*/

static UBYTE HeroJoyUp(void)
{
	if ((JOY_UP & hero->input) && (TRUE == HeroCanUp()))
	{
		HeroStateSetClimbUp();
		return TRUE;
	}

	return FALSE;
}

/*--------------------------------------------------------------------------*/

static UBYTE HeroJoyDown(void)
{
	if (JOY_DOWN & hero->input && (TRUE == HeroCanDown()))
	{
		HeroStateSetClimbDown();
		return TRUE;
	}

	return FALSE;
}

/*--------------------------------------------------------------------------*/

static void HeroStateIdle()
{
	if (TRUE == HeroIsFall())
	{
		HeroStateSetFall();
		return;
	}

	if (TRUE == HeroJoyRight())
	{
		return;
	}

	if (TRUE == HeroJoyLeft())
	{
		return;
	}

	if (TRUE == HeroJoyUp())
	{
		return;
	}

	if (TRUE == HeroJoyDown())
	{
		return;
	}

	if ((JOY_BUTTON_RED & hero->input) && (TRUE == HeroTryExchange()))
	{
		HeroStateSetExchange();
		return;
	}
	

	if (0 == hero->steps)
	{
		hero->man.frame = HERO_SPR_IDLE;
	}
	else
	{
		hero->steps--;
	}

}

/*--------------------------------------------------------------------------*/

static void HeroStateWalk(void)
{
	hero->man.frameOffset = (hero->man.x >> 1) & 3;
	HeroMoveOneStep();

	if (0 != hero->steps)
	{
		return;
	}

	if (TRUE == HeroIsFall())
	{
		HeroStateSetFall();
		return;
	}

	if (TRUE == HeroJoyRight())
	{
		return;
	}

	if (TRUE == HeroJoyLeft())
	{
		return;
	}

	HeroStateSetIdle();
}

/*--------------------------------------------------------------------------*/

static void HeroStateLadder()
{
	hero->man.frameOffset = (hero->man.y >> 2) & 1;
	HeroMoveOneStep();

	if (0 != hero->steps)
	{
		return;
	}

	if (TRUE == HeroJoyUp())
	{
		return;
	}

	if (TRUE == HeroJoyDown())
	{
		return;
	}

	HeroStateSetLadderIdle();
}

/*--------------------------------------------------------------------------*/

void HeroStateLadderIdle()
{
	if (TRUE == HeroJoyUp())
	{
		return;
	}

	if (TRUE == HeroJoyDown())
	{
		return;
	}

	if (TRUE == HeroJoyRight())
	{
		return;
	}

	if (TRUE == HeroJoyLeft())
	{
		return;
	}

	if ((JOY_BUTTON_RED & hero->input) && (TRUE == HeroTryExchange()))
	{
		HeroStateSetExchange();
		return;
	}

}

/*--------------------------------------------------------------------------*/

void HeroStateSetLadderIdle(void)
{
	hero->man.dx = 0;
	hero->man.dy = 0;
	hero->man.frame = HERO_SPR_LADDER;
	hero->man.frameOffset = 0;
	hero->state = HERO_STATE_LADDER_IDLE;
	hero->steps = 0;

}

/*--------------------------------------------------------------------------*/

void HeroStateFall(void)
{
	hero->man.frameOffset = (hero->man.y >> 2) & 1;
	HeroMoveOneStep();

	if (0 != hero->steps)
	{
		return;
	}

	hero->steps = 8;

	if (FALSE == HeroIsFall())
	{
		HeroStateSetIdle();
		hero->steps = 8;
	}

	if (JOY_BUTTON_RED & hero->input)
	{
		HeroStateSetExchange();
	}
}

/*--------------------------------------------------------------------------*/

static void HeroStateExchange()
{
	HeroMoveOneStep();

	if (0 != hero->steps)
	{
		return;
	}

	if ((JOY_BUTTON_RED & hero->input) && (TRUE == HeroTryExchange()))
	{
		HeroStateSetExchange();
		return;
	}

	HeroStateSetIdle();

	UBYTE tile = MapCheck(hero->man.x, hero->man.y + 8);

	if (tile & TILE_LADDER)
	{
		hero->man.frame = HERO_SPR_LADDER;
		hero->man.frameOffset = 0;
	}

}

/*--------------------------------------------------------------------------*/

void HeroHandleInput(Match* game)
{
	hero->input = InputJoystickGetState();

	switch (hero->state)
	{
		case HERO_STATE_IDLE:
			HeroStateIdle();
			HeroCollectItems(game);
			break;

		case HERO_STATE_WALK:
			HeroStateWalk();
			HeroCollectItems(game);
			break;

		case HERO_STATE_LADDER:
			HeroStateLadder();
			HeroCollectItems(game);
			break;

		case HERO_STATE_LADDER_IDLE:
			HeroStateLadderIdle();
			break;

		case HERO_STATE_FALL:
			HeroStateFall();
			HeroCollectItems(game);
			break;

		case HERO_STATE_EXCHANGE:
			HeroStateExchange();
			break;
	}

	HeroShow();

	{
		UBYTE tile = MapCheck(hero->man.x, hero->man.y + 8);
	
		if (TILE_WATER == tile)
		{
			game->state = GAME_STATE_FAIL;
		}
	}

}

/*--------------------------------------------------------------------------*/

void HeroCollectItems(Match* game)
{
	UBYTE tile = MapCheck(hero->man.x, hero->man.y + 8);

	if (TILE_ITEM1 == tile)
	{
		ItemTake(hero->man.x / 8, hero->man.y + 8);
		game->itemsToCollect--;
		MapClearTile(hero->man.x, hero->man.y + 8);
	}

	tile = MapCheck(hero->ego.x, hero->ego.y + 8);

	if (TILE_ITEM2 == tile)
	{
		ItemTake(hero->ego.x / 8, hero->ego.y + 8);
		game->itemsToCollect--;
		MapClearTile(hero->ego.x, hero->ego.y + 8);
	}
}

/*--------------------------------------------------------------------------*/

void HeroShow(void)
{
	SpriteDrawHero(&hero->man);
	SpriteDrawEgo(&hero->ego);
}

/*--------------------------------------------------------------------------*/
