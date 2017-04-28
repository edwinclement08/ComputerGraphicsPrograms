/*
 * scanLineFilling.c
 *
 *  Created on: Apr 28, 2017
 *      Author: edwin
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
struct line
{
	float x1,y1,x2,y2,m;
	int flag;
};
struct vertex
{
	float x,y;
};
void dda(float x1,float y1,float x2,float y2)
{
	//variable declaration
	float i,dx,dy;
	float xi,yi,steps;//xi is x_incrementand yi is y_increment

	//calculate dx and dy as difference of x and y respectively
	dx=x2-x1;
	dy=y2-y1;

	if(abs(dx)>abs(dy))
		steps=abs(dx);
	else
		steps=abs(dy);

	//increment x and y
	xi=dx/steps;
	yi=dy/steps;

	glBegin(GL_POINTS);
	printf("\n(%f,%f)",x1,y1);
	glVertex2f(x1,y1);

	for(i=0.0;i<=steps;i++)
	{
		x1=x1+xi;
		y1=y1+yi;
		printf("\n(%f,%f)",x1,y1);
		glVertex2f(x1,y1);

	}
	glEnd();
}
void scan_line()
{
	int i,n,ymax=0,ymin,j=0, k;
	float x[10];
	struct line l[10];
	struct vertex v[10];
	ymin=99999;
	printf("Enter the number of vertices");           //number of vertices
	//scanf("%d",&n);

	n=6;
	v[1].x=0;
	v[2].x=100;
	v[3].x=200;
	v[4].x=300;
	v[5].x=400;
	v[6].x=200;

	v[1].y=0;
	v[2].y=100;
	v[3].y=50;
	v[4].y=100;
	v[5].y=0;
	v[6].y=-100;

	for(i=1;i<=n;i++)
	{
		//printf("Enter the x and y value of vertex");
		//scanf("%f%f",&v[i].x,&v[i].y);

		if(ymax<v[i].y)
			ymax=v[i].y;

		if(ymin>v[i].y)
			ymin=v[i].y;
	}
	//printf("ymax=%d ymin=%d",ymax,ymin);
	for(i=1;i<=n;i++)
	{
		if(i==n)
		{
			l[i].x1=v[i].x;
			l[i].y1=v[i].y;
			l[i].x2=v[n-(n-1)].x;
			l[i].y2=v[n-(n-1)].y;

		}
		else
		{
			l[i].x1=v[i].x;
			l[i].y1=v[i].y;
			l[i].x2=v[i+1].x;
			l[i].y2=v[i+1].y;
		}
		l[i].m=(l[i].x2-l[i].x1)/(l[i].y2-l[i].y1);
		l[i].flag=0;

		//printf("x1=%f y1=%f x2=%f y2=%f",l[i].x1,l[i].y1,l[i].x2,l[i].y2);


	}
	for(i=1;i<=n;i++)
		dda(l[i].x1,l[i].y1,l[i].x2,l[i].y2);

	k=0;
	//logic for scan line, scanning from ymax to ymin
	while(ymax>=ymin)
	{
		j=0;
		//for loop to find active edges
		for(i=1;i<=n;i++)
		{
			if((l[i].y1>=ymax && l[i].y2<ymax) || (l[i].y2>=ymax && l[i].y1<ymax))
				l[i].flag=1;
			else
				l[i].flag=0;
			//calculate x value for active edges
			if(l[i].flag==1)
			{
					x[j]=(l[i].x1 + (l[i].m * (ymax-l[i].y1)));
					j++;

			}

		}
		for(i=0;(i<j);i+=2)
			dda(x[i],ymax,x[i+1],ymax);

		ymax=ymax-1;
	}
}



void disp()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,1);

	scan_line();
	glFlush();

}
int main(int argv,char **argc)
{
	glutInit(&argv,argc);
	glutInitWindowSize(600,600);
	glutCreateWindow("Scanline");
	gluOrtho2D(-600,600,-600,600);
	glutDisplayFunc(disp);
	glutMainLoop();
	return 0;
}
