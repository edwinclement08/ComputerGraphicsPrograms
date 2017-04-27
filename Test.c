#include<stdio.h>
#include<stdlib.h>

#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you can't make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;

        // Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

        // Reset Matrix
	glLoadIdentity();

	// Set the view port to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Model view
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable (GL_DEPTH_TEST);   // Enables Depth Testing
    glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glLoadIdentity();
	gluLookAt(	0.0f, 0.0f, 10.0f,
			1.0f, 1.0f,  1.0f,
			0.0f, 1.0f,  0.0f);


	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
	switch(key) {
	case 'q':
		break;
	case 'a':
		break;
	case 'w':
		break;
	case 's':
		break;
	case 'e':
		break;
	case 'd':

		break;


	}

}

void processSpecialKeys(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_F1 : break;
		case GLUT_KEY_F2 : break;
		case GLUT_KEY_F3 : break;
	}
}


void processMouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
	}
}

void processMouseMotion(int x, int y) {
}

int main(int argc, char **argv) {
	// test texture


	// initialize GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1024,728);
	glutCreateWindow("CG Project - Edwin");
	glClearColor(1,1,1,1);

	// register callback
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);


	// here are the new entries
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(processMouseClick);
	glutMotionFunc(processMouseMotion);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
