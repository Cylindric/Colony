#pragma once
#include <SDL.h>
#include <list>
#include <algorithm>
#include "CEntity.h"
#include "CEntity_TargetCursor.h"
#include "Define.h"
#include "CCoord.h"

class CEntity_Buggy : public CEntity {

public:
	CEntity_Buggy();
	void OnLoop();
	bool OnLoad(SDL_Surface* Tileset);
	void OnRender(SDL_Surface* Surf_Display);

private:
	float Speed;
	CCoord Destination;

	int testD;
	unsigned long LastMove;

	CEntity_TargetCursor DestinationCursor;
	int CostToDestination();
};
