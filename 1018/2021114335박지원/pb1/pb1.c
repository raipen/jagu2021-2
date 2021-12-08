#define _CRT_SECURE_NO_WARNINGS
#include "Linkedlist.h"

void main() {
    FILE* fp = fopen("list.txt", "r");
    list* a = newLinkedList();      //새로운 연결리스트 a 만들기
    while (!feof(fp)) {
        int temp;
        fscanf(fp, "%d", &temp);
        if(!(temp%2))                        //짝수 이면
            insert(a, temp, 0);            //연결리스트 a 의 맨 앞에 temp값 추가
    }
    printf("짝수 리스트:\n");
    printNode(a,"%4d");             //연결리스트 a 출력
    deleteLinkedList(a);
}