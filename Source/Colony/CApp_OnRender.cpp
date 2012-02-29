#include "CApp.h"

void CApp::OnRender() {
	CArea::AreaControl.OnRender(Surf_Display, CCamera::CameraControl.GetX(), CCamera::CameraControl.GetY());
	CCursor::CursorControl.OnRender(Surf_Display);
	SDL_Flip(Surf_Display);

	char buffer[30];
	sprintf_s(buffer, "Colony: %i FPS",  CFPS::FPSControl.GetFPS());
	SDL_WM_SetCaption(buffer, "Colony");
}