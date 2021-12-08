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
        i = left - 1; j = right;
        pivot = a[right].key;
        printf("pivot(name): %3d(%4s)\n", pivot, a[right].data);
        do {
            do i++; while (a[i].key < pivot);
            do j--; while (a[j].key > pivot);
            if (i < j) {
                SWAP(a[i], a[j], temp);
            }
        } while (i < j);
        SWAP(a[right], a[i], temp);
        quickSort(a, left, i - 1);
        quickSort(a, i + 1, right);
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
    printf("[after quick sort]\n");
    quickSort(arr, 0, cnt - 1);
    printf("\n");
    printarr(arr, cnt);
    free(arr);
}