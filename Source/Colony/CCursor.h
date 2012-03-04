#pragma once
#include <SDL.h> 
#include "Define.h"
#include "CSurface.h"

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
	bool OnLoad(SDL_Surface* Tileset);
	bool OnMove(int MouseX, int MouseY);
	void OnRender(SDL_Surface* Surf_Display);
};
