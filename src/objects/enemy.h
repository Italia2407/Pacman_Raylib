//
// Created by IGRec on 29 Jun 2020.
//

#ifndef PACMAN_ENEMY_H
#define PACMAN_ENEMY_H

#include "../globals.h"
#include "../management/sprite-manager.h"

typedef enum EnemyState
{
	ES_CHASE,
	ES_SCATTER,
	ES_FRIGHT,
	ES_EATEN
} EnemyState;

typedef struct Enemy
{
	union
	{
		Vector2Int position;
		struct
		{
			int x;
			int y;
		};
	};
	Vector2Int scatterTile;
	
	MovementDirection currentDirection;
	EnemyState currentState;
	
	Vector2Int (*targetPosition)();
	
	float movementTimer;
	
	float frightTimer;
	
	Color colour;
	Sprite sprites[4];
} Enemy;

extern Texture FrightTexture;
extern Texture EyeTextures[4];

extern Enemy blinky;
extern Enemy inky;
extern Enemy pinky;
extern Enemy clyde;

Enemy InitEnemy(Vector2Int position, Vector2Int scatterTile, Vector2Int (*targetPostion)(), Color colour);

void MoveEnemy(Enemy* enemy);
void UpdateStates();
void EnterFright();

bool CheckPlayerCollision(Vector2Int playerPos);

void RenderEnemy(Enemy enemy);

#endif //PACMAN_ENEMY_H
