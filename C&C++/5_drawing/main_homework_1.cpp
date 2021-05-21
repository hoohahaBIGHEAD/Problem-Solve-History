#include "cg.h"	//���� �ִ� �⺻���� �����
#include "draw.h"	//primitive �׸��� ���� �ҷ����Ҵ�.

//openGL �Լ��� �򰥸���
//www.opengl.org >> Documentation >> OpenGL 2.1

int w = 512;
int h = 512;

vector2D points[100];
int count;

bool moveOn = true;

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

}

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


int main(int argc, char** argv)
{
	//ó�� glutInit���� �������� �޾ƿ� �ʱ�ȭ�Ѵ�.
	glutInit(&argc, argv);
	//���÷��� ��带 GLUT_DOUBLE, RGB ���ķ� �Ѵ�.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//������ ����� �����ش�.
	glutInitWindowSize(w, h);
	glutCreateWindow("Simple interactive application");
	glColor3f(1.0, 0.4, 0.4);

	count = 0;

	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);

	glutMouseFunc(mouse);
	glutDisplayFunc(display);

	//�갡 ��� �ݺ��ȴ�.
	glutMainLoop();
	return 0;
}
