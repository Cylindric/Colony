#include "CApp.h"

void CApp::OnRender() {
	CArea::AreaControl.OnRender(Surf_Display, CCamera::CameraControl.GetX(), CCamera::CameraControl.GetY());

	for(unsigned int i = 0; i < CEntity::EntityList.size(); i++) {
		if(!CEntity::EntityList[i]) continue;
		CEntity::EntityList[i]->OnRender(Surf_Display);
	}

	CCursor::CursorControl.OnRender(Surf_Display);


	SDL_Flip(Surf_Display);

	char buffer[30];
	sprintf_s(buffer, "Colony: %i FPS",  CFPS::FPSControl.GetFPS());
	SDL_WM_SetCaption(buffer, "Colony");
}