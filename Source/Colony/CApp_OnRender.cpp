#include <vector>
#include "CApp.h"
#include "CMap.h"
#include "CEntity.h"
#include "CCursor.h"
#include "CFPS.h"
#include "CCamera.h"
#include "CTile.h"

void CApp::OnRender() {
	SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
	
	// render the map tiles
	CMap::MapControl.onRender(Surf_Display, CCamera::CameraControl.GetX(), CCamera::CameraControl.GetY());


	for(unsigned int i = 0; i < CEntity::EntityList.size(); i++) {
		if(!CEntity::EntityList[i]) continue;
		CEntity::EntityList[i]->OnRender(Surf_Display);
	}

	CCamera::CameraControl.OnRender(Surf_Display);
	CCursor::CursorControl.OnRender(Surf_Display);

	SDL_Flip(Surf_Display);

	// clear the tiles
	for (std::vector<CTile*>::iterator itTile=CMap::MapControl.getTiles()->begin(); itTile!=CMap::MapControl.getTiles()->end(); ++itTile) {
		(*itTile)->Label = L"";
	}

	char buffer[30];
	sprintf_s(buffer, "Colony FPS:%i SF:%f",  CFPS::FPSControl.GetFPS(), CFPS::FPSControl.GetSpeedFactor());
	SDL_WM_SetCaption(buffer, "Colony");
}