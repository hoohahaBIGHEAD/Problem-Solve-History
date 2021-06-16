#include "cg.h"
#include "vec.h"

void rect(vector2D a, vector2D b)
/*
*  a : 왼쪽 위 코너
*  b : 오른쪽 아래 코너
*/
{
	glBegin(GL_POLYGON);
	glVertex2f(a.x, a.y);
	glVertex2f(b.x, a.y);
	glVertex2f(b.x, b.y);
	glVertex2f(a.x, b.y);
	glEnd();
}

void triangle(vector2D a, vector2D b)
{
	glBegin(GL_TRIANGLES);
	glVertex2f(a[0], b[1]);
	glVertex2f(b[0], b[1]);
	glVertex2f((a[0]+b[0])/2, a[1]);
	glEnd();
}

void circle(vector2D center, float radius)
{
	float x, y;

	glBegin(GL_POLYGON);
	// 중심을 기준으로 점을 생성해 점끼리 이어 원을 그린다.
	for (float f = 0.0; f < 2*M_PI; f += M_PI/36.0)
	{
		x = center.x + radius * cos(f);
		y = center.y + radius * sin(f);
		glVertex2f(x, y);
	}
	glEnd();
}

void ellipse(vector2D a, vector2D b)
{
	float x, y;

	glBegin(GL_POLYGON);
	//원과 비슷하되 점을 가로세로 비율에 따라 정해준다.
	for (float f = 0.0; f < 2 * M_PI; f += M_PI / 36.0)
	{
		x = (a.x+b.x)/2 + ((b.x - a.x)/2) * cos(f);
		y = (a.y + b.y) / 2 + ((b.y - a.y)/2) * sin(f);
		glVertex2f(x, y);
	}
	glEnd();
}

void ellipse(vector2D center, float width, float height)
{
	float x, y;

	glBegin(GL_POLYGON);
	//원과 비슷하되 점을 가로세로 비율에 따라 정해준다.
	for (float f = 0.0; f < 2 * M_PI; f += M_PI / 36.0)
	{
		x = center.x + width * cos(f);
		y = center.y + height * sin(f);
		glVertex2f(x, y);
	}
	glEnd();
}

void triangle(vector2D a, vector2D b, vector2D c)
{
	glBegin(GL_TRIANGLES);
	glVertex2f(a[0], a[1]);
	glVertex2f(b[0], b[1]);
	glVertex2f(c[0], c[1]);
	glEnd();
}

void line(vector2D a, vector2D b)
{
	glBegin(GL_LINES);
	glVertex2f(a[0], a[1]);
	glVertex2f(b[0], b[1]);
	glEnd();
}