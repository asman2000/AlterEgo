#include "enemy.h"

#include "copper.h"
#include "game.h"
#include "gfxtile.h"
#include "hero.h"
#include "map.h"
#include "memory.h"
#include "sizes.h"


#include <hardware/custom.h>

extern struct Custom* custom;
/*--------------------------------------------------------------------------*/



typedef struct
{
	UWORD PosX;
	UWORD PosY;
	UWORD Frame;
	UWORD Direction;

} EnemySprite;

EnemySprite Enemies[ENEMY_MAX_AMOUNT];


ULONG* spriteAdress[ENEMY_MAX_AMOUNT];

typedef struct
{
	UWORD Index;
	UWORD PosY;
} SortEntry;

ULONG* sprites[4];


//enemy vars

UBYTE enemy_cnt;
UBYTE enemy_move_cnt;


void SpritesMultiplexed(void);
void SpritesDrawEnemies(void);
void EnemySkullAnimation(UBYTE frameCounter);
void EnemyCheckBlockCollision(void);

/*--------------------------------------------------------------------------*/

void  EnemyInit(void)
{
	enemy_move_cnt = 8;
}

/*--------------------------------------------------------------------------*/

void EnemyAnimation(EnemySprite* enemy, UWORD frame_cnt)
{
	UWORD j = enemy->Direction;

	if (TILE_NUM_ENEMY_L == j)
	{
		UWORD spr = (frame_cnt >> 2) & 3;
		enemy->Frame = 4 + spr;
		enemy->PosX--;

		if (0 == enemy_move_cnt)
		{
			UWORD px = enemy->PosX;
			UWORD py = enemy->PosY;

			if (!(MapCheck(px, py + 8) & TILE_FLOOR) || (MapCheck(px - 8, py) & TILE_WALL))
			{
				enemy->Direction = TILE_NUM_ENEMY_R;
			}
		}

		return;
	}
	
	if (TILE_NUM_ENEMY_R == j)
	{
		UWORD spr = (frame_cnt >> 2) & 3;
		enemy->Frame = spr;
		enemy->PosX++;

		if (0 == enemy_move_cnt)
		{
			UWORD px = enemy->PosX;
			UWORD py = enemy->PosY;
			if (!(MapCheck(px + 8, py + 8) & TILE_FLOOR) || (MapCheck(px + 8, py) & TILE_WALL))
			{
				enemy->Direction = TILE_NUM_ENEMY_L;
			}			
		}

		return;
	}

	if (TILE_NUM_ENEMY_U == j)
	{
		UWORD spr = (frame_cnt >> 4) & 3;
		enemy->Frame = 8 + spr;
		enemy->PosY--;

		if (0 == enemy_move_cnt)
		{
			UWORD px = enemy->PosX;
			UWORD py = enemy->PosY;
			if (MapCheck(px, py - 8) & (TILE_WALL | TILE_BRIDGE | TILE_WATER))
			{
				enemy->Direction = TILE_NUM_ENEMY_D;
			}
		}

		return;
	}

	if (TILE_NUM_ENEMY_D == j)
	{
		UWORD spr = (frame_cnt >> 4) & 3;
		enemy->Frame = 8 + spr;
		enemy->PosY++;

		if (0 == enemy_move_cnt)
		{
			UWORD px = enemy->PosX;
			UWORD py = enemy->PosY;

			if (MapCheck(px, py + 8) & (TILE_WALL | TILE_BRIDGE | TILE_WATER))
			{
				enemy->Direction = TILE_NUM_ENEMY_U;
			}
		}

		return;
	}
}
/*--------------------------------------------------------------------------*/

UBYTE EnemyProcess(struct Hero* hero, UBYTE frame_cnt)
{
	if ( !(frame_cnt & 1) || hero->state == HERO_STATE_EXCHANGE)
	{
		return GAME_STATE_NOTHING;
	}

	UWORD x = hero->man.x + 8;
	UWORD y = hero->man.y + 16;
	EnemySprite* enemy = Enemies;

	for (UBYTE i = 0; i < enemy_cnt; i++)
	{
		UWORD py = enemy->PosY;

		//check collision with hero 
		if (py >= (hero->man.y + 8) && py < y)
		{
			UWORD px = enemy->PosX;
			if (px >= hero->man.x && px < x)
			{
				return GAME_STATE_FAIL;
			}
		}

		//do animation of enemy (movement too)
		EnemyAnimation(enemy, frame_cnt);

		enemy++;
	}

	if (enemy_move_cnt == 0)
	{
		enemy_move_cnt = 8;
	}

	enemy_move_cnt--;

	EnemySkullAnimation(frame_cnt);

	return GAME_STATE_NOTHING;
}

