#include <iostream>
#include <direct.h>
#include "CApp.h"

bool CApp::OnInit() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
		return false;
	}

	if((Default_Tileset = CSurface::OnLoad("./gfx/floor.png")) == false) return false;
	if((Buggy_Tileset = CSurface::OnLoad("./gfx/buggy.png")) == false) return false;

	if(CArea::AreaControl.OnLoad(Default_Tileset) == false) return false;
	if(Buggy1.OnLoad(Buggy_Tileset, 20, 20,	4) == false) return false;
	Buggy1.X = 100;
	Buggy1.Y = 100;
	CEntity::EntityList.push_back(&Buggy1);

	if(CCursor::CursorControl.OnLoad(Default_Tileset) == false) return false;
	SDL_ShowCursor(0);

	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

	return true;
}