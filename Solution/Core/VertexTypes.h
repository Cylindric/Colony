#pragma once

//create a basic vertex type
struct SpriteVertex
{
	//clip space coordinates
	float topLeft[2];
	float dimensions[2];
	unsigned int spritenum;
	float opacity;
};

