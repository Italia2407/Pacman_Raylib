#include "globals.h"
#include "objects/player.h"
#include "objects/enemy.h"
#include "management/level-manager.h"

#define SCREEN_WIDTH (TILES_HORIZONTAL * TILE_SIZE)
#define SCREEN_HEIGHT (TILES_VERTICAL * TILE_SIZE)

#define LEVEL_COLOUR RAYWHITE
#define UI_COLOUR (Color){235, 235, 235, 255}

Vector2Int BlinkyTarget();

Player player;

Enemy blinky;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Puck-Man");
    SetTargetFPS(60);
    
    CreateLevelMap();
    
    player = InitPlayer((Vector2Int){13, 26}, MD_UP);
    
    blinky = InitEnemy((Vector2Int){1, 5}, (Vector2Int){0, 0}, &BlinkyTarget);
    
    while (!WindowShouldClose())
    {
    	UpdatePosition(&player);
    	MoveEnemy(&blinky);
    	
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