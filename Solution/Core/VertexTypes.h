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
	int topLeft[2];
	int dimensions[2];
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

