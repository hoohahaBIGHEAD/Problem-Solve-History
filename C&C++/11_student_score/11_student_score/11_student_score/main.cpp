#include <random>
#include <iostream>
using namespace std;
int main() {

	std::normal_distribution<double> dist(/* ��� = */ 70, /* ǥ�� ���� = */ 20);

	int arr[100];
	for (size_t i = 0; i < 50; i++)
	{
		arr[i] = hist[std::round(dist(gen))];
	}

	for (size_t i = 0; i < 50; i++)
	{
		printf("%d�� �л� : %d\n", i, arr[i]);
	}

	return 0;
}

void printMenu(){
	printf("1. ���� �����л�+���� ���(1-1 : �й���, 1-2: ������\n");
	printf("2. ���� �����л�+�������� ���(�й���)\n");
	printf("3. ��ü ���������� ���� �������(�й���)\n");
	printf("4. ���α׷� ����\n");

	int menuIndex;
	cin >> menuIndex;

}