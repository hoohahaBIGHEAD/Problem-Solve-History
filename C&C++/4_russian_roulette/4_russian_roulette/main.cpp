//-----------�� add_comment_here ��-----------
//-----------�� add_comment_here ��-----------

#include <iostream>
#include <time.h>
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


//-----------�� �Ҹ� Ȯ�ο� ��-----------
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
//-----------�� �Ҹ� Ȯ�ο� ��-----------

//-----------�� �޸� �Ҵ� ���� ��-----------
/* Function to traverse a given Circular linked list and print nodes */
void print_list(linked_list_circular* list) {
	
	node* temp;
	temp = list->last;
	//���� ���� last �̵�
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
//-----------�� �Ҹ� Ȯ�ο� ��-----------


//Conditions: ��rotate�� means that Revolver��s head moves to the next node by a random number.
//Conditions: After ��rotate�� clean the screen using ��system(��cls��)��.
void rotate(linked_list_circular* list) {

	//���� �õ� �ʱ�ȭ
	srand(time(NULL));

	//0���� 5 ������ ������ ���ڸ� �����Ѵ�.
	int random = rand() % 6;

	for (int i = 0; i < random; i++)
	{
		//����Ʈ�� ����Ű�� ��忡�� random ��ŭ �̵��Ѵ�.
		list->last = list->last->next;
	}

	
}
//�䱸���� 4. If receive ��shoot�� command 
bool shoot(linked_list_circular* list) {
	//�䱸���� 4. then check the bullet, 
	//Conditions: The ��shoot�� command checks Revolver��s head and moves the head to the next node.
	//����Ʈ�� ��� ����� ���� ���θ� Ȯ���Ѵ�.
	bool is_loaded = list->last->next->is_loaded;

	//if exists, then print ��You Died���� and program end.
	// ���� �����Ǿ� �ִٸ� �׾��ٴ� �޽����� ������ ������ �����Ѵ�.
	// �̶� shoot �� false�� �����ϰ� main �� while ���� ����ȴ�.
	if (is_loaded)
	{
		printf("You Died...\n");
		//�� ������ ���۵ǵ��� list�� rotate�Ѵ�.
		rotate(list);
		return false;
	}
	//�䱸���� 5. If not exists, then print ��You Survived!�� and repeat 3.
	else
	{
		printf("You Survived!\n");
		//Conditions: moves the head to the next node.
		// ����Ʈ�� ��带 �� ĭ �̵��Ѵ�.
		list->last = list->last->next;
		return true;
	}
}

//-----------�� circular linked list ��-----------


int main() {

	//-----------�� ��� �ν��Ͻ� ���� ��-----------
	/* ��� ���� ����
	
	// ��� �ν��Ͻ��� ������ ������ ��带 ����Ű�� �����͸� �������ش�.
	// �������� �����Ϳ� ��� ��ŭ �޸𸮸� �Ҵ����ش�.

	node_pointer A;
	
	// �̶� sizeof(*A) = sizeof(node) �̴�.
	//printf("sizeof(*A) : %d\tsizeof(node) : %d", sizeof(*A), sizeof(node));
	
	A = node_initialize(true);

	*/
	string command;


	//�䱸���� 1. Create a Revolver, which is circular linked list.
	linked_list_circular* Revolver;
	Revolver = linked_list_circular_initialize();

	//�䱸���� 2. Insert one bullet to Revolver and ��rotate��.
	//Conditions: Revolver is connected to 6 nodes, which are created in Revolver��s constructor.
	insert_node_front(Revolver, false);
	insert_node_front(Revolver, false);
	insert_node_front(Revolver, false);
	insert_node_front(Revolver, false);
	insert_node_front(Revolver, false);
	insert_node_front(Revolver, true);
	rotate(Revolver);


	//�䱸���� 5. repeat 3.
	//������ 3�� ����
	int is_survived = true;
	for (int i = 0; i < 3; i++)
	{
		is_survived = true;
		// ��� �Ѿ� Ȯ��
		//print_list(Revolver);
		// printf("���� %dȸ��\n", i+1);
		
		//�䱸���� 3. ��shoot�� / ��rotate�� command to shoot or rotate.
		printf("Command list(shoot/rotate)\n");
		while (is_survived)
		{
			cout << "CMD>> ";
			cin >> command;
			//* Assume that there is no input of the same word with different case >> string ������ == �����ڴ� ��ҹ��ڰ� �ٸ��� �ٸ� ����� �ν��Ѵ�.
			if (command == "rotate") {
				rotate(Revolver);
				//Conditions: After ��rotate�� clean the screen using ��system(��cls��)��.
				system("cls");
				printf("Command list(shoot/rotate)\n");
			}
			// �䱸���� 4. If receive ��shoot�� command then check the bullet, if exists, then print ��You Died���� and program end.
			else if (command == "shoot")
			{
				is_survived = shoot(Revolver);
			}
			//* Handle exceptions for possible exceptions >> string �Է¿� �� �� Ŀ�ǵ带 �����ϸ� "Wrong Command!"�� ��µǵ��� ��
			else
			{
				printf("Wrong Command!\n");
			}
		}
		
	}

	//-----------�� ��� �ν��Ͻ� ���� ��-----------

	//* If dynamic allocation is not deallocated, you will have -0.2 point penalty for each task
	

	return 0;
}

