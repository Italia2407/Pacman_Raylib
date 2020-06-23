//
// Created by IGRec on 23 Jun 2020.
//

#include "level-manager.h"

Tile LevelTileMap[TILES_HORIZONTAL][TILES_VERTICAL-5] = {0};

static Tile ValidWall = {true};

void CreateLevelMap()
{
	LevelTileMap[0][0] = ValidWall;
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
	
	if (tilePosition.y < 0 ||
		tilePosition.y >= TILES_VERTICAL-5 ||
		tilePosition.x < 0 ||
		tilePosition.x >= TILES_HORIZONTAL)
	{
		return true;
	} else
	{
		return LevelTileMap[tilePosition.x][tilePosition.y].wall;
	}
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
						.y = y + 3.0f*TILE_SIZE
				};
				Rectangle rectangle = {
						.x = position.x,
						.y = position.y,
						.width = TILE_SIZE,
						.height = TILE_SIZE
				};
				DrawRectangleRec(rectangle, LIME);
			}
		}
	}
}