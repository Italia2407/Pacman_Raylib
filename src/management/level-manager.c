//
// Created by IGRec on 23 Jun 2020.
//

#include "level-manager.h"

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

void CreateLevelMap()
{
	for (int i = 0; i < 13; i++)
	{
		tileTextures[i] = LoadTexture(tileTexturesFiles[i]);
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
				//DrawRectangleRec(rectangle, LIME);
				DrawTexturePro(tileTextures[LevelTileMap[y][x]], source, rectangle, Vector2Zero(), 0.0f, WHITE);
			}
		}
	}
}

/*
typedef struct Tile
{
	bool wall;
} Tile;

typedef enum TileType
{
	TT_EMPTY,
	TT_TOP,
	TT_TOPLEFT,
	TT_LEFT,
	TT_BOTTOMLEFT,
	TT_BOTTOM,
	TT_BOTTOMRIGHT,
	TT_RIGHT,
	TT_TOP_RIGHT,
	TT_TOPLEFTIN,
	TT_BOTTOMLEFTIN,
	TT_BOTTOMRIGHTIN,
	TT_TOPRIGHTIN,
	TT_FILLED
} TileType;

static const char* tileTextures[13] = {
		ASSET_PATH"walls/Top.png",
		ASSET_PATH"walls/Top_Left_Out.png",
		ASSET_PATH"walls/Left.png",
		ASSET_PATH"walls/Bottom_Left_Out.png",
		ASSET_PATH"walls/Bottom.png",
		ASSET_PATH"walls/Bottom_Right_Out.png",
		ASSET_PATH"walls/Right.png",
		ASSET_PATH"walls/Top_Right_Out.png",
		ASSET_PATH"walls/Top_Left_In.png",
		ASSET_PATH"walls/Bottom_Left_In.png",
		ASSET_PATH"walls/Bottom_Right_In.png",
		ASSET_PATH"walls/Top_Right_In.png",
		ASSET_PATH"walls/Filled.png"
		};

Tile LevelTileMap[TILES_HORIZONTAL][TILES_VERTICAL-5] = {0};
TileType TileMap[TILES_HORIZONTAL][TILES_VERTICAL-5] = {
		{}
};

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
 */