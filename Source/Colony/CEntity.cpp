#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include "CEntity.h"
#include "CMap.h"
#include "ATile.h"
#include "CTile.h"
#include "CCamera.h"
#include "CSurface.h"

std::vector<CEntity*> CEntity::EntityList;

class HeapCompare_f {
public:
	bool operator() ( const ATile* x, const ATile* y ) const {
		return x->f > y->f;
	}
};


CEntity::CEntity() {
	this->EntityTileset = NULL;
	this->Coord = CCoord();
	this->SpriteWidth = CMap::MapControl.getTileSize();
	this->SpriteHeight = CMap::MapControl.getTileSize();
	this->AnimState = 0;
	this->Label[0] = 0;
	currentState = SEARCH_STATE_NOT_INITIALISED;
}


CEntity::~CEntity() {
}


bool CEntity::OnLoad() {
	this->EntityTileset = CMap::MapControl.getTileset();
	return true;
}


void CEntity::OnLoop() {
	Anim_Control.OnAnimate();
}


void CEntity::OnRender(SDL_Surface* Surf_Display) {
	if(this->EntityTileset == NULL || Surf_Display == NULL) return;

	// calculate the 'real' position on the view
	int screenX = ((this->Coord.X * CMap::MapControl.getTileSize()) + CCamera::CameraControl.GetX());
	int screenY = ((this->Coord.Y * CMap::MapControl.getTileSize()) + CCamera::CameraControl.GetY());

	// if the sprite is off-camera, don't bother drawing it
	if((screenX + SpriteWidth < 0) || (screenY + SpriteHeight < 0)) return;
	if((screenX - SpriteWidth > CCamera::CameraControl.GetWidth()) || (screenY - SpriteHeight > CCamera::CameraControl.GetWidth())) return;

	int cell = Anim_Control.GetCurrentFrame();
    int cellX = (cell % CMap::MapControl.getTilesetColumns()) * CMap::MapControl.getTileSize();
    int cellY = (cell / CMap::MapControl.getTilesetColumns()) * CMap::MapControl.getTileSize();

	CSurface::OnDraw(Surf_Display, this->EntityTileset, screenX, screenY, cellX, cellY, SpriteWidth, SpriteHeight);
}

void CEntity::OnCleanup() {
}


unsigned int CEntity::setSearchStates(CTile* start, CTile* goal) {
	openList_.clear();
	closedList_.clear();
	pathToDestination_.clear();
	startTile_ = new ATile();
	goalTile_ = new ATile();

	startTile_->tile = start;
	goalTile_->tile = goal;

	currentState = SEARCH_STATE_SEARCHING;

	startTile_->g = 0;
	startTile_->h = GetHeuristic(start->Coord, goal->Coord);
	startTile_->f = startTile_->g + startTile_->h;
	startTile_->parent = NULL;
	openList_.push_back(startTile_);
	std::push_heap(openList_.begin(), openList_.end(), HeapCompare_f());
	stepCount_ = 0;

	return currentState;
}


