#ifndef _ATILE_H_
#define _ATILE_H_

// Forward declarations
class CTile;

// The actual class
class ATile {

public:
	ATile(void);
	ATile(CTile* Tile, CTile* Parent, int G, int H);
	~ATile(void);

public:
	CTile* tile;
	CTile* parent;
	int Gcost;
	int Hcost;
	int Fscore;
	bool operator==(const ATile &other) const;
	bool operator!=(const ATile &other) const;

};

#endif