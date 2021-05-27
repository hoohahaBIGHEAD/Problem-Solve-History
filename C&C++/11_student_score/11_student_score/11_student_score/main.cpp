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

	std::normal_distribution<double> dist(/* 평균 = */ 70, /* 표준 편차 = */ 20);
	float sample;
	
	Student student[50];
	int score[SUBJECTNUMBER];
	for (size_t i = 0; i < STUDENTNUMBER; i++) {
		for (size_t j = 0; j < SUBJECTNUMBER; j++)
			score[j] = dist(gen);
		student[i] = Student(score);
		student[i].number = i + 1;
	}
	//정렬
	Sort(student);

	printMenu(student);


	

	return 0;
}

void PrintNumOrder(Student student[]) {
	for (size_t i = 0; i < STUDENTNUMBER; i++)
	{
		cout << student[i].number << "번 학생 과목1 : " << student[i].grade[0] << "(" << student[i].score[0] << ")  과목2 : " << student[i].grade[1] << "(" << student[i].score[1] << ")" << endl;
	}
}
void PrintTotal(Student student[]) {
	for (size_t i = 0; i < STUDENTNUMBER; i++)
	{
		cout << student[rankTotal[i]].number << "번 학생 과목1 : " << student[rankTotal[i]].grade[0] << "(" << student[rankTotal[i]].score[0] << ")  과목2 : " << student[rankTotal[i]].grade[1] << "(" << student[rankTotal[i]].score[1] << ")" << endl;
	}
}
void Sort(Student student[]) {
	int score[SUBJECTNUMBER][STUDENTNUMBER];
	int rank[SUBJECTNUMBER][STUDENTNUMBER];
	int scoreTotal[STUDENTNUMBER];

	//전체 학생들의 totalGPA를 받아와 score[]에 저장한다.
	for (size_t i = 0; i < SUBJECTNUMBER; i++) {//2
		for (size_t j = 0; j < STUDENTNUMBER; j++)//50
		{
			score[i][j] = student[j].score[i];
			rank[i][j] = 1;	// 점수를 다른 사람과 비교하기 전에는 모두 1등일 가능성이 있으므로 석차배열을 1로 초기화한다. 
		}
	}

	for (size_t i = 0; i < SUBJECTNUMBER; i++) {//2
		for (size_t j = 0; j < STUDENTNUMBER; j++)//50
		{
			scoreTotal[i] = student[i].totalScore;
			rankTotal[i] = 1;	// 점수를 다른 사람과 비교하기 전에는 모두 1등일 가능성이 있으므로 석차배열을 1로 초기화한다. 
		}
	}
	for (size_t i = 0; i < STUDENTNUMBER; i++)//50
			for (size_t j = 0; j < STUDENTNUMBER; j++)//50
				if (scoreTotal[i] < scoreTotal[j])	//j번째 학생보다 score 가 높은 k번째 학생이 있고
					rankTotal[i]++;	//i번째 학생의 석차를 증가시킨다.

	for (size_t i = 0; i < STUDENTNUMBER; i++)//50
		student[i].totalRank = rankTotal[i];

	for (size_t i = 0; i < SUBJECTNUMBER; i++) //2
		for (size_t j = 0; j < STUDENTNUMBER; j++)//50
			for (size_t k = 0; k < STUDENTNUMBER; k++)//50
				if (score[i][j] < score[i][k])	//j번째 학생보다 score 가 높은 k번째 학생이 있고
					rank[i][j]++;	//i번째 학생의 석차를 증가시킨다.

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
		printf("1. 과목별 수강학생+총점 출력(1-1 : 학번순, 1-2: 성적순\n");
		printf("2. 과목별 수강학생+최종학점 출력(학번순)\n");
		printf("3. 전체 수강교과목에 대한 성적출력(학번순)\n");
		printf("4. 프로그램 종료\n");

		cin >> menuIndex;
		if (menuIndex == 1)
		{
			printf("1 : 학번순, 2: 성적순\n");
			cin >> menuIndex;
			if (menuIndex == 1)
			{
				//학번순 출력
				PrintNumOrder(student);
			}
			else if (menuIndex == 2)
			{
				//성적순 출력
				PrintTotal(student);
			}
		}
		else if (menuIndex == 2)
		{
			//printf("2. 과목별 수강학생+최종학점 출력(학번순)\n");
		}
		else if (menuIndex == 3)
		{
			//printf("3. 전체 수강교과목에 대한 성적출력(학번순)\n");
		}
		else if (menuIndex == 4)
		{
			//printf("4. 프로그램 종료\n");
		}
	}
	

}