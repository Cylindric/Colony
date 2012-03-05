#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

enum {
	FONT_NORMAL = 0,
	FONT_TILE
};

class CFont {
public:
	CFont();

public:
	static CFont FontControl;

private:
	TTF_Font* NormalFont;
	TTF_Font* TileFont;
	SDL_Surface* TextSurface;
	void SetTextSurface(int Font, SDL_Color Colour, char Text[]);

public:
	bool OnInit();
	TTF_Font* GetFont(int Font);
	void AddTextToSurface(SDL_Surface* Surface, int Font, int X, int Y, SDL_Color Colour, char Text[]);
	void AddTextToSurface(SDL_Surface* Surface, int Font, int X1, int Y1, int X2, int Y2, SDL_Color Colour, char Text[]);
};