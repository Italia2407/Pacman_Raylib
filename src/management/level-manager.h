//
// Created by IGRec on 23 Jun 2020.
//

#ifndef PACMAN_LEVEL_MANAGER_H
#define PACMAN_LEVEL_MANAGER_H

#include "../globals.h"

void CreateLevelMap();

bool FacesWall(Vector2Int position, MovementDirection direction);

void DrawLevelTileMap();

#endif //PACMAN_LEVEL_MANAGER_H
