#pragma once
#include <SDL.h>
#include "CEntity.h"

class CEntity_TargetCursor : public CEntity {

public:
	CEntity_TargetCursor();
	void OnLoop();
	bool OnLoad(SDL_Surface* Tileset);
};
