#include <stdio.h>
#include <stdlib.h>

/*
���� ����
���� �� 3��° ������ 2��° ������ ������ �ٲ� �� �����ϴ�.
�̷��� ������ ������ ������ �׸� ������ �׷����ϴ�.

���� ���� ī��(�׸�1)
��6������������������(You have (42) cards.)
��(���� ���� ī��)

��6(���� ���� ī��)�� ��7(�ﰢ��)�� �����ϰ� ��7�� ��6�� �� ������ �ɴϴ�.
���� ���� ī��
��7��6������������������(You have (43) cards.)
��(���� ���� ī��)

��7(���� ���� ī��)�� ��6(�ﰢ��)�� �����ϰ� ��6�� ��7�� �� ������ �ɴϴ�.
���� ���� ī��
��6��7��6������������������(You have (44) cards.)
��(���� ���� ī��)

��6(���� ���� ī��)�� ���� �� ���� remove�մϴ�.(���ſ� �ٸ�. ���Ŵ� ī�峢�� ¦�� ����)
���� ���� ī��
��7��6������������������(You have (43) cards.)
��(���� ���� ī��)

��7(���� ���� ī��)�� ���� �� ���� remove�մϴ�.(���ſ� �ٸ�. ���Ŵ� ī�峢�� ¦�� ����)
���� ���� ī��(�׸�3)
��6������������������(You have (42) cards.)
��(���� ���� ī��)

��6(���� ���� ī��)�� ���� �� ���� remove�մϴ�.(���ſ� �ٸ�. ���Ŵ� ī�峢�� ¦�� ����)
���� ���� ī��(�׸�3)(�׸�2)
��K����������������(You have (41) cards.)
��(���� ���� ī��)

��K(���� ���� ī��)�� ��Q(�ﰢ��)�� �����ϰ� ��K�� ��Q�� �� ������ �ɴϴ�.
���� ���� ī��(�׸�2)
��Q��K����������������(You have (42) cards.)
��(���� ���� ī��)

�̶� ��7�� ���µǰ� �ﰢ�� ������ ��7, ��9, ��4�� ���Դϴ�.
���� ���� ī��(�׸�2)
��Q��K����������������(You have (42) cards.)
��(���� ���� ī��)

�̶����� ��Q��K�� ����� ��7, ��9, ��4�� ���� ī�尡 ���� ������ ���� ���� ī�忡�� ��Q��K���� �����ϴ�.
����������������(You have (40) cards.)
��(���� ���� ī��)

�� ������ �ݺ��մϴ�.

//////////////////////////////////////////////////////
���� ����

ī�� ��带 ���� �Ҵ����ݴϴ�.(malloc ���)

ī�带 ó�� ��� �����ϰ� �����ݴϴ�.
�׸��� 10���� ī�带 �ﰢ�� ��� ī�� Ʈ���� �Ҵ����ݴϴ�.
���� ī��� ������� �տ� �ִ� ��ũ�� �������� �ű�ϴ�.

���� �տ� �ִ� 42(�Ǵ� 16)���� ī���� �� ���� top���� Ȯ���� ����ڿ��� �����ݴϴ�.

top�� �ִ� ī��� �ﰢ�� ���� ī�带 �����ϱ�� �����ϸ� �� ���� �ִ� top ī��� �����ǰ� 
�����ϱ�� �� ī�� Ʈ�� ���� �ִ� ī�尡 �� ���� ��ũ�� ������������ �ɴϴ�.

���� ��Ī�Ǵ� ���� ���ٸ� -1�� ���� ��ũ�� ������ pop���ݴϴ�.


*/



#define NUM_SHAPE 2

//MALLOC ����
#define M��LLOC(p, s) \
	if (!((p) = malloc(s))) { \
	printf("Insufficient memory"); \
	exit(EXIT_FAILURE);}




// Card tree : doubly linked list (tree node is created by malloc())
// Hand card : linked stack (top node card is to be played)

typedef struct node_type* node_ptr;
typedef struct node_type {
	int num; // A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K
	int shape; // 0, 1, 2, 3 = {space, heart, clover, diamond} = 2 or 4 sets
	int show; // 0 = hide, 1 = show
	node_ptr llink, rlink;
}Node;

