#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL.h>
#include "Tile.h"


CTile::CTile(void)
{
}


CTile::~CTile(void) 
{
}


void CTile::onRender(GLuint texture) 
{
	int size = 50;
	int texSize = 256;
	int tileSize = 20;

	float t = (float)tileSize/texSize;
	float dx = (float)size;
	float dy = (float)size;
	float px = (float)x*size;
	float py = (float)y*size;

	float tx = (tileId % 12)*t;
	float ty = (tileId / 12)*t;

	glPushMatrix();
	glTranslatef(px, py, 0);

	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_TRIANGLE_STRIP); 
	glTexCoord2f(tx, 1.0f-(ty+t)); glVertex3f(0.0f, 0.0f, 0.0f); //A
	glTexCoord2f(tx+t,    1.0f-(ty+t)); glVertex3f(dx,   0.0f, 0.0f); //C
	glTexCoord2f(tx, 1.0f-ty);   glVertex3f(0.0f,   dy, 0.0f); //B
	glTexCoord2f(tx+t,    1.0f-ty);   glVertex3f(dx,     dy, 0.0f); //D
	glEnd();

	glPopMatrix();
}
