//
// Created by IGRec on 23 Jun 2020.
//

#include "level-manager.h"
#include "../objects/edible.h"

typedef enum TileType
{
	TT_FILLED,
	TT_TOPLEFTOUT,
	TT_TOP,
	TT_TOPRIGHTOUT,
	TT_RIGHT,
	TT_BOTTOMLEFTIN,
	TT_BOTTOMRIGHTIN,
	TT_BOTTOMRIGHTOUT,
	TT_BOTTOMLEFTOUT,
	TT_LEFT,
	TT_TOPRIGHTIN,
	TT_BOTTOM,
	TT_TOPLEFTIN,
	TT_EMPTY
} TileType;

TileType LevelTileMap[TILES_VERTICAL-5][TILES_HORIZONTAL] = {
		{12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 10, 12, 11, 11, 11, 11, 10, 12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 10},
		{ 4, 13, 13, 13, 13, 13, 13, 13, 13, 13,  9,  4, 13, 13, 13, 13,  9,  4, 13, 13, 13, 13, 13, 13, 13, 13, 13,  9},
		{ 4, 13,  1,  2,  2,  2,  2,  2,  3, 13,  9,  4, 13,  1,  3, 13,  9,  4, 13,  1,  2,  2,  2,  2,  2,  3, 13,  9},
		{ 4, 13,  8, 11, 10, 12, 11, 11,  7, 13,  8,  7, 13,  9,  4, 13,  8,  7, 13,  8, 11, 11, 10, 12, 11,  7, 13,  9},
		{ 4, 13, 13, 13,  9,  4, 13, 13, 13, 13, 13, 13, 13,  9,  4, 13, 13, 13, 13, 13, 13, 13,  9,  4, 13, 13, 13,  9},
		{ 5,  2,  3, 13,  9,  4, 13,  1,  3, 13,  1,  3, 13,  9,  4, 13,  1,  3, 13,  1,  3, 13,  9,  4, 13,  1,  2,  6},
		{ 0,  0,  4, 13,  9,  4, 13,  9,  4, 13,  9,  4, 13,  9,  4, 13,  9,  4, 13,  9,  4, 13,  9,  4, 13,  9,  0,  0},
		{ 0,  0,  4, 13,  8,  7, 13,  9,  4, 13,  9,  4, 13,  8,  7, 13,  9,  4, 13,  9,  4, 13,  8,  7, 13,  9,  0,  0},
		{ 0,  0,  4, 13, 13, 13, 13,  9,  4, 13,  9,  4, 13, 13, 13, 13,  9,  4, 13,  9,  4, 13, 13, 13, 13,  9,  0,  0},
		{ 0,  0,  4, 13,  1,  2,  2,  6,  4, 13,  9,  5,  2,  2,  2,  2,  6,  4, 13,  9,  5,  2,  2,  3, 13,  9,  0,  0},
		{12, 11,  7, 13,  8, 11, 11, 11,  7, 13,  8, 11, 11, 11, 11, 11, 11,  7, 13,  8, 11, 11, 11,  7, 13,  8, 11, 10},
		{ 4, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  9},
		{ 4, 13,  1,  2,  2,  3, 13,  1,  3, 13,  1,  3, 13,  1,  3, 13,  1,  3, 13,  1,  3, 13,  1,  2,  2,  3, 13,  9},
		{ 4, 13,  8, 11, 11,  7, 13,  9,  4, 13,  9,  4, 13,  8,  7, 13,  9,  4, 13,  9,  4, 13,  8, 11, 11,  7, 13,  9},
		{ 4, 13, 13, 13, 13, 13, 13,  9,  4, 13,  9,  4, 13, 13, 13, 13,  9,  4, 13,  9,  4, 13, 13, 13, 13, 13, 13,  9},
		{ 5,  2,  2,  2,  2,  3, 13,  9,  4, 13,  9,  5,  2,  2,  2,  2,  6,  4, 13,  9,  4, 13,  1,  2,  2,  2,  2,  6},
		{ 0,  0,  0,  0,  0,  4, 13,  9,  4, 13,  8, 11, 11, 11, 11, 11, 11,  7, 13,  9,  4, 13,  9,  0,  0,  0,  0,  0},
		{ 0,  0,  0,  0,  0,  4, 13,  9,  4, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  9,  4, 13,  9,  0,  0,  0,  0,  0},
		{ 0,  0,  0,  0,  0,  4, 13,  9,  5,  2,  2,  3, 13,  1,  3, 13,  1,  2,  2,  6,  4, 13,  9,  0,  0,  0,  0,  0},
		{ 0,  0, 12, 11, 11,  7, 13,  8, 11, 11, 11,  7, 13,  9,  4, 13,  8, 11, 11, 11,  7, 13,  8, 11, 11, 10,  0,  0},
		{ 0,  0,  4, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  9,  4, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  9,  0,  0},
		{ 0,  0,  4, 13,  1,  2,  2,  2,  3, 13,  1,  2,  2,  6,  5,  2,  2,  3, 13,  1,  2,  2,  2,  3, 13,  9,  0,  0},
		{12, 11,  7, 13,  8, 11, 11, 10,  4, 13,  8, 11, 11, 11, 11, 11, 11,  7, 13,  9, 12, 11, 11,  7, 13,  8, 11, 10},
		{ 4, 13, 13, 13, 13, 13, 13,  9,  4, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  9,  4, 13, 13, 13, 13, 13, 13,  9},
		{ 5,  2,  3, 13,  1,  3, 13,  9,  4, 13,  1,  2,  2,  2,  2,  2,  2,  3, 13,  9,  4, 13,  1,  3, 13,  1,  2,  6},
		{12, 11,  7, 13,  9,  4, 13,  8,  7, 13,  9, 12, 11, 11, 11, 11, 10,  4, 13,  8,  7, 13,  9,  4, 13,  8, 11, 10},
		{ 4, 13, 13, 13,  9,  4, 13, 13, 13, 13,  9,  4, 13, 13, 13, 13,  9,  4, 13, 13, 13, 13,  9,  4, 13, 13, 13,  9},
		{ 4, 13,  1,  2,  6,  5,  2,  2,  3, 13,  9,  4, 13,  1,  3, 13,  9,  4, 13,  1,  2,  2,  6,  5,  2,  3, 13,  9},
		{ 4, 13,  8, 11, 11, 11, 11, 11,  7, 13,  8,  7, 13,  9,  4, 13,  8,  7, 13,  8, 11, 11, 11, 11, 11,  7, 13,  9},
		{ 4, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  9,  4, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  9},
		{ 5,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  6,  5,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  6}
};

