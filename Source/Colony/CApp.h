#ifndef _CAPP_H_
#define _CAPP_H_

#include "SDL.h"
#include "CEvent.h"
#include "CSurface.h"

class CApp : public CEvent {

private:
	bool Running;
	SDL_Surface* Surf_Display;
	SDL_Surface* Surf_Test;

public:
	CApp();
	int OnExecute();

public:
	bool OnInit();
	void OnEvent(SDL_Event* Event);
	void OnLoop();
	void OnExit();
	void OnRender();
	void OnCleanup();
	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

};

#endif