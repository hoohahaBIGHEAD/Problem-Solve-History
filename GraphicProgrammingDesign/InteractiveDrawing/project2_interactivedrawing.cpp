/*
   INTERACTIVE DRAWING
*/

#include "cg.h"
#include "draw.h"

int w = 1024;
int h = 1024;

struct polytype {
	vector2D a, b;
	int pmode;// 1: line, 2: triangle, 3:circle, 4:rectangle
	vector3D color;
	bool on=false;
};

polytype polygon[100];
int index = 0;

int mode = 1;
vector3D color = vector3D(0.9, 0.9, 0.8);

void mydisplay()
{
	vector2D a, b;
	vector3D color = vector3D(0.9, 0.0, 0.9);
	int mode = 1;

	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i <= index; i++) {
		if (polygon[i].on == true) {
			a = polygon[i].a;
			b = polygon[i].b;
			color = polygon[i].color;
			mode = polygon[i].pmode;

			glColor3f(color.x, color.y, color.z);
			if (mode == 1)
				line(a, b);
			else if (mode == 2) {
				//triangle
			}
			else if (mode == 3) {
				//ellipse
			}
			else if (mode == 4) {  //rectangle
				rect(a, b);
			}
		}
	}
	
	glutSwapBuffers();
}

void mymouse(int button, int state, int x, int y)
{
	float px, py;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		px=(float)x/(float)w*2.0-1.0;
		py = -(float)y/(float)h*2.0+1.0;

		if (polygon[index].on == true) index++;
		polygon[index].a = vector2D(px, py);
		polygon[index].color = color;
		polygon[index].pmode = mode;
	}
}

void mymousemotion(int x, int y)
{
	float px, py;
	px = (float)x/(float)w*2.0-1.0;
	py = -(float)y/(float)h*2.0+1.0;
	polygon[index].b = vector2D(px, py);
	polygon[index].on = true;
	
	glutPostRedisplay();
}

void mykey(unsigned char key, int x, int y)
{
	if ((key == 'Q') | (key == 'q'))
		exit(0);
	else if (key == '1')
		mode = 1; // line
	else if (key == '2')
		mode = 2;
	else if (key == '3')
		mode = 3;
	else if (key == '4')
		mode = 4;
	else if (key == 'r')
		color = vector3D(1.0, 0.0, 0.0);
	else if (key == 'y')
		color = vector3D(1.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(w, h);
	glutCreateWindow("simple");

	glutDisplayFunc(mydisplay);
	glutMouseFunc(mymouse);
	glutMotionFunc(mymousemotion);
	glutKeyboardFunc(mykey);

	glutMainLoop();
}
