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
	if(SDL_GetTicks() > (this->lastMoveTime_ + 200)) {
		CTile* currentTile = CMap::MapControl.getTile(this->Coord);
		CTile* targetTile = CMap::MapControl.getTile(this->Destination);

		if (currentTile == targetTile) {
			// target reached, pick a new one
			bool keepSearching = true;
			while (keepSearching) {
				this->Destination.X = (rand() % CMap::MapControl.getWidth());
				this->Destination.Y = (rand() % CMap::MapControl.getHeight());
				targetTile = CMap::MapControl.getTile(this->Destination);
				if(targetTile->TypeID == TILE_TYPE_NORMAL) {
					keepSearching = false;
					isValidPath_ = false;
				}
			}

		} else {

			// Calculate route to target
			if (this->isValidPath_ == false) {
				CalcRoute(currentTile, targetTile);
			}

			// decorate the path
			//decorateClosedList();
			decorateFinalPath();

			// move to the next tile in the path
			Coord = (*pathToDestination_.begin())->Coord;
		
			// remove the first tile from the path
			pathToDestination_.erase(pathToDestination_.begin());
		}
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
