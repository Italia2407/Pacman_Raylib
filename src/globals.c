//
// Created by IGRec on 21 Jun 2020.
//

#include "globals.h"

Vector2 GridToScreen(Vector2 position)
{
	return Vector2Scale(position, TILE_SIZE);
}