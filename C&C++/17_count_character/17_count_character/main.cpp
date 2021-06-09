#include <stdio.h>
#include <iostream>
#include <atlstr.h>	//CString

using namespace std;

int character_counter(CString string, char character_temp){
	int msg_len = string.GetLength();
	int find_count = 0;
	for (size_t i = 0; i < msg_len; i++)
		if (string[i] == character_temp)
			find_count++;
	return find_count;
}

int main() {
	//_UNICODE가 정의되어 있으면 _T는 리터럴 문자열을 L 접두사가 있는 형식으로 변환하고, 그렇지 않으면 L 접두사가 없는 문자열로 변환합니다. 
	//_T 매크로는 _TEXT 매크로와 동일합니다.

	CString string = _T("");
	char string_temp[1024];
	char character_temp;
	int character_count;

	cin.clear();
	cout << "Enter a string: ";
	cin.getline(string_temp, sizeof(string_temp), '\n');
	string = string_temp;
	cout << "Enter a character: ";
	cin >> character_temp;
	character_count = character_counter(string, character_temp);
	printf("%c appears in %S %d times\n", character_temp, string, character_count);

	return 0;
}