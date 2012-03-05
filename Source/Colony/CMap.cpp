#include "CMap.h"

CMap::CMap() {
	Surf_Tileset = NULL;
}


bool CMap::OnLoad(char* File) {
	this->Surf_Tileset = CArea::AreaControl.GetTileSet();
	this->AreaX = AreaX;
	this->AreaY = AreaY;

	TileList.clear();
	FILE* FileHandle;
	fopen_s(&FileHandle, File, "r");
	if(FileHandle == NULL) {
		return false;
	}

	int inType = 0;
	int inTile = 0;

	for(int Y = 0; Y < MAP_HEIGHT; Y++) {
		for(int X = 0; X < MAP_WIDTH; X++) {
			fscanf_s(FileHandle, "%d:%d ", &inTile, &inType);

			CTile tempTile;
			tempTile.TileID = inTile;
			tempTile.TypeID = inType;

			TileList.push_back(tempTile);
		}
		fscanf_s(FileHandle, "\n");
	}
	fclose(FileHandle);
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
 
			int tID = TileList[id].TileID;
            int tX = MapX + (X * TILE_SIZE);
            int tY = MapY + (Y * TILE_SIZE);
 
            int TilesetX = (tID % TILESET_COLS) * TILE_SIZE;
            int TilesetY = (tID / TILESET_COLS) * TILE_SIZE;

            CSurface::OnDraw(Surf_Display, Surf_Tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);

			// draw a grid
			if(SHOW_GRID) {
				CSurface::OnDraw(Surf_Display, Surf_Tileset, tX, tY, (GRID_TILE % TILESET_COLS)*TILE_SIZE, (GRID_TILE / TILESET_COLS)*TILE_SIZE, TILE_SIZE, TILE_SIZE);
			}

			// labels
			SDL_Color C;
			C.r = 255;
			C.g = 255;
			C.b = 255;
			char label[] = " ";
			label[0]=0;

			// check for any lables from resident entities
			for(unsigned int i = 0; i < TileList[id].EntityList.size(); i++) {
				if (TileList[id].EntityList[i]->Label[0] != 0) {
					label[0] = TileList[id].EntityList[i]->Label[0];
				}
			}

			// check for a label on the tile itself
			if(label[0] == 0) {
				label[0] = TileList[id].Label[0];
			}

			// if no entity labels, check for labels for the tile-type
			//if(label[0] == 0) {
			//	switch(TileList[id].TypeID) {
			//	case TILE_TYPE_NORMAL: label[0] = '-'; break;
			//	case TILE_TYPE_BLOCK: label[0] = '#'; break;
			//	default: label[0] = 0; break;
			//	}
			//}

			// if there is a label to show, show it
			if(label[0] != 0) {
				CFont::FontControl.AddTextToSurface(Surf_Display, FONT_TILE, tX, tY, tX+TILE_SIZE, tY+TILE_SIZE, C, label);
			}
            id++;
        }
    }

}