#include <stdio.h>
#include <stdlib.h>

#define LINE 4
#define NUM_SHAPE 4

/*
문제 이해
문제 속 3번째 사진과 2번째 사진의 순서가 바뀐 것 같습니다.
이렇게 이해한 이유는 사진의 그림 때문에 그렇습니다.

제가 가진 카드(그림1)
♣6ㅁㅁㅁㅁㅁㅁㅁㅁㅁ(You have (42) cards.)
↑(제일 위의 카드)

♣6(제일 위의 카드)이 ♥7(삼각형)을 제거하고 ♥7과 ♣6은 제 손으로 옵니다.
제가 가진 카드
♥7♣6ㅁㅁㅁㅁㅁㅁㅁㅁㅁ(You have (43) cards.)
↑(제일 위의 카드)

♥7(제일 위의 카드)이 ♠6(삼각형)을 제거하고 ♠6과 ♥7은 제 손으로 옵니다.
제가 가진 카드
♠6♥7♣6ㅁㅁㅁㅁㅁㅁㅁㅁㅁ(You have (44) cards.)
↑(제일 위의 카드)

♠6(제일 위의 카드)이 지울 게 없어 remove합니다.(제거와 다름. 제거는 카드끼리 짝을 맞춤)
제가 가진 카드
♥7♣6ㅁㅁㅁㅁㅁㅁㅁㅁㅁ(You have (43) cards.)
↑(제일 위의 카드)

♥7(제일 위의 카드)이 지울 게 없어 remove합니다.(제거와 다름. 제거는 카드끼리 짝을 맞춤)
제가 가진 카드(그림3)
♣6ㅁㅁㅁㅁㅁㅁㅁㅁㅁ(You have (42) cards.)
↑(제일 위의 카드)

♣6(제일 위의 카드)이 지울 게 없어 remove합니다.(제거와 다름. 제거는 카드끼리 짝을 맞춤)
제가 가진 카드(그림3)(그림2)
◆Kㅁㅁㅁㅁㅁㅁㅁㅁ(You have (41) cards.)
↑(제일 위의 카드)

◆K(제일 위의 카드)이 ♣Q(삼각형)을 제거하고 ◆K과 ♣Q은 제 손으로 옵니다.
제가 가진 카드(그림2)
♣Q◆Kㅁㅁㅁㅁㅁㅁㅁㅁ(You have (42) cards.)
↑(제일 위의 카드)

이때 ♣7이 오픈되고 삼각형 위에는 ♣7, ♠9, ◆4가 보입니다.
제가 가진 카드(그림2)
♣Q◆Kㅁㅁㅁㅁㅁㅁㅁㅁ(You have (42) cards.)
↑(제일 위의 카드)

이때부터 ♣Q◆K는 지우고 ♣7, ♠9, ◆4를 지울 카드가 나올 때까지 제가 가진 카드에서 ♣Q◆K등을 버립니다.
ㅁㅁㅁㅁㅁㅁㅁㅁ(You have (40) cards.)
↑(제일 위의 카드)

이 과정을 반복합니다.

//////////////////////////////////////////////////////
파일 구조

노드(카드)를 전부 할당해줍니다.(malloc 사용)

카드를 처음 모두 랜덤하게 섞어줍니다.
그리고 10개의 카드를 삼각형 모양 카드 트리로 할당해줍니다.
남은 카드는 사용자의 손에 있는 링크드 스택으로 옮깁니다.

남은 손에 있는 42(또는 16)개의 카드의 맨 위를 top으로 확인해 사용자에게 보여줍니다.

top에 있는 카드로 삼각형 위의 카드를 제거하기로 선택하면 제 손의 있는 top 카드는 유지되고 
제거하기로 한 카드 트리 위에 있던 카드가 제 손의 링크드 스택으로으로 옵니다.

만약 매칭되는 것이 없다면 -1을 눌러 링크드 스택을 pop해줍니다.


(참고)아래 코드는 이미 뽑은 중복된 카드인지 아닌지를 검사해야 하기 때문에 남은 카드가 0에 가까워질수록 불필요한 연산이 많아져 쓰지 않았습니다.
	int mark[4][13]; //randomly pick cards
	int sh, no;
	sh = rand() % NUM_SHAPE; // NUM_SHAPE = 2 or 4, (2 is recommended.)
	no = rand() % 13; // 0 = A, 12 = K
*/


// Card tree : doubly linked list (tree node is created by malloc())
// Hand card : linked hand_stack (top node card is to be played)

////////////////노드(카드) 정의////////////////////

typedef struct node_type* node_ptr;
typedef struct node_type {
	int num; // A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K
	int shape; // 0, 1, 2, 3 = {space, heart, clover, diamond} = 2 or 4 sets
	int show; // 0 = hide, 1 = show
	node_ptr llink, rlink;
}card;

