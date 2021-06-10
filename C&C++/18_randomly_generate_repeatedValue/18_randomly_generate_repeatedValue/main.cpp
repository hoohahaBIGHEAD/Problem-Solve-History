/*
랜덤한 인덱스를 만들 배열 정의
배열을 0부터 ROW*COL 까지 초기화	// 배열에는 0, 1, 2, ..., ROW*COL-1 이 저장된다.

해당 배열의 인덱스 섞기(shuffle)	// 배열에는 52, 1, 35, ..., 2 등의 값이 저장된다.

array_repeated_value = 랜덤한 repeatedValue 를 저장할 배열 정의

반복문 시작(i = 0부터 ROW*MIN-1까지)
	duplicated_count = repeatedValue 몇 개 저장할 지 생성. 현재 코드에서는 2개 이상 10개 이하로 했다.
	repeatedValue 생성

	만약 위 숫자대로 저장하고 남은 원소 수가 1개 이하라면
		repeatedValue 를 마지막까지 저장하도록 인덱스 정의

	반복문 시작(j = i부터 i + duplicated_count -1까지
		array_repeated_value[j] = repeatedValue

	i+= duplicated_count
반복문 종료	//배열에는 0.1 0.1 0.1 0.33 0.33 0.22 0.22 0.22 0.22 0.22 0.22 등이 저장된다.

Element 클래스를 저장할 배열 생성

반복문 시작(i = 0부터 ROW*MIN-1까지)
	element[array_index[i]] = new Element(array_index[i] / COL, array_index[i] % COL, array_repeated_value[i]);
	//element의 array_index[i]에 해당 원소의 행과 열을 초기화하고 array_repeated_value[i] 를 넣는다.
	//element 배열에는 순차적으로 0부터 99까지 저장된다. 이때 repeatedValue는 최소 2개 이상 중복된다. 위의 반복문에 따라.

반복문 시작(i = 0부터 ROW*MIN-1까지)
	printf("%d, %d, %f\n", element[i]->getRow(), element[i]->getColumn(), element[i]->getRepeatedValue());
	//클래스를 0부터 ROW*MIN-1까지 순차적으로 출력한다.
*/

#include <stdlib.h>	//srand
#include <time.h>
#include <stdio.h>

#define ROW 5
#define COL 10

class Element
{
public:
	Element();
	~Element();

	Element(int row, int column, double repeatedValue) {
		this->row = row;
		this->column = column;
		this->repeatedValue = repeatedValue;
	}

	void setRow(int row) {
		this->row = row;
	}
	int getRow() {
		return this->row;
	}
	void setColumn(int column) {
		this->column = column;
	}
	int getColumn() {
		return this->column;
	}
	void setRepeatedValue(double repeatedValue) {
		this->repeatedValue = repeatedValue;
	}
	double getRepeatedValue() {
		return this->repeatedValue;
	}

private:
	int row;
	int column;
	double repeatedValue;

	
};

Element::Element()
{
}

Element::~Element()
{
}


void shuffle(int* array, int array_number);




int FLOAT_MIN = 1;
int FLOAT_MAX = 10;
int INTRANDOM_MIN = 2;
int INTRANDOM_MAX = 10;



int main() {

	int array_index[ROW * COL] = { 0 };	//배열을 0으로 초기화. 이걸로 초기의 배열 위치를 초기화한다.
	int array_number = ROW * COL;	//전체 배열의 원소 수 초기화

	//array_index를 0, 1, 2, ..., array_number-1로 초기화
	for (size_t i = 0; i < array_number; i++)
		array_index[i] = i;

	shuffle(array_index, array_number);	//인덱스 섞기


	double repeated_value;
	int duplicated_count;
	
	double array_repeated_value[ROW * COL] = { 0 };	//배열을 0으로 초기화
	for (size_t i = 0; i < array_number;)
	{
		duplicated_count = INTRANDOM_MIN + (rand() % (INTRANDOM_MAX - INTRANDOM_MIN));	//INTRANDOM_MIN부터 INTRANDOM_MAX까지 랜덤 생성
		repeated_value = FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX / (FLOAT_MAX - FLOAT_MIN)));	//FLOAT_MIN부터 FLOAT_MAX까지 랜덤 생성
		int val = array_number - (i + duplicated_count);
		if (val < 2)	//만약 위 숫자대로 저장하고 남은 원소 수가 1개 이하라면
		{
			duplicated_count = (array_number) - i;
		}
		for (size_t j = i; j <(i+ duplicated_count); j++)
		{
			array_repeated_value[j] = repeated_value;
		}

		i += duplicated_count;
	}

	Element** element = new Element*[array_number];

	for (size_t i = 0; i < array_number; i++)
	{
		element[array_index[i]] = new Element(array_index[i] / COL, array_index[i] % COL, array_repeated_value[i]);
	}
	for (size_t i = 0; i < array_number; i++)
	{
		printf("%d, %d, %f\n", element[i]->getRow(), element[i]->getColumn(), element[i]->getRepeatedValue());
	}


	return 0;
}

////////////////카드 섞는 함수 정의////////////////////
// 배열을 섞는 함수 
void shuffle(int* array, int array_number) {
	//srand 는 호출할 때 전달받는 인자를 기반으로 해서 난수를 초기화 시켜주는 역할을 한다.
	//rand 는 srand 로 인해 생성된 값을 바탕으로 난수를 생성해 주는 역할을 한다.
	srand(time(NULL));
	int temp;
	int random_index;
	//맨 마지막의 원소에서는 섞지 않기 위해 for loop의 조건문에서 -1 했고 random_index에 +i 하였다.
	for (int i = 0; i < array_number - 1; i++) {
		random_index = rand() % (array_number - i) + i; // i 부터 array_number-1 사이에 임의의 정수 생성  - 배열의 인덱스를 고르는 것이다.
		temp = array[i];
		array[i] = array[random_index];
		array[random_index] = temp;
	}
}
////////////////카드 섞는 함수 정의//////////////////