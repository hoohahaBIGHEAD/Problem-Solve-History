//#include <stdio.h>
//#include <string.h>
//
//#define MAX_STR_SIZE 128
//
//struct node {
//	char* key;
//	struct node* left;
//	struct node* right;
//} node;
//
//// ��� ����
//struct node* newNode(char* key) {
//	// �޸� �Ҵ�
//	struct node* node = (struct node*)malloc(sizeof(struct node));
//	//���ڿ� ���� + 1��ŭ �޸� �Ҵ�(���ڿ� �� NULL �����)
//	char* newKey = malloc(sizeof(char) * (strlen(key)+1));
//	//char* newKey = malloc(sizeof(char) * MAX_STR_SIZE);
//	// ������ ���� �� ����
//	strcpy_s(newKey, (strlen(key) + 1), key);
//	//strcpy_s(newKey, MAX_STR_SIZE, key);
//	node->key = newKey;
//
//	// ������ �ʱ�ȭ
//	node->left = NULL;
//	node->right = NULL;
//	
//	//������ ��� ����
//	return (node);
//}
//
//// ��� ����
//struct node* InsertNode(struct node* node, char* key) {
//	// ���� ���� �湮�� ��尡 NULL �̶�� �� ��带 �����ϰ� �����϶�
//	if (node == NULL)
//		return newNode(key);
//
//	int ret = strcmp(key, node->key);    // �Էµ� ���ڿ� ��
//	//���� ������ ����� ���ĺ� ������ ���� �湮�� ��庸�� ���̶�� �湮�� ����� ���ʿ� �����Ѵ�.
//	switch (ret)
//	{
//	case 0:
//		printf("�Է��� ���ڿ��� �̹� �ֽ��ϴ�.\n");
//		break;
//	case 1:
//		node->right = InsertNode(node->right, key);
//		break;
//	case -1:
//		node->left = InsertNode(node->left, key);
//		break;
//	}
//
//	return node;
//}
//
//// ��� ����
//struct node* DeleteNode(struct node* node, char* key) {
//	if (node == NULL)
//		return NULL;
//
//	int ret = strcmp(key, node->key);    // �Էµ� ���ڿ� ��
//	//������ ����� ���ĺ� ������ ���� �湮�� ��庸�� ���̶�� �湮�� ����� �������� �̵��Ѵ�.
//	switch (ret)
//	{
//	case 0:
//		// �ڽ��� ���� ���
//		if (node->left == NULL && node->right == NULL)
//		{
//			free(node);
//		}
//		
//		printf("��带 �����߽��ϴ�.\n");
//		break;
//	case 1:
//		node->right = DeleteNode(node->right, key);
//		break;
//	case -1:
//		node->left = DeleteNode(node->left, key);
//		break;
//	}
//
//	printf("��尡 �����ϴ�.\n");
//	return node;
//}
//
//void InorderView(struct node* node) {
//	//�� �����Ͱ� �ƴ϶��!
//	if (node) {
//		InorderView(node->left);	// ���ʼ���Ʈ�� ��ȸ
//		printf("%s\n", node->key);
//		InorderView(node->right);	// �����ʼ���Ʈ�� ��ȸ
//	}
//}
//
//struct node* ReturnRight(struct node* node) {
//	//�� �����Ͱ� �ƴ϶��!
//	if (node) {
//		ReturnRight(node->left);	// ���ʼ���Ʈ�� ��ȸ
//		ReturnRight(node->right);	// �����ʼ���Ʈ�� ��ȸ
//		return node;
//	}
//	else
//	{
//		printf("��尡 �����ϴ�.\n");
//	}
//}
//
//int main() {
//
//	// ���� ����ü�� �����ϰ� �̸� ����ϰ��� �ϸ� struct �� �տ� ����� �Ѵ�.
//	struct node* tree = NULL;
//	char COMMAND[MAX_STR_SIZE];
//	char KEY[MAX_STR_SIZE];
//	char* keyTemp;
//	for (;;) {
//		/*
//		printf("��ɾ �Է��ϼ���.\n");
//		printf("INSERT : (ex. INSERT abcd)\n");
//		printf("SEARCH : (ex. SEARCH abcd)\n");
//		printf("DELETE : (ex. DELETE abcd)\n");
//		printf("VIEWALL : (ex. VIEWALL)\n");
//		printf("QUIT : (ex. QUIT)\n");
//		printf("=============================\n");
//		scanf_s("%s", COMMAND, MAX_STR_SIZE);
//	
//		if (strcmp(COMMAND, "VIEWALL") == 0)
//		{
//			//VIEWALL
//			printf("VIEWALL\n");
//			InorderView(tree);
//		}
//		// QUIT �� �Է� ������ ���α׷��� �����Ѵ�.
//		else if (strcmp(COMMAND, "QUIT") == 0)
//		{
//			printf("QUIT\n");
//			break;
//		}
//		else {
//			scanf_s("%s", KEY, MAX_STR_SIZE);
//			if (strcmp(COMMAND, "INSERT") == 0)
//			{
//				printf("INSERT %s\n", KEY);
//				tree = InsertNode(tree, KEY);
//			}
//			else if (strcmp(COMMAND, "SEARCH") == 0)
//			{
//				printf("SEARCH %s\n", KEY);
//
//			}
//			else if (strcmp(COMMAND, "DELETE") == 0)
//			{
//				printf("DELETE %s\n", KEY);
//
//			}
//			else
//			{
//				printf("�߸��� �Է��Դϴ�.\n");
//			}
//
//		}
//		*/
//		printf("��ɾ �Է��ϼ���.\n");
//		printf("INSERT : (ex. 1 abcd)\n");
//		printf("SEARCH : (ex. 2 abcd)\n");
//		printf("DELETE : (ex. 3 abcd)\n");
//		printf("VIEWALL : (ex. 4)\n");
//		printf("QUIT : (ex. 5)\n");
//		printf("=============================\n");
//		int menuIndex = 0;
//		scanf_s("%d", &menuIndex, MAX_STR_SIZE);
//		switch (menuIndex)
//		{
//		case 1:
//			scanf_s("%s", KEY, MAX_STR_SIZE);
//			printf("INSERT %s\n", KEY);
//			tree = InsertNode(tree, KEY);
//			break; 
//		case 2:
//			printf("SEARCH %s\n", KEY);
//			scanf_s("%s", KEY, MAX_STR_SIZE);
//			break;
//		case 3:
//			printf("DELETE %s\n", KEY);
//			scanf_s("%s", KEY, MAX_STR_SIZE);
//			break;
//		case 4:
//			//VIEWALL
//			printf("VIEWALL\n");
//			InorderView(tree);
//			break;
//		case 5:
//			printf("QUIT\n");
//			break;
//		default:
//			break;
//		}
//		
//
//
//	}
//
//
//	return 0;
//}