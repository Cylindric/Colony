#pragma once
#include <vector>
#include <SDL.h>
#include "CCoord.h"
#include "CTile.h"
#include "Define.h"
#include "CSurface.h"
#include "CFont.h"

class CMap {

public: // constructor
	CMap();

public: // public properties
	static CMap MapControl;
	std::vector<CTile> TileList;
	int Width;
	int Height;

private: // private properties
	SDL_Surface* Surf_Tileset;

public: // public methods
	bool OnLoad(char* File);
	void OnRender(SDL_Surface* Surf_Display, int MapX, int MapY);
	void OnCleanup();

	CTile* GetTile(CCoord coord);
};
