#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int contents;

typedef struct {
    contents* queue;
    int front;
    int rear;
    int size;
}queue;

int isEmpty(queue* this) {
    return (this->front == this->rear) ? 1 : 0;
}

int isFull(queue* this,char type) {
    return type == 'c' ? (((this->rear + 1) % this->size == this->front % this->size) ? 1 : 0 ): ((this->rear+1==this->size) ? 1 : 0);
}

queue* newQueue(int n,char type) {
    queue* temp = (queue*) malloc(sizeof(queue));
    temp->queue = (contents*) calloc(n, sizeof(contents));
    temp->front = type == 'c' ? 0 : -1;
    temp->rear = type == 'c' ? 0 : -1;
    temp->size = n;
    return temp;
}

void printq(queue* this,char type) {
    if (type == 'c') {
        printf("Circular queue: ");
        for (int i = this->front;i <= this->rear - 1;i++) {
            printf("%d ", this->queue[i % this->size]);
        }
        printf("\n");

    }
    else {
        printf("List queue: ");
        for (int i = this->front + 1;i <= this->rear;i++) {
            printf("%d ", this->queue[i]);
        }
        printf("\n");
    }
}

void addq(queue* this, contents con,char type) {
    if (isFull(this,type)) {
        printf("%s queue is full\n",type=='c'? "Circular":"List");
        return;
    }
    this->queue[type == 'c'? (this->rear++) % this->size :(++this->rear)] = con;
    printq(this,type);
}

contents deleteq(queue* this,char type) {
    if (isEmpty(this)) {
        printf("%s queue is empty\n", type == 'c' ? "Circular" : "List");
        return;
    }
    this->front++;
    if (isEmpty(this)) {
        printf("%s queue is empty\n", type == 'c' ? "Circular" : "List");
        return;
    }
    printq(this,type);
}

void deleteQueue(queue* this) {
    free(this->queue);
    free(this);
}


void main() {

    char input;
    int value;
    printf("input size: ");
    scanf("%d", &value);
    queue* Cq = newQueue(value,'c'); //Circular queue 持失
    queue* Lq = newQueue(value, 'l'); //List queue 持失
    printf("Queue size: %d\n", value);
    while (1) {
        printf("input: ");
        scanf(" %c", &input);
        switch (input) {
        case 'a':
            scanf("%d", &value);
            addq(Cq, value,'c');
            addq(Lq, value, 'l');
            break;
        case 'd':
            deleteq(Cq,'c');
            deleteq(Lq, 'l');
            break;
        case 'q':
            printf("quit\n");
            deleteQueue(Cq);
            deleteQueue(Lq);
            return;
        }
    }
}