#include <stdio.h>
#include <stdlib.h>

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


//MALLOC 정의
#define MΑLLOC(p, s) \
	if (!((p) = malloc(s))) { \
	printf("Insufficient memory"); \
	exit(EXIT_FAILURE);}

#define NUM_SHAPE 2

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
		// new_top의 상단 포인터에 NULL을 할당한다.
		new_top->rlink = NULL;
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
////////////////카드 섞는 함수 정의////////////////////

} int main(void) {

	//각 카드는 0~(13*NUM_SHAPE-1)까지의 고유키가 할당된다. 중복 없음
	//이렇게 하면 0~12는 ♠1~♠12, 13~25는 ♥0~12, 26~38는 ♣0~12, 39~51는 ◆0~12가 할당된다.
	//각 카드는 0~12까지의 card_num, 0~(NUM_SHAPE-1)까지의 shape가 할당된다.
	//각 카드의 num을 구하려면 고유키 % 13을
	//각 카드의 shape을 구하려면 고유키 / 13 을 하면 된다.

	//마크에는 1~(NUM_SHAPE*13)의 고유 번호가 붙는다. 이걸 랜덤으로 섞어서 카드를 섞어준다.
	int card_num = 13 * NUM_SHAPE;

	// hand_stack 이라는 리스트를 생성. 손에 쥔 카드 리스트이다.
	LinkedListStack* hand_stack;
	// 함수를 통해 리스트 형태의 스택을 생성
	hand_stack = LLS_Stack_Init();

	node_ptr *card_array;
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

	// 카드 트리를 형성한다.
	for (int i = 0; i < 10; i++)
	{
		
	}

	// 나머지 카드를 hand_stack 에 push 한다.
	for (int i = 10; i < card_num; i++)
	{
		LLS_Push(hand_stack, card_array[i]->num, card_array[i]->shape);
		printf("top : %d %d\n\n", LLS_Top(hand_stack)->num, LLS_Top(hand_stack)->shape);
	}

	//printarr(card_key, card_num);
	return 0;


	// 1개의 노드(카드)를 푸쉬
	printf("Push a node\n");
	LLS_Push(hand_stack, 1, 1);
	// hand_stack 리스트 top의 데이터를 출력
	printf("top : %d %d\n\n", LLS_Top(hand_stack)->num, LLS_Top(hand_stack)->shape);

	// 3개의 노드(카드)를 푸쉬
	printf("Push three nodes\n");
	LLS_Push(hand_stack, 2, 1);
	LLS_Push(hand_stack, 3, 1);
	LLS_Push(hand_stack, 4, 1);
	// hand_stack 리스트 top의 데이터를 출력
	printf("top : %d %d\n\n", LLS_Top(hand_stack)->num, LLS_Top(hand_stack)->shape);

	// Pop실행 최상위 노드(카드) 제거
	printf("Pop\n");
	LLS_Pop(hand_stack);
	// hand_stack 리스트 top의 데이터를 출력
	printf("top : %d %d\n\n", LLS_Top(hand_stack)->num, LLS_Top(hand_stack)->shape);

	// Pop을 두번 실행
	printf("Pop two nodes\n");
	LLS_Pop(hand_stack);
	LLS_Pop(hand_stack);
	// hand_stack 리스트 top의 데이터를 출력
	printf("top : %d %d\n\n", LLS_Top(hand_stack)->num, LLS_Top(hand_stack)->shape);

	LLS_Destroy(hand_stack);

	//MALLOC(card[i], sizeof(card));


	// 이 자체로 인덱스인데? 인덱스를 가지고 뭘 하라는 말이야. 왜냐면 인덱스에 뭐 들어갈 게 없거든. 카드 52장 주고 배열의 내부 원소를 랜덤하게 배열하면 몰라.
	// 그러면 카드를 주고 마크에다가 인덱스를 할당해주자고? 근데 마크의 값은 인트잖아. 이걸로 하이드, 쇼를 하라는 뜻이야?
	//숫자쌍을 저장해야 한다. 어떻게? 카드라는 구조체로.
	// 카드 구조체를 이용해서 노드(카드)타입에 넣어주자.



}

