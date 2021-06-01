#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MAX_STR_SIZE 128


#define MAX_QUEUE_SIZE 100
struct node
{
    char* key; //node will store an integer
    struct node* right_child; // right child
    struct node* left_child; // left child
};

struct node* search(struct node* node, char* key)
{
    if (node == NULL)
        return NULL;

    int ret = strcmp(key, node->key);    // �Էµ� ���ڿ� ��
    switch (ret)
    {
    case 0:
        return node;
        break;
    case 1:
        return search(node->right_child, key);
        break;
    case -1:
        return search(node->left_child, key);
        break;
    }
}

//function to find the minimum value in a node
struct node* find_minimum(struct node* root)
{
    if (root == NULL)
        return NULL;
    else if (root->left_child != NULL) // node with minimum value will have no left child
        return find_minimum(root->left_child); // left most element will be minimum
    return root;
}

//function to create a node
struct node* new_node(char* key)
{
    struct node* p;
    p = malloc(sizeof(struct node));
    p->key = key;
    p->left_child = NULL;
    p->right_child = NULL;

    return p;
}

struct node* insert(struct node* root, char* key)
{
    //searching for the place to insert
    if (root == NULL)
        return new_node(key);
    else if (key > root->key) // x is greater. Should be inserted to right
        root->right_child = insert(root->right_child, key);
    else // x is smaller should be inserted to left
        root->left_child = insert(root->left_child, key);
    return root;
}

// ��� ����
struct node* InsertNode(struct node* node, char* key) {
    // ���� ���� �湮�� ��尡 NULL �̶�� �� ��带 �����ϰ� �����϶�
    if (node == NULL)
        return new_node(key);

    int ret = strcmp(key, node->key);    // �Էµ� ���ڿ� ��
    //���� ������ ����� ���ĺ� ������ ���� �湮�� ��庸�� ���̶�� �湮�� ����� ���ʿ� �����Ѵ�.
    switch (ret)
    {
    case 0:
        printf("�Է��� ���ڿ��� �̹� �ֽ��ϴ�.\n");
        break;
    case 1:
        node->right_child = InsertNode(node->right_child, key);
        break;
    case -1:
        node->left_child = InsertNode(node->left_child, key);
        break;
    }

    return node;
}


// funnction to delete a node
struct node* delete(struct node* root, char* key)
{
    //searching for the item to be deleted
    if (root == NULL) {
        printf("������ ���ڿ��� �����ϴ�.\n");
        return NULL;
    }
    
    int ret = strcmp(key, root->key);    // �Էµ� ���ڿ� ��
    if (ret == 1)
        root->right_child = delete(root->right_child, key);
    else if (ret == -1)
        root->left_child = delete(root->left_child, key);
    else
    {
        //No Children
        if (root->left_child == NULL && root->right_child == NULL)
        {
            free(root);
            return NULL;
        }

        //One Child
        else if (root->left_child == NULL || root->right_child == NULL)
        {
            struct node* temp;
            // if roots' left child is NULL
            if (root->left_child == NULL)
                temp = root->right_child;
            else
                temp = root->left_child;
            free(root);
            return temp;
        }

        //Two Children
        else
        {
            //������ ����Ʈ���� ���� ���� ��带 ���� �ް�
            struct node* temp = find_minimum(root->right_child);
            //������� ���� ��忡 �ش� ���� �����.
            root->key = temp->key;
            //���� ����� ������ ��忡 ������ ����Ʈ������ ���� ���� ���� ���� Ʈ���� ä���.
            root->right_child = delete(root->right_child, temp->key);
        }
    }
    return root;
}

void inorder(struct node* root)
{
    if (root != NULL) // checking if the root is not null
    {
        inorder(root->left_child); // visiting left child
        printf(" %s ", root->key); // printing data at root
        inorder(root->right_child);// visiting right child
    }
}

////////////////////////////////////////////
// A structure to represent a queue 
struct Queue {
    int front, rear, size;
    unsigned capacity;
    struct node** array;
};

// function to create a queue 
// of given capacity. 
// It initializes size of queue as 0 
struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(
        sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;

    // This is important, see the enqueue 
    queue->rear = capacity - 1;
    queue->array = (struct node*)malloc(
        queue->capacity * sizeof(struct node*));
    return queue;
}

// Queue is full when size becomes 
// equal to the capacity 
int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}

// Queue is empty when size is 0 
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}

// Function to add an item to the queue. 
// It changes rear and size 
void enqueue(struct Queue* queue, struct node* item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
        % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    //printf("%p enqueued to queue\n", item);
}

// Function to remove an item from queue. 
// It changes front and size 
struct node* dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return NULL;
    struct node* item = queue->array[queue->front];
    queue->front = (queue->front + 1)
        % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Function to get front of queue 
struct node* front(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}

// Function to get rear of queue 
struct node* rear(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->rear];
}



//level order tree traversal
void levelOrder(struct node* ptr) {
    struct Queue* queue = createQueue(MAX_QUEUE_SIZE);
    if (!ptr) return;   // empty tree
    enqueue(queue, ptr);
    for (;;) {
        ptr = dequeue(queue);
        if (ptr) {
            printf(" %s ", ptr->key);
            if (ptr->left_child)
                enqueue(queue, ptr->left_child);
            if (ptr->right_child)
                enqueue(queue, ptr->right_child);
        }
        else break;
    }
}

