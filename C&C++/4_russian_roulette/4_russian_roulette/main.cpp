//-----------�� add_comment_here ��-----------
//-----------�� add_comment_here ��-----------

#include <iostream>
using namespace std;

//-----------�� ��� ����ü ���� ��� ��-----------

//���� ������ �ʵ�� ��ũ �ʵ�� ������ �ִ�.
//���� ��ũ Ÿ���� ���� �������ְ�
//��ũ ��ü�� ����Ű�� ����� ��� ��ü�̴�.
//��ũ�� ������ Ÿ���� �����ͷ� ���� ������ �Ѵ�.
//�����Ͱ� ����Ű�� ����� ����̱� ������ ��带 ����Ű�� ������ ������ _node* Ÿ���� ������.
typedef struct _node* node_pointer;
// ������ �� :: _node - tag �̴�. �ڷ����� ��Ī�� ���� node �̴�.
typedef struct _node {
	//declaration of data filds
	//���� ����. true - �Ѿ� ����. false - �Ѿ� ����.
	bool is_loaded;
	
	//�ڱ� �ڽ��� �����ϴ� ����ü�̴�.
	//C���� ������ ����Ѵ�.
	node_pointer next;
} node;

//-----------�� ��� ����ü ���� ��� ��-----------


//-----------�� Dynamic allocation of a node ��-----------

// node_initialize : ��带 �ʱ�ȭ�ϰ� �޸𸮸� �������� �Ҵ�
node* node_initialize(bool bullet) {
	// ���ο� ����� �޸𸮸� �� ������ �Ҵ�
	node* new_node = (node*)malloc(sizeof(node));
	// ����� ������ �� ������ �Ҵ�
	// ����� is_loaded�� bullet�� �Ҵ�
	new_node->is_loaded = bullet;

	// ����� �����͸� ����
	new_node->next= NULL;

	// �޸𸮰� �Ҵ�� ���ο� ��带 node_pointer ������ ����
	return new_node;
}

//-----------�� Dynamic allocation of a node ��-----------


//-----------�� circular linked list ��-----------

// _linked_list_circular : circular ������ linked list ����

// ����Ʈ�� ������ Ÿ���� Ư���ѵ�, ����Ʈ�� ��尡 �������� ����Ų��.
// �̷��� �ϴ� ������, ����Ʈ�� ������ ��带 ���� ã�� �ϱ� ���ؼ��̴�.
// ����Ʈ�� ó�� ��带 ����Ű�� �Ǹ�, ������ ��带 ã�� �� O(n)�� �ɸ���. 
// ������ ��带 ����Ű�� �Ǹ�, ������ ��带 O(1)�� ã�� �� �ְ�
// ù ��° ��嵵 O(1)�� ã�� �� �ִ�.
// ���� ����Ʈ�� �����͸� ������ �� O(1)�� �ɸ���.

// ��ũ�� ����Ʈ�� 
typedef struct _linked_list_circular {
	node_pointer last; // ����Ʈ�� ������ ��� �ּҸ� ����ų ������
} linked_list_circular;

linked_list_circular* linked_list_circular_initialize() {
	
	// linked_list_circular�� ����ų ������ ����
	linked_list_circular* new_list;
	// new_list�� �޸� �Ҵ�
	new_list = (linked_list_circular*)malloc(sizeof(linked_list_circular));
	// �� ����Ʈ�� ó������ ��带 ������ ���� �ʴ�.
	// ����Ʈ�� last �����͸� NULL�� �Ҵ�
	new_list->last = NULL;
	return new_list;
}

// ����Ʈ�� front�� ���ο� ��带 �߰��Ѵ�.
void insert_node_front(linked_list_circular* list, bool bullet) {
	// ����Ʈ�� front�� ���� ���ο� ���
	node* new_front = node_initialize(bullet);

	// ����Ʈ�� ��尡 ���� ���
	if (list->last == NULL) {
		// ���� ����Ʈ�� ���ο� ��带 ����Ű�� �Ѵ�.
		list->last = new_front;
		// �ش� ���� �ڱ� �ڽ��� ����Ű���� �Ѵ�.
		new_front->next = new_front;
	}

	// ����Ʈ�� ��尡 �ִ� ���
	else
	{
		// ���ο� ��尡 ����Ʈ�� front ���(=���� ����Ʈ�� ������ ����� ���� ��� = list->last->next)�� ����Ű�� �Ѵ�.
		// ������ ����Ʈ�� front�� new_front�� ����Ű�Ƿ� �ι�°�� �ȴ�.
		new_front->next = list->last->next;
		// ����Ʈ�� ������ ����� ���� ���(����Ʈ�� front�� ����Ŵ)�� ���ο� ��带 ����Ű���� �Ѵ�.
		list->last->next = new_front;
	}
}

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
			printf("%d��° ĭ ���� ����? ", count++);
			printf(temp->is_loaded ? "true" : "false");
			printf("\n");
			temp = temp->next;
		} while (temp != list->last->next);
	}
}


void rotate(linked_list_circular* list) {

	//0���� 5 ������ ������ ���ڸ� �����Ѵ�.
	int random = rand() % 6;

	for (int i = 0; i < random; i++)
	{
		//����Ʈ�� ����Ű�� ��忡�� random ��ŭ �̵��Ѵ�.
		list->last = list->last->next;
	}

}

void shoot(linked_list_circular* list) {
	//����Ʈ�� ù ����� ���� ���θ� Ȯ���Ѵ�.
	bool is_loaded = list->last->next->is_loaded;
	// ���� �����Ǿ� �ִٸ� �׾��ٴ� �޽����� ������.
	if (is_loaded)
	{
		printf("You Died...\n");
	}
	else
	{
		printf("You Survived!\n");
	}
}

//-----------�� circular linked list ��-----------




int main() {

	//-----------�� ��� �ν��Ͻ� ���� ��-----------
	// ��� �ν��Ͻ��� ������ ������ ��带 ����Ű�� �����͸� �������ش�.
	// �������� �����Ϳ� ��� ��ŭ �޸𸮸� �Ҵ����ش�.

	node_pointer A;
	
	// �̶� sizeof(*A) = sizeof(node) �̴�.
	//printf("sizeof(*A) : %d\tsizeof(node) : %d", sizeof(*A), sizeof(node));
	
	A = node_initialize(true);
	
	// ����Ʈ�� ����ų ������ ����
	linked_list_circular* Revolver;
	// ����Ʈ �ʱ�ȭ
	Revolver = linked_list_circular_initialize();

	insert_node_front(Revolver, false);
	insert_node_front(Revolver, false);
	insert_node_front(Revolver, false);
	insert_node_front(Revolver, false);
	insert_node_front(Revolver, false);
	insert_node_front(Revolver, true);
	
	 // ��� �Ѿ� Ȯ��
	print_list(Revolver);

	//-----------�� ��� �ν��Ͻ� ���� ��-----------

	


	return 0;
}

