#include <stdio.h>
#include <iostream>
#include "ATile.h"
#include "CTile.h"

ATile::ATile(void)
{
	this->f = 0;
	this->g = 0;
	this->h = 0;
	this->parent = NULL;
	this->tile = 0;
	this->child = NULL;
}


ATile::~ATile(void)
{
	this->parent = NULL;
	this->tile = 0;
	this->child = NULL;
}


std::ostream& operator<<(std::ostream& output, const ATile* p) {
	output << "T:";
	if (p->tile == NULL) {
		output << "No Tile";
	} else {
		output << "<" << p->tile->Coord << ">";
	}

	output << " P:";
	if (p->parent == NULL) {
		output << "No parent";
	} else {
		output << "<" << p->parent->tile->Coord << ">";
	}

	output << " C:";
	if (p->child == NULL) {
		output << "No child";
	} else {
		output << "<" << p->child->tile->Coord << ">";
	}

	return output;
}