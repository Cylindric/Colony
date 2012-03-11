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

	if(SDL_GetTicks() > (this->lastMoveTime_ + 500)) {
		CTile* currentTile = CMap::MapControl.getTile(this->Coord);
		CTile* targetTile = CMap::MapControl.getTile(this->Destination);

#ifdef RUN_AI_TESTS
		// AI tests
		long tStart = SDL_GetTicks();
		int tests = 10;
		for (int i = 0; i < tests; i++) {
			this->Coord = CCoord(1,1);
			this->Destination = CCoord(5, 3);
			currentTile = CMap::MapControl.getTile(this->Coord);
			targetTile = CMap::MapControl.getTile(this->Destination);
			setSearchStates(currentTile, targetTile);
			while(searchStep() <= SEARCH_STATE_SEARCHING) {
				// search until end
			}
		}
		long tDuration = SDL_GetTicks() - tStart;
		std::cout << "Test of " << tests << " A* loops took " << tDuration << "ms, " << (tDuration/tests) << " avg" << std::endl;
#endif

		this->isValidPath_ = false; // force re-calc every loop
			// move to the next tile in the path
			//Coord = (*pathToDestination_.begin())->Coord;
		
			// remove the first tile from the path
			//pathToDestination_.erase(pathToDestination_.begin());
		//}
		this->lastMoveTime_ = SDL_GetTicks();
	}

	// decorate the path
	//decorateClosedList();
	decorateFinalPath();

	(*this->DestinationCursor).Coord.X = this->Destination.X;
	(*this->DestinationCursor).Coord.Y = this->Destination.Y;
	Anim_Control.OnAnimate();
	(*this->DestinationCursor).OnLoop();
}


void CEntity_Buggy::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);
	(*this->DestinationCursor).OnRender(Surf_Display);
}
