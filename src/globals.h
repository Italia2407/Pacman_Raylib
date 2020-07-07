//
// Created by IGRec on 21 Jun 2020.
//

#ifndef RAYLIB_TEMPLATE_GLOBALS_H
#define RAYLIB_TEMPLATE_GLOBALS_H

#include "raylib.h"
#include "raymath.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSET_PATH "../assets/"

#define TILES_HORIZONTAL (28)
#define TILES_VERTICAL (36)
#define TILE_SIZE (24)

#define MOVEMENT_TIMER (0.25f)

typedef struct Vector2Int
{
	int x;
	int y;
} Vector2Int;

typedef enum MovementDirection
{
	MD_UP,
	MD_LEFT,
	MD_RIGHT,
	MD_DOWN
} MovementDirection;

MovementDirection GetOpposite(MovementDirection direction);

Vector2 GridToScreen(Vector2Int position);

Vector2Int Vector2IntAdd(Vector2Int a, Vector2Int b);
Vector2Int Vector2IntSubtract(Vector2Int a, Vector2Int b);
Vector2Int Vector2IntScale(Vector2Int vector, int scale);

Vector2Int GetDirectionVector2Scaled(MovementDirection direction, int scale);

int DistanceSquared(Vector2Int a, Vector2Int b);
bool Vector2IntEquals(Vector2Int a, Vector2Int b);

#endif //RAYLIB_TEMPLATE_GLOBALS_H
