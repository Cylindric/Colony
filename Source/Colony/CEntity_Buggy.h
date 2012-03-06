#pragma once

// Forward declared dependencies

// Included dependencies
#include <iostream>
#include <direct.h>
#include <list>
#include <algorithm>
#include <SDL.h>
#include "Define.h"
#include "CEntity.h"
#include "CEntity_TargetCursor.h"
#include "CCoord.h"
#include "ATile.h"

// The class
class CEntity_Buggy : public CEntity {

public:
	CEntity_Buggy();
	void OnLoop();
	bool OnLoad();
	void OnRender(SDL_Surface* Surf_Display);
	CCoord Destination;

private:
	float Speed;

	int testD;
	unsigned long LastMove;

	CEntity_TargetCursor DestinationCursor;
	int CostToDestination();

	int IterationCap;
	void CalcRoute(std::list<ATile*> &openList, std::list<ATile*> &closedList, CTile* StartNode, CTile* EndNode);
	int GetHeuristic(CCoord A, CCoord B);
	ATile* GetLowestF(std::list<ATile*> List);
	ATile* FindTileOnList(std::list<ATile*> List, CTile* Tile);
};