// LinkedListStack : ���� ������ ����Ʈ�� ����
typedef struct LinkedListStack {
	Node* top; // ����Ʈ�� ���� ��� �ּҸ� ����ų ������
	int size; // ����Ʈ�� ��� ������ ������ ����
} LinkedListStack;


// LLS_Stack_Init : ���� ������ ����Ʈ�� �ʱ�ȭ
LinkedListStack* LLS_Stack_Init() {
	LinkedListStack* stack;
	stack = (LinkedListStack*)malloc(sizeof(LinkedListStack));
	stack->top = NULL;
	stack->size = 0;
	return stack;
}

// LLS_Node_Init : ���ÿ� �� ��带 �ʱ�ȭ
Node* LLS_Node_Init(int num, int shape) {
	// ���ο� ����� �޸𸮸� �� ������ �Ҵ�
	Node* newNode = (Node*)malloc(sizeof(Node));
	// ����� ������ �� ������ �Ҵ�
	// ����� num, shape�� num, shape�� �Ҵ�
	newNode->num = num;
	newNode->shape = shape;
	//�⺻������ hide�� �Ҵ�
	newNode->show = 0;
	// ����� �����͸� ����
	newNode->llink = NULL;
	newNode->rlink = NULL;
	return newNode;
}

//next�� �����̴ϱ� rlink, prev�� �����̴ϱ� llink

// LLS_Push : ����Ʈ(����)�� Top���� ���ο� ��带 �߰�
void LLS_Push(LinkedListStack* list, int num, int shape) {
	// ���ο� ��带 ����
	Node* newNode = LLS_Node_Init(num, shape);
	// oldTop : ������ ������(���� ��) ��带 ������ ����
	Node* oldTop;

	// ����Ʈ(����)�� ��尡 ���� ���
	if (list->top == NULL) {
		list->top = newNode;
	}
	// ����Ʈ(����)�� ��尡 �ִ� ���
	else {
		oldTop = list->top;
		oldTop->rlink = newNode;
		newNode->llink = oldTop;
		list->top = newNode;
	}
	// ����Ʈ�� ��� ������ �߰�
	list->size++;
}

// LLS_Pop : ����Ʈ(����)�� Top�� ����
// ī�尡 ��Ī�Ǹ� �����.
void LLS_Pop(LinkedListStack* list) {
	// currentTop : ���� �� ������ Top ��带 ������ ����
	Node* currentTop = list->top;
	// newTop : Top ��尡 ���ŵǰ� ���Ӱ� Top ��尡 �� ����
	Node* newTop;

	// ����Ʈ(����)�� ��尡 �ϳ��� ���� ��� �Լ��� ����
	if (currentTop == NULL) {

		printf("�տ� ���� �ִ� ī�尡 �����ϴ�.\n");
		return;
	}
		
	else {
		newTop = list->top->llink;
		newTop->rlink = NULL;
		list->top = newTop;
	}
	list->size--;
	// ����� �޸𸮸� ����
	free(currentTop);
}


// LLS_Top : ����Ʈ(����)�� Top�� ��ȯ�ϴ� �Լ�. ���� �� ī�带 �����ش�.
Node* LLS_Top(LinkedListStack* list) {
	return list->top;
}


// LLS_Destroy : ����Ʈ(����)�� ��� ���� ����Ʈ�� �޸𸮸� ����
void LLS_Destroy(LinkedListStack* list) {
	Node* delNode = list->top;
	while (delNode != NULL) {
		list->top = list->top->llink;
		free(delNode);
		delNode = list->top;
	}
	free(list);
}

int mark[4][13]; //randomly pick cards



