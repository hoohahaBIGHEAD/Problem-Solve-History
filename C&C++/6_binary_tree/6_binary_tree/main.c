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


////중위 순회 구현
//inorder(TreeNode node) {
//	//만약 현재 노드에 데이터가 있다면
//	if (node.data != NULL){
//		//왼쪽 노드를 방문해라.
//		inorder(*node.left);
//		//노드의 데이터를 출력해라
//		printf("%d", node.data);
//		//오른쪽 노드를 방문해라.
//		inorder(*node.right);
//	}
//}

// 중위 순회
inorder(TreeNode* root) {
	//널 포인터가 아니라면!
	if (root) {
		inorder(root->left);	// 왼쪽서브트리 순회
		printf("%d\t", root->data); 	// 노드 방문
		inorder(root->right);	// 오른쪽서브트리 순회
	}
}


/// <summary>
/// /////////////////////////
/// </summary>
int arr_odd[MAXNODENUMBER];
int arr_even[MAXNODENUMBER];
int arr_sorted[MAXNODENUMBER];
int index_odd = 0;
int index_even = 0;

int inorder_odd(TreeNode* root) {
	//널 포인터가 아니라면!
	if (root) {
		inorder_odd(root->left);	// 왼쪽서브트리 순회
		arr_odd[index_odd++] = root->data;
		inorder_odd(root->right);	// 오른쪽서브트리 순회
	}
}
int inorder_even(TreeNode* root) {
	//널 포인터가 아니라면!
	if (root) {
		inorder_even(root->left);	// 왼쪽서브트리 순회
		arr_even[index_even++] = root->data;
		inorder_even(root->right);	// 오른쪽서브트리 순회
	}
}

inorder_test(TreeNode* odd, TreeNode* even) {
	inorder_odd(odd);
	inorder_even(even);
	index_odd = 0;
	index_even = 0;
	for (int i = 0; i < MAXNODENUMBER - 1; i++)
	{
		if (arr_odd[index_odd] < arr_even[index_even])
		{
			arr_sorted[i] = arr_odd[index_odd++];
		}
		else
		{
			arr_sorted[i] = arr_even[index_even++];
		}
	}
	arr_sorted[MAXNODENUMBER-1] = 

	for (int i = 0; i < MAXNODENUMBER; i++)
	{
		printf("%d\n", arr_sorted[i]);

	}
}





int odd_s, even_s;
//5. 중위순회하는 알고리즘을 참고하여 두 개의 짝수 및 홀수 이진탐색트리를 동시에 오름차순으로 순회하는 알고리즘을 작성하라.(결과는 전체의 오름차순 정렬 값) 
// 중위 순회 전체
inorder_whole(TreeNode* root1, TreeNode* root2) {
	//널 포인터가 아니라면!
	if (root1) {
		//inorder_whole(root1->left, root2);	// 왼쪽서브트리 순회
		odd_s = root1->data;
		even_s = root2->data;
		if (odd_s < even_s) {
			inorder_whole(root1->left, root2);	// 왼쪽서브트리 순회
			printf("%d\t", root1->data); 	// 노드 방문
		}
		else
		{
			inorder_whole(root1, root2->left);	// 왼쪽서브트리 순회
			printf("%d\t", root2->data); 	// 노드 방문
		}
		inorder_whole(root1->right, root2);	// 오른쪽서브트리 순회
	}
}

