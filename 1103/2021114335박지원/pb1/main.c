#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int contents;
typedef struct s {
	contents value;
	struct s* link;
}stack;

int isEmpty(stack** head) {
	return (*head) == NULL ? 1 : 0;
}

void push(stack** head, contents value) {
	stack* temp = (stack*)malloc(sizeof(stack));
	temp->value = value;
	temp->link = (*head);
	(*head) = temp;
}

contents pop(stack** head) {
	if (isEmpty(head)) {
		printf("스택이 비었음\n");
		return;
	}
	stack* temp = (*head);
	(*head) = (*head)->link;
	contents temp2 = temp->value;
	free(temp);
	return temp2;
}

void printStack(stack* head) {
	while (head != NULL) {
		printf("%d ", head->value);
		head = head->link;
	}
	printf("\n");
}

void printEqClass(stack* seq[],int size) {
	int* isprinted = (int*)calloc(size + 1, sizeof(int));
	for (int i = 0;i <= size;i++) {
		if (!isprinted[i]) {
			isprinted[i] = 1;
			printf("New class: %5d",i);
			stack* out = NULL;
			stack* cur = seq[i];
			while (1) {
				while (cur != NULL) {
					int cur_data = cur->value;
					if (!isprinted[cur_data]) {
						printf("%5d", cur_data);
						isprinted[cur_data] = 1;
						push(&out, cur_data);
					}
					cur = cur->link;
				}
				if (isEmpty(&out)) break;
				cur = seq[pop(&out)];
			}
			printf("\n");
		}
	}
}

void main() {
	FILE* fp = fopen("e3.txt", "r");
	contents input;
	int size;
	fscanf(fp, "%d", &size);
	stack** seq = (stack**)malloc(sizeof(stack*) * size+1);
	for (int i = 0;i <= size;i++) {
		seq[i] = NULL;
	}
	int input1,input2;
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &input1,&input2);
		push(&seq[input1], input2);
		push(&seq[input2], input1);
	}
	printEqClass(seq,size);
}