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

int search(list* this, contents n, int (*fun)(contents, contents)) {
    node* cur = this->head;
    int index = 0;
    while (cur != NULL) {
        if (fun(cur->value, n))
            return index;
        cur = cur->next;
        index++;
    }
    return -1;
}

void removeNode(list* this, int index) {
    if (!index) {
        node* next = this->head->next;
        free(this->head);
        this->head = next;
        return;
    }
    node* cur = this->head;
    for (int i = 0; i < index - 1;i++) {
        cur = cur->next;
    }
    node* next = cur->next->next;
    free(cur->next);
    cur->next = next;
    if (cur->next == NULL) {
        this->tail = cur;
    }
}

void printNode(list* this, char* form) {
    if (this== NULL) {
        printf("empty list\n");
        return;
    }
    node* cur = this->head;
    while (cur != NULL) {
        printf(form, cur->value.coef, cur->value.expon);
        cur = cur->next;
    }
    printf("\n");
}

list* deleteLinkedList(list* this) {
    node* cur = this->head;
    while (cur != NULL) {
        node* temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(this);
    return NULL;
}