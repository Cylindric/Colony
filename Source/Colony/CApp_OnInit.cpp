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

	if(CMap::MapControl.OnLoad("./maps/wall.txt") == false) {
		std::cerr << "Error loading map";
		return false;
	}

	if(CFont::FontControl.OnInit() == false) {
		std::cout << "Error initialising fonts";
		return false;
	}

	// hack in a single buggy for testing
	//if(Buggy1.OnLoad() == false) {
	//	return false;
	//}
	//Buggy1.Coord.X = 3;
	//Buggy1.Coord.Y = 6;
	//Buggy1.Destination.X = 5;
	//Buggy1.Destination.Y = 7;
	//CTile* buggyTile = CMap::MapControl.GetTile(Buggy1.Coord);
	//buggyTile->EntityList.push_back(&Buggy1);
	//CEntity::EntityList.push_back(&Buggy1);

	if(CCursor::CursorControl.OnLoad() == false) {
		return false;
	}
	SDL_ShowCursor(0);


	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

	return true;
}