unsigned int CEntity::searchStep() {
	// A* help from http://www.policyalmanac.org/games/aStarTutorial.htm
	// More help from http://code.google.com/p/a-star-algorithm-implementation/source/browse/trunk/stlastar.h

	bool Finished = false;
	int Iteration = 0; // for tracking the loop-count and bailing out early - mostly for visualisation reasons
	int newG = 0;
	long startTime = SDL_GetTicks();

	// break if not initialised
	assert( (currentState > SEARCH_STATE_NOT_INITIALISED) && (currentState < SEARCH_STATE_INVALID) );

	// just return if the search is already finished or failed
	if (currentState == SEARCH_STATE_SUCCEEDED || currentState == SEARCH_STATE_FAILED) {
		return currentState;
	}

	// if the open list is empty, we're done
	if (openList_.empty()) {
		FreeAllNodes();
		currentState = SEARCH_STATE_FAILED;
		return currentState;
	}

	stepCount_++;


	// Find the tile with the lowest F in the Open List
	ATile* currentTile = openList_.front();
	std::pop_heap(openList_.begin(), openList_.end(), HeapCompare_f());
	openList_.pop_back();

	if(currentTile->tile == goalTile_->tile) {
		std::cout << "Current ATile: " << currentTile << std::endl;
		goalTile_->parent = currentTile;

		if (currentTile->tile != startTile_->tile) {
			///FreeNode(currentTile);
			ATile* nodeChild = goalTile_;
			ATile* nodeParent = goalTile_->parent;
			do {
				//std::cout << "T:" << nodeChild->tile->Coord;
				//std::cout << " P:" << nodeParent->tile->Coord;

				nodeParent->child = nodeChild;
				nodeChild = nodeParent;
				nodeParent = nodeParent->parent;
			} while (nodeChild != startTile_);
		}

		FreeUnusedNodes();

		currentState = SEARCH_STATE_SUCCEEDED;
		return currentState;

	} else {

		AddSuccessors(currentTile);
		for (std::vector<ATile*>::iterator successor = successorList_.begin(); successor != successorList_.end(); successor++) {

			if ((*successor)->tile->Coord.Y == currentTile->tile->Coord.Y || (*successor)->tile->Coord.X == currentTile->tile->Coord.X) {
				newG = currentTile->g + COST_STRAIGHT; // perpendicular tiles
			} else {
				newG = currentTile->g + COST_DIAGONAL; // diagonal tiles
			}

			// is it on the Open List?
			std::vector<ATile*>::iterator openListResult;
			for (openListResult = openList_.begin(); openListResult != openList_.end(); openListResult++) {
				if ( (*openListResult)->tile == (*successor)->tile ) {
					break;
				}
			}
			if (openListResult != openList_.end()) {
				// already on open list
				if ((*openListResult)->g <= newG) {
					// the current G in the open list is better than this one
					FreeNode((*successor));
					continue;
				}
			}

			// is it on the Closed list?
			std::vector<ATile*>::iterator closedListResult;
			for (closedListResult = closedList_.begin(); closedListResult != closedList_.end(); closedListResult++) {
				if ( (*closedListResult)->tile == (*successor)->tile ) {
					break;
				}
			}
			if (closedListResult != closedList_.end()) {
				// on closed list
				if((*closedListResult)->g <= newG) {
					// the current G in the closed list is better than this one
					FreeNode((*successor));
					continue;
				}
			}

			// To get here, the current node is better than any open or closed nodes
			(*successor)->parent = currentTile;
			(*successor)->g = newG;
			(*successor)->h = GetHeuristic((*successor)->tile->Coord, goalTile_->tile->Coord);
			(*successor)->f = (*successor)->g + (*successor)->h;

			// if the current tile is on the closed list, remove it
			if (closedListResult != closedList_.end()) {
				FreeNode((*closedListResult));
				closedList_.erase(closedListResult);
			}

			// if the current tile is on the open list already, remove it (it will be added back in the correct place later
			if (openListResult != openList_.end()) {
				FreeNode((*openListResult));
				openList_.erase(openListResult);
				std::make_heap(openList_.begin(), openList_.end(), HeapCompare_f());
			}

			// push the current tile onto the open list (which unsorts the heap, so resort it)
			openList_.push_back((*successor));
			std::push_heap(openList_.begin(), openList_.end(), HeapCompare_f());
		}

		// current tile has now been expanded, so close it
		closedList_.push_back(currentTile);
	}
	return currentState;
}


CTile* CEntity::getSolutionStart() {
	currentSolutionNode_ = startTile_;
	if (currentSolutionNode_) {
		return currentSolutionNode_->tile;
	} else {
		return NULL;
	}
}


CTile* CEntity::getSolutionNext() {
	if (currentSolutionNode_) {
		if (currentSolutionNode_->child) {
			ATile* child = currentSolutionNode_->child;
			return child->tile;
		}
	}
	return NULL;
}


void CEntity::FreeAllNodes() {
	std::vector<ATile*>::iterator i;
	
	i = openList_.begin();
	while (i != openList_.end()) {
		ATile* n = (*i);
		FreeNode(n);
	}
	openList_.clear();

	i = closedList_.begin();
	while (i != closedList_.end()) {
		ATile* n = (*i);
		FreeNode(n);
	}
	closedList_.clear();
}


void CEntity::FreeNode(ATile* n) {
	delete n;
}


void CEntity::FreeUnusedNodes() {
	std::vector<ATile*>::iterator iterOpen = openList_.begin();
	while (iterOpen != openList_.end()) {
		ATile* n = (*iterOpen);
		if (!n->child) {
			FreeNode(n);
			n = NULL;
		}
		iterOpen++;
	}

	std::vector<ATile*>::iterator iterClosed = closedList_.begin();
	while (iterClosed != closedList_.end()) {
		ATile* n = (*iterClosed);
		if (!n->child) {
			FreeNode(n);
			n = NULL;
		}
		iterClosed++;
	}
}