////////////////노드(카드) 정의////////////////////



void show_shape_num(node_ptr node);
void show_board();



void shuffle(int* card_key, int card_num);






////////////////스택 및 스택함수 정의////////////////////

// LinkedListStack : 스택 형태의 리스트를 정의
typedef struct LinkedListStack {
	card* top; // 리스트의 탑 노드(카드) 주소를 가리킬 포인터
	int size; // 리스트의 노드(카드) 갯수를 저장할 변수
} LinkedListStack;

// LLS_Stack_Init : 스택 형태의 리스트를 초기화
LinkedListStack* LLS_Stack_Init() {
	LinkedListStack* hand_stack;
	hand_stack = (LinkedListStack*)malloc(sizeof(LinkedListStack));
	hand_stack->top = NULL;
	hand_stack->size = 0;
	return hand_stack;
}

LinkedListStack* LLS_Stack_Init();
card* LLS_Node_Init(int num, int shape);
void LLS_Push(LinkedListStack* list, int num, int shape);
void LLS_Pop(LinkedListStack* list);
card* LLS_Top(LinkedListStack* list);
void LLS_Destroy(LinkedListStack* list);


// LLS_Node_Init : 스택에 들어갈 노드(카드)를 초기화
card* LLS_Node_Init(int num, int shape) {
	// 새로운 노드(카드)의 메모리를 힙 영역에 할당
	card* new_top = (card*)malloc(sizeof(card));
	// 노드(카드)의 공간을 힙 영역에 할당
	// 노드(카드)의 card_num, shape에 card_num, shape을 할당
	new_top->num = num;
	new_top->shape = shape;
	// 노드(카드)의 show에 기본적으로 hide(0)를 할당
	new_top->show = 0;
	// 노드(카드)의 포인터를 지정
	new_top->llink = NULL;
	new_top->rlink = NULL;
	return new_top;
}

// LLS_Push : 리스트(스택)의 Top위에 새로운 노드(카드)를 추가
void LLS_Push(LinkedListStack* list, int num, int shape) {
	// top에 넣을 새로운 노드(카드)를 생성
	card* new_top = LLS_Node_Init(num, shape);
	// old_top : 현재의 마지막(가장 위) 노드(카드)를 보관할 변수
	card* old_top;

	// 리스트(스택)에 노드(카드)가 없는 경우
	if (list->top == NULL) {
		//현재 top에 new_top를 할당한다.
		list->top = new_top;
	}
	// 리스트(스택)에 노드(카드)가 있는 경우
	else {
		//현재 리스트의 top을 old_top에 할당한다.
		old_top = list->top;
		//old_top의 상단 포인터(rlink)가 new_top를 가리키도록 한다.
		old_top->rlink = new_top;
		//new_top의 하단 포인터(llink)가 old_top를 가리키도록 한다.
		new_top->llink = old_top;
		//현재 리스트의 top에 new_top를 할당한다.
		list->top = new_top;
	}
	// 리스트의 노드(카드) 갯수를 추가
	list->size++;
}

// LLS_Pop : 리스트(스택)의 Top을 제거
// -1을 선택하면 remove한다.
void LLS_Pop(LinkedListStack* list) {
	// old_top : 제거 전 현재의 Top 노드(카드)를 저장할 노드(카드)
	card* old_top = list->top;
	// new_top : old_top 노드(카드)가 제거되고 새롭게 Top 노드(카드)가 될 노드(카드). old_top->llink이다.
	card* new_top;

	// 리스트(스택)에 노드(카드)가 하나도 없는 경우 함수를 종료
	if (old_top == NULL) {
		printf("손에 남아 있는 카드가 없습니다.\n");
		return;
	}
	// 리스트(스택)에 노드(카드)가 있는 경우
	else {
		// old_top->llink 의 노드(카드)를 new_top 에 할당한다.
		// 만약 스택에 1개가 남은 상태라면 NULL이 할당된다.
		new_top = old_top->llink;
		//old_top이 마지막이라면 new_top에는 NULL이 할당된다. 이때 new_top->rlink은 에러가 난다.
		if (new_top != NULL) {
			// new_top의 상단 포인터에 NULL을 할당한다.
			new_top->rlink = NULL;
		}
		// list->top 에 new_top을 할당한다.
		list->top = new_top;
		
	}
	//리스트의 사이즈를 1 뺀다. list->size == 0이면 게임 종료
	list->size--;
	// old_top 노드(카드)의 메모리를 해제
	free(old_top);
}

// LLS_Top : 리스트(스택)의 Top을 반환하는 함수. 가장 위의 카드를 보여준다.
card* LLS_Top(LinkedListStack* list) {
	return list->top;
}

