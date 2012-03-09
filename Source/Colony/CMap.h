#ifndef _CMAP_H_
#define _CMAP_H_

// Forward declared dependencies
class CEntity_Buggy;
struct SDL_Surface;
class CTile;
class CCoord;

// Included dependencies
#include <vector>

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