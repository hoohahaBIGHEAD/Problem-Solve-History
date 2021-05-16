#include <iostream>
using namespace std;
#include <string>


//------------------함수 선언부------------------
void menu();	// 메뉴 출력 함수
//------------------함수 선언부------------------

//------------------클래스 선언부------------------

// Student 정의
class Student {
public:
	//생성자로 입력
	string name;
	float majorCredit;
	float minorCredit;
	float majorGPA;
	float minorGPA;

	//연산으로 생성
	float totalGPA;
	float tuition;

	virtual string getStudentInfo() {
	}

	virtual float getGPA() {
	}

	virtual float getTuition() {
	}

	
};

class UndergraduateStudent : public Student{
private:
	string circle;
	
public:
	virtual string getStudentInfo() {
		return this->name + " " +
			to_string(this->majorCredit) + " " +
			to_string(this->minorCredit) + " " +
			to_string(this->majorGPA) + " " +
			to_string(this->minorGPA) + " " +
			this->circle + " " +
			to_string(this->totalGPA) + " " +
			to_string(this->tuition) + "만원\n";
	}

	virtual float getGPA() {
		return ((this->majorCredit * this->majorGPA) + (this->minorCredit * this->minorGPA)) / (this->majorCredit + this->minorCredit);
	}

	virtual float getTuition(){
		return ((this->majorCredit * 10) + (this->minorCredit) * 6);
	}

	UndergraduateStudent(string name, float majorCredit, float minorCredit, float majorGPA, float minorGPA, string circle) {
		this->name = name;
		this->majorCredit = majorCredit;
		this->minorCredit = minorCredit;
		this->majorGPA = majorGPA;
		this->minorGPA = minorGPA;
		this->circle = circle;

		//연산으로 생성
		this->totalGPA = this->getGPA();
		this->tuition = this->getTuition();
	}
};

class GraduateStudent : public Student {
private:
	string lab;
	string degreeProgram;

public:
	virtual string getStudentInfo() {
		return this->name + " " +
			to_string(this->majorCredit) + " " +
			to_string(this->minorCredit) + " " +
			to_string(this->majorGPA) + " " +
			to_string(this->minorGPA) + " " +
			this->lab + " " +
			this->degreeProgram + " " +
			to_string(this->totalGPA) + " " +
			to_string(this->tuition) + "만원\n";
	}

	virtual float getGPA() {
		return ((this->majorCredit * this->majorGPA) * 1.1 + (this->minorCredit * this->minorGPA) * 0.9) / (this->majorCredit + this->minorCredit);
	}

	virtual float getTuition() {
		return ((this->majorCredit * 12) + (this->minorCredit) * 4);
	}

	GraduateStudent(string name, float majorCredit, float minorCredit, float majorGPA, float minorGPA, string lab, string degreeProgram) {
		this->name = name;
		this->majorCredit = majorCredit;
		this->minorCredit = minorCredit;
		this->majorGPA = majorGPA;
		this->minorGPA = minorGPA;
		
		this->lab = lab;
		this->degreeProgram = degreeProgram;

		//연산으로 생성
		this->totalGPA = this->getGPA();
		this->tuition = this->getTuition();
	}
};


class ScholarshipManagement {
	Student** studentList;
	int num_of_students;

	void run() {
		int menuIndex;	// 메뉴 선택을 위한 인덱스
		cin >> menuIndex;

		// 입력에 맞게 함수를 부른다.
		if (menuIndex == 1) {
			for (int i = 0; i < this->num_of_students; i++)
			{
				//this->studentList[i]()
			}

			/*
			else if (menuIndex == 2) student_change();
			else if (menuIndex == 3) student_search();
			else if (menuIndex == 4) student_delete();
			else if (menuIndex == 5) student_lookup(student_array, student_count);
			else if (menuIndex == 0) save_exit();
			else
			{
				cout << "잘못된 값을 입력했습니다.\n\n";
				// 잘못된 값이 입력될 경우 메뉴 함수를 다시 호출한다.
				menu();
			}
			*/
		}
	}

	ScholarshipManagement(Student** student, int num_of_students) {
		this->studentList = student;
		this->num_of_students = num_of_students;
	}
};

//------------------클래스 선언부------------------

int main() {
	Student** studentList = new Student*[6];
	
	menu();	// 메뉴 출력 함수


	
	
	



	return 0;
}
//------------------main 실행------------------


// 메뉴 출력 함수
void menu() {

	cout << "\n메뉴\n";
	cout << "1. 장학금 지원\n";
	cout << "2. 장학금 지원자 정보\n";
	cout << "3. 장학생 선정\n";
	cout << "4. 종료하기\n";
	cout << "* 연산을 입력하세요: ";

};