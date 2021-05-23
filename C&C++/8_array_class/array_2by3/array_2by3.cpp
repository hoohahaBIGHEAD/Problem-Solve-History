#include <iostream>
using namespace std;

int main() {
	//int 형에 원소의 갯수가 2*3개인 배열 생성
	//생성 후 배열에 
	//1, 3, 5, 
	//7, 9, 11 할당
	//해당 배열의 원소 6개를 더할 것이다.
	int arr[2][3] = { 1, 3, 5, 7, 9, 11 };

	//int 형 변수 sum 을 생성하고 0을 할당한다.
	//변수 sum 에 배열 arr[2][3] 속의 원소들을 더할 것이다.
	int sum = 0;

	// i = 0부터 i = 1까지 2번 반복되는 for문을 수행한다.
	for (int i = 0; i < 2; i++)
	{
		// j = 0부터 i = 2까지 3번 반복되는 for문을 수행한다.
		for (int j = 0; j < 3; j++)
		{
			//sum 에 arr[0][0], arr[0][1], arr[0][2], arr[1][0], arr[1][1], arr[1][2] 를 순서대로 더할 것이다.
			sum += arr[i][j];
		}
		
	}

	//합을 출력한다
	cout << "sum : " << sum;

}