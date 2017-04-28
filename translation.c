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

float translation[16] = {0};

#define NO_OF_VERTICES 4
float translationMatrix[3][3] = {
		{1, 0, 150},
		{0, 1, 1},
		{0, 0, 1}
};

float vertices[3][NO_OF_VERTICES]	= {
		{100	,100	,50		,100},
		{50		,100	,50		,50},
		{1		,1		,1		,1}
};

float output[3][NO_OF_VERTICES];

void multiplyMatrix(float mat1[3][3], float row1, float col1, float mat2[3][NO_OF_VERTICES], float row2, float col2, float output[3][NO_OF_VERTICES]) {
	int i,j,k;
	for(i = 0; i < row1; i++) {
		for(j = 0; j < col2; j++){
			output[i][j] = 0;
			for(k = 0; k < col1; k++)
				output[i][j] += mat1[i][k] * mat2[k][j];
		}
	}
}

void outputVertexMatrix(float vertexes[3][NO_OF_VERTICES], int noOfVertexes) {
	int i;
	glBegin(GL_LINE_LOOP);
	for(i = 0; i < noOfVertexes; i++)
		glVertex2f(vertexes[0][i], vertexes[1][i]);

	glEnd();
}



// the function definition should be of type :  void fn_name(void)
void display()	{
	glClearColor(1,1,1,1); 					// Set clear Color to white (Red, green, blue, alpha)
	glClear(GL_COLOR_BUFFER_BIT);			// Clear the color frame buffer
	glColor3f(0,0,0);						// set r,g,b to 0,0,0 i.e. black
											// 3f means 3 floats

	// the Hard way, the function definitions above are required
	outputVertexMatrix(vertices, 4);
	multiplyMatrix(translationMatrix, 3, 3, vertices, 3, 4, output);
	outputVertexMatrix(output, 4);


	/* The Easy Way */
	// column major order
	translation[0] = 1;		//  |
	translation[5] = 1;		// 	| Identity matrix Part
	translation[10] = 1;	// 	|
	translation[15] = 1;	//  /

	translation[3] = 100;		// tx
	translation[7] = 0;		// ty
	translation[11] = 0;	// tz

	glBegin(GL_LINE_STRIP);
	glVertex2f(200,150);
	glVertex2f(200,200);
	glVertex2f(150,250);
	glVertex2f(200,150);
	glEnd();

	glMultTransposeMatrixf(translation);
	glBegin(GL_LINE_STRIP);
	glVertex2f(200,150);
	glVertex2f(200,200);
	glVertex2f(150,250);
	glVertex2f(200,150);
	glEnd();

	glMultTransposeMatrixf(translation);
	glBegin(GL_LINE_STRIP);
	glVertex2f(200,150);
	glVertex2f(200,200);
	glVertex2f(150,250);
	glVertex2f(200,150);
	glEnd();



	glFlush();								// send all the buffer data to screen

}


int main(int argc, char** argv) {
	glutInit(&argc, argv);					// <-Pass all the command line parameters to Glut
	glutInitWindowSize(500, 500);			// Set the window Size
	glutCreateWindow("Translation");
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
