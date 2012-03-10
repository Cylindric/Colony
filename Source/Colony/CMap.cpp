#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <SDL.h>

#include "CMap.h"
#include "Define.h"
#include "CTile.h"
#include "CSurface.h"
#include "CFont.h"
#include "CEntity.h"
#include "CEntity_Buggy.h"


CMap CMap::MapControl;


CMap::CMap() {
	tileset_ = NULL;
}


bool CMap::onLoad(char* filename) {
	tileList_.clear();

	// open the map file
	std::ifstream mapFile(filename);

	// First line must be the tileset
	std::string tilesetFilename;
	mapFile >> tilesetFilename >> tileSize_ >> tileColumns_;
	if((tileset_ = CSurface::OnLoad((char*)tilesetFilename.c_str())) == false) {
		std::cerr << "Error loading map tileset";
		return false;
	}
	std::cout << "Tileset: " << tilesetFilename << std::endl;

	// Next is the width and height of the map
	mapFile >> width_ >> height_;
	std::cout << "Dimensions: " << width_ << "x" << height_ << std::endl;

	// Next should be lines of tiles
	int tileCount = 0;
	while (tileCount < (width_ * height_)) {
		int valA = 0;
		int valB = 0;
		char sep = ' ';

		mapFile >> valA >> sep >> valB;

		CTile* tempTile = new CTile();
		tempTile->Coord.X = (tileCount % width_);
		tempTile->Coord.Y = (tileCount / width_);
		tempTile->TileID = valA;
		tempTile->TypeID = valB;
		tileList_.push_back(tempTile);
		tileCount++;
	}

	// Next should be any entities
	while (mapFile.good()) {
		std::string objectName = "";
		int valA = 0;
		int valB = 0;
		int valC = 0;
		int valD = 0;

		mapFile >> objectName >> valA >> valB >> valC >> valD;
		if (objectName == "buggy") {
			CEntity_Buggy* ent = new CEntity_Buggy();
			ent->OnLoad();
			ent->Coord.X = valA;
			ent->Coord.Y = valB;
			ent->Destination.X = valC;
			ent->Destination.Y = valD;
			CTile* entTile = CMap::MapControl.getTile(ent->Coord);
			entTile->EntityList.push_back(ent);
			CEntity::EntityList.push_back(ent);
		}
	}

	mapFile.close();
	return true;
}


void CMap::onRender(SDL_Surface* Surf_Display, int MapX, int MapY) {
	if(tileset_ == NULL) return;

	int TilesetWidth = tileset_->w / tileSize_;
	int TilesetHeight = tileset_->h / tileSize_;

	int id = 0;

	std::vector<CTile*>::iterator i;
	for (i=this->tileList_.begin(); i!=this->tileList_.end(); ++i) {
		CTile* tile = *i;

        if(tile->TypeID == TILE_TYPE_NONE) {
            continue;
        }
 
		int tID = tile->TileID;
        int tX = MapX + (tile->Coord.X * tileSize_);
        int tY = MapY + (tile->Coord.Y * tileSize_);
 
        int TilesetX = (tID % tileColumns_) * tileSize_;
        int TilesetY = (tID / tileColumns_) * tileSize_;

        CSurface::OnDraw(Surf_Display, tileset_, tX, tY, TilesetX, TilesetY, tileSize_, tileSize_);

		// draw a grid
		if(SHOW_GRID) {
			CSurface::OnDraw(Surf_Display, tileset_, tX, tY, (GRID_TILE % tileColumns_)*tileSize_, (GRID_TILE / tileColumns_)*tileSize_, tileSize_, tileSize_);
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
		//	switch(tileList_[id].TypeID) {
		//	case TILE_TYPE_NORMAL: label[0] = '-'; break;
		//	case TILE_TYPE_BLOCK: label[0] = '#'; break;
		//	default: label[0] = 0; break;
		//	}
		//}

		// if there is a label to show, show it
		if(label[0] != 0) {
			CFont::FontControl.AddTextToSurface(Surf_Display, FONT_TILE, tX, tY, tX+tileSize_, tY+tileSize_, C, label);
		}

		// tile labels
		CFont::FontControl.AddTextToSurface(Surf_Display, FONT_TILE, tX, tY, tX+(tileSize_/2), tY+(tileSize_/2), C, tile->LTopLeft);
		CFont::FontControl.AddTextToSurface(Surf_Display, FONT_TILE, tX+(tileSize_/2), tY, tX+tileSize_, tY+(tileSize_/2), C, tile->LTopRight);
		CFont::FontControl.AddTextToSurface(Surf_Display, FONT_TILE, tX, tY+(tileSize_/2), tX+(tileSize_/2), tY+tileSize_, C, tile->LBottomLeft);
		CFont::FontControl.AddTextToSurface(Surf_Display, FONT_TILE, tX+(tileSize_/2), tY+(tileSize_/2), tX+tileSize_, tY+tileSize_, C, tile->LBottomRight);

		id++;
	}
}


void CMap::onCleanup() {
	tileList_.clear();
	SDL_FreeSurface(tileset_);
}


CTile* CMap::getTile(CCoord coord) {
	return getTile(coord.X, coord.Y);
}


CTile* CMap::getTile(int X, int Y) {
	return tileList_[(Y * width_)+X];
}


SDL_Surface* CMap::getTileset() {
	return tileset_;
}

int CMap::getTilesetColumns() {
	return tileColumns_;
}

int CMap::getTileSize() {
	return tileSize_;
}

int CMap::getWidth() {
	return width_;
}

int CMap::getHeight() {
	return height_;
}

std::vector<CTile*>* CMap::getTiles() {
	return &tileList_;
}