/* 이 프로그램은 반지름을 입력받아 원의 면적을 구하는 프로그램이다. */

/* 도입부 */
#include <stdio.h>	// printf()와 scanf_s()를 사용하기 위한 헤더 파일 포함

// 각종 사용자 지정 문자들을 정의한다.
//#define은 
// 컴파일 시 해당 사용자 지정 문자는 #define
#define IN "원의 반지름은 100입니다. \n"
#define PI 3.1415926535
#define AREA(X) (PI*(X)*(X))
#define OUT printf("원의 면적을 구하고 프로그램을 종료합니다. \n")

void main() {
	printf("%s \n", IN);
	printf("원의 면적은 %10.5f입니다. \n\n", AREA(100));
	OUT;
}
