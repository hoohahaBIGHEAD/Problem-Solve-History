/* �� ���α׷��� �� ���� Ű����� �Է¹޾� ���� ����� ����ϴ� ���α׷��̴�. */

/* ���Ժ� */

#include <stdio.h>	// printf()�� scanf_s()�� ����ϱ� ���� ��� ���� ����
#pragma warning(disable:4996)	// �������� �ʴ� �Լ� ��뿡 ���� ��� �޽��� ����

int a, b, c;	// ������ �����ϴ� ���� ����
int product(int x, int y);	// ����� �Լ� ����

void main() {
	/* ù ��° ���� �Է� */
	printf("Enter a number between 1 and 100 : ");
	scanf_s("%d", &a);	// scanf�� ���� ������ scanf_s�� ��� �Ѵ�.
	/* �� ��° ���� �Է� */
	printf("Enter another number between 1 and 100 : ");
	scanf_s("%d", &b);	// scanf�� ���� ������ scanf_s�� ��� �Ѵ�.
	/* �Լ� ȣ�⿡ ���� �� ���� ���ϰ� ����� ��� */
	c = product(a, b);	//����� �Լ��� ȣ���Ѵ�.
	printf("%d * %d = %d \n", a, b, c);
}


/* �� ���� ���� ����Ͽ� �����ִ� ����� �Լ� */
int product(int x, int y)
{
	return (x * y);
}
