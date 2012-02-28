#include "CApp.h"

void CApp::OnRender() {
	int glyph = 0;
	int tsize = 20;
	int cols = Surf_Display->w / tsize;
	int rows = Surf_Display->h / tsize;

	for(int row = 0; row < rows; row++) {
		for(int col = 0; col < cols; col++) {
			glyph = rand() % 5;
			CSurface::OnDraw(Surf_Display, Surf_Test, tsize*col, tsize*row, glyph*tsize, 0, tsize, tsize);
		}
	}
	SDL_Flip(Surf_Display);
}