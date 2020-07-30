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
	HERO_STATE_FALL

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
}

/*--------------------------------------------------------------------------*/

void HeroSetPosition(UWORD x, UWORD y)
{
	hero->man.x = x;
	hero->man.y = y;
}

static void HeroSetIdle(void)
{
	hero->state = HERO_STATE_IDLE;
	hero->dir = DIR_NONE;
	hero->idleCounter = HERO_IDLE_COUNTER_MAX;
}

static UBYTE HeroIsFall(void)
{
	UBYTE tile = MapCheck(hero->man.x, hero->man.y + 8);
	UBYTE bottom = MapCheck(hero->man.x, hero->man.y + 16);

	if (!(bottom & TILE_FLOOR) && !(tile & TILE_LADDER))
	{
		hero->dir = DIR_DOWN;
		hero->state = HERO_STATE_FALL;
		return TRUE;
	}

	return FALSE;
}

/*--------------------------------------------------------------------------*/

static void HeroStateIdle(UBYTE joy)
{
	if (TRUE == HeroIsFall())
	{
		return;
	}

	if (JOY_LEFT & joy)
	{
		hero->dir = DIR_LEFT;
		hero->man.dx = 0xffff;
		hero->man.dy = 0;
		hero->state = HERO_STATE_WALK_LEFT;
	}
	else if (JOY_RIGHT & joy)
	{
		hero->dir = DIR_RIGHT;
		hero->man.dx = 0x0001;
		hero->man.dy = 0;
		hero->state = HERO_STATE_WALK_RIGHT;
	}
	else if (JOY_UP & joy)
	{
		hero->dir = DIR_UP;
		hero->man.dx = 0;
		hero->man.dy = 0xffff;
		hero->state = HERO_STATE_CLIMB_UP;
	}
	else if (JOY_DOWN & joy)
	{
		hero->dir = DIR_DOWN;
		hero->man.dx = 0;
		hero->man.dy = 0x0001;
		hero->state = HERO_STATE_CLIMB_DOWN;
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
	if (0 == hero->steps)
	{
		if (TRUE == HeroIsFall())
		{
			return;
		}

		if (MapCheck(hero->man.x + 8, hero->man.y + 8) & TILE_WALL)
		{
			HeroSetIdle();
			return;
		}

		if (0 == (JOY_RIGHT & joy))
		{
			HeroSetIdle();
			return;
		}

		//FUTURE add possibility to go down or up 
		// if (JOY_DOWN & joy)
		// {
		// 	hero->state = HERO_STATE_CLIMB_DOWN;
		// 	hero->dir = DIR_DOWN;
		// 	return;
		// }

		hero->steps = 8;
	}

	hero->man.frame = HERO_SPR_WALK_RIGHT + ((hero->man.x >> 1) & 3);
	hero->man.x += hero->man.dx;
	hero->steps--;
}

/*--------------------------------------------------------------------------*/

static void HeroStateWalkLeft(UBYTE joy)
{
	if (0 == hero->steps)
	{
		if (TRUE == HeroIsFall())
		{
			return;
		}

		if (MapCheck(hero->man.x - 8, hero->man.y + 8) & TILE_WALL)
		{
			HeroSetIdle();
			return;
		}

		if (0 == (JOY_LEFT & joy))
		{
			HeroSetIdle();
			return;
		}

		hero->steps = 8;
	}

	hero->man.frame = HERO_SPR_WALK_LEFT + ((hero->man.x >> 1) & 3);
	hero->man.x += hero->man.dx;
	hero->steps--;
}

/*--------------------------------------------------------------------------*/

static void HeroStateClimbUp(UBYTE joy)
{
	if (0 == hero->steps)
	{
		UBYTE ladder = MapCheck(hero->man.x, hero->man.y + 8) & TILE_LADDER;
		UBYTE above = MapCheck(hero->man.x, hero->man.y) & TILE_LADDER;

		if (!(ladder ) || !(above))
		{
			HeroSetIdle();
			return;
		}

		if (0 == (JOY_UP & joy))
		{
			HeroSetIdle();
			return;
		}

		hero->steps = 8;
	}


	hero->man.frame = HERO_SPR_LADDER + ((hero->man.y >> 2) & 1);
	hero->man.y += hero->man.dy;
	hero->steps--;

}

/*--------------------------------------------------------------------------*/

static void HeroStateClimbDown(UBYTE joy)
{
	if (0 == hero->steps)
	{
		UBYTE ladder = MapCheck(hero->man.x, hero->man.y + 8) & TILE_LADDER;
		UBYTE above = MapCheck(hero->man.x, hero->man.y + 16);

		if (!(ladder ) && !(above & TILE_LADDER))
		{
			HeroSetIdle();
			return;
		}

		if (above & (TILE_WALL | TILE_BRIDGE))
		{
			HeroSetIdle();
			return;
		}

		if (0 == (JOY_DOWN & joy))
		{
			HeroSetIdle();
			return;
		}

		hero->steps = 8;
	}


	hero->man.frame = HERO_SPR_LADDER + ((hero->man.y >> 2) & 1);
	hero->man.y += hero->man.dy;
	hero->steps--;
}
/*--------------------------------------------------------------------------*/

void HeroStateFall(UBYTE joy)
{
	if (0 == hero->steps)
	{
		UBYTE tile = MapCheck(hero->man.x, hero->man.y + 8);
		UBYTE bottom = MapCheck(hero->man.x, hero->man.y + 16);

		if ((bottom & TILE_FLOOR) || (tile & TILE_LADDER))
		{
			HeroSetIdle();
			return;
		}

		hero->steps = 8;
	}

	hero->man.frame = HERO_SPR_FALL + ((hero->man.y >> 2) & 1);
	hero->man.y++;
	hero->steps--;
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
	}

	SpriteDrawHero(&hero->man);
}

/*--------------------------------------------------------------------------*/
