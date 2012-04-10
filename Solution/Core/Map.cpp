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


	std::vector<SpriteVertex>* Map::GetSprites(SpriteType type)
	{
		if(type == SPRITE_TYPE_TILE)
		{
			return &m_Tiles;
		}
		return NULL;
	}


	void Map::SetSpriteSizePx(int px)
	{
		m_SpriteSizePx = px;
	}


	bool Map::Initialise(int screenWidth, int screenHeight)
	{
		m_ScreenWidth = screenWidth;
		m_ScreenHeight = screenHeight;
		m_SpriteSizePx = 32;
		m_Tiles.clear();
		return true;
	}


	bool Map::CreateRandomTiles(int w, int h)
	{
		SpriteVertex v;
		v.spriteType = SPRITE_TYPE_TILE;

		// try creating a bunch of tiles
		int rows = h;
		int cols = w;
		int left = (m_ScreenWidth / 2) - (int)(m_SpriteSizePx * cols * 0.5f);
		int top  = (m_ScreenHeight / 2) - (int)(m_SpriteSizePx * rows * 0.5f);

		// calculate the row and column for the sprite
		float twidth = 0.0625; // width of a single sprite texture (16/256)
		float j = 0.001953125; // width of half a texture pixel (0.5/256)
		unsigned int columns = 16;

		unsigned int spriteCol;
		unsigned int spriteRow;
		int spritenum;

		for(int row = 0; row < rows; row++)
		{
			for(int col = 0; col < cols; col++)
			{
				spritenum = (rand() % 16)+16; // just grab a random road tile for now
				if(row == 0 || row == rows-1 || col == 0 || col == cols-1) spritenum = 0;


				spriteCol = spritenum % columns;
				spriteRow = spritenum / columns;

				v.topLeft[0] = left + (col * m_SpriteSizePx);
				v.topLeft[1] = top + (row * m_SpriteSizePx);
				v.dimensions[0] = m_SpriteSizePx;
				v.dimensions[1] = m_SpriteSizePx;

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


	bool Map::Update(double timeStep)
	{
		return true;
	}


	void Map::UpdateTiles()
	{
	}


	void Map::Release()
	{
		m_Tiles.clear();
	}

}