#pragma once
#include <iostream>
using namespace std;
#include <string>
#include <sstream>

#define STUDENTNUMBER 4	//�л� �� ����

//��------------------�Լ� �����------------------��
void menu();	// �޴� ��� �Լ�
//��------------------�Լ� �����------------------��



//��------------------Ŭ���� �����------------------��
/////////////////////////////////////////////////////////////////////////////
//
//  Student
//
/////////////////////////////////////////////////////////////////////////////

/*protected, virtual*/
// Student ����
class Student {
protected:
	//�Է��� �ʿ��� ����
	string name;	//�̸�
	int majorCredit;	//��������
	int minorCredit;	//��������
	float majorGPA;	//��������
	float minorGPA;	//��������
	
	int tuition;	//��Ϻ�



public:
	//���� ����
	bool apply = false;
	//���Ǵ� ����
	float totalGPA;	//��ü����


	//virtual �Լ� ����
// �л� ������ string���� �������ִ� �Լ�
	virtual string getStudentInfo() { return ""; }
	// ��� ������ float�� �������ִ� �Լ�
	virtual float getGPA() { return 0; }
	// ��Ϻ� int�� �������ִ� �Լ�
	virtual int getTuition() { return 0; }

};

/*class inheritance*/
/////////////////////////////////////////////////////////////////////////////
//
//  UndergraduateStudent : public Student
//
/////////////////////////////////////////////////////////////////////////////

class UndergraduateStudent : public Student {
private:
	string circle;	//���Ƹ�

public:
	virtual string getStudentInfo();
	virtual float getGPA();
	virtual int getTuition();

	// ������. ������ 6�� �޴´�.
	UndergraduateStudent(string name, int majorCredit, int minorCredit, float majorGPA, float minorGPA, string circle);
};

/*class inheritance*/
/////////////////////////////////////////////////////////////////////////////
//
//  GraduateStudent : public Student
//
/////////////////////////////////////////////////////////////////////////////

class GraduateStudent : public Student {
private:
	string lab;	//������
	string degreeProgram;	//����ڻ� ����

public:
	virtual string getStudentInfo();
	virtual float getGPA();
	virtual int getTuition();

	// ������. ������ 7�� �޴´�.
	GraduateStudent(string name, int majorCredit, int minorCredit, float majorGPA, float minorGPA, string lab, string degreeProgram);
};

/////////////////////////////////////////////////////////////////////////////
//
//  ScholarshipManagement
//
/////////////////////////////////////////////////////////////////////////////

class ScholarshipManagement {
public:
	Student** studentList;	//Student �迭�� �޴� ������
	int num_of_students;	//�л��� ��

	// ������
	ScholarshipManagement(Student** student, int num_of_students);

	//���α׷��� ���� ����
	void run();
};
//��------------------Ŭ���� �����------------------��