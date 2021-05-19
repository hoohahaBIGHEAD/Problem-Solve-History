#pragma once
#include "vec.h"

void rect(vector2D a, vector2D b); // a: 왼쪽 위   b: 오른쪽 아래
void circle(vector2D center, float radius); // center : 중심점, radius: 반지름
void ellipse(vector2D center, float width, float height);  // center: 중심점, width: 가로 반지름, height: 세로 반지름
void triangle(vector2D a, vector2D b, vector2D c); // a, b, c 꼭지점
void line(vector2D a, vector2D b); // a - b 까지 라인