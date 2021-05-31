#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MAX_QUEUE_SIZE 100
struct node
{
    int data; //node will store an integer
    struct node* right_child; // right child
    struct node* left_child; // left child
};

struct node* search(struct node* root, int x)
{
    if (root == NULL || root->data == x) //if root->data is x then the element is found
        return root;
    else if (x > root->data) // x is greater, so we will search the right subtree
        return search(root->right_child, x);
    else //x is smaller than the data, so we will search the left subtree
        return search(root->left_child, x);
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
struct node* new_node(int x)
{
    struct node* p;
    p = malloc(sizeof(struct node));
    p->data = x;
    p->left_child = NULL;
    p->right_child = NULL;

    return p;
}

struct node* insert(struct node* root, int x)
{
    //searching for the place to insert
    if (root == NULL)
        return new_node(x);
    else if (x > root->data) // x is greater. Should be inserted to right
        root->right_child = insert(root->right_child, x);
    else // x is smaller should be inserted to left
        root->left_child = insert(root->left_child, x);
    return root;
}

// funnction to delete a node
struct node* delete(struct node* root, int x)
{
    //searching for the item to be deleted
    if (root == NULL)
        return NULL;
    if (x > root->data)
        root->right_child = delete(root->right_child, x);
    else if (x < root->data)
        root->left_child = delete(root->left_child, x);
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
            //오른쪽 서브트리의 가장 작은 노드를 리턴 받고
            struct node* temp = find_minimum(root->right_child);
            //지우려는 현재 노드에 해당 값을 씌운다.
            root->data = temp->data;
            //현재 노드의 오른쪽 노드에 오른쪽 서브트리에서 가장 작은 값을 지운 트리로 채운다.
            root->right_child = delete(root->right_child, temp->data);
        }
    }
    return root;
}

void inorder(struct node* root)
{
    if (root != NULL) // checking if the root is not null
    {
        inorder(root->left_child); // visiting left child
        printf(" %d ", root->data); // printing data at root
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
            printf(" %d ", ptr->data);
            if (ptr->left_child)
                enqueue(queue, ptr->left_child);
            if (ptr->right_child)
                enqueue(queue, ptr->right_child);
        }
        else break;
    }
}

//level order tree traversal
void levelOrderModified(struct node* ptr) {
    int level = 0;
    struct node* temp = new_node(0);
    int null_test = 0;
    int enter = 0;
    int no_child_test = 0;
    int linetest = 1;
    struct Queue* queue = createQueue(MAX_QUEUE_SIZE);
    if (!ptr) return;   // empty tree
    enqueue(queue, ptr);
    for (;;) {
        ptr = dequeue(queue);
        if (ptr) {
            printf(" %d ", ptr->data);
            if (ptr->data == 0) no_child_test++;
            enter++;
            if (no_child_test >= linetest)
                break;
            if (enter >= linetest)
            {
                printf("\n");
                enter = 0;
                no_child_test = 0;
                linetest *= 2;
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
}

/*
                                                                    20

                                    ┌───────────────────────────────┴───────────────────────────────┐

                                    5                                                               30

                    ┌───────────────┴───────────────┐                               ┌───────────────┴───────────────┐

                                                    15                              25                              42

                                            ┌───────┴───────┐

                                            12
                                        ┌───┴───┐

                                        7








    */

int main()
{
    /*
                   20
                 /    \
                /      \
               5       30
             /   \     /\
            /     \   /  \
           1      15 25  40
                /          \
               /            \
              9             45
            /   \          /
           /     \        /
          7      12      42
    */
    struct node* root;
    root = new_node(20);
    insert(root, 5);
    insert(root, 1);
    insert(root, 15);
    insert(root, 9);
    insert(root, 7);
    insert(root, 12);
    insert(root, 30);
    insert(root, 25);
    insert(root, 40);
    insert(root, 45);
    insert(root, 42);

    inorder(root);
    printf("\n");

    root = delete(root, 1);
    /*
                   20
                 /    \
                /      \
               5       30
                 \     /\
                  \   /  \
                  15 25   40
                /           \
               /             \
              9              45
            /   \           /
           /     \         /
          7      12       42
    */

    root = delete(root, 40);
    /*
                   20
                 /    \
                /      \
               5       30
                 \     /\
                  \   /  \
                  15 25  45
                 /       /
                /       /
               9       42
             /   \
            /     \
           7      12
    */

    root = delete(root, 45);
    /*
                   20
                 /    \
                /      \
               5       30
                 \     /\
                  \   /  \
                  15 25  42
                 /
                /
               9
             /   \
            /     \
           7      12
    */
    root = delete(root, 9);
    inorder(root);
    /*
                   20
                 /    \
                /      \
               5       30
                 \     /\
                  \   /  \
                  15 25  42
                 /
                /
               12
             /
            /
           7
    */
    

    printf("\n");


    struct Queue* queue = createQueue(1000);

    enqueue(queue, root);
    enqueue(queue, root->left_child);
    enqueue(queue, root->right_child);

    printf("%p dequeued from queue\n\n",
        dequeue(queue));

    printf("Front item is %p\n", front(queue));
    printf("Rear item is %p\n", rear(queue));

    levelOrder(root);
    printf("\n");
    levelOrderModified(root);
    return 0;
}