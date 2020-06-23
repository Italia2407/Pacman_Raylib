//
// Created by IGRec on 23 Jun 2020.
//

#include "level-manager.h"

Tile LevelTileMap[TILES_HORIZONTAL][TILES_VERTICAL-5] = {0};

static Tile ValidWall = {true};

void CreateLevelMap()
{
	for (int i = 0; i < TILES_HORIZONTAL; i++)
	{
		LevelTileMap[i][0] = ValidWall;
		LevelTileMap[i][TILES_VERTICAL-5 - 1] = ValidWall;
	}
	for (int i = 0; i < TILES_VERTICAL-5; i++)
	{
		LevelTileMap[0][i] = ValidWall;
		LevelTileMap[TILES_HORIZONTAL - 1][i] = ValidWall;
	}
}

bool FacesWall(Vector2Int position, MovementDirection direction)
{
	Vector2Int tilePosition = position;
	tilePosition.y -= 3;
	switch (direction)
	{
		case MD_UP:
		{
			tilePosition.y -= 1;
			break;
		}
		case MD_DOWN:
		{
			tilePosition.y += 1;
			break;
		}
		case MD_LEFT:
		{
			tilePosition.x -= 1;
			break;
		}
		case MD_RIGHT:
		{
			tilePosition.x += 1;
			break;
		}
	}
	
	return LevelTileMap[tilePosition.x][tilePosition.y].wall;
}

void DrawLevelTileMap()
{
	for (int y = 0; y < TILES_VERTICAL-5; y++)
	{
		for (int x = 0; x < TILES_HORIZONTAL; x++)
		{
			if (LevelTileMap[x][y].wall)
			{
				Vector2 position = {
						.x = x,
						.y = y + 3.0f
				};
				Rectangle rectangle = {
						.x = position.x*TILE_SIZE,
						.y = position.y*TILE_SIZE,
						.width = TILE_SIZE,
						.height = TILE_SIZE
				};
				DrawRectangleRec(rectangle, LIME);
			}
		}
	}
}