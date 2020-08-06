#include "hero.h"

#include "input.h"
#include "map.h"
#include "sprite.h"


/*--------------------------------------------------------------------------*/

#define HERO_SPR_IDLE		12
#define HERO_SPR_WALK_LEFT	13
#define HERO_SPR_WALK_RIGHT	17
#define HERO_SPR_LADDER		21
#define HERO_SPR_FALL		23
#define HERO_SPR_ALTER		25


#define DIR_NONE			0
#define DIR_LEFT			1
#define DIR_RIGHT			2
#define DIR_UP				3
#define DIR_DOWN			4

#define HERO_IDLE_COUNTER_MAX	50

static struct Hero heroes[2];

static struct Hero* hero;

typedef enum
{
	HERO_STATE_IDLE,
	HERO_STATE_CLIMB_UP,
	HERO_STATE_CLIMB_DOWN,
	HERO_STATE_WALK_RIGHT,
	HERO_STATE_WALK_LEFT,
	HERO_STATE_FALL,
	HERO_STATE_EXCHANGE

} HeroStates;

// struct HeroState;
// typedef void (*HeroStateFunc)(struct HeroState*);

// struct HeroState
// {
// 	HeroStateFunc next;

// 	UBYTE joy;
// };

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

	hero->dir = DIR_NONE;
	hero->man.x = 0;
	hero->man.y = 0;
	hero->man.dx = 0;
	hero->man.dy = 0;
	
	//TODO
	hero->man.src = 0;	// spriteGfxData + 12 * 16 * 4;
	hero->man.dst = 0;	//spriteHero;

	hero->steps = 0;
	hero->man.frame = HERO_SPR_IDLE;
	hero->state = HERO_STATE_IDLE;
	hero->idleCounter = 0;


	hero->ego.x = 8;
	hero->ego.y = 32;
	hero->ego.frame = HERO_SPR_ALTER;
	hero->ego.frameOffset = 0;
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
	hero->dir = DIR_NONE;
	hero->idleCounter = HERO_IDLE_COUNTER_MAX;
	hero->man.frameOffset = 0;
}

/*--------------------------------------------------------------------------*/

static void HeroStateSetWalkingLeft(void)
{
	hero->dir = DIR_LEFT;
	hero->man.dx = 0xffff;
	hero->man.dy = 0;
	hero->state = HERO_STATE_WALK_LEFT;
	hero->steps = 8;
	hero->man.frame = HERO_SPR_WALK_LEFT;
	hero->man.frameOffset = 0;
}

/*--------------------------------------------------------------------------*/

static void HeroStateSetWalkingRight(void)
{
	hero->dir = DIR_RIGHT;
	hero->man.dx = 0x0001;
	hero->man.dy = 0;
	hero->state = HERO_STATE_WALK_RIGHT;
	hero->steps = 8;
	hero->man.frame = HERO_SPR_WALK_RIGHT;
	hero->man.frameOffset = 0;
}

/*--------------------------------------------------------------------------*/

static void HeroStateSetClimbUp(void)
{
	hero->dir = DIR_UP;
	hero->man.dx = 0;
	hero->man.dy = 0xffff;
	hero->state = HERO_STATE_CLIMB_UP;
	hero->steps = 8;
	hero->man.frame = HERO_SPR_LADDER;
	hero->man.frameOffset = 0;
}

/*--------------------------------------------------------------------------*/

static void HeroStateSetClimbDown(void)
{
	hero->dir = DIR_DOWN;
	hero->man.dx = 0;
	hero->man.dy = 0x0001;
	hero->man.frame = HERO_SPR_LADDER;
	hero->man.frameOffset = 0;
	hero->state = HERO_STATE_CLIMB_DOWN;
	hero->steps = 8;
}

/*--------------------------------------------------------------------------*/

