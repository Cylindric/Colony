#ifndef _CCURSOR_H_
#define _CCURSOR_H_

// Forward declared dependencies

// Included dependencies
#include <SDL.h>
#include "Define.h"
#include "CSurface.h"
#include "CMap.h"

class CCursor {

private:
	SDL_Surface* Surf_Tileset;
    int X;
    int Y;

public:
	static CCursor CursorControl;

public:
	CCursor();
	int GetX();
	int GetY();

public:
	bool OnLoad();
	bool OnMove(int MouseX, int MouseY);
	void OnRender(SDL_Surface* Surf_Display);
};

#endif