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

	if((Default_Tileset = CSurface::OnLoad("./gfx/tiles.png")) == false) return false;

	if(CArea::AreaControl.OnLoad("./areas/area1.txt") == false) return false;

	if(CFont::FontControl.OnInit() == false) {
		std::cout << "Error initialising fonts";
		return false;
	}

	// hack in a single buggy for testing
	if(Buggy1.OnLoad(Default_Tileset) == false) return false;
	Buggy1.X = 5;
	Buggy1.Y = 5;
	CTile buggyTile = CArea::AreaControl.GetTile(Buggy1.X, Buggy1.Y);
	buggyTile.EntityList.push_back(&Buggy1);
	CEntity::EntityList.push_back(&Buggy1);

	if(CCursor::CursorControl.OnLoad(Default_Tileset) == false) return false;
	SDL_ShowCursor(0);


	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

	return true;
}