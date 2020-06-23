//
// Created by IGRec on 21 Jun 2020.
//

#ifndef RAYLIB_TEMPLATE_GLOBALS_H
#define RAYLIB_TEMPLATE_GLOBALS_H

#include "raylib.h"
#include "raymath.h"

#include <stdio.h>
#include <string.h>

#define TILES_HORIZONTAL (28)
#define TILES_VERTICAL (36)
#define TILE_SIZE (24)

#define ASSET_PATH "../assets/"

typedef enum MovementDirection
{
	MD_UP,
	MD_DOWN,
	MD_LEFT,
	MD_RIGHT
} MovementDirection;

MovementDirection GetOpposite(MovementDirection direction);

Vector2 GridToScreen(Vector2 position);

#endif //RAYLIB_TEMPLATE_GLOBALS_H
