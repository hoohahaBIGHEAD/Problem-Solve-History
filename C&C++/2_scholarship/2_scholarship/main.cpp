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


