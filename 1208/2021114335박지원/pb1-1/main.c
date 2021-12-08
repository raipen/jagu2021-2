#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

typedef int element;

int digit(int b, int i) {
    return b / ((int)pow(10, i)) % 10;
}

int radixSort(element a[], int link[], int d, int r, int n) {
    int* front = (int*)malloc(sizeof(int) * r);
    int* rear = (int*)malloc(sizeof(int) * r);
    int i, bin, current, first, last;
    first = 1;
    for (i = 1; i < n; i++) {
        link[i] = i + 1;
    }
    link[n] = 0;
    for (i = 0; i <= d - 1; i++) {
        for (bin = 0; bin < r; bin++)
            front[bin] = 0;
        for (current = first; current; current = link[current]) {
            bin = digit(a[current], i);

            if (front[bin] == 0)
                front[bin] = current;
            else
                link[rear[bin]] = current;
            rear[bin] = current;
        }
        for (bin = 9; !front[bin]; bin--);
        first = front[bin];
        last = rear[bin];

        for (bin--;bin >= 0;bin--)
            if (front[bin]) {
                link[last] = front[bin];
                last = rear[bin];
            }
        link[last] = 0;
    }
    return first;
}

void printData(element a[], int link[], int start) {
    while (start != 0) {
        printf("%2d ", a[start]);
        start = link[start];
    }
}

int main() {
    int i = 0;
    int n = 0;

    srand(time(NULL));
    printf("Input size:");
    scanf("%d", &i);
    element* a = (int*)calloc((i + 1), sizeof(int));
    int* link = (int*)calloc((i + 1), sizeof(int));
    printf("Input range(10~9999):");
    scanf("%d", &n);
    printf("before radix sort...\n");
    for (int x = 1; x < i + 1; x++) {
        a[x] = rand() % (n+1);
        printf("%d ", a[x]);
    }

    int count = 0;
    for (int key = 1;n / key;key *= 10, count++);

    printf("\nafter radix sort...\n");
    int first = radixSort(a, link, count, 10, i);
    printData(a,link,first);

    free(link);
    free(a);
    return 0;
}