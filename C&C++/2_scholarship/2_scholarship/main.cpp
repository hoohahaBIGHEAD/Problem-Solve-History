#include "header.h"

int main() {
	//Student 배열을 생성한다.
	Student** studentList = new Student*[STUDENTNUMBER];
	
	//ScholarshipManagement에 생성한 studentList와 STUDENTNUMBER를 보내준다.
	ScholarshipManagement scholarshipManagement(studentList, STUDENTNUMBER);

	//프로그램을 실행하고 메뉴를 출력한다.
	menu();	// 메뉴 출력 함수
	
	//scholarshipManagement를 실행시킨다.
	scholarshipManagement.run();

	//성공적으로 프로그램이 끝났다면 0을 리턴한다.
	return 0;
}