/*--------------------------------------------------------------------------*/

UWORD AnimColors[] = { 0x0A20, 0x0E00, 0x0E80 ,0x0E00 };

void EnemySkullAnimation(UBYTE frameCounter)
{
	//palette animation for eyes of enemies

	UBYTE index = (frameCounter >> 4) & 3;

	//sprite colors
	// spr0 i spr1: 16-bg, 17,18,19
	// spr2 i spr3: 20-bg, 21,22,23
	// spr4 i spr5: 24-bg, 25,26,27
	// spr6 i spr7: 28-bg, 29,30,31

	custom->color[17] = AnimColors[index];
	custom->color[21] = AnimColors[index];
}

/*--------------------------------------------------------------------------*/

void EnemyAdd(UWORD x, UWORD y, UWORD dir)
{
	UWORD frame = 8; //skull up or down (they share same frames)

	if (TILE_NUM_ENEMY_L == dir)
	{
		frame = 4;
	}
	else if (TILE_NUM_ENEMY_R == dir)
	{
		frame = 0;
	}

	Enemies[enemy_cnt].PosX = x;
	Enemies[enemy_cnt].PosY = y;
	Enemies[enemy_cnt].Frame = frame;
	Enemies[enemy_cnt].Direction = dir;

	enemy_cnt++;
}

/*--------------------------------------------------------------------------*/

void EnemyInitCnt(void)
{
	enemy_cnt = 0;
}

/*--------------------------------------------------------------------------*/

void EnemyDraw(void)
{
	SpritesMultiplexed();
	SpritesDrawEnemies();
}

/*---------------------------------------------------------------------------*/

void SpritesClearEnemyBuffer(void)
{
	ULONG* memory = (ULONG*)mem->spriteEnemyAddress;

	for (int i = 0; i < SPRITES_ENEMIES / 4; ++i)
	{
		*memory++ = 0;
	}
}

/*---------------------------------------------------------------------------*/

SortEntry sortY[ENEMY_MAX_AMOUNT];

void SortCopyPositionWithIndex(void)
{
	int k = enemy_cnt;
	int i = 0;

	SortEntry* sort = sortY;

	while (k > 0)
	{
		sort->PosY = Enemies[i].PosY;
		sort->Index = i;
		sort++;
		++i;
		--k;
	}
}

void SortInsertion(void)
{
	for (int i = 1; i < enemy_cnt; i++)
	{
		SortEntry tmp = sortY[i];
		int j = i - 1;
		while (j >= 0 && tmp.PosY < sortY[j].PosY)
		{
			sortY[j + 1] = sortY[j];
			j = j - 1;
		}
		sortY[j + 1] = tmp;
	}
}

void SpritesMultiplexed(void)
{
	//0. copy y position with index
	SortCopyPositionWithIndex();

	//1. sorting (insertion sort)
	SortInsertion();

	ULONG* spriteData = (ULONG*)mem->spriteEnemyAddress;

	int i = 3;
	do
	{
		UWORD lastY = 0;
		sprites[3 - i] = spriteData;

		for (int k = 0; k < enemy_cnt; ++k)
		{
			if (sortY[k].PosY > lastY)
			{
				spriteAdress[sortY[k].Index] = spriteData;
				spriteData += 17; //add 17 longs
				lastY = sortY[k].PosY + 16;
				sortY[k].PosY = 0;
			}
		}

		*spriteData = 0x0;
		spriteData++;

		--i;
	}
	while (i >= 0);
}

/*---------------------------------------------------------------------------*/

void SpritesDrawEnemies(void)
{
	for (int i = 0; i < enemy_cnt; ++i)
	{
		ULONG sprite = (ULONG)spriteAdress[i];

		UWORD x = Enemies[i].PosX;
		UWORD y = Enemies[i].PosY - 8;
		UBYTE charNr = Enemies[i].Frame;

		ULONG gfxSprites = mem->spritesData + charNr * 16 * 4;

		Sprite spr;
		spr.x = x;
		spr.y = y;
		spr.src = gfxSprites;
		spr.dst = sprite;

		SpriteDraw(&spr);
	}

	for (int i = 0; i < 4; ++i)
	{
		ULONG sprite = (ULONG)sprites[i];
		ULONG copperSprite = mem->copperAddress + 9 * 4 + 2 + i * 8;
		CopperUpdateAddress(copperSprite, sprite);
	}
}

/*--------------------------------------------------------------------------*/
