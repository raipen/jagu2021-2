#define _CRT_SECURE_NO_WARNINGS
#include "Linkedlist.h"

int same(contents a, contents b) {
    return a == b ? 1 : 0;
}

int compare(contents a, contents b) {
    return a < b ? 1 : 0;
}

void main() {
    FILE* fp = fopen("list.txt", "r");
    list* a = newLinkedList();      //���ο� ���Ḯ��Ʈ a �����
    while (!feof(fp)) {
        int temp;
        fscanf(fp, "%d", &temp);
        insert(a, temp, -1);            //�� �� ��忡 �߰�(-1)
    }
    printf("����Ʈ:\n");
    printNode(a,"[%2d]");       //���Ḯ��Ʈ a ���
    printf("\n");

    while (1) {
        printf("input number:");
        int input;
        scanf("%d", &input);
        if (input == -1) {                  //�Է¹��� ���� -1�̸�
            deleteLinkedList(a);       //���Ḯ��Ʈ�� �Ҵ�� �޸𸮸� �����ϰ�
            exit(0);                            //���α׷� ����
        }

        if (input % 10>4) {                                      //1�� �ڸ����� 5~9�̸�
            int index = search(a, input, same);        //�ش� �� ��ġ�� ����, �̶� ���� �� ã���� -1�� ����
            if (index == -1)                                       //���� �� ã�Ҵٸ�
                printf("������ �� %d ����.\n", input);//���ٰ� ���
            else {                                                     //���� ������
                removeNode(a, index);                     //�ش� ��� ����
            }
            printNode(a, "[%2d]");   //��� ���
        }
        else {                                                          //1�� �ڸ����� 0~4�̸�
            int index = search(a, input, compare);   //�ش簪���� ���� ���� ������ �� ��ġ�� ����, ������ -1 ����
            insert(a, input, index);                            //�� ��ġ�� ���� ����, �� ū ���� ���ٸ� -1 �̹Ƿ� �ڵ����� �� �ڿ� �߰�
            printNode(a, "[%2d]");                           //��� ���
        }
    }
}