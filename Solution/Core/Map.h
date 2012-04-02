#pragma once

#include <vector>
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

		std::vector<SpriteVertex>* GetSprites(SpriteType type);

	private:
		std::vector<SpriteVertex> m_Tiles;
	};
}