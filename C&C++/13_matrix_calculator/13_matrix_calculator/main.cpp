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

		cout << "A ����� ũ�⸦ �˷��ּ���.(-1:: ���α׷��� �����մϴ�.)" << endl;
		printf("ex) 1X3 :: \"1 3\", 4X2 :: \"4 2\" �Է�\n");
		cin >> row >> col;
		//-1 �Է� �޾��� �� ����
		if (row == -1)
		{
			printf("���α׷��� �����մϴ�.\n");
			break;
		}
		A_row = row;
		A_col = col;

		cout << "A(" << row << "X" << col << ") ����� ���Ҹ� �˷��ּ���." << endl;
		//printf("ex) 2�� 3���̸�\n\"1 2 1\"\n\"3 1 2\" �Է�\n2�� 2���̸�\n\"4 2\"\n\"1 2\"\n �Է�\n");
		for (size_t i = 0; i < row; i++)
			for (size_t j = 0; j < col; j++)
			{
				cin >> row_temp[j];
				A[i][j] = row_temp[j];
			}

		/*printf("�Է��� ����� �Ʒ��� �����ϴ�.\n");
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
				cout << A[i][j] << " ";
			cout << "\n";
		}*/

		cout << "B ����� ũ�⸦ �˷��ּ���." << endl;
		printf("ex) 1X3 :: \"1 3\", 4X2 :: \"4 2\" �Է�\n");
		cin >> row >> col;
		B_row = row;
		B_col = col;

		cout << "B(" << row << "X" << col << ") ����� ���Ҹ� �˷��ּ���." << endl;
		//printf("ex) 2�� 3���̸�\n\"1 2 1\"\n\"3 1 2\" �Է�\n2�� 2���̸�\n\"4 2\"\n\"1 2\"\n �Է�\n");
		for (size_t i = 0; i < row; i++)
			for (size_t j = 0; j < col; j++)
			{
				cin >> row_temp[j];
				B[i][j] = row_temp[j];
			}

		/*printf("�Է��� ����� �Ʒ��� �����ϴ�.\n");
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
				cout << B[i][j] << " ";
			cout << "\n";
		}*/

		while (true)
		{
			printf("������ ������ �Է��ϼ���. 1: ����(A+B) 2: ����(A-B) 3: ����(A*B) 4: ���ο� ��� �Է�\n");
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
					printf("�� �� �����ϴ�.\n");
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
					printf("�� �� �����ϴ�.\n");
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
					printf("�� �� �����ϴ�.\n");
				}
			}
			else if (index == 4)
			{
				printf("���ο� ����� �Է��մϴ�.\n");
				break;
			}
		}
	}

	

	

	




}