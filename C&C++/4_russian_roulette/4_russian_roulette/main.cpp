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
node* node_initialize() {
	// 새로운 노드의 메모리를 힙 영역에 할당
	node* new_node = (node*)malloc(sizeof(node));
	// 노드의 공간을 힙 영역에 할당
	// 노드의 is_loaded에 처음 false를 할당
	new_node->is_loaded = false;

	// 노드의 포인터를 지정
	new_node->next= NULL;

	// 메모리가 할당된 새로운 노드를 node_pointer 형으로 리턴
	return new_node;
}

//-----------↑ Dynamic allocation of a node ↑-----------

int main() {

	//-----------↓ 노드 인스턴스 선언 ↓-----------
	// 노드 인스턴스를 선언할 때에는 노드를 가리키는 포인터를 선언해준다.
	// 선언해준 포인터에 노드 만큼 메모리를 할당해준다.

	node_pointer A;
	
	// 이때 sizeof(*A) = sizeof(node) 이다.
	//printf("sizeof(*A) : %d\tsizeof(node) : %d", sizeof(*A), sizeof(node));
	
	A = node_initialize();
	


	//-----------↑ 노드 인스턴스 선언 ↑-----------

	return 0;
}