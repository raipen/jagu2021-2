#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int contents;

typedef struct n {
	struct n* llink;
	contents value;
	struct n* rlink;
}node;

void insert(node** head, contents value,int (*func)(contents,contents)) {
	node* temp = (node*)malloc(sizeof(node));
	temp->value = value;
	node* cur = (*head);
	while (cur->rlink != (*head) && !func(cur->rlink->value,value)) {
		cur = cur->rlink;
	}
	temp->rlink = cur->rlink;
	temp->llink = cur;
	cur->rlink->llink = temp;
	cur->rlink = temp;
}

//int inFirst(contents a, contents b) {
//	return 1;
//}

int inLast(contents a, contents b) {
	return 0;
}

int sort_up(contents a, contents b) {
	return a>b? 1:0;
}

int sort_down(contents a, contents b) {
	return a < b ? 1 : 0;
}

node* newNode() {
	node* head = (node*)malloc(sizeof(node));
	head->llink = head;
	head->rlink = head;
	return head;
}

void printNode(node* head) {
	node* cur = head->rlink;
	while (cur != head) {
		printf("[%3d]", cur->value);
		cur = cur->rlink;
	}
	printf("\n");
}

void printNode_inv(node* head) {
	node* cur = head->llink;
	while (cur != head) {
		printf("[%3d]", cur->value);
		cur = cur->llink;
	}
	printf("\n");
}

void main() {
	node* head = newNode();
	FILE* fp = fopen("in.txt", "r");
	int a;
	while (!feof(fp)) {
		fscanf(fp,"%d", &a);
		insert(&head, a, inLast);
	}
	printf("print list\n");
	printNode(head);
	printf("print inverse order\n");
	printNode_inv(head);
	fclose(fp);

	while (1) {
		printf("Input number:");
		scanf("%d", &a);
		if (a < -100 || a>100) {
			printf("Quit!\n");
			exit(0);
		}
		insert(&head, a, sort_down);
		printf("After %d inserted...\n",a);
		printNode(head);
		printf("print inverse order\n");
		printNode_inv(head);
		printf("\n");
	}
}