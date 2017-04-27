/*
 * translation.c
 *
 *  Created on: Apr 28, 2017
 *      Author: edwin
 */

#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>
#include<math.h>

float rotation[16] = {0};


// the function definition should be of type :  void fn_name(void)
void display()	{
	glClearColor(1,1,1,1); 					// Set clear Color to white (Red, green, blue, alpha)
	glClear(GL_COLOR_BUFFER_BIT);			// Clear the color framebuffer

	glColor3f(0,0,0);						// set r,g,b to 0,0,0 i.e. black
											// 3f means 3 floats

	// column major order
	rotation[0] = 1;		//  |
	rotation[5] = 1;		// 	| Identity matrix Part
	rotation[10] = 1;	// 	|
	rotation[15] = 1;	//  /


	// column major order
	rotation[0] = cos(3.14/180.0 * 12);		//  |
	rotation[1] = -sin(3.14/180.0 * 12);		// 	| Identity matrix Part
	rotation[4] = sin(3.14/180.0 * 12);	// 	|
	rotation[5] = cos(3.14/180.0 * 12);	//  /


	glBegin(GL_LINE_STRIP);
	glVertex2f(100,50);
	glVertex2f(100,100);
	glVertex2f(50,50);
	glVertex2f(100,50);
	glEnd();

	glMultTransposeMatrixf(rotation);

	glBegin(GL_LINE_STRIP);
	glVertex2f(100,50);
	glVertex2f(100,100);
	glVertex2f(50,50);
	glVertex2f(100,50);
	glEnd();


	glMultTransposeMatrixf(rotation);

	glBegin(GL_LINE_STRIP);
	glVertex2f(100,50);
	glVertex2f(100,100);
	glVertex2f(50,50);
	glVertex2f(100,50);
	glEnd();

	glFlush();								// send all the buffer data to screen

}


int main(int argc, char** argv) {
	glutInit(&argc, argv);					// <-Pass all the command line parameters to Glut
	glutInitWindowSize(500, 500);			// Set the window Size
	glutCreateWindow("Rotation");
											// Create a window with the specified title

	// The only *glu* function here in main
	gluOrtho2D(0, 500, 0, 500);				// define a 2D orthographic projection matrix
	// void gluOrtho2D(double left,  double right,  double bottom,  double top);
	// specify the clipping planes for left, right, bottom and top, in that order <>v^
	// same as window size

	glutDisplayFunc(display);				// callback function called for displaying your stuff
	glutMainLoop();							// start the program

	return 0;
}
