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
	
	//printf("%d %d\n", N_location, M_roads);


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
	
	//K_array출력
	/*printf("\nK = %d\n", K_candidates);
	for (int i = 0; i < K_candidates; i++)
	{
		printf("K_array[%d] = %d\n", i, K_array[i]);
	}*/

	//초기화
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
	
	//초기 입력
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
	//K 합치기
	for (int i = 0; i < N_location; i++)
	{
		for (int j = 0; j < N_location; j++)
		{
			if(dimention[N_location - 1][j][i]!= INFINITY)
			K_array_distance_total[i] += dimention[N_location - 1][j][i];
		}
	}
	//printf("\n");

	//벌텍스로 된 값들만 빼주기
	for (int i = 0; i < N_location; i++)
	{
		for (int j = 0; j < K_candidates; j++)
		{
			K_array_distance_total[i] -= dimention[N_location - 1][K_array[j]-1][i];
		}
	}
	
	//K_array_distance_total에서 K_array[j]-1 각각의 점들 중에서 제일 큰 값을 골라라. 그리고 그걸 평균 거리를 출력해라. 반올림해서.
	//2개 이상이면 모두 출력해라.
	int temp = K_array_distance_total[K_array[0]-1];	//첫 값을 제일 크게 주어라. 아니, 첫값을 K어레이중 하나로 주어라
	int j = 0;	//최종 후보 수 = j+1개
	int K_done[100] = { 0, }; //최종 후보 번호들. 인덱스는 -1 해주어야 한다.
	K_done[0] = K_array[0]; //후보 점들만 넣을 것이다.
	//캔디데이트까지 확인해라. 맥스라면 K_done[0]에 노드 값을 넣고, 하위 인덱스들을 모두 초기화해줘라 같다면 그 다음 인덱스에 넣어라.
	for (int i = 0; i < K_candidates; i++)
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
				//처음 1명이면 j = 1이 된다.
				K_done[j++] = K_array[i];
			}
		}
	}

	//printf("\n최종후보 출력\n");
	for (size_t i = 0; i < j; i++)
	{
		printf("%d\t", K_done[i]);
	}
	
	printf("\n%.2f", (float)K_array_distance_total[K_done[0] - 1] / (float)(N_location-K_candidates));

	//K_array 출력
	/*printf("K_array 출력\n");
	for (int i = 0; i < N_location; i++) {
		printf("%d\t", K_array_distance_total[i]);
	}
	printf("\n");*/
	

	//DP출력
	/*printf("DP출력\n");
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
	}*/



	return 0;
	
}