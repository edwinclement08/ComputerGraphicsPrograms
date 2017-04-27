/*
Created on:22/03/2017
Name:Kaumudi Kulkarni
Class: SE COMPS
Roll no:7646
Program:X and Y Shear
*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<glut.h>

//takes initial object and plots the final object
void matrixMul(float shearMatrix[][3],float a[][10], int n)		
{
	int i,j,k;
	float result[3][10];
	for(i=0;i<3;i++)
	{
		for(j=0;j<n;j++)
		{
			result[i][j]=0;
			for(k=0;k<3;k++)
				result[i][j]+=shearMatrix[i][k]*a[k][j];
		}
	}
	glBegin(GL_LINE_LOOP);
	glColor3f(0,1,0);
	for(i=0;i<n;i++)
	{
		glVertex2f(result[0][i],result[1][i]);
	}
	glEnd();
	glFlush();
}

//creates the shear matrix
void	shearObject(float a[][10], int n)
{
	int choice;
	float shearMatrix[3][3]={1,0,0},
								{0,1,0},
								{0,0,1};
	printf("enter 1) X Shear \n\t 2) Y Shear\n");
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("\nY factor:");
		scanf("%f",&shearMatrix[0][2]);
	}
	else if(choice==2)
	{
		printf("\nY factor:");
		scanf("%f",&shearMatrix[1][2]);
	}
	matrixMul(shearMatrix,a,n);
}

//takes the co ordiates of initial object ad plots it
void takeInput()
{
	int n;
	float a[3][10];
	printf("enter the no of points:");
	scanf("%d",&n);
	printf("enter the points:");
	for(i=0;i<n;i++)
	{
		scanf("%f%f",&a[0][i],&a[1][i]);
		a[2][i]=1.0;
	}
	glBegin(GL_LINE_LOOP);
	for(i=0;i<n;i++)
	{
		glVertex2f(a[0][i],a[1][i]);
	}
	glEnd();
	glFlush();
	shearObject(a,n);
}

void disp()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
	takeInput();
	glFlush();
}

int main(int argv, char **argc)
{
	glutInit(&argv,argc);
	glutInitWindowSize(300,300);
	glutCreateWindow("Shear");
	glutOrtho2D(-300,300,-300,300);

	glutDisplayFunc(disp);
	glutMainLoop();
	return 0;
}