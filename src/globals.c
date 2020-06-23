//
// Created by IGRec on 21 Jun 2020.
//

#include "globals.h"

MovementDirection GetOpposite(MovementDirection direction)
{
	switch (direction)
	{
		case MD_UP:
		{
			return MD_DOWN;
		}
		case MD_DOWN:
		{
			return MD_UP;
		}
		case MD_LEFT:
		{
			return MD_RIGHT;
		}
		case MD_RIGHT:
		{
			return MD_LEFT;
		}
	}
}

Vector2 GridToScreen(Vector2Int position)
{
	Vector2 screenSpace = {
			.x = position.x * TILE_SIZE,
			.y = position.y * TILE_SIZE
	};
	return screenSpace;
}