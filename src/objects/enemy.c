//
// Created by IGRec on 29 Jun 2020.
//

#include "enemy.h"
#include "../management/level-manager.h"
#include <limits.h>

Enemy InitEnemy(Vector2Int position, Vector2Int scatterTile, Vector2Int (*targetPostion)(), Color colour)
{
	Enemy newEnemy = {
			.position = position,
			.scatterTile = scatterTile,
			.currentDirection = MD_RIGHT,
			.currentState = ES_CHASE,
			.targetPosition = targetPostion,
			.colour = colour
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

void RenderEnemy(Enemy enemy)
{
	Vector2 screenSpace = GridToScreen(enemy.position);
	Rectangle rectangle = {
			.x = screenSpace.x - 0.25f*TILE_SIZE,
			.y = screenSpace.y - 0.25f*TILE_SIZE,
			.width = TILE_SIZE*1.5f,
			.height = TILE_SIZE*1.5f
	};
	
	DrawRectangleRec(rectangle, enemy.colour);
}