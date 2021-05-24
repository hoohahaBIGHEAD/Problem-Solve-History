/* 이 프로그램은 윗변, 밑변, 높이를 키보드로 입력받아 사다리꼴의 면적을 소수점 이하 세 자리까지 출력하는 프로그램이다. */

/* 도입부 */
#include <stdio.h>

int main() {

	// 정수를 저장하는 변수 선언
	int upper_side;
	int lower_side;
	int height;

	printf("사다리꼴의 넓이를 구하기 위해 윗변, 밑변, 높이를 입력하시오.\n");

	// 각각의 변수를 입력 받는다.
	printf("윗변 : ");
	scanf_s("%d", &upper_side);
	printf("밑변 : ");
	scanf_s("%d", &lower_side);
	printf("높이 : ");
	scanf_s("%d", &height);

	// 각각의 변수의 출력과 함께 사다리꼴의 면적을 출력한다.
	// (float)((upper_side + lower_side) *(height)) / (2) 설명
	// (float) :: 정수형 변수를 실수로 변환시킨다.
	// / (2) :: 실수로 변환 후 2로 나눠준다. 변환 전 2로 나누면 소수점 이하가 버려질 수 있다.
	// %.3f :: 소수점 세 자리까지 출력한다. 해당 수는 반올림된다.
	printf("윗변(%d), 밑변(%d), 높이(%d)를 가지는 사다리꼴의 면적은 %.3f입니다.", upper_side, lower_side, height, (float)((upper_side + lower_side) *(height)) / (2));
}
