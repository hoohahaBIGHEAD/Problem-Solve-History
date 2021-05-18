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
node* node_initialize() {
	// ���ο� ����� �޸𸮸� �� ������ �Ҵ�
	node* new_node = (node*)malloc(sizeof(node));
	// ����� ������ �� ������ �Ҵ�
	// ����� is_loaded�� ó�� false�� �Ҵ�
	new_node->is_loaded = false;

	// ����� �����͸� ����
	new_node->next= NULL;

	// �޸𸮰� �Ҵ�� ���ο� ��带 node_pointer ������ ����
	return new_node;
}

//-----------�� Dynamic allocation of a node ��-----------

int main() {

	//-----------�� ��� �ν��Ͻ� ���� ��-----------
	// ��� �ν��Ͻ��� ������ ������ ��带 ����Ű�� �����͸� �������ش�.
	// �������� �����Ϳ� ��� ��ŭ �޸𸮸� �Ҵ����ش�.

	node_pointer A;
	
	// �̶� sizeof(*A) = sizeof(node) �̴�.
	//printf("sizeof(*A) : %d\tsizeof(node) : %d", sizeof(*A), sizeof(node));
	
	A = node_initialize();
	


	//-----------�� ��� �ν��Ͻ� ���� ��-----------

	return 0;
}