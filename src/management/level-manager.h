//
// Created by IGRec on 23 Jun 2020.
//

#ifndef PACMAN_LEVEL_MANAGER_H
#define PACMAN_LEVEL_MANAGER_H

#include "../globals.h"

typedef struct Tile
{
	bool wall;
} Tile;

extern Tile LevelTileMap[TILES_HORIZONTAL][TILES_VERTICAL-5];

void CreateLevelMap();

bool FacesWall(Vector2Int position, MovementDirection direction);

void DrawLevelTileMap();

#endif //PACMAN_LEVEL_MANAGER_H
