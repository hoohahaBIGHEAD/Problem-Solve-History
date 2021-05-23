#include <stdio.h>
#include <stdlib.h>

#define MAXNODENUMBER 6

typedef enum _boolean {
	FALSE,
	TRUE
} boolean;

#define FALSE 0
#define TRUE 1

//��� ����ü ǥ��
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

// ���� ��ȸ
void inorder(TreeNode* root) {
	//�� �����Ͱ� �ƴ϶��!
	if (root) {
		inorder(root->left);	// ���ʼ���Ʈ�� ��ȸ
		printf("%d\t", root->data); 	// ��� �湮
		inorder(root->right);	// �����ʼ���Ʈ�� ��ȸ
	}
}

/// <summary>
/// 5. ������ȸ�ϴ� �˰����� �����Ͽ� �� ���� ¦�� �� Ȧ�� ����Ž��Ʈ���� ���ÿ� ������������ ��ȸ�ϴ� �˰����� �ۼ��϶�.(����� ��ü�� �������� ���� ��) 
/// </summary>
int arr_odd[MAXNODENUMBER];
int arr_even[MAXNODENUMBER];
int arr_sorted[MAXNODENUMBER];
int index_odd = 0;
int index_even = 0;

void inorder_odd(TreeNode* root) {
	//�� �����Ͱ� �ƴ϶��!
	if (root) {
		inorder_odd(root->left);	// ���ʼ���Ʈ�� ��ȸ
		arr_odd[index_odd++] = root->data;
		inorder_odd(root->right);	// �����ʼ���Ʈ�� ��ȸ
	}
}
void inorder_even(TreeNode* root) {
	//�� �����Ͱ� �ƴ϶��!
	if (root) {
		inorder_even(root->left);	// ���ʼ���Ʈ�� ��ȸ
		arr_even[index_even++] = root->data;
		inorder_even(root->right);	// �����ʼ���Ʈ�� ��ȸ
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
	/// 6. �� ���� ����Ž��Ʈ���� ��ȸ�ϴ� �Լ��� ���������� �۵� �Ǵ��� Ȯ���ϱ� ���Ͽ� ����� ����ϵ��� �Ѵ�.
	/// </summary>
	for (int i = 0; i < MAXNODENUMBER; i++)
	{
		printf("%d\n", arr_sorted[i]);

	}
}
/// <summary>
/// 5. ������ȸ�ϴ� �˰����� �����Ͽ� �� ���� ¦�� �� Ȧ�� ����Ž��Ʈ���� ���ÿ� ������������ ��ȸ�ϴ� �˰����� �ۼ��϶�.(����� ��ü�� �������� ���� ��) 
/// </summary>



// ��带 �����ϰ� �������ִ� �Լ�
TreeNode* new_node(int data) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, int data) {
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�. 
	if (node == NULL) return new_node(data);

	// �׷��� ������ ��ȯ������ Ʈ���� ��������. 
	// ���ĵ� ���� ����
	if (data < node->data)	//���� ���� ������ ����� �����Ͱ� ���� �湮�� ����� �����ͺ��� �۴ٸ� �湮�� ����� ���ʿ� �����Ѵ�.
		node->left = insert_node(node->left, data);
	else if (data > node->data)	//���� ���� ������ ����� �����Ͱ� ���� �湮�� ����� �����ͺ��� ũ�ٸ� �湮�� ����� �����ʿ� �����Ѵ�.
		node->right = insert_node(node->right, data);

	// ����� ��Ʈ �����͸� ��ȯ�Ѵ�. 
	return node;
}

int main() {

	//1. ����Ž��Ʈ���� ���԰� ������ ������ �ڵ带 å�� �����Ͽ� �ۼ��ϰ� 2���� ����Ž��Ʈ���� �����.
	TreeNode* tree_even = NULL;
	TreeNode* tree_odd = NULL;

	//2. 1���� 100������ ���� ���� ���� ���� ���� n(���Ƿ� ����)���� �����Ѵ�. 
	//���� �� �迭�� �������־���.
	int temp[MAXNODENUMBER];
	for (int i = 0; i < MAXNODENUMBER; i++)
		temp[i] = rand() % 101 + 1;

	for (int i = 0; i < MAXNODENUMBER; i++) {
		if (i % 10 == 0)
			printf("\n");
		printf("%d\t", temp[i]);

	}

	//3. n���� ���� �߿��� ¦�� ���� ���� ��� ¦�� ����Ž��Ʈ���� �����ϰ�, ȫ�� ���� ���� ��� Ȧ�� ����Ž��Ʈ���� �����ϵ��� �Ѵ�.
	for (int i = 0; i < MAXNODENUMBER; i++)
	{
		//¦����� tree_even �� �����ϰ�
		if (temp[i] % 2 == 0) {
			tree_even = insert_node(tree_even, temp[i]);
		}
		//Ȧ����� tree_odd �� �����ϰ�
		else
		{
			tree_odd = insert_node(tree_odd, temp[i]);
		}
	}

	//4. ��� ���� ������ ����Ǹ� ¦�� ���� Ʈ���� Ȧ�� ���� Ʈ���� �ٸ��� �����Ǿ����� Ȯ���ϱ� ���Ͽ� ���� ��ȸ�� �����Ͽ� ���� ����ϵ��� �Ѵ�.
	printf("\n");
	inorder(tree_even);
	printf("\n");
	inorder(tree_odd);
	printf("\n");
	//5. ������ȸ�ϴ� �˰����� �����Ͽ� �� ���� ¦�� �� Ȧ�� ����Ž��Ʈ���� ���ÿ� ������������ ��ȸ�ϴ� �˰����� �ۼ��϶�.(����� ��ü�� �������� ���� ��) 
	//6. �� ���� ����Ž��Ʈ���� ��ȸ�ϴ� �Լ��� ���������� �۵� �Ǵ��� Ȯ���ϱ� ���Ͽ� ����� ����ϵ��� �Ѵ�.
	inorder_test(tree_odd, tree_even);
	return 0;
}