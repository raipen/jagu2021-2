#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int contents;
typedef struct t {
    struct t* left;
    contents value;
    struct t* right;
}tree;

typedef tree* element;
typedef struct q {
    element value;
    struct q* link;
}q_node;
typedef struct {
    struct q* front;
    struct q* rear;
}queue;

typedef struct {
    queue* a;
    queue* b;
}stack;

//링크드 큐 구현 시작
queue* newQ() {
    queue* que = (queue*)malloc(sizeof(queue));
    que->front = NULL;
    que->rear = NULL;
    return que;
}

void freeQ(queue* this) {
    while (this->front != NULL) {
        q_node* temp = this->front;
        this->front = this->front->link;
        free(temp);
    }
    free(this);
}

int isEmpty(queue* this) {
    return this->front == NULL ? 1 : 0;
}

void addq(queue* this, element value) {
    q_node* temp = (q_node*)malloc(sizeof(q_node));
    temp->value = value;
    temp->link = NULL;
    if (this->front)
        this->rear->link = temp;
    else
        this->front = temp;
    this->rear = temp;
}

element deleteq(queue* this) {
    q_node* temp = this->front;
    if (!temp)
        return NULL;
    tree* item = temp->value;
    this->front = temp->link;
    free(temp);
    return item;
}
//링크드 큐 구현 끝


//링크드 큐를 이용한 스택 구현 시작
stack* newStack() {
    stack* temp = (stack*)malloc(sizeof(stack));
    temp->a = newQ();
    temp->b = newQ();
    return temp;
}

void freeStack(stack* this) {
    freeQ(this->a);
    freeQ(this->b);
    free(this);
}

void push(stack* this, element* value) {
    if (isEmpty(this->a)) {
        addq(this->a, value);
        return;
    }
    while (!isEmpty(this->a)) {
        addq(this->b, deleteq(this->a));
    }
    addq(this->a, value);
    while (!isEmpty(this->b)) {
        addq(this->a, deleteq(this->b));
    }
}

tree* pop(stack* this) {
    return deleteq(this->a);
}

tree* peek(stack* this) {
    tree* temp = pop(this);
    push(this, temp);
    return temp;
}
//링크드 큐를 이용한 스택 구현 끝


//레벨오더 순서대로 트리를 만드는 함수
tree* makeTree_levelorder(int input) {
    queue* que = newQ();
    tree* root = (tree*)malloc(sizeof(tree));
    int count = 1;
    addq(que, root);
    count++;
    tree* cur;
    for (int i = 1; i <= input;i++) {
        cur = deleteq(que);
        cur->value = i;
        cur->left = NULL;
        cur->right = NULL;
        if (count <= input) {
            cur->left = (tree*)malloc(sizeof(tree));
            addq(que, cur->left);
            count++;
        }
        if (count <= input) {
            cur->right = (tree*)malloc(sizeof(tree));
            addq(que, cur->right);
            count++;
        }
    }
    freeQ(que);
    return root;
}

//레벨 오더 순서대로 트리를 출력하는 함수
void levelorder(tree* root) {
    queue* que = newQ();
    if (!root) return;
    addq(que, root);
    while (1) {
        root = deleteq(que);
        if (root) {
            printf("%d ", root->value);
            if (root->left)
                addq(que, root->left);
            if (root->right)
                addq(que, root->right);
        }
        else
            return;
    }
    freeQ(que);
}

//재귀를 쓰지 않고 인오더로 출력하는 함수
void iterative_Inorder(tree* root) {
    stack* sta = newStack();
    while (1) {
        while (root) {
            push(sta, root);
            root = root->left;
        }
        root = pop(sta);
        if (!root) break;
        printf("%d ", root->value);
        root = root->right;
    }
    freeStack(sta);
}

//재귀를 쓰지 않고 프리오더로 출력하는 함수
void iterative_preorder(tree* root) {
    stack* sta = newStack();
    while (1) {
        while (root) {
            push(sta, root);
            printf("%d ", root->value);
            root = root->left;
        }
        root = pop(sta);
        if (!root) break;
        root = root->right;
    }
    freeStack(sta);
}

//재귀를 쓰지 않고 포스트오더로 출력하는 함수
void iterative_postorder(tree* root) {
    stack* sta = newStack();
    while (1) {
        while (root) {
            push(sta, root);
            push(sta, root);
            root = root->left;
        }
        root = pop(sta);
        if (!root) break;
        if (root == peek(sta)) {
            root = root->right;
        }
        else {
            printf("%d ", root->value);
            root = NULL;
        }
    }
    freeStack(sta);
}

//트리 메모리 할당해제
void freeTree(tree* root) {
    if (root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void main() {
    printf("input data:");
    int a;
    scanf("%d", &a);
    tree* root = makeTree_levelorder(a);
    printf("levelorder:");
    levelorder(root);
    printf("\ninorder:");
    iterative_Inorder(root);
    printf("\npreorder:");
    iterative_preorder(root);
    printf("\npostorder:");
    iterative_postorder(root);
    freeTree(root);
}