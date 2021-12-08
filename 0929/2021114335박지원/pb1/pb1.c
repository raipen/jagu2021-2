#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    int value;
}contents;

typedef struct st {
    contents * m;
    int t;
    int capacity;
}stack;

int isEmpty(stack* this) {
    return (this->t == -1) ? 1 : 0;
}

int isFull(stack* this) {
    return (this->t == this->capacity -1) ? 1 : 0;
}

void stackFull(stack * this) {
    this->capacity *= 2;
    this->m = (contents*) realloc(this->m, sizeof(contents)*this->capacity);
    printf("\t doubling: %d", this->capacity);
}

void printstack(stack* this) {
    for (int i = 0;i <= this->t;i++) {
        printf("[%2d] ", this->m[i].value);
    }
    printf("\n");
}

void push(stack* this, contents m) {
    printf("push item: %d", m.value);
    if (isFull(this)) {
        stackFull(this);
    }
    printf("\n");
    this->m[++(this->t)] = m;
    printstack(this);
}

contents pop(stack* this) {
    printf("pop\n");
    if (isEmpty(this)) {
        printf("stack empty: cannot POP!\n");
        return;
    }
    contents temp = this->m[this->t--];
    printstack(this);
    return temp;
}

contents top(stack* this) {
    if (isEmpty(this)) {
        printf("스택이 비어있습니다\n");
        return;
    }
    return this->m[this->t];
}

stack* newStack() {
    stack* temp = (stack*)malloc(sizeof(stack));
    temp->m = (contents*)calloc(1, sizeof(contents));
    temp->t = -1;
    temp->capacity = 1;
    return temp;
}

void deleteStack(stack* sta) {
    free(sta->m);
    free(sta);
}

void main() {
    FILE* fp1 = fopen("in2.txt", "r");
    stack* in = newStack();
    while (!feof(fp1)) {
        char temp;
        fscanf(fp1, "%c ", &temp);
        contents tempc;
        switch (temp) {
        case 'I':
            fscanf(fp1, "%d ", &tempc.value);
            push(in, tempc);
            break;
        case 'D':
            pop(in);
            break;
        }
    }
    deleteStack(in);
}