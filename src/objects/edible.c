//
// Created by IGRec on 4 Jul 2020.
//

#include "edible.h"
#include "player.h"

#define MAX_EDIBLES (TILES_HORIZONTAL * (TILES_VERTICAL-5))
static int NumberEdibles = 0;
int EdibleSize = 8;
Edible* Edibles = NULL;

bool AddEdible(Edible edible)
{
	if (NumberEdibles >= EdibleSize)
	{
		if (EdibleSize < MAX_EDIBLES)
		{
			EdibleSize += 8;
			if (EdibleSize > MAX_EDIBLES)
				EdibleSize = MAX_EDIBLES;
			
			Edibles = (Edible*)realloc(Edibles, EdibleSize*sizeof(Edible));
		} else
			return false;
	}
	
	Edibles[NumberEdibles] = edible;
	NumberEdibles++;
	
	return true;
}

void CheckPlayerCollisionEdible(Vector2Int playerPosition)
{
	for (int i = 0; i < NumberEdibles; i++)
	{
		if (Vector2IntEquals(Edibles[i].position, playerPosition))
		{
			AteEdible(Edibles[i].type);
			for (int j = i; j < NumberEdibles-1; j++)
			{
				Edibles[j] = Edibles[j+1];
			}
			NumberEdibles--;
		}
	}
}

void DrawEdibles()
{
	for (int i = 0; i < NumberEdibles; i++)
	{
		Edible current = Edibles[i];
		DrawRectangle(current.position.x*TILE_SIZE, current.position.y*TILE_SIZE, TILE_SIZE, TILE_SIZE, GRAY);
	}
}