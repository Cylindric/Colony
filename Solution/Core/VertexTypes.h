#pragma once

struct SpriteVertex
{
	float topLeft[2];
	float dimensions[2];
	unsigned int spritenum;
	float opacity;
};


struct FontVertex
{
	float position[3];
	float texture[2];
};
