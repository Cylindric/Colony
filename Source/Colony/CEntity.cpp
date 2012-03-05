#include "CEntity.h"

std::vector<CEntity*> CEntity::EntityList;

CEntity::CEntity() {
	this->EntityTileset = NULL;
	this->Coord = CCoord();
	this->SpriteWidth = TILE_SIZE;
	this->SpriteHeight = TILE_SIZE;
	this->AnimState = 0;
	this->Label[0] = 0;
}


CEntity::~CEntity() {
}


bool CEntity::OnLoad(SDL_Surface* Tileset) {
	if(Tileset == NULL) {
        return false;
    }
	this->EntityTileset = Tileset;
	return true;
}


void CEntity::OnLoop() {
	Anim_Control.OnAnimate();
}


void CEntity::OnRender(SDL_Surface* Surf_Display) {
	if(this->EntityTileset == NULL || Surf_Display == NULL) return;

	// calculate the 'real' position on the view
	int screenX = ((this->Coord.X * TILE_SIZE) + CCamera::CameraControl.GetX());
	int screenY = ((this->Coord.Y * TILE_SIZE) + CCamera::CameraControl.GetY());

	// if the sprite is off-camera, don't bother drawing it
	if((screenX + SpriteWidth < 0) || (screenY + SpriteHeight < 0)) return;
	if((screenX - SpriteWidth > CCamera::CameraControl.GetWidth()) || (screenY - SpriteHeight > CCamera::CameraControl.GetWidth())) return;

	int cell = Anim_Control.GetCurrentFrame();
    int cellX = (cell % TILESET_COLS) * TILE_SIZE;
    int cellY = (cell / TILESET_COLS) * TILE_SIZE;

	CSurface::OnDraw(Surf_Display, this->EntityTileset, screenX, screenY, cellX, cellY, SpriteWidth, SpriteHeight);
}

void CEntity::OnCleanup() {
}