// �迭�� ����Ʈ ���ִ� �Լ� 
void printarr(int* arr, int num)
{
	for (int i = 0; i < num; i++) 
		printf("%d ", arr[i]); 
	printf("\n");
}
// �迭�� ���� �Լ� 
void shuffle(int* arr, int num) {
	srand(time(NULL)); 
	int temp; int rn; 
	for (int i = 0; i < num - 1; i++) {
		rn = rand() % (num - i) + i; // i ���� card_num-1 ���̿� ������ ���� ����  - �迭�� �ε����� ���� ���̴�.
		temp = arr[i]; 
		arr[i] = arr[rn]; 
		arr[rn] = temp;
	}


} int main(void) {


	// stack�̶�� ����Ʈ�� ����. �տ� �� ī�� ����Ʈ�̴�.
	LinkedListStack* stack;
	// �Լ��� ���� ����Ʈ ������ ������ ����
	stack = LLS_Stack_Init();

	// 1���� ��带 Ǫ��
	printf("Push a node\n");
	LLS_Push(stack, 1, 1);
	// stack ����Ʈ top�� �����͸� ���
	printf("top : %d %d\n\n", LLS_Top(stack)->num, LLS_Top(stack)->shape);
	
	// 3���� ��带 Ǫ��
	printf("Push three nodes\n");
	LLS_Push(stack, 2, 1);
	LLS_Push(stack, 3, 1);
	LLS_Push(stack, 4, 1);
	// stack ����Ʈ top�� �����͸� ���
	printf("top : %d %d\n\n", LLS_Top(stack)->num, LLS_Top(stack)->shape);

	// Pop���� �ֻ��� ��� ����
	printf("Pop\n");
	LLS_Pop(stack);
	// stack ����Ʈ top�� �����͸� ���
	printf("top : %d %d\n\n", LLS_Top(stack)->num, LLS_Top(stack)->shape);

	// Pop�� �ι� ����
	printf("Pop two nodes\n");
	LLS_Pop(stack);
	LLS_Pop(stack);
	// stack ����Ʈ top�� �����͸� ���
	printf("top : %d %d\n\n", LLS_Top(stack)->num, LLS_Top(stack)->shape);

	LLS_Destroy(stack);


	//�̴� ���� ī�尡 �̹� ���� �ߺ��� ī������ �ƴ����� �˻��ؾ� �ϱ� ������ ���� ī�尡 0�� ����������� ���ʿ��� ������ ������ ���� �ʾҽ��ϴ�.
	/*int sh, no;
	sh = rand() % NUM_SHAPE; // NUM_SHAPE = 2 or 4, (2 is recommended.)
	no = rand() % 13; // 0 = A, 12 = K
	*/


	return 0;

	/*

	//��ũ���� 1~(NUM_SHAPE*13)�� ���� ��ȣ�� �ٴ´�. �̰� �������� ��� �����͸� �Ҵ����ش�.
	int mark[NUM_SHAPE][13]; //randomly pick cards


	int card_num = 13 * NUM_SHAPE;

	node_ptr *card;
	card = (int*)malloc(sizeof(int) * card_num); // ī���� �迭�� ũ�⸸ŭ �޸� �Ҵ�
	



	int* arr;
	arr = (int*)malloc(sizeof(int) * card_num); // ī���� �迭�� ũ�⸸ŭ �޸� �Ҵ�
	
	for (int i = 0; i < card_num; i++)
		arr[i] = i; // �迭�� 0���� card_num-1 ������ ��ҷ� �ʱ�ȭ 
	shuffle(arr, card_num);
	
	//ī�尡 ���� ������ �������� �Ҵ�
	for (int i = 0; i < NUM_SHAPE; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			mark[i][j] = arr[j + i * 13];
			printf("%d ", mark[i][j]);
		}
	}
	free(arr);

	
	int sh, no;
	sh = rand() % NUM_SHAPE; // NUM_SHAPE = 2 or 4, (2 is recommended.)
	no = rand() % 13; // 0 = A, 12 = K

	if (card[mark[sh][no]]->show == 0)
	{

	}
	


	for (int i = 0; i < 10; i++)
	{
		
	}

	//printarr(arr, card_num);
	return 0;


	*/
	

	//MALLOC(card[i], sizeof(card));


	// �� ��ü�� �ε����ε�? �ε����� ������ �� �϶�� ���̾�. �ֳĸ� �ε����� �� �� �� ���ŵ�. ī�� 52�� �ְ� �迭�� ���� ���Ҹ� �����ϰ� �迭�ϸ� ����.
	// �׷��� ī�带 �ְ� ��ũ���ٰ� �ε����� �Ҵ������ڰ�? �ٵ� ��ũ�� ���� ��Ʈ�ݾ�. �̰ɷ� ���̵�, � �϶�� ���̾�?
	//���ڽ��� �����ؾ� �Ѵ�. ���? ī���� ����ü��.
	// ī�� ����ü�� �̿��ؼ� ���Ÿ�Կ� �־�����.



}

