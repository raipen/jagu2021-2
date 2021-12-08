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

typedef struct n{
	struct n* next;
	element data;
}node;
typedef struct {
	node** list;
	int size;
}Linked_adj_list;

Adj_matrix newAM(char* file) {
	Adj_matrix temp;
	FILE* fp = fopen(file, "r");
	fscanf(fp,"%d", &temp.size);
	temp.data = (int**)malloc(sizeof(int*)*temp.size);
	for (int i = 0;i < temp.size;i++) {
		temp.data[i] = (int*)calloc(temp.size,sizeof(int));
	}

	coordinate a;
	while (!feof(fp)) {
		fscanf(fp,"%d %d", &a.row, &a.col);
		temp.data[a.row][a.col] = 1;
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

void insertF(node** head, element item) {
	if ((*head)==NULL) {
		(*head) = (node*)malloc(sizeof(node));
		(*head)->data = item;
		(*head)->next = NULL;
		return;
	}
	node* temp = (node*)malloc(sizeof(node));
	temp->data = item;
	temp->next = (*head);
	(*head) = temp;
}

Linked_adj_list newLAL(char* file) {
	Linked_adj_list temp;
	FILE* fp = fopen(file, "r");
	fscanf(fp, "%d", &temp.size);
	temp.list = (node**)calloc(temp.size, sizeof(node*));

	coordinate a;
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &a.row, &a.col);
		insertF(&temp.list[a.row], a.col);
	}
	fclose(fp);
	return temp;
}

Linked_adj_list newIAL(char* file) {
	Linked_adj_list temp;
	FILE* fp = fopen(file, "r");
	fscanf(fp, "%d", &temp.size);
	temp.list = (node**)calloc(temp.size,sizeof(node*));

	coordinate a;
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &a.row, &a.col);
		insertF(&temp.list[a.col], a.row);
	}
	fclose(fp);
	return temp;
}

Linked_adj_list newIAL_fromLAL(Linked_adj_list LAL) {
	Linked_adj_list temp;
	temp.size = LAL.size;
	temp.list = (node**)calloc(temp.size, sizeof(node*));

	coordinate a;
	for (int i = 0;i < temp.size;i++) {
		node* cur = LAL.list[i];
		while (cur != NULL) {
			a.row = i;
			a.col = cur->data;
			insertF(&temp.list[a.col], a.row);
			cur = cur->next;
		}
	}
	return temp;
}

void printLL(Linked_adj_list this) {
	for (int i = 0;i < this.size;i++) {
		printf("[%2d]", i);
		node* cur = this.list[i];
		while(cur!=NULL) {
			printf("%3d", cur->data);
			cur = cur->next;
		}
		printf("\n");
	}
}

void printCLL(Linked_adj_list this) {
	for (int i = 0;i < this.size;i++) {
		printf("[%2d]", i);
		node* cur = this.list[i];
		int j = 0;
		while (cur != NULL) {
			j++;
			cur = cur->next;
		}
		printf(" %d\n",j);
	}
}

void main() {
	Adj_matrix am = newAM("in.txt");
	printf("(1) Adjacency matrix\n");
	printAM(am);

	Linked_adj_list lal = newLAL("in.txt");
	printf("\n\n(2) Linked adjacency matrix\n");
	printLL(lal);

	Linked_adj_list ial = newIAL_fromLAL(lal);
	printf("\n\n(3) Inverse adjacency matrix\n");
	printLL(ial);

	printf("\n\n(4) Inverse adjacency matrix\n");
	printCLL(ial);
	printf("\n\n(5) Inverse adjacency matrix\n");
	printCLL(lal);
}