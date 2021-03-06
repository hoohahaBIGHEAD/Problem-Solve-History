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
//// 노드 생성
//struct node* newNode(char* key) {
//	// 메모리 할당
//	struct node* node = (struct node*)malloc(sizeof(struct node));
//	//문자열 길이 + 1만큼 메모리 할당(문자열 끝 NULL 저장용)
//	char* newKey = malloc(sizeof(char) * (strlen(key)+1));
//	//char* newKey = malloc(sizeof(char) * MAX_STR_SIZE);
//	// 데이터 복사 후 저장
//	strcpy_s(newKey, (strlen(key) + 1), key);
//	//strcpy_s(newKey, MAX_STR_SIZE, key);
//	node->key = newKey;
//
//	// 포인터 초기화
//	node->left = NULL;
//	node->right = NULL;
//	
//	//생성한 노드 리턴
//	return (node);
//}
//
//// 노드 삽입
//struct node* InsertNode(struct node* node, char* key) {
//	// 만약 현재 방문한 노드가 NULL 이라면 새 노드를 생성하고 리턴하라
//	if (node == NULL)
//		return newNode(key);
//
//	int ret = strcmp(key, node->key);    // 입력된 문자열 비교
//	//새로 생성할 노드의 알파벳 순서가 지금 방문한 노드보다 앞이라면 방문한 노드의 왼쪽에 삽입한다.
//	switch (ret)
//	{
//	case 0:
//		printf("입력한 문자열이 이미 있습니다.\n");
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
//// 노드 삭제
//struct node* DeleteNode(struct node* node, char* key) {
//	if (node == NULL)
//		return NULL;
//
//	int ret = strcmp(key, node->key);    // 입력된 문자열 비교
//	//삭제할 노드의 알파벳 순서가 지금 방문한 노드보다 앞이라면 방문한 노드의 왼쪽으로 이동한다.
//	switch (ret)
//	{
//	case 0:
//		// 자식이 없는 경우
//		if (node->left == NULL && node->right == NULL)
//		{
//			free(node);
//		}
//		
//		printf("노드를 삭제했습니다.\n");
//		break;
//	case 1:
//		node->right = DeleteNode(node->right, key);
//		break;
//	case -1:
//		node->left = DeleteNode(node->left, key);
//		break;
//	}
//
//	printf("노드가 없습니다.\n");
//	return node;
//}
//
//void InorderView(struct node* node) {
//	//널 포인터가 아니라면!
//	if (node) {
//		InorderView(node->left);	// 왼쪽서브트리 순회
//		printf("%s\n", node->key);
//		InorderView(node->right);	// 오른쪽서브트리 순회
//	}
//}
//
//struct node* ReturnRight(struct node* node) {
//	//널 포인터가 아니라면!
//	if (node) {
//		ReturnRight(node->left);	// 왼쪽서브트리 순회
//		ReturnRight(node->right);	// 오른쪽서브트리 순회
//		return node;
//	}
//	else
//	{
//		printf("노드가 없습니다.\n");
//	}
//}
//
//int main() {
//
//	// 위에 구조체를 정의하고 이를 사용하고자 하면 struct 를 앞에 써줘야 한다.
//	struct node* tree = NULL;
//	char COMMAND[MAX_STR_SIZE];
//	char KEY[MAX_STR_SIZE];
//	char* keyTemp;
//	for (;;) {
//		/*
//		printf("명령어를 입력하세요.\n");
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
//		// QUIT 를 입력 받으면 프로그램을 종료한다.
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
//				printf("잘못된 입력입니다.\n");
//			}
//
//		}
//		*/
//		printf("명령어를 입력하세요.\n");
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