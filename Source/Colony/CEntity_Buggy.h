#pragma once

#include <SDL.h>
#include "CSurface.h"
#include "CEntity.h"
#include "CFPS.h"
#include "CEntity_TargetCursor.h"
#include "CArea.h"

class CEntity_Buggy : public CEntity {

public:
	CEntity_Buggy();
	void OnLoop();
	bool OnLoad(SDL_Surface* Tileset);
	void OnRender(SDL_Surface* Surf_Display);

private:
	float Speed;
	int DestinationX;
	int DestinationY;
	int testD;
	unsigned long LastMove;

	CEntity_TargetCursor DestinationCursor;
};

