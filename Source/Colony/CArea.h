#pragma once
#include "CMap.h"
#include "CCamera.h"

class CArea {

public:
	static CArea AreaControl;

public:
	std::vector<CMap> MapList;

private:
	SDL_Surface* Surf_Tileset;

public:
	CArea();
	bool OnLoad(SDL_Surface* Tileset);
	void OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY);
	void OnCleanup();
};
