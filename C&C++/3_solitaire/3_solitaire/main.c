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

���(ī��)�� ���� �Ҵ����ݴϴ�.(malloc ���)

ī�带 ó�� ��� �����ϰ� �����ݴϴ�.
�׸��� 10���� ī�带 �ﰢ�� ��� ī�� Ʈ���� �Ҵ����ݴϴ�.
���� ī��� ������� �տ� �ִ� ��ũ�� �������� �ű�ϴ�.

���� �տ� �ִ� 42(�Ǵ� 16)���� ī���� �� ���� top���� Ȯ���� ����ڿ��� �����ݴϴ�.

top�� �ִ� ī��� �ﰢ�� ���� ī�带 �����ϱ�� �����ϸ� �� ���� �ִ� top ī��� �����ǰ� 
�����ϱ�� �� ī�� Ʈ�� ���� �ִ� ī�尡 �� ���� ��ũ�� ������������ �ɴϴ�.

���� ��Ī�Ǵ� ���� ���ٸ� -1�� ���� ��ũ�� ������ pop���ݴϴ�.


(����)�Ʒ� �ڵ�� �̹� ���� �ߺ��� ī������ �ƴ����� �˻��ؾ� �ϱ� ������ ���� ī�尡 0�� ����������� ���ʿ��� ������ ������ ���� �ʾҽ��ϴ�.
	int mark[4][13]; //randomly pick cards
	int sh, no;
	sh = rand() % NUM_SHAPE; // NUM_SHAPE = 2 or 4, (2 is recommended.)
	no = rand() % 13; // 0 = A, 12 = K
*/


//MALLOC ����
#define M��LLOC(p, s) \
	if (!((p) = malloc(s))) { \
	printf("Insufficient memory"); \
	exit(EXIT_FAILURE);}

#define NUM_SHAPE 2

// Card tree : doubly linked list (tree node is created by malloc())
// Hand card : linked hand_stack (top node card is to be played)








////////////////���(ī��) ����////////////////////

typedef struct node_type* node_ptr;
typedef struct node_type {
	int num; // A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K
	int shape; // 0, 1, 2, 3 = {space, heart, clover, diamond} = 2 or 4 sets
	int show; // 0 = hide, 1 = show
	node_ptr llink, rlink;
}card;

////////////////���(ī��) ����////////////////////



////////////////���� �� �����Լ� ����////////////////////

// LinkedListStack : ���� ������ ����Ʈ�� ����
typedef struct LinkedListStack {
	card* top; // ����Ʈ�� ž ���(ī��) �ּҸ� ����ų ������
	int size; // ����Ʈ�� ���(ī��) ������ ������ ����
} LinkedListStack;

// LLS_Stack_Init : ���� ������ ����Ʈ�� �ʱ�ȭ
LinkedListStack* LLS_Stack_Init() {
	LinkedListStack* hand_stack;
	hand_stack = (LinkedListStack*)malloc(sizeof(LinkedListStack));
	hand_stack->top = NULL;
	hand_stack->size = 0;
	return hand_stack;
}

// LLS_Node_Init : ���ÿ� �� ���(ī��)�� �ʱ�ȭ
card* LLS_Node_Init(int num, int shape) {
	// ���ο� ���(ī��)�� �޸𸮸� �� ������ �Ҵ�
	card* new_top = (card*)malloc(sizeof(card));
	// ���(ī��)�� ������ �� ������ �Ҵ�
	// ���(ī��)�� card_num, shape�� card_num, shape�� �Ҵ�
	new_top->num = num;
	new_top->shape = shape;
	// ���(ī��)�� show�� �⺻������ hide(0)�� �Ҵ�
	new_top->show = 0;
	// ���(ī��)�� �����͸� ����
	new_top->llink = NULL;
	new_top->rlink = NULL;
	return new_top;
}

// LLS_Push : ����Ʈ(����)�� Top���� ���ο� ���(ī��)�� �߰�
void LLS_Push(LinkedListStack* list, int num, int shape) {
	// top�� ���� ���ο� ���(ī��)�� ����
	card* new_top = LLS_Node_Init(num, shape);
	// old_top : ������ ������(���� ��) ���(ī��)�� ������ ����
	card* old_top;

	// ����Ʈ(����)�� ���(ī��)�� ���� ���
	if (list->top == NULL) {
		//���� top�� new_top�� �Ҵ��Ѵ�.
		list->top = new_top;
	}
	// ����Ʈ(����)�� ���(ī��)�� �ִ� ���
	else {
		//���� ����Ʈ�� top�� old_top�� �Ҵ��Ѵ�.
		old_top = list->top;
		//old_top�� ��� ������(rlink)�� new_top�� ����Ű���� �Ѵ�.
		old_top->rlink = new_top;
		//new_top�� �ϴ� ������(llink)�� old_top�� ����Ű���� �Ѵ�.
		new_top->llink = old_top;
		//���� ����Ʈ�� top�� new_top�� �Ҵ��Ѵ�.
		list->top = new_top;
	}
	// ����Ʈ�� ���(ī��) ������ �߰�
	list->size++;
}

