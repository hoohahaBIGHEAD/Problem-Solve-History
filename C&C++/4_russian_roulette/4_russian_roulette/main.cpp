//-----------↓ add_comment_here ↓-----------
//-----------↑ add_comment_here ↑-----------

#include <iostream>
#include <time.h>
using namespace std;

//-----------↓ 노드 구조체 정의 방식 ↓-----------

//노드는 데이터 필드와 링크 필드로 나뉘어 있다.
//노드는 링크 타입을 먼저 선언해주고
//링크 자체가 가리키는 대상이 노드 자체이다.
//링크의 데이터 타입을 포인터로 먼저 선언을 한다.
//포인터가 가리키는 대상은 노드이기 때문에 노드를 가리키는 포인터 형식인 _node* 타입을 가진다.
typedef struct _node* node_pointer;
// 주의할 점 :: _node - tag 이다. 자료형의 명칭은 뒤의 node 이다.
typedef struct _node {
	//declaration of data filds
	//장전 여부. true - 총알 있음. false - 총알 없음.
	bool is_loaded;
	
	//자기 자신을 참조하는 구조체이다.
	//C언어는 구문을 허용한다.
	node_pointer next;
} node;

//-----------↑ 노드 구조체 정의 방식 ↑-----------


//-----------↓ Dynamic allocation of a node ↓-----------

// node_initialize : 노드를 초기화하고 메모리를 동적으로 할당
node* node_initialize(bool bullet) {
	// 새로운 노드의 메모리를 힙 영역에 할당
	node* new_node = (node*)malloc(sizeof(node));
	// 노드의 공간을 힙 영역에 할당
	// 노드의 is_loaded에 bullet을 할당
	new_node->is_loaded = bullet;

	// 노드의 포인터를 지정
	new_node->next= NULL;

	// 메모리가 할당된 새로운 노드를 node_pointer 형으로 리턴
	return new_node;
}

//-----------↑ Dynamic allocation of a node ↑-----------


//-----------↓ circular linked list ↓-----------

// _linked_list_circular : circular 형태의 linked list 정의

// 리스트의 데이터 타입이 특이한데, 리스트의 노드가 마지막을 가리킨다.
// 이렇게 하는 이유는, 리스트의 마지막 노드를 쉽게 찾게 하기 위해서이다.
// 리스트를 처음 노드를 가리키게 되면, 마지막 노드를 찾는 데 O(n)이 걸린다. 
// 마지막 노드를 가리키게 되면, 마지막 노드를 O(1)에 찾을 수 있고
// 첫 번째 노드도 O(1)에 찾을 수 있다.
// 따라서 리스트에 데이터를 삽입할 때 O(1)이 걸린다.

// 링크드 리스트의 
typedef struct _linked_list_circular {
	node_pointer last; // 리스트의 마지막 노드 주소를 가리킬 포인터
} linked_list_circular;

linked_list_circular* linked_list_circular_initialize() {
	
	// linked_list_circular를 가리킬 포인터 생성
	linked_list_circular* new_list;
	// new_list에 메모리 할당
	new_list = (linked_list_circular*)malloc(sizeof(linked_list_circular));
	// 이 리스트는 처음에는 노드를 가지고 있지 않다.
	// 리스트의 last 포인터를 NULL로 할당
	new_list->last = NULL;
	return new_list;
}

// 리스트의 front에 새로운 노드를 추가한다.
void insert_node_front(linked_list_circular* list, bool bullet) {
	// 리스트의 front에 넣을 새로운 노드
	node* new_front = node_initialize(bullet);

	// 리스트에 노드가 없는 경우
	if (list->last == NULL) {
		// 현재 리스트가 새로운 노드를 가리키게 한다.
		list->last = new_front;
		// 해당 노드는 자기 자신을 가리키도록 한다.
		new_front->next = new_front;
	}

	// 리스트에 노드가 있는 경우
	else
	{
		// 새로운 노드가 리스트의 front 노드(=기존 리스트의 마지막 노드의 다음 노드 = list->last->next)를 가리키게 한다.
		// 기존의 리스트의 front는 new_front가 가리키므로 두번째가 된다.
		new_front->next = list->last->next;
		// 리스트의 마지막 노드의 다음 노드(리스트의 front를 가리킴)가 새로운 노드를 가리키도록 한다.
		list->last->next = new_front;
	}
}


//-----------↓ 불릿 확인용 ↓-----------
/* Function to traverse a given Circular linked list and print nodes */
void print_list(linked_list_circular* list) {
	node* temp = list->last->next;
	int count = 1;

	// If linked list is not empty
	if (list->last->next != NULL)
	{
		// Keep printing nodes till we reach the first node again
		do
		{
			printf("%d번째 칸 장전 여부? ", count++);
			printf(temp->is_loaded ? "true" : "false");
			printf("\n");
			temp = temp->next;
		} while (temp != list->last->next);
	}
}
//-----------↑ 불릿 확인용 ↑-----------

