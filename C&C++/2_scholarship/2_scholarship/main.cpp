#include <iostream>
using namespace std;

//------------------�Լ� �����------------------
void menu();	// �޴� ��� �Լ�
//------------------�Լ� �����------------------

int main() {

	menu();	// �޴� ��� �Լ�

	return 0;
}
//------------------main ����------------------


// �޴� ��� �Լ�
void menu() {

	int menu_index;	// �޴� ������ ���� �ε���
	cout << "\n�޴�\n";
	cout << "1. ���б� ����\n";
	cout << "2. ���б� ������ ����\n";
	cout << "3. ���л� ����\n";
	cout << "4. �����ϱ�\n";

	cout << "* ������ �Է��ϼ���: ";
	cin >> menu_index;


	/*
	// �Է¿� �°� �Լ��� �θ���.
	if (menu_index == 1) student_insert();
	else if (menu_index == 2) student_change();
	else if (menu_index == 3) student_search();
	else if (menu_index == 4) student_delete();
	else if (menu_index == 5) student_lookup(student_array, student_count);
	else if (menu_index == 0) save_exit();
	else
	{
		cout << "�߸��� ���� �Է��߽��ϴ�.\n\n";
		// �߸��� ���� �Էµ� ��� �޴� �Լ��� �ٽ� ȣ���Ѵ�.
		menu();
	}
	*/

};