/*
������ �ε����� ���� �迭 ����
�迭�� 0���� ROW*COL ���� �ʱ�ȭ	// �迭���� 0, 1, 2, ..., ROW*COL-1 �� ����ȴ�.

�ش� �迭�� �ε��� ����(shuffle)	// �迭���� 52, 1, 35, ..., 2 ���� ���� ����ȴ�.

array_repeated_value = ������ repeatedValue �� ������ �迭 ����

�ݺ��� ����(i = 0���� ROW*MIN-1����)
	duplicated_count = repeatedValue �� �� ������ �� ����. ���� �ڵ忡���� 2�� �̻� 10�� ���Ϸ� �ߴ�.
	repeatedValue ����

	���� �� ���ڴ�� �����ϰ� ���� ���� ���� 1�� ���϶��
		repeatedValue �� ���������� �����ϵ��� �ε��� ����

	�ݺ��� ����(j = i���� i + duplicated_count -1����
		array_repeated_value[j] = repeatedValue

	i+= duplicated_count
�ݺ��� ����	//�迭���� 0.1 0.1 0.1 0.33 0.33 0.22 0.22 0.22 0.22 0.22 0.22 ���� ����ȴ�.

Element Ŭ������ ������ �迭 ����

�ݺ��� ����(i = 0���� ROW*MIN-1����)
	element[array_index[i]] = new Element(array_index[i] / COL, array_index[i] % COL, array_repeated_value[i]);
	//element�� array_index[i]�� �ش� ������ ��� ���� �ʱ�ȭ�ϰ� array_repeated_value[i] �� �ִ´�.
	//element �迭���� ���������� 0���� 99���� ����ȴ�. �̶� repeatedValue�� �ּ� 2�� �̻� �ߺ��ȴ�. ���� �ݺ����� ����.

�ݺ��� ����(i = 0���� ROW*MIN-1����)
	printf("%d, %d, %f\n", element[i]->getRow(), element[i]->getColumn(), element[i]->getRepeatedValue());
	//Ŭ������ 0���� ROW*MIN-1���� ���������� ����Ѵ�.
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

	int array_index[ROW * COL] = { 0 };	//�迭�� 0���� �ʱ�ȭ. �̰ɷ� �ʱ��� �迭 ��ġ�� �ʱ�ȭ�Ѵ�.
	int array_number = ROW * COL;	//��ü �迭�� ���� �� �ʱ�ȭ

	//array_index�� 0, 1, 2, ..., array_number-1�� �ʱ�ȭ
	for (size_t i = 0; i < array_number; i++)
		array_index[i] = i;

	shuffle(array_index, array_number);	//�ε��� ����


	double repeated_value;
	int duplicated_count;
	
	double array_repeated_value[ROW * COL] = { 0 };	//�迭�� 0���� �ʱ�ȭ
	for (size_t i = 0; i < array_number;)
	{
		duplicated_count = INTRANDOM_MIN + (rand() % (INTRANDOM_MAX - INTRANDOM_MIN));	//INTRANDOM_MIN���� INTRANDOM_MAX���� ���� ����
		repeated_value = FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX / (FLOAT_MAX - FLOAT_MIN)));	//FLOAT_MIN���� FLOAT_MAX���� ���� ����
		int val = array_number - (i + duplicated_count);
		if (val < 2)	//���� �� ���ڴ�� �����ϰ� ���� ���� ���� 1�� ���϶��
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

////////////////ī�� ���� �Լ� ����////////////////////
// �迭�� ���� �Լ� 
void shuffle(int* array, int array_number) {
	//srand �� ȣ���� �� ���޹޴� ���ڸ� ������� �ؼ� ������ �ʱ�ȭ �����ִ� ������ �Ѵ�.
	//rand �� srand �� ���� ������ ���� �������� ������ ������ �ִ� ������ �Ѵ�.
	srand(time(NULL));
	int temp;
	int random_index;
	//�� �������� ���ҿ����� ���� �ʱ� ���� for loop�� ���ǹ����� -1 �߰� random_index�� +i �Ͽ���.
	for (int i = 0; i < array_number - 1; i++) {
		random_index = rand() % (array_number - i) + i; // i ���� array_number-1 ���̿� ������ ���� ����  - �迭�� �ε����� ���� ���̴�.
		temp = array[i];
		array[i] = array[random_index];
		array[random_index] = temp;
	}
}
////////////////ī�� ���� �Լ� ����//////////////////