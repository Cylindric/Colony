#include "CArea.h"

CArea CArea::AreaControl;

CArea::CArea() {
}


int CArea::GetAreaSize() {
	return this->AreaSize;
}

SDL_Surface* CArea::GetTileSet() {
	return this->Surf_Tileset;
}


bool CArea::OnLoad(char* File) {
	MapList.clear();

	FILE* FileHandle;
	fopen_s(&FileHandle, File, "r");
	if(FileHandle == NULL) {
		return false;
	}

	// determine the tileset to use
	char TilesetFile[255];
	fscanf_s(FileHandle, "%s\n", TilesetFile);
	if((Surf_Tileset = CSurface::OnLoad(TilesetFile)) == false) {
		return false;
	}

	// determine the size of the area
	fscanf_s(FileHandle, "%d\n", &this->AreaSize);

	// read the maps
	for(int row = 0; row < this->AreaSize; row++) {
		for(int col = 0; col < this->AreaSize; col++) {
			// determine the map file
			char MapFile[255];
			fscanf_s(FileHandle, "%s ", MapFile);

			// read the map
			CMap tmpMap;
			if(tmpMap.OnLoad(MapFile) == false) {
				fclose(FileHandle);
				return false;
			}
			MapList.push_back(tmpMap);
		}
		fscanf_s(FileHandle, "\n");
	}
	fclose(FileHandle);
	return true;
}


void CArea::OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY) {
	int MapWidth = MAP_WIDTH * TILE_SIZE;
	int MapHeight = MAP_HEIGHT * TILE_SIZE;

	int FirstID = -CameraX / MapWidth;
	FirstID = FirstID + ((-CameraY / MapHeight) * this->AreaSize);

	int nHorizontalMaps = (CCamera::CameraControl.GetWidth()/(MAP_WIDTH*TILE_SIZE)) + 2;
	int nVerticalMaps = (CCamera::CameraControl.GetHeight()/(MAP_HEIGHT*TILE_SIZE)) + 2;
	for(int i = 0; i < nHorizontalMaps*nVerticalMaps; i++) {
		unsigned int id = FirstID + ((i / nHorizontalMaps) * this->AreaSize) + (i % nHorizontalMaps);

		if(id >= MapList.size()) continue;

		int x = ((id % this->AreaSize) * MapWidth) + CameraX;
		int y = ((id / this->AreaSize) * MapHeight) + CameraY;

		MapList[id].OnRender(Surf_Display, x, y);
	}
}


void CArea::OnCleanup() {
	MapList.clear();
}


CTile& CArea::GetTile(int X, int Y) {
	int mapX = (X/20);
	int mapY = (Y/20);
	int mapID = (this->AreaSize*mapY)+mapX;

	int tileX = X % 20;
	int tileY = Y % 20;
	int tileID = (MAP_WIDTH*tileY)+tileX;
	return MapList[mapID].TileList[tileID];
}