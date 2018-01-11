#include <ctype.h>
#include "GL/glut.h"
#include "GL/glu.h"
#include "GL/gl.h"
#include <math.h>
#include <stdio.h>
#define false 0
#define true 1

const int BOARD_X = 31;
const int BOARD_Y = 28;
char tmp_str[40];
bool paused=false;
bool camera=false;
int angle=-60;

GLubyte list[5];
int tp_array[31][28];
int pebbles_left;
double speed1 = 0.1;
double angle1 = 90;
double a=13.5, b=23;
bool animate = false;
int lives=3; //nombre de vies
int points=0;
unsigned char ckey='z';

//fantômes

bool open_move[4];
bool gameover = false;
int num_ghosts = 4; //nombre de fantômes
int start_timer=5; 

void keys();
void mykey(unsigned char key,int x,int y);
bool Open(int a,int b);

#include "ghost.cpp"

Ghost *ghost[4];

#include "board.cpp"
#include "keys.cpp"
#include "render.cpp"

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize(1200, 780);
	glutInitWindowPosition(0,0);
	glutCreateWindow("IMACMAN 3D");
	// glClearColor(1.0,1.0,1.0,1.0);

	init();

	glutDisplayFunc(RenderScene);
	create_list_lib();

	glutKeyboardFunc(mykey);
	glEnable(GL_DEPTH_TEST);

	//init fantômes
	int start_x[4] = {11,12,15,16};
	float ghost_colors[4][3] = {{201,31,31},{0,255,222},{255,200,200},{240,131,13}};
	for (int i = 0; i < num_ghosts; i++)
	{
		ghost[i] = new Ghost(start_x[i],14);
		ghost[i]->x = start_x[i];
		ghost[i]->y = 14;
		ghost[i]->eaten = false;
		ghost[i]->max_speed = 0.1 - 0.01*(float)i;
		ghost[i]->speed = ghost[i]->max_speed;

		for (int j = 0; j < 3; j++)
			ghost[i]->color[j] = ghost_colors[i][j]/255.0f;

	}
	for (int i = 0; i < BOARD_X; i++)
		for (int j = 0; j < BOARD_Y; j++)
			tp_array[i][j] = pebble_array[i][j];

	pebbles_left = 244;

	glShadeModel(GL_SMOOTH);
	glutMainLoop();

	for (int i = 0; i < num_ghosts; i++)
	{
		delete ghost[i];
	}
	return 0;
}