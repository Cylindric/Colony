#include "ATile.h"


ATile::ATile(void)
{
	this->f = 0;
	this->g = 0;
	this->h = 0;
	this->parent = 0;
	this->tile = 0;
}

ATile::ATile(CTile* Tile, CTile* Parent, int G, int H)
{
	this->tile = Tile;
	this->parent = Parent;
	this->g = G;
	this->h = H;
	this->f = G + H;
}


ATile::~ATile(void)
{
	this->parent = 0;
	this->tile = 0;
}
