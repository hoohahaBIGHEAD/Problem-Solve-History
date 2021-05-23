#define _USE_MATH_DEFINES	//pi를 사용하기 위해 <cmath>를 써야 하는데 이를 선언해야 한다.
#include <cmath>	//M_PI로 pi 사용 가능
#include <iostream>
using namespace std;

//public: :: 외부에서 접근할 수 있는 변수 및 메소드
//this :: 자기 자신을 나타내는 키워드고 -> 로 멤버 변수에 접근한다.
//함수를 정의할 때 {클래스이름}::{클래스함수}(){} 형태로 선언하는 이유는 소스코드를 분리하여 관리할 때 해당 클래스의 함수임을 알려주기 위해 붙인 것이다.


//도형 클래스 생성
class Shape
{
public:
	//넓이 및 둘레 변수(멤버 변수) 생성
	float Area;
	float Girth;

	//상속 후 함수를 재정의하기 위해 virtual과 함께 함수 정의(선언과 다르다. 선언은 함수의 사용 형태를 표현하고 정의는 함수의 내부를 정의한다.)
	virtual float GetArea() { return 0; }
	virtual float GetGirth() { return 0; }
};

//도형 클래스를 상속하는 사각형 클래스 생성
class Rectangle : public Shape
{
public:
	//생성자 형태 선언
	Rectangle(float width, float length);
	//함수 형태 선언
	virtual float GetArea();
	virtual float GetGirth();
};

//생성자 정의 :: 이 객체는 변수를 2개 받으며 생성한다.
Rectangle::Rectangle(float width, float length)
{
	//넓이 :: w * l
	this->Area = width * length;
	//둘레 :: 2 * ( w + l )
	this->Girth = 2 * (width + length);
}

//함수 정의
float Rectangle::GetArea() {
	//해당 객체의 Area를 리턴한다.
	return this->Area;
}

//함수 정의
float Rectangle::GetGirth() {
	//해당 객체의 Girth를 리턴한다.
	return this->Girth;
}

class Circle : public Shape
{
public:
	//생성자 형태 선언
	Circle(float radius);
	//함수 형태 선언
	virtual float GetArea();
	virtual float GetGirth();
};

//생성자 정의 :: 이 객체는 변수를 1개 받으며 생성한다.
Circle::Circle(float radius)
{
	//넓이 :: pi * r * r
	this->Area = M_PI * radius * radius;
	//둘레 :: 2 * pi * r
	this->Girth = 2 * M_PI * radius;
}

float Circle::GetArea() {
	//해당 객체의 Area를 리턴한다.
	return this->Area;
}

float Circle::GetGirth() {
	//해당 객체의 Girth를 리턴한다.
	return this->Girth;
}

int main() {

	//사각형 인스턴스 생성하면서 가로세로 할당
	Rectangle rec(3, 4);
	cout << "Area: " << rec.GetArea() << endl;
	cout << "Girth: " << rec.GetGirth() << endl;
	
	//원 인스턴스 생성하면서 반지름 할당
	Circle cir(5);
	cout << "Area: " << cir.GetArea() << endl;
	cout << "Girth: " << cir.GetGirth() << endl;

	return 0;
}

