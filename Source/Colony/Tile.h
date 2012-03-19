#ifndef _CTILE_H_
#define _CTILE_H_

#include <GL/glew.h>

class Vector2f;
class Vector2i;

enum TileType
{
	TILE_TYPE_OPEN = 1,
	TILE_TYPE_WALL = 2
};

enum TileTextureId
{
	TILE_TEX_WALLS = 16,
	TILE_TEX_HIGHLIGHT = 32
};

enum TileTextureType
{
	TILE_TEXTYPE_TEE,
	TILE_TEXTYPE_CORNER,
	TILE_TEXTYPE_END,
	TILE_TEXTYPE_CROSS,
	TILE_TEXTYPE_STRAIGHT
};

enum Directions
{
	DIRECTION_N = 1,
	DIRECTION_E = 2,
	DIRECTION_S = 4,
	DIRECTION_W = 8
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
	int getTextureId();
	int getTypeId();
	void setHighlight(bool active);
	void nextTextureId();
	void previousTextureId();
	void cycleType(int type);

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