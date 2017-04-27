/*
 * Mid_PointElipse.c
 *
 *  Created on: 27-Apr-2017
 *      Author: edwin
 */




#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>

void putPixelWithReflection(float x, float y, float cx, float cy)	{
	glBegin(GL_POINTS);
		glVertex2f(cx + x,cy + y);
		glVertex2f(cx + x,cy - y);
		glVertex2f(cx - x,cy + y);
		glVertex2f(cx - x,cy - y);

		glVertex2f(cx + y,cy + x);
		glVertex2f(cx + y,cy - x);
		glVertex2f(cx - y,cy + x);
		glVertex2f(cx - y,cy - x);
	glEnd();
}

void midPointCircle(float cx, float cy, float radius)	{
	float x = 0;
	float y = radius;								// The Start point
	float p = 5/4.0 - radius;							// The initial p0

	while(x < y)	{
		putPixelWithReflection(x, y, cx, cy);		// reflect across octants

		x++;
		if (p <= 0)	{
			p +=  (2*x + 1);						// the increment part
		} else {
			y--;
			p +=  (2*x + 1) - 2*y;					// the decrement part
		}
	}
}


// the function definition should be of type :  void fn_name(void)
void display()	{
	glClearColor(1,1,1,1); 					// Set clear Color to white (Red, green, blue, alpha)
	glClear(GL_COLOR_BUFFER_BIT);			// Clear the color framebuffer

	glColor3f(0,0,0);						// set r,g,b to 0,0,0 i.e. black
											// 3f means 3 floats

	midPointCircle(250,250, 170);		 	// draw a circle
	glFlush();								// send all the buffer data to screen

}


int main(int argc, char** argv) {
	glutInit(&argc, argv);					// <-Pass all the command line parameters to Glut
	glutInitWindowSize(500, 500);			// Set the window Size
	glutCreateWindow("Mid-Point Circle Generation Algorithm");
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
