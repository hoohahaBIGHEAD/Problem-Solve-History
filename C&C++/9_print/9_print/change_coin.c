/* 이 프로그램은 금액을 키보드로 입력받아 해당 금액을 500원, 100원,  50원, 10원짜리  동전으로 교환해 주는 프로그램이다. */

/* 도입부 */

#include <stdio.h>	// printf()와 scanf_s()를 사용하기 위한 헤더 파일 포함
#pragma warning(disable:4996)	// 권장하지 않는 함수 사용에 대한 경고 메시지 무시

void main() {
	int in_money, coin_500, coin_100, coin_50, coin_10;
	printf(" 동전으로 교환할 금액은? ");
	scanf_s("%d", &in_money);	// scanf는 보안 문제로 scanf_s를 써야 한다.
	
	coin_500 = in_money / 500;	// 정수형 in_money를 500으로 나누면 500의 몫만 나오기에 500원의 갯수를 알 수 있다.
	in_money = in_money % 500;	// 정수형 in_money를 모듈러 500을 취하면 500으로 나눈 나머지가 나오기에 500원 미만의 돈을 알 수 있다. 이는 아래의 연산에 동일하게 적용된다.
	coin_100 = in_money / 100;
	in_money = in_money % 100;
	coin_50 = in_money / 50;
	in_money = in_money % 50;
	coin_10 = in_money / 10;
	in_money = in_money % 10;

	//연산된 값을 출력한다.
	printf("\n 오백 원짜리 ==> %d 개 \n", coin_500);
	printf(" 백 원짜리   ==> %d 개 \n", coin_100);
	printf(" 오십 원짜리 ==> %d 개 \n", coin_50);
	printf(" 십 원짜리   ==> %d 개 \n", coin_10);
	printf(" 바꾸지 못한 잔돈 ==> %d 원 \n", in_money);

}
