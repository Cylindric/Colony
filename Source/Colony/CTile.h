#pragma once
#include <vector>
#include "CEntity.h"
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

public:
	CTile(void);

};


class ATile {
public:
	ATile(void);
	CTile* tile;
	CTile* parent;
	int Gcost;
	int Hcost;
	int Fscore;
	bool operator==(const ATile &other) const;
	bool operator!=(const ATile &other) const;
};