static const char* tileTexturesFiles[13] = {
		ASSET_PATH"walls/Filled.png",
		ASSET_PATH"walls/Top_Left_Out.png",
		ASSET_PATH"walls/Top.png",
		ASSET_PATH"walls/Top_Right_Out.png",
		ASSET_PATH"walls/Right.png",
		ASSET_PATH"walls/Bottom_Left_In.png",
		ASSET_PATH"walls/Bottom_Right_In.png",
		ASSET_PATH"walls/Bottom_Right_Out.png",
		ASSET_PATH"walls/Bottom_Left_Out.png",
		ASSET_PATH"walls/Left.png",
		ASSET_PATH"walls/Top_Right_In.png",
		ASSET_PATH"walls/Bottom.png",
		ASSET_PATH"walls/Top_Left_In.png"
};
static Texture tileTextures[13];

static Vector2Int PowerPellets[6] = {
		(Vector2Int){1, 4},
		(Vector2Int){1, 12},
		(Vector2Int){3, 23},
		(Vector2Int){26, 4},
		(Vector2Int){26, 12},
		(Vector2Int){24, 23}
};

void CreateLevelMap()
{
	for (int i = 0; i < 13; i++)
	{
		tileTextures[i] = LoadTexture(tileTexturesFiles[i]);
	}
	
	for (int y = 0; y < TILES_VERTICAL-5; y++)
	{
		for (int x = 0; x < TILES_HORIZONTAL; x++)
		{
			if (LevelTileMap[y][x] == TT_EMPTY)
			{
				bool PowerLocation = false;
				for (int i = 0; i < 6; i++)
				{
					if (Vector2IntEquals((Vector2Int){x, y}, PowerPellets[i]))
						PowerLocation = true;
				}
				Edible newEdible = {
						.position = (Vector2Int){x, y+3},
						.type = (PowerLocation) ? ET_POWERUP : ET_NORMAL
				};
				AddEdible(newEdible);
			}
		}
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
	
	return LevelTileMap[tilePosition.y][tilePosition.x] != TT_EMPTY;
}

void DrawLevelTileMap()
{
	Rectangle source = {
			.width = 8,
			.height = 8
	};
	for (int y = 0; y < TILES_VERTICAL-5; y++)
	{
		for (int x = 0; x < TILES_HORIZONTAL; x++)
		{
			if (LevelTileMap[y][x] != TT_EMPTY)
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
				DrawTexturePro(tileTextures[LevelTileMap[y][x]], source, rectangle, Vector2Zero(), 0.0f, WHITE);
			}
		}
	}
}