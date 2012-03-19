// includes
#include <string>
#include <iostream>
#include <fstream>
#include "Map.h"
#include "Tile.h"
#include "Soil\SOIL.h"
#include "Vector2i.h"

using namespace std;

// Singleton object
CMap* CMap::instance = NULL;


CMap* CMap::getInstance(void)
{
	if (instance == NULL) {
		instance = new CMap();
	}
	return instance;
}


unsigned int CMap::getTileSize(void)
{
	return tileSize;
}


CMap::CMap(void) 
{
	highlightedTile = new Vector2i(0, 0);
}

CMap::~CMap(void)
{
	instance = NULL;
	delete instance;
}


bool CMap::onInit(char* filename)
{
	tiles.clear();

	// open the map file
	ifstream mapFile(filename);

	// First line must be the tileset
	string tilesetFilename;
	mapFile >> tilesetFilename >> tileSize;
	tilesetTextureId = SOIL_load_OGL_texture(
		tilesetFilename.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	if (tilesetTextureId == 0)
	{
		cerr << "Error loading map tileset" << endl;
		return false;
	}
	cout << "Loaded tileset: " << tilesetFilename << endl;


	// Next is the width and height of the map
	mapFile >> tileColumns >> tileRows;
	cout << "Dimensions: " << tileColumns << "x" << tileRows << endl;

	// Next should be lines of tiles
	unsigned int tileCount = 0;
	while (tileCount < (tileColumns * tileRows)) {
		int tileTexId = 0;
		int tileTypeId = 0;
		char sep = ' ';
		int row = tileRows - (tileCount / tileColumns) - 1;

		mapFile >> tileTexId >> sep >> tileTypeId;

		CTile* t = new CTile();
		t->setPosition((tileCount % tileColumns), row);
		t->setTypeId(tileTypeId);
		t->setTextureId(tileTexId);
		tiles.push_back(t);
		tileCount++;
	}

	// Next should be any entities
	//while (mapFile.good()) {
	//	std::string objectName = "";
	//	int valA = 0;
	//	int valB = 0;
	//	int valC = 0;
	//	int valD = 0;

	//	mapFile >> objectName >> valA >> valB >> valC >> valD;
	//	if (objectName == "buggy") {
	//		CEntity_Buggy* ent = new CEntity_Buggy();
	//		ent->OnLoad();
	//		ent->Position.X = valA;
	//		ent->Position.Y = valB;
	//		ent->Destination.X = valC;
	//		ent->Destination.Y = valD;
	//		CTile* entTile = CMap::MapControl.getTile(ent->Position);
	//		entTile->EntityList.push_back(ent);
	//		CEntity::EntityList.push_back(ent);
	//	}
	//}

	mapFile.close();
	return true;
}


void CMap::onRender()
{
	for (vector<CTile*>::iterator t = tiles.begin(); t < tiles.end(); t++)
	{
		Vector2i tp = (*t)->getPosition();
		if (tp == *highlightedTile)
		{
			(*t)->setHighlight(true);
		}
		else
		{
			(*t)->setHighlight(false);
		}
		(*t)->onRender(tilesetTextureId);
	}
}


CTile* CMap::getTileAt(unsigned int x, unsigned int y)
{
	return tiles[((tileRows-y-1)*tileColumns) + x];
}


void CMap::setHighlightedTile(int x, int y)
{
	if (x > tileColumns - 1) x = tileColumns - 1;
	if (x < 0) x = 0;

	if (y > tileRows - 1) y = tileRows - 1;
	if (y < 0) y = 0;

	highlightedTile->x = x;
	highlightedTile->y = y;
}