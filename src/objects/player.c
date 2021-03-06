//
// Created by IGRec on 22 Jun 2020.
//

#include "player.h"
#include "../management/level-manager.h"
#include "enemy.h"

Texture PlayerTextures[5];

Player InitPlayer(Vector2Int position, MovementDirection direction)
{
	Player newPlayer = {
			.position = position,
			
			.currentDirection = direction,
			.nextDirection = direction,
			
			.movementTimer = 0.0f
	};
	
	return newPlayer;
}

void UpdatePosition(Player* player)
{
	// Change direction
	{
		if (IsKeyPressed(KEY_W))
		{
			player->nextDirection = MD_UP;
		} else if (IsKeyPressed(KEY_S))
		{
			player->nextDirection = MD_DOWN;
		} else if (IsKeyPressed(KEY_A))
		{
			player->nextDirection = MD_LEFT;
		} else if (IsKeyPressed(KEY_D))
		{
			player->nextDirection = MD_RIGHT;
		}
	}
	
	// Move player to next tile
	{
		if (player->movementTimer >= MOVEMENT_TIMER)
		{
			player->movementTimer = 0.0f;
			player->currentDirection = player->nextDirection;
			
			if (!FacesWall(player->position, player->currentDirection))
			{
				switch (player->currentDirection)
				{
					case MD_UP:
					{
						player->y -= 1;
						break;
					}
					case MD_DOWN:
					{
						player->y += 1;
						break;
					}
					case MD_LEFT:
					{
						player->x -= 1;
						break;
					}
					case MD_RIGHT:
					{
						player->x += 1;
						break;
					}
				}
			}
		}
		
		player->movementTimer += GetFrameTime();
	}
}

void AteEdible(EdibleType type)
{
	if (type == ET_POWERUP)
	{
		EnterFright();
	}
}

void RenderPlayer(Player player, bool isDead)
{
	Rectangle source = {
			.width = 12,
			.height = 12
	};
	
	Vector2 screenSpace = GridToScreen(player.position);
	Rectangle rectangle = {
			.x = screenSpace.x - 0.25f*TILE_SIZE,
			.y = screenSpace.y - 0.25f*TILE_SIZE,
			.width = TILE_SIZE*1.5f,
			.height = TILE_SIZE*1.5f
	};
	
	DrawTexturePro(isDead ? PlayerTextures[4] : PlayerTextures[player.currentDirection], source, rectangle, Vector2Zero(), 0.0f, WHITE);
}