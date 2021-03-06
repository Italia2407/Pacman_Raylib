#include "globals.h"
#include "objects/player.h"
#include "objects/enemy.h"
#include "objects/edible.h"
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

bool gameOver = false;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Puck-Man");
    SetTargetFPS(60);
    
    // Load all textures once
	{
		PlayerTextures[0] = LoadTexture(ASSET_PATH"player/Player_Up.png");
		PlayerTextures[1] = LoadTexture(ASSET_PATH"player/Player_Left.png");
		PlayerTextures[2] = LoadTexture(ASSET_PATH"player/Player_Right.png");
		PlayerTextures[3] = LoadTexture(ASSET_PATH"player/Player_Down.png");
		PlayerTextures[4] = LoadTexture(ASSET_PATH"player/Player_Dead.png");
		
		FrightTexture = LoadTexture(ASSET_PATH"enemies/Ghost_Frightened.png");
		EyeTextures[0] = LoadTexture(ASSET_PATH"enemies/Eyes_Up.png");
		EyeTextures[1] = LoadTexture(ASSET_PATH"enemies/Eyes_Left.png");
		EyeTextures[2] = LoadTexture(ASSET_PATH"enemies/Eyes_Right.png");
		EyeTextures[3] = LoadTexture(ASSET_PATH"enemies/Eyes_Down.png");
		
		PelletTexture = LoadTexture(ASSET_PATH"Pellet.png");
		PowerPelletTexture = LoadTexture(ASSET_PATH"Power_Pellet.png");
	}
    
    Edibles = (Edible*)calloc(EdibleSize, sizeof(Edible));
    
    CreateLevelMap();
    
    player = InitPlayer((Vector2Int){13, 26}, MD_UP);
    
    blinky = InitEnemy((Vector2Int){26, 4}, (Vector2Int){TILES_HORIZONTAL-1, 0}, &BlinkyTarget, (Color){174, 79, 80, 255});
    inky = InitEnemy((Vector2Int){26, 32}, (Vector2Int){TILES_HORIZONTAL-1, TILES_VERTICAL-1}, &InkyTarget, (Color){104, 172, 169, 255});
    pinky = InitEnemy((Vector2Int){1, 4}, (Vector2Int){0, 0}, &PinkyTarget, (Color){195, 136, 144, 255});
    clyde = InitEnemy((Vector2Int){1, 32}, (Vector2Int){0, TILES_VERTICAL-1}, &ClydeTarget, (Color){190, 149, 92, 255});
    
    while (!WindowShouldClose())
    {
    	if (!gameOver)
		{
			UpdatePosition(&player);
			CheckPlayerCollisionEdible(player.position);
			
			if (CheckPlayerCollision(player.position))
			{
				gameOver = true;
			}
		
			UpdateStates();
			MoveEnemy(&blinky);
			MoveEnemy(&inky);
			MoveEnemy(&pinky);
			MoveEnemy(&clyde);
			
			if (CheckPlayerCollision(player.position))
			{
				gameOver = true;
			}
		}
    	
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
			
			if (gameOver)
				DrawText("GAME OVER!", TILE_SIZE, 34*TILE_SIZE, 2*TILE_SIZE, BLACK);
			
			EndScissorMode();
		}
		// Middle section of the screen
		{
			BeginScissorMode(0, 3*TILE_SIZE, SCREEN_WIDTH, 31*TILE_SIZE);
			ClearBackground(LEVEL_COLOUR);
			
			DrawLevelTileMap();
			DrawEdibles();
			
			RenderPlayer(player, gameOver);
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