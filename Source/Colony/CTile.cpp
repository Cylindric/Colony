#include "CTile.h"

CTile::CTile(void) {
	TileID = 0;
	TypeID = TILE_TYPE_NONE;
	Label[0] = 0;
}


ATile::ATile(void) {
}

bool ATile::operator==(const ATile &other) const {
	return (this->parent == other.parent) && (this->tile == other.tile);
}


bool ATile::operator!=(const ATile &other) const {
	return !(*this == other);
}

