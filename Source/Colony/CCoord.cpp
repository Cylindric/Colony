#include "CCoord.h"
#include <iostream>

CCoord::CCoord(void)
{
	CCoord::CCoord(0,0);
}


CCoord::CCoord(int X, int Y)
{
	this->X = X;
	this->Y = X;
}

std::ostream& operator<<(std::ostream& output, const CCoord& p) {
	output << p.X << "," << p.Y;
	return output;
}