#pragma once

#define STUDENTNUMBER 6	//학생 수 정의

//↓------------------함수 선언부------------------↓
void menu();	// 메뉴 출력 함수
//↑------------------함수 선언부------------------↑


//↓------------------클래스 선언부------------------↓
/////////////////////////////////////////////////////////////////////////////
//
//  Student
//
/////////////////////////////////////////////////////////////////////////////


// Student 정의
class Student {
public:
	//입력이 필요한 변수
	string name;	//이름
	int majorCredit;	//전공학점
	int minorCredit;	//교양학점
	float majorGPA;	//전공평점
	float minorGPA;	//교양평점

	//계산되는 변수
	float totalGPA;	//전체평점
	int tuition;	//등록비

	//지원 여부
	bool apply = false;

	//virtual 함수 정의
	// 학생 정보를 string으로 리턴해주는 함수
	virtual string getStudentInfo() {
		return "";
	}

	// 평균 평점을 float로 리턴해주는 함수
	virtual float getGPA() {
		return 0;
	}

	// 등록비를 int로 리턴해주는 함수
	virtual int getTuition() {
		return 0;
	}
};

/////////////////////////////////////////////////////////////////////////////
//
//  UndergraduateStudent : public Student
//
/////////////////////////////////////////////////////////////////////////////

class UndergraduateStudent : public Student {
private:
	string circle;	//동아리

public:
	// to_string - 리턴을 위해 string으로 형변환
	// substr(0, 4) - float의 뒷자리를 잘라주는 함수
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

	virtual int getTuition() {
		return ((this->majorCredit * 10) + (this->minorCredit) * 6);
	}

