#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int student;
	char score[3];
}contents;
typedef struct s {
	contents value;
	struct s* link;
}stack;
stack* top[5];

int isEmpty(int i) {
	return top[i] == NULL ? 1 : 0;
}

void push(int i, contents value) {
	printf("push to top[%d]: %d, %s\n", i, value.student, value.score);
	stack* temp = (stack*)malloc(sizeof(stack));
	temp->value = value;
	temp->link = top[i];
	top[i] = temp;
}

contents pop(int i) {
	if (isEmpty(i)) {
		printf("스택이 비었음\n");
		exit(1);
	}
	stack* temp = top[i];
	top[i] = top[i]->link;
	contents temp2 = temp->value;
	free(temp);
	return temp2;
}

void main() {
	FILE* fp = fopen("score.txt", "r");
	contents input;
	int index;
	while (!feof(fp)) {
		fscanf(fp, "%d %d %s", &index,&input.student, input.score);
		push(index, input);
	}
	for (int i = 0;i < 5;i++) {
		printf("[과목%d]:\n", i);
		while (!isEmpty(i)) {
			input = pop(i);
			printf("pop from top[%d]: %d, %s\n", i,input.student,input.score);
		}
	}
}