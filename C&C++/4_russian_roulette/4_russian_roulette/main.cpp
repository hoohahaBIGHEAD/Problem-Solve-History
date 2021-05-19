//-----------↓ add_comment_here ↓-----------
//-----------↑ add_comment_here ↑-----------

#include <iostream>
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

typedef struct _linked_list_circular {
	node* last; // 리스트의 마지막 노드 주소를 가리킬 포인터
} linked_list_circular;

linked_list_circular* linked_list_circular_initialize() {
	
	//linked_list_circular를 가리킬 포인터 생성
	linked_list_circular* new_list;
	//메모리 할당
	new_list = (linked_list_circular*)malloc(sizeof(linked_list_circular));
	//처음 리스트의 last 포인터를 NULL로 할당
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

//-----------↑ circular linked list ↑-----------


int main() {

	//-----------↓ 노드 인스턴스 선언 ↓-----------
	// 노드 인스턴스를 선언할 때에는 노드를 가리키는 포인터를 선언해준다.
	// 선언해준 포인터에 노드 만큼 메모리를 할당해준다.

	node_pointer A;
	
	// 이때 sizeof(*A) = sizeof(node) 이다.
	//printf("sizeof(*A) : %d\tsizeof(node) : %d", sizeof(*A), sizeof(node));
	
	A = node_initialize(true);
	
	// 리스트를 가리킬 포인터 생성
	linked_list_circular* list;
	// 리스트 초기화
	list = linked_list_circular_initialize();

	insert_node_front(list, false);
	insert_node_front(list, false);
	insert_node_front(list, false); 
	insert_node_front(list, true);
	insert_node_front(list, false); 
	insert_node_front(list, false);

	 

	//-----------↑ 노드 인스턴스 선언 ↑-----------

	return 0;
}