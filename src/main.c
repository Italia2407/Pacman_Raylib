#include "globals.h"

#define SCREEN_WIDTH (TILES_HORIZONTAL * TILE_SIZE)
#define SCREEN_HEIGHT (TILES_VERTICAL * TILE_SIZE)

#define LEVEL_COLOUR RAYWHITE
#define UI_COLOUR (Color){235, 235, 235, 255}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Puck-Man");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        
        // Top section of the screen
		{
			BeginScissorMode(0, 0, SCREEN_WIDTH, 3*TILE_SIZE);
			ClearBackground(UI_COLOUR);
			EndScissorMode();
		}
		// Middle section of the screen
		{
			BeginScissorMode(0, 3*TILE_SIZE, SCREEN_WIDTH, 31*TILE_SIZE);
			ClearBackground(LEVEL_COLOUR);
			EndScissorMode();
		}
		// Bottom section of the screen
		{
			BeginScissorMode(0, 34*TILE_SIZE, SCREEN_WIDTH, 2*TILE_SIZE);
			ClearBackground(UI_COLOUR);
			EndScissorMode();
		}

        EndDrawing();
    }
    CloseWindow();
    return 0;
}