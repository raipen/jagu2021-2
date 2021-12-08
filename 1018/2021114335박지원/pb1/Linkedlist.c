#include "Linkedlist.h"

list* newLinkedList() {
    list* temp = (list*)malloc(sizeof(list));
    temp->head = NULL;
    temp->tail = NULL;
    return temp;
}

void insert(list* this, contents value, int index) {
    if (this->head == NULL) {
        this->head = (node*)malloc(sizeof(node));
        this->head->value = value;
        this->head->next = NULL;
        this->tail = this->head;
        return;
    }
    if (index == 0) {
        node* temp = (node*)malloc(sizeof(node));
        temp->value = value;
        temp->next = this->head;
        this->head = temp;
        return;
    }
    if (index == -1) {
        node* temp = (node*)malloc(sizeof(node));
        temp->value = value;
        temp->next = NULL;
        this->tail->next = temp;
        this->tail = temp;
        return;
    }
    node* cur = this->head;
    for (int i = 0; i < index - 1 && cur->next != NULL;i++) {
        cur = cur->next;
    }
    node* temp = (node*)malloc(sizeof(node));
    temp->value = value;
    temp->next = cur->next;
    cur->next = temp;
    if (temp->next == NULL) {
        this->tail = temp;
    }
    return;
}

void printNode(list* this,char* form) {
    node* cur = this->head;
    while (cur != NULL) {
        printf(form, cur->value);
        cur = cur->next;
    }
    printf("\n");
}

void deleteLinkedList(list* this) {
    node* cur = this->head;
    while (cur != NULL) {
        node* temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(this);
}