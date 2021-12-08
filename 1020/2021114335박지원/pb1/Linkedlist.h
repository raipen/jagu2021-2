#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int coef;
    int expon;
}contents;

typedef struct n {
    contents value;
    struct n* next;
}node;

typedef struct {
    node* head;
    node* tail;
}list;

list* newLinkedList();

void insert(list* this, contents value, int index);

int search(list* this, contents n, int (*fun)(contents, contents));

void removeNode(list* this, int index);

void printNode(list* this, char* form);

list* deleteLinkedList(list* this);