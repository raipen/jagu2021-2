#define _CRT_SECURE_NO_WARNINGS
#include "Linkedlist.h"

void main() {
    FILE* fp = fopen("list.txt", "r");
    list* a = newLinkedList();      //���ο� ���Ḯ��Ʈ a �����
    while (!feof(fp)) {
        int temp;
        fscanf(fp, "%d", &temp);
        if(!(temp%2))                        //¦�� �̸�
            insert(a, temp, 0);            //���Ḯ��Ʈ a �� �� �տ� temp�� �߰�
    }
    printf("¦�� ����Ʈ:\n");
    printNode(a,"%4d");             //���Ḯ��Ʈ a ���
    deleteLinkedList(a);
}