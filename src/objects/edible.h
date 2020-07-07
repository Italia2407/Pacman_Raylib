//
// Created by IGRec on 4 Jul 2020.
//

#ifndef PACMAN_EDIBLE_H
#define PACMAN_EDIBLE_H

#include "../globals.h"

typedef enum EdibleType
{
	ET_NORMAL,
	ET_POWERUP
} EdibleType;

typedef struct Edible
{
	Vector2Int position;
	
	EdibleType type;
} Edible;

extern Edible* Edibles;
extern int EdibleSize;

bool AddEdible(Edible edible);
void CheckPlayerCollisionEdible(Vector2Int playerPosition);

void DrawEdibles();

#endif //PACMAN_EDIBLE_H
