#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int ibs(int a[], int s, int l, int r) {
    int m;
    while (l <= r) {
        m = (l + r) / 2;
        switch (a[m] < s ? -1 : (a[m]>s ? 1 : 0)) {
        case -1:l = m + 1; break;
        case 0: return m;
        case 1: r = m - 1;
        }
    }
    return -1;
}

int rbs(int a[], int s, int l, int r) {
    int m;
    while (l <= r) {
        m = (l + r) / 2;
        switch (a[m] < s ? -1 : (a[m] > s ? 1 : 0)) {
        case -1: return rbs(a, s, m + 1, r);
        case 0: return m;
        case 1: return rbs(a, s, l, m-1);
        }
    }
    return -1;
}


void main() {
    int arr[100];
    int index=0;

	FILE* fp = fopen("in.txt", "r");
    if (!fp) {
        printf("파일 없음");
        exit(1);
    }
    while (fscanf(fp, "%d ", &arr[index])!=-1) 
        index++;

    int input;
    while (1) {
        printf("Input number: ");
        fscanf(stdin, "%d", &input);
        if (input < 0) {
            printf("Exit");
            return;
        }
        int temp1 = ibs(arr, input, 0, c);
        int temp2 = rbs(arr, input, 0, c);
        printf("interative binaray search: ");
        if(temp1==-1)
            printf("없음\n");
        else
            printf("있음\n");
        printf("recursive binaray search: ");
        if (temp2 == -1)
            printf("없음\n");
        else
            printf("있음\n");
    }
}