#include "CApp.h"

void CApp::OnRender() {
	SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
	
	// render the map tiles
	CMap::MapControl.OnRender(Surf_Display, CCamera::CameraControl.GetX(), CCamera::CameraControl.GetY());


	for(unsigned int i = 0; i < CEntity::EntityList.size(); i++) {
		if(!CEntity::EntityList[i]) continue;
		CEntity::EntityList[i]->OnRender(Surf_Display);
	}

	CCamera::CameraControl.OnRender(Surf_Display);
	CCursor::CursorControl.OnRender(Surf_Display);

	SDL_Flip(Surf_Display);

	char buffer[30];
	sprintf_s(buffer, "Colony FPS:%i SF:%f",  CFPS::FPSControl.GetFPS(), CFPS::FPSControl.GetSpeedFactor());
	SDL_WM_SetCaption(buffer, "Colony");
}