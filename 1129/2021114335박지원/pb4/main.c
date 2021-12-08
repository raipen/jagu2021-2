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
    for (i = 0; i <= d-1; i++) {
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

int main() {
    int i = 0;
    int n = 0;
    int key = 1;
    int count = 0;

    srand(time(NULL));
    printf("Input size:");
    scanf("%d", &i);
    element* a = (int*)calloc((i + 1),sizeof(int));
    int* link = (int*) calloc((i + 1),sizeof(int));
    printf("Input range(10~9999):");
    scanf("%d", &n);
    printf("before radix sort...\n");
    for (int x = 1; x < i + 1; x++) {
        int random = rand() % n;
        a[x] = random;
        printf("%d ", a[x]);
    }

    while (n / key) {
        key *= 10;
        count++;
    }


    printf("\nafter radix sort...\n");
    int first = radixSort(a, link, count, 10, i);
    int next = 0;

    printf("%d ", a[first]);
    next = link[first];
    while (next != 0) {
        printf("%2d ", a[next]);
        next = link[next];
    }
    printf("\n");

    free(link);
    free(a);
    return 0;
}