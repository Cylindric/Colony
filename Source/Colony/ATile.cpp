#include "ATile.h"


ATile::ATile(void)
{
	this->Fscore = 0;
	this->Gcost = 0;
	this->Hcost = 0;
	this->parent = 0;
	this->tile = 0;
}


ATile::~ATile(void)
{
	this->parent = 0;
	this->tile = 0;
}


bool ATile::operator==(const ATile &other) const {
	return (this->parent == other.parent) && (this->tile == other.tile);
}


bool ATile::operator!=(const ATile &other) const {
	return !(*this == other);
}
