//
// Created by IGRec on 24 May 2020.
//

#include "../globals.h"

#ifndef PACMAN_RAYLIB_SPRITEMANAGER_H
#define PACMAN_RAYLIB_SPRITEMANAGER_H

typedef struct sprite
{
	Image original;
	Texture image;
	
	int palette_size;
	Color* palette;
} Sprite;

Sprite LoadSprite(const char* asset_file);
Sprite LoadSpriteWithPalette(const char* asset_file, Color* new_palette);

void DrawSprite(Sprite sprite, Vector2 position);
void DrawSpriteCentred(Sprite sprite, Vector2 position);

void SetColourPalette(Sprite* sprite, Color* new_palette);
void ResetColourPalette(Sprite* sprite);
Color* GetOriginalPalette(Sprite sprite);

#endif //PACMAN_RAYLIB_SPRITEMANAGER_H
