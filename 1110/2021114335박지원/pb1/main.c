#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n==MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)
typedef char element;
element heap[MAX_ELEMENTS];
int n = 0;

void push(element item){
    int i;

    if (HEAP_FULL(n)){
        fprintf(stderr, "The heap is full.\n");
        exit(1);
    }

    i = ++n;
    while ((i != 1) && (item < heap[i / 2])) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = item;
}

element pop() {
    int parent, child;
    int item, temp;

    if (HEAP_EMPTY(n)) {
        fprintf(stderr, "The heap is empty\n");
        exit(1);
    }

    item = heap[1];
    temp = heap[(n)--];
    parent = 1;
    child = 2;

    while (child <= n)
    {
        if ((child < n) && (heap[child] > heap[child + 1]))
            child++;

        if (temp <= heap[child])    break;

        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }

    heap[parent] = temp;
    return item;
}

void levelorder() {
    for (int i = 1;i <= n;i++) {
        printf("%c ", heap[i]);
    }
    printf("\n");
}

void main() {
    char a;
    FILE* fp = fopen("in1.txt", "r");
    while (!feof(fp)) {
        fscanf(fp, "%c ", &a);
        push(a);
    }

    printf("Min Heap(Before deleting)\n");
    levelorder();


    printf("\nInput delete number:");
    int d;
    scanf("%d", &d);

    for (int i = 0;i < d;i++) {
        printf("deleted item: %c\n", pop());
    }
    printf("Min Heap(After deleting)\n");
    levelorder();
}