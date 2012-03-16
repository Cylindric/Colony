// includes
#include "Map.h"
#include "Tile.h"


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


void CMap::onInit(void)
{
	tiles.clear();
	unsigned int rows = 100;
	unsigned int cols = 100;
	for (unsigned int row = 0; row < rows; row++) {
		for (unsigned int col = 0; col < cols; col++) {
			CTile* tile = new CTile(col, row, ((row*cols)+col)%6);
			tiles.push_back(tile);
		}
	} 
}


void CMap::onRender(GLuint texture)
{
	for (vector<CTile*>::iterator t = tiles.begin(); t < tiles.end(); t++)
	{
		(*t)->onRender(texture);
	}
}
