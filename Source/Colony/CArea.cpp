#include "CArea.h"

CArea CArea::AreaControl;

CArea::CArea() {
}

bool CArea::OnLoad(SDL_Surface* Tileset) {
	if(Tileset == NULL) {
		return false;
	}
	Surf_Tileset = Tileset;

	MapList.clear();

	for(int row = 0; row < AREA_SIZE; row++) {
		for(int col = 0; col < AREA_SIZE; col++) {
			CMap tmpMap;
			if(tmpMap.OnLoad(Surf_Tileset, col, row) == false) {
				return false;
			}
			MapList.push_back(tmpMap);
		}
	}
	return true;
}

void CArea::OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY) {
	int MapWidth = MAP_WIDTH * TILE_SIZE;
	int MapHeight = MAP_HEIGHT * TILE_SIZE;

	int FirstID = -CameraX / MapWidth;
	FirstID = FirstID + ((-CameraY / MapHeight) * AREA_SIZE);

	int nHorizontalMaps = (CCamera::CameraControl.GetWidth()/(MAP_WIDTH*TILE_SIZE)) + 2;
	int nVerticalMaps = (CCamera::CameraControl.GetHeight()/(MAP_HEIGHT*TILE_SIZE)) + 2;
	for(int i = 0; i < nHorizontalMaps*nVerticalMaps; i++) {
		unsigned int id = FirstID + ((i / nHorizontalMaps) * AREA_SIZE) + (i % nHorizontalMaps);

		if(id >= MapList.size()) continue;

		int x = ((id % AREA_SIZE) * MapWidth) + CameraX;
		int y = ((id / AREA_SIZE) * MapHeight) + CameraY;

		MapList[id].OnRender(Surf_Display, x, y);
	}
}

void CArea::OnCleanup() {
	MapList.clear();
}

CTile CArea::GetTile(int X, int Y) {
	int mapX = (X/20);
	int mapY = (Y/20);
	int mapID = (AREA_SIZE*mapY)+mapX;

	int tileX = X % 20;
	int tileY = Y % 20;
	int tileID = (MAP_WIDTH*tileY)+tileX;
	return MapList[mapID].TileList[tileID];
}