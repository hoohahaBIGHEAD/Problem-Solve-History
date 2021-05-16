#include <iostream>
using namespace std;
#include <string>
#include <sstream>

#define STUDENTNUMBER 2

//------------------함수 선언부------------------
void menu();	// 메뉴 출력 함수
//------------------함수 선언부------------------

//------------------클래스 선언부------------------

// Student 정의
class Student {
public:
	//생성자로 입력
	string name;
	int majorCredit;
	int minorCredit;
	float majorGPA;
	float minorGPA;

	//연산으로 생성
	float totalGPA;
	int tuition;

	bool apply = false;

	virtual string getStudentInfo() {
		return "";
	}

	virtual float getGPA() {
		return 0;
	}

	virtual int getTuition() {
		return 0;
	}
};

class UndergraduateStudent : public Student{
private:
	string circle;
	
public:
	virtual string getStudentInfo() {
		return " - " + 
			this->name + " " +
			to_string(this->majorCredit) + " " +
			to_string(this->minorCredit) + " " +
			to_string(this->majorGPA).substr(0, 4) + " " +
			to_string(this->minorGPA).substr(0, 4) + " " +
			this->circle + " " +
			to_string(this->totalGPA).substr(0, 4) + " " +
			to_string(this->tuition) + "만원\n";
	}

	virtual float getGPA() {
		return ((this->majorCredit * this->majorGPA) + (this->minorCredit * this->minorGPA)) / (this->majorCredit + this->minorCredit);
	}

	virtual int getTuition(){
		return ((this->majorCredit * 10) + (this->minorCredit) * 6);
	}

	UndergraduateStudent(string name, int majorCredit, int minorCredit, float majorGPA, float minorGPA, string circle) {
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
		return " - " +
			this->name + " " +
			to_string(this->majorCredit) + " " +
			to_string(this->minorCredit) + " " +
			to_string(this->majorGPA).substr(0,4) + " " +
			to_string(this->minorGPA).substr(0, 4) + " " +
			this->lab + " " +
			this->degreeProgram + " " +
			to_string(this->totalGPA).substr(0, 4) + " " +
			to_string(this->tuition) + "만원\n";
	}

	virtual float getGPA() {
		return ((this->majorCredit * this->majorGPA) * 1.1 + (this->minorCredit * this->minorGPA) * 0.9) / (this->majorCredit + this->minorCredit);
	}

	virtual int getTuition() {
		return ((this->majorCredit * 12) + (this->minorCredit) * 4);
	}

	GraduateStudent(string name, int majorCredit, int minorCredit, float majorGPA, float minorGPA, string lab, string degreeProgram) {
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
public:
	Student** studentList;
	int num_of_students;

	

	ScholarshipManagement(Student** student, int num_of_students) {
		this->studentList = student;
		this->num_of_students = num_of_students;
	}

	void run() {
		while (true)
		{
			int menuIndex;	// 메뉴 선택을 위한 인덱스
			cin >> menuIndex;
			cin.clear();	//에러비트 막고
			cin.ignore(INT_MAX, '\n');	//\n 비우기
			
			string temp;
			string stringBuffer[10];
			int index;
			// 입력에 맞게 함수를 부른다.


			if (menuIndex == 1) {
				for (int i = 0; i <= this->num_of_students; i++)
				{
					if (i == this->num_of_students) {
						cout << "* 지원 대상 학생들의 수와 각각의 번호를 연속해서 입력하시오: ";
						getline(cin, temp);//문자열 공백도 입력
						istringstream stringStream(temp);
						index = 0;
						while (getline(stringStream, stringBuffer[index], ' '))
						{
							index++;
						}
						for (int j = 1; j <= stoi(stringBuffer[0]); j++)
						{
							studentList[stoi(stringBuffer[j])-1]->apply = true;
						}
						
					}
					else
					{
						cout << " " << i + 1 << ")";

						getline(cin, temp);//문자열 공백도 입력
						istringstream stringStream(temp);
						index = 0;
						while (getline(stringStream, stringBuffer[index], ' '))
						{
							index++;
						}

						if (index == 6) {
							studentList[i] = new UndergraduateStudent(
								stringBuffer[0],
								stoi(stringBuffer[1]),
								stoi(stringBuffer[2]),
								stof(stringBuffer[3]),
								stof(stringBuffer[4]),
								stringBuffer[5]);
						}
						else if (index == 7) {
							studentList[i] = new GraduateStudent(
								stringBuffer[0],
								stoi(stringBuffer[1]),
								stoi(stringBuffer[2]),
								stof(stringBuffer[3]),
								stof(stringBuffer[4]),
								stringBuffer[5],
								stringBuffer[6]);
						}
					}
				}

			}
			else if (menuIndex == 2)
			{
				for (int i = 0; i < this->num_of_students; i++) {
					if(studentList[i]->apply)
					cout << studentList[i]->getStudentInfo();
				}

			}
			else if (menuIndex == 3)
			{

			}
			else if (menuIndex == 4)
			{
				cout << " - 종료합니다.";
				break;
			}
			menu();

		}
		}
		
};

//------------------클래스 선언부------------------

int main() {
	Student** studentList = new Student*[STUDENTNUMBER];
	
	ScholarshipManagement scholarshipManagement(studentList, STUDENTNUMBER);
	menu();	// 메뉴 출력 함수
	scholarshipManagement.run();

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