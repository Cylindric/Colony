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
	int AreaX;
	int AreaY;

public:
	CMap();

public:
	bool OnLoad(SDL_Surface* Tileset, int AreaX, int AreaY);
	void OnRender(SDL_Surface* Surf_Display, int MapX, int MapY);
};
