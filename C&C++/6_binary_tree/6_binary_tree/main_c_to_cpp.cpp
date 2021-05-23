#include <stdio.h>
#include <stdlib.h>

#define MAXNODENUMBER 6

typedef enum _boolean {
	FALSE,
	TRUE
} boolean;

#define FALSE 0
#define TRUE 1

//노드 구조체 표현
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

// 중위 순회
void inorder(TreeNode* root) {
	//널 포인터가 아니라면!
	if (root) {
		inorder(root->left);	// 왼쪽서브트리 순회
		printf("%d\t", root->data); 	// 노드 방문
		inorder(root->right);	// 오른쪽서브트리 순회
	}
}

/// <summary>
/// 5. 중위순회하는 알고리즘을 참고하여 두 개의 짝수 및 홀수 이진탐색트리를 동시에 오름차순으로 순회하는 알고리즘을 작성하라.(결과는 전체의 오름차순 정렬 값) 
/// </summary>
int arr_odd[MAXNODENUMBER];
int arr_even[MAXNODENUMBER];
int arr_sorted[MAXNODENUMBER];
int index_odd = 0;
int index_even = 0;

void inorder_odd(TreeNode* root) {
	//널 포인터가 아니라면!
	if (root) {
		inorder_odd(root->left);	// 왼쪽서브트리 순회
		arr_odd[index_odd++] = root->data;
		inorder_odd(root->right);	// 오른쪽서브트리 순회
	}
}
void inorder_even(TreeNode* root) {
	//널 포인터가 아니라면!
	if (root) {
		inorder_even(root->left);	// 왼쪽서브트리 순회
		arr_even[index_even++] = root->data;
		inorder_even(root->right);	// 오른쪽서브트리 순회
	}
}

void inorder_test(TreeNode* odd, TreeNode* even) {
	inorder_odd(odd);
	inorder_even(even);
	index_odd = 0;
	index_even = 0;
	for (int i = 0; i < MAXNODENUMBER; i++)
	{
		if (arr_odd[index_odd] == 0)
		{
			arr_sorted[i] = arr_even[index_even++];
		}
		else if (arr_even[index_even] == 0)
		{
			arr_sorted[i] = arr_odd[index_odd++];
		}
		else if (arr_odd[index_odd] < arr_even[index_even])
		{
			arr_sorted[i] = arr_odd[index_odd++];
		}
		else
		{
			arr_sorted[i] = arr_even[index_even++];
		}
	}
	/// <summary>
	/// 6. 두 개의 이진탐색트리를 순회하는 함수가 정상적으로 작동 되는지 확인하기 위하여 결과를 출력하도록 한다.
	/// </summary>
	for (int i = 0; i < MAXNODENUMBER; i++)
	{
		printf("%d\n", arr_sorted[i]);

	}
}
/// <summary>
/// 5. 중위순회하는 알고리즘을 참고하여 두 개의 짝수 및 홀수 이진탐색트리를 동시에 오름차순으로 순회하는 알고리즘을 작성하라.(결과는 전체의 오름차순 정렬 값) 
/// </summary>



// 노드를 생성하고 리턴해주는 함수
TreeNode* new_node(int data) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, int data) {
	// 트리가 공백이면 새로운 노드를 반환한다. 
	if (node == NULL) return new_node(data);

	// 그렇지 않으면 순환적으로 트리를 내려간다. 
	// 정렬도 같이 수행
	if (data < node->data)	//만약 새로 생성할 노드의 데이터가 지금 방문한 노드의 데이터보다 작다면 방문한 노드의 왼쪽에 삽입한다.
		node->left = insert_node(node->left, data);
	else if (data > node->data)	//만약 새로 생성할 노드의 데이터가 지금 방문한 노드의 데이터보다 크다면 방문한 노드의 오른쪽에 삽입한다.
		node->right = insert_node(node->right, data);

	// 변경된 루트 포인터를 반환한다. 
	return node;
}

int main() {

	//1. 이진탐색트리의 삽입과 삭제를 포함한 코드를 책을 참조하여 작성하고 2개의 이진탐색트리를 만든다.
	TreeNode* tree_even = NULL;
	TreeNode* tree_odd = NULL;

	//2. 1에서 100사이의 양의 정수 값을 갖는 난수 n(임의로 정함)개를 생성한다. 
	//생성 후 배열에 저장해주었다.
	int temp[MAXNODENUMBER];
	for (int i = 0; i < MAXNODENUMBER; i++)
		temp[i] = rand() % 101 + 1;

	for (int i = 0; i < MAXNODENUMBER; i++) {
		if (i % 10 == 0)
			printf("\n");
		printf("%d\t", temp[i]);

	}

	//3. n개의 값들 중에서 짝수 값을 가질 경우 짝수 이진탐색트리에 삽입하고, 홍수 값을 가질 경우 홀수 이진탐색트리에 삽입하도록 한다.
	for (int i = 0; i < MAXNODENUMBER; i++)
	{
		//짝수라면 tree_even 에 삽입하고
		if (temp[i] % 2 == 0) {
			tree_even = insert_node(tree_even, temp[i]);
		}
		//홀수라면 tree_odd 에 삽입하고
		else
		{
			tree_odd = insert_node(tree_odd, temp[i]);
		}
	}

	//4. 모든 값의 삽입이 종료되면 짝수 이진 트리와 홀수 이진 트리가 바르게 구성되었는지 확인하기 위하여 중위 순회를 수행하여 각각 출력하도록 한다.
	printf("\n");
	inorder(tree_even);
	printf("\n");
	inorder(tree_odd);
	printf("\n");
	//5. 중위순회하는 알고리즘을 참고하여 두 개의 짝수 및 홀수 이진탐색트리를 동시에 오름차순으로 순회하는 알고리즘을 작성하라.(결과는 전체의 오름차순 정렬 값) 
	//6. 두 개의 이진탐색트리를 순회하는 함수가 정상적으로 작동 되는지 확인하기 위하여 결과를 출력하도록 한다.
	inorder_test(tree_odd, tree_even);
	return 0;
}