	// 생성자. 변수를 6개 받는다.
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
	// to_string - 리턴을 위해 string으로 형변환
	// substr(0, 4) - float의 뒷자리를 잘라주는 함수
	virtual string getStudentInfo() {
		return " - " +
			this->name + " " +
			to_string(this->majorCredit) + " " +
			to_string(this->minorCredit) + " " +
			to_string(this->majorGPA).substr(0, 4) + " " +
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

	// 생성자. 변수를 7개 받는다.
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
	ScholarshipManagement(Student** student, int num_of_students) {
		this->studentList = student;
		this->num_of_students = num_of_students;
	}

	/*
	프로그램을 위한 진행
	*/
	void run() {
		while (true)
		{
			int menuIndex;	//메뉴 선택을 위한 인덱스
			cin >> menuIndex;
			cin.clear();	//에러비트 막고
			cin.ignore(INT_MAX, '\n');	//\n 비우기

			string temp;	//Student 생성을 위해 변수를 받아오는 임시 변수
			string token[10];	//temp로 받아온 문장을 ' '를 기준으로 분리해 저장하기 위한 토큰 배열
			int tokenIndex;	// Student 생성 시 변수로 
			
			/*
			menuIndex의 선택에 따라 함수를 진행시킨다.
			menuIndex == 1 - 1. 장학금 지원 : 지원하는 학생 수와 지원자의 번호를 연속으로 입력한다.
			menuIndex == 2 - 2. 장학금 지원자 정보 : 장학금 지원자의 정보를 출력한다.
			menuIndex == 3 - 3. 장학생 선정 : 학점이 높은 순으로 2명을 선정한다.
			menuIndex == 4 - 4. 종료하기 : 메시지 출력 후 프로그램을 종료한다.
			*/

			//menuIndex == 1 - 1. 장학금 지원 : 지원하는 학생 수와 지원자의 번호를 연속으로 입력한다.
			if (menuIndex == 1) {
				//학생수 + 1만큼 1줄씩 변수를 받아온다.
				for (int i = 0; i <= this->num_of_students; i++)
				{
					//num_of_students만큼 학생 정보를 입력 받는다.
					if(i != this->num_of_students){
						cout << " " << i + 1 << ")";

						getline(cin, temp);	//문자열 공백도 입력받아 temp에 저장하는 함수
						istringstream stringStream(temp);	//temp를 복사해 버퍼에서 stream으로 제공한다.
						tokenIndex = 0;	//token 배열에 저장해준다.

						//stringStream을 통해 제공 받은 버퍼를 ' '를 기준으로 나누어 token[tokenIndex]에 저장한다.
						//저장 후 tokenIndex를 1씩 증가시킨다.
						//최종적으로 token[]에는 temp를 ' '를 기준으로 나눠진 단어가 저장된다.
						while (getline(stringStream, token[tokenIndex], ' '))
							tokenIndex++;

						//토큰 수가 6개라면 == 받은 변수가 6개라면 == UndergraduateStudent라면
						if (tokenIndex == 6) {
							//studentList[i]에 UndergraduateStudent를 저장한다.
							studentList[i] = new UndergraduateStudent(
								token[0],
								stoi(token[1]),
								stoi(token[2]),
								stof(token[3]),
								stof(token[4]),
								token[5]);
						}
						//토큰 수가 7개라면 == 받은 변수가 7개라면 == GraduateStudent라면
						else if (tokenIndex == 7) {
							//studentList[i]에 GraduateStudent를 저장한다.
							studentList[i] = new GraduateStudent(
								token[0],
								stoi(token[1]),
								stoi(token[2]),
								stof(token[3]),
								stof(token[4]),
								token[5],
								token[6]);
						}
					}

					//학생을 전부 받아오면 지원 대상 학생들의 수와 각각의 번호를 연속해서 입력 받는다.
					else if (i == this->num_of_students) {
						cout << "* 지원 대상 학생들의 수와 각각의 번호를 연속해서 입력하시오: ";
						getline(cin, temp);	//문자열 공백도 입력받아 temp에 저장하는 함수
						istringstream stringStream(temp);	//temp를 복사해 버퍼에서 stream으로 제공한다.
						tokenIndex = 0;	//token 배열에 저장해준다.

						//stringStream을 통해 제공 받은 버퍼를 ' '를 기준으로 나누어 token[tokenIndex]에 저장한다.
						//저장 후 tokenIndex를 1씩 증가시킨다.
						//최종적으로 token[]에는 temp를 ' '를 기준으로 나눠진 단어가 저장된다.
						while (getline(stringStream, token[tokenIndex], ' '))
							tokenIndex++;

						//장학금 지원한 학생들의 apply 여부를 true로 바꾼다.
						for (int j = 1; j <= stoi(token[0]); j++)
						{
							studentList[stoi(token[j]) - 1]->apply = true;
						}
					}
				}
			}

			//menuIndex == 2 - 2. 장학금 지원자 정보 : 장학금 지원자의 정보를 출력한다.
			else if (menuIndex == 2)
			{
				//전체 학생들 중 장학금 지원한 학생들의 apply 여부를 보고 학생 정보를 출력한다.
				for (int i = 0; i < this->num_of_students; i++) {
					if (studentList[i]->apply)
						cout << studentList[i]->getStudentInfo();
				}
			}
			
			//menuIndex == 3 - 3. 장학생 선정 : 학점이 높은 순으로 2명을 선정한다.
			//전체 학생들의 totalGPA를 받아와 totalGPA[]에 저장 후 장학생들의 순위를 매긴다.
			//rank[]에 장학생들간의 매겨진 순위를 저장한다.
			else if (menuIndex == 3)
			{
				float totalGPA[STUDENTNUMBER];
				int rank[STUDENTNUMBER];

				//전체 학생들의 totalGPA를 받아와 totalGPA[]에 저장한다.
				for (int i = 0; i < STUDENTNUMBER; i++) {
					totalGPA[i] = studentList[i]->totalGPA;
					rank[i] = 1;	// 점수를 다른 사람과 비교하기 전에는 모두 1등일 가능성이 있으므로 석차배열을 1로 초기화한다. 
				}

				//장학생들의 순위를 매긴다.
				//i번째 학생보다 GPA가 높은 j번째 학생이 있고 j번째 학생이 장학금을 지원했다면 i번째 학생의 석차를 증가시킨다.
				//장학금에 지원한 학생들끼리 등수를 비교했기 때문에 rank[]에는 장학생들간의 매겨진 순위가 저장된다.
				for (int i = 0; i < STUDENTNUMBER; i++)
				{
					for (int j = 0; j < STUDENTNUMBER; j++)
						if (totalGPA[i] < totalGPA[j] &&	//i번째 학생보다 GPA가 높은 j번째 학생이 있고
							studentList[i]->apply && studentList[j]->apply)	//j번째 학생이 장학금을 지원했다면
							rank[i]++;	//i번째 학생의 석차를 증가시킨다.
				}

				//전체 학생들 중에서 장학금을 지원한 학생의 순위가 2등 안이라면 해당 학생의 정보를 출력시킨다.
				for (int i = 0; i < STUDENTNUMBER; i++)
				{
					if (rank[i] <= 2 && studentList[i]->apply)
						cout << studentList[i]->getStudentInfo();
				}
			}


			//menuIndex == 4 - 4. 종료하기 : 메시지 출력 후 프로그램을 종료한다.
			//break를 통해 while문을 빠져나온다.
			else if (menuIndex == 4)
			{
				cout << " - 종료합니다.";
				break;
			}

			//매 프로시저가 끝나면 메뉴를 보여준다.
			menu();
		}
	}
};
//↑------------------클래스 선언부------------------↑