//
//
//#include <stdio.h>
//#include <stdlib.h>	//EXIT_FAILURE
////#include <cstddef>	//NULL �̰� ���� ��������.
//
////������ ��ü�� ���
//#define TO_STRING(a) #a
//
//
////MALLOC ����
//#define M��LLOC(p, s) \
//	if (!((p) = malloc(s))) { \
//	printf("Insufficient memory"); \
//	exit(EXIT_FAILURE);}
//
////�������� �����κ��� ��� ��ġ ���� ��ũ��
//#define CHECK(p) if (p == first) str = "first";\
//else if (p == second) str = "secon";\
//else if (p == third) str = "third";\
//else str = "NULL";\
//
////����Ʈ ��� ��ũ��
//#define PRINT(p) print = p;\
//printf("%s", TO_STRING(p));\
//i = 1;\
///*ù ����� �ּҰ��� ����ϱ� ���� ������*/\
//temp = print;\
//printf("\taddr\t\tdata\tlink\n");\
//if(print){\
//	/*ù ��带 ����Ѵ�.*/\
//	CHECK(print)\
//	printf("n_%d\t%p(%s)\t", i, print, str);\
//	printf("%d\t", print->data);\
//	CHECK(print->link)\
//	printf("%p(%s)\n", print->link, str);\
//	i++;\
//	print = print->link;\
///* ù ����� �ּҿ� ������ ������ ���. circular�̱� ���� */ \
//for (; print != temp; print = print->link) {\
//	CHECK(print)\
//	printf("n_%d\t%p(%s)\t", i, print, str);\
//	printf("%d\t", print->data);\
//	CHECK(print->link)\
//	printf("%p(%s)\n", print->link, str);\
//	i++;\
//}}\
//else printf("\tNULL\n")
//
////��� 1�� ��� ��ũ��
//#define PRINT1(p) print = p;\
//printf("%s", TO_STRING(p));\
//printf("\taddr\t\tdata\tlink\n");\
//	CHECK(print)\
//	printf("\t%p(%s)\t", print, str);\
//	printf("%d\t", print->data);\
//	CHECK(print->link)\
//	printf("%p(%s)\n", print->link, str);
//
//
//typedef struct list_node* list_pointer;
//typedef struct list_node {
//	int data;
//	list_pointer link;
//};
//
////���� �����Ϳ� ����Ʈ�� ������ 2��(print, temp)
//list_pointer first, second, third, print, temp;
////string ���
//char* str;
//
////for������ node�� ���� ����� ����
//int i;
////����Ʈ�� ��� ������ ���� ��� ��� ���� ��¿�
//int node_count;
//
////cinvert �Լ�
//list_pointer cinvert(list_pointer lead)
//{//lead�� ����Ű�� �ִ� ����Ʈ�� �������� �����.
//	list_pointer middle, trail;
//	middle = NULL;
//	trail = NULL;	//������ ���ϵ� �������̴�.
//	int count = 1;
//	while (lead)	//lead�� null�� �� ������ ����. lead�� ó�� ��带 �ް� ����� ���� null�� �ް� �ȴ�.
//	{
//		/*
//		1. lead�� ����Ʈ�� ù ������ ������_������ ���������� �����Ѵ�.
//			1.1. ó�� while���� middle->link = trail;�� ���Ͽ� ����Ʈ�� ���� ��� first->link = null�� �ȴ�.
//			1.2. ������_���->link = first�̴�. ���� ���������� �湮�ϴ� ���� first�� �ȴ�.(���������� �湮�ϴ� ��� != ������_���)
//		2. trail�� ���ݱ��� ������ middle�� �޴´�.
//		3. middle�� lead, �� ���� ���, ������ ��带 �޴´�.
//		4. middle->link�� trail�� �־� ������ ����� �ڿ� �������� ������ middle�� �ٿ� ������ ����Ʈ�� �����.
//		5. ���������� lead�� null�� �Ǹ� while ���� ������, while ������ ������ ����, 1.2.�� ���Ͽ� middle�� first ��带 ����Ű�� �ȴ�.
//			5.1. �츮�� ������_����� �ּҰ��� ���� �ް� �ʹ�.
//			5.2. first(=middle)->link = ������_����̴�.
//			5.3. middle->link = trail�̴�.
//			5.4. ���� trail = ������_����̴�.
//			5.5. ���� trail�� ���� ������ ������_����� �ּҰ��� ���� �ް� �ȴ�.
//		6. �̶�, first���� �����ؼ� ������_��带 �湮�ϰ� �ٽ� first�� �湮�Ѵ�. ���� while ���� n+1�� ����ȴ�.
//			6.1. lead == NULL�� �� while ���� ������� �ʴ´�. �̶�, lead = trail = NULL�̹Ƿ� trail�� �����ص� ������ ����� ���´�.
//		7. 5.5., 6.1.�� ���Ͽ� trail�� �����Ѵ�.
//		*/
//		trail = middle;	//trail�� middle�� �ִ´�. ó������ null�� ����.
//		middle = lead;	//middle�� lead�� �ִ´�. ó������ ���� �������� �ּҰ� ����. 1���� ���� 0���� �� ���� �� ����.
//		lead = lead->link;	//lead�� ���� ��带 ����Ų��. 1.1., 1.2.�� ���Ͽ� �������� null�� ����Ű�� �ǰ� �̶� while ���� ����������.
//		middle->link = trail;	//middle�� link, �� �ڿ� �� �͵鿡 trail�� �ִ´�.
//
//		printf("----------------------�䱸���� 3��----------------------\n");
//		printf("**************while�� %d�� ° ����**************\n", count);
//		CHECK(trail);
//		printf("trail--addr: %p(%s)\n", trail, str);
//		CHECK(middle);
//		printf("middle-addr: %p(%s)\n", middle, str);
//		CHECK(lead);
//		printf("lead---addr: %p(%s)\n", lead, str);
//		switch (node_count)
//		{
//		case 2:
//			PRINT1(first);
//			PRINT1(second);
//			break;
//		case 1:
//			PRINT1(third);
//			break;
//		}
//
//
//		printf("----------------------�䱸���� 3��----------------------\n");
//		count++;
//	}
//	//7. 5.5., 6.1.�� ���Ͽ� trail�� �����Ѵ�.
//	return trail;
//}
//
//int main() {
//	//����Ʈ ���� �� �Ҵ�
//	list_pointer L2, L2_cinv, L1, L1_cinv, L0, L0_cinv;
//	//��忡 �޸� �Ҵ�
//	M��LLOC(first, sizeof(*first));
//	M��LLOC(second, sizeof(*second));
//	M��LLOC(third, sizeof(*third));
//
//	//�� �Ҵ�
//	first->data = 10;
//	first->link = second;
//	second->data = 20;
//	second->link = first;
//
//	third->data = 30;
//	third->link = third;
//
//	//������ Ȯ�ο� ù ���
//	PRINT1(first);
//	PRINT1(second);
//	PRINT1(third);
//
//	//L2�� ù ��� �Ҵ�
//	L2 = first;
//	//ó�� L2�� �޾Ƽ� ��� �� L2�� ���� ����� �ּҰ����� �ٲ۴�.
//	//first�� second�� ������ ���� �ʴ´�.
//	printf("----------------------�䱸���� 1��----------------------\n");
//	node_count = 2;
//	PRINT(L2);
//	printf("----------------------�䱸���� 1��----------------------\n");
//
//	//L2�� first�� cinvert�ϰ� �Ҵ�
//	printf("----------------------�䱸���� 2��----------------------\n");
//	L2_cinv = cinvert(L2);
//	printf("----------------------�䱸���� 2��----------------------\n");
//
//	printf("----------------------�䱸���� 4��----------------------\n");
//	PRINT(L2_cinv);
//	printf("----------------------�䱸���� 4��----------------------\n");
//
//
//	printf("----------------------�䱸���� 5��----------------------\n");
//	node_count = 1;
//	//��� 1��¥�� second�� L1�� �Ҵ�.
//	L1 = third;
//	PRINT(L1);
//	L1_cinv = cinvert(third);
//	PRINT(L1_cinv);
//	printf("----------------------�䱸���� 5��----------------------\n");
//
//	printf("----------------------�䱸���� 6��----------------------\n");
//	node_count = 0;
//	L0 = NULL;
//	PRINT(L0);
//	L0_cinv = cinvert(L0);
//	PRINT(L0_cinv);
//	printf("----------------------�䱸���� 6��----------------------\n");
//	return 0;
//}
