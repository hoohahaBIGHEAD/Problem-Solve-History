#pragma once
#include <iostream>
using namespace std;
#include <string>
#include <sstream>
#include "Student.h"
#include "UndergraduateStudent.h"
#include "GraduateStudent.h"


#define STUDENTNUMBER 4	//학생 수 정의

//↓------------------함수 선언부------------------↓
void menu();	// 메뉴 출력 함수
//↑------------------함수 선언부------------------↑



//↓------------------클래스 선언부------------------↓



/////////////////////////////////////////////////////////////////////////////
//
//  ScholarshipManagement
//
/////////////////////////////////////////////////////////////////////////////

class ScholarshipManagement {
public:
	Student** studentList;	//Student 배열을 받는 포인터
	int num_of_students;	//학생의 수

	// 생성자
	ScholarshipManagement(Student** student, int num_of_students);

	//프로그램을 위한 진행
	void run();
};
//↑------------------클래스 선언부------------------↑