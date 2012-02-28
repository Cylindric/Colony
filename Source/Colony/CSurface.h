#ifndef _CSURFACe_H_
#define _CSURFACe_H_

#include "SDL.h"

class CSurface
{
public:
	CSurface();

	static SDL_Surface* OnLoad(char* File);
	static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);
	static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);
};

#endif