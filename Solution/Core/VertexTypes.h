#pragma once

struct SpriteVertex
{
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