//level order tree traversal
void levelOrderModified(struct node* ptr, int level) {
    int tab_count = 1;
    for (size_t i = 0; i < level; i++)
    {
        tab_count *= 2;
    }

    struct node* temp = new_node(0);
    int null_test = 0;
    int element = 0;
    int zero_element = 0;
    int line_element_max = 1;
    struct Queue* queue = createQueue(MAX_QUEUE_SIZE);
    if (!ptr) return;   // empty tree
    enqueue(queue, ptr);
    for (;;) {
        ptr = dequeue(queue);
        if (ptr) {

            //��º�
            if (element == 0)
                for (size_t i = 0; i < (tab_count / 2); i++)
                    printf("\t");
            else
                for (size_t i = 0; i < tab_count; i++)
                    printf("\t");

            if (ptr->key == 0)
                zero_element++;
            else
                printf("%s", ptr->key);


            //�ش� ���� element ���� 1 ���϶�
            element++;
            //��� ���ҵ��� NULL �̶�� �����
            if (zero_element >= line_element_max)
                break;
            //�ش� ���� element ���� �ִ�ġ�� �Ѵ´ٸ�
            if (element >= line_element_max)
            {
                printf("\n\n\n");
                element = 0;
                zero_element = 0;
                //�ִ�ġ�� 2�� �ض�
                tab_count /= 2;
                line_element_max *= 2;
            }

            if (ptr->left_child)
                enqueue(queue, ptr->left_child);
            else {
                enqueue(queue, temp);
                null_test++;
            }
            if (ptr->right_child)
                enqueue(queue, ptr->right_child);
            else {
                enqueue(queue, temp);
                null_test++;
            }
        }
        else break;
    }
    printf("\n");
}

//level order tree traversal
int levelCheck(struct node* ptr) {
    int level = 0;
    struct node* temp = new_node(0);
    int null_test = 0;
    int element = 0;
    int zero_element = 0;
    int line_element_max = 1;
    struct Queue* queue = createQueue(MAX_QUEUE_SIZE);
    if (!ptr) return;   // empty tree
    enqueue(queue, ptr);
    for (;;) {
        ptr = dequeue(queue);
        if (ptr) {
            if (ptr->key == 0)
                zero_element++;
            element++;
            if (zero_element >= line_element_max)
                return level;
            if (element >= line_element_max)
            {
                level++;
                element = 0;
                zero_element = 0;
                line_element_max *= 2;
            }

            if (ptr->left_child)
                enqueue(queue, ptr->left_child);
            else {
                enqueue(queue, temp);
                null_test++;
            }
            if (ptr->right_child)
                enqueue(queue, ptr->right_child);
            else {
                enqueue(queue, temp);
                null_test++;
            }
        }
        else return level;
    }
    return level;
}

void menu(struct node* tree);

int main()
{
    struct node* root;
    root = NULL;
    //root = new_node("asdf");
    //InsertNode(root, "bsss");
    //InsertNode(root, "csss");

    //inorder(root);
    //printf("\n");

    
    ////levelOrder(root);

    //int level = 0;
    //level = levelCheck(root);
    //printf("\nlevel : %d\n", level);
    //levelOrderModified(root, level);
    //printf("\n");


    //root = delete(root, "asdf");
    //level = levelCheck(root);
    //printf("\nlevel : %d\n", level);
    //levelOrderModified(root, level);

    //printf("\n");
    menu(root);

    return 0;
}

void menu(struct node* tree) {
    char KEY[MAX_STR_SIZE];
    char COMMAND[MAX_STR_SIZE];
    struct node* temp;
    for (;;)
    {

        printf("��ɾ �Է��ϼ���.\n");
        printf("INSERT : (ex. INSERT abcd)\n");
        printf("SEARCH : (ex. SEARCH abcd)\n");
        printf("DELETE : (ex. DELETE abcd)\n");
        printf("VIEWALL : (ex. VIEWALL)\n");
        printf("VIEWTREE : (ex. VIEWTREE)\n");
        printf("QUIT : (ex. QUIT)\n");
        printf("=============================\n");
        scanf_s("%s", COMMAND, MAX_STR_SIZE);

        if (strcmp(COMMAND, "VIEWALL") == 0)
        {
            //VIEWALL
            printf("VIEWALL\n");
            inorder(tree);
            printf("\n");
        }
        else if (strcmp(COMMAND, "VIEWTREE") == 0) {
            int level = 0;
            level = levelCheck(tree);
            printf("\nlevel : %d\n", level);
            levelOrderModified(tree, level);
        }
        // QUIT �� �Է� ������ ���α׷��� �����Ѵ�.
        else if (strcmp(COMMAND, "QUIT") == 0)
        {
            printf("QUIT\n");
            break;
        }
        else {
            scanf_s("%s", KEY, MAX_STR_SIZE);
            char* temp = malloc(sizeof(char) * MAX_STR_SIZE);
            strcpy_s(temp, MAX_STR_SIZE, KEY);

            if (strcmp(COMMAND, "INSERT") == 0)
            {
                printf("INSERT %s\n", temp);
                tree = InsertNode(tree, temp);
            }
            else if (strcmp(COMMAND, "SEARCH") == 0)
            {
                struct node* result;
                printf("SEARCH %s\n", temp);
                result = search(tree, temp);
                if(result != NULL)
                    printf("�ش� ���ڿ� %s �� �ֽ��ϴ�.\n", result->key);
                else
                    printf("�ش� ���ڿ� %s �� �����ϴ�.\n", temp);
            }
            else if (strcmp(COMMAND, "DELETE") == 0)
            {
                printf("DELETE %s\n", temp);
                tree = delete(tree, temp);
            }
            else
            {
                printf("�߸��� �Է��Դϴ�.\n");
            }

        }

    }


}