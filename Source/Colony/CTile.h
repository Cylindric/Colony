#pragma once

// Forward declared dependencies
class CEntity;

// Included dependencies
#include <vector>
#include "CCoord.h"


enum {
	TILE_TYPE_NONE = 0,
	TILE_TYPE_NORMAL = 1,
	TILE_TYPE_BLOCK = 2
};

class CTile {

public:
	std::vector<CEntity*> EntityList;
	int TileID;
	int TypeID;
	char Label[5];
	CCoord Coord;

	char LTopLeft[5];
	char LTopRight[5];
	char LBottomLeft[5];
	char LBottomRight[5];

public:
	CTile(void);

};
