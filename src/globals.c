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

Vector2Int Vector2IntAdd(Vector2Int a, Vector2Int b)
{
	return (Vector2Int){a.x + b.x, a.y + b.y};
}

Vector2Int Vector2IntSubtract(Vector2Int a, Vector2Int b)
{
	return (Vector2Int){a.x - b.x, a.y - b.y};
}

Vector2Int Vector2IntScale(Vector2Int vector, int scale)
{
	return (Vector2Int){vector.x * scale, vector.y * scale};
}

Vector2Int GetDirectionVector2Scaled(MovementDirection direction, int scale)
{
	switch (direction)
	{
		case MD_UP:
		{
			return (Vector2Int){0, -scale};
		}
		case MD_DOWN:
		{
			return (Vector2Int){0, scale};
		}
		case MD_LEFT:
		{
			return (Vector2Int){-scale, 0};
		}
		case MD_RIGHT:
		{
			return (Vector2Int){scale, 0};
		}
	}
}

int DistanceSquared(Vector2Int a, Vector2Int b)
{
	int hor = (b.x - a.x);
	int ver = (b.y - a.y);
	return hor*hor + ver*ver;
}

bool Vector2IntEquals(Vector2Int a, Vector2Int b)
{
	return (a.x == b.x) && (a.y == b.y);
}