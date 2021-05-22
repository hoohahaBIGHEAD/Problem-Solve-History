#include <stdio.h>
#include <stdlib.h> 
//#include <cstdlib>

//#define _CRT_SECURE_NO_WARNINGS    // strtok 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>
#include <string.h>    // strtok 함수가 선언된 헤더 파일


#define VERTEXNUMBERMAX 10
#define INFINITY 100000
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))


int main() {

	int dimention[VERTEXNUMBERMAX][VERTEXNUMBERMAX][VERTEXNUMBERMAX];

	int N_location;
	int M_roads;
	int K_candidates = 1;
	int K_array[100];
	int K_array_distance_total[100] = {0, };

	int X, Y, Z;

	char s1[INFINITY];

	fgets(s1, INFINITY, stdin);

	char* context = NULL;
	char* ptr = strtok_s(s1, " ", &context);
	N_location = atoi(ptr);
	ptr = strtok_s(NULL, " ", &context);
	M_roads = atoi(ptr);
	
	printf("%d %d\n", N_location, M_roads);


	fgets(s1, INFINITY, stdin);
	context = NULL;
	ptr = strtok_s(s1, " ", &context);
	K_array[0] = atoi(ptr);
	ptr = strtok_s(NULL, " ", &context);
	
	
	//파싱 부분
	for (int i = 1; ptr!=NULL; i++)
	{
		K_array[i] = atoi(ptr);
		ptr = strtok_s(NULL, " ", &context);
		K_candidates++;
	}
	
	printf("\nK = %d\n", K_candidates);
	for (int i = 0; i < K_candidates; i++)
	{
		printf("K_array[%d] = %d\n", i, K_array[i]);
	}

	for (int k = 0; k < N_location; k++)
	{
		for (int i = 0; i < N_location; i++)
		{
			for (int j = 0; j < N_location; j++)
			{
				if (i == j)
					dimention[k][i][j] = 0;
				else
					dimention[k][i][j] = INFINITY;
			}
		}
	}
	
	//초기 선언
	for (int i = 0; i < M_roads; i++)
	{
		fgets(s1, INFINITY, stdin);
		context = NULL;
		ptr = strtok_s(s1, " ", &context);
		X = atoi(ptr);
		ptr = strtok_s(NULL, " ", &context);
		Y = atoi(ptr);
		ptr = strtok_s(NULL, " ", &context);
		Z = atoi(ptr);
		//문제에서 입력은 1부터 시작
		dimention[0][X-1][Y-1] = Z;
		dimention[0][Y - 1][X - 1] = Z;
	}
	
	//입력 확인
	/*for (int i = 0; i < N_location; i++)
	{
		for (int j = 0; j < N_location; j++)
		{
			printf("%d\t", dimention[0][i][j]);
		}
		printf("\n");
	}*/

	
	//DP
	for (int k = 1; k < N_location; k++)
	{
		for (int i = 0; i < N_location; i++)
		{
			for (int j = 0; j < N_location; j++)
			{
					dimention[k][i][j] = min(dimention[k - 1][i][j], dimention[k - 1][i][k] + dimention[k - 1][k][j]);
				}
			}
		}
	


	//k 대신 N_location-1
	
	
	for (int i = 0; i < N_location; i++)
	{
		for (int j = 0; j < N_location; j++)
		{
			if(dimention[N_location - 1][j][i]!= INFINITY)
			K_array_distance_total[i] += dimention[N_location - 1][j][i];
		}
	}
	printf("\n");

	//K_array 출력
	printf("K_array 출력\n");
	for (int i = 0; i < N_location; i++) {
		printf("%d\t", K_array_distance_total[i]);
	}
	printf("\n");
	

	//DP출력
	printf("DP출력\n");
	for (int k = 0; k < N_location; k++)
	{
		for (int i = 0; i < N_location; i++)
		{
			for (int j = 0; j < N_location; j++)
			{
				printf("%d\t", dimention[k][i][j]);
			}
			printf("\n");
		}
		printf("\n\n");
	}



	return 0;
	
}