static void HeroStateSetFall(void)
{
	hero->dir = DIR_DOWN;
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

	//TODO sfx exchane
	//TODO hud or sprite update

	hero->swaps--;

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

static void HeroStateIdle(UBYTE joy)
{
	if (TRUE == HeroIsFall())
	{
		HeroStateSetFall();
		return;
	}

	if ((JOY_RIGHT & joy) && (TRUE == HeroCanRight()))
	{
		HeroStateSetWalkingRight();
		return;
	}

	if ((JOY_LEFT & joy) && (TRUE == HeroCanLeft()))
	{
		HeroStateSetWalkingLeft();
		return;
	}

	if ((JOY_UP & joy) && (TRUE == HeroCanUp()))
	{
		HeroStateSetClimbUp();
		return;
	}

	if (JOY_DOWN & joy && (TRUE == HeroCanDown()))
	{
		HeroStateSetClimbDown();
		return;
	}

	if ((JOY_BUTTON_RED & joy) && (TRUE == HeroTryExchange()))
	{
		HeroStateSetExchange();
		return;
	}

	if (0 == hero->idleCounter)
	{
		hero->man.frame = HERO_SPR_IDLE;
	}
	else
	{
		hero->idleCounter--;
	}

}

/*--------------------------------------------------------------------------*/

static void HeroStateWalkRight(UBYTE joy)
{
	hero->man.frameOffset = (hero->man.x >> 1) & 3;
	HeroMoveOneStep();

	if (0 != hero->steps)
	{
		return;
	}

	hero->steps = 8;

	if (TRUE == HeroIsFall())
	{
		HeroStateSetFall();
		return;
	}

	if ((JOY_RIGHT & joy) && (TRUE == HeroCanRight()))
	{
		return;
	}

	HeroStateSetIdle();
}

/*--------------------------------------------------------------------------*/

static void HeroStateWalkLeft(UBYTE joy)
{
	hero->man.frameOffset = (hero->man.x >> 1) & 3;
	HeroMoveOneStep();

	if (0 != hero->steps)
	{
		return;
	}

	hero->steps = 8;

	if (TRUE == HeroIsFall())
	{
		HeroStateSetFall();
		return;
	}

	if (JOY_LEFT & joy)
	{
		if (TRUE == HeroCanLeft())
		{
			return;
		}
	}

	HeroStateSetIdle();
}

/*--------------------------------------------------------------------------*/

static void HeroStateClimbUp(UBYTE joy)
{
	hero->man.frameOffset = (hero->man.y >> 2) & 1;
	HeroMoveOneStep();

	if (0 != hero->steps)
	{
		return;
	}

	hero->steps = 8;

	if ((JOY_UP & joy) && (TRUE == HeroCanUp()))
	{
		return;
	}

	HeroStateSetIdle();
}

/*--------------------------------------------------------------------------*/

static void HeroStateClimbDown(UBYTE joy)
{
	hero->man.frameOffset = (hero->man.y >> 2) & 1;
	HeroMoveOneStep();

	if (0 != hero->steps)
	{
		return;
	}

	hero->steps = 8;

	if ((JOY_DOWN & joy) && (TRUE == HeroCanDown()))
	{
		return;
	}

	HeroStateSetIdle();
}

/*--------------------------------------------------------------------------*/

void HeroStateFall(UBYTE joy)
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
	}

	if (JOY_BUTTON_RED & joy)
	{
		HeroStateSetExchange();
	}
}

/*--------------------------------------------------------------------------*/

static void HeroStateExchange(UBYTE joy)
{
	HeroMoveOneStep();

	if (0 != hero->steps)
	{
		return;
	}

	if ((JOY_BUTTON_RED & joy) && (TRUE == HeroTryExchange()))
	{
		HeroStateSetExchange();
		return;
	}

	HeroStateSetIdle();
}

/*--------------------------------------------------------------------------*/

void HeroHandleInput(UBYTE joy)
{
	UWORD dx;
	UWORD dy;

	switch (hero->state)
	{
		case HERO_STATE_IDLE:

			HeroStateIdle(joy);
			break;

		case HERO_STATE_WALK_RIGHT:

			HeroStateWalkRight(joy);
			break;

		case HERO_STATE_WALK_LEFT:
			HeroStateWalkLeft(joy);
			break;

		case HERO_STATE_CLIMB_UP:

			HeroStateClimbUp(joy);
			break;
		case HERO_STATE_CLIMB_DOWN:

			HeroStateClimbDown(joy);
			break;
		case HERO_STATE_FALL:

			HeroStateFall(joy);
			break;
		case HERO_STATE_EXCHANGE:

			HeroStateExchange(joy);
			break;
	}

	//HeroSyncWithEgo();

	SpriteDrawHero(&hero->man);
	SpriteDrawEgo(&hero->ego);
}

/*--------------------------------------------------------------------------*/
