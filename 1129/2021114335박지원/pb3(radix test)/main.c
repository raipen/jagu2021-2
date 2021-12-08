#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100

typedef int element;

//int link[MAX];
int first;

int digit(element a, int i, int r, int d) {// i =2 ,1, 0... r= 10 , d = 3;
    int val = a;
    for (int j = 0; j < d - i - 1; j++) //1의 자릿수면 for 문 1번 10의 자릿수면 2번 3의 자릿수면 3번돌고
        val /= r; // 몫으로 먼저 나눠준후
    return val % 10; // 나머지를 반환
}

int radixsort(element a[], int link[], int d, int r, int n) {//d는 자릿수?
    int* front, * rear;
    front = (int*)malloc(sizeof(int) * r); // r은 10진수니까 10
    rear = (int*)malloc(sizeof(int) * r);
    int i, bin, current, last;
    first = 1;

    for (i = 1; i < n; i++) {
        link[i] = i + 1; // link 초기화
    }
    link[n] = 0; //n은 size
    ;

    for (i = d - 1; i >= 0; i--) {
        for (bin = 0; bin < r; bin++) {
            front[bin] = 0;

        }

        for (current = first; current; current = link[current]) {
            bin = digit(a[current], i, r, d);
            if (front[bin] == 0)
                front[bin] = current;
            else link[rear[bin]] = current;
            rear[bin] = current;

        }
        for (bin = 9; !front[bin]; bin--); // 내림차순 정렬하려면 bin 을 마지막에서부터 읽어들여서 bin--하는 방식으로!!
        first = front[bin]; last = rear[bin];

        for (bin--; bin >= 0; bin--) {
            if (front[bin])
            {
                link[last] = front[bin]; last = rear[bin];
            }
        }
        link[last] = 0;

    }
    return first;
}

void print_link(int first) {
    printf("%2d ", a[first].key);
    int next = link[first];
    while (next != 0) {
        printf("%2d ", a[next].key);
        next = link[next];
    }
    printf("\n");
}

void print_arr(int n) {
    for (int i = 1; i <= n; i++) {
        printf("%2d ", a[i].key);
    }
    printf("\n\n");
}

int main() {
    int size, temp;
    int count = 0;
    printf("input size: ");
    scanf("%d", &size);
    element* a = (element*)malloc(sizeof(element) * (size + 1));
    int* link = (int*)malloc(sizeof(int) * (size + 1));
    printf("input range(10~9999): ");
    scanf("%d", &temp);

    printf("before radix sort...\n");
    int i;
    srand(time(NULL));
    for (i = 1; i <= size; i++) {
        a[i] = (rand() % (temp + 1 - 10)) + 10;
        printf("%d ", a[i]);
    }
    printf("\n");
    while (temp != 0) {
        temp = temp / 10;
        ++count;
    }

    int first = radixsort(a, link, count, 10, size);
    //   printf("first: %d\n\n", first);
    printf("after radix sort...\n");
    print_link(first);

    free(link);
    free(a);
    return 0;

}