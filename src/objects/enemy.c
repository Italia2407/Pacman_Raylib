//
// Created by IGRec on 29 Jun 2020.
//

#include "enemy.h"
#include "../management/level-manager.h"
#include <limits.h>

#define CHASE_TIME (24.0f)
#define SCATTER_TIME (6.0f)
#define FRIGHT_TIME (12.0f)

static EnemyState GlobalState = ES_CHASE;
static bool FrightMode = false;
static float StateTimer = 0.0f;
static float FrightTimer = 0.0f;

Enemy blinky;
Enemy inky;
Enemy pinky;
Enemy clyde;

Texture FrightTexture;
Texture EyeTextures[4];

Enemy InitEnemy(Vector2Int position, Vector2Int scatterTile, Vector2Int (*targetPostion)(), Color colour)
{
	Color palette[] = {colour, (Color){197, 204, 184, 255}, (Color){67, 52, 85, 255}};
	Enemy newEnemy = {
			.position = position,
			.scatterTile = scatterTile,
			.currentDirection = MD_RIGHT,
			.currentState = GlobalState,
			.targetPosition = targetPostion,
			.colour = colour,
			.sprites[0] = LoadSpriteWithPalette(ASSET_PATH"enemies/Ghost_Up.png", palette),
			.sprites[1] = LoadSpriteWithPalette(ASSET_PATH"enemies/Ghost_Left.png", palette),
			.sprites[2] = LoadSpriteWithPalette(ASSET_PATH"enemies/Ghost_Right.png", palette),
			.sprites[3] = LoadSpriteWithPalette(ASSET_PATH"enemies/Ghost_Down.png", palette)
	};
	
	return newEnemy;
}

void MoveEnemy(Enemy* enemy)
{
	if (enemy->movementTimer >= MOVEMENT_TIMER)
	{
		enemy->movementTimer = 0.0f;
		
		Vector2Int targetTile;
		if (enemy->currentState == ES_CHASE)
			targetTile = enemy->targetPosition();
		else
			targetTile = enemy->scatterTile;
		
		int distances[5];
		distances[4] = INT_MAX-1;
		if (enemy->currentState != ES_FRIGHT)
		{
			distances[0] = DistanceSquared(Vector2IntAdd(enemy->position, (Vector2Int){0, -1}), targetTile);
			distances[1] = DistanceSquared(Vector2IntAdd(enemy->position,(Vector2Int){-1, 0}), targetTile);
			distances[2] = DistanceSquared(Vector2IntAdd(enemy->position,(Vector2Int){0, 1}), targetTile);
			distances[3] = DistanceSquared(Vector2IntAdd(enemy->position,(Vector2Int){1, 0}), targetTile);
		} else
		{
			for (int i = 0; i < 4; i++)
			{
				distances[i] = GetRandomValue(INT_MIN, INT_MAX-2);
			}
		}
		
		int shortest = -1;
		while (shortest == -1)
		{
			shortest = 0;
			
			for (int i = 1; i <= 4; i++)
			{
				if (distances[i] < distances[shortest])
					shortest = i;
			}
			
			switch (shortest)
			{
				case 0:
				{
					if (enemy->currentDirection == MD_DOWN || FacesWall(enemy->position, MD_UP))
					{
						distances[0] = INT_MAX;
						shortest = -1;
					} else
					{
						enemy->currentDirection = MD_UP;
					}
					break;
				}
				case 1:
				{
					if (enemy->currentDirection == MD_RIGHT || FacesWall(enemy->position, MD_LEFT))
					{
						distances[1] = INT_MAX;
						shortest = -1;
					} else
					{
						enemy->currentDirection = MD_LEFT;
					}
					break;
				}
				case 2:
				{
					if (enemy->currentDirection == MD_UP || FacesWall(enemy->position, MD_DOWN))
					{
						distances[2] = INT_MAX;
						shortest = -1;
					} else
					{
						enemy->currentDirection = MD_DOWN;
					}
					break;
				}
				case 3:
				{
					if (enemy->currentDirection == MD_LEFT || FacesWall(enemy->position, MD_RIGHT))
					{
						distances[3] = INT_MAX;
						shortest = -1;
					} else
					{
						enemy->currentDirection = MD_RIGHT;
					}
					break;
				}
				default:
				{
					enemy->currentDirection = 3 - enemy->currentDirection;
				}
			}
		}
		
		switch (enemy->currentDirection)
		{
			case MD_UP:
			{
				enemy->y -= 1;
				break;
			}
			case MD_DOWN:
			{
				enemy->y += 1;
				break;
			}
			case MD_LEFT:
			{
				enemy->x -= 1;
				break;
			}
			case MD_RIGHT:
			{
				enemy->x += 1;
				break;
			}
		}
	}
	
	enemy->movementTimer += GetFrameTime();
}

