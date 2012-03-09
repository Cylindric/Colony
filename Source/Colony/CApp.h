#ifndef _CAPP_H_
#define _CAPP_H_

// Included dependencies
#include "CEvent.h"

// Forward declarations
struct SDL_Surface;

// The actual class
class CApp : public CEvent {

private:
	bool Running;
	SDL_Surface* Surf_Display;
	SDL_Surface* Default_Tileset;

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
	void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
	void OnResize(int w,int h);
};

#endif