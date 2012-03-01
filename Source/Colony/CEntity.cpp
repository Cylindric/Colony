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

bool CEntity::OnLoad(char* Filename, int Width, int Height, int MaxFrames) {
	if((Surf_Tileset = CSurface::OnLoad(Filename)) == NULL) {
        return false;
    }
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

	// calculate the 'real' position on the view
	int screenX = (int)(X + CCamera::CameraControl.GetX());
	int screenY = (int)(Y + CCamera::CameraControl.GetY());

	// center the sprite
	screenX = screenX - (Width / 2);
	screenY = screenY - (Height / 2);

	// if the sprite is off-camera, don't bother drawing it
	if((screenX + Width < 0) || (screenY + Height < 0)) return;
	if((screenX - Width > CCamera::CameraControl.GetWidth()) || (screenY - Height > CCamera::CameraControl.GetWidth())) return;

	CSurface::OnDraw(Surf_Display, Surf_Tileset, screenX, screenY, Anim_Control.GetCurrentFrame() * Width, AnimState * Height, Width, Height);
}

void CEntity::OnCleanup() {
	if(Surf_Tileset) {
		SDL_UnlockSurface(Surf_Tileset);
	}
}