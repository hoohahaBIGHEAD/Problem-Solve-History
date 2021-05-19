#include "cg.h"	//���� �ִ� �⺻���� �����
#include "draw.h"	//primitive �׸��� ���� �ҷ����Ҵ�.

//openGL �Լ��� �򰥸���
//www.opengl.org >> Documentation >> OpenGL 2.1

void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	

	/*
	glColor3f(1.0, 0.0, 0.0);	//red
	line(vector2D(0.2, -0.5), vector2D(0.2, 0.5));	//�� �׸���.	��ǥ���� â ������ �������� -1~+1�̴�.-

	glColor3f(1.0, 1.0, 0.0);	//yellow
	rect(vector2D(-0.5, 0.4), vector2D(0.4, -0.3));	//�簢�� �׸���

	glColor3f(1.0, 0.0, 1.0);	//magenta
	circle(vector2D(0.0, 0.0), 0.2);	//�� �׸���
	*/

	/*
	//ȸ�� �簢������ ��ü ĥ�ϱ�
	glColor3f(0.4, 0.4, 0.4);
	rect(vector2D(-1.0, 1.0), vector2D(1.0, -1.0));

	//������� �� �� �簢�� �׸���
	//�������� �׸� �� �ܰ����� �׷���
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//�̰��� �ӱ��� ä����
	glColor3f(1.0, 1.0, 1.0);
	rect(vector2D(-0.7, 0.7), vector2D(0.2, -0.2));

	//���������� �밢�� �׸���
	glColor3f(0.0, 0.0, 0.0);
	//������ �β��� �ٲ� �� �ִ�.
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
	//����Ʈ : ���İ� �� ���� ��
	//������ enable�϶�
	glEnable(GL_BLEND);
	//�ҽ��� ���İ���ŭ, �������� 1-���ĸ�ŭ�� ������ �����
	//���� ���� �⺻ ����̴�.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(0, 0, 0);
	rect(vector2D(0.0, 1.0), vector2D(1.0, -1.0));
	glColor3f(0, 0, 1.0);
	rect(vector2D(-1.0, 1.0), vector2D(0.0, -1.0));

    glColor4f(1.0, 0, 0.0, 1.0);	//�������� �󸶳� ���������� ���´�.
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
	glBegin(GL_LINES);	//������ �׷���
	for (float t = -1.0; t <= 1.0; t = t+0.05)
	{
		glVertex2f(x, y);
		x = t; 
		y = - t * t;
		glVertex2f(x, y);
	}
	glEnd();
	*/

	/* �������� �� ����� */
	/*
	//���� �׸��µ� �������� ���� ������Ű�鼭 ��´�.
	float x, y; x = 0.0; y = 0.0;
	//glBegin(GL_LINES);	//������ �׷���
	glBegin(GL_POINTS);	//������ ����
	glPointSize(10); glColor3f(1.0, 0.0, 1.0);
	//�������� ���� g �� �� ����
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
	//x�� ��� ������Ʈ
	for (x=-1.0 ; x <= 1.0; x += 0.001)
	{
		glColor3f(1.0, 0.0, 1.0);
		y = 0.5*cos(2.0*M_PI*x);	//������ -1~1�̴� M_PI�� ���Ѵ�.
		glVertex2f(x, y);
		glColor3f(1.0, 1.0, 0.0);
		y = 0.5 * sin(2.0 * M_PI * x);
		glVertex2f(x, y);
	}
	glEnd();
	*/

	///////////////////////////////////////////////////
	//ȸ�� �簢������ ��ü ĥ�ϱ�
glColor3f(0.95, 0.95, 0.95);
rect(vector2D(-1.0, 1.0), vector2D(1.0, -1.0));

glColor3f(1.0, 1.0, 0.0);	//yellow
circle(vector2D(0.0, 0.0), 0.8);	//�� �׸���

glColor3f(1.0, 0.75, 0.0);	//yellow
circle(vector2D(0.0, -0.4), 0.4);	//�� �׸���

glColor3f(1.0, 0.0, 0.0);	//yellow
circle(vector2D(0.0, -0.5), 0.3);	//�� �׸���


	///////////////////////////////////////////////////


	//�� �������� �̸� ���ش�.
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	//ó�� glutInit���� �������� �޾ƿ� �ʱ�ȭ�Ѵ�.
	glutInit(&argc, argv);
	//���÷��� ��带 GLUT_DOUBLE, RGB ���ķ� �Ѵ�.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//������ ����� �����ش�.
	glutInitWindowSize(512, 512);
	glutCreateWindow("simple");
	glutDisplayFunc(mydisplay);

	//�갡 ��� �ݺ��ȴ�.
	glutMainLoop();
}
