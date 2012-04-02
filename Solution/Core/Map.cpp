#include "Map.h"
#include <random>

namespace Core
{

	Map::Map()
	{
	}


	Map::~Map()
	{
	}


	std::vector<SpriteVertex>* Map::GetSprites()
	{
		return &m_Tiles;
	}


	inline float convertPixelsToClipSpace( const int pixelDimension, const int pixels )
	{
		return (float)pixels/pixelDimension*2 -1;
	}

	inline float convertPixelsToClipSpaceDistance( const int pixelDimension, const int pixels )
	{
		return (float)pixels/pixelDimension*2;
	}

	bool Map::Initialise()
	{
		int spriteSize = 32;
		int numSprites = 3;
		
		m_Tiles.clear();

		SpriteVertex v;

		// try creating a bunch of tiles
		int rows = 50;
		int cols = 50;
		int left = 400 - (int)(spriteSize * cols * 0.5f);
		int top  = 300 - (int)(spriteSize * rows * 0.5f);

		// calculate the row and column for the sprite
		float twidth = 0.0625; // width of a single sprite texture (16/256)
		float j = 0.001953125; // width of half a pixel (0.5/256)
		unsigned int columns = 16;

		unsigned int spriteCol;
		unsigned int spriteRow;
		int spritenum;

		for(int row = 0; row < rows; row++)
		{
			for(int col = 0; col < cols; col++)
			{
				spritenum = (rand() % 16)+16; // just grab a random road tile for now
				spriteCol = spritenum % columns;
				spriteRow = spritenum / columns;

				v.topLeft[0] = convertPixelsToClipSpace(800, left + (col * spriteSize));
				v.topLeft[1] = -convertPixelsToClipSpace(600, top + (row * spriteSize));
				v.dimensions[0] = convertPixelsToClipSpaceDistance(800, spriteSize);
				v.dimensions[1] = convertPixelsToClipSpaceDistance(600, spriteSize);

				v.uvLeft = (spriteCol * twidth) + j + 0.0f;
				v.uvRight = (spriteCol * twidth) - j + twidth;
				v.uvTop = (spriteRow * twidth) + j + 0.0f;
				v.uvBottom = (spriteRow * twidth) - j + twidth;

				v.opacity = 1;
				m_Tiles.push_back(v);
			}
		}

		return true;
	}


	bool Map::Update()
	{
		return true;
	}


	void Map::Release()
	{
		m_Tiles.clear();
	}

}