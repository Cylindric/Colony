#pragma once
#include <vector>
#include "CEntity.h"

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
	char Label[1];

public:
	CTile(void);

};
