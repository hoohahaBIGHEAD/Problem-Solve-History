/* �� ���α׷��� �������� �Է¹޾� ���� ������ ���ϴ� ���α׷��̴�. */

/* ���Ժ� */
#include <stdio.h>	// printf()�� scanf_s()�� ����ϱ� ���� ��� ���� ����

// ���� ����� ���� ���ڵ��� �����Ѵ�.
//#define�� 
// ������ �� �ش� ����� ���� ���ڴ� #define
#define IN "���� �������� 100�Դϴ�. \n"
#define PI 3.1415926535
#define AREA(X) (PI*(X)*(X))
#define OUT printf("���� ������ ���ϰ� ���α׷��� �����մϴ�. \n")

void main() {
	printf("%s \n", IN);
	printf("���� ������ %10.5f�Դϴ�. \n\n", AREA(100));
	OUT;
}