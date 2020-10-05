#include "sort.h"

/*--------------------------------------------------------------------------*/

void SortCopyPositionWithIndex(void)
{
	int k = mem->enemy_cnt;
	int i = 0;

	SortEntry* sort = mem->sortY;

	while (k > 0)
	{
		sort->PosY = mem->Enemies[i].PosY;
		sort->Index = i;
		sort++;
		++i;
		--k;
	}
}

/*--------------------------------------------------------------------------*/

void SortInsertion(void)
{
	for (int i = 1; i < mem->enemy_cnt; i++)
	{
		SortEntry tmp = mem->sortY[i];
		int j = i - 1;

		while (j >= 0 && tmp.PosY < mem->sortY[j].PosY)
		{
			mem->sortY[j + 1] = mem->sortY[j];
			j = j - 1;
		}

		mem->sortY[j + 1] = tmp;
	}
}

/*--------------------------------------------------------------------------*/
