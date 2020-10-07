#include "enemy.h"

#include "copper.h"
#include "game.h"
#include "gfxtile.h"
#include "hero.h"
#include "map.h"
#include "memory.h"
#include "sort.h"


#include <hardware/custom.h>

extern struct Custom* custom;

/*--------------------------------------------------------------------------*/

void EnemySpritesMultiplexing(void);
void EnemySpritesDraw(void);
void EnemySkullAnimation(void);

/*--------------------------------------------------------------------------*/

void  EnemyInit(void)
{
	mem->enemy_move_cnt = 8;
}

/*--------------------------------------------------------------------------*/

void EnemyWalkLeft(EnemySprite* enemy)
{
	UWORD spr = (mem->frameCounter >> 2) & 3;
	enemy->Frame = 4 + spr;
	enemy->PosX--;

	if (0 == mem->enemy_move_cnt)
	{
		return;
	}

	UWORD px = enemy->PosX;
	UWORD py = enemy->PosY;

	if (!(MapCheck(px, py + 8) & TILE_FLOOR) || (MapCheck(px - 8, py) & TILE_WALL))
	{
		enemy->Direction = TILE_NUM_ENEMY_R;
	}
}

/*--------------------------------------------------------------------------*/

void EnemyWalkRight(EnemySprite* enemy)
{
	UWORD spr = (mem->frameCounter >> 2) & 3;
	enemy->Frame = spr;
	enemy->PosX++;

	if (0 != mem->enemy_move_cnt)
	{
		return;
	}

	UWORD px = enemy->PosX;
	UWORD py = enemy->PosY;
	if (!(MapCheck(px + 8, py + 8) & TILE_FLOOR) || (MapCheck(px + 8, py) & TILE_WALL))
	{
		enemy->Direction = TILE_NUM_ENEMY_L;
	}
}

/*--------------------------------------------------------------------------*/

void EnemyWalkUp(EnemySprite* enemy)
{
	UWORD spr = (mem->frameCounter >> 4) & 3;
	enemy->Frame = 8 + spr;
	enemy->PosY--;

	if (0 != mem->enemy_move_cnt)
	{
		return;
	}

	UWORD px = enemy->PosX;
	UWORD py = enemy->PosY;
	if (MapCheck(px, py - 8) & (TILE_WALL | TILE_BRIDGE | TILE_WATER))
	{
		enemy->Direction = TILE_NUM_ENEMY_D;
	}
}

/*--------------------------------------------------------------------------*/

void EnemyWalkDown(EnemySprite* enemy)
{
	UWORD spr = (mem->frameCounter >> 4) & 3;
	enemy->Frame = 8 + spr;
	enemy->PosY++;

	if (0 != mem->enemy_move_cnt)
	{
		return;
	}

	UWORD px = enemy->PosX;
	UWORD py = enemy->PosY;

	if (MapCheck(px, py + 8) & (TILE_WALL | TILE_BRIDGE | TILE_WATER))
	{
		enemy->Direction = TILE_NUM_ENEMY_U;
	}
}

/*--------------------------------------------------------------------------*/
void EnemyAnimation(EnemySprite* enemy)
{
	switch (enemy->Direction)
	{
		case TILE_NUM_ENEMY_L:
			EnemyWalkLeft(enemy);
			break;
		case TILE_NUM_ENEMY_R:
			EnemyWalkRight(enemy);
			break;
		case TILE_NUM_ENEMY_U:
			EnemyWalkUp(enemy);
			break;
		case TILE_NUM_ENEMY_D:
			EnemyWalkDown(enemy);
			break;
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
	EnemySprite* enemy = mem->Enemies;

	for (UBYTE i = 0; i < mem->enemy_cnt; i++)
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
		EnemyAnimation(enemy);

		enemy++;
	}

	if (mem->enemy_move_cnt == 0)
	{
		mem->enemy_move_cnt = 8;
	}

	mem->enemy_move_cnt--;

	EnemySkullAnimation();

	return GAME_STATE_NOTHING;
}

/*--------------------------------------------------------------------------*/

UWORD AnimColors[] = { 0x0A20, 0x0E00, 0x0E80 ,0x0E00 };

void EnemySkullAnimation(void)
{
	//palette animation for eyes of enemies

	UBYTE index = (mem->frameCounter >> 4) & 3;

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

	mem->Enemies[mem->enemy_cnt].PosX = x;
	mem->Enemies[mem->enemy_cnt].PosY = y;
	mem->Enemies[mem->enemy_cnt].Frame = frame;
	mem->Enemies[mem->enemy_cnt].Direction = dir;

	mem->enemy_cnt++;
}

/*--------------------------------------------------------------------------*/

void EnemyInitCnt(void)
{
	mem->enemy_cnt = 0;
}

/*--------------------------------------------------------------------------*/

void EnemyDraw(void)
{
	EnemySpritesMultiplexing();
	EnemySpritesDraw();
}

/*---------------------------------------------------------------------------*/

void EnemyClearSpritesBuffer(void)
{
	ULONG* memory = (ULONG*)mem->spriteEnemyAddress;

	for (int i = 0; i < SPRITES_ENEMIES / 4; ++i)
	{
		*memory++ = 0;
	}
}

/*---------------------------------------------------------------------------*/

void EnemySpritesMultiplexing(void)
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
		mem->sprites[3 - i] = spriteData;

		for (int k = 0; k < mem->enemy_cnt; ++k)
		{
			if (mem->sortY[k].PosY > lastY)
			{
				mem->spriteAdress[mem->sortY[k].Index] = spriteData;
				spriteData += 17; //add 17 longs
				lastY = mem->sortY[k].PosY + 16;
				mem->sortY[k].PosY = 0;
			}
		}

		*spriteData = 0x0;
		spriteData++;

		--i;
	}
	while (i >= 0);
}

/*---------------------------------------------------------------------------*/

void EnemySpritesDraw(void)
{
	for (int i = 0; i < mem->enemy_cnt; ++i)
	{
		Sprite spr;
		spr.dst = (ULONG)mem->spriteAdress[i];
		spr.x = mem->Enemies[i].PosX;
		spr.y = mem->Enemies[i].PosY - 8;

		UBYTE charNr = mem->Enemies[i].Frame;
		spr.src = mem->spritesData + charNr * 16 * 4;

		SpriteDraw(&spr);
	}

	for (int i = 0; i < 4; ++i)
	{
		ULONG sprite = (ULONG)mem->sprites[i];
		ULONG copperSprite = mem->copperAddress + 9 * 4 + 2 + i * 8;
		CopperUpdateAddress(copperSprite, sprite);
	}
}

/*--------------------------------------------------------------------------*/
