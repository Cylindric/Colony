#ifndef _CMAP_H_
#define _CMAP_H_

// Forward declared dependencies

// Included dependencies
#include <vector>
#include <SDL.h>
#include "Define.h"
#include "CTile.h"
#include "CSurface.h"
#include "CFont.h"
#include "CEntity.h"
//#include "CEntity_Buggy.h"

class CMap {

public: // constructor
	CMap();

public: // public properties
	static CMap MapControl;
	std::vector<CTile*> TileList;
	int Width;
	int Height;

private: // private properties
	SDL_Surface* Surf_Tileset;

public: // public methods
	bool OnLoad(char* File);
	void OnRender(SDL_Surface* Surf_Display, int MapX, int MapY);
	void OnCleanup();

	CTile* GetTile(CCoord coord);
	CTile* GetTile(int X, int Y);
	SDL_Surface* GetTileset();
};

#endif