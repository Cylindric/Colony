#pragma once
#include "Define.h"
#include "CEntity.h"

enum {
	TILE_TYPE_NONE = 0,
	TILE_TYPE_NORMAL,
	TILE_TYPE_BLOCK
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
