#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL.h>

using namespace std;

int w;
int h;
float angle = 0.0f; // camera angle
float lx = 0.0f; // camera direction
float lz = -1.0f; // camera direction
float x = 0.0f; // camera position
float z = 0.0f; // camera position

float deltaAngle = 0.0f;
float deltaMove = 0.0f;
int xOrigin = 0;

float red = 1.0f;
float green = 1.0f;
float blue = 1.0f;


void drawSnowman() {
	glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);

// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f,0.5f,10,2);
}


void computePosition(float deltaMove) {
	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}


void computeAngle(float deltaAngle) {
	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}


void renderBitmapString(float x, float y, float z, char* string) {
	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}


void setOrthographicProjection(void) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	//glScalef(1, -1, 1);
	//glTranslatef(0, -h, 0);
	glMatrixMode(GL_MODELVIEW);
	
}


void restorePerpectiveProjection(void) {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


void onRenderScene(void) {

	// clear the colour and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// reset any transforms
	glLoadIdentity();

	// set the camera
	gluLookAt(
		x, 1.0f, z,
		x+lx, 1.0f,  z+lz,
		0.0f, 1.0f,  0.0f);

	// ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f,  100.0f);
	glVertex3f( 100.0f, 0.0f,  100.0f);
	glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
	
	// 36 snowmen
	for(int i = -3; i < 3; i++) {
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0f, 0.0f, j * 10.0f);
			drawSnowman();
			glPopMatrix();
		}
	}

	// text
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(5, 30, 0, "Test");
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
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}


void onKeyDown(unsigned char key, int xx, int yy) {
}


void onKeyDown(int key, int xx, int yy) {
	switch (key) {
	case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
	case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
	case GLUT_KEY_UP : deltaMove = 0.5f; break;
	case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
	}
}


void onKeyUp(unsigned char key, int xx, int yy) {
	switch (key) {
	case 27: exit(0);
	}
}


void onKeyUp(int key, int xx, int yy) {
	switch (key) {
	case 27: exit(0);
	case GLUT_KEY_LEFT : deltaAngle = 0.0f; break;
	case GLUT_KEY_RIGHT : deltaAngle = 0.0f; break;
	case GLUT_KEY_UP : deltaMove = 0.0f; break;
	case GLUT_KEY_DOWN : deltaMove = 0.0f; break;
	}
}


void onMouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		} else {
			xOrigin = x;
		}
	}
}


void onMouseMove(int x, int y) {
	if (xOrigin >= 0) {
		deltaAngle = (x - xOrigin) * 0.001f;
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}


void onMousePassiveMotion(int x, int y) {
}


int main(int argc, char* args[]) {
	// init GLUT and create windows
	glutInit(&argc, args);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Colony");
	glutIgnoreKeyRepeat(true);

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
	GLuint tex_2d = SOIL_load_OGL_texture (
		"./gfx/test.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	if( 0 == tex_2d )
	{
		printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
	}

	// enter main processing cycle
	glutMainLoop();

	return 1;
}
