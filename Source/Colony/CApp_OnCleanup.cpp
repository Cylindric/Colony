#include "CApp.h"

void CApp::OnCleanup() {
	for(unsigned int i = 0; i < CEntity::EntityList.size(); i++) {
		if(!CEntity::EntityList[i]) continue;
		CEntity::EntityList[i]->OnCleanup();
	}

	SDL_FreeSurface(Default_Tileset);
	SDL_FreeSurface(Surf_Display);
	CArea::AreaControl.OnCleanup();
	SDL_Quit();
}