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
	glEnd();
}

void midPointEllipse(float cx, float cy, float rx, float ry)	{
	float x = 0;
	float y = ry;									// The Start point
	float px = 0;
	float py = 2*rx*rx * y;

	putPixelWithReflection(x, y, cx, cy);		// reflect across octants

	float pk = ry*ry - (rx*rx * ry) + (0.25 * rx*rx);
	while(px < py)	{
		x++;
		px += 2 * ry*ry;

		if(pk < 0) {
			pk += ry*ry + px;
		} else {
			y--;
			py -= 2 * rx*rx;
			pk += ry*ry + px - py;
		}

		putPixelWithReflection(x, y, cx, cy);		// reflect across 4 octants
	}

	// Only a minor change without this line, so ignoring it.
	// pk = ry*ry*(x + 0.5)*(x + 0.5) + rx*rx * (y - 1) * (y - 1) - rx*rx*ry*ry;
	while(y > 0) 	{
		y--;
		py -= 2 * rx*rx;
		if(pk > 0)	{
			pk += rx*rx - py;
		} else {
			x++;
			px += 2 * ry*ry;
			pk += rx*rx - py + px;
		}
		putPixelWithReflection(x, y, cx, cy);		// reflect across 4 octants
	}
}


// the function definition should be of type :  void fn_name(void)
void display()	{
	glClearColor(1,1,1,1); 					// Set clear Color to white (Red, green, blue, alpha)
	glClear(GL_COLOR_BUFFER_BIT);			// Clear the color framebuffer

	glColor3f(0,0,0);						// set r,g,b to 0,0,0 i.e. black
											// 3f means 3 floats
	midPointEllipse(250,250, 140, 150);		// draw a circle
	glFlush();								// send all the buffer data to screen

}


int main(int argc, char** argv) {
	glutInit(&argc, argv);					// <-Pass all the command line parameters to Glut
	glutInitWindowSize(500, 500);			// Set the window Size
	glutCreateWindow("Mid-Point Ellipse Algorithm");
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
