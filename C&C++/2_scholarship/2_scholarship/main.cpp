#include <iostream>
using namespace std;
#include <string>


//------------------�Լ� �����------------------
void menu();	// �޴� ��� �Լ�
//------------------�Լ� �����------------------

//------------------Ŭ���� �����------------------

// Student ����
class Student {
public:
	//�����ڷ� �Է�
	string name;
	float majorCredit;
	float minorCredit;
	float majorGPA;
	float minorGPA;

	//�������� ����
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
			to_string(this->tuition) + "����\n";
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
		return this->name + " " +
			to_string(this->majorCredit) + " " +
			to_string(this->minorCredit) + " " +
			to_string(this->majorGPA) + " " +
			to_string(this->minorGPA) + " " +
			this->lab + " " +
			this->degreeProgram + " " +
			to_string(this->totalGPA) + " " +
			to_string(this->tuition) + "����\n";
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

		//�������� ����
		this->totalGPA = this->getGPA();
		this->tuition = this->getTuition();
	}
};


class ScholarshipManagement {
	Student** studentList;
	int num_of_students;

	void run() {
		int menuIndex;	// �޴� ������ ���� �ε���
		cin >> menuIndex;

		// �Է¿� �°� �Լ��� �θ���.
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
				cout << "�߸��� ���� �Է��߽��ϴ�.\n\n";
				// �߸��� ���� �Էµ� ��� �޴� �Լ��� �ٽ� ȣ���Ѵ�.
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

//------------------Ŭ���� �����------------------

int main() {
	Student** studentList = new Student*[6];
	
	menu();	// �޴� ��� �Լ�


	
	
	



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