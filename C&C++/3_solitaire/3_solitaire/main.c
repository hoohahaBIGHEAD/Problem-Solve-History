#include <stdio.h>
#include <stdlib.h>

#define LINE 4
#define NUM_SHAPE 4

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
void show_shape_num(node_ptr node);
void show_board();


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
		//old_top�� �������̶�� new_top���� NULL�� �Ҵ�ȴ�. �̶� new_top->rlink�� ������ ����.
		if (new_top != NULL) {
			// new_top�� ��� �����Ϳ� NULL�� �Ҵ��Ѵ�.
			new_top->rlink = NULL;
		}
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
} 
////////////////ī�� ���� �Լ� ����////////////////////


node_ptr* card_array;

// hand_stack �̶�� ����Ʈ�� ����. �տ� �� ī�� ����Ʈ�̴�.
LinkedListStack* hand_stack;
int index_position = 0;
int remain = 10;

int main(void) {

	//�� ī��� 0~(13*NUM_SHAPE-1)������ ����Ű�� �Ҵ�ȴ�. �ߺ� ����
	//�̷��� �ϸ� 0~12�� ��1~��12, 13~25�� ��0~12, 26~38�� ��0~12, 39~51�� ��0~12�� �Ҵ�ȴ�.
	//�� ī��� 0~12������ card_num, 0~(NUM_SHAPE-1)������ shape�� �Ҵ�ȴ�.
	//�� ī���� num�� ���Ϸ��� ����Ű % 13��
	//�� ī���� shape�� ���Ϸ��� ����Ű / 13 �� �ϸ� �ȴ�.

	//��ũ���� 1~(NUM_SHAPE*13)�� ���� ��ȣ�� �ٴ´�. �̰� �������� ��� ī�带 �����ش�.
	int card_num = 13 * NUM_SHAPE;

	
	// �Լ��� ���� ����Ʈ ������ ������ ����
	hand_stack = LLS_Stack_Init();

	
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


	int cnt = 0;
	// ī�� Ʈ���� �����Ѵ�.
	/*
			cnt		c+i		i
cnt	i	j	�°�		�찪		��-��
0	1	0	0		1		1
1	2	0	1		3		2
2	2	1	2		4		2
3	3	0	3		6		3
4	3	1	4		7		3
5	3	2	5		8		3
6	4	0	6		10		4
7	4	1	7		11		4
8	4	2	8		12		4
9	4	3	9		13		4
	*/
	for (int i = 1; i < LINE; i++)
	{
		for (int j = 0; j < i; j++)
		{
			card_array[cnt]->llink = card_array[cnt + i];
			card_array[cnt]->rlink = card_array[cnt + i + 1];
			cnt++;
		}
	}
	
	// ������ ī�带 hand_stack �� push �Ѵ�.
	for (int i = 10; i < card_num; i++)
	{
		LLS_Push(hand_stack, card_array[i]->num, card_array[i]->shape);
		//printf("top : %d %d\n\n", LLS_Top(hand_stack)->num, LLS_Top(hand_stack)->shape);
	}
	while (1)
	{
		//������ 0�϶� ��忡�� �� ������ ����?
		show_board();
		if (index_position == -1)
		{
			//���� �� ����� �Ѵ�. ���µ� ���� �� 1����� ������ 0�� �Ǵ� �� ���̴�.�� ���̴�.
			if (hand_stack->size == 1) {
				printf("\n You Lose. \n");
				return;
			}
			LLS_Pop(hand_stack); // if no more card to play(empty stack), you lose.
			
		}
		if (remain == 0)
		{
			printf("\n You Win. \n");
			return;
		}

		/*ī�� Ȯ�� ��¿�
		
		card* card_temp;
		int count = 0;
		card_temp = hand_stack->top;
		while (card_temp != NULL) {
			printf("%d��° ����: ", count);
			show_shape_num(card_temp);
			printf("\n");
			card_temp = card_temp->llink;
			count++;
		}

		for (int i = 0; i < card_num; i++)
		{
			printf("%d��° ī��: ", i);
			show_shape_num(card_array[i]);
			printf("\n");
		}
		*/
	}

	return 0;

	/*
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
	*/
	LLS_Destroy(hand_stack);

	//MALLOC(card[i], sizeof(card));


	// �� ��ü�� �ε����ε�? �ε����� ������ �� �϶�� ���̾�. �ֳĸ� �ε����� �� �� �� ���ŵ�. ī�� 52�� �ְ� �迭�� ���� ���Ҹ� �����ϰ� �迭�ϸ� ����.
	// �׷��� ī�带 �ְ� ��ũ���ٰ� �ε����� �Ҵ������ڰ�? �ٵ� ��ũ�� ���� ��Ʈ�ݾ�. �̰ɷ� ���̵�, � �϶�� ���̾�?
	//���ڽ��� �����ؾ� �Ѵ�. ���? ī���� ����ü��.
	// ī�� ����ü�� �̿��ؼ� ���(ī��)Ÿ�Կ� �־�����.



}


