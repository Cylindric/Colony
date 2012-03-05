#include "CTile.h"

CTile::CTile(void) {
	this->TileID = 0;
	this->TypeID = TILE_TYPE_NONE;
	this->Label[0] = 0;
	this->Coord = CCoord();
}

/*
ATile::ATile(void) {
}


bool ATile::operator==(const ATile &other) const {
	return (this->parent == other.parent) && (this->tile == other.tile);
}


bool ATile::operator!=(const ATile &other) const {
	return !(*this == other);
}
*/