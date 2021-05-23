#include <iostream>
using namespace std;

int main() {
	//int 형에 원소의 갯수가 5개인 배열 생성
	//생성 후 배열에 1, 3, 5, 7, 9 할당
	//해당 배열의 원소 5개를 더할 것이다.
	int arr[5] = {1, 3, 5, 7, 9};
	
	//int 형 변수 sum 을 생성하고 0을 할당한다.
	//변수 sum 에 배열 arr[5] 속의 원소들을 더할 것이다.
	int sum = 0;

	// i = 0부터 i = 4까지 5번 반복되는 for문을 수행한다.
	for (int i = 0; i < 5; i++)
	{
		//sum 에 arr[0], arr[1], ..., arr[4]를 더할 것이다.
		sum += arr[i];
	}
	
	//합을 출력한다
	cout << "sum : " << sum;
	
	//프로그램이 잘 끝나면 0을 출력하며 종료한다.
	return 0;
}