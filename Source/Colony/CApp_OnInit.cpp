#include "CApp.h"

#include <iostream>
#include "CCamera.h"
#include "CCursor.h"
#include "CFont.h"
#include "CMap.h"


bool CApp::OnInit() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "Error initialising SDL library" << std::endl;
		return false;
	}

	SDL_EnableUNICODE(SDL_ENABLE);

	// Initialise random seed
	srand(0);

	if(TTF_Init() != 0) {
		std::cerr << "Error initialising TTF library" << std::endl;
		return false;
	}

	Surf_Display = CCamera::CameraControl.OnInit();
	if(Surf_Display == false) return false;

	if(CMap::MapControl.onLoad("./maps/maze2.txt") == false) {
		std::cerr << "Error loading map" << std::endl;
		return false;
	}

	if(CFont::FontControl.OnInit() == false) {
		std::cout << "Error initialising fonts" << std::endl;
		return false;
	}

	if(CCursor::CursorControl.OnLoad() == false) {
		return false;
	}
	SDL_ShowCursor(0);

	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

	return true;
}