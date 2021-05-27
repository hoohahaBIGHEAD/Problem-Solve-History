#pragma once
#include <iostream>
using namespace std;
#include <string>
#include <sstream>

#define STUDENTNUMBER 4	//학생 수 정의

//↓------------------함수 선언부------------------↓
void menu();	// 메뉴 출력 함수
//↑------------------함수 선언부------------------↑



//↓------------------클래스 선언부------------------↓
/////////////////////////////////////////////////////////////////////////////
//
//  Student
//
/////////////////////////////////////////////////////////////////////////////

/*protected, virtual*/
// Student 정의
class Student {
protected:
	//입력이 필요한 변수
	string name;	//이름
	int majorCredit;	//전공학점
	int minorCredit;	//교양학점
	float majorGPA;	//전공평점
	float minorGPA;	//교양평점
	
	int tuition;	//등록비



public:
	//지원 여부
	bool apply = false;
	//계산되는 변수
	float totalGPA;	//전체평점


	//virtual 함수 정의
// 학생 정보를 string으로 리턴해주는 함수
	virtual string getStudentInfo() { return ""; }
	// 평균 평점을 float로 리턴해주는 함수
	virtual float getGPA() { return 0; }
	// 등록비를 int로 리턴해주는 함수
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
	string circle;	//동아리

public:
	virtual string getStudentInfo();
	virtual float getGPA();
	virtual int getTuition();

	// 생성자. 변수를 6개 받는다.
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
	string lab;	//연구실
	string degreeProgram;	//석사박사 과정

public:
	virtual string getStudentInfo();
	virtual float getGPA();
	virtual int getTuition();

	// 생성자. 변수를 7개 받는다.
	GraduateStudent(string name, int majorCredit, int minorCredit, float majorGPA, float minorGPA, string lab, string degreeProgram);
};

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