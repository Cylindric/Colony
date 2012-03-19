#include <stdio.h>
#include <math.h>
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Soil\SOIL.h"
#include "Map.h"
#include "Tile.h"
#include "Vector2i.h"
#include "Vector2f.h"
#include "Vector4f.h"

using namespace std;

int w;
int h;
float deltaMove;
int lastUpdateTime;

// camera control states
const float scrollFactor = 2.0f;
Vector4f cameraDelta;
Vector2i cameraOffset;
Vector2i mouseDragStart;
bool mouseDragging = false;
Vector2i mouseLocation;
GLint viewportDim[4];

// framerate tracking
unsigned int frames;
unsigned int timebase;
float fps;


Vector2i mouseToMapCoord()
{
	Vector2i v;
	v.x = (mouseLocation.x + cameraOffset.x);
	v.y = (h - mouseLocation.y + cameraOffset.y);
	return v;
}



Vector2i mouseToTileCoord()
{
	Vector2i v;
	v.x = (mouseLocation.x + cameraOffset.x) / 32;
	v.y = (h - mouseLocation.y + cameraOffset.y) / 32;
	return v;
}


void renderBitmapString(float x, float y, float z, char* string) 
{
	glRasterPos3f(x, y, z);
	char *c;
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	//glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)string);
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

	// update the fps
	frames++;
	int t = glutGet(GLUT_ELAPSED_TIME);
	if (t - timebase > 1000) {
		fps = (float)frames * 1000 / (t-timebase);
		timebase = t;
		frames = 0;
	}

	// update the camera position
	cameraOffset.x += (int)cameraDelta.x;
	cameraOffset.y += (int)cameraDelta.y;

	// set the camera viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(cameraOffset.x, w+cameraOffset.x, cameraOffset.y, h+cameraOffset.y);
	glMatrixMode(GL_MODELVIEW);

	// clear the colour and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// reset any transforms
	glLoadIdentity();

	// get map tiles and render them
	CMap::getInstance()->onRender();

	// text
	setOrthographicProjection();
	glLoadIdentity();
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

	// highlight the tile under the cursor
	Vector2i mouseCoords = mouseToTileCoord();
	CMap::getInstance()->setHighlightedTile(mouseCoords.x, mouseCoords.y);

	char status[128];
	sprintf(status, "FPS: %d, Mouse: %d,%d, Cam: %d,%d, Tile: %d,%d", (int)fps, mouseLocation.x, mouseLocation.y, cameraOffset.x, cameraOffset.y, mouseCoords.x, mouseCoords.y);
	glDisable(GL_BLEND);
	renderBitmapString(5, 5, 0.1f, status);
	glEnable(GL_BLEND);

	glColor3f(1.0f, 1.0f, 1.0f);
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
	glMatrixMode(GL_MODELVIEW);
}


void onKeyDown(unsigned char key, int xx, int yy) 
{
}


void onKeyDown(int key, int xx, int yy) 
{
	switch (key) {
	case GLUT_KEY_LEFT : cameraDelta.x = scrollFactor; break;
	case GLUT_KEY_RIGHT : cameraDelta.x = -scrollFactor; break;
	case GLUT_KEY_UP : cameraDelta.y = -scrollFactor; break;
	case GLUT_KEY_DOWN : cameraDelta.y = scrollFactor; break;
	}
}


void onKeyUp(unsigned char key, int xx, int yy) 
{
	switch (key) {
	case 27: exit(0); // escape
	}
}


void onKeyUp(int key, int xx, int yy) 
{
	switch (key) {
	case GLUT_KEY_LEFT : cameraDelta.x = 0.0f; break;
	case GLUT_KEY_RIGHT : cameraDelta.x = 0.0f; break;
	case GLUT_KEY_UP : cameraDelta.y = 0.0f; break;
	case GLUT_KEY_DOWN : cameraDelta.y = 0.0f; break;
	}
}


void onMouseClick(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			if ((mouseLocation.x == mouseDragStart.x) && (mouseLocation.y == mouseDragStart.y))
			{
				CMap::getInstance()->onClick(button, mouseToMapCoord());
			}

			mouseDragging = false;
			mouseDragStart.x = 0;
			mouseDragStart.y = 0;
		} 
		else if (state == GLUT_DOWN)
		{
			mouseDragging = true;
			mouseDragStart.x = x;
			mouseDragStart.y = y;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			CMap::getInstance()->onClick(button, mouseToMapCoord());
		}
	}
}


void onMousePassiveMotion(int x, int y) 
{
	mouseLocation.x = x;
	mouseLocation.y = y;
}


void onMouseMove(int x, int y) 
{
	if (mouseDragging)
	{
		cameraOffset.x -= (x - mouseDragStart.x);
		cameraOffset.y += (y - mouseDragStart.y);
		mouseDragStart.x = x;
		mouseDragStart.y = y;
	}
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
	glutPassiveMotionFunc(onMousePassiveMotion);

	// OpenGL init
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	CMap::getInstance()->onInit("./maps/maze.txt");

	mouseLocation.x = 0;
	mouseLocation.y = 0;

	// enter main processing cycle
	glutMainLoop();

	return 1;
}
