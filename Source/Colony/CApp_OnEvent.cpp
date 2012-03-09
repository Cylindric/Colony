#include "CApp.h"
#include "CCamera.h"
#include "CCursor.h"

void CApp::OnEvent(SDL_Event* Event) {
	CEvent::OnEvent(Event);
}

void CApp::OnExit() {
	Running = false;
}

void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch(sym) {
		case SDLK_ESCAPE: Running = false; break;
		case SDLK_UP: CCamera::CameraControl.OnMove(0, 5); break;
		case SDLK_DOWN: CCamera::CameraControl.OnMove(0, -5); break;
		case SDLK_LEFT: CCamera::CameraControl.OnMove(5, 0); break;
		case SDLK_RIGHT: CCamera::CameraControl.OnMove(-5, 0); break;
		default: {
				 }
	}
}

void CApp::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
	CCursor::CursorControl.OnMove(mX, mY);
}

void CApp::OnResize(int w,int h) {
	CCamera::CameraControl.SetSize(w, h);
}