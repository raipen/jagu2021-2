#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) t=x;x=y;y=t

typedef struct {
	int key;
	char data[100];
}element;

void printarr(element arr[], int n) {
	for (int i = 0;i < n;i++) {
		printf("%5s:%4d\n", arr[i].data, arr[i].key);
	}
}

void quickSort(element a[], int left, int right) {
	int pivot, i, j;
	element temp;
	if (left < right) {
		i = left; j = right+1;
		pivot = a[left].key;
		do {
			do i++; while (a[i].key > pivot);
			do j--; while (a[j].key < pivot);
			if (i < j) {
				SWAP(a[i], a[j], temp);
			}
		} while (i < j);
		SWAP(a[left], a[j], temp);
		quickSort(a, left, j - 1);
		quickSort(a, j + 1, right);
	}
}

void main() {
	FILE* fp = fopen("in.txt", "r");
	int cnt;
	fscanf(fp, "%d", &cnt);
	element* arr = (element*)malloc(sizeof(element) * cnt);
	for (int i = 0;i < cnt;i++) {
		fscanf(fp, "%s %d", arr[i].data, &arr[i].key);
	}
	printf("[before quick sort]\n");
	printarr(arr, cnt);
	quickSort(arr, 0, cnt-1);
	printf("[after quick sort]\n");
	printarr(arr, cnt);
	free(arr);
}