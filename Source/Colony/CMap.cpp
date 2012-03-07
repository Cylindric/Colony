#include "CMap.h"

CMap CMap::MapControl;


CMap::CMap() {
	Surf_Tileset = NULL;
}


bool CMap::OnLoad(char* File) {
	TileList.clear();
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

	// determine the X and Y dimensions of the map
	fscanf_s(FileHandle, "%d %d\n", &this->Width, &this->Height);

	// read in all the cells
	for(int Y = 0; Y < this->Height; Y++) {
		for(int X = 0; X < this->Width; X++) {
			CTile tempTile;
			tempTile.Coord.X = X;
			tempTile.Coord.Y = Y;
			fscanf_s(FileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);
			TileList.push_back(tempTile);
		}
		fscanf_s(FileHandle, "\n");
	}

	// read any extra commands
	char EntityName[255];
	int EntityPosX;
	int EntityPosY;
	int EntityTarX;
	int EntityTarY;

	bool getEnts = true;
	while (getEnts) {
		int c = fscanf_s(FileHandle, "%s %d %d %d %d\n", &EntityName, &EntityPosX, &EntityPosY, &EntityTarX, &EntityTarY);
		if (c == EOF) {
			getEnts = false;
		} else {
			if (EntityName == "buggy") {
				CEntity_Buggy ent;
				ent.OnLoad();
				ent.Coord.X = EntityPosX;
				ent.Coord.Y = EntityPosY;
				ent.Destination.X = EntityTarX;
				ent.Destination.Y = EntityTarY;
				CTile* entTile = CMap::MapControl.GetTile(ent.Coord);
				entTile->EntityList.push_back(&ent);
				CEntity::EntityList.push_back(&ent);
			}
		}
	}

	fclose(FileHandle);
	return true;
}


void CMap::OnRender(SDL_Surface* Surf_Display, int MapX, int MapY) {
	if(Surf_Tileset == NULL) return;

	int TilesetWidth = Surf_Tileset->w / TILE_SIZE;
	int TilesetHeight = Surf_Tileset->h / TILE_SIZE;

	int id = 0;

	for (std::vector<CTile>::iterator i=this->TileList.begin(); i!=this->TileList.end(); ++i) {
		CTile* tile = &*i;

        if(tile->TypeID == TILE_TYPE_NONE) {
            continue;
        }
 
		int tID = tile->TileID;
        int tX = MapX + (tile->Coord.X * TILE_SIZE);
        int tY = MapY + (tile->Coord.Y * TILE_SIZE);
 
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
		char label[10] = "";
		label[0]=0;

		// check for any lables from resident entities
		for(unsigned int i = 0; i < tile->EntityList.size(); i++) {
			if (tile->EntityList[i]->Label[0] != 0) {
				label[0] = tile->EntityList[i]->Label[0];
			}
		}

		// check for a label on the tile itself
		if(label[0] == 0) {
			sprintf_s(label, "%s", tile->Label);
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

		// tile labels
		CFont::FontControl.AddTextToSurface(Surf_Display, FONT_TILE, tX, tY, tX+(TILE_SIZE/2), tY+(TILE_SIZE/2), C, tile->LTopLeft);
		CFont::FontControl.AddTextToSurface(Surf_Display, FONT_TILE, tX+(TILE_SIZE/2), tY, tX+TILE_SIZE, tY+(TILE_SIZE/2), C, tile->LTopRight);
		CFont::FontControl.AddTextToSurface(Surf_Display, FONT_TILE, tX, tY+(TILE_SIZE/2), tX+(TILE_SIZE/2), tY+TILE_SIZE, C, tile->LBottomLeft);
		CFont::FontControl.AddTextToSurface(Surf_Display, FONT_TILE, tX+(TILE_SIZE/2), tY+(TILE_SIZE/2), tX+TILE_SIZE, tY+TILE_SIZE, C, tile->LBottomRight);

		id++;
	}
}


void CMap::OnCleanup() {
	this->TileList.clear();
	SDL_FreeSurface(this->Surf_Tileset);
}


CTile* CMap::GetTile(CCoord coord) {
	return this->GetTile(coord.X, coord.Y);
}


CTile* CMap::GetTile(int X, int Y) {
	return &this->TileList[(Y * this->Width)+X];
}


SDL_Surface* CMap::GetTileset() {
	return this->Surf_Tileset;
}