//
//
//#include <stdio.h>
//#include <stdlib.h>	//EXIT_FAILURE
////#include <cstddef>	//NULL 이거 쓰면 에러난다.
//
////변수명 자체를 출력
//#define TO_STRING(a) #a
//
//
////MALLOC 정의
//#define MΑLLOC(p, s) \
//	if (!((p) = malloc(s))) { \
//	printf("Insufficient memory"); \
//	exit(EXIT_FAILURE);}
//
////포인터의 값으로부터 노드(카드) 위치 추출 매크로
//#define CHECK(p) if (p == first) str = "first";\
//else if (p == second) str = "secon";\
//else if (p == third) str = "third";\
//else str = "NULL";\
//
////리스트 출력 매크로
//#define PRINT(p) print = p;\
//printf("%s", TO_STRING(p));\
//i = 1;\
///*첫 노드(카드)의 주소값을 기억하기 위한 포인터*/\
//temp = print;\
//printf("\taddr\t\tdata\tlink\n");\
//if(print){\
//	/*첫 노드(카드)를 출력한다.*/\
//	CHECK(print)\
//	printf("n_%d\t%p(%s)\t", i, print, str);\
//	printf("%d\t", print->data);\
//	CHECK(print->link)\
//	printf("%p(%s)\n", print->link, str);\
//	i++;\
//	print = print->link;\
///* 첫 노드(카드)의 주소와 같아질 때까지 출력. circular이기 때문 */ \
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
////노드(카드) 1개 출력 매크로
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
////노드(카드)용 포인터와 프린트용 포인터 2개(print, temp)
//list_pointer first, second, third, print, temp;
////string 출력
//char* str;
//
////for문에서 node의 숫자 출력을 위함
//int i;
////리스트의 노드(카드) 갯수에 따른 모든 노드(카드) 각각 출력용
//int node_count;
//
////cinvert 함수
//list_pointer cinvert(list_pointer lead)
//{//lead가 가리키고 있는 리스트를 역순으로 만든다.
//	list_pointer middle, trail;
//	middle = NULL;
//	trail = NULL;	//마지막 리턴될 포인터이다.
//	int count = 1;
//	while (lead)	//lead가 null이 될 때까지 진행. lead는 처음 노드(카드)를 받고 노드(카드)의 끝인 null을 받게 된다.
//	{
//		/*
//		1. lead는 리스트의 첫 노드(카드)부터 마지막_노드(카드)까지 순차적으로 접근한다.
//			1.1. 처음 while문의 middle->link = trail;에 의하여 리스트의 시작 노드(카드) first->link = null이 된다.
//			1.2. 마지막_노드(카드)->link = first이다. 따라서 마지막으로 방문하는 노드(카드)는 first가 된다.(마지막으로 방문하는 노드(카드) != 마지막_노드(카드))
//		2. trail은 지금까지 생성된 middle을 받는다.
//		3. middle은 lead, 즉 다음 노드(카드), 연산할 노드(카드)를 받는다.
//		4. middle->link에 trail을 주어 연산할 노드(카드)의 뒤에 그전까지 생성된 middle을 붙여 역순의 리스트를 만든다.
//		5. 최종적으로 lead는 null이 되면 while 문이 끝나고, while 문에서 나가기 직전, 1.2.에 의하여 middle은 first 노드(카드)를 가리키게 된다.
//			5.1. 우리는 마지막_노드(카드)의 주소값을 리턴 받고 싶다.
//			5.2. first(=middle)->link = 마지막_노드(카드)이다.
//			5.3. middle->link = trail이다.
//			5.4. 따라서 trail = 마지막_노드(카드)이다.
//			5.5. 따라서 trail을 리턴 받으면 마지막_노드(카드)의 주소값을 리턴 받게 된다.
//		6. 이때, first부터 시작해서 마지막_노드(카드)를 방문하고 다시 first를 방문한다. 따라서 while 문은 n+1번 시행된다.
//			6.1. lead == NULL일 때 while 문은 실행되지 않는다. 이때, lead = trail = NULL이므로 trail을 리턴해도 동일한 결과를 갖는다.
//		7. 5.5., 6.1.에 의하여 trail을 리턴한다.
//		*/
//		trail = middle;	//trail에 middle을 넣는다. 처음에는 null이 들어간다.
//		middle = lead;	//middle에 lead를 넣는다. 처음에는 받은 포인터의 주소가 들어간다. 1개일 때와 0개일 때 동일 값 리턴.
//		lead = lead->link;	//lead의 다음 노드(카드)를 가리킨다. 1.1., 1.2.에 의하여 마지막에 null을 가리키게 되고 이때 while 문을 빠져나간다.
//		middle->link = trail;	//middle의 link, 즉 뒤에 올 것들에 trail을 넣는다.
//
//		printf("----------------------요구사항 3↓----------------------\n");
//		printf("**************while문 %d번 째 실행**************\n", count);
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
//		printf("----------------------요구사항 3↑----------------------\n");
//		count++;
//	}
//	//7. 5.5., 6.1.에 의하여 trail을 리턴한다.
//	return trail;
//}
//
//int main() {
//	//리스트 선언 및 할당
//	list_pointer L2, L2_cinv, L1, L1_cinv, L0, L0_cinv;
//	//노드(카드)에 메모리 할당
//	MΑLLOC(first, sizeof(*first));
//	MΑLLOC(second, sizeof(*second));
//	MΑLLOC(third, sizeof(*third));
//
//	//값 할당
//	first->data = 10;
//	first->link = second;
//	second->data = 20;
//	second->link = first;
//
//	third->data = 30;
//	third->link = third;
//
//	//포인터 확인용 첫 출력
//	PRINT1(first);
//	PRINT1(second);
//	PRINT1(third);
//
//	//L2에 첫 노드(카드) 할당
//	L2 = first;
//	//처음 L2를 받아서 출력 시 L2를 다음 노드(카드)의 주소값으로 바꾼다.
//	//first와 second는 영향을 받지 않는다.
//	printf("----------------------요구사항 1↓----------------------\n");
//	node_count = 2;
//	PRINT(L2);
//	printf("----------------------요구사항 1↑----------------------\n");
//
//	//L2에 first를 cinvert하고 할당
//	printf("----------------------요구사항 2↓----------------------\n");
//	L2_cinv = cinvert(L2);
//	printf("----------------------요구사항 2↑----------------------\n");
//
//	printf("----------------------요구사항 4↓----------------------\n");
//	PRINT(L2_cinv);
//	printf("----------------------요구사항 4↑----------------------\n");
//
//
//	printf("----------------------요구사항 5↓----------------------\n");
//	node_count = 1;
//	//노드(카드) 1개짜리 second를 L1에 할당.
//	L1 = third;
//	PRINT(L1);
//	L1_cinv = cinvert(third);
//	PRINT(L1_cinv);
//	printf("----------------------요구사항 5↑----------------------\n");
//
//	printf("----------------------요구사항 6↓----------------------\n");
//	node_count = 0;
//	L0 = NULL;
//	PRINT(L0);
//	L0_cinv = cinvert(L0);
//	PRINT(L0_cinv);
//	printf("----------------------요구사항 6↑----------------------\n");
//	return 0;
//}
