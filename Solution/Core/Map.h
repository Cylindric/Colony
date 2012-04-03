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

		bool Initialise(void);
		void Release(void);
		bool Update(void);
		bool CreateRandomTiles(int w, int h);

		std::vector<SpriteVertex>* GetSprites(SpriteType type);

	private:
		std::vector<SpriteVertex> m_Tiles;
	};
}