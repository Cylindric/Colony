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


bool CCursor::OnLoad() {
	Surf_Tileset = CMap::MapControl.getTileset();
	return true;
}

bool CCursor::OnMove(int MouseX, int MouseY) {
	X = MouseX - (CMap::MapControl.getTileSize() / 2);
	Y = MouseY - (CMap::MapControl.getTileSize() / 2);
	return true;
}

void CCursor::OnRender(SDL_Surface* Surf_Display) {
	int TilesetX = (CURSOR_TILE % CMap::MapControl.getTilesetColumns()) * CMap::MapControl.getTileSize();
	int TilesetY = (CURSOR_TILE / CMap::MapControl.getTilesetColumns()) * CMap::MapControl.getTileSize();

	CSurface::OnDraw(Surf_Display, Surf_Tileset, X, Y, TilesetX, TilesetY, CMap::MapControl.getTileSize(), CMap::MapControl.getTileSize());
}
