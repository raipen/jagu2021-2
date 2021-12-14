#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char element;
typedef struct {
	int t;
	char slot[10];
}hash;

hash* new_hash_table(int size) {
	hash* temp= (hash*)calloc(size,sizeof(hash));
	for (int i = 0;i < size;i++) {
		temp[i].t = 0;
	}
	return temp;
}

void print_hash_table(hash* h,int size) {
	for (int i = 0;i < size;i++) {
		printf("[%d]: %s\n", i, h[i].slot);
	}
}

int return_key(char data[], int D) {
	int sum = 0;
	for (int i = 0;i < strlen(data);i++) {
		sum += data[i];
	}
	return sum % D;
}

void insert_hash(hash* h,char data[],int size) {
	int key = return_key(data,size);
	//printf("%d %s", key,data);
	if (!h[key].t) {
		strcpy(h[key].slot, data);
		h[key].t = 1;
	}
	else {
		while (h[key%size].t) {
			key++;
		}
		strcpy(h[key% size].slot,data);
		h[key].t = 1;
	}
}

void insert_hash_from_file(hash* input, char* file,int size) {
	FILE* fp = fopen(file, "r");
	element* temp[10];
	while (!feof(fp)) {
		fscanf(fp, "%s", temp);
		insert_hash(input, temp,size);
	}
}

int search_hash(hash* h, char data[], int size) {
	int key = return_key(data, size);
	int start = key;
	if (!strcmp(h[key++].slot,data)) return key-1;
	else {
		while ((key) % size != start) {
			if (!strcmp(h[key++%size].slot, data)) return key;
		}
		return 0;
	}
}

void main() {
	int size;
	printf("Input bucket size:");
	scanf("%d", &size);
	hash* input = new_hash_table(size);
	insert_hash_from_file(input, "in.txt",size);
	print_hash_table(input,size);
	char find[10];
	printf("Input string(Q for quit):");
	while (scanf("%s", &find) && strcmp(find, "Q")) {
		printf("%s\n", search_hash(input, find,size) ? "Success" : "Fail");
		printf("Input string(Q for quit):");
	}
	printf("Exit\n");
}