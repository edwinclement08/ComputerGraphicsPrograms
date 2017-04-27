/*
 * DDA_Algorithm.c
 *
 *  Created on: 27-Apr-2017
 *      Author: edwin
 */


#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>

void dda(float x1, float y1, float x2, float y2)	{
	float dx,dy,steps,xinc,yinc;
	int i;
	dx=x2-x1;
	dy=y2-y1;
	if(abs(dx)>=abs(dy))					// get the divisor
		steps=abs(dx);
	else
		steps=abs(dy);

	xinc=dx/steps;							// find the increments
	yinc=dy/steps;

	glBegin(GL_POINTS);
	glVertex2f(x1,y1);
	for(i=0;i<=steps;i++)
	{
		x1=x1+xinc;
		y1=y1+yinc;
		glVertex2f(x1,y1);					// plot all points

		printf("\nVertex (%d) : [%f, %f]", i, x1, y1);
	}
	glEnd();

}


// the function definition should be of type :  void fn_name(void)
void display()	{
	glClearColor(1,1,1,1); 					// Set clear Color to white (Red, green, blue, alpha)
	glClear(GL_COLOR_BUFFER_BIT);			// Clear the color framebuffer

	glColor3f(0,0,0);						// set r,g,b to 0,0,0 i.e. black
											// 3f means 3 floats

	dda(50,50, 150, 200);					// draw a line (50,50) -> (250, 200)
	glFlush();								// send all the buffer data to screen


}


int main(int argc, char** argv) {
	glutInit(&argc, argv);					// <-Pass all the command line parameters to Glut
	glutInitWindowSize(500, 500);			// Set the window Size
	glutCreateWindow("DDA Algorithm"); 		// Create a window with the specified title


	// The only *glu* function here in main
	gluOrtho2D(0, 500, 0, 500);				// define a 2D orthographic projection matrix
	// void gluOrtho2D(double left,  double right,  double bottom,  double top);
	// specify the clipping planes for left, right, bottom and top, in that order <>v^
	// same as window size

	glutDisplayFunc(display);				// callback function called for displaying your stuff
	glutMainLoop();							// start the program

	return 0;
}
