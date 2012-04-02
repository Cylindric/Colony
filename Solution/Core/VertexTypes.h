#pragma once

enum SpriteType
{
	SPRITE_TYPE_NONE,
	SPRITE_TYPE_TILE,
	SPRITE_TYPE_TEXT
};


struct SpriteVertex
{
	unsigned int spriteType;
	float topLeft[2];
	float dimensions[2];
	float uvLeft;
	float uvTop;
	float uvRight;
	float uvBottom;
	float opacity;
};


struct FontVertex
{
	float position[3];
	float texture[2];
};


inline float convertPixelsToClipSpace( const int pixelDimension, const int pixels )
{
	return (float)pixels/pixelDimension*2 -1;
}

inline float convertPixelsToClipSpaceDistance( const int pixelDimension, const int pixels )
{
	return (float)pixels/pixelDimension*2;
}
