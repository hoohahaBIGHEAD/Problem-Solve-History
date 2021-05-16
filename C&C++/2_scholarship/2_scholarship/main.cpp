#include <iostream>
using namespace std;
#include <string>
#include <sstream>

#define STUDENTNUMBER 2

//------------------�Լ� �����------------------
void menu();	// �޴� ��� �Լ�
//------------------�Լ� �����------------------

//------------------Ŭ���� �����------------------

// Student ����
class Student {
public:
	//�����ڷ� �Է�
	string name;
	int majorCredit;
	int minorCredit;
	float majorGPA;
	float minorGPA;

	//�������� ����
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
			to_string(this->tuition) + "����\n";
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

		//�������� ����
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
			to_string(this->tuition) + "����\n";
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

		//�������� ����
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
			int menuIndex;	// �޴� ������ ���� �ε���
			cin >> menuIndex;
			cin.clear();	//������Ʈ ����
			cin.ignore(INT_MAX, '\n');	//\n ����
			
			string temp;
			string stringBuffer[10];
			int index;
			// �Է¿� �°� �Լ��� �θ���.


			if (menuIndex == 1) {
				for (int i = 0; i <= this->num_of_students; i++)
				{
					if (i == this->num_of_students) {
						cout << "* ���� ��� �л����� ���� ������ ��ȣ�� �����ؼ� �Է��Ͻÿ�: ";
						getline(cin, temp);//���ڿ� ���鵵 �Է�
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

						getline(cin, temp);//���ڿ� ���鵵 �Է�
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
				cout << " - �����մϴ�.";
				break;
			}
			menu();

		}
		}
		
};

//------------------Ŭ���� �����------------------

int main() {
	Student** studentList = new Student*[STUDENTNUMBER];
	
	ScholarshipManagement scholarshipManagement(studentList, STUDENTNUMBER);
	menu();	// �޴� ��� �Լ�
	scholarshipManagement.run();

	return 0;
}
//------------------main ����------------------


// �޴� ��� �Լ�
void menu() {

	cout << "\n�޴�\n";
	cout << "1. ���б� ����\n";
	cout << "2. ���б� ������ ����\n";
	cout << "3. ���л� ����\n";
	cout << "4. �����ϱ�\n";
	cout << "* ������ �Է��ϼ���: ";

};