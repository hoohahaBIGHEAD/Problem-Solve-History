/* �� ���α׷��� �ݾ��� Ű����� �Է¹޾� �ش� �ݾ��� 500��, 100��,  50��, 10��¥��  �������� ��ȯ�� �ִ� ���α׷��̴�. */

/* ���Ժ� */

#include <stdio.h>	// printf()�� scanf_s()�� ����ϱ� ���� ��� ���� ����
#pragma warning(disable:4996)	// �������� �ʴ� �Լ� ��뿡 ���� ��� �޽��� ����

void main() {
	int in_money, coin_500, coin_100, coin_50, coin_10;
	printf(" �������� ��ȯ�� �ݾ���? ");
	scanf_s("%d", &in_money);	// scanf�� ���� ������ scanf_s�� ��� �Ѵ�.
	
	coin_500 = in_money / 500;	// ������ in_money�� 500���� ������ 500�� �� �����⿡ 500���� ������ �� �� �ִ�.
	in_money = in_money % 500;	// ������ in_money�� ��ⷯ 500�� ���ϸ� 500���� ���� �������� �����⿡ 500�� �̸��� ���� �� �� �ִ�. �̴� �Ʒ��� ���꿡 �����ϰ� ����ȴ�.
	coin_100 = in_money / 100;
	in_money = in_money % 100;
	coin_50 = in_money / 50;
	in_money = in_money % 50;
	coin_10 = in_money / 10;
	in_money = in_money % 10;

	//����� ���� ����Ѵ�.
	printf("\n ���� ��¥�� ==> %d �� \n", coin_500);
	printf(" �� ��¥��   ==> %d �� \n", coin_100);
	printf(" ���� ��¥�� ==> %d �� \n", coin_50);
	printf(" �� ��¥��   ==> %d �� \n", coin_10);
	printf(" �ٲ��� ���� �ܵ� ==> %d �� \n", in_money);

}