/*
//처음 temp는 100으로 시작. 한쪽트리 반대쪽 트리 왔다갔다로 하자
//1. 한쪽 트리 왼쪽으로 계속 이동. 널을 만날 때까지.
//널을 만났다? 일단 그냥 나와라. 그럼 바로 아래줄이 실행된다.
//템프에 현재의 노드를 집어넣자.
inorder_whole_tempte(TreeNode* root_in, TreeNode* root_wait, int temp) {
	//널 포인터가 아니라면!
	if (root_in) {
		printf("\n현재 NULL 포인터가 아니다. 데이터 : %d, temp : %d\n", root_in->data, temp);
		printf("왼쪽 노드가 NULL인지 확인한다.\n");
		if (root_in->left != NULL) printf("안 빈 왼쪽 %d를 가진 노드로 이동\n", root_in->left->data);
		else printf("빈 왼쪽 노드로 이동\n");
		inorder_whole_temp(root_in->left, root_wait, temp);	// 왼쪽서브트리 순회
		printf("널에서 나왔다. 지금 가진 %d와 현재 노드의 데이터 %d를 비교한다.\n", temp, root_in->data);
		if (temp < root_in->data) {
			printf("지금 가진 %d보다 노드의 데이터 %d가 커 %d를 가지고 작은 것을 출력한다.\n", temp, root_in->data, root_in->data);
			printf("%d\n", temp); 	// 노드 방문
			temp = root_in->data;
			printf("반대쪽 데이터가 널인지 아닌지 확인한다.\n");
			if (root_wait->data != NULL) {
				printf("반대쪽이 널이 아니다. %d를 가지고 반대쪽 트리의 널이 아닌 노드값 %d로 이동한다.\n", temp, root_wait->data);
				inorder_whole_temp(root_wait, root_in, temp);	// 반대트리 호출
			} else printf("반대쪽이 널이다. 그냥 넘어간다.\n"); 
		}
		else
		{
			printf("지금 가진 %d보다 노드의 데이터 %d가 작다. 작은 것을 출력한다.\n", temp, root_in->data);
			printf("%d\n", root_in->data); 	// 노드 방문
		}
		printf("\n현재 NULL 포인터가 아니다. 데이터 : %d, temp : %d\n", root_in->data, temp);
		printf("오른쪽 노드가 NULL인지 확인한다.\n");
		if (root_in->right != NULL) printf("안 빈 오른쪽 %d를 가진 노드로 이동\n", root_in->left->data);
		else printf("빈 오른쪽 노드로 이동\n");
		inorder_whole_temp(root_in->right, root_wait, temp);	// 오른쪽서브트리 순회
	}
	else
	{
		printf("널을 만났다. 지금 %d를 가지고 있다. 나온다.\n", temp);
	}

}
*/

int temp = -1;
inorder_whole_temp(TreeNode* root_in, TreeNode* root_wait, boolean passed) {
	//널 포인터가 아니라면!
	if (root_in->left != NULL)
		inorder_whole_temp(root_in->left, root_wait, temp, FALSE);	// 왼쪽서브트리 순회

	//가진 값이 방문 노드값보다 작다면
	if (temp < root_in->data) {
		//반대쪽 체크했는지 확인해라.
		//확인했다면 출력하고
		if (passed) {
			printf("%d\n", root_in->data); 	// 노드 방문
			temp = root_in->data;
			//return;
		}
		//확인하지 않았다면 반대로 이동해라
		else
		{
			inorder_whole_temp(root_wait, root_in, temp, TRUE);	// 반대편 트리로 이동
		}
	}
	//가진 값이 방문 노드값보다 크다면
	else
	{
	//	return;
	}
	if (root_in->right != NULL)
		inorder_whole_temp(root_in->right, root_wait, temp, FALSE);	// 오른쪽서브트리 순회
}






//
//// 중위 순회 홀수용
//int inorder_odd(TreeNode* odd) {
//	if (odd) {
//		inorder(odd->left);	// 왼쪽서브트리 순회
//		odd_s = odd->data;
//		//홀수가 작다면 출력하고
//		if (odd_s < even_s) {
//			printf("%d\t", odd_s); 	// 노드 방문
//		}
//		//짝수가 작다면 짝수를 출력해라
//		else
//		{
//
//		}
//		inorder(odd->right);	// 오른쪽서브트리 순회
//	}
//}
//// 중위 순회 짝수용
//inorder_even(TreeNode* even) {
//	if (even) {
//		inorder(even->left);	// 왼쪽서브트리 순회
//		even_s = even->data;
//		inorder(even->right);	// 오른쪽서브트리 순회
//	}
//}


// 노드를 생성하고 리턴해주는 함수
TreeNode* new_node(int data) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, int data){
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
		temp[i] = rand()%101 + 1;

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
	//inorder_whole_temp( tree_even, tree_odd, FALSE);
	//inorder_test(tree_even, tree_odd);
	inorder_test(tree_odd, tree_even);
	return 0;
}