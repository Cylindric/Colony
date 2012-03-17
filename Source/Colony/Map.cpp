// includes
#include <string>
#include <iostream>
#include <fstream>
#include "Map.h"
#include "Tile.h"
#include "Soil\SOIL.h"

using namespace std;

// Singleton object
CMap* CMap::instance = NULL;


CMap* CMap::getInstance() {
	if (instance == NULL) {
		instance = new CMap();
	}
	return instance;
}


CMap::CMap(void) 
{
}

CMap::~CMap(void)
{
	instance = NULL;
	delete instance;
}


bool CMap::onInit(char* filename)
{
	tiles.clear();
	//unsigned int rows = 100;
	//unsigned int cols = 100;
	//for (unsigned int row = 0; row < rows; row++) {
	//	for (unsigned int col = 0; col < cols; col++) {
	//		CTile* tile = new CTile(col, row, ((row*cols)+col)%6);
	//		tiles.push_back(tile);
	//	}
	//} 

	// open the map file
	ifstream mapFile(filename);

	// First line must be the tileset
	string tilesetFilename;
	mapFile >> tilesetFilename >> tileSize >> tilesetColumns;
	tilesetTextureId = SOIL_load_OGL_texture(
		"./gfx/tiles.png",
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
		int valA = 0;
		int valB = 0;
		char sep = ' ';

		mapFile >> valA >> sep >> valB;

		CTile* t = new CTile();
		t->setPosition((tileCount % tileColumns), (tileCount / tileColumns));
		t->setTypeId(valA);
		t->setTextureId(valB);
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
		(*t)->onRender(tilesetTextureId);
	}
}
