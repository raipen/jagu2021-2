#define _CRT_SECURE_NO_WARNINGS
#include "Linkedlist.h"

list* avail;

typedef struct {
    node* last;
}c_list;

node* get_node() {
    node* temp;
    if (avail->head != NULL) {
        temp = avail->head;
        avail->head = avail->head->next;
    }
    else {
        temp = (node*)malloc(sizeof(node));
    }
    return temp;
}

void ret_node(node* this) {
    this->next = avail->head;
    avail->head = this;
}

void cerase(c_list* this) {
    node* temp;
    if (this->last != NULL) {
        temp = this->last->next;
        this->last->next = avail->head;
        avail->head = temp;
        this->last = NULL;
    }
    free(this);
}

c_list* newCircularLinkedList(contents value) {
    c_list* temp = (c_list*)malloc(sizeof(c_list));
    temp->last = get_node();
    temp->last->value = value;
    temp->last->next = temp->last;
    return temp;
}

void insertFront(c_list* this, contents value) {
    node* temp = get_node();
    temp->value = value;
    temp->next = this->last->next;
    this->last->next = temp;
}

void insertRear(c_list* this, contents value) {
    node* temp = get_node();
    temp->value = value;
    temp->next = this->last->next;
    this->last->next = temp;
    this->last = temp;
}

void printCircularLinkedList(c_list* this) {
    node* cur = this->last->next;
    while (cur != this->last) {
        printf("%d ", cur->value);
        cur = cur->next;
    }
    printf("%d \n",cur->value);
}

void main() {
    avail = newLinkedList();

    FILE* fp = fopen("poly1.txt", "r");
    c_list* poly = newCircularLinkedList(50);
    printCircularLinkedList(poly);
    while (!feof(fp)) {
        contents temp;
        fscanf(fp, "%d", &temp);
        if (temp < 0) {
            insertFront(poly, temp);
            printCircularLinkedList(poly);
        }
        else{
            insertRear(poly, temp);
            printCircularLinkedList(poly);
        }
    }
    fclose(fp);
    cerase(poly);
    deleteLinkedList(avail);
}