#include <iostream>
#include <direct.h>
#include "CApp.h"

bool CApp::OnInit() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	if(TTF_Init() != 0) {
		return false;
	}

	Surf_Display = CCamera::CameraControl.OnInit();
	if(Surf_Display == false) return false;

	if((Default_Tileset = CSurface::OnLoad("./gfx/floor.png")) == false) return false;

	if(CArea::AreaControl.OnLoad(Default_Tileset) == false) return false;
	if(Buggy1.OnLoad() == false) return false;
	Buggy1.X = 200;
	Buggy1.Y = 200;
	CEntity::EntityList.push_back(&Buggy1);

	if(CCursor::CursorControl.OnLoad(Default_Tileset) == false) return false;
	SDL_ShowCursor(0);


	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

	return true;
}