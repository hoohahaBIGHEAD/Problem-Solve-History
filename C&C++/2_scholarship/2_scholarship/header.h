#pragma once
#include <iostream>
using namespace std;
#include <string>
#include <sstream>
#include "Student.h"
#include "UndergraduateStudent.h"
#include "GraduateStudent.h"


#define STUDENTNUMBER 4	//�л� �� ����

//��------------------�Լ� �����------------------��
void menu();	// �޴� ��� �Լ�
//��------------------�Լ� �����------------------��



//��------------------Ŭ���� �����------------------��



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