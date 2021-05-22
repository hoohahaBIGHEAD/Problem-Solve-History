#include <stdio.h>
#include <stdlib.h> 

#include <stdio.h>
#include <string.h>


#define VERTEXNUMBERMAX 10
#define INFINITY 100000
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))


int main() {

	int dimention[VERTEXNUMBERMAX][VERTEXNUMBERMAX][VERTEXNUMBERMAX];

	int N;
	int M;
	int K = 1;
	int K_array[100];
	int K_done[100] = { 0, };
	int K_array_distance_total[100] = { 0, };

	int X, Y, Z;

	char s1[INFINITY];

	fgets(s1, INFINITY, stdin);

	char* context = NULL;
	char* ptr = strtok_s(s1, " ", &context);
	N = atoi(ptr);
	ptr = strtok_s(NULL, " ", &context);
	M = atoi(ptr);

	fgets(s1, INFINITY, stdin);
	context = NULL;
	ptr = strtok_s(s1, " ", &context);
	K_array[0] = atoi(ptr);
	ptr = strtok_s(NULL, " ", &context);


	//파싱 부분
	for (int i = 1; ptr != NULL; i++)
	{
		K_array[i] = atoi(ptr);
		ptr = strtok_s(NULL, " ", &context);
		K++;
	}

	//초기화
	for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				if (i == j) dimention[k][i][j] = 0;
				else dimention[k][i][j] = INFINITY;
			}

	//초기 입력
	for (int i = 0; i < M; i++)
	{
		fgets(s1, INFINITY, stdin);
		context = NULL;
		ptr = strtok_s(s1, " ", &context);
		X = atoi(ptr);
		ptr = strtok_s(NULL, " ", &context);
		Y = atoi(ptr);
		ptr = strtok_s(NULL, " ", &context);
		Z = atoi(ptr);
		dimention[0][X - 1][Y - 1] = Z;
		dimention[0][Y - 1][X - 1] = Z;
	}


	//DP
	for (int k = 1; k < N; k++)
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				dimention[k][i][j] = min(dimention[k - 1][i][j], dimention[k - 1][i][k] + dimention[k - 1][k][j]);
	}


	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (dimention[N - 1][j][i] != INFINITY)
				K_array_distance_total[i] += dimention[N - 1][j][i];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < K; j++)
			K_array_distance_total[i] -= dimention[N - 1][K_array[j] - 1][i];

	int temp = K_array_distance_total[K_array[0] - 1];
	int j = 0;
	K_done[0] = K_array[0];
	for (int i = 0; i < K; i++)
	{
		{
			if (K_array_distance_total[K_array[i] - 1] < temp) {
				for (int k = 0; k < 100; k++)
				{
					K_done[k] = 0;
					j = 1;
				}
				K_done[0] = K_array[i];
				temp = K_array_distance_total[i];
			}
			else if (K_array_distance_total[K_array[i] - 1] == temp)
			{
				K_done[j++] = K_array[i];
			}
		}
	}

	for (size_t i = 0; i < j; i++)
	{
		printf("%d\t", K_done[i]);
	}

	printf("\n%.2f", (float)K_array_distance_total[K_done[0] - 1] / (float)(N - K));

	return 0;

}
