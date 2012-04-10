#pragma once


//////////////
// INCLUDES //
//////////////
#include <vector>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "VertexTypes.h"


namespace Core
{
	class Map
	{
	public:
		Map(void);
		~Map(void);

		bool Initialise(int screenWidth, int screenHeight);
		void Release(void);
		bool Update(double timeStep);
		bool CreateRandomTiles(int w, int h);
		void SetSpriteSizePx(int px);

		std::vector<SpriteVertex>* GetSprites(SpriteType type);

	private:
		int m_SpriteSizePx;
		int m_ScreenWidth;
		int m_ScreenHeight;
		std::vector<SpriteVertex> m_Tiles;

		void UpdateTiles(void);
	};
}