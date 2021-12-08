#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    char data[100];
}element;

void printarr(int arr[], int n) {
    for (int i = 0;i < n;i++) {
        printf("%4d ", arr[i]);
    }
    printf("\n");
}

void printarr2(element arr[], int link[],int n) {
    int temp = link[0];
    for (int i = 0;i < n;i++) {
        printf("%5s:%4d\n", arr[temp].data, arr[temp].key);
        temp = link[temp];
    }
}

int listMerge(element a[], int link[], int start1, int start2) {
    int last1, last2, lastResult = 0;
    //printf("list: %d %d\n",start1,start2);
    for (last1 = start1, last2 = start2;last1 && last2;) {
        if (a[last1].key <= a[last2].key) {
            link[lastResult] = last1;
            lastResult = last1; last1 = link[last1];
        }
        else {
            link[lastResult] = last2;
            lastResult = last2; last2 = link[last2];
        }
    }
    if (last1 == 0) link[lastResult] = last2;
    else link[lastResult] = last1;
    //printarr(link, 14);
    return link[0];
}

int rmergeSort(element a[], int link[], int left, int right)
{
    //printf("%d %d\n", left, right);
    if (left >= right) return left;
    int mid = (left + right) / 2;
    printf("mid: %4d\n", mid);
    return listMerge(a, link, rmergeSort(a, link, left, mid),rmergeSort(a, link, mid + 1, right));
}

void main() {
    FILE* fp = fopen("in.txt", "r");
    int cnt;
    fscanf(fp, "%d", &cnt);
    element* arr = (element*)calloc(cnt + 1,sizeof(element));
    int* link = (int*)calloc(cnt+2, sizeof(int));
    for (int i = 1;i < cnt+1;i++) {
        fscanf(fp, "%s %d", arr[i].data, &arr[i].key);
    }
    printf("[after merge sort]\n");
    rmergeSort(arr, link, 1, cnt);
    printf("\n");
    printarr2(arr, link, cnt);
    free(arr);
}