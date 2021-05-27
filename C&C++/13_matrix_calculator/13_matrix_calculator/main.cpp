#include <iostream>
using namespace std;


#define MAX_ROW_COL 3	//최대 행과 열의 갯수를 지정한다.

//행렬 할당
int A[MAX_ROW_COL][MAX_ROW_COL];
int B[MAX_ROW_COL][MAX_ROW_COL];
int C[MAX_ROW_COL][MAX_ROW_COL];

//각 행렬의 행, 열을 저장한다. 이를 이용해 연산이 가능한지 판단한다.
int A_row, A_col, B_row, B_col, C_row, C_col;

void Run();

int main() {

	//행렬 연산 시행
	Run();
	return 0;
}

void Run() {
	while (true)
	{
		int index;
		int row, col, value;
		int row_temp[MAX_ROW_COL];

		cout << "A 행렬의 크기를 알려주세요.(-1:: 프로그램을 종료합니다.)" << endl;
		printf("ex) 1X3 :: \"1 3\", 4X2 :: \"4 2\" 입력\n");
		cin >> row >> col;
		//-1 입력 받았을 시 종료
		if (row == -1)
		{
			printf("프로그램을 종료합니다.\n");
			break;
		}
		A_row = row;
		A_col = col;

		cout << "A(" << row << "X" << col << ") 행렬의 원소를 알려주세요." << endl;
		for (size_t i = 0; i < row; i++)
			for (size_t j = 0; j < col; j++)
			{
				//cin 입력은 엔터를 읽을 때까지 버퍼에 남아 있다.
				cin >> row_temp[j];
				//행렬의 i열들에 값을 입력한다.
				A[i][j] = row_temp[j];
			}

		cout << "B 행렬의 크기를 알려주세요." << endl;
		printf("ex) 1X3 :: \"1 3\", 4X2 :: \"4 2\" 입력\n");
		cin >> row >> col;
		B_row = row;
		B_col = col;

		cout << "B(" << row << "X" << col << ") 행렬의 원소를 알려주세요." << endl;
		for (size_t i = 0; i < row; i++)
			for (size_t j = 0; j < col; j++)
			{
				//cin 입력은 엔터를 읽을 때까지 버퍼에 남아 있다.
				cin >> row_temp[j];
				//행렬의 i열들에 값을 입력한다.
				B[i][j] = row_temp[j];
			}

		//주어진 행렬로 연산을 시행한다.
		while (true)
		{
			printf("수행할 연산을 입력하세요. 1: 덧셈(A+B) 2: 뺄셈(A-B) 3: 곱셈(A*B) 4: 새로운 행렬 입력\n");
			cin >> index;
			//덧셈 수행
			if (index == 1)
			{
				//A와 B가 같은 크기인지 확인
				if (A_row == B_row && A_col == B_col)
				{
					//C의 행렬 크기를 지정한다.
					C_row = A_row;
					C_col = A_col;

					//덧셈 연산 수행
					for (size_t i = 0; i < A_row; i++)
						for (size_t j = 0; j < A_col; j++)
							C[i][j] = A[i][j] + B[i][j];

					printf("Matrix Add\n");
					printf("----------\n");
					for (size_t i = 0; i < C_row; i++)
					{
						for (size_t j = 0; j < C_col; j++)
							cout << C[i][j] << " ";
						//행 출력 후 엔터
						cout << "\n";
					}
				}
				//A와 B가 같은 크기가 아니라면
				else
					printf("할 수 없습니다.\n");
			}
			//뺄셈 수행
			else if (index == 2)
			{
				//A와 B가 같은 크기인지 확인
				if (A_row == B_row && A_col == B_col)
				{
					//C의 행렬 크기를 지정한다.
					C_row = A_row;
					C_col = A_col;

					//뺄셈 연산 수행
					for (size_t i = 0; i < A_row; i++)
						for (size_t j = 0; j < A_col; j++)
							C[i][j] = A[i][j] - B[i][j];

					printf("Matrix Sub\n");
					printf("----------\n");
					for (size_t i = 0; i < C_row; i++)
					{
						for (size_t j = 0; j < C_col; j++)
							cout << C[i][j] << " ";
						//행 출력 후 엔터
						cout << "\n";
					}
				}
				//A와 B가 같은 크기가 아니라면
				else
					printf("할 수 없습니다.\n");
			}
			//곱셈 수행
			else if (index == 3)
			{
				//A의 열과 B의 행 수가 일치하는지 확인
				if (A_col == B_row)
				{
					//C의 행렬 크기를 지정한다.
					C_row = A_row;
					C_col = B_col;

					/*for문 3번 돈다.
					1, 2번째 for문 : C[i][j]를 구하기 위해 연산
					3번째 for문 : k
					C[i][j]는 시그마 A의 i행 k열 * B의 k행 j열이다.
					이를 아래에 구현했다.
					*/
					for (size_t i = 0; i < A_row; i++)
						for (size_t j = 0; j < B_col; j++)
							for (size_t k = 0; k < A_row; k++)
								C[i][j] += A[i][k] * B[k][j];

					printf("Matrix Mul\n");
					printf("----------\n");
					for (size_t i = 0; i < C_row; i++)
					{
						for (size_t j = 0; j < C_col; j++)
							cout << C[i][j] << " ";
						//행 출력 후 엔터
						cout << "\n";
					}
				}
				//A의 열과 B의 행 수가 일치하지 않는다면
				else
					printf("할 수 없습니다.\n");
			}
			//행렬의 계산을 빠져나간다. 그러면 Run()의 첫번째 while 문으로 들어간다.
			else if (index == 4)
			{
				printf("새로운 행렬을 입력합니다.\n");
				break;
			}
		}
	}
