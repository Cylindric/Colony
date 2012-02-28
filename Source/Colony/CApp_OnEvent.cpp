#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event) {
	CEvent::OnEvent(Event);
}

void CApp::OnExit() {
	Running = false;
}

void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	if(sym == SDLK_ESCAPE) {
		Running = false;
	}
}