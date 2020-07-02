#include "globals.h"
#include "objects/player.h"
#include "objects/enemy.h"
#include "management/level-manager.h"

#define SCREEN_WIDTH (TILES_HORIZONTAL * TILE_SIZE)
#define SCREEN_HEIGHT (TILES_VERTICAL * TILE_SIZE)

#define LEVEL_COLOUR RAYWHITE
#define UI_COLOUR (Color){235, 235, 235, 255}

Vector2Int BlinkyTarget();
Vector2Int InkyTarget();
Vector2Int PinkyTarget();
Vector2Int ClydeTarget();

Player player;

Enemy blinky;
Enemy inky;
Enemy pinky;
Enemy clyde;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Puck-Man");
    SetTargetFPS(60);
    
    CreateLevelMap();
    
    player = InitPlayer((Vector2Int){13, 26}, MD_UP);
    
    blinky = InitEnemy((Vector2Int){26, 4}, (Vector2Int){TILES_HORIZONTAL-1, 0}, &BlinkyTarget, RED);
    inky = InitEnemy((Vector2Int){26, 32}, (Vector2Int){TILES_HORIZONTAL-1, TILES_VERTICAL-1}, &InkyTarget, SKYBLUE);
    pinky = InitEnemy((Vector2Int){1, 4}, (Vector2Int){0, 0}, &PinkyTarget, MAGENTA);
    clyde = InitEnemy((Vector2Int){1, 32}, (Vector2Int){0, TILES_VERTICAL-1}, &ClydeTarget, ORANGE);
    
    while (!WindowShouldClose())
    {
    	UpdatePosition(&player);
    	
    	MoveEnemy(&blinky);
    	MoveEnemy(&inky);
    	MoveEnemy(&pinky);
    	MoveEnemy(&clyde);
    	
        BeginDrawing();
        
        // Top section of the screen
		{
			BeginScissorMode(0, 0, SCREEN_WIDTH, 3*TILE_SIZE);
			ClearBackground(UI_COLOUR);
			EndScissorMode();
		}
		// Bottom section of the screen
		{
			BeginScissorMode(0, 34*TILE_SIZE, SCREEN_WIDTH, 2*TILE_SIZE);
			ClearBackground(UI_COLOUR);
			EndScissorMode();
		}
		// Middle section of the screen
		{
			BeginScissorMode(0, 3*TILE_SIZE, SCREEN_WIDTH, 31*TILE_SIZE);
			ClearBackground(LEVEL_COLOUR);
			
			DrawLevelTileMap();
			RenderPlayer(player);
			RenderEnemy(blinky);
			RenderEnemy(inky);
			RenderEnemy(pinky);
			RenderEnemy(clyde);
			
			EndScissorMode();
		}

        EndDrawing();
    }
    CloseWindow();
    return 0;
}

Vector2Int BlinkyTarget()
{
	return player.position;
}

Vector2Int InkyTarget()
{
	Vector2Int intermediate = Vector2IntAdd(player.position, GetDirectionVector2Scaled(player.currentDirection, 2));
	
	return Vector2IntSubtract(Vector2IntScale(intermediate, 2), blinky.position);
}

Vector2Int PinkyTarget()
{
	return Vector2IntAdd(player.position, GetDirectionVector2Scaled(player.currentDirection, 4));
}

Vector2Int ClydeTarget()
{
	if (DistanceSquared(clyde.position, player.position) > 64)
		return player.position;
	else
		return clyde.scatterTile;
}