#ifndef _CCOORD_H_
#define _CCOORD_H_

#include <iostream>

class CCoord {
public:
	CCoord(void);
	CCoord(int X, int Y);
	
	int X;
	int Y;

};

std::ostream& operator<<(std::ostream& output, const CCoord& p);

#endif