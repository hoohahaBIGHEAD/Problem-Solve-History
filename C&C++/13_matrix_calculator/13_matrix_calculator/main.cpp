#include <iostream>
using namespace std;


#define MAX_ROW_COL 3

int A[MAX_ROW_COL][MAX_ROW_COL];
int B[MAX_ROW_COL][MAX_ROW_COL];
int C[MAX_ROW_COL][MAX_ROW_COL];

int A_row, A_col, B_row, B_col, C_row, C_col;


void Run();


int main() {

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
		//printf("ex) 2행 3열이면\n\"1 2 1\"\n\"3 1 2\" 입력\n2행 2열이면\n\"4 2\"\n\"1 2\"\n 입력\n");
		for (size_t i = 0; i < row; i++)
			for (size_t j = 0; j < col; j++)
			{
				cin >> row_temp[j];
				A[i][j] = row_temp[j];
			}

		/*printf("입력한 행렬은 아래와 같습니다.\n");
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
				cout << A[i][j] << " ";
			cout << "\n";
		}*/

		cout << "B 행렬의 크기를 알려주세요." << endl;
		printf("ex) 1X3 :: \"1 3\", 4X2 :: \"4 2\" 입력\n");
		cin >> row >> col;
		B_row = row;
		B_col = col;

		cout << "B(" << row << "X" << col << ") 행렬의 원소를 알려주세요." << endl;
		//printf("ex) 2행 3열이면\n\"1 2 1\"\n\"3 1 2\" 입력\n2행 2열이면\n\"4 2\"\n\"1 2\"\n 입력\n");
		for (size_t i = 0; i < row; i++)
			for (size_t j = 0; j < col; j++)
			{
				cin >> row_temp[j];
				B[i][j] = row_temp[j];
			}

		/*printf("입력한 행렬은 아래와 같습니다.\n");
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
				cout << B[i][j] << " ";
			cout << "\n";
		}*/

		while (true)
		{
			printf("수행할 연산을 입력하세요. 1: 덧셈(A+B) 2: 뺄셈(A-B) 3: 곱셈(A*B) 4: 새로운 행렬 입력\n");
			cin >> index;
			if (index == 1)
			{
				if (A_row == B_row && A_col == B_col)
				{
					C_row = A_row;
					C_col = A_col;

					for (size_t i = 0; i < A_row; i++)
						for (size_t j = 0; j < A_col; j++)
							C[i][j] = A[i][j] + B[i][j];

					printf("Matrix Add\n");
					printf("----------\n");
					for (size_t i = 0; i < C_row; i++)
					{
						for (size_t j = 0; j < C_col; j++)
							cout << C[i][j] << " ";
						cout << "\n";
					}
				}
				else
				{
					printf("할 수 없습니다.\n");
				}
			}
			else if (index == 2)
			{
				if (A_row == B_row && A_col == B_col)
				{
					C_row = A_row;
					C_col = A_col;

					for (size_t i = 0; i < A_row; i++)
						for (size_t j = 0; j < A_col; j++)
							C[i][j] = A[i][j] - B[i][j];

					printf("Matrix Sub\n");
					printf("----------\n");
					for (size_t i = 0; i < C_row; i++)
					{
						for (size_t j = 0; j < C_col; j++)
							cout << C[i][j] << " ";
						cout << "\n";
					}
				}
				else
				{
					printf("할 수 없습니다.\n");
				}
			}
			else if (index == 3)
			{
				if (A_col == B_row)
				{
					C_row = A_row;
					C_col = B_col;


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
						cout << "\n";
					}
				}
				else
				{
					printf("할 수 없습니다.\n");
				}
			}
			else if (index == 4)
			{
				printf("새로운 행렬을 입력합니다.\n");
				break;
			}
		}
	}

	

	

	




}