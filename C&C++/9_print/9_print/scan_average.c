/* 이 프로그램은 두 정수를 키보드로 입력받아 평균값을 정수로 구한 후 부호를 바꾸어 출력하는 프로그램이다. */

/* 도입부 */
#include <stdio.h>

int main() {

	// 정수를 저장하는 변수 선언
	int x;
	int y;

	printf("2개의 정수값을 입력하시오\n");
	
	// 각각의 변수를 입력 받는다.
	printf("정수 x : ");
	scanf_s("%d", &x);
	printf("정수 y : ");
	scanf_s("%d", &y);

	// 각각의 변수의 출력과 함께 평균값에 부호를 반전한 값을 정수형으로 출력한다.
	// 정수형으로 출력하기 때문에 소수점 아래는 버림이 발생한다.
	printf("x(%d)와 y(%d)의 평균값에 부호를 반전한 값은 %d입니다.", x, y, (x+y)*(-1)/(2));
}
