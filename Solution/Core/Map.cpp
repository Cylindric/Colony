#include "Map.h"

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

		v.topLeft[0] = convertPixelsToClipSpace(800, 400); // 0
		v.topLeft[1] = -convertPixelsToClipSpace(600, 300); // 0
		v.dimensions[0] = convertPixelsToClipSpaceDistance(800, spriteSize); //0.0400
		v.dimensions[1] = convertPixelsToClipSpaceDistance(600, spriteSize); //0.0533
		v.opacity = 1;
		m_Tiles.push_back(v);

		v.topLeft[0] = convertPixelsToClipSpace(800, 400+spriteSize); // 0.08
		v.topLeft[1] = -convertPixelsToClipSpace(600, 300); // 0
		v.dimensions[0] = convertPixelsToClipSpaceDistance(800, spriteSize); //0.0400
		v.dimensions[1] = convertPixelsToClipSpaceDistance(600, spriteSize); //0.0533
		v.opacity = 1;
		m_Tiles.push_back(v);

		v.topLeft[0] = convertPixelsToClipSpace(800, 400+spriteSize+spriteSize); // 0.16
		v.topLeft[1] = -convertPixelsToClipSpace(600, 300); // 0
		v.dimensions[0] = convertPixelsToClipSpaceDistance(800, spriteSize); //0.0400
		v.dimensions[1] = convertPixelsToClipSpaceDistance(600, spriteSize); //0.0533
		v.opacity = 1;
		m_Tiles.push_back(v);


		//SpriteVertex* v;
		//v = new SpriteVertex();
		//v->topLeft[0] = convertPixelsToClipSpace(800, 400); // 0
		//v->topLeft[1] = -convertPixelsToClipSpace(600, 300); // 0
		//v->dimensions[0] = convertPixelsToClipSpaceDistance(800, spriteSize); //0.0400
		//v->dimensions[1] = convertPixelsToClipSpaceDistance(600, spriteSize); //0.0533
		//v->opacity = 1;
		//m_Tiles.push_back(v);

		//v = new SpriteVertex();
		//v->topLeft[0] = convertPixelsToClipSpace(800, 400+spriteSize); // 0.08
		//v->topLeft[1] = -convertPixelsToClipSpace(600, 300); // 0
		//v->dimensions[0] = convertPixelsToClipSpaceDistance(800, spriteSize); //0.0400
		//v->dimensions[1] = convertPixelsToClipSpaceDistance(600, spriteSize); //0.0533
		//v->opacity = 1;
		//m_Tiles.push_back(v);

		//v = new SpriteVertex();
		//v->topLeft[0] = convertPixelsToClipSpace(800, 400+spriteSize+spriteSize); // 0.16
		//v->topLeft[1] = -convertPixelsToClipSpace(600, 300); // 0
		//v->dimensions[0] = convertPixelsToClipSpaceDistance(800, spriteSize); //0.0400
		//v->dimensions[1] = convertPixelsToClipSpaceDistance(600, spriteSize); //0.0533
		//v->opacity = 1;
		//m_Tiles.push_back(v);

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