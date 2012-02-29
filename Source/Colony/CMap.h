#pragma once
#include <SDL.h>
#include <vector>
#include "CTile.h"
#include "CSurface.h"
#include "Define.h"

class CMap {

private:
	std::vector<CTile> TileList;
	SDL_Surface* Surf_Tileset;

public:
	CMap();

public:
	bool OnLoad(SDL_Surface* Tileset);
	void OnRender(SDL_Surface* Surf_Display, int MapX, int MapY);
};
