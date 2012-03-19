// includes
#define UNICODE
#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
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
	mapFilename = filename;

	tiles.clear();

	// open the map file
	ifstream mapFile(filename);

	// First line must be the tileset
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
		char c = ' ';
		int row = tileRows - (tileCount / tileColumns) - 1;

		mapFile >> c;

		CTile* t = new CTile();
		t->setPosition((tileCount % tileColumns), row);
		switch (c) 
		{
		case '.':
			t->setTypeId(TILE_TYPE_OPEN);
			t->setTextureId(0);
			break;
		case '#':
			t->setTypeId(TILE_TYPE_WALL);
			t->setTextureId(31);
			break;
		}
		tiles.push_back(t);
		tileCount++;
	}

	mapFile.close();

	// process walls
	bool wallN, wallS, wallE, wallW;
	CTile* tileN;
	CTile* tileE;
	CTile* tileS;
	CTile* tileW;
	for (unsigned int row = 0; row < tileRows; row++)
	{
		for (unsigned int col = 0; col < tileColumns; col++)
		{
			CTile* tile = getTileAt(col, row);

			wallN = false;
			wallS = false;
			wallE = false;
			wallW = false;

			if (col == 5 && row == 2)
			{
				cerr << "wut";
			}

			if (tile->getTypeId() == TILE_TYPE_WALL)
			{
				char walls = 0;

				tileN = getTileAt(col, row+1);
				tileE = getTileAt(col+1, row);
				tileS = getTileAt(col, row-1);
				tileW = getTileAt(col-1, row);
				if (row > 0) 
				{
					if(tileS->getTypeId() == TILE_TYPE_WALL) walls += DIRECTION_S;
				}
				if (row < tileRows-1)
				{
					if(tileN->getTypeId() == TILE_TYPE_WALL) walls += DIRECTION_N;
				}
				if (col > 0)
				{
					if(tileW->getTypeId() == TILE_TYPE_WALL) walls += DIRECTION_W;
				}
				if (col < tileColumns-1)
				{
					if(tileE->getTypeId() == TILE_TYPE_WALL) walls += DIRECTION_E;
				}

				if (walls == DIRECTION_E) tile->setTextureId(16); // end
				if (walls == DIRECTION_S) tile->setTextureId(17); // end
				if (walls == DIRECTION_N) tile->setTextureId(18); // end
				if (walls == DIRECTION_W) tile->setTextureId(19); // end

				if (walls == (DIRECTION_E + DIRECTION_S)) tile->setTextureId(20); // corner
				if (walls == (DIRECTION_W + DIRECTION_S)) tile->setTextureId(21); // corner
				if (walls == (DIRECTION_N + DIRECTION_E)) tile->setTextureId(22); // corner
				if (walls == (DIRECTION_N + DIRECTION_W)) tile->setTextureId(23); // corner

				if (walls == (DIRECTION_N + DIRECTION_S + DIRECTION_E)) tile->setTextureId(24); // tee
				if (walls == (DIRECTION_E + DIRECTION_S + DIRECTION_W)) tile->setTextureId(25); // tee
				if (walls == (DIRECTION_E + DIRECTION_N + DIRECTION_W)) tile->setTextureId(26); // tee
				if (walls == (DIRECTION_N + DIRECTION_S + DIRECTION_W)) tile->setTextureId(27); // tee

				if (walls == (DIRECTION_N + DIRECTION_S)) tile->setTextureId(28); // straight
				if (walls == (DIRECTION_E + DIRECTION_W)) tile->setTextureId(29); // straight

				if (walls == (DIRECTION_N + DIRECTION_S + DIRECTION_W + DIRECTION_E)) tile->setTextureId(30); // cross

				if (walls == 0) tile->setTextureId(31); // single

			}
		}
	}


	return true;
}


void CMap::saveMap()
{
	// open the map file
	ofstream mapFile(mapFilename);

	// First line must be the tileset
	mapFile << tilesetFilename << endl << tileSize << endl;

	// Next is the width and height of the map
	mapFile << tileColumns << " " << tileRows << endl;

	// Next should be lines of tiles
	for (unsigned int row = 0; row < tileRows; row++)
	{
		for (unsigned int col = 0; col < tileColumns; col++)
		{
			CTile* tile = getTileAt(col, (tileRows - row - 1));
			switch (tile->getTypeId())
			{
			case TILE_TYPE_OPEN: mapFile << '.'; break;
			case TILE_TYPE_WALL: mapFile << '#'; break;
			}
		}
		mapFile << endl;
	}

	mapFile.close();
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


void CMap::onClick(int button, Vector2i mouseXY)
{
	int tileX = mouseXY.x/32;
	int tileY = mouseXY.y/32;
	CTile* t = getTileAt(tileX, tileY);
	if (button == GLUT_LEFT_BUTTON)
	{
		t->nextTextureId();
	} 
	else
	{
		t->previousTextureId();
	}
}


CTile* CMap::getTileAt(unsigned int x, unsigned int y)
{
	return tiles[((tileRows-y-1)*tileColumns) + x];
}


void CMap::setHighlightedTile(unsigned int x, unsigned int y)
{
	if (x > tileColumns - 1) x = tileColumns - 1;
	if (x < 0) x = 0;

	if (y > tileRows - 1) y = tileRows - 1;
	if (y < 0) y = 0;

	highlightedTile->x = x;
	highlightedTile->y = y;
}