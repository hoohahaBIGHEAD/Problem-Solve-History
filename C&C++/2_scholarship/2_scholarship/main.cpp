#include <iostream>
using namespace std;
#include <string>
#include <sstream>

#include "header.h"


int main() {
	//Student �迭�� �����Ѵ�.
	Student** studentList = new Student*[STUDENTNUMBER];
	
	//ScholarshipManagement�� ������ studentList�� STUDENTNUMBER�� �����ش�.
	ScholarshipManagement scholarshipManagement(studentList, STUDENTNUMBER);

	//���α׷��� �����ϰ� �޴��� ����Ѵ�.
	menu();	// �޴� ��� �Լ�
	
	//scholarshipManagement�� �����Ų��.
	scholarshipManagement.run();

	//���������� ���α׷��� �����ٸ� 0�� �����Ѵ�.
	return 0;
}


// �޴� ��� �Լ�
void menu() {

	cout << "\n�޴�\n";
	cout << "1. ���б� ����\n";
	cout << "2. ���б� ������ ����\n";
	cout << "3. ���л� ����\n";
	cout << "4. �����ϱ�\n";
	cout << "* ������ �Է��ϼ���: ";

};