// LLS_Pop : ����Ʈ(����)�� Top�� ����
// -1�� �����ϸ� remove�Ѵ�.
void LLS_Pop(LinkedListStack* list) {
	// old_top : ���� �� ������ Top ���(ī��)�� ������ ���(ī��)
	card* old_top = list->top;
	// new_top : old_top ���(ī��)�� ���ŵǰ� ���Ӱ� Top ���(ī��)�� �� ���(ī��). old_top->llink�̴�.
	card* new_top;

	// ����Ʈ(����)�� ���(ī��)�� �ϳ��� ���� ��� �Լ��� ����
	if (old_top == NULL) {
		printf("�տ� ���� �ִ� ī�尡 �����ϴ�.\n");
		return;
	}
	// ����Ʈ(����)�� ���(ī��)�� �ִ� ���
	else {
		// old_top->llink �� ���(ī��)�� new_top �� �Ҵ��Ѵ�.
		// ���� ���ÿ� 1���� ���� ���¶�� NULL�� �Ҵ�ȴ�.
		new_top = old_top->llink;
		// new_top�� ��� �����Ϳ� NULL�� �Ҵ��Ѵ�.
		new_top->rlink = NULL;
		// list->top �� new_top�� �Ҵ��Ѵ�.
		list->top = new_top;
	}
	//����Ʈ�� ����� 1 ����. list->size == 0�̸� ���� ����
	list->size--;
	// old_top ���(ī��)�� �޸𸮸� ����
	free(old_top);
}

// LLS_Top : ����Ʈ(����)�� Top�� ��ȯ�ϴ� �Լ�. ���� ���� ī�带 �����ش�.
card* LLS_Top(LinkedListStack* list) {
	return list->top;
}

// LLS_Destroy : ����Ʈ(����)�� ��� ���(ī��)�� ����Ʈ�� �޸𸮸� ����
void LLS_Destroy(LinkedListStack* list) {
	card* delNode = list->top;
	while (delNode != NULL) {
		list->top = list->top->llink;
		free(delNode);
		delNode = list->top;
	}
	free(list);
}
////////////////���� �� �����Լ� ����////////////////////


