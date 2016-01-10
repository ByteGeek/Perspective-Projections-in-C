#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<dos.h>

union REGS i, o;
int x1,y1,x2,y2,status;
double vertex[8][3];
int gd=DETECT,gm;
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


void resetviewport()
{
	rectangle(10,10,530,470);

	rectangle(540,30,620,55);
	rectangle(540,60,620,80);
	rectangle(540,85,620,105);
	rectangle(540,110,620,130);
	rectangle(540,135,630,155);
	rectangle(540,160,630,180);
	rectangle(540,185,620,205);

	//rectangle(540,210,620,230);

	outtextxy(543,32,"draw the");
	outtextxy(555,43,"cube");
	outtextxy(543,62,"1-point");
	outtextxy(545,69,"x-axis");
	outtextxy(543,87,"1-point");
	outtextxy(545,95,"y-axis");
	outtextxy(543,113,"1-point");
	outtextxy(545,121,"z-axis");
	outtextxy(545,138,"2-point");
	outtextxy(545,146,"projection");
	outtextxy(545,163,"3-point");
	outtextxy(545,171,"projection");
	outtextxy(545,187,"Exit");
}

int initmouse()
{
   i.x.ax = 0;
   int86(0X33,&i,&o);
   return ( o.x.ax );
}
 
void showmouseptr()
{
   i.x.ax = 1;
   int86(0X33,&i,&o);
}

void get_mouse_pos(int *mouse_x1,int *mouse_y1,int *button)
{
	i.x.ax=3;
	int86(0x33,&i,&o);
	*mouse_x1=o.x.cx;
	*mouse_y1=o.x.dx;
	*button=o.x.bx&1;
	/*if(button==1)
	{
		closegraph();
		printf("x1=%d,y1=%d,button=%d",mouse_x1,mouse_y1,button);
		getch();
		initgraph(&gd,&gm,"c://tc//bgi");
		resetviewport();
	}*/
}

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
	//clearviewport();
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
	int i,j,cop_x,cop_y,cop_z,plane_x,plane_y,choice,ch,dist,pass=-1;
	int mouse_x1,mouse_y1,button;
	clrscr();
	initgraph(&gd,&gm,"c://tc//bgi");
	initmouse();
	showmouseptr();
	resetviewport();
	restore();
	DrawCube();
	get_mouse_pos(&mouse_x1,&mouse_y1,&button);
	getch();
	while(!kbhit())
	{
		while(button!=1)
		{
			//showmouseptr();
			get_mouse_pos(&mouse_x1,&mouse_y1,&button);
			button=1;
			mouse_x1=541;mouse_y1=35;
		}
		if(button==1)
		{
			if(mouse_x1>=540&&mouse_x1<=620)
			{
				if(mouse_y1>=30&&mouse_y1<=55)
				{
					choice=0;
					pass=1;
				}
			}
			else if(mouse_x1>=540&&mouse_x1<=620)
			{
				if(mouse_y1>=60&&mouse_y1<=80)
				{
					choice=1;
					ch=1;
					pass=1;
				}
			}
			else if(mouse_x1>=540&&mouse_x1<=620)
			{
				if(mouse_y1>=85&&mouse_y1<=105)
				{
					choice=1;
					ch=2;
					pass=1;
				}
			}
			else if(mouse_x1>=540&&mouse_x1<=620)
			{
				if(mouse_y1>=110&&mouse_y1<=130)
				{
					choice=1;
					ch=3;
					pass=1;
				}
			}
			else if(mouse_x1>=540&&mouse_x1<=620)
			{
				if(mouse_y1>=135&&mouse_y1<=155)
				{
					choice=2;
					pass=1;
				}
			}
			else if(mouse_x1>=540&&mouse_x1<=620)
			{
				if(mouse_y1>=160&&mouse_y1<=180)
				{
					choice=3;
					pass=1;
				}
			}
			else if(mouse_x1>=540&&mouse_x1<=620)
			{
				if(mouse_y1>=185&&mouse_y1<=205)
				{
					choice=4;
					pass=1;
				}
			}
			restore();
			if(pass==1)
			{
			switch(choice)
			{
				case 0: restore();
					DrawCube();
					choice=-1;
					pass=-1;
					break;

				case 1: if(ch==1)
					{
						closegraph();
						printf("enter the distance\n");
						scanf("%d",&dist);
						initgraph(&gd,&gm,"c://tc//bgi");
						resetviewport();
						x_perspective(dist);
						restore();
					}
					else if(ch==2)
					{
						closegraph();
						printf("enter the distance\n");
						scanf("%d",&dist);
						initgraph(&gd,&gm,"c://tc//bgi");
						resetviewport();
						y_perspective(dist);
						restore();
					}
					else if(ch==3)
					{
						closegraph();
						printf("enter the distance\n");
						scanf("%d",&dist);
						initgraph(&gd,&gm,"c://tc//bgi");
						resetviewport();
						z_perspective(dist);
						restore();
					}
					pass=-1;
					choice=-1;
					break;

				case 2: closegraph();
					printf("enter the center of projection(x,y,z)\n");
					scanf("%d%d%d",&cop_x,&cop_y,&cop_z);
					initgraph(&gd,&gm,"c://tc//bgi");
					resetviewport();
					rotate_x(atan(cop_x/cop_z));
					z_perspective(cop_z);
					restore();
					choice=-1;
					pass=-1;
					break;

				case 3: closegraph();
					printf("enter the center of projection(x,y,z)\n");
					scanf("%d%d%d",&cop_x,&cop_y,&cop_z);
					initgraph(&gd,&gm,"c://tc//bgi");
					resetviewport();
					rotate_x(atan(cop_x/cop_z));
					rotate_y(atan(cop_y/cop_z));
					z_perspective(cop_z);
					restore();
					choice=-1;
					pass=-1;
					break;

				case 4: exit(0);
			}
			}
		button=-1;
		}
	}
	//closegraph();
}