void UpdateStates()
{
	if (FrightMode)
	{
		FrightTimer += GetFrameTime();
		// Check if fright timer has ended
		if (FrightTimer >= FRIGHT_TIME)
		{
			blinky.currentState = GlobalState;
			inky.currentState = GlobalState;
			pinky.currentState = GlobalState;
			clyde.currentState = GlobalState;
			
			FrightMode = false;
		}
	} else
	{
		StateTimer += GetFrameTime();
		
		// Check if chase timer has ended
		if (GlobalState == ES_CHASE && StateTimer >= CHASE_TIME)
		{
			blinky.currentState = ES_SCATTER;
			inky.currentState = ES_SCATTER;
			pinky.currentState = ES_SCATTER;
			clyde.currentState = ES_SCATTER;
			
			StateTimer = 0.0f;
			GlobalState = ES_SCATTER;
		}
		// Check if scatter timer has ended
		else if (GlobalState == ES_SCATTER && StateTimer >= SCATTER_TIME)
		{
			blinky.currentState = ES_CHASE;
			inky.currentState = ES_CHASE;
			pinky.currentState = ES_CHASE;
			clyde.currentState = ES_CHASE;
			
			StateTimer = 0.0f;
			GlobalState = ES_CHASE;
		}
	}
}

void EnterFright()
{
	FrightTimer = 0.0f;
	FrightMode = true;
	
	blinky.currentState = ES_FRIGHT;
	inky.currentState = ES_FRIGHT;
	pinky.currentState = ES_FRIGHT;
	clyde.currentState = ES_FRIGHT;
	
	blinky.currentDirection = 3 - blinky.currentDirection;
	inky.currentDirection = 3 - inky.currentDirection;
	pinky.currentDirection = 3 - pinky.currentDirection;
	clyde.currentDirection = 3 - clyde.currentDirection;
}

static bool EnemyCollided(Enemy* enemy, Vector2Int playerPos)
{
	if (Vector2IntEquals(enemy->position, playerPos))
	{
		if (FrightMode)
		{
			printf("Fright collision happened!");
			enemy->currentState = ES_EATEN;
		}
		
		return !FrightMode;
	}
	
	return false;
}

bool CheckPlayerCollision(Vector2Int playerPos)
{
	bool BlinkyCollsion = EnemyCollided(&blinky, playerPos);
	bool InkyCollsion = EnemyCollided(&inky, playerPos);
	bool PinkyCollsion = EnemyCollided(&pinky, playerPos);
	bool ClydeCollsion = EnemyCollided(&clyde, playerPos);
	
	return BlinkyCollsion || InkyCollsion || PinkyCollsion || ClydeCollsion;
}

void RenderEnemy(Enemy enemy)
{
	Texture usedTexture;
	if (enemy.currentState == ES_CHASE || enemy.currentState == ES_SCATTER)
		usedTexture = enemy.sprites[enemy.currentDirection].image;
	else if (enemy.currentState == ES_FRIGHT)
		usedTexture = FrightTexture;
	else if (enemy.currentState == ES_EATEN)
		usedTexture = EyeTextures[enemy.currentDirection];
	
	
	Rectangle source = {
			.width = usedTexture.width,
			.height = usedTexture.height
	};
	
	Vector2 screenSpace = GridToScreen(enemy.position);
	Rectangle rectangle = {
			.x = screenSpace.x - 0.25f*TILE_SIZE,
			.y = screenSpace.y - 0.25f*TILE_SIZE,
			.width = TILE_SIZE*1.5f,
			.height = TILE_SIZE*1.5f
	};
	
	DrawTexturePro(usedTexture, source, rectangle, Vector2Zero(), 0.0f, WHITE);
}