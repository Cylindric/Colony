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
	Anim_Control.SetLoop(30, 33);
	return rv;
}


void CEntity_Buggy::OnLoop() {
	if(SDL_GetTicks() > (this->LastMove + 1000)) {
		int nextX = this->X + this->testD;

		CTile destinationTile = CArea::AreaControl.GetTile(nextX, this->Y);
		if(destinationTile.TypeID == TILE_TYPE_BLOCK) {
			nextX = this->X;
			this->testD = -this->testD;
		}

		this->X = nextX;
		this->LastMove = SDL_GetTicks();
	}


	this->DestinationCursor.X = this->X + this->testD;
	this->DestinationCursor.Y = this->Y;
	Anim_Control.OnAnimate();
	this->DestinationCursor.OnLoop();
}


void CEntity_Buggy::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);
	this->DestinationCursor.OnRender(Surf_Display);
}