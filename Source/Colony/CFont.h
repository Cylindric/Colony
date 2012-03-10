#ifndef _CFONT_H_
#define _CFONT_H_

// Included dependencies
#include <string>
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
	void SetTextSurface(int Font, SDL_Color Colour, std::wstring text);

public:
	bool OnInit();
	TTF_Font* GetFont(int Font);
	void AddTextToSurface(SDL_Surface* Surface, int Font, int X, int Y, SDL_Color Colour, std::wstring text);
	void AddTextToSurface(SDL_Surface* Surface, int Font, int X1, int Y1, int X2, int Y2, SDL_Color Colour, std::wstring text);
};

#endif