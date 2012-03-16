#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Soil\SOIL.h"
#include "Tile.h"
#include "Vector4f.h"


CTile::CTile(void)
{
	CTile(0, 0, 0);
}


CTile::CTile(int x, int y, int texId)
{
	posX = x;
	posY = y;
	textureId = texId;
}


CTile::~CTile(void) 
{
}


void CTile::setPosition(int x, int y)
{
	posX = x;
	posY = y;
}


void CTile::setTextureId(int id)
{
	textureId = id;
}


void CTile::onRender(GLuint texture) 
{
	int size = 20;
	int texSize = 256;
	int tileSize = 20;

	float tw = (float)tileSize/texSize; // width of a single tile in the big texture map
	float th = (float)tileSize/texSize; // height of a single tile in the big texture map
	float dx = (float)size; // output width of a single tile
	float dy = (float)size; // output height of a single tile
	float px = (float)posX*size; // bottom-left x-coordinate of the output tile
	float py = (float)posY*size; // bottom-left y-coordinate of the output tile

	float tu = (textureId % 12)*tw; // bottom-left u-coordinate of the output tile
	float tv = (textureId / 12)*th; // bottom-left v-coordinate of the output tile

	float j = (0.5f / (float)texSize); // half-pixel offset to prevent tile bleed


	/*  1 3
	 *  0 2 */
	Vector4f vertices[4];

	vertices[0].x = 0.0f;
	vertices[0].y = 0.0f;
	vertices[0].u = tu+j;
	vertices[0].v = 1.0f-(tv+th)+j;

	vertices[1].x = dx;
	vertices[1].y = 0.0f;
	vertices[1].u = tu+tw-j;
	vertices[1].v = 1.0f-(tv+th)+j;

	vertices[2].x = 0.0f;
	vertices[2].y = dy;
	vertices[2].u = tu+j;
	vertices[2].v = 1.0f-tv-j;

	vertices[3].x = dx;
	vertices[3].y = dy;
	vertices[3].u = tu+tw-j;
	vertices[3].v = 1.0f-tv-j;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glPushMatrix();
	glTranslatef(px, py, 0);
	glVertexPointer(2, GL_FLOAT, sizeof(Vector4f), &vertices[0].x);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vector4f), &vertices[0].u);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glPopMatrix();
}
