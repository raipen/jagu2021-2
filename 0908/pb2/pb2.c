#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int br(n) {
    if (n == 0) return;
    br(n / 2);
    printf("%d",n % 2);
}

int brz(n,c) {
    if (n == 0) return c;
    if (n % 2 == 0) c++;
    brz(n / 2,c);
}

void main() {
    int input;
    while (1) {
        printf("Input number: ");
        fscanf(stdin, "%d", &input);
        if (input < 0) {
            printf("Exit");
            return;
        }
        printf("2��ǥ��: ");
        br(input);
        printf("\n%d�� 0�� %d�� �ִ�.\n",input, brz(input,0));
    }
}