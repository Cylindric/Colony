#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>


float angle = 0.0f; // camera angle
float lx = 0.0f; // camera direction
float lz = -1.0f; // camera direction
float x = 0.0f; // camera position
float z = 0.0f; // camera position

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


void renderScene(void) {
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

	// swap the buffers
	glutSwapBuffers();
}


void changeSize(int w, int h) {
	// prevent zero-height screens to prevent DIV/0 errors
	if (h == 0) h = 1;

	// calculate the screen ratio
	float ratio = (float)w / h;

	// reset the GL matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, ratio, 1, 100);
	glMatrixMode(GL_MODELVIEW);
}


void processNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}


void processSpecialKeys(int key, int x, int y) {
	
	float fraction = 0.5f;

	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;

	case GLUT_KEY_RIGHT:
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;

	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lx * fraction;
		break;

	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lx * fraction;
		break;

	}

}


int main(int argc, char* args[]) {
	// init GLUT and create windows
	glutInit(&argc, args);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Colony");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter main processing cycle
	glutMainLoop();

	return 1;
}
