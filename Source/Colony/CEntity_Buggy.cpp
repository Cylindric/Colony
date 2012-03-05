#include "CEntity_Buggy.h"
#include <iostream>
#include <direct.h>


CEntity_Buggy::CEntity_Buggy() {
	this->Speed = 1;
	this->Destination = CCoord();
	this->LastMove = SDL_GetTicks();
	this->testD = 1;
}


bool CEntity_Buggy::OnLoad(SDL_Surface* Tileset) {
	bool rv = CEntity::OnLoad(Tileset);
	this->DestinationCursor.OnLoad(Tileset);
	this->Destination.X = 15;
	this->Destination.Y = 10;
	Anim_Control.SetLoop(30, 33);
	return rv;
}


void CEntity_Buggy::OnLoop() {
	//std::list<ATile> openList;
	//std::list<ATile> closedList;

	//if(SDL_GetTicks() > (this->LastMove + 1000)) {
	//	CTile& currentTile = CArea::AreaControl.GetTile(this->X, this->Y);

	//	// decorate the tiles for testing
	//	for (std::vector<CMap>::iterator itMap=CArea::AreaControl.MapList.begin(); itMap!=CArea::AreaControl.MapList.end(); ++itMap) {
	//		for (std::vector<CTile>::iterator itTile=itMap->TileList.begin(); itTile!=itMap->TileList.end(); ++itTile) {
	//			sprintf_s(itTile->Label, "-");
	//		}
	//	}

	//	// pop a footprint on the current tile

	//	// A* test
	//	openList.clear();
	//	closedList.clear();

	//	// Start the Open List
	//	ATile rootTile;
	//	rootTile.tile = &currentTile;
	//	rootTile.parent = &currentTile;
	//	rootTile.Gcost = 0;
	//	rootTile.Hcost = 1 * std::max(abs(this->X - this->DestinationX), abs(this->Y - this->DestinationY));
	//	rootTile.Fscore = rootTile.Gcost + rootTile.Hcost;
	//	openList.push_back(rootTile);

	//	// Add neighbours
	//	for(int row = this->Y - 1; row <= this->Y + 1; row++) {
	//		for(int col = this->X - 1; col <= this->X + 1; col++) {
	//			std::cerr<<"testing row "<<row<<", col "<<col<<"\n";

	//			if(row == this->Y && col == this->X) continue; // skip current cell

	//			CTile& neighbour = CArea::AreaControl.GetTile(col, row);
	//			if(neighbour.TypeID == TILE_TYPE_NORMAL) {
	//				ATile tmpTile;
	//				tmpTile.tile = &neighbour;
	//				tmpTile.parent = &currentTile;

	//				// calculate G - the cost to get to neighbour from currentCell
	//				tmpTile.Gcost = rootTile.Gcost + 1; // all cells are '1' away

	//				// calculate H - the cost to the destination from the neighbour
	//				tmpTile.Hcost = 1 * std::max(abs(col - this->DestinationX), abs(row - this->DestinationY));

	//				// calculate F
	//				tmpTile.Fscore = tmpTile.Gcost + tmpTile.Hcost;

	//				openList.push_back(tmpTile);
	//			}
	//		}
	//	}
	//	openList.remove(rootTile);
	//	closedList.push_back(rootTile);

	//	// find lowest-F open tile
	//	int lowestF = -1;
	//	ATile* lowestTile = NULL;

	//	for (std::list<ATile>::iterator tile=openList.begin(); tile!=openList.end(); ++tile) {
	//		if(lowestF == -1 || tile->Fscore < lowestF) {
	//			lowestTile = &*tile;
	//		}
	//	}
	//	closedList.push_back(*lowestTile);
	//	openList.remove(*lowestTile);


	//	for (std::list<ATile>::iterator tile=openList.begin(); tile!=openList.end(); ++tile) {
	//		sprintf_s(tile->tile->Label, "O%d", tile->Fscore);
	//	}

	//	for (std::list<ATile>::iterator tile=closedList.begin(); tile!=closedList.end(); ++tile) {
	//		sprintf_s(tile->tile->Label, "C%d", tile->Fscore);
	//	}

	//	sprintf_s(lowestTile->tile->Label, "H%d", lowestTile->Fscore);


	//	std::cerr<<"\n";


	//	//currentTile.Label[0] = 'o';
	//	//sprintf_s(currentTile.Label, "%i", this->CostToDestination());

	//	int nextX = this->X;// + this->testD;
	//	CTile destinationTile = CArea::AreaControl.GetTile(this->DestinationX, this->DestinationY);
	//	if(destinationTile.TypeID == TILE_TYPE_BLOCK) {
	//		nextX = this->X;
	//		this->testD = -this->testD;
	//	}

	//	this->X = nextX;
	//	this->LastMove = SDL_GetTicks();
	//}

	//this->DestinationCursor.X = this->DestinationX;
	//this->DestinationCursor.Y = this->DestinationY;
	//Anim_Control.OnAnimate();
	//this->DestinationCursor.OnLoop();
}


void CEntity_Buggy::OnRender(SDL_Surface* Surf_Display) {
//	CEntity::OnRender(Surf_Display);
	this->DestinationCursor.OnRender(Surf_Display);
}


int CEntity_Buggy::CostToDestination() {
	int cost = 0;
	cost = 1 * std::max(abs(this->Coord.X - this->Destination.X), abs(this->Coord.Y - this->Destination.Y));
	return cost;
}