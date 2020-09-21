#include "hero.h"

#include "game.h"
#include "input.h"
#include "item.h"
#include "map.h"
#include "sprite.h"

#include "smallfont.h"
//#include "dbg.h"

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
void HeroCollectItems(Match* game, const MemoryDetails* m);
/*--------------------------------------------------------------------------*/

void HeroSetUp(HeroNumber number)
{
	hero = &heroes[0];

	if (HERO_TWO == number)
	{
		hero = &heroes[1];
	}
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

static UBYTE HeroIsFall(const MemoryDetails* m)
{
	UBYTE tile = MapCheck(hero->man.x, hero->man.y + 8, m);
	UBYTE bottom = MapCheck(hero->man.x, hero->man.y + 16, m);

	if (!(bottom & TILE_FLOOR) && !(tile & TILE_LADDER))
	{
		return TRUE;
	}

	return FALSE;
}

/*--------------------------------------------------------------------------*/

static UBYTE HeroCanLeft(const MemoryDetails* m)
{
	if (MapCheck(hero->man.x - 8, hero->man.y + 8, m) & TILE_WALL)
	{
		return FALSE;
	}

	return TRUE;
}

/*--------------------------------------------------------------------------*/

static UBYTE HeroCanRight(const MemoryDetails* m)
{
	if (MapCheck(hero->man.x + 8, hero->man.y + 8, m) & TILE_WALL)
	{
		return FALSE;
	}

	return TRUE;
}

/*--------------------------------------------------------------------------*/

static UBYTE HeroCanUp(const MemoryDetails* m)
{
	UBYTE ladder = MapCheck(hero->man.x, hero->man.y + 8, m);
	UBYTE above = MapCheck(hero->man.x, hero->man.y, m);

	if ((ladder & TILE_LADDER) && (above & TILE_LADDER))
	{
		return TRUE;
	}

	return FALSE;
}

/*--------------------------------------------------------------------------*/

static UBYTE HeroCanDown(const MemoryDetails* m)
{
	UBYTE ladder = MapCheck(hero->man.x, hero->man.y + 8, m);
	UBYTE above = MapCheck(hero->man.x, hero->man.y + 16, m);

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

static UBYTE HeroTryExchange(const MemoryDetails* m)
{
	if (0 == hero->swaps)
	{
		//TODO sfx no swaps
		return FALSE;
	}

	UBYTE tile = MapCheck(hero->ego.x, hero->ego.y + 8, m);

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

UBYTE HeroJoyRight(const MemoryDetails* m)
{
	if ((JOY_RIGHT & hero->input) && (TRUE == HeroCanRight(m)))
	{
		HeroStateSetWalkingRight();
		return TRUE;
	}

	return FALSE;
}

/*--------------------------------------------------------------------------*/

UBYTE HeroJoyLeft(const MemoryDetails* m)
{
	if ((JOY_LEFT & hero->input) && (TRUE == HeroCanLeft(m)))
	{
		HeroStateSetWalkingLeft();
		return TRUE;
	}

	return FALSE;
}

/*--------------------------------------------------------------------------*/

static UBYTE HeroJoyUp(const MemoryDetails* m)
{
	if ((JOY_UP & hero->input) && (TRUE == HeroCanUp(m)))
	{
		HeroStateSetClimbUp();
		return TRUE;
	}

	return FALSE;
}

/*--------------------------------------------------------------------------*/

static UBYTE HeroJoyDown(const MemoryDetails* m)
{
	if (JOY_DOWN & hero->input && (TRUE == HeroCanDown(m)))
	{
		HeroStateSetClimbDown();
		return TRUE;
	}

	return FALSE;
}

/*--------------------------------------------------------------------------*/

static void HeroStateIdle(const MemoryDetails* m)
{
	if (TRUE == HeroIsFall(m))
	{
		HeroStateSetFall();
		return;
	}

	if (TRUE == HeroJoyRight(m))
	{
		return;
	}

	if (TRUE == HeroJoyLeft(m))
	{
		return;
	}

	if (TRUE == HeroJoyUp(m))
	{
		return;
	}

	if (TRUE == HeroJoyDown(m))
	{
		return;
	}

	if ((JOY_BUTTON_RED & hero->input) && (TRUE == HeroTryExchange(m)))
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

static void HeroStateWalk(const MemoryDetails* m)
{
	hero->man.frameOffset = (hero->man.x >> 1) & 3;
	HeroMoveOneStep();

	if (0 != hero->steps)
	{
		return;
	}

	if (TRUE == HeroIsFall(m))
	{
		HeroStateSetFall();
		return;
	}

	if (TRUE == HeroJoyRight(m))
	{
		return;
	}

	if (TRUE == HeroJoyLeft(m))
	{
		return;
	}

	HeroStateSetIdle();
}

/*--------------------------------------------------------------------------*/

static void HeroStateLadder(const MemoryDetails* m)
{
	hero->man.frameOffset = (hero->man.y >> 2) & 1;
	HeroMoveOneStep();

	if (0 != hero->steps)
	{
		return;
	}

	if (TRUE == HeroJoyUp(m))
	{
		return;
	}

	if (TRUE == HeroJoyDown(m))
	{
		return;
	}

	HeroStateSetLadderIdle();
}

/*--------------------------------------------------------------------------*/

void HeroStateLadderIdle(const MemoryDetails* m)
{
	if (TRUE == HeroJoyUp(m))
	{
		return;
	}

	if (TRUE == HeroJoyDown(m))
	{
		return;
	}

	if (TRUE == HeroJoyRight(m))
	{
		return;
	}

	if (TRUE == HeroJoyLeft(m))
	{
		return;
	}

	if ((JOY_BUTTON_RED & hero->input) && (TRUE == HeroTryExchange(m)))
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

void HeroStateFall(const MemoryDetails* m)
{
	hero->man.frameOffset = (hero->man.y >> 2) & 1;
	HeroMoveOneStep();

	if (0 != hero->steps)
	{
		return;
	}

	hero->steps = 8;

	if (FALSE == HeroIsFall(m))
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

static void HeroStateExchange(const MemoryDetails* m)
{
	HeroMoveOneStep();

	if (0 != hero->steps)
	{
		return;
	}

	if ((JOY_BUTTON_RED & hero->input) && (TRUE == HeroTryExchange(m)))
	{
		HeroStateSetExchange();
		return;
	}

	HeroStateSetIdle();

	UBYTE tile = MapCheck(hero->man.x, hero->man.y + 8, m);

	if (tile & TILE_LADDER)
	{
		hero->man.frame = HERO_SPR_LADDER;
		hero->man.frameOffset = 0;
	}

}

/*--------------------------------------------------------------------------*/

void HeroHandleInput(Match* game, const MemoryDetails* m)
{
	hero->input = InputJoystickGetState();

	switch (hero->state)
	{
		case HERO_STATE_IDLE:
			HeroStateIdle(m);
			HeroCollectItems(game, m);
			break;

		case HERO_STATE_WALK:
			HeroStateWalk(m);
			HeroCollectItems(game, m);
			break;

		case HERO_STATE_LADDER:
			HeroStateLadder(m);
			HeroCollectItems(game, m);
			break;

		case HERO_STATE_LADDER_IDLE:
			HeroStateLadderIdle(m);
			break;

		case HERO_STATE_FALL:
			HeroStateFall(m);
			HeroCollectItems(game, m);
			break;

		case HERO_STATE_EXCHANGE:
			HeroStateExchange(m);
			break;
	}

	HeroShow(m);

	{
		UBYTE tile = MapCheck(hero->man.x, hero->man.y + 8, m);
	
		if (TILE_WATER == tile)
		{
			game->state = GAME_STATE_FAIL;
		}
	}

}

/*--------------------------------------------------------------------------*/

void HeroCollectItems(Match* game, const MemoryDetails* m)
{
	UBYTE tile = MapCheck(hero->man.x, hero->man.y + 8, m);

	if (TILE_ITEM1 == tile)
	{
		ItemTake(hero->man.x / 8, hero->man.y + 8, m);
		game->itemsToCollect--;
		MapClearTile(hero->man.x, hero->man.y + 8, m);
	}

	tile = MapCheck(hero->ego.x, hero->ego.y + 8, m);

	if (TILE_ITEM2 == tile)
	{
		ItemTake(hero->ego.x / 8, hero->ego.y + 8, m);
		game->itemsToCollect--;
		MapClearTile(hero->ego.x, hero->ego.y + 8, m);
	}
}

/*--------------------------------------------------------------------------*/

void HeroShow(const MemoryDetails* m)
{
	SpriteDrawHero(&hero->man, m);
	SpriteDrawEgo(&hero->ego, m);
}

/*--------------------------------------------------------------------------*/