void CEntity::AddSuccessors(ATile* tile) {
	successorList_.clear();
	for(int row = tile->tile->Coord.Y - 1; row <= tile->tile->Coord.Y + 1; row++) {
		for(int col = tile->tile->Coord.X - 1; col <= tile->tile->Coord.X + 1; col++) {

			if(row == tile->tile->Coord.Y && col == tile->tile->Coord.X) continue; // skip current cell
			if(row < 0 || row > CMap::MapControl.getHeight()) continue; // skip tiles outside map
			if(col < 0 || col > CMap::MapControl.getWidth()) continue; // skip tiles outside map

			CTile* successorTile = CMap::MapControl.getTile(col, row);

			// Only passable tiles are processed
			if (successorTile->TypeID == TILE_TYPE_NORMAL) {
				ATile* successor = new ATile();
				successor->tile = successorTile;
				successorList_.push_back(successor);
			}
		}
	}
}


int CEntity::GetHeuristic(CCoord A, CCoord B) {
	//return COST_STRAIGHT * std::max(abs(A.X-B.X), abs(A.Y-B.Y));
	return COST_STRAIGHT * (abs(A.X-B.X) + abs(A.Y-B.Y)); // Manhattan Distance
}


void CEntity::decorateClosedList() {
	for (std::vector<ATile*>::iterator i=closedList_.begin(); i!=closedList_.end(); ++i) {
		CTile* tile = (*i)->tile;
		CTile* parent = (*i)->parent->tile;

		if ((parent->Coord.X <  tile->Coord.X) && (parent->Coord.Y <  tile->Coord.Y)) tile->Label = L"↖";
		if ((parent->Coord.X <  tile->Coord.X) && (parent->Coord.Y == tile->Coord.Y)) tile->Label = L"←";
		if ((parent->Coord.X <  tile->Coord.X) && (parent->Coord.Y >  tile->Coord.Y)) tile->Label = L"↙";
		if ((parent->Coord.X == tile->Coord.X) && (parent->Coord.Y <  tile->Coord.Y)) tile->Label = L"↑";
		if ((parent->Coord.X == tile->Coord.X) && (parent->Coord.Y >  tile->Coord.Y)) tile->Label = L"↓";
		if ((parent->Coord.X >  tile->Coord.X) && (parent->Coord.Y <  tile->Coord.Y)) tile->Label = L"↗";
		if ((parent->Coord.X >  tile->Coord.X) && (parent->Coord.Y == tile->Coord.Y)) tile->Label = L"→";
		if ((parent->Coord.X >  tile->Coord.X) && (parent->Coord.Y >  tile->Coord.Y)) tile->Label = L"↘";
	}
}


void CEntity::decorateFinalPath() {
	if (pathToDestination_.size() == 0) return;

	CTile* parent = (*pathToDestination_.begin());
	for(std::vector<CTile*>::iterator i = pathToDestination_.begin(); i!=pathToDestination_.end(); ++i) {
		CTile* tile = (*i);
		if ((parent->Coord.X <  tile->Coord.X) && (parent->Coord.Y <  tile->Coord.Y)) tile->Label = L"⇖";
		if ((parent->Coord.X <  tile->Coord.X) && (parent->Coord.Y == tile->Coord.Y)) tile->Label = L"⇐";
		if ((parent->Coord.X <  tile->Coord.X) && (parent->Coord.Y >  tile->Coord.Y)) tile->Label = L"⇙";
		if ((parent->Coord.X == tile->Coord.X) && (parent->Coord.Y <  tile->Coord.Y)) tile->Label = L"⇑";
		if ((parent->Coord.X == tile->Coord.X) && (parent->Coord.Y >  tile->Coord.Y)) tile->Label = L"⇓";
		if ((parent->Coord.X >  tile->Coord.X) && (parent->Coord.Y <  tile->Coord.Y)) tile->Label = L"⇗";
		if ((parent->Coord.X >  tile->Coord.X) && (parent->Coord.Y == tile->Coord.Y)) tile->Label = L"⇒";
		if ((parent->Coord.X >  tile->Coord.X) && (parent->Coord.Y >  tile->Coord.Y)) tile->Label = L"⇘";
		parent = tile;
	}
}



void CEntity::dumpClosedList() {
	for(std::vector<ATile*>::iterator i = closedList_.begin(); i!=closedList_.end(); ++i) {
		std::cout << "T:" << (*i)->tile->Coord;
		if ((*i)->parent != NULL) {
			std::cout << " P:" << (*i)->parent->tile->Coord;
		}
		std::cout << std::endl;
	}
}
