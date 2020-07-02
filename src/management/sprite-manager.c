//
// Created by IGRec on 31 May 2020.
//

#include "sprite-manager.h"

#define MAX_PALETTE_SIZE 256

Sprite LoadSprite(const char* asset_file)
{
	Sprite new_sprite = {0};
	
	new_sprite.original = LoadImage(asset_file);
	ImageFormat(&new_sprite.original, UNCOMPRESSED_R8G8B8A8);
	
	new_sprite.palette = ImageExtractPalette(new_sprite.original, MAX_PALETTE_SIZE, &new_sprite.palette_size);
	new_sprite.image = LoadTextureFromImage(new_sprite.original);
	
	return new_sprite;
}

Sprite LoadSpriteWithPalette(const char* asset_file, Color* new_palette)
{
	Sprite new_sprite = {0};
	
	new_sprite.original = LoadImage(asset_file);
	ImageFormat(&new_sprite.original, UNCOMPRESSED_R8G8B8A8);
	
	new_sprite.palette = ImageExtractPalette(new_sprite.original, MAX_PALETTE_SIZE, &new_sprite.palette_size);
	SetColourPalette(&new_sprite, new_palette);
	
	return new_sprite;
}

void DrawSprite(Sprite sprite, Vector2 position)
{
	Rectangle imageSection = {
			.width = sprite.image.width,
			.height = sprite.image.height
	};
	DrawTextureRec(sprite.image, imageSection, position, WHITE);
}

void DrawSpriteCentred(Sprite sprite, Vector2 position)
{
	Vector2 centreOffset = (Vector2){sprite.image.width / 2, sprite.image.height / 2};
	DrawSprite(sprite, Vector2Subtract(position, centreOffset));
}

void SetColourPalette(Sprite* sprite, Color* new_palette)
{
	Image copy = ImageCopy(sprite->original);
	Color* pixels = copy.data;
	
	Color* original_palette = GetOriginalPalette(*sprite);
	
	for (int y = 0; y < sprite->original.height; y++)
	{
		for (int x = 0; x < sprite->original.width; x++)
		{
			Color* pixel = &pixels[y * copy.width + x];
			for (int i = 0; i < sprite->palette_size; i++)
			{
				if (ColorToInt(*pixel) == ColorToInt(original_palette[i]))
				{
					*pixel = new_palette[i];
					break;
				}
			}
		}
	}
	
	sprite->image = LoadTextureFromImage(copy);
	sprite->palette = new_palette;
}

void ResetColourPalette(Sprite* sprite)
{
	sprite->image = LoadTextureFromImage(sprite->original);
	sprite->palette = GetOriginalPalette(*sprite);
}

Color* GetOriginalPalette(Sprite sprite)
{
	Color* palette = ImageExtractPalette(sprite.original, MAX_PALETTE_SIZE, &sprite.palette_size);
	
	return palette;
}