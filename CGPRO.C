#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>

int x1,y1,x2,y2;
double vertex[8][3];
double edge[12][2]={	{0,1},
			{1,2},
			{2,3},
			{3,0},
			{4,5},
			{5,6},
			{6,7},
			{7,4},
			{0,4},
			{1,5},
			{2,6},
			{3,7}	};

/*void getProjectedPoints(int *x,int *y,int *z)
{
	if(*z<0)
	{
		*x=*x - (*z/4);
		*y=*y + (*z/4);
	}
	else
	{
		*x=*x - (*z/4);
		*y=*y + (*z/4);
	}
}*/

void restore()
{
	int i;
	int cube[8][3]={
	     {0,0,0},      //  back left top
	     {0,100,0},     //  back right top
	     {100,100,0},     //  back right bottom
	     {100,0,0},      //  back left bottom
	     {0,0,100},     //  front left top
	     {0,100,100},    //  front right top
	     {100,100,100},    //  front right bottom
	     {100,0,100}      //  front left bottom
	      };
	for(i=0;i<8;i++)
	{
		vertex[i][0]=cube[i][0];
		vertex[i][1]=cube[i][1];
		vertex[i][2]=cube[i][2];
	}
}

void DrawCube()
{
	int i;
	clearviewport();
	/*for(i=0;i<8;i++)
	{
		printf("%d,%d,%d\n",vertex[i][0],vertex[i][1],vertex[i][2]);
	}*/
	for(i=0;i<12;i++)
	{
		if(i>=0&&i<=3)
		{
			setcolor(2);
		}
		else if(i>=4&&i<=7)
		{
			setcolor(3);
		}
		else
		{
			setcolor(15);
		}
		x1=vertex[edge[i][0]][0] + vertex[edge[i][0]][2]*(cos(2.3562));
		y1=vertex[edge[i][0]][1] - vertex[edge[i][0]][2]*(sin(2.3562));
		x2=vertex[edge[i][1]][0] + vertex[edge[i][1]][2]*(cos(2.3562));
		y2=vertex[edge[i][1]][1] - vertex[edge[i][1]][2]*(sin(2.3562));
		line(x1+300,200-y1,x2+300,200-y2);
		//printf("%d,%d and %d,%d\n",x1,y1,x2,y2);
	}
	getch();
}

void rotate_x(float theta)
{
	double temp,temp1;
	int i;
	theta=(theta*3.14)/180;
	for(i=0;i<8;i++)
	{
		vertex[i][0]=vertex[i][0];
		temp=vertex[i][1];
		temp1=vertex[i][2];
		vertex[i][1]=temp*cos(theta)-temp1*sin(theta);
		vertex[i][2]=temp*sin(theta)+temp1*cos(theta);
	}
}

void rotate_y(float theta)
{
	double temp,temp1;
	int i;
	theta=(theta*3.14)/180;
	for(i=0;i<8;i++)
	{
		vertex[i][1]=vertex[i][1];
		temp=vertex[i][0];
		temp1=vertex[i][2];
		vertex[i][0]=temp*cos(theta)+temp1*sin(theta);
		vertex[i][2]=-temp*sin(theta)+temp1*cos(theta);
	}
}

void rotate_z(float theta)
{
	double temp,temp1;
	int i;
	theta=(theta*3.14)/180;
	for(i=0;i<8;i++)
	{
		vertex[i][2]=vertex[i][2];
		temp=vertex[i][0];
		temp1=vertex[i][1];
		vertex[i][0]=temp*cos(theta)-temp1*sin(theta);
		vertex[i][1]=temp*sin(theta)+temp1*cos(theta);
	}
}

void x_perspective(int dist)
{
	int i;
	for(i=0;i<8;i++)
	{
		vertex[i][0]=vertex[i][0]/(vertex[i][0]/dist+1);
		vertex[i][1]=vertex[i][1]/(vertex[i][0]/dist+1);
		vertex[i][2]=vertex[i][2]/(vertex[i][0]/dist+1);
	}
	DrawCube();
}

void y_perspective(int dist)
{
	int i;
	for(i=0;i<8;i++)
	{
		vertex[i][1]=vertex[i][1]/(vertex[i][1]/dist+1);
		vertex[i][0]=vertex[i][0]/(vertex[i][1]/dist+1);
		vertex[i][2]=vertex[i][2]/(vertex[i][1]/dist+1);
	}
	DrawCube();
}

void z_perspective(int dist)
{
	int i;
	for(i=0;i<8;i++)
	{
		vertex[i][2]=vertex[i][2]/(vertex[i][2]/dist+1);
		vertex[i][0]=vertex[i][0]/(vertex[i][2]/dist+1);
		vertex[i][1]=vertex[i][1]/(vertex[i][2]/dist+1);
	}
	DrawCube();
}

void main()
{
	float x,y,p1,p2;
	int i,j,cop_x,cop_y,cop_z,plane_x,plane_y,choice,ch,dist;
	int gd=DETECT,gm;
	clrscr();
	while(1)
	{
		printf("0--> Draw object\n");
		printf("1--> one point perspective projection\n");
		printf("2--> two point perspective projection\n");
		printf("3--> three point perspective projection\n");
		printf("4--> exit\n");
		printf("Enter your choice\n");
		scanf("%d",&choice);
		restore();
		switch(choice)
		{
			case 0: initgraph(&gd,&gm,"c://tc//bgi");
				setcolor(15);
				restore();
				DrawCube();
				closegraph();
				break;

			case 1: printf("perspective projection about?..\n");
				printf("1--> x-axis\n2--> y-axis\n3--> z-axis\n");
				printf("enter your choice\n");
				scanf("%d",&ch);
				if(ch==1)
				{
					printf("enter the distance\n");
					scanf("%d",&dist);
					initgraph(&gd,&gm,"c://tc//bgi");
					x_perspective(dist);
					closegraph();
					restore();
				}
				else if(ch==2)
				{
					printf("enter the distance\n");
					scanf("%d",&dist);
					initgraph(&gd,&gm,"c://tc//bgi");
					y_perspective(dist);
					closegraph();
					restore();
				}
				else if(ch==3)
				{
					printf("enter the distance\n");
					scanf("%d",&dist);
					initgraph(&gd,&gm,"c://tc//bgi");
					z_perspective(dist);
					closegraph();
					restore();
				}
				else
				{
					printf("invalid entry\n");
				}
				break;

			case 2: printf("enter the center of projection\n");
				scanf("%d%d%d",&cop_x,&cop_y,&cop_z);
				initgraph(&gd,&gm,"c://tc//bgi");
				rotate_x(atan(cop_x/cop_z));
				z_perspective(cop_z);
				closegraph();
				restore();
				break;

			case 3: printf("enter the center of projection\n");
				scanf("%d%d%d",&cop_x,&cop_y,&cop_z);
				initgraph(&gd,&gm,"c://tc//bgi");
				rotate_x(atan(cop_x/cop_z));
				rotate_y(atan(cop_y/cop_z));
				z_perspective(cop_z);
				closegraph();
				restore();
				break;

			case 4: exit(0);

			default: printf("invalid selection\n");
					getch();
					break;
		}
	}
	//closegraph();
}