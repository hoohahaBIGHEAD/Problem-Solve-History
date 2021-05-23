#define _USE_MATH_DEFINES	//pi�� ����ϱ� ���� <cmath>�� ��� �ϴµ� �̸� �����ؾ� �Ѵ�.
#include <cmath>	//M_PI�� pi ��� ����
#include <iostream>
using namespace std;

//public: :: �ܺο��� ������ �� �ִ� ���� �� �޼ҵ�
//this :: �ڱ� �ڽ��� ��Ÿ���� Ű����� -> �� ��� ������ �����Ѵ�.
//�Լ��� ������ �� {Ŭ�����̸�}::{Ŭ�����Լ�}(){} ���·� �����ϴ� ������ �ҽ��ڵ带 �и��Ͽ� ������ �� �ش� Ŭ������ �Լ����� �˷��ֱ� ���� ���� ���̴�.


//���� Ŭ���� ����
class Shape
{
public:
	//���� �� �ѷ� ����(��� ����) ����
	float Area;
	float Girth;

	//��� �� �Լ��� �������ϱ� ���� virtual�� �Բ� �Լ� ����(����� �ٸ���. ������ �Լ��� ��� ���¸� ǥ���ϰ� ���Ǵ� �Լ��� ���θ� �����Ѵ�.)
	virtual float GetArea() { return 0; }
	virtual float GetGirth() { return 0; }
};

//���� Ŭ������ ����ϴ� �簢�� Ŭ���� ����
class Rectangle : public Shape
{
public:
	//������ ���� ����
	Rectangle(float width, float length);
	//�Լ� ���� ����
	virtual float GetArea();
	virtual float GetGirth();
};

//������ ���� :: �� ��ü�� ������ 2�� ������ �����Ѵ�.
Rectangle::Rectangle(float width, float length)
{
	//���� :: w * l
	this->Area = width * length;
	//�ѷ� :: 2 * ( w + l )
	this->Girth = 2 * (width + length);
}

//�Լ� ����
float Rectangle::GetArea() {
	//�ش� ��ü�� Area�� �����Ѵ�.
	return this->Area;
}

//�Լ� ����
float Rectangle::GetGirth() {
	//�ش� ��ü�� Girth�� �����Ѵ�.
	return this->Girth;
}

class Circle : public Shape
{
public:
	//������ ���� ����
	Circle(float radius);
	//�Լ� ���� ����
	virtual float GetArea();
	virtual float GetGirth();
};

//������ ���� :: �� ��ü�� ������ 1�� ������ �����Ѵ�.
Circle::Circle(float radius)
{
	//���� :: pi * r * r
	this->Area = M_PI * radius * radius;
	//�ѷ� :: 2 * pi * r
	this->Girth = 2 * M_PI * radius;
}

float Circle::GetArea() {
	//�ش� ��ü�� Area�� �����Ѵ�.
	return this->Area;
}

float Circle::GetGirth() {
	//�ش� ��ü�� Girth�� �����Ѵ�.
	return this->Girth;
}

int main() {

	//�簢�� �ν��Ͻ� �����ϸ鼭 ���μ��� �Ҵ�
	Rectangle rec(3, 4);
	cout << "Area: " << rec.GetArea() << endl;
	cout << "Girth: " << rec.GetGirth() << endl;
	
	//�� �ν��Ͻ� �����ϸ鼭 ������ �Ҵ�
	Circle cir(5);
	cout << "Area: " << cir.GetArea() << endl;
	cout << "Girth: " << cir.GetGirth() << endl;

	return 0;
}

