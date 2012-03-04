#pragma once

#include <SDL.h>
#include "CSurface.h"
#include "CEntity.h"
#include "CFPS.h"
#include "CCursor.h"

class CEntity_TargetCursor : public CEntity {

public:
	CEntity_TargetCursor();
	void OnLoop();
	bool OnLoad(SDL_Surface* Tileset);
};
