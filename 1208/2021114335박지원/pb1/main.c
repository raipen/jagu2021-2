#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x,y,t) t=x;x=y;y=t

typedef int element;
typedef struct {
	int size;
	int range;
	int* arr;
}data;

data newData() {
	data temp;
	printf("input size:");
	scanf("%d", &temp.size);
	printf("input range(10~9999):");
	scanf("%d", &temp.range);

	temp.arr = (int*)malloc(sizeof(int) * temp.size);
	for (int i = 0;i < temp.size;i++) {
		temp.arr[i] = rand() % (temp.range + 1);
	}
	return temp;
}

void printData(data d) {
	for (int i = 0;i < d.size;i++) {
		printf("%d ", d.arr[i]);
	}
	printf("\n");
}

void insert(element e, element a[], int i, int key) {
	while (i != -1 && e / key % 10 > a[i] / key % 10) {
		a[i + 1] = a[i];
		i--;
	}
	a[i + 1] = e;
}

void insertionSort(element a[], int n, int key) {
	for (int i = 1;i < n;i++) {
		insert(a[i], a, i - 1, key);
	}
}

void radixSort(data d) {
	int key = 1;
	while (d.range / key) {
		insertionSort(d.arr, d.size, key);
		key *= 10;
	}
}

void main() {
	srand(time(NULL));
	data input = newData();
	printf("before radix sort...\n");
	printData(input);
	radixSort(input);
	printf("after radix sort...\n");
	printData(input);
}