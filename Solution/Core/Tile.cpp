#include "Tile.h"

namespace Core
{

	Tile::Tile()
	{
	}


	Tile::~Tile()
	{
	}


	bool Tile::Initialise()
	{
		m_Sprite.spriteType = SpriteType::SPRITE_TYPE_TILE;
		m_Sprite.dimensions[0] = 16;
		m_Sprite.dimensions[1] = 16;
		return true;
	}


	void Tile::SetType(int type)
	{
		m_TextureTileId = type;
		m_Sprite.opacity = 1;
		UpdateUV();

	}

	void Tile::SetPosition(int col, int row)
	{
		m_PosX = col;
		m_PosY = row;
	}


	SpriteVertex* Tile::GetSprite()
	{
		return &m_Sprite;
	}
	

	void Tile::UpdateUV()
	{
		float twidth = 0.0625; // width of a single sprite texture (16/256)
		float j = 0.001953125; // width of half a texture pixel (0.5/256)
		unsigned int columns = 16;
		m_Sprite.uvLeft = (m_PosX * twidth) + j + 0.0f;
		m_Sprite.uvRight = (m_PosX * twidth) - j + twidth;
		m_Sprite.uvTop = (m_PosY * twidth) + j + 0.0f;
		m_Sprite.uvBottom = (m_PosY * twidth) - j + twidth;
	}


	bool Tile::IsVisible()
	{
		return true;
	}

}