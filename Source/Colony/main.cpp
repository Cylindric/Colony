#include <stdio.h>
#include <math.h>
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Soil\SOIL.h"
#include "Map.h"

using namespace std;

int w;
int h;
GLuint texture;
float deltaMove;


void renderBitmapString(float x, float y, float z, char* string) 
{
	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}


void setOrthographicProjection(void) 
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
}


void restorePerpectiveProjection(void) 
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


void onRenderScene(void) {

	// clear the colour and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// reset any transforms
	glLoadIdentity();

	// get map tiles and render them
	CMap::getInstance()->onRender(texture);

	// text
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	renderBitmapString(10, 10, 0, "Test");
	glColor3f(1.0f, 1.0f, 1.0f);
	glPopMatrix();
	restorePerpectiveProjection();

	// swap the buffers
	glutSwapBuffers();
}


void onChangeSize(int newW, int newH) {
	w = newW;
	h = newH;

	// prevent zero-height screens to prevent DIV/0 errors
	if (h == 0) h = 1;

	// calculate the screen ratio
	float ratio = (float)w / h;

	// reset the GL matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
}


void onKeyDown(unsigned char key, int xx, int yy) 
{
}


void onKeyDown(int key, int xx, int yy) 
{
	switch (key) {
	case GLUT_KEY_LEFT : deltaMove = -0.01f; break;
	case GLUT_KEY_RIGHT : deltaMove = 0.01f; break;
	case GLUT_KEY_UP : deltaMove = 0.5f; break;
	case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
	}
}


void onKeyUp(unsigned char key, int xx, int yy) 
{
	switch (key) {
	case 27: exit(0);
	}
}


void onKeyUp(int key, int xx, int yy) 
{
	switch (key) {
	case 27: exit(0);
	case GLUT_KEY_LEFT : deltaMove = 0.0f; break;
	case GLUT_KEY_RIGHT : deltaMove = 0.0f; break;
	case GLUT_KEY_UP : deltaMove = 0.0f; break;
	case GLUT_KEY_DOWN : deltaMove = 0.0f; break;
	}
}


void onMouseClick(int button, int state, int x, int y) 
{
}


void onMouseMove(int x, int y) 
{
}


void onMousePassiveMotion(int x, int y) 
{
}


int main(int argc, char* args[]) 
{
	// init GLUT and create windows
	glutInit(&argc, args);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Colony");
	glutIgnoreKeyRepeat(true);

	glewInit();

	// register callbacks
	glutDisplayFunc(onRenderScene);
	glutReshapeFunc(onChangeSize);
	glutIdleFunc(onRenderScene);
	glutKeyboardFunc(onKeyDown);
	glutKeyboardUpFunc(onKeyUp);
	glutSpecialFunc(onKeyDown);
	glutSpecialUpFunc(onKeyUp);
	glutMouseFunc(onMouseClick);
	glutMotionFunc(onMouseMove);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	// test a texture load from png
	texture = SOIL_load_OGL_texture (
		"./gfx/tiles.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	if( 0 == texture )
	{
		printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
	}

	CMap::getInstance()->onInit();

	// enter main processing cycle
	glutMainLoop();

	return 1;
}
