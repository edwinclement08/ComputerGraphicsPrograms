/*
 * transformationAboutFixedPoint.c
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

float transformMatrix[3][3] = {
		{1,	0,	0},
		{0,	1,	0},
		{0,	0,	1},
};

void putPixelWithTransform(float x, float y)	{
	float vertex[3] = {x, y, 1};
	float output[3] = {0};

	// slightly optimized as only one vertex
	int i,k;
	for(i = 0; i < 3; i++)
		for(k = 0; k < 3; k++)
			output[i] += transformMatrix[i][k] * vertex[k];

	glVertex2f(output[0], output[1]);
}

void putPixelWithReflection(float x, float y, float cx, float cy)	{
	glBegin(GL_POINTS);
		putPixelWithTransform(cx + x,cy + y);
		putPixelWithTransform(cx + x,cy - y);
		putPixelWithTransform(cx - x,cy + y);
		putPixelWithTransform(cx - x,cy - y);

		putPixelWithTransform(cx + y,cy + x);
		putPixelWithTransform(cx + y,cy - x);
		putPixelWithTransform(cx - y,cy + x);
		putPixelWithTransform(cx - y,cy - x);
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

void setIndentity(float matrix[3][3])	{
	int i,j;
	for(i = 0;i < 3; i++)
		for(j = 0; j< 3; j++)
			if(i == j) matrix[i][j] = 1;
			else matrix[i][j] = 0;
}

void setRotation(float angle) {
	float c = cos(3.141 / 180 * angle);
	float s = sin(3.141 / 180 * angle);

	setIndentity(transformMatrix);
	transformMatrix[0][0] = c; transformMatrix[0][1] = -s;
	transformMatrix[1][0] = s; transformMatrix[1][1] = c;
}

void setTranslate(float x, float y) {
	setIndentity(transformMatrix);
	transformMatrix[0][2] = x;
	transformMatrix[1][2] = y;
}

void multiplyMatrix(float mat1[3][3], float mat2[3][3])	{
	// gives mat1 * mat2 in mat1
	float output[3][3] = {0};

	int i, j, k;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			for(k = 0; k < 3; k++)
				output[i][j] += mat1[i][k] * mat2[k][j];

	// copy back to mat1
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			mat1[i][j] = output[i][j];
}

void doRotation(float angle) {
	float c = cos(3.141 / 180 * angle);
	float s = sin(3.141 / 180 * angle);

	float output[3][3];
	setIndentity(output);
	output[0][0] = c; output[0][1] = -s;
	output[1][0] = s; output[1][1] = c;

	multiplyMatrix(transformMatrix, output);
}


void doTranslate(float x, float y) {
	float output[3][3];
	setIndentity(output);

	output[0][2] = x;
	output[1][2] = y;
	multiplyMatrix(transformMatrix, output);
}

// the function definition should be of type :  void fn_name(void)
void display()	{
	glClearColor(1,1,1,1); 					// Set clear Color to white (Red, green, blue, alpha)
	glClear(GL_COLOR_BUFFER_BIT);			// Clear the color framebuffer

	glColor3f(0,0,0);						// set r,g,b to 0,0,0 i.e. black
											// 3f means 3 floats

//	midPointCircle(100,100, 50);

	// put tx = 200
//	setTranslate(200, 0);
//	midPointCircle(100,100, 50);

	// setRotation as 10, 20, 30, 40 w.r.t origin
//	int i;
//	for(i = 10; i < 50; i+= 10)	{
//		setRotation(i);
//		midPointCircle(100,100, 50);
//	}

//	doRotation(10);
//	midPointCircle(100,100, 50);
//	doRotation(10);
//	midPointCircle(100,100, 50);

	int i;
	for( i = 10; i < 180; i+=10){

		setTranslate(250, 250);
		midPointCircle(0,0, 50);		// now thats is reference circle
		//assuming rotation about 100, 100, 40 deg
		doTranslate(-100, -100);
		doRotation(i);
		doTranslate(100, 100);

		midPointCircle(0,0, 50);		// now thats is reference circle
	}





	glFlush();								// send all the buffer data to screen

}


int main(int argc, char** argv) {
	glutInit(&argc, argv);					// <-Pass all the command line parameters to Glut
	glutInitWindowSize(500, 500);			// Set the window Size
	glutCreateWindow("transformationAboutFixedPoint");
											// Create a window with the specified title

	// The only *glu* function here in main
	gluOrtho2D(0,500, 0, 500);				// define a 2D orthographic projection matrix
	// void gluOrtho2D(double left,  double right,  double bottom,  double top);
	// specify the clipping planes for left, right, bottom and top, in that order <>v^
	// same as window size

	glutDisplayFunc(display);				// callback function called for displaying your stuff
	glutMainLoop();							// start the program

	return 0;
}