//-----------↓ 메모리 할당 삭제 ↓-----------
/* Function to traverse a given Circular linked list and print nodes */
void print_list(linked_list_circular* list) {
	
	node* temp;
	temp = list->last;
	//다음 노드로 last 이동
	list->last = list->last->next;
	list->last->next = NULL;
	free(list->last);

	// If linked list is not empty
	if (list->last->next != NULL)
	{
		// Keep printing nodes till we reach the first node again
		do
		{
			temp = temp->next;
		} while (temp != list->last->next);
	}

}
//-----------↑ 불릿 확인용 ↑-----------


//Conditions: “rotate” means that Revolver’s head moves to the next node by a random number.
//Conditions: After “rotate” clean the screen using ‘system(“cls”)’.
void rotate(linked_list_circular* list) {

	//랜덤 시드 초기화
	srand(time(NULL));

	//0에서 5 사이의 랜덤한 숫자를 생성한다.
	int random = rand() % 6;

	for (int i = 0; i < random; i++)
	{
		//리스트가 가리키는 노드에서 random 만큼 이동한다.
		list->last = list->last->next;
	}

	
}
//요구사항 4. If receive “shoot” command 
bool shoot(linked_list_circular* list) {
	//요구사항 4. then check the bullet, 
	//Conditions: The “shoot” command checks Revolver’s head and moves the head to the next node.
	//리스트의 헤드 노드의 장전 여부를 확인한다.
	bool is_loaded = list->last->next->is_loaded;

	//if exists, then print “You Died…” and program end.
	// 만약 장전되어 있다면 죽었다는 메시지를 보내고 게임을 종료한다.
	// 이때 shoot 은 false를 리턴하고 main 의 while 문은 종료된다.
	if (is_loaded)
	{
		printf("You Died...\n");
		//새 게임이 시작되도록 list를 rotate한다.
		rotate(list);
		return false;
	}
	//요구사항 5. If not exists, then print “You Survived!” and repeat 3.
	else
	{
		printf("You Survived!\n");
		//Conditions: moves the head to the next node.
		// 리스트의 노드를 한 칸 이동한다.
		list->last = list->last->next;
		return true;
	}
}

//-----------↑ circular linked list ↑-----------


int main() {

	//-----------↓ 노드 인스턴스 선언 ↓-----------
	/* 노드 예시 설명
	
	// 노드 인스턴스를 선언할 때에는 노드를 가리키는 포인터를 선언해준다.
	// 선언해준 포인터에 노드 만큼 메모리를 할당해준다.

	node_pointer A;
	
	// 이때 sizeof(*A) = sizeof(node) 이다.
	//printf("sizeof(*A) : %d\tsizeof(node) : %d", sizeof(*A), sizeof(node));
	
	A = node_initialize(true);

	*/
	string command;


	//요구사항 1. Create a Revolver, which is circular linked list.
	linked_list_circular* Revolver;
	Revolver = linked_list_circular_initialize();

	//요구사항 2. Insert one bullet to Revolver and “rotate”.
	//Conditions: Revolver is connected to 6 nodes, which are created in Revolver’s constructor.
	insert_node_front(Revolver, false);
	insert_node_front(Revolver, false);
	insert_node_front(Revolver, false);
	insert_node_front(Revolver, false);
	insert_node_front(Revolver, false);
	insert_node_front(Revolver, true);
	rotate(Revolver);


	//요구사항 5. repeat 3.
	//게임을 3번 진행
	int is_survived = true;
	for (int i = 0; i < 3; i++)
	{
		is_survived = true;
		// 모든 총알 확인
		//print_list(Revolver);
		// printf("게임 %d회차\n", i+1);
		
		//요구사항 3. “shoot” / “rotate” command to shoot or rotate.
		printf("Command list(shoot/rotate)\n");
		while (is_survived)
		{
			cout << "CMD>> ";
			cin >> command;
			//* Assume that there is no input of the same word with different case >> string 끼리의 == 연산자는 대소문자가 다르면 다른 결과로 인식한다.
			if (command == "rotate") {
				rotate(Revolver);
				//Conditions: After “rotate” clean the screen using ‘system(“cls”)’.
				system("cls");
				printf("Command list(shoot/rotate)\n");
			}
			// 요구사항 4. If receive “shoot” command then check the bullet, if exists, then print “You Died…” and program end.
			else if (command == "shoot")
			{
				is_survived = shoot(Revolver);
			}
			//* Handle exceptions for possible exceptions >> string 입력에 위 두 커맨드를 제외하면 "Wrong Command!"가 출력되도록 함
			else
			{
				printf("Wrong Command!\n");
			}
		}
		
	}

	//-----------↑ 노드 인스턴스 선언 ↑-----------

	//* If dynamic allocation is not deallocated, you will have -0.2 point penalty for each task
	

	return 0;
}