////////////////ī�� ���� �Լ� ����////////////////////
// �迭�� ���� �Լ� 
void shuffle(int* card_key, int card_num) {
	//srand �� ȣ���� �� ���޹޴� ���ڸ� ������� �ؼ� ������ �ʱ�ȭ �����ִ� ������ �Ѵ�.
	//rand �� srand �� ���� ������ ���� �������� ������ ������ �ִ� ������ �Ѵ�.
	srand(time(NULL)); 
	int temp;
	int random_index; 
	for (int i = 0; i < card_num - 1; i++) {
		random_index = rand() % (card_num - i) + i; // i ���� card_num-1 ���̿� ������ ���� ����  - �迭�� �ε����� ���� ���̴�.
		temp = card_key[i]; 
		card_key[i] = card_key[random_index]; 
		card_key[random_index] = temp;
	}
////////////////ī�� ���� �Լ� ����////////////////////

} int main(void) {

	//�� ī��� 0~(13*NUM_SHAPE-1)������ ����Ű�� �Ҵ�ȴ�. �ߺ� ����
	//�̷��� �ϸ� 0~12�� ��1~��12, 13~25�� ��0~12, 26~38�� ��0~12, 39~51�� ��0~12�� �Ҵ�ȴ�.
	//�� ī��� 0~12������ card_num, 0~(NUM_SHAPE-1)������ shape�� �Ҵ�ȴ�.
	//�� ī���� num�� ���Ϸ��� ����Ű % 13��
	//�� ī���� shape�� ���Ϸ��� ����Ű / 13 �� �ϸ� �ȴ�.

	//��ũ���� 1~(NUM_SHAPE*13)�� ���� ��ȣ�� �ٴ´�. �̰� �������� ��� ī�带 �����ش�.
	int card_num = 13 * NUM_SHAPE;

	// hand_stack �̶�� ����Ʈ�� ����. �տ� �� ī�� ����Ʈ�̴�.
	LinkedListStack* hand_stack;
	// �Լ��� ���� ����Ʈ ������ ������ ����
	hand_stack = LLS_Stack_Init();

	node_ptr *card_array;
	card_array = (int*)malloc(sizeof(card) * card_num); // ī���� ����ŭ ���(ī��) �޸� �Ҵ�

	int* card_key;
	card_key = (int*)malloc(sizeof(int) * card_num); // ī���� ����ŭ �迭 �޸� �Ҵ�
	
	for (int i = 0; i < card_num; i++) {
		card_key[i] = i; // �迭�� 0���� card_num-1 ������ ��ҷ� �ʱ�ȭ 
		card_array[i] = LLS_Node_Init(0, 0);	// �� ī����� �ʱ�ȭ(���� ������ �ʱ�ȭ���� ���� �� ������ ���)
	}
		


	// ī���� ������ �����ش�.
	shuffle(card_key, card_num);
	
	// ���� card_key �� �������� ���(ī��)�� ī�带 �Ҵ��Ѵ�. �̷��� ������ �迭�� ī�尡 �����ȴ�.
	for (int i = 0; i < card_num; i++)
	{
		card_array[i]->num = card_key[i] % 13;
		card_array[i]->shape = card_key[i] / 13;
	}

	// ���̻� �ʿ� ���� card_key �� �Ҵ�� �޸𸮸� �����Ѵ�.
	free(card_key);

	// ī�� Ʈ���� �����Ѵ�.
	for (int i = 0; i < 10; i++)
	{
		
	}

	// ������ ī�带 hand_stack �� push �Ѵ�.
	for (int i = 10; i < card_num; i++)
	{
		LLS_Push(hand_stack, card_array[i]->num, card_array[i]->shape);
		printf("top : %d %d\n\n", LLS_Top(hand_stack)->num, LLS_Top(hand_stack)->shape);
	}

	//printarr(card_key, card_num);
	return 0;


	// 1���� ���(ī��)�� Ǫ��
	printf("Push a node\n");
	LLS_Push(hand_stack, 1, 1);
	// hand_stack ����Ʈ top�� �����͸� ���
	printf("top : %d %d\n\n", LLS_Top(hand_stack)->num, LLS_Top(hand_stack)->shape);

	// 3���� ���(ī��)�� Ǫ��
	printf("Push three nodes\n");
	LLS_Push(hand_stack, 2, 1);
	LLS_Push(hand_stack, 3, 1);
	LLS_Push(hand_stack, 4, 1);
	// hand_stack ����Ʈ top�� �����͸� ���
	printf("top : %d %d\n\n", LLS_Top(hand_stack)->num, LLS_Top(hand_stack)->shape);

	// Pop���� �ֻ��� ���(ī��) ����
	printf("Pop\n");
	LLS_Pop(hand_stack);
	// hand_stack ����Ʈ top�� �����͸� ���
	printf("top : %d %d\n\n", LLS_Top(hand_stack)->num, LLS_Top(hand_stack)->shape);

	// Pop�� �ι� ����
	printf("Pop two nodes\n");
	LLS_Pop(hand_stack);
	LLS_Pop(hand_stack);
	// hand_stack ����Ʈ top�� �����͸� ���
	printf("top : %d %d\n\n", LLS_Top(hand_stack)->num, LLS_Top(hand_stack)->shape);

	LLS_Destroy(hand_stack);

	//MALLOC(card[i], sizeof(card));


	// �� ��ü�� �ε����ε�? �ε����� ������ �� �϶�� ���̾�. �ֳĸ� �ε����� �� �� �� ���ŵ�. ī�� 52�� �ְ� �迭�� ���� ���Ҹ� �����ϰ� �迭�ϸ� ����.
	// �׷��� ī�带 �ְ� ��ũ���ٰ� �ε����� �Ҵ������ڰ�? �ٵ� ��ũ�� ���� ��Ʈ�ݾ�. �̰ɷ� ���̵�, � �϶�� ���̾�?
	//���ڽ��� �����ؾ� �Ѵ�. ���? ī���� ����ü��.
	// ī�� ����ü�� �̿��ؼ� ���(ī��)Ÿ�Կ� �־�����.



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
////�������� �����κ��� ���(ī��) ��ġ ���� ��ũ��
//#define CHECK(p) if (p == first) str = "first";\
//else if (p == second) str = "secon";\
//else if (p == third) str = "third";\
//else str = "NULL";\
//
////����Ʈ ��� ��ũ��
//#define PRINT(p) print = p;\
//printf("%s", TO_STRING(p));\
//i = 1;\
///*ù ���(ī��)�� �ּҰ��� ����ϱ� ���� ������*/\
//temp = print;\
//printf("\taddr\t\tdata\tlink\n");\
//if(print){\
//	/*ù ���(ī��)�� ����Ѵ�.*/\
//	CHECK(print)\
//	printf("n_%d\t%p(%s)\t", i, print, str);\
//	printf("%d\t", print->data);\
//	CHECK(print->link)\
//	printf("%p(%s)\n", print->link, str);\
//	i++;\
//	print = print->link;\
///* ù ���(ī��)�� �ּҿ� ������ ������ ���. circular�̱� ���� */ \
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
////���(ī��) 1�� ��� ��ũ��
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
////���(ī��)�� �����Ϳ� ����Ʈ�� ������ 2��(print, temp)
//list_pointer first, second, third, print, temp;
////string ���
//char* str;
//
////for������ node�� ���� ����� ����
//int i;
////����Ʈ�� ���(ī��) ������ ���� ��� ���(ī��) ���� ��¿�
//int node_count;
//
////cinvert �Լ�
//list_pointer cinvert(list_pointer lead)
//{//lead�� ����Ű�� �ִ� ����Ʈ�� �������� �����.
//	list_pointer middle, trail;
//	middle = NULL;
//	trail = NULL;	//������ ���ϵ� �������̴�.
//	int count = 1;
//	while (lead)	//lead�� null�� �� ������ ����. lead�� ó�� ���(ī��)�� �ް� ���(ī��)�� ���� null�� �ް� �ȴ�.
//	{
//		/*
//		1. lead�� ����Ʈ�� ù ���(ī��)���� ������_���(ī��)���� ���������� �����Ѵ�.
//			1.1. ó�� while���� middle->link = trail;�� ���Ͽ� ����Ʈ�� ���� ���(ī��) first->link = null�� �ȴ�.
//			1.2. ������_���(ī��)->link = first�̴�. ���� ���������� �湮�ϴ� ���(ī��)�� first�� �ȴ�.(���������� �湮�ϴ� ���(ī��) != ������_���(ī��))
//		2. trail�� ���ݱ��� ������ middle�� �޴´�.
//		3. middle�� lead, �� ���� ���(ī��), ������ ���(ī��)�� �޴´�.
//		4. middle->link�� trail�� �־� ������ ���(ī��)�� �ڿ� �������� ������ middle�� �ٿ� ������ ����Ʈ�� �����.
//		5. ���������� lead�� null�� �Ǹ� while ���� ������, while ������ ������ ����, 1.2.�� ���Ͽ� middle�� first ���(ī��)�� ����Ű�� �ȴ�.
//			5.1. �츮�� ������_���(ī��)�� �ּҰ��� ���� �ް� �ʹ�.
//			5.2. first(=middle)->link = ������_���(ī��)�̴�.
//			5.3. middle->link = trail�̴�.
//			5.4. ���� trail = ������_���(ī��)�̴�.
//			5.5. ���� trail�� ���� ������ ������_���(ī��)�� �ּҰ��� ���� �ް� �ȴ�.
//		6. �̶�, first���� �����ؼ� ������_���(ī��)�� �湮�ϰ� �ٽ� first�� �湮�Ѵ�. ���� while ���� n+1�� ����ȴ�.
//			6.1. lead == NULL�� �� while ���� ������� �ʴ´�. �̶�, lead = trail = NULL�̹Ƿ� trail�� �����ص� ������ ����� ���´�.
//		7. 5.5., 6.1.�� ���Ͽ� trail�� �����Ѵ�.
//		*/
//		trail = middle;	//trail�� middle�� �ִ´�. ó������ null�� ����.
//		middle = lead;	//middle�� lead�� �ִ´�. ó������ ���� �������� �ּҰ� ����. 1���� ���� 0���� �� ���� �� ����.
//		lead = lead->link;	//lead�� ���� ���(ī��)�� ����Ų��. 1.1., 1.2.�� ���Ͽ� �������� null�� ����Ű�� �ǰ� �̶� while ���� ����������.
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
//	//���(ī��)�� �޸� �Ҵ�
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
//	//L2�� ù ���(ī��) �Ҵ�
//	L2 = first;
//	//ó�� L2�� �޾Ƽ� ��� �� L2�� ���� ���(ī��)�� �ּҰ����� �ٲ۴�.
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
//	//���(ī��) 1��¥�� second�� L1�� �Ҵ�.
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
