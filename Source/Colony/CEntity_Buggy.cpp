#include "CEntity_Buggy.h"

#include <iostream>
#include "Define.h"
#include "CEntity_TargetCursor.h"
#include "CTile.h"
#include "ATile.h"
#include "CMap.h"


CEntity_Buggy::CEntity_Buggy() {
	Destination = CCoord();
	lastMoveTime_ = SDL_GetTicks();
	DestinationCursor = new CEntity_TargetCursor();
	isValidPath_ = false;
	pathToDestination_.clear();
}


bool CEntity_Buggy::OnLoad() {
	bool rv = CEntity::OnLoad();
	(*this->DestinationCursor).OnLoad();
	this->Destination.X = -1;
	this->Destination.Y = -1;
	Anim_Control.SetLoop(30, 33);
	return rv;
}


void CEntity_Buggy::OnLoop() {
	if(SDL_GetTicks() > (this->lastMoveTime_ + 100)) {
		CTile* currentTile = CMap::MapControl.getTile(this->Coord);
		CTile* targetTile = CMap::MapControl.getTile(this->Destination);

		// decorate the tiles for testing
		for (std::vector<CTile*>::iterator itTile=CMap::MapControl.getTiles()->begin(); itTile!=CMap::MapControl.getTiles()->end(); ++itTile) {
			sprintf_s((*itTile)->Label, "");
		}

		// A* test
		if (this->isValidPath_ == false) {
			CalcRoute(currentTile, targetTile);
		}


		//std::list<ATile*>::iterator tile;
		//for (tile=openList_.begin(); tile!=openList_.end(); ++tile) {
		//	sprintf_s((*tile)->tile->LTopLeft, "%d", (*tile)->Fscore);
		//	sprintf_s((*tile)->tile->LBottomLeft, "%d", (*tile)->Gcost);
		//	sprintf_s((*tile)->tile->LBottomRight, "%d", (*tile)->Hcost);
		//	(*tile)->tile->TileID = 10;
		//	if((*tile)->parent->Coord.X == (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y <  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 1; //up
		//	if((*tile)->parent->Coord.X >  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y == (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 2; //right
		//	if((*tile)->parent->Coord.X == (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y >  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 3; //down
		//	if((*tile)->parent->Coord.X <  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y == (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 4; //left
		//	if((*tile)->parent->Coord.X <  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y <  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 5; //up-left
		//	if((*tile)->parent->Coord.X >  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y <  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 6; //up-right
		//	if((*tile)->parent->Coord.X >  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y >  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 7; //down-right
		//	if((*tile)->parent->Coord.X <  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y >  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 8; //down-left
		//}

		//for (tile=closedList_.begin(); tile!=closedList_.end(); ++tile) {
		//	sprintf_s((*tile)->tile->LTopLeft, "%d", (*tile)->Fscore);
		//	sprintf_s((*tile)->tile->LBottomLeft, "%d", (*tile)->Gcost);
		//	sprintf_s((*tile)->tile->LBottomRight, "%d", (*tile)->Hcost);
		//	(*tile)->tile->TileID = 20;
		//	if((*tile)->parent->Coord.X == (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y <  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 1; //up
		//	if((*tile)->parent->Coord.X >  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y == (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 2; //right
		//	if((*tile)->parent->Coord.X == (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y >  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 3; //down
		//	if((*tile)->parent->Coord.X <  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y == (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 4; //left
		//	if((*tile)->parent->Coord.X <  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y <  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 5; //up-left
		//	if((*tile)->parent->Coord.X a>  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y <  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 6; //up-right
		//	if((*tile)->parent->Coord.X >  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y >  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 7; //down-right
		//	if((*tile)->parent->Coord.X <  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y >  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 8; //down-left
		//}


		// highlight the path
		for(std::vector<CTile*>::iterator tile = this->pathToDestination_.begin(); tile!=this->pathToDestination_.end(); ++tile) {
			(*tile)->TileID = 2;
		}


		sprintf_s(currentTile->Label, "S");
		sprintf_s(currentTile->LTopLeft, "F");
		sprintf_s(currentTile->LBottomLeft, "G");
		sprintf_s(currentTile->LBottomRight, "H");

		this->lastMoveTime_ = SDL_GetTicks();
	}

	(*this->DestinationCursor).Coord.X = this->Destination.X;
	(*this->DestinationCursor).Coord.Y = this->Destination.Y;
	Anim_Control.OnAnimate();
	(*this->DestinationCursor).OnLoop();
}


void CEntity_Buggy::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);
	(*this->DestinationCursor).OnRender(Surf_Display);
}
