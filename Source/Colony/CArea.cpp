#include "CArea.h"

CArea CArea::AreaControl;

CArea::CArea() {
	AreaSize = 0;
}

bool CArea::OnLoad(SDL_Surface* Tileset) {
	if(Tileset == NULL) {
		return false;
	}
	Surf_Tileset = Tileset;

	MapList.clear();

	AreaSize = 4;
	for(int row = 0; row < AreaSize; row++) {
		for(int col = 0; col < AreaSize; col++) {
			CMap tmpMap;
			if(tmpMap.OnLoad(Surf_Tileset) == false) {
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
	FirstID = FirstID + ((-CameraY / MapHeight) * AreaSize);

	for(int i = 0; i < 4; i++) {
		unsigned int id = FirstID + ((i / 2) * AreaSize) + (i % 2);

		if(id < 0 || id >= MapList.size()) continue;

		int x = ((id % AreaSize) * MapWidth) + CameraX;
		int y = ((id / AreaSize) * MapHeight) + CameraY;

		MapList[id].OnRender(Surf_Display, x, y);
	}
}

void CArea::OnCleanup() {
	MapList.clear();
}