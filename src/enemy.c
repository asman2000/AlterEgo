#include "enemy.h"

#include "copper.h"
#include "game.h"
#include "gfxtile.h"
#include "hero.h"
#include "map.h"
#include "memory.h"


#include <hardware/custom.h>

extern struct Custom* custom;
/*--------------------------------------------------------------------------*/

#define ENEMY_MAX_AMOUNT 8

typedef struct
{
	UWORD PosX;
	UWORD PosY;
	UWORD Frame;
	UWORD Direction;

} EnemySprite;

EnemySprite Enemies[ENEMY_MAX_AMOUNT];

ULONG* enemySpritesMemory = NULL;

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
void SpritesDrawEnemies(const MemoryDetails* m);
void EnemySkullAnimation(UBYTE frameCounter);
void EnemyCheckBlockCollision(const MemoryDetails* m);

/*--------------------------------------------------------------------------*/

void  EnemyInit(void)
{
	enemy_move_cnt = 8;
}

/*--------------------------------------------------------------------------*/

void EnemyAnimation(EnemySprite* enemy, UWORD frame_cnt, const MemoryDetails* m)
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

			if (!(MapCheck(px, py + 8, m) & TILE_FLOOR) || (MapCheck(px - 8, py, m) & TILE_WALL))
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
			if (!(MapCheck(px + 8, py + 8, m) & TILE_FLOOR) || (MapCheck(px + 8, py, m) & TILE_WALL))
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
			if (MapCheck(px, py - 8, m) & (TILE_WALL | TILE_BRIDGE | TILE_WATER))
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

			if (MapCheck(px, py + 8, m) & (TILE_WALL | TILE_BRIDGE | TILE_WATER))
			{
				enemy->Direction = TILE_NUM_ENEMY_U;
			}
		}

		return;
	}
}
/*--------------------------------------------------------------------------*/
UBYTE EnemyProcess(struct Hero* player, UBYTE frame_cnt, const MemoryDetails* m)
{
	if ( !(frame_cnt & 1) || player->state == HERO_STATE_EXCHANGE)
	{
		return 0;
	}

	UWORD player_x1e = player->man.x + 8;
	UWORD player_y1e = player->man.y + 8;
	EnemySprite* enemy = Enemies;

	for (UBYTE i = 0; i < enemy_cnt; i++)
	{
		
		UWORD py = enemy->PosY;

		//check collision with hero 
		if (py >= player->man.y && py < player_y1e)
		{
			UWORD px = enemy->PosX;
			if (px >= player->man.x && px < player_x1e)
			{
				//DONE_NOLUCK
				return 1;
			}
		}

		//do animation of enemy (movement too)
		EnemyAnimation(enemy, frame_cnt, m);

		enemy++;
	}

	if (enemy_move_cnt == 0)
	{
		enemy_move_cnt = 8;
	}

	enemy_move_cnt--;

	//EnemyCheckBlockCollision();

	EnemySkullAnimation(frame_cnt);

	return 0;
}

/*--------------------------------------------------------------------------*/

void EnemyCheckBlockCollision(const MemoryDetails* m)
{
	enemy_move_cnt--;

	//wait for synchronization
	if (!enemy_move_cnt)
	{
		return;
	}

	//check enemy collision with level blocks
	for (UBYTE i = 0; i < enemy_cnt; i++)
	{
		UWORD px = Enemies[i].PosX;
		UWORD py = Enemies[i].PosY;

		switch(Enemies[i].Direction)
		{
		case TILE_NUM_ENEMY_L:
			if (!(MapCheck(px, py + 8, m) & TILE_FLOOR) ||
				(MapCheck(px - 8, py, m) & TILE_WALL))
			{
				Enemies[i].Direction = TILE_NUM_ENEMY_R;
			}
			break;

		case TILE_NUM_ENEMY_R:
			if (!(MapCheck(px + 8, py + 8, m)&TILE_FLOOR) ||
				(MapCheck(px + 8, py, m)  &TILE_WALL))
			{
				Enemies[i].Direction = TILE_NUM_ENEMY_L;
			}
			break;

		case TILE_NUM_ENEMY_U:
			if (MapCheck(px, py - 8, m)&(TILE_WALL | TILE_BRIDGE | TILE_WATER))
			{
				Enemies[i].Direction = TILE_NUM_ENEMY_D;
			}
			break;

		case TILE_NUM_ENEMY_D:
			if (MapCheck(px, py + 8, m)&(TILE_WALL | TILE_BRIDGE | TILE_WATER))
			{
				Enemies[i].Direction = TILE_NUM_ENEMY_U;
			}
			break;
		}
	}

	enemy_move_cnt = 8;

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

void EnemyDraw(const MemoryDetails* m)
{
	SpritesMultiplexed();
	SpritesDrawEnemies(m);
}

/*---------------------------------------------------------------------------*/

// void SpritesSetUp(void)
// {
// 	enemySpritesMemory = (ULONG*)MemoryGetSpriteEnemy();
// }

/*---------------------------------------------------------------------------*/

void SpritesClearEnemyBuffer(void)
{
	ULONG* memory = enemySpritesMemory;

	for (int i = 0; i < (ENEMY_MAX_AMOUNT * 18 * 4) / 4; ++i)
	{
		*memory++ = 0;
	}
}

/*---------------------------------------------------------------------------*/

SortEntry sortY[ENEMY_MAX_AMOUNT];

void SortCopyPositionWithIndex(void)
{
	//for (int i = 0; i < enemy_cnt; ++i)
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


	ULONG* spriteData = enemySpritesMemory;


	//for (int i = 0; i < 4; ++i)
	
	//for (int i = 3; i >= 0; --i)
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

// extern void PrintSprite(__reg("a0") ULONG sprite,
// 	__reg("d0") UWORD x,
// 	__reg("d1") UWORD y,
// 	__reg("a1") ULONG gfx);

void SpritesDrawEnemies(const MemoryDetails* m)
{
	for (int i = 0; i < enemy_cnt; ++i)
	{
		ULONG sprite = (ULONG)spriteAdress[i];

		UWORD x = Enemies[i].PosX;
		UWORD y = Enemies[i].PosY - 8;
		UBYTE charNr = Enemies[i].Frame;

		//ULONG gfxSprites = MemoryGetSpritesData() + charNr * 16 * 4;
		ULONG gfxSprites = m->sprites.data + charNr * 16 * 4;

		//PrintSprite(sprite, x, y, gfxSprites);
		
		//TODO SpriteDraw()
	}

	for (int i = 0; i < 4; ++i)
	{
		ULONG sprite = (ULONG)sprites[i];
		ULONG copperSprite = m->copper.address + 9 * 4 + 2 + i * 8;
		CopperUpdateAddress(copperSprite, sprite);
	}
}

/*--------------------------------------------------------------------------*/
