#include <stdio.h>
#include "ATile.h"


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
