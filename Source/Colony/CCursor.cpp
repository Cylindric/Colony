#include "CCursor.h"

CCursor CCursor::CursorControl;

CCursor::CCursor() {
	X = 0;
	Y = 0;
}


int CCursor::GetX() {
	return X;
}


int CCursor::GetY() {
	return Y;
}


bool CCursor::OnLoad(SDL_Surface* Tileset) {
	if(Tileset == NULL) {
		return false;
	}
	Surf_Tileset = Tileset;
	return true;
}

bool CCursor::OnMove(int MouseX, int MouseY) {
	X = MouseX - (TILE_SIZE / 2);
	Y = MouseY - (TILE_SIZE / 2);
	return true;
}

void CCursor::OnRender(SDL_Surface* Surf_Display) {
	int TilesetX = (CURSOR_TILE % TILESET_COLS) * TILE_SIZE;
	int TilesetY = (CURSOR_TILE / TILESET_COLS) * TILE_SIZE;

	CSurface::OnDraw(Surf_Display, Surf_Tileset, X, Y, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
}
