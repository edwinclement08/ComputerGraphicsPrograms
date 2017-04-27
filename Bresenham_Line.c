/*
 * Bresenham_Line.c
 *
 *  Created on: 27-Apr-2017
 *      Author: edwin
 */

#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>

void bresenham(float x1, float y1, float x2, float y2)	{
	float dx, dy;
	dx=x2-x1;
	dy=y2-y1;

	float p = 2*dy - dx;					// Initial Decision parameter
	float x = x1, y = y1;

	glBegin(GL_POINTS);
	glVertex2f(x,y);

	// m <= 1
	if(dy <= dx)	{
		while(x <= x2) {
			x++;							// increment x till it reaches x2
			if(p < 0){
				p += 2*dy;					// increment p with 2dy till its more than 0
			} else {
				y++;
				p += 2*dy - 2*dx;			// decrement with 2dx now that its tipped over
			}
			glVertex2f(x,y);
		}
	} else {								// m > 1, replace x with y and vice versa
		while(y <= y2) {
			y++;
			if(p < 0){
				p += 2*dx;
			} else {
				x++;
				p += 2*dx - 2*dy;
			}
			glVertex2f(x,y);
		}
	}
	glEnd();

}


// the function definition should be of type :  void fn_name(void)
void display()	{
	glClearColor(1,1,1,1); 					// Set clear Color to white (Red, green, blue, alpha)
	glClear(GL_COLOR_BUFFER_BIT);			// Clear the color framebuffer

	glColor3f(0,0,0);						// set r,g,b to 0,0,0 i.e. black
											// 3f means 3 floats

	bresenham(50,50, 250, 120);					// draw a line (50,50) -> (250, 200)
	glFlush();								// send all the buffer data to screen
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);					// <-Pass all the command line parameters to Glut
	glutInitWindowSize(500, 500);			// Set the window Size
	glutCreateWindow("Bresenham Line Algorithm"); 		// Create a window with the specified title

	// The only *glu* function here in main
	gluOrtho2D(0, 500, 0, 500);				// define a 2D orthographic projection matrix
	// void gluOrtho2D(double left,  double right,  double bottom,  double top);
	// specify the clipping planes for left, right, bottom and top, in that order <>v^
	// same as window size

	glutDisplayFunc(display);				// callback function called for displaying your stuff
	glutMainLoop();							// start the program

	return 0;
}
