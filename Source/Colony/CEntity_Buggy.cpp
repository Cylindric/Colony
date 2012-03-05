#include "CEntity_Buggy.h"


CEntity_Buggy::CEntity_Buggy() {
	this->Speed = 1;
	this->DestinationX = -1;
	this->DestinationY = -1;
	this->LastMove = SDL_GetTicks();
	this->testD = 1;
}


bool CEntity_Buggy::OnLoad(SDL_Surface* Tileset) {
	bool rv = CEntity::OnLoad(Tileset);
	this->DestinationCursor.OnLoad(Tileset);
	this->DestinationX = 15;
	this->DestinationY = 10;
	Anim_Control.SetLoop(30, 33);
	return rv;
}


void CEntity_Buggy::OnLoop() {
	if(SDL_GetTicks() > (this->LastMove + 1000)) {
		int nextX = this->X + this->testD;

		// pop a footprint on the current tile
		CTile& currentTile = CArea::AreaControl.GetTile(this->X, this->Y);
		//currentTile.Label[0] = 'o';
		sprintf_s(currentTile.Label, "%i", this->CostToDestination());

		CTile destinationTile = CArea::AreaControl.GetTile(this->DestinationX, this->DestinationY);
		if(destinationTile.TypeID == TILE_TYPE_BLOCK) {
			nextX = this->X;
			this->testD = -this->testD;
		}

		this->X = nextX;
		this->LastMove = SDL_GetTicks();
	}

	this->DestinationCursor.X = this->DestinationX;
	this->DestinationCursor.Y = this->DestinationY;
	Anim_Control.OnAnimate();
	this->DestinationCursor.OnLoop();
}


void CEntity_Buggy::OnRender(SDL_Surface* Surf_Display) {
//	CEntity::OnRender(Surf_Display);
	this->DestinationCursor.OnRender(Surf_Display);
}


int CEntity_Buggy::CostToDestination() {
	int cost = 0;
	cost = 1 * std::max(abs(this->X - this->DestinationX), abs(this->Y - this->DestinationY));
	return cost;
}