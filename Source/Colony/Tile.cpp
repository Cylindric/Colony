#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Soil\SOIL.h"
#include "Tile.h"
#include "Vector2f.h"
#include "Vector2i.h"
#include "Vector4f.h"
#include "Vector6f.h"
#include "Map.h"


CTile::CTile(void)
{
	posX = 0;
	posY = 0;
	typeId = 0;
	textureId = 0;
	isHighlighted = false;
}


CTile::CTile(int x, int y, int type, int tex)
{
	posX = x;
	posY = y;
	typeId = type;
	textureId = tex;
	isHighlighted = false;
}


void CTile::setPosition(int x, int y)
{
	posX = x;
	posY = y;
}


Vector2i CTile::getPosition()
{
	return Vector2i(posX, posY);
}


void CTile::setHighlight(bool active)
{
	isHighlighted = active;
}


void CTile::setTypeId(int id)
{
	typeId = id;
}


void CTile::setTextureId(int id)
{
	textureId = id;
}


Vector2f* CTile::getTilesetCoords(int t)
{
	int texTileSize = CMap::getInstance()->getTileSize();
	int texSize = 256;
	int texColumns = texSize / texTileSize;

	float tw = (float)texTileSize/texSize; // width of a single tile in the big texture map
	float th = (float)texTileSize/texSize; // height of a single tile in the big texture map
	float tu = (t % texColumns)*tw; // bottom-left u-coordinate of the texture map tile
	float tv = (t / texColumns)*th; // bottom-left v-coordinate of the texture map tile
	float j = (0.5f / (float)texSize); // half-pixel offset to prevent tile bleed
	
	Vector2f ret[4];
	ret[0].u = tu+j;
	ret[0].v = 1.0f-(tv+th)+j;
	ret[1].u = tu+tw-j;
	ret[1].v = 1.0f-(tv+th)+j;
	ret[2].u = tu+j;
	ret[2].v = 1.0f-tv-j;
	ret[3].u = tu+tw-j;
	ret[3].v = 1.0f-tv-j;
	return ret;
}


void CTile::onRender(GLuint texture) 
{
	int size = 32;
	float px = (float)posX*size; // bottom-left x-coordinate of the output tile
	float py = (float)posY*size; // bottom-left y-coordinate of the output tile

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glPushMatrix();
	glTranslatef(px, py, 0);

	drawTile(textureId, px, py, size, 0);
	if (isHighlighted) {
		drawTile(TILE_TEX_HIGHLIGHT, px, py, size, 1);
	}

	glPopMatrix();
}


void CTile::drawTile(int tileId, float x, float y, int size, int layer) {

	Vector2f* tCoords = getTilesetCoords(tileId);

	float dx = (float)size; // output width of a single tile
	float dy = (float)size; // output height of a single tile
	float dz = (float)layer / 100; // output z of the tile

	/*  1 3
	 *  0 2 */
	Vector6f vertices[4];

	vertices[0].x = 0.0f;
	vertices[0].y = 0.0f;
	vertices[0].z = dz;
	vertices[0].u = tCoords[0].u;
	vertices[0].v = tCoords[0].v;

	vertices[1].x = dx;
	vertices[1].y = 0.0f;
	vertices[1].z = dz;
	vertices[1].u = tCoords[1].u;
	vertices[1].v = tCoords[1].v;

	vertices[2].x = 0.0f;
	vertices[2].y = dy;
	vertices[2].z = dz;
	vertices[2].u = tCoords[2].u;
	vertices[2].v = tCoords[2].v;

	vertices[3].x = dx;
	vertices[3].y = dy;
	vertices[3].z = dz;
	vertices[3].u = tCoords[3].u;
	vertices[3].v = tCoords[3].v;

	glVertexPointer(3, GL_FLOAT, sizeof(Vector6f), &vertices[0].x);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vector6f), &vertices[0].u);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}