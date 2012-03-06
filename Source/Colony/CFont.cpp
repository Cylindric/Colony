#include "CFont.h"

CFont CFont::FontControl;

CFont::CFont() {
}

bool CFont::OnInit() {
	this->NormalFont = TTF_OpenFont("./fonts/regular.ttf", 16);
	if(this->NormalFont == NULL) return false;

	this->TileFont = TTF_OpenFont("./fonts/Instruction.ttf", 10);
	if(this->TileFont == NULL) return false;

	return true;
}


TTF_Font* CFont::GetFont(int Font) {
	switch(Font) {
	case FONT_TILE: return this->TileFont; break;
	default: return this->NormalFont; break;
	}
}


void CFont::AddTextToSurface(SDL_Surface* Surface, int Font, int X, int Y, SDL_Color Colour, char Text[]) {
	this->SetTextSurface(Font, Colour, Text);

	SDL_Rect r;
	r.x = X;
	r.y = Y;
	SDL_BlitSurface(this->TextSurface, NULL, Surface, &r);
	SDL_FreeSurface(this->TextSurface);
}


void CFont::AddTextToSurface(SDL_Surface* Surface, int Font, int X1, int Y1, int X2, int Y2, SDL_Color Colour, char Text[]) {
	if(Text[0]==0) return;

	this->SetTextSurface(Font, Colour, Text);

	int offsetX = ((X2-X1) - this->TextSurface->w)/2;
	int offsetY = ((Y2-Y1) - this->TextSurface->h)/2;
	SDL_Rect centred = {X1+offsetX, Y1+offsetY, 0, 0};

	SDL_BlitSurface(this->TextSurface, NULL, Surface, &centred);
	SDL_FreeSurface(this->TextSurface);
}


void CFont::SetTextSurface(int Font, SDL_Color Colour, char Text[]) {
	this->TextSurface = TTF_RenderText_Blended(this->GetFont(Font), Text, Colour);
}