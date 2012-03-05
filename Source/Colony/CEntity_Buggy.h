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

// The class
class CEntity_Buggy : public CEntity {

public:
	CEntity_Buggy();
	void OnLoop();
	bool OnLoad();
	void OnRender(SDL_Surface* Surf_Display);

private:
	float Speed;
	CCoord Destination;

	int testD;
	unsigned long LastMove;

	CEntity_TargetCursor DestinationCursor;
	int CostToDestination();
};
