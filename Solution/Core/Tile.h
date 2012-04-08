#pragma once

#include "VertexTypes.h"

namespace Core
{

	class Tile
	{
	public:
		Tile(void);
		~Tile(void);

		bool Initialise(void);
		void Release(void);
		SpriteVertex* GetSprite(void);
		void SetPosition(int x, int y);
		void SetType(int type);
		bool IsVisible(void);

	private:
		SpriteVertex m_Sprite;
		float m_PosX;
		float m_PosY;
		int m_TextureTileId;

		void UpdateUV(void);
	};

}