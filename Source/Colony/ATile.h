#ifndef _ATILE_H_
#define _ATILE_H_

// Forward declarations
class CTile;

// The actual class
class ATile {

public:
	ATile(void);
	~ATile(void);

public:
	CTile* tile;
	ATile* parent;
	ATile* child;
	int g;
	int h;
	int f;
};

std::ostream& operator<<(std::ostream& output, const ATile* p);

#endif