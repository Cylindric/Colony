#ifndef _CTILE_H_
#define _CTILE_H_

// Included dependencies
#include <vector>
#include <string>
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
	std::wstring Label;
	CCoord Coord;

	std::wstring LTopLeft;
	std::wstring LTopRight;
	std::wstring LBottomLeft;
	std::wstring LBottomRight;

public:
	CTile(void);

};

#endif
