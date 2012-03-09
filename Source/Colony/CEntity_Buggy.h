#ifndef _CENTITY_BUGGY_H_
#define _CENTITY_BUGGY_H_

// Included dependencies
#include "CEntity.h"
#include <list>

// Forward declared dependencies
class ATile;
class CTile;
class CEntity_TargetCursor;

// The class
class CEntity_Buggy : public CEntity {

public:
	CEntity_Buggy();
	void OnLoop();
	bool OnLoad();
	void OnRender(SDL_Surface* Surf_Display);
	CCoord Destination;

private:
	bool ValidPath;
	std::vector<CTile*> PathToDestination;
	unsigned long LastMove;

	CEntity_TargetCursor* DestinationCursor;
	int CostToDestination();

	int IterationCap;
	void CalcRoute(std::list<ATile*> &openList, std::list<ATile*> &closedList, CTile* StartNode, CTile* EndNode);
	int GetHeuristic(CCoord A, CCoord B);
	ATile* GetLowestF(std::list<ATile*> List);
	ATile* FindTileOnList(std::list<ATile*> List, CTile* Tile);
};

#endif