#pragma once
#include <vector>
#include <SDL.h>
#include "CMap.h"
#include "CTile.h"
#include "CCamera.h"

class CMap;

class CArea {

public:
	static CArea AreaControl;

public:
	std::vector<CMap> MapList;

private:
	SDL_Surface* Surf_Tileset;
	int AreaSize;

public:
	CArea();
	bool OnLoad(char* File);
	void OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY);
	void OnCleanup();
	CTile& GetTile(int X, int Y);
	int GetAreaSize();
	SDL_Surface* GetTileSet();
};
