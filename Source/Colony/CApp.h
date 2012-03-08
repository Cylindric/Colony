#pragma once

// Forward declared dependencies


// Included dependencies
#include <iostream>
#include <direct.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Define.h"

#include "CEvent.h"
//#include "CEntity_Buggy.h"
#include "CMap.h"
#include "CCursor.h"
#include "CFPS.h"
//#include "CCoord.h"
//#include "CEntity.h"
//#include "CCamera.h"
//#include "CSurface.h"
//#include "CFont.h"

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