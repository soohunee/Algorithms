#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RED 1
#define BLACK 0
#define MAX 100


typedef struct Node_{
    int data;
    int clr;
    struct Node_* left;
    struct Node_* right;
    struct Node_* parent;
}Node;
typedef struct queue_{
    Node* items[MAX];
    int front;
    int rear;
}queue;


Node* createNode();
int empty(struct queue* pq);
Node* BST_INSERT(Node** root, int x);
void insert(Node** root, int x);
Node* findNode(Node** root,Node* node, int x);
void delete(Node** root, int x);
void leftRotate(Node** root, Node* x);
void rightRotate(Node** root, Node* y);
Node* minimum(Node** root);
Node* successor(Node** root);
int height(Node* root);
void printTree(Node* root);
Node* dequeue(struct queue* pq);
void enqueue(struct queue* pq, Node* x);

Node* createNode()
{
    Node* p;
    p = (Node*)malloc(sizeof(Node));
    p->left = NULL;
    p->right = NULL;
    p->parent = NULL;
    return (p);
}
void insert(Node** root, int data)
{
    Node* x, *y, *temp;
    x = BST_INSERT(root, data);
    if (x == NULL)
        return;
    x->clr = RED;
    while ((x != (*root)) && (x->parent->clr == RED)) {
        if (x->parent == x->parent->parent->left) {
            y = x->parent->parent->right;
            if (y != NULL && y->clr == RED) {
                x->parent->clr = BLACK;
                y->clr = BLACK;
                x->parent->parent->clr = RED;
                x = x->parent->parent;
            }
            else {
                if (x == x->parent->right) {
                    x = x->parent;
                    leftRotate(root, x);
                }
                x->parent->clr = BLACK;
                x->parent->parent->clr = RED;
                rightRotate(root, x->parent->parent);
            }
        }
        else {
            y = x->parent->parent->left;
            if (y != NULL && y->clr == RED) {
                x->parent->clr = BLACK;
                y->clr = BLACK;
                x->parent->parent->clr = RED;
                x = x->parent->parent;
            }
            else {
                if (x == x->parent->left) {
                    x = x->parent;
                    rightRotate(root, x);
                }
                x->parent->clr = BLACK;
                x->parent->parent->clr = RED;
                leftRotate(root, x->parent->parent);
            }
        }
    }
    (*root)->clr = BLACK;
}
Node* findNode(Node** root, Node* node, int x) {
    if (node->data == x)
        return node;
    findNode(root, node->left, x);
    findNode(root, node->right, x);
}
void delete(Node** root, int value) {
    Node* x;
    Node* z, *y, *a;
    z= root;
    z = findNode(root, z, value);
    if (z->left == NULL || z->right == NULL) {
        y = z;
    }
    else
        y = successor(z);
    if (y->left != NULL)
        x = y->left;
    else
        x = y->right;
    x->parent = y->parent;
    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    if (y != z) {
        z->data = y->data;
    }
    if (y->clr == BLACK) {
        while (x != NULL && x->clr == BLACK) {
            if (x = x->parent->left) {
                a = x->parent->right;
                if (a->clr == RED) {
                    a->clr = BLACK;
                    x->parent->clr = RED;
                    leftRotate(root, x->parent);
                    a = x->parent->right;
                }
                if (a->left->clr == BLACK && a->right->clr == BLACK) {
                    a->clr = RED;
                    x = x->parent;
                }
                else if (a->right->clr == BLACK) {
                    a->left->clr = BLACK;
                    a->clr = RED;
                    rightRotate(root, a);
                    a = x->parent->right;
                }
                a->clr = x->parent->clr;
                x->parent->clr = BLACK;
                a->right->clr = BLACK;
                leftRotate(root, x->parent);
                x = root;
            }
            else {
                a = x->parent->left;
                if (a->clr == RED) {
                    a->clr = BLACK;
                    x->parent->clr = RED;
                    rightRotate(root, x->parent);
                    a = x->parent->left;
                }
                if (a->right->clr == BLACK && a->left->clr == BLACK) {
                    a->clr = RED;
                    x = x->parent;
                }
                else if (a->left->clr == BLACK) {
                    a->right->clr = BLACK;
                    a->clr = RED;
                    leftRotate(root, a);
                    a = x->parent->right;
                }
                a->clr = x->parent->clr;
                x->parent->clr = BLACK;
                a->left->clr = BLACK;
                rightRotate(root, x->parent);
                x = root;
            }
            x->clr = BLACK;
        }
    }
    return y;
}   
Node* BST_INSERT(Node** root, int x){
    Node* p, *q, *S;
    q = NULL;
    p = createNode();
    p->data = x;
    if ((*root) == NULL) {
        (*root) = p;
    }
    else {
        S = (*root);
        while (S != NULL) {
            q = S;
            if (x == q->data)
                return NULL;
            else if (x > S->data) {
                S = S->right;
            }
            else {
                S = S->left;
            }
        }
        if (x > q->data) {
            q->right = p;
        }
        else {
            q->left = p;
        }
        p->parent = q;
    }
    return(p);
}
void leftRotate(Node** root, Node* x) {
    Node* y;
    y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    if (x->parent == NULL) {
        (*root) = y;
    }
    else {
        y->parent = x->parent;
        if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
    }

    y->left = x;
    x->parent = y;
}
void rightRotate(Node** root, Node* y) {
    Node* x;
    x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }
    if (y->parent == NULL) {
        (*root) = x;
    }
    else {
        x->parent = y->parent;
        if (y == y->parent->left) {
            y->parent->left = x;
        }
        else {
            y->parent->right = x;
        }
    }
    x->right = y;
    y->parent = x;
}
Node* successor(Node** root) {
    Node *temp, *y;
    temp = root;
    if (temp->right != NULL)
        return minimum(root, temp->right);
    else {
        y = temp->right;
        while (y) {
            while (temp = y->right) {
                temp = y;
                y = y->parent;
            }
        }

    }
    return y;
}
Node* minimum(Node** root) {
    Node* temp;
    temp = *root;
    while (temp->left != NULL)
        temp = temp->left;
    return temp;
}
int height(Node* root){
    if (root == NULL || root->data == -1)
        return 0;
    else{
        int left = height(root->left);
        int right = height(root->right);
        if (left <= right)
            return right + 1;
        else
            return left + 1;
    }
}
void printTree(Node* root) {
    Node* temp, * nil;
    queue q, q2;
    int h = height(root);
    q.front = q.rear = MAX - 1;
    int count1 = 0;
    int count2 = 0;
    nil = createNode();
    nil->data = -1;

    if (root == NULL)
        return;
    enqueue(&q, root);
    count1++;
    for (int i = 0; i < h;i++) {
        while (count1 != 0){
            temp = dequeue(&q);
            count1--;
            if (temp->data == -1){
                enqueue(&q, nil);
                enqueue(&q, nil);
                printf("N ");
                count2 += 2;
            }
            else {
                if (temp->clr == BLACK){
                    printf("%d[B] ", temp->data);
                }
                else{
                    printf("%d[R] ", temp->data);
                }
                if (temp->left == NULL){
                    enqueue(&q, nil);
                }
                else {
                    enqueue(&q, temp->left);
                }
                if (temp->right == NULL){
                    enqueue(&q, nil);
                }
                else{
                    enqueue(&q, temp->right);
                }
                count2 += 2;
            }
        }
        printf("\n");
        count1 = count2;
        count2 = 0;
    }
}
int empty(queue* pq) {
    return(pq->front == pq->rear);
}
Node* dequeue(queue* pq) {
    if (pq->front == MAX - 1) {
        pq->front = 0;
    }
    else {
        pq->front = pq->front + 1;
    }
    return (pq->items[pq->front]);
}
void enqueue(queue* pq, Node* x){
    if (pq->rear == MAX - 1) {
        pq->rear = 0;
    }
    else  {
        pq->rear = pq->rear + 1;
    }
    if (pq->rear == pq->front)
    {
        printf("error\n");
    }
    else
    {
        pq->items[pq->rear] = x;
    }
}

int main() {
    int* A = (int*)malloc(sizeof(int) * 20);
    srand(time(NULL));
    A[0] = rand() % 50;
    for (int i = 0; i < 20; i++) {
        A[i] = rand() % 50;
        for (int j = 0; j < i; j++) {
            if (A[i] == A[j])
                i--;
        }
    }
    Node* root;
    root = createNode();
    root = NULL;
    for (int i = 0; i < 20; i++) {
        insert(&root, A[i]);
    }
    printf("After inserting random 20 keys\n");
    printTree(root);
    insert(&root, 2);
    printf("\n\nAfter inserting 2\n");
    printTree(root);
    insert(&root, 22);
    printf("\n\nAfter inserting 22\n");
    printTree(root);
    insert(&root, 13);
    printf("\n\nAfter inserting 13\n");
    printTree(root);
    insert(&root, 47);
    printf("\n\nAfter inserting 47\n");
    printTree(root);
    insert(&root, 36);
    printf("\n\nAfter inserting 36\n");
    printTree(root);
    return 0;
}
