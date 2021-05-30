#include <omp.h>
#include <stdio.h>
#include<stdlib.h>

typedef enum _boolean {
	FALSE,
	TRUE
} boolean;

#define FALSE 0
#define TRUE 1

#define PRIMENUMBER 200000

int main(int argc, char* argv[]) {
	int count = 0;
	int type, threadNumber;
	double t1, t2;
	int i;
	type = atoi(argv[1]);
	threadNumber = atoi(argv[2]);
	omp_set_num_threads(threadNumber);
	printf("mode : %d\t threads : %d\n", type, threadNumber);
	
	t1 = omp_get_wtime();
	if (type == 1)
	{
#pragma omp parallel for schedule(static) reduction(+:count)
		for (i = 0; i < PRIMENUMBER; i++) {
			int val = 0;
			if (isPrime(i))
				val = val + 1;
			count = count + val;
		}

	}
	else if (type == 2)
	{
#pragma omp parallel for schedule(dynamic) reduction(+:count)
		for (i = 0; i < PRIMENUMBER; i++) {
			int val = 0;
			if (isPrime(i))
				val = val + 1;
			count = count + val;
		}
	}
	else if (type == 3)
	{
#pragma omp parallel for schedule(guided) reduction(+:count)
		for (i = 0; i < PRIMENUMBER; i++) {
			int val = 0;
			if (isPrime(i))
				val = val + 1;
			count = count + val;
		}
	}
	else
	{
		printf("잘못된 입력입니다.\n");
	}
	t2 = omp_get_wtime();


	printf("count : %d\tcomputation time : %lf\n", count, t2-t1);
	return 0;
}

boolean isPrime(int x) {

	int i;
	if (x <= 1) return FALSE;
	for ( i = 2; i < x; i++)
		if (((x % i) == 0) && (i != x)) return FALSE;
	return TRUE;
}