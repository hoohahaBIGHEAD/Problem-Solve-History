//노드 구조체 선언 방식
//노드는 데이터 필드와 링크 필드로 나뉘어 있다.
//노드는 링크 타입을 먼저 선언해주고
//링크 자체가 가리키는 대상이 노드 자체이다.
//링크의 데이터 타입을 포인터로 먼저 선언을 한다.
//포인터가 가리키는 대상은 노드이기 때문에 노드를 가리키는 포인터 형식인 _list_node* 타입을 가진다.
typedef struct _list_node* node_pointer;
// 주의할 점 :: _node - tag 이다. 자료형의 명칭은 뒤의 node 이다. 이는 생략해도 된다.
typedef struct _node {
	//declaration of data filds
	
	//자기 자신을 참조하는 구조체이다.
	//C언어는 구문을 허용한다.
	node_pointer previous_node;
	node_pointer next_node;
} node;

