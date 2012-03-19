#ifndef _CTILE_H_
#define _CTILE_H_

#include <GL/glew.h>

class Vector2f;
class Vector2i;

enum TileTextureId
{
	TILE_TEX_WALLS = 16,
	TILE_TEX_HIGHLIGHT = 32
};


class CTile
{
public:
	CTile(void);
	CTile(int x, int y, int typeId, int texId);
	void onRender(GLuint texture);
	void setPosition(int x, int y);
	Vector2i getPosition();
	void setTextureId(int id);
	void setTypeId(int id);
	void setHighlight(bool active);

private:
	int typeId;
	int	textureId;
	int posX;
	int posY;
	bool isHighlighted;

	Vector2f* getTilesetCoords(int i);
	void drawTile(int tileId, float x, float y, int size, int layer);
};

#endif