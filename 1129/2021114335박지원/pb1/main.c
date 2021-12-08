#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) t=x;x=y;y=t

typedef struct {
	int key;
	char data[100];
}element;

void insert(element e, element a[], int i) {
	while (i!=-1&&e.key>a[i].key) {
		a[i + 1] = a[i];
		i--;
	}
	a[i + 1] = e;
}

void insertionSort(element a[], int n) {
	for (int i = 1;i < n;i++) {
		insert(a[i], a, i - 1);
	}
}

void printarr(element arr[], int n) {
	for (int i = 0;i < n;i++) {
		printf("%5s:%4d\n", arr[i].data, arr[i].key);
	}
}

void main() {
	FILE* fp = fopen("in.txt", "r");
	int cnt;
	fscanf(fp, "%d", &cnt);
	element* arr = (element*) malloc(sizeof(element)*cnt);
	for (int i = 0;i < cnt;i++) {
		fscanf(fp, "%s %d", arr[i].data,&arr[i].key);
	}

	printf("[before insert sort]\n");
	printarr(arr, cnt);
	insertionSort(arr, cnt);
	printf("[after insert sort]\n");
	printarr(arr, cnt);
	free(arr);
}