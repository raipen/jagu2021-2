#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//이진탐색 함수
int rbs(int a[], int s, int l, int r) { 
    int m;
    while (l <= r) {
        m = (l + r) / 2;
        switch (a[m] < s ? -1 : (a[m] > s ? 1 : 0)) {
        case 1: return rbs(a, s, m + 1, r);
        case 0: return m;
        case -1: return rbs(a, s, l, m - 1);
        }
    }
    return -1;
}


void asdf(int* a, int n1, int* b, int n2) {
    int n = n1 < n2 ? n1 : n2;
    int nn = n1 < n2 ? n2 : n1;
    int* arr = n1 < n2 ? a : b;
    int* arr2 = n1 < n2 ? b : a;

    for (int i = 0;i < n;i++) {
        int temp = rbs(arr2, arr[i], 0, nn-1);
        if (temp!= -1)
            printf("%d ",arr2[temp]);
    }
}

void main() {

    FILE* fp1 = fopen("in1.txt", "r");
    if (!fp1) {
        printf("파일 없음");
        exit(1);
    }
    FILE* fp2 = fopen("in2.txt", "r");
    if (!fp2) {
        printf("파일 없음");
        exit(1);
    }
    int t1;
    fscanf(fp1, "%d ", &t1);
    int* a1 = (int*)calloc(t1, sizeof(int));

    int t2;
    fscanf(fp2, "%d ", &t2);
    int* a2 = (int*)calloc(t2, sizeof(int));

    int c = 0;
    while (fscanf(fp1, "%d ", a1 + c++) != -1);
    c = 0;
    while (fscanf(fp2, "%d ", a2 + c++) != -1);

    asdf(a1, t1, a2, t2);
}