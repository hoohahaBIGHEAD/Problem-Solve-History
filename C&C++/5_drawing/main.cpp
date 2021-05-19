#include "cg.h"	//원래 있던 기본적인 내용들
#include "draw.h"	//primitive 그리는 것을 불러놓았다.

//openGL 함수가 헷갈리면
//www.opengl.org >> Documentation >> OpenGL 2.1

void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	

	/*
	glColor3f(1.0, 0.0, 0.0);	//red
	line(vector2D(0.2, -0.5), vector2D(0.2, 0.5));	//선 그리기.	좌표들은 창 비율을 기준으로 -1~+1이다.-

	glColor3f(1.0, 1.0, 0.0);	//yellow
	rect(vector2D(-0.5, 0.4), vector2D(0.4, -0.3));	//사각형 그리기

	glColor3f(1.0, 0.0, 1.0);	//magenta
	circle(vector2D(0.0, 0.0), 0.2);	//원 그리기
	*/

	/*
	//회색 사각형으로 전체 칠하기
	glColor3f(0.4, 0.4, 0.4);
	rect(vector2D(-1.0, 1.0), vector2D(1.0, -1.0));

	//흰색으로 속 빈 사각형 그리기
	//폴리곤을 그릴 때 외곽점만 그려라
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//이것은 속까지 채워라
	glColor3f(1.0, 1.0, 1.0);
	rect(vector2D(-0.7, 0.7), vector2D(0.2, -0.2));

	//검정색으로 대각선 그리기
	glColor3f(0.0, 0.0, 0.0);
	//라인의 두께를 바꿀 수 있다.
	glLineWidth(20.0);
	line(vector2D(-1.0, 1.0), vector2D(1.0, -1.0));
	*/
	
	/*  circular face */
	/*
	glColor3f(0.7, 0.7, 0.7);
	rect(vector2D(-1.0, 1.0), vector2D(1.0, -1.0));

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(1.0, 1.0, 1.0);
	rect(vector2D(-0.1, 0.1), vector2D(0.1, -0.6));
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(3.0);
	glColor3f(0.0, 0.0, 0.0);
	rect(vector2D(-0.1, 0.1), vector2D(0.1, -0.6));
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(1.0, 1.0, 1.0);
	circle(vector2D(0.0, 0.4), 0.35);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(3.0);
	glColor3f(0.0, 0.0, 0.0);
	circle(vector2D(0.0, 0.4), 0.35);
	
	ellipse(vector2D(-0.2, 0.4), 0.1, 0.2);
	ellipse(vector2D(0.2, 0.4), 0.1, 0.2);
	
	line(vector2D(-0.1, -0.6), vector2D(-0.2, -0.7));
	line(vector2D(0.1, -0.6), vector2D(0.2, -0.7));
	*/
	

	/* red transparency */
	/*
	//디폴트 : 알파값 안 쓰는 것
	//블렌딩을 enable하라
	glEnable(GL_BLEND);
	//소스의 알파값만큼, 나머지는 1-알파만큼의 비율로 섞어라
	//블렌딩 가장 기본 모드이다.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(0, 0, 0);
	rect(vector2D(0.0, 1.0), vector2D(1.0, -1.0));
	glColor3f(0, 0, 1.0);
	rect(vector2D(-1.0, 1.0), vector2D(0.0, -1.0));

    glColor4f(1.0, 0, 0.0, 1.0);	//마지막은 얼마나 투명한지를 적는다.
	rect(vector2D(-1.0, 1.0), vector2D(1.0, 0.6));
	glColor4f(1.0, 0, 0.0, 0.8);
	rect(vector2D(-1.0, 0.5), vector2D(1.0, 0.1));
	glColor4f(1.0, 0, 0.0, 0.5);
	rect(vector2D(-1.0, 0.0), vector2D(1.0, -0.4));
	glColor4f(1.0, 0, 0.0, 0.2);
	rect(vector2D(-1.0, -0.5), vector2D(1.0, -0.9));
	*/
	
	/*  y = x^2  */
	/*
float x, y; x = -1.0; y = -1.0;
	glLineWidth(4.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINES);	//선으로 그려라
	for (float t = -1.0; t <= 1.0; t = t+0.05)
	{
		glVertex2f(x, y);
		x = t; 
		y = - t * t;
		glVertex2f(x, y);
	}
	glEnd();
	*/

	/* 점진적인 원 드로잉 */
	/*
	//원을 그리는데 반지름을 점점 증가시키면서 찍는다.
	float x, y; x = 0.0; y = 0.0;
	//glBegin(GL_LINES);	//선으로 그려라
	glBegin(GL_POINTS);	//점으로 찍어라
	glPointSize(10); glColor3f(1.0, 0.0, 1.0);
	//반지름과 각도 g 둘 다 증가
	for (float r = 0.0, g = 0.0; r<= 1.3; r += 0.00001, g += 0.001)
	{
		x = r * cos(g);
		y = r * sin(g);
		glVertex2f(x, y);
	}
	glEnd();
	*/

	/*
	// Sin Cos drawing
	float x, y; x = 0.0; y = 0.0;
	glBegin(GL_POINTS);
	glPointSize(10); 
	//x는 계속 업데이트
	for (x=-1.0 ; x <= 1.0; x += 0.001)
	{
		glColor3f(1.0, 0.0, 1.0);
		y = 0.5*cos(2.0*M_PI*x);	//비율이 -1~1이니 M_PI를 곱한다.
		glVertex2f(x, y);
		glColor3f(1.0, 1.0, 0.0);
		y = 0.5 * sin(2.0 * M_PI * x);
		glVertex2f(x, y);
	}
	glEnd();
	*/

	///////////////////////////////////////////////////
	//회색 사각형으로 전체 칠하기
glColor3f(0.95, 0.95, 0.95);
rect(vector2D(-1.0, 1.0), vector2D(1.0, -1.0));

glColor3f(1.0, 1.0, 0.0);	//yellow
circle(vector2D(0.0, 0.0), 0.8);	//원 그리기

glColor3f(1.0, 0.75, 0.0);	//yellow
circle(vector2D(0.0, -0.4), 0.4);	//원 그리기

glColor3f(1.0, 0.0, 0.0);	//yellow
circle(vector2D(0.0, -0.5), 0.3);	//원 그리기


	///////////////////////////////////////////////////


	//맨 마지막에 이를 해준다.
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	//처음 glutInit으로 변수들을 받아와 초기화한다.
	glutInit(&argc, argv);
	//디스플레이 모드를 GLUT_DOUBLE, RGB 알파로 한다.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//윈도우 사이즈를 정해준다.
	glutInitWindowSize(512, 512);
	glutCreateWindow("simple");
	glutDisplayFunc(mydisplay);

	//얘가 계속 반복된다.
	glutMainLoop();
}
