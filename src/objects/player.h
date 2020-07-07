//
// Created by IGRec on 22 Jun 2020.
//

#ifndef RAYLIB_TEMPLATE_PLAYER_H
#define RAYLIB_TEMPLATE_PLAYER_H

#include "../globals.h"
#include "edible.h"

typedef struct Player
{
	union
	{
		Vector2Int position;
		struct
		{
			int x;
			int y;
		};
	};
	
	MovementDirection currentDirection;
	MovementDirection nextDirection;
	
	float movementTimer;
	
} Player;

Player InitPlayer(Vector2Int position, MovementDirection direction);

void UpdatePosition(Player* player);
void AteEdible(EdibleType type);

void RenderPlayer(Player player);

#endif //RAYLIB_TEMPLATE_PLAYER_H
