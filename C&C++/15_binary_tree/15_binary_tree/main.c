#include <stdio.h>
#include <string.h>

#define MAX_STR_SIZE 128

struct node {
	char* key;
	struct node* left;
	struct node* right;
} node;

// ��� ����
struct node* newNode(char* key) {
	// �޸� �Ҵ�
	struct node* node = (struct node*)malloc(sizeof(struct node));
	//���ڿ� ���� + 1��ŭ �޸� �Ҵ�(���ڿ� �� NULL �����)
	char* newKey = malloc(sizeof(char) * (strlen(key)+1));
	//char* newKey = malloc(sizeof(char) * MAX_STR_SIZE);
	// ������ ���� �� ����
	strcpy_s(newKey, (strlen(key) + 1), key);
	//strcpy_s(newKey, MAX_STR_SIZE, key);
	node->key = newKey;

	// ������ �ʱ�ȭ
	node->left = NULL;
	node->right = NULL;
	
	//������ ��� ����
	return (node);
}

// ��� ����
struct node* InsertNode(struct node* node, char* key) {
	// ���� ���� �湮�� ��尡 NULL �̶�� �� ��带 �����ϰ� �����϶�
	if (node == NULL)
		return newNode(key);

	int ret = strcmp(key, node->key);    // �Էµ� ���ڿ� ��
	//���� ������ ����� ���ĺ� ������ ���� �湮�� ��庸�� ���̶�� �湮�� ����� ���ʿ� �����Ѵ�.
	switch (ret)
	{
	case 0:
		printf("�Է��� ���ڿ��� �̹� �ֽ��ϴ�.\n");
		break;
	case 1:
		node->right = InsertNode(node->right, key);
		break;
	case -1:
		node->left = InsertNode(node->left, key);
		break;
	}

	return node;
}

void Inorder(struct node* node) {
	//�� �����Ͱ� �ƴ϶��!
	if (node) {
		Inorder(node->left);	// ���ʼ���Ʈ�� ��ȸ
		printf("%s\n", node->key);
		Inorder(node->right);	// �����ʼ���Ʈ�� ��ȸ
	}
}

int main() {

	// ���� ����ü�� �����ϰ� �̸� ����ϰ��� �ϸ� struct �� �տ� ����� �Ѵ�.
	struct node* tree = NULL;
	char COMMAND[MAX_STR_SIZE];
	char KEY[MAX_STR_SIZE];
	char* keyTemp;
	for (;;) {
		printf("��ɾ �Է��ϼ���.\n");
		printf("INSERT : (ex. INSERT abcd)\n");
		printf("SEARCH : (ex. SEARCH abcd)\n");
		printf("DELETE : (ex. DELETE abcd)\n");
		printf("VIEWALL : (ex. VIEWALL)\n");
		printf("QUIT : (ex. QUIT)\n");
		printf("=============================\n");
		scanf_s("%s", COMMAND, MAX_STR_SIZE);
	
		if (strcmp(COMMAND, "VIEWALL") == 0)
		{
			//VIEWALL
			printf("VIEWALL\n");
			Inorder(tree);
		}
		// QUIT �� �Է� ������ ���α׷��� �����Ѵ�.
		else if (strcmp(COMMAND, "QUIT") == 0)
		{
			printf("QUIT\n");
			break;
		}
		else {
			scanf_s("%s", KEY, MAX_STR_SIZE);
			if (strcmp(COMMAND, "INSERT") == 0)
			{
				printf("INSERT %s\n", KEY);
				tree = InsertNode(tree, KEY);
			}
			else if (strcmp(COMMAND, "SEARCH") == 0)
			{
				printf("SEARCH %s\n", KEY);

			}
			else if (strcmp(COMMAND, "DELETE") == 0)
			{
				printf("DELETE %s\n", KEY);

			}
			else
			{
				printf("�߸��� �Է��Դϴ�.\n");
			}

		}


	}


	return 0;
}