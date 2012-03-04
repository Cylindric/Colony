#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Define.h"
#include "CEvent.h"
#include "CSurface.h"
#include "CMap.h"
#include "CArea.h"
#include "CCamera.h"
#include "CCursor.h"
#include "CFPS.h"
#include "CEntity.h"
#include "CEntity_Buggy.h"
#include "CFont.h"

class CApp : public CEvent {

private:
	bool Running;
	SDL_Surface* Surf_Display;
	SDL_Surface* Default_Tileset;
	SDL_Surface* Buggy_Tileset;
	CEntity_Buggy Buggy1;

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