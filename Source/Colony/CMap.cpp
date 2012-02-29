#include "CMap.h"

CMap::CMap() {
	Surf_Tileset = NULL;
}

bool CMap::OnLoad(SDL_Surface* Tileset) {
	if(Tileset == NULL) {
		return false;
	}

	Surf_Tileset = Tileset;
	// default ground tiles
	int groundTiles[18] = {0, 1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15, 20, 21, 22, 23, 24, 25};

	TileList.clear();
	for(int Y = 0;Y < MAP_HEIGHT;Y++) {
		for(int X = 0;X < MAP_WIDTH;X++) {
			CTile tempTile;
			int r = (rand() % 18);
			tempTile.TileID = groundTiles[r];
			tempTile.TypeID = TILE_TYPE_NORMAL;
 			TileList.push_back(tempTile);
		}
	}
	return true;
}

void CMap::OnRender(SDL_Surface* Surf_Display, int MapX, int MapY) {
	if(Surf_Tileset == NULL) return;

	int TilesetWidth = Surf_Tileset->w / TILE_SIZE;
	int TilesetHeight = Surf_Tileset->h / TILE_SIZE;

	int id = 0;

    for(int Y = 0;Y < MAP_HEIGHT;Y++) {
        for(int X = 0;X < MAP_WIDTH;X++) {
            if(TileList[id].TypeID == TILE_TYPE_NONE) {
                id++;
                continue;
            }
 
            int tX = MapX + (X * TILE_SIZE);
            int tY = MapY + (Y * TILE_SIZE);
 
            int TilesetX = (TileList[id].TileID % TILESET_COLS) * TILE_SIZE;
            int TilesetY = (TileList[id].TileID / TILESET_COLS) * TILE_SIZE;
 
            CSurface::OnDraw(Surf_Display, Surf_Tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
 
            id++;
        }
    }

}