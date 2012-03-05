#pragma once
#include <vector>
#include <SDL.h>
#include "CTile.h"
#include "CArea.h"
#include "Define.h"
#include "CMap.h"
#include "CSurface.h"
#include "CFont.h"

class CMap {

public:
	std::vector<CTile> TileList;

private:
	SDL_Surface* Surf_Tileset;
	int AreaX;
	int AreaY;

public:
	CMap();

public:
	bool OnLoad(char* File);
	void OnRender(SDL_Surface* Surf_Display, int MapX, int MapY);
};
