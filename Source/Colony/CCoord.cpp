#include "CCoord.h"
#include <iostream>
#include <iomanip>

CCoord::CCoord(void)
{
	CCoord::CCoord(0,0);
}


CCoord::CCoord(int X, int Y)
{
	this->X = X;
	this->Y = Y;
}


bool CCoord::operator==(CCoord& rhs) {
	return ((this->X == rhs.X) && (this->Y == rhs.Y));
}


std::ostream& operator<<(std::ostream& output, const CCoord& p) {
	output << std::setw(2) << p.X << "," << std::setw(2) << p.Y;
	return output;
}