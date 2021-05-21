#include "cg.h"	//원래 있던 기본적인 내용들
#include "draw.h"	//primitive 그리는 것을 불러놓았다.

//openGL 함수가 헷갈리면
//www.opengl.org >> Documentation >> OpenGL 2.1

int w = 512;
int h = 512;

vector2D points[100];
int count;

bool moveOn = true;

void idle() {
	for (int i = 0; i < count; i++)
	{
		//2. 마우스 (중간버튼) 누르면 애니메이션 on/off
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
//1. 키보드 입력에 따라서 색상이 바뀜
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
		//윈도우 >> OpenGL 좌표 변환
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
	//너무 빨리 진행되어서 시간을 주었음
	Sleep(100);
	glutSwapBuffers();
}


int main(int argc, char** argv)
{
	//처음 glutInit으로 변수들을 받아와 초기화한다.
	glutInit(&argc, argv);
	//디스플레이 모드를 GLUT_DOUBLE, RGB 알파로 한다.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//윈도우 사이즈를 정해준다.
	glutInitWindowSize(w, h);
	glutCreateWindow("Simple interactive application");
	glColor3f(1.0, 0.4, 0.4);

	count = 0;

	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);

	glutMouseFunc(mouse);
	glutDisplayFunc(display);

	//얘가 계속 반복된다.
	glutMainLoop();
	return 0;
}
