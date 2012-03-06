#include "CEntity_Buggy.h"


CEntity_Buggy::CEntity_Buggy() {
	this->Speed = 1;
	this->Destination = CCoord();
	this->LastMove = SDL_GetTicks();
	this->testD = 1;
	this->IterationCap = 0;
}


bool CEntity_Buggy::OnLoad() {
	bool rv = CEntity::OnLoad();
	this->DestinationCursor.OnLoad();
	this->Destination.X = -1;
	this->Destination.Y = -1;
	Anim_Control.SetLoop(30, 33);
	return rv;
}


void CEntity_Buggy::CalcRoute(std::list<ATile*> &openList, std::list<ATile*> &closedList, CTile* StartNode, CTile* EndNode) {

	bool Finished = false;
	int Iteration = 0; // for tracking the loop-count and bailing out early - mostly for visualisation reasons

	// push the StartNode into the Open List to start things off
	ATile* tile = new ATile();
	tile->tile = StartNode;
	tile->parent = StartNode;
	tile->Gcost = 0;
	tile->Hcost = GetHeuristic(StartNode->Coord, EndNode->Coord);
	tile->Fscore = tile->Gcost + tile->Hcost;
	openList.push_back(tile);

	while(Finished == false && Iteration < this->IterationCap) {

		// Find the tile with the lowest F in the Open List
		ATile* currentTile = GetLowestF(openList);

		// Move the closest tile off the Open List, onto the Closed List
		openList.remove(currentTile);
		closedList.push_back(currentTile);

		if(currentTile->tile == EndNode) {
			Finished = true;
		} else {

			// Check each neighbouring cell of the current cell
			for(int row = currentTile->tile->Coord.Y - 1; row <= currentTile->tile->Coord.Y + 1; row++) {
				for(int col = currentTile->tile->Coord.X - 1; col <= currentTile->tile->Coord.X + 1; col++) {
					if(row == currentTile->tile->Coord.Y && col == currentTile->tile->Coord.X) continue; // skip current cell

					CTile* neighbour = CMap::MapControl.GetTile(col, row);

					// Only passable tiles are processed
					if(neighbour->TypeID == TILE_TYPE_NORMAL) {
						// is it on the Open List already?
						ATile* foundNeighbour = FindTileOnList(openList, neighbour);
						if (foundNeighbour == 0) {
							// not on list
							foundNeighbour = new ATile(neighbour, currentTile->tile, currentTile->Gcost+1, GetHeuristic(neighbour->Coord, EndNode->Coord));
							openList.push_back(foundNeighbour);
						} else {
							// on list
							if(currentTile->Gcost + 1 < foundNeighbour->Gcost) {
								// on list, and this route is cheaper
								foundNeighbour->parent = currentTile->tile;
							}
						}
					}
				}
			}
		}

		Iteration++;
	}

	this->IterationCap++;
}


int CEntity_Buggy::GetHeuristic(CCoord A, CCoord B) {
	// cheap and simple H for now
	return std::max(abs(A.X-B.X), abs(A.Y-B.Y));
}


ATile* CEntity_Buggy::GetLowestF(std::list<ATile*> List) {
	int lowestF = -1;
	ATile* lowestTile = 0;
	for (std::list<ATile*>::iterator tile=List.begin(); tile!=List.end(); ++tile) {
		if(lowestF == -1 || (*tile)->Fscore < lowestF) {
			lowestF = (*tile)->Fscore;
			lowestTile = *tile;
		}
	}
	return lowestTile;
}


ATile* CEntity_Buggy::FindTileOnList(std::list<ATile*> List, CTile* Tile) {
	for (std::list<ATile*>::iterator tile=List.begin(); tile!=List.end(); ++tile) {
		if((*tile)->tile == Tile) {
			return (*tile);
		}
	}
	return 0;
}


void CEntity_Buggy::OnLoop() {
	// A* help from http://www.policyalmanac.org/games/aStarTutorial.htm

	std::list<ATile*> openList;
	std::list<ATile*> closedList;

	if(SDL_GetTicks() > (this->LastMove + 500)) {
		CTile* currentTile = CMap::MapControl.GetTile(this->Coord);
		CTile* targetTile = CMap::MapControl.GetTile(5, 2);

		// decorate the tiles for testing
		for (std::vector<CTile>::iterator itTile=CMap::MapControl.TileList.begin(); itTile!=CMap::MapControl.TileList.end(); ++itTile) {
			sprintf_s(itTile->Label, "-");
		}

		// A* test
		openList.clear();
		closedList.clear();
		CalcRoute(openList, closedList, currentTile, targetTile);


		std::list<ATile*>::iterator tile;
		if(this->IterationCap==7) {
			std::cerr<<"end";
		}
		for (tile=openList.begin(); tile!=openList.end(); ++tile) {
			int i = 0;
			if(i==2) {
				std::cerr<<"end";
			}
			sprintf_s((*tile)->tile->LTopLeft, "%d", (*tile)->Fscore);
			sprintf_s((*tile)->tile->LBottomLeft, "%d", (*tile)->Gcost);
			sprintf_s((*tile)->tile->LBottomRight, "%d", (*tile)->Hcost);
			(*tile)->tile->TileID = 10;
			if((*tile)->parent->Coord.X == (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y <  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 1; //up
			if((*tile)->parent->Coord.X >  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y == (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 2; //right
			if((*tile)->parent->Coord.X == (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y <  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 3; //down
			if((*tile)->parent->Coord.X <  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y == (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 4; //left
			if((*tile)->parent->Coord.X <  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y <  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 5; //up-left
			if((*tile)->parent->Coord.X >  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y <  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 6; //up-right
			if((*tile)->parent->Coord.X >  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y >  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 7; //down-right
			if((*tile)->parent->Coord.X <  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y >  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 8; //down-left
			i++;
		}

		for (tile=closedList.begin(); tile!=closedList.end(); ++tile) {
			sprintf_s((*tile)->tile->LTopLeft, "%d", (*tile)->Fscore);
			sprintf_s((*tile)->tile->LBottomLeft, "%d", (*tile)->Gcost);
			sprintf_s((*tile)->tile->LBottomRight, "%d", (*tile)->Hcost);
			(*tile)->tile->TileID = 20;
			if((*tile)->parent->Coord.X == (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y <  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 1; //up
			if((*tile)->parent->Coord.X >  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y == (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 2; //right
			if((*tile)->parent->Coord.X == (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y <  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 3; //down
			if((*tile)->parent->Coord.X <  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y == (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 4; //left
			if((*tile)->parent->Coord.X <  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y <  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 5; //up-left
			if((*tile)->parent->Coord.X >  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y <  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 6; //up-right
			if((*tile)->parent->Coord.X >  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y >  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 7; //down-right
			if((*tile)->parent->Coord.X <  (*tile)->tile->Coord.X && (*tile)->parent->Coord.Y >  (*tile)->tile->Coord.Y) (*tile)->tile->TileID += 8; //down-left
		}

		//sprintf_s(lowestTile->tile->Label, "H");


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
		this->LastMove = SDL_GetTicks();
	}

	this->DestinationCursor.Coord.X = this->Destination.X;
	this->DestinationCursor.Coord.Y = this->Destination.Y;
	Anim_Control.OnAnimate();
	this->DestinationCursor.OnLoop();
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