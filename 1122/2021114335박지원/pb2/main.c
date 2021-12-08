#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
    int row;
    int col;
}coordinate;

typedef struct {
    element** data;
    int size;
}Adj_matrix;

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
    element item = temp->value;
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

element pop(stack* this) {
    return deleteq(this->a);
}

element top(stack* this) {
    return this->a->front->value;
}
//링크드 큐를 이용한 스택 구현 끝


Adj_matrix newAM(char* file) {
    Adj_matrix temp;
    FILE* fp = fopen(file, "r");
    fscanf(fp, "%d", &temp.size);
    temp.data = (int**)malloc(sizeof(int*) * temp.size);
    for (int i = 0;i < temp.size;i++) {
        temp.data[i] = (int*)calloc(temp.size, sizeof(int));
    }
    for (int i = 0;i < temp.size;i++) {
        for (int j = 0;j < temp.size;j++) {
            fscanf(fp, "%d", &temp.data[i][j]);
        }
    }
    fclose(fp);
    return temp;
}

void printAM(Adj_matrix this) {
    for (int i = 0;i < this.size;i++) {
        for (int j = 0;j < this.size;j++) {
            printf("%d  ", this.data[i][j]);
        }
        printf("\n");
    }
}

void printDFS(Adj_matrix matrix,int a) {
    printf("DFS Spanning Tree:\n");
    int* isPrinted = (int*)calloc(matrix.size, sizeof(int));
    stack* sta = newStack();
    isPrinted[a] = 1;
    push(sta, a);
    int cur;
    while (!isEmpty(sta->a)) {
        cur = top(sta);
        int i;
        for (i = 0;i < matrix.size;i++) {
            if (matrix.data[cur][i] && !isPrinted[i]) {
                printf("(%d, %d)",cur, i);
                isPrinted[i] = 1;
                push(sta, i);
                break;
            }
        }
        if (i == matrix.size) {
            pop(sta);
        }
    }
    printf("\n");
    freeStack(sta);
}

int printBFS(Adj_matrix matrix,int a) {
    printf("BFS Spanning Tree:\n");
    int* isPrinted = (int*)calloc(matrix.size, sizeof(int));
    queue* que = newQ();
    isPrinted[a] = 1;
    addq(que, a);
    int cur;
    while (!isEmpty(que)) {
        cur = deleteq(que);
        int i;
        for (i = 0;i < matrix.size;i++) {
            if (matrix.data[cur][i] && !isPrinted[i]) {
                printf("(%d, %d)", cur, i);
                isPrinted[i] = 1;
                addq(que, i);
            }
        }
    }
    printf("\n");
    freeQ(que);
    return 1;
}

void freeMatrix(Adj_matrix am) {
    for (int i = 0;i < am.size;i++) {
        free(am.data[i]);
    }
    free(am.data);
}

void main() {
    Adj_matrix am = newAM("in.txt");
    int a;
    while (1) {
        printf("Starting number:");
        scanf("%d", &a);
        if (a < 0 || a >= am.size)
            return;
        printDFS(am,a);
        printBFS(am,a);
        printf("\n");
    }
    freeMatrix(am);
}