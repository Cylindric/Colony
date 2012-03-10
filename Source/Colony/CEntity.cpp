#include <iostream>
#include <vector>
#include <algorithm>
#include "CEntity.h"
#include "CMap.h"
#include "ATile.h"
#include "CTile.h"
#include "CCamera.h"
#include "CSurface.h"

std::vector<CEntity*> CEntity::EntityList;


CEntity::CEntity() {
	this->EntityTileset = NULL;
	this->Coord = CCoord();
	this->SpriteWidth = CMap::MapControl.getTileSize();
	this->SpriteHeight = CMap::MapControl.getTileSize();
	this->AnimState = 0;
	this->Label[0] = 0;
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


void CEntity::CalcRoute(CTile* StartNode, CTile* EndNode) {
	// A* help from http://www.policyalmanac.org/games/aStarTutorial.htm

	bool Finished = false;
	int Iteration = 0; // for tracking the loop-count and bailing out early - mostly for visualisation reasons
	int newCost = 0;
	long startTime = SDL_GetTicks();

	// push the StartNode into the Open List to start things off
	ATile* tile = new ATile();
	tile->tile = StartNode;
	tile->parent = StartNode;
	tile->Gcost = 0;
	tile->Hcost = GetHeuristic(StartNode->Coord, EndNode->Coord);
	tile->Fscore = tile->Gcost + tile->Hcost;
	openList_.insert(tile);

	while(Finished == false) {

		if (openList_.size() == 0) {
			Finished = true;
			continue;
		}

		// Find the tile with the lowest F in the Open List
		ATile* currentTile = GetLowestF(openList_);

		// Move the closest tile off the Open List, onto the Closed List
		openList_.erase(currentTile);
		closedList_.insert(currentTile);

		if(currentTile->tile == EndNode) {
			openList_.clear();
			Finished = true;
		} else {

			// Check each neighbouring cell of the current cell
			for(int row = currentTile->tile->Coord.Y - 1; row <= currentTile->tile->Coord.Y + 1; row++) {
				for(int col = currentTile->tile->Coord.X - 1; col <= currentTile->tile->Coord.X + 1; col++) {

					if(row == currentTile->tile->Coord.Y && col == currentTile->tile->Coord.X) continue; // skip current cell
					if(row < 0 || row > CMap::MapControl.getHeight()) continue; // skip tiles outside map
					if(col < 0 || col > CMap::MapControl.getWidth()) continue; // skip tiles outside map

					CTile* neighbour = CMap::MapControl.getTile(col, row);

					// Only passable tiles are processed
					if (neighbour->TypeID == TILE_TYPE_NORMAL) {
						// is it on the Closed List already?
						ATile* foundNeighbour = FindTileOnList(closedList_, neighbour);
						if (foundNeighbour == 0) {

							if (row == currentTile->tile->Coord.Y || col == currentTile->tile->Coord.X) {
								newCost = currentTile->Gcost + COST_STRAIGHT; // perpendicular tiles
							} else {
								newCost = currentTile->Gcost + COST_DIAGONAL; // diagonal tiles
							}

							// is it on the Open List already?
							foundNeighbour = FindTileOnList(openList_, neighbour);
							if (foundNeighbour == 0) {
								// not on list
								foundNeighbour = new ATile();
								foundNeighbour->parent = currentTile->tile;
								foundNeighbour->tile = neighbour;
								foundNeighbour->Gcost = newCost;
								foundNeighbour->Hcost = GetHeuristic(neighbour->Coord, EndNode->Coord);
								foundNeighbour->Fscore = foundNeighbour->Gcost + foundNeighbour->Hcost;

								openList_.insert(foundNeighbour);
							} else {
								// on list
								if(newCost < foundNeighbour->Gcost) {
									// on list, and this route is cheaper
									foundNeighbour->parent = currentTile->tile;
									foundNeighbour->Gcost = newCost;
									foundNeighbour->Hcost = GetHeuristic(neighbour->Coord, EndNode->Coord);
									foundNeighbour->Fscore = foundNeighbour->Gcost + foundNeighbour->Hcost;
								}
							}
						}
					}
				}
			}
		}
		Iteration++;
	}

	// Populate the final path to destination
	if (isValidPath_ == false) {
		if (openList_.size() == 0) {
			pathToDestination_.clear();
			bool finished = false;
			CTile* pathTile = EndNode;
			while(finished == false) {
				ATile* thisATile = FindTileOnList(closedList_, pathTile);
				pathToDestination_.insert(pathToDestination_.begin(), thisATile->tile);
				pathTile = thisATile->parent;
				if(pathTile == StartNode) {
					finished = true;
				}
			}
			isValidPath_ = true;
		}
	}

	std::cout << "A* took " << (SDL_GetTicks() - startTime) << std::endl;

}


int CEntity::GetHeuristic(CCoord A, CCoord B) {
	//return COST_STRAIGHT * std::max(abs(A.X-B.X), abs(A.Y-B.Y));
	return COST_STRAIGHT * (abs(A.X-B.X) + abs(A.Y-B.Y)); // Manhattan Distance
}


ATile* CEntity::GetLowestF(std::set<ATile*> List) {
	int lowestF = -1;
	ATile* lowestTile = 0;
	for (std::set<ATile*>::iterator tile=List.begin(); tile!=List.end(); ++tile) {
		if(lowestF == -1 || (*tile)->Fscore < lowestF) {
			lowestF = (*tile)->Fscore;
			lowestTile = *tile;
		}
	}
	return lowestTile;
}


ATile* CEntity::FindTileOnList(std::set<ATile*> List, CTile* Tile) {
	for (std::set<ATile*>::iterator tile=List.begin(); tile!=List.end(); ++tile) {
		if((*tile)->tile == Tile) {
			return (*tile);
		}
	}
	return 0;
}
