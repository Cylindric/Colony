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
	unsigned long searchStartTime = SDL_GetTicks();
	if (currentState == SEARCH_STATE_SEARCHING) {
		unsigned long runningTime = (SDL_GetTicks() - searchStartTime);
		while((currentState == SEARCH_STATE_SEARCHING) && (runningTime < 10) ) {
			doSearchStep();
		}
	}

	if(SDL_GetTicks() > (this->lastMoveTime_ + 500)) {
		CTile* currentTile = CMap::MapControl.getTile(this->Position);
		CTile* targetTile = CMap::MapControl.getTile(this->Destination);

		// if the current destination is the same as the current tile, randomise a new target
		if ((currentTile->Coord == this->Destination)) {
			currentState = SEARCH_STATE_NOT_INITIALISED;
			CCoord nextCoord;
			do {
				nextCoord.X = (rand() % (CMap::MapControl.getWidth()-1));
				nextCoord.Y = (rand() % (CMap::MapControl.getHeight()-1));
				targetTile = CMap::MapControl.getTile(nextCoord);
			} while (targetTile->TypeID != TILE_TYPE_NORMAL);
			this->Destination = nextCoord;
			CTile* targetTile = CMap::MapControl.getTile(this->Destination);
		}

#ifdef DEBUG_RUN_AI_TESTS
		// AI tests
		long tStart = SDL_GetTicks();
		int tests = 10;
		unsigned int searchState;
		for (int i = 0; i < tests; i++) {
			this->Coord = CCoord(1,2);
			this->Destination = CCoord(3, 2);
			currentTile = CMap::MapControl.getTile(this->Coord);
			targetTile = CMap::MapControl.getTile(this->Destination);
			
			searchState = setSearchStates(currentTile, targetTile);
			while(searchState == SEARCH_STATE_SEARCHING) {
				// search until end
				searchState = searchStep();
			}
		}

		// check for solution
		if (searchState == SEARCH_STATE_SUCCEEDED) {
			CTile* node = getSolutionStart();
			while (node != NULL) {
				std::cout << node->Coord << ", ";
				node = getSolutionNext();
			}
			std::cout << std::endl;
		}

		long tDuration = SDL_GetTicks() - tStart;
		std::cout << "Test of " << tests << " A* loops took " << tDuration << "ms, " << (tDuration/tests) << " avg" << std::endl;
#endif


		if (currentState == SEARCH_STATE_NOT_INITIALISED) {
			setSearchStates(currentTile, targetTile);
		}

		if (currentState == SEARCH_STATE_SUCCEEDED) {
			CTile* node = getSolutionStart();
			if (node != NULL) {
				unsigned int s = 0;
				while (s <= currentPathStep_) {
					node = getSolutionNext();
					if (node != NULL) {
						Position = (*node).Coord;
					}
					s++;
				}
			}
			currentPathStep_++;
		}
		
		this->lastMoveTime_ = SDL_GetTicks();
	}

	// decorate the path
	//decorateClosedList();
	decorateFinalPath();

	(*this->DestinationCursor).Position.X = this->Destination.X;
	(*this->DestinationCursor).Position.Y = this->Destination.Y;
	Anim_Control.OnAnimate();
	(*this->DestinationCursor).OnLoop();
}


void CEntity_Buggy::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);
	(*this->DestinationCursor).OnRender(Surf_Display);
}
