#ifndef _CMAP_H_
#define _CMAP_H_

// Included dependencies
#include <vector>

// Forward declarations
class CEntity_Buggy;
struct SDL_Surface;
class CTile;
class CCoord;


class CMap {

public: // constructors
	CMap();

public: // public properties
	static CMap MapControl;

public: // public methods
	bool onLoad(char* filename);
	void onRender(SDL_Surface* displaySurface, int mapX, int mapY);
	void onCleanup();

	CTile* getTile(CCoord coord);
	CTile* getTile(int x, int y);
	int getTileSize();
	int getTilesetColumns();
	int getWidth();
	int getHeight();
	SDL_Surface* getTileset();
	std::vector<CTile*>* getTiles();

private: // private properties
	SDL_Surface* tileset_;
	std::vector<CTile*> tileList_;
	int tileSize_;
	int tileColumns_;
	int width_;
	int height_;

};

#endif