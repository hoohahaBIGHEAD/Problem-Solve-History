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


////���� ��ȸ ����
//inorder(TreeNode node) {
//	//���� ���� ��忡 �����Ͱ� �ִٸ�
//	if (node.data != NULL){
//		//���� ��带 �湮�ض�.
//		inorder(*node.left);
//		//����� �����͸� ����ض�
//		printf("%d", node.data);
//		//������ ��带 �湮�ض�.
//		inorder(*node.right);
//	}
//}

// ���� ��ȸ
inorder(TreeNode* root) {
	//�� �����Ͱ� �ƴ϶��!
	if (root) {
		inorder(root->left);	// ���ʼ���Ʈ�� ��ȸ
		printf("%d\t", root->data); 	// ��� �湮
		inorder(root->right);	// �����ʼ���Ʈ�� ��ȸ
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
	//�� �����Ͱ� �ƴ϶��!
	if (root) {
		inorder_odd(root->left);	// ���ʼ���Ʈ�� ��ȸ
		arr_odd[index_odd++] = root->data;
		inorder_odd(root->right);	// �����ʼ���Ʈ�� ��ȸ
	}
}
int inorder_even(TreeNode* root) {
	//�� �����Ͱ� �ƴ϶��!
	if (root) {
		inorder_even(root->left);	// ���ʼ���Ʈ�� ��ȸ
		arr_even[index_even++] = root->data;
		inorder_even(root->right);	// �����ʼ���Ʈ�� ��ȸ
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
//5. ������ȸ�ϴ� �˰����� �����Ͽ� �� ���� ¦�� �� Ȧ�� ����Ž��Ʈ���� ���ÿ� ������������ ��ȸ�ϴ� �˰����� �ۼ��϶�.(����� ��ü�� �������� ���� ��) 
// ���� ��ȸ ��ü
inorder_whole(TreeNode* root1, TreeNode* root2) {
	//�� �����Ͱ� �ƴ϶��!
	if (root1) {
		//inorder_whole(root1->left, root2);	// ���ʼ���Ʈ�� ��ȸ
		odd_s = root1->data;
		even_s = root2->data;
		if (odd_s < even_s) {
			inorder_whole(root1->left, root2);	// ���ʼ���Ʈ�� ��ȸ
			printf("%d\t", root1->data); 	// ��� �湮
		}
		else
		{
			inorder_whole(root1, root2->left);	// ���ʼ���Ʈ�� ��ȸ
			printf("%d\t", root2->data); 	// ��� �湮
		}
		inorder_whole(root1->right, root2);	// �����ʼ���Ʈ�� ��ȸ
	}
}

/*
//ó�� temp�� 100���� ����. ����Ʈ�� �ݴ��� Ʈ�� �Դٰ��ٷ� ����
//1. ���� Ʈ�� �������� ��� �̵�. ���� ���� ������.
//���� ������? �ϴ� �׳� ���Ͷ�. �׷� �ٷ� �Ʒ����� ����ȴ�.
//������ ������ ��带 �������.
inorder_whole_tempte(TreeNode* root_in, TreeNode* root_wait, int temp) {
	//�� �����Ͱ� �ƴ϶��!
	if (root_in) {
		printf("\n���� NULL �����Ͱ� �ƴϴ�. ������ : %d, temp : %d\n", root_in->data, temp);
		printf("���� ��尡 NULL���� Ȯ���Ѵ�.\n");
		if (root_in->left != NULL) printf("�� �� ���� %d�� ���� ���� �̵�\n", root_in->left->data);
		else printf("�� ���� ���� �̵�\n");
		inorder_whole_temp(root_in->left, root_wait, temp);	// ���ʼ���Ʈ�� ��ȸ
		printf("�ο��� ���Դ�. ���� ���� %d�� ���� ����� ������ %d�� ���Ѵ�.\n", temp, root_in->data);
		if (temp < root_in->data) {
			printf("���� ���� %d���� ����� ������ %d�� Ŀ %d�� ������ ���� ���� ����Ѵ�.\n", temp, root_in->data, root_in->data);
			printf("%d\n", temp); 	// ��� �湮
			temp = root_in->data;
			printf("�ݴ��� �����Ͱ� ������ �ƴ��� Ȯ���Ѵ�.\n");
			if (root_wait->data != NULL) {
				printf("�ݴ����� ���� �ƴϴ�. %d�� ������ �ݴ��� Ʈ���� ���� �ƴ� ��尪 %d�� �̵��Ѵ�.\n", temp, root_wait->data);
				inorder_whole_temp(root_wait, root_in, temp);	// �ݴ�Ʈ�� ȣ��
			} else printf("�ݴ����� ���̴�. �׳� �Ѿ��.\n"); 
		}
		else
		{
			printf("���� ���� %d���� ����� ������ %d�� �۴�. ���� ���� ����Ѵ�.\n", temp, root_in->data);
			printf("%d\n", root_in->data); 	// ��� �湮
		}
		printf("\n���� NULL �����Ͱ� �ƴϴ�. ������ : %d, temp : %d\n", root_in->data, temp);
		printf("������ ��尡 NULL���� Ȯ���Ѵ�.\n");
		if (root_in->right != NULL) printf("�� �� ������ %d�� ���� ���� �̵�\n", root_in->left->data);
		else printf("�� ������ ���� �̵�\n");
		inorder_whole_temp(root_in->right, root_wait, temp);	// �����ʼ���Ʈ�� ��ȸ
	}
	else
	{
		printf("���� ������. ���� %d�� ������ �ִ�. ���´�.\n", temp);
	}

}
*/

int temp = -1;
inorder_whole_temp(TreeNode* root_in, TreeNode* root_wait, boolean passed) {
	//�� �����Ͱ� �ƴ϶��!
	if (root_in->left != NULL)
		inorder_whole_temp(root_in->left, root_wait, temp, FALSE);	// ���ʼ���Ʈ�� ��ȸ

	//���� ���� �湮 ��尪���� �۴ٸ�
	if (temp < root_in->data) {
		//�ݴ��� üũ�ߴ��� Ȯ���ض�.
		//Ȯ���ߴٸ� ����ϰ�
		if (passed) {
			printf("%d\n", root_in->data); 	// ��� �湮
			temp = root_in->data;
			//return;
		}
		//Ȯ������ �ʾҴٸ� �ݴ�� �̵��ض�
		else
		{
			inorder_whole_temp(root_wait, root_in, temp, TRUE);	// �ݴ��� Ʈ���� �̵�
		}
	}
	//���� ���� �湮 ��尪���� ũ�ٸ�
	else
	{
	//	return;
	}
	if (root_in->right != NULL)
		inorder_whole_temp(root_in->right, root_wait, temp, FALSE);	// �����ʼ���Ʈ�� ��ȸ
}






//
//// ���� ��ȸ Ȧ����
//int inorder_odd(TreeNode* odd) {
//	if (odd) {
//		inorder(odd->left);	// ���ʼ���Ʈ�� ��ȸ
//		odd_s = odd->data;
//		//Ȧ���� �۴ٸ� ����ϰ�
//		if (odd_s < even_s) {
//			printf("%d\t", odd_s); 	// ��� �湮
//		}
//		//¦���� �۴ٸ� ¦���� ����ض�
//		else
//		{
//
//		}
//		inorder(odd->right);	// �����ʼ���Ʈ�� ��ȸ
//	}
//}
//// ���� ��ȸ ¦����
//inorder_even(TreeNode* even) {
//	if (even) {
//		inorder(even->left);	// ���ʼ���Ʈ�� ��ȸ
//		even_s = even->data;
//		inorder(even->right);	// �����ʼ���Ʈ�� ��ȸ
//	}
//}


// ��带 �����ϰ� �������ִ� �Լ�
TreeNode* new_node(int data) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, int data){
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
		temp[i] = rand()%101 + 1;

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
	//inorder_whole_temp( tree_even, tree_odd, FALSE);
	//inorder_test(tree_even, tree_odd);
	inorder_test(tree_odd, tree_even);
	return 0;
}