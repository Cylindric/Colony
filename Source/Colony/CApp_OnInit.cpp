#include "CApp.h"

#include "CCamera.h"
#include "CCursor.h"
#include "CFont.h"
#include "CMap.h"
#include <iostream>


bool CApp::OnInit() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}


	if(TTF_Init() != 0) {
		return false;
	}

	Surf_Display = CCamera::CameraControl.OnInit();
	if(Surf_Display == false) return false;

	if(CMap::MapControl.OnLoad("./maps/maze.txt") == false) {
		std::cerr << "Error loading map";
		return false;
	}

	if(CFont::FontControl.OnInit() == false) {
		std::cout << "Error initialising fonts";
		return false;
	}

	if(CCursor::CursorControl.OnLoad() == false) {
		return false;
	}
	SDL_ShowCursor(0);

	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

	return true;
}