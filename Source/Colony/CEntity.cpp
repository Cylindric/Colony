#include "CEntity.h"

std::vector<CEntity*> CEntity::EntityList;

CEntity::CEntity() {
	Surf_Tileset = NULL;
	X = 0.0f;
	Y = 0.0f;
	Width = 0;
	Height = 0;
	AnimState = 0;
}

CEntity::~CEntity() {
}

bool CEntity::OnLoad(SDL_Surface* Tileset, int Width, int Height, int MaxFrames) {
	if(Tileset == NULL) return false;
	Surf_Tileset = Tileset;

	this->Width = Width;
	this->Height = Height;
	Anim_Control.MaxFrames = MaxFrames;
	return true;
}

void CEntity::OnLoop() {
	Anim_Control.OnAnimate();
}

void CEntity::OnRender(SDL_Surface* Surf_Display) {
	if(Surf_Tileset == NULL || Surf_Display == NULL) return;

	CSurface::OnDraw(Surf_Display, Surf_Tileset, (int)X, (int)Y, Anim_Control.GetCurrentFrame() * Width, AnimState * Height, Width, Height);
}

void CEntity::OnCleanup() {
}