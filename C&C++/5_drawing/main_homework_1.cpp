#include "cg.h"	//���� �ִ� �⺻���� �����
#include "draw.h"	//primitive �׸��� ���� �ҷ����Ҵ�.

//openGL �Լ��� �򰥸���
//www.opengl.org >> Documentation >> OpenGL 2.1

int w = 1024;
int h = 1024;

struct polytype {
	vector2D a, b;
	int pmode;// 1: line, 2: triangle, 3:circle, 4:rectangle
	vector3D color;
	bool on = false;
};

polytype polygon[100];
int index = 0;

int mode = 1;
vector3D color = vector3D(0.9, 0.9, 0.8);
bool on = true;


/*
vector2D points[100];
int count;
*/

bool moveOn = true;

/*
void idle() {
	for (int i = 0; i < count; i++)
	{
		//2. ���콺 (�߰���ư) ������ �ִϸ��̼� on/off
		if (moveOn)
		{
			points[i].x += 0.01;
		}

		glutPostRedisplay();
	}
}
*/

void reshape(int rw, int rh) {
	w = rw;
	h = rh;
	glViewport(0, 0, w, h);
}


//1. Ű���� �Է¿� ���� ������ �ٲ�
void key(unsigned char key, int x, int y) {
	if (key == 'Q' || key == 'q')
		exit(0);
	if (key == 'R' || key == 'r') {
		glColor3f(1.0, 0.0, 0.0);
		glEnd();
	}if (key == 'G' || key == 'g') {
		glColor3f(0.0, 1.0, 0.0);
		glEnd();
	}if (key == 'B' || key == 'b') {
		glColor3f(0.0, 0.0, 1.0);
		glEnd();
	}if (key == 'C' || key == 'c') {
		glColor3f(0.0, 1.0, 1.0);
		glEnd();
	}if (key == 'P' || key == 'p') {
		glColor3f(1.0, 0.0, 1.0);
		glEnd();
	}if (key == 'Y' || key == 'y') {
		glColor3f(1.0, 1.0, 0.0);
		glEnd();
	}
	else if (key == '1')
		mode = 1; // line
	else if (key == '2')
		mode = 2;
	else if (key == '3')
		mode = 3;
	else if (key == '4')
		mode = 4;

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
	else if (key == '5')
		mode = 5;	//select
	else if (key == 'r') color = vector3D(1.0, 0.0, 0.0);
	else if (key == 'g') color = vector3D(0.0, 1.0, 0.0);
	else if (key == 'b') color = vector3D(0.0, 0.0, 1.0);
	else if (key == 'c') color = vector3D(0.0, 0.7, 0.7);
	else if (key == 'p') color = vector3D(0.7, 0.0, .7);
	else if (key == 'y') color = vector3D(0.7, 0.7, 0.0);
	else if (key == 'n') {
		if (on == true) on = false;
		else on = true;
	}
}



/*
void mouse(GLint button, GLint state, GLint x, GLint y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		exit(0);
	}
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		if (moveOn)
			moveOn = false;
		else
			moveOn = true;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//������ >> OpenGL ��ǥ ��ȯ
		points[count].x = (float)x / (float)w * 2.0 - 1.0;
		points[count].y = -(float)y / (float)h * 2.0 + 1.0;
		count++;
	}
}
*/

void select(vector2D a, vector2D b) {
	float px, py, tempx1, tempy1, tempx2, tempy2;
	//px = (float)x / (float)w * 2.0 - 1.0;
	//py = -(float)y / (float)h * 2.0 + 1.0;
	vector2D va, vb, vc;
	va = a;
	vb = b;
	vc = vb - va;
	px = a.x;
	py = b.y;
	for (int i = index-1; i >= 0; i--)
	{
		va = polygon[i].a;
		vb = polygon[i].b;
		if (va.x < vb.x) {
			tempx1 = va.x;
			tempx2 = vb.x;
		}
		else
		{
			tempx1 = vb.x;
			tempx2 = va.x;
		}
		if (va.y < vb.y) {
			tempy1 = va.y;
			tempy2 = vb.y;
		}
		else
		{
			tempy1 = vb.y;
			tempy2 = va.y;
		}

		if (tempx1 <= px && px <= tempx2 && tempy1 <= py && py <= tempy2)
		{
			polygon[i].on = true;
			polygon[i].a.x += vc.x;
			polygon[i].a.y += vc.y;
			polygon[i].b.x += vc.x;
			polygon[i].b.y += vc.y;
			//polygon[i].on = false;
			break;
		}
		glutPostRedisplay();

	}
}


void mymouse(int button, int state, int x, int y)
{
	float px, py;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		px = (float)x / (float)w * 2.0 - 1.0;
		py = -(float)y / (float)h * 2.0 + 1.0;

		if (polygon[index].on == true) index++;
		polygon[index].a = vector2D(px, py);
		polygon[index].color = color;
		polygon[index].pmode = mode;
		

	}

}

void mymousemotion(int x, int y)
{
	float px, py;
	px = (float)x / (float)w * 2.0 - 1.0;
	py = -(float)y / (float)h * 2.0 + 1.0;
	polygon[index].b = vector2D(px, py);
	polygon[index].on = true;

	glutPostRedisplay();
}


/*
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	//glClearColor(0.8, 0.8, 0.8, 1.0);

	//glColor3f(1.0, 0.4, 0.4);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < count; i++)
	{
		glVertex3f(points[i].x, points[i].y, 0.0);
	}
	glEnd();
	//�ʹ� ���� ����Ǿ �ð��� �־���
	Sleep(100);
	glutSwapBuffers();
}
*/


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
				triangle(a, b);
			}
			else if (mode == 3) {
				ellipse(a, b);
			}
			else if (mode == 4) {  //rectangle
				rect(a, b);
			}
			else if (mode == 5) {
				//select mode
				select(a.x, a.y);
			}
		}
	}

	glutSwapBuffers();
}


int main(int argc, char** argv)
{
	//ó�� glutInit���� �������� �޾ƿ� �ʱ�ȭ�Ѵ�.
	glutInit(&argc, argv);
	//���÷��� ��带 GLUT_DOUBLE, RGB ���ķ� �Ѵ�.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//������ ����� �����ش�.
	glutInitWindowSize(w, h);
	glutCreateWindow("Simple interactive application");
	
	
	//glColor3f(1.0, 0.4, 0.4);

	//count = 0;

	//glutIdleFunc(idle);
	//glutReshapeFunc(reshape);
	//glutKeyboardFunc(key);


	//glutDisplayFunc(display);
	glutDisplayFunc(mydisplay);
	glutMouseFunc(mymouse);
	//glutMouseFunc(mouse);
	//glutDisplayFunc(display);
	glutMotionFunc(mymousemotion);
	//glutKeyboardFunc(key);
	glutKeyboardFunc(mykey);

	//�갡 ��� �ݺ��ȴ�.
	glutMainLoop();
	return 0;
}
