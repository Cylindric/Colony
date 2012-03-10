#include "CApp.h"
#include "CEntity.h"
#include "CMap.h"

void CApp::OnCleanup() {
	for(unsigned int i = 0; i < CEntity::EntityList.size(); i++) {
		if(!CEntity::EntityList[i]) continue;
		CEntity::EntityList[i]->OnCleanup();
	}

	SDL_FreeSurface(Default_Tileset);
	SDL_FreeSurface(Surf_Display);
	CMap::MapControl.onCleanup();
	SDL_Quit();
}