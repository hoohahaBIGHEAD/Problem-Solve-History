#include <random>
#include <iostream>
using namespace std;
int main() {

	std::normal_distribution<double> dist(/* 평균 = */ 70, /* 표준 편차 = */ 20);

	int arr[100];
	for (size_t i = 0; i < 50; i++)
	{
		arr[i] = hist[std::round(dist(gen))];
	}

	for (size_t i = 0; i < 50; i++)
	{
		printf("%d번 학생 : %d\n", i, arr[i]);
	}

	return 0;
}

void printMenu(){
	printf("1. 과목별 수강학생+총점 출력(1-1 : 학번순, 1-2: 성적순\n");
	printf("2. 과목별 수강학생+최종학점 출력(학번순)\n");
	printf("3. 전체 수강교과목에 대한 성적출력(학번순)\n");
	printf("4. 프로그램 종료\n");

	int menuIndex;
	cin >> menuIndex;

}