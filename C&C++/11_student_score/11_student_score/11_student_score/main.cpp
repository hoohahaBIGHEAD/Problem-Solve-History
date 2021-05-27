#
#include <random>
#include <iostream>
using namespace std;

#define SUBJECTNUMBER 2
#define STUDENTNUMBER 50

static int rankTotal[STUDENTNUMBER];

class Student
{
public:
	int score[SUBJECTNUMBER];
	int rank[SUBJECTNUMBER];
	int number;
	int totalScore;
	int totalRank;
	string grade[SUBJECTNUMBER];
	Student(int score[]) {
		totalScore = 0;
		for (size_t i = 0; i < SUBJECTNUMBER; i++)
		{
			if (score[i] > 100) score[i] = 100;
			if (score[i] < 0) score[i] = 0;
			this->score[i] = score[i];
			totalScore += score[i];
		}
		
		
	}
	Student() {
	}

private:

};
void PrintNumOrder(Student student[]);
void Sort(Student student[]);
void printMenu(Student student[]);



int main() {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::normal_distribution<double> dist(/* ��� = */ 70, /* ǥ�� ���� = */ 20);
	float sample;
	
	Student student[50];
	int score[SUBJECTNUMBER];
	for (size_t i = 0; i < STUDENTNUMBER; i++) {
		for (size_t j = 0; j < SUBJECTNUMBER; j++)
			score[j] = dist(gen);
		student[i] = Student(score);
		student[i].number = i + 1;
	}
	//����
	Sort(student);

	printMenu(student);


	

	return 0;
}

void PrintNumOrder(Student student[]) {
	for (size_t i = 0; i < STUDENTNUMBER; i++)
	{
		cout << student[i].number << "�� �л� ����1 : " << student[i].grade[0] << "(" << student[i].score[0] << ")  ����2 : " << student[i].grade[1] << "(" << student[i].score[1] << ")" << endl;
	}
}
void PrintTotal(Student student[]) {
	for (size_t i = 0; i < STUDENTNUMBER; i++)
	{
		cout << student[rankTotal[i]].number << "�� �л� ����1 : " << student[rankTotal[i]].grade[0] << "(" << student[rankTotal[i]].score[0] << ")  ����2 : " << student[rankTotal[i]].grade[1] << "(" << student[rankTotal[i]].score[1] << ")" << endl;
	}
}
void Sort(Student student[]) {
	int score[SUBJECTNUMBER][STUDENTNUMBER];
	int rank[SUBJECTNUMBER][STUDENTNUMBER];
	int scoreTotal[STUDENTNUMBER];

	//��ü �л����� totalGPA�� �޾ƿ� score[]�� �����Ѵ�.
	for (size_t i = 0; i < SUBJECTNUMBER; i++) {//2
		for (size_t j = 0; j < STUDENTNUMBER; j++)//50
		{
			score[i][j] = student[j].score[i];
			rank[i][j] = 1;	// ������ �ٸ� ����� ���ϱ� ������ ��� 1���� ���ɼ��� �����Ƿ� �����迭�� 1�� �ʱ�ȭ�Ѵ�. 
		}
	}

	for (size_t i = 0; i < SUBJECTNUMBER; i++) {//2
		for (size_t j = 0; j < STUDENTNUMBER; j++)//50
		{
			scoreTotal[i] = student[i].totalScore;
			rankTotal[i] = 1;	// ������ �ٸ� ����� ���ϱ� ������ ��� 1���� ���ɼ��� �����Ƿ� �����迭�� 1�� �ʱ�ȭ�Ѵ�. 
		}
	}
	for (size_t i = 0; i < STUDENTNUMBER; i++)//50
			for (size_t j = 0; j < STUDENTNUMBER; j++)//50
				if (scoreTotal[i] < scoreTotal[j])	//j��° �л����� score �� ���� k��° �л��� �ְ�
					rankTotal[i]++;	//i��° �л��� ������ ������Ų��.

	for (size_t i = 0; i < STUDENTNUMBER; i++)//50
		student[i].totalRank = rankTotal[i];

	for (size_t i = 0; i < SUBJECTNUMBER; i++) //2
		for (size_t j = 0; j < STUDENTNUMBER; j++)//50
			for (size_t k = 0; k < STUDENTNUMBER; k++)//50
				if (score[i][j] < score[i][k])	//j��° �л����� score �� ���� k��° �л��� �ְ�
					rank[i][j]++;	//i��° �л��� ������ ������Ų��.

	for (size_t i = 0; i < SUBJECTNUMBER; i++) //2
		for (size_t j = 0; j < STUDENTNUMBER; j++)//50
			student[j].rank[i] = rank[i][j];

	for (size_t i = 0; i < SUBJECTNUMBER; i++) //2
		for (size_t j = 0; j < STUDENTNUMBER; j++) {
			if (rank[i][j] < (STUDENTNUMBER * 0.35))
			{
				if (rank[i][j] < (STUDENTNUMBER * 0.35) / 3)
					student[j].grade[i] = "A+";
				else if ((STUDENTNUMBER * 0.35) / 3 < rank[i][j] && rank[i][j] < (STUDENTNUMBER * 0.35 * 2) / 3)
					student[j].grade[i] = "A0";
				else
					student[j].grade[i] = "A-";
			}
			else if ((STUDENTNUMBER * 0.35) / 3 < rank[i][j] && rank[i][j] < (STUDENTNUMBER * 0.75))
			{
				if ((STUDENTNUMBER * 0.35) / 3 < rank[i][j] && rank[i][j] < (STUDENTNUMBER * (0.35 + 0.4 / 3)))
					student[j].grade[i] = "B+";
				else if ((STUDENTNUMBER * (0.35 + 0.4 / 3)) < rank[i][j] && rank[i][j] < (STUDENTNUMBER * (0.35 + 2 * 0.4 / 3)))
					student[j].grade[i] = "B0";
				else
					student[j].grade[i] = "B-";
			}
			else
			{
				if ((STUDENTNUMBER * (0.35 + 0.4)) < rank[i][j] && rank[i][j] < (STUDENTNUMBER * (0.35 + 0.4 + 0.25/3)))
					student[j].grade[i] = "C+";
				else if ((STUDENTNUMBER * (0.35 + 0.4 + 0.25 / 3)) < rank[i][j] && rank[i][j] < (STUDENTNUMBER * (0.35 + 0.4 + 2*0.25 / 3)))
					student[j].grade[i] = "C0";
				else
					student[j].grade[i] = "C-";
			}
		}
			//50
	


}



void printMenu(Student student[]){
	int menuIndex;
	while (true)
	{
		printf("1. ���� �����л�+���� ���(1-1 : �й���, 1-2: ������\n");
		printf("2. ���� �����л�+�������� ���(�й���)\n");
		printf("3. ��ü ���������� ���� �������(�й���)\n");
		printf("4. ���α׷� ����\n");

		cin >> menuIndex;
		if (menuIndex == 1)
		{
			printf("1 : �й���, 2: ������\n");
			cin >> menuIndex;
			if (menuIndex == 1)
			{
				//�й��� ���
				PrintNumOrder(student);
			}
			else if (menuIndex == 2)
			{
				//������ ���
				PrintTotal(student);
			}
		}
		else if (menuIndex == 2)
		{
			//printf("2. ���� �����л�+�������� ���(�й���)\n");
		}
		else if (menuIndex == 3)
		{
			//printf("3. ��ü ���������� ���� �������(�й���)\n");
		}
		else if (menuIndex == 4)
		{
			//printf("4. ���α׷� ����\n");
		}
	}
	

}