#include "CApp.h"

void CApp::OnCleanup() {
	SDL_FreeSurface(Default_Tileset);
	SDL_FreeSurface(Surf_Display);
	CArea::AreaControl.OnCleanup();
	SDL_Quit();
}