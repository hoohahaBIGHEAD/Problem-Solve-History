#include <iostream>
using namespace std;

//------------------함수 선언부------------------
void menu();	// 메뉴 출력 함수
//------------------함수 선언부------------------

int main() {

	menu();	// 메뉴 출력 함수

	return 0;
}
//------------------main 실행------------------


// 메뉴 출력 함수
void menu() {

	int menu_index;	// 메뉴 선택을 위한 인덱스
	cout << "\n메뉴\n";
	cout << "1. 장학금 지원\n";
	cout << "2. 장학금 지원자 정보\n";
	cout << "3. 장학생 선정\n";
	cout << "4. 종료하기\n";

	cout << "* 연산을 입력하세요: ";
	cin >> menu_index;


	/*
	// 입력에 맞게 함수를 부른다.
	if (menu_index == 1) student_insert();
	else if (menu_index == 2) student_change();
	else if (menu_index == 3) student_search();
	else if (menu_index == 4) student_delete();
	else if (menu_index == 5) student_lookup(student_array, student_count);
	else if (menu_index == 0) save_exit();
	else
	{
		cout << "잘못된 값을 입력했습니다.\n\n";
		// 잘못된 값이 입력될 경우 메뉴 함수를 다시 호출한다.
		menu();
	}
	*/

};