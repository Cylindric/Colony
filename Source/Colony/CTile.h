#ifndef _CTILE_H_
#define _CTILE_H_

// Included dependencies
#include <vector>
#include "CCoord.h"

// Forward declarations
class CEntity;


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

#endif