// LLS_Destroy : 리스트(스택)의 모든 노드(카드)와 리스트의 메모리를 해제
void LLS_Destroy(LinkedListStack* list) {
	card* delNode = list->top;
	while (delNode != NULL) {
		list->top = list->top->llink;
		free(delNode);
		delNode = list->top;
	}
	free(list);
}
////////////////스택 및 스택함수 정의////////////////////




////////////////카드 섞는 함수 정의////////////////////
// 배열을 섞는 함수 
void shuffle(int* card_key, int card_num) {
	//srand 는 호출할 때 전달받는 인자를 기반으로 해서 난수를 초기화 시켜주는 역할을 한다.
	//rand 는 srand 로 인해 생성된 값을 바탕으로 난수를 생성해 주는 역할을 한다.
	srand(time(NULL)); 
	int temp;
	int random_index; 
	for (int i = 0; i < card_num - 1; i++) {
		random_index = rand() % (card_num - i) + i; // i 부터 card_num-1 사이에 임의의 정수 생성  - 배열의 인덱스를 고르는 것이다.
		temp = card_key[i]; 
		card_key[i] = card_key[random_index]; 
		card_key[random_index] = temp;
	}
} 
////////////////카드 섞는 함수 정의////////////////////


node_ptr* card_array;

// hand_stack 이라는 리스트를 생성. 손에 쥔 카드 리스트이다.
LinkedListStack* hand_stack;
int index_position = 0;
int remain = 10;

int main(void) {

	//각 카드는 0~(13*NUM_SHAPE-1)까지의 고유키가 할당된다. 중복 없음
	//이렇게 하면 0~12는 ♠1~♠12, 13~25는 ♥0~12, 26~38는 ♣0~12, 39~51는 ◆0~12가 할당된다.
	//각 카드는 0~12까지의 card_num, 0~(NUM_SHAPE-1)까지의 shape가 할당된다.
	//각 카드의 num을 구하려면 고유키 % 13을
	//각 카드의 shape을 구하려면 고유키 / 13 을 하면 된다.

	//마크에는 1~(NUM_SHAPE*13)의 고유 번호가 붙는다. 이걸 랜덤으로 섞어서 카드를 섞어준다.
	int card_num = 13 * NUM_SHAPE;

	
	// 함수를 통해 리스트 형태의 스택을 생성
	hand_stack = LLS_Stack_Init();

	
	card_array = (int*)malloc(sizeof(card) * card_num); // 카드의 수만큼 노드(카드) 메모리 할당

	int* card_key;
	card_key = (int*)malloc(sizeof(int) * card_num); // 카드의 수만큼 배열 메모리 할당
	
	for (int i = 0; i < card_num; i++) {
		card_key[i] = i; // 배열을 0부터 card_num-1 까지의 요소로 초기화 
		card_array[i] = LLS_Node_Init(0, 0);	// 각 카드들을 초기화(하지 않으면 초기화되지 않은 값 에러가 뜬다)
	}
		


	// 카드의 순서를 섞어준다.
	shuffle(card_key, card_num);
	
	// 섞인 card_key 를 바탕으로 노드(카드)에 카드를 할당한다. 이렇게 랜덤한 배열의 카드가 생성된다.
	for (int i = 0; i < card_num; i++)
	{
		card_array[i]->num = card_key[i] % 13;
		card_array[i]->shape = card_key[i] / 13;
	}

	// 더이상 필요 없는 card_key 에 할당된 메모리를 해제한다.
	free(card_key);


	int cnt = 0;
	// 카드 트리를 형성한다.
	/*
			cnt		c+i		i
cnt	i	j	좌값		우값		우-좌
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
	
	// 나머지 카드를 hand_stack 에 push 한다.
	for (int i = 10; i < card_num; i++)
	{
		LLS_Push(hand_stack, card_array[i]->num, card_array[i]->shape);
		//printf("top : %d %d\n\n", LLS_Top(hand_stack)->num, LLS_Top(hand_stack)->shape);
	}
	while (1)
	{
		//스택이 0일때 쇼보드에서 왜 에러가 나지?
		show_board();
		if (index_position == -1)
		{
			//순서 잘 해줘야 한다. 뺐는데 남은 게 1개라면 다음은 0이 되니 진 것이다.진 것이다.
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

	}

	return 0;

	
	LLS_Destroy(hand_stack);


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

	//남은 카드 출력부
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
			//디버깅용
		//	if (1) {
			if (node->shape == 0)
				printf("♠");
			else if (node->shape == 1)
				printf("♥");
			else if (node->shape == 2)
				printf("♣");
			else if (node->shape == 3)
				printf("◆");

			//인덱스는 0부터 시작하니 출력은 1씩 더함
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
			printf("■  ");
		}
	}
	else {
		printf("    ");
	}
	
	

}
