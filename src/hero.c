#include "hero.h"

#include "sprite.h"
#include "input.h"
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

struct Hero
{
	UWORD x;
	UWORD y;
	UWORD src;
	UWORD dst;

	UWORD dir;
	UWORD steps;

	UBYTE frame;
};


static struct Hero heroes[2];

static struct Hero* hero;



void HeroInit(HeroNumber number)
{
	hero = &heroes[0];

	if (HERO_TWO == number)
	{
		hero = &heroes[1];
	}

	hero->dir = DIR_NONE;
	hero->x = 64;
	hero->y = 128;
	//TODO
	hero->src = 0;	// spriteGfxData + 12 * 16 * 4;
	hero->dst = 0;	//spriteHero;

	hero->steps = 8;
	hero->frame = HERO_SPR_IDLE;
}

void HeroDraw(void)
{
	//just for test
	//SpriteDrawHero(100,100);
}

void HeroProcess(UBYTE joy)
{
	if (DIR_NONE == hero->dir)
	{
		if (JOY_LEFT & joy)
		{
			hero->dir = DIR_LEFT;
			hero->steps = 8;
		}
		else if (JOY_RIGHT & joy)
		{
			hero->dir = DIR_RIGHT;
			hero->steps = 8;
			
		}

		if (JOY_UP & joy)
		{
			hero->dir = DIR_UP;
			hero->steps = 8;
		}
		else if (JOY_DOWN & joy)
		{
			hero->dir = DIR_DOWN;
			hero->steps = 8;
		}
	}

	HeroMove();


	SpriteDrawHero(hero->x, hero->y, hero->frame);
}

void HeroMove(void)
{
	if (DIR_NONE == hero->dir)
	{
		return;
	}

	if (DIR_LEFT == hero->dir)
	{
		hero->x--;
		hero->frame = HERO_SPR_WALK_LEFT + (3 - ((hero->x >> 1) & 3));
	}
	else if (DIR_RIGHT == hero->dir)
	{
		hero->x++;
		hero->frame = HERO_SPR_WALK_RIGHT + ((hero->x >> 1) & 3);
	}

	if (DIR_UP == hero->dir)
	{
		hero->y--;
		hero->frame = HERO_SPR_LADDER + ((hero->y >> 2) & 1);
	}
	else if (DIR_DOWN == hero->dir)
	{
		hero->y++;
		hero->frame = HERO_SPR_LADDER + ((hero->y >> 2) & 1);
	}

	hero->steps--;

	if (0 == hero->steps)
	{
		hero->dir = DIR_NONE;
	}
}

/*--------------------------------------------------------------------------*/
