#include <stdio.h>
#include "CTile.h"

CTile::CTile(void) {
	this->TileID = 0;
	this->TypeID = TILE_TYPE_NONE;
	this->Label[0] = 0;
	this->Coord = CCoord();

	this->LTopLeft[0] = 0;
	this->LTopRight[0] = 0;
	this->LBottomLeft[0] = 0;
	this->LBottomRight[0] = 0;
}


std::ostream& operator<<(std::ostream& output, const CTile& p) {
	output << p.Coord;
	return output;
}