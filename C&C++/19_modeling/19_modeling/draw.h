#pragma once
#include "vec.h"

void circle(vector2D center, float radius); // center : �߽���, radius: ������
void ellipse(vector2D center, float width, float height);  // center: �߽���, width: ���� ������, height: ���� ������
void triangle(vector2D a, vector2D b, vector2D c); // a, b, c ������
void line(vector2D a, vector2D b); // a - b ���� ����
void rect(vector2D a, vector2D b); // a: ���� ��   b: ������ �Ʒ