void show_board() {
	printf("\n      0      \t");
	printf("      "); show_shape_num(card_array[0]); printf("   \n\n\n");
	printf("    1   2    \t");
	printf("    "); show_shape_num(card_array[1]); show_shape_num(card_array[2]); printf("\n\n\n");
	printf("  3   4   5  \t");
	printf("  "); show_shape_num(card_array[3]); show_shape_num(card_array[4]); show_shape_num(card_array[5]); printf("\n\n\n");
	printf("6   7   8   9\t");
	show_shape_num(card_array[6]); show_shape_num(card_array[7]); show_shape_num(card_array[8]); show_shape_num(card_array[9]); printf(" "); printf("\n\n\n");

	printf("You have (%2d) cards.\n", hand_stack->size);
	printf("============================================\n");

	//���� ī�� ��º�
	card* card_temp;
	int count = 0;
	hand_stack->top->show = 1;
	card_temp = hand_stack->top;
	while (hand_stack->size != count && count < 11) {
		show_shape_num(card_temp);
		card_temp = card_temp->llink;
		count++;
	}

	
	printf("\n\nEnter a number[0..9] to remove (-1 = new card) : ");
	scanf_s("%d", &index_position);

	if (card_array[index_position] != NULL) {
		if (index_position == -1) {
			return;
		}
		else if(0<=index_position && index_position <=9)
		{
			if ((hand_stack->top->num - card_array[index_position]->num == 1 ||
				hand_stack->top->num - card_array[index_position]->num == -1 ||
				hand_stack->top->num - card_array[index_position]->num == 12 ||
				hand_stack->top->num - card_array[index_position]->num == -12)
				&& card_array[index_position]->show == 1
				) {

				int cnt = 0;
				for (int i = 1; i < LINE; i++)
				{
					for (int j = 0; j < i; j++)
					{
						if (index_position == cnt + i) {
							card_array[cnt]->llink = NULL;
						}
						else if (index_position == cnt + i + 1) {
							card_array[cnt]->rlink = NULL;
						}
						cnt++;
					}
				}
				remain--;
				LLS_Push(hand_stack, card_array[index_position]->num, card_array[index_position]->shape);
				show_shape_num(card_array[index_position]);
				printf(" is removed.\n");
				free(card_array[index_position]);
				card_array[index_position] = NULL;
			}
			else
			{
				printf("Wrong input\n");
			}
		}
		else
		{
			printf("Wrong input\n");
		}

	
	}
	else
	{
		printf("Wrong input\n");
	}

	
	

}


void show_shape_num(node_ptr node) {
	if (node != NULL) {
		if (node->llink == NULL && node->rlink == NULL)
			node->show = 1;

		
		if (node->show == 1) {
			//������
		//	if (1) {
			if (node->shape == 0)
				printf("��");
			else if (node->shape == 1)
				printf("��");
			else if (node->shape == 2)
				printf("��");
			else if (node->shape == 3)
				printf("��");

			//�ε����� 0���� �����ϴ� ����� 1�� ����
			if (node->num == 0)
				printf("A ");
			else if (node->num == 9)
				printf("10");
			else if (node->num == 10)
				printf("J ");
			else if (node->num == 11)
				printf("Q ");
			else if (node->num == 12)
				printf("K ");
			else {
				printf("%d ", node->num+1);
			}
		}
		else {
			printf("��  ");
		}
	}
	else {
		printf("    ");
	}
	
	

}
