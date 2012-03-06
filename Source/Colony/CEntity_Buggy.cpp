#include "CEntity_Buggy.h"


CEntity_Buggy::CEntity_Buggy() {
	this->Speed = 1;
	this->Destination = CCoord();
	this->LastMove = SDL_GetTicks();
	this->testD = 1;
}


bool CEntity_Buggy::OnLoad() {
	bool rv = CEntity::OnLoad();
	this->DestinationCursor.OnLoad();
	this->Destination.X = -1;
	this->Destination.Y = -1;
	Anim_Control.SetLoop(30, 33);
	return rv;
}


void CEntity_Buggy::OnLoop() {
	std::list<ATile> openList;
	std::list<ATile> closedList;

	if(SDL_GetTicks() > (this->LastMove + 1000)) {
		CTile* currentTile = CMap::MapControl.GetTile(this->Coord);

		// decorate the tiles for testing
		for (std::vector<CTile>::iterator itTile=CMap::MapControl.TileList.begin(); itTile!=CMap::MapControl.TileList.end(); ++itTile) {
			sprintf_s(itTile->Label, "-");
		}

		// A* test
		openList.clear();
		closedList.clear();

		// Start the Open List
		ATile rootTile;
		rootTile.tile = currentTile;
		rootTile.parent = currentTile;
		rootTile.Gcost = 0;
		rootTile.Hcost = 1 * std::max(abs(this->Coord.X - this->Destination.X), abs(this->Coord.Y - this->Destination.Y));
		rootTile.Fscore = rootTile.Gcost + rootTile.Hcost;
		openList.push_back(rootTile);

		// Add neighbours
		for(int row = this->Coord.Y - 1; row <= this->Coord.Y + 1; row++) {
			for(int col = this->Coord.X - 1; col <= this->Coord.X + 1; col++) {

				if(row == this->Coord.Y && col == this->Coord.X) continue; // skip current cell

				CTile* neighbour = CMap::MapControl.GetTile(col, row);
				if(neighbour->TypeID == TILE_TYPE_NORMAL) {
					ATile tmpTile;
					tmpTile.tile = neighbour;
					tmpTile.parent = currentTile;

					// calculate G - the cost to get to neighbour from currentCell
					tmpTile.Gcost = rootTile.Gcost + 1; // all cells are '1' away

					// calculate H - the cost to the destination from the neighbour
					tmpTile.Hcost = 1 * std::max(abs(col - this->Destination.X), abs(row - this->Destination.Y));

					// calculate F
					tmpTile.Fscore = tmpTile.Gcost + tmpTile.Hcost;

					openList.push_back(tmpTile);
				}
			}
		}
		openList.remove(rootTile);
		closedList.push_back(rootTile);

		// find lowest-F open tile
		int lowestF = -1;
		ATile* lowestTile = &rootTile;
		std::list<ATile>::iterator lowest;

		for (std::list<ATile>::iterator tile=openList.begin(); tile!=openList.end(); ++tile) {
			if(lowestF == -1 || tile->Fscore < lowestF) {
				lowestTile = &*tile;
				lowest = tile;
			}
		}
		closedList.push_back(*lowestTile);
		openList.erase(lowest);


		// iter 2
		// Add neighbours
		for(int row = lowestTile->tile->Coord.Y - 1; row <= lowestTile->tile->Coord.Y + 1; row++) {
			for(int col = lowestTile->tile->Coord.X - 1; col <= lowestTile->tile->Coord.X + 1; col++) {
				if(row == lowestTile->tile->Coord.Y && col == lowestTile->tile->Coord.X) continue; // skip current cell
				CTile* neighbour = CMap::MapControl.GetTile(col, row);
				if(neighbour->TypeID == TILE_TYPE_NORMAL) {
					ATile tmpTile;
					tmpTile.tile = neighbour;
					tmpTile.parent = lowestTile->tile;

					// calculate G - the cost to get to neighbour from currentCell
					tmpTile.Gcost = lowestTile->Gcost + 1; // all cells are '1' away

					// calculate H - the cost to the destination from the neighbour
					tmpTile.Hcost = 1 * std::max(abs(col - this->Destination.X), abs(row - this->Destination.Y));

					// calculate F
					tmpTile.Fscore = tmpTile.Gcost + tmpTile.Hcost;

					openList.push_back(tmpTile);
				}

			}
		}



		std::list<ATile>::iterator tile;
		for (tile=openList.begin(); tile!=openList.end(); ++tile) {
			tile->tile->TileID = 3;
			sprintf_s(tile->tile->LTopLeft, "%d", tile->Fscore);
			sprintf_s(tile->tile->LBottomLeft, "%d", tile->Gcost);
			sprintf_s(tile->tile->LBottomRight, "%d", tile->Hcost);
		}

		for (tile=closedList.begin(); tile!=closedList.end(); ++tile) {
			tile->tile->TileID = 4;
			sprintf_s(tile->tile->LTopLeft, "%d", tile->Fscore);
			sprintf_s(tile->tile->LBottomLeft, "%d", tile->Gcost);
			sprintf_s(tile->tile->LBottomRight, "%d", tile->Hcost);
		}

		//sprintf_s(lowestTile->tile->Label, "H%d", lowestTile->Fscore);


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