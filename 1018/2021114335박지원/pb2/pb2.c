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
    list* a = newLinkedList();      //새로운 연결리스트 a 만들기
    while (!feof(fp)) {
        int temp;
        fscanf(fp, "%d", &temp);
        insert(a, temp, -1);            //맨 끝 노드에 추가(-1)
    }
    printf("리스트:\n");
    printNode(a,"[%2d]");       //연결리스트 a 출력
    printf("\n");

    while (1) {
        printf("input number:");
        int input;
        scanf("%d", &input);
        if (input == -1) {                  //입력받은 값이 -1이면
            deleteLinkedList(a);       //연결리스트에 할당된 메모리를 해제하고
            exit(0);                            //프로그램 종료
        }

        if (input % 10>4) {                                      //1의 자리수가 5~9이면
            int index = search(a, input, same);        //해당 값 위치를 리턴, 이때 값을 못 찾으면 -1을 리턴
            if (index == -1)                                       //값을 못 찾았다면
                printf("삭제할 수 %d 없음.\n", input);//없다고 출력
            else {                                                     //값이 있으면
                removeNode(a, index);                     //해당 노드 삭제
            }
            printNode(a, "[%2d]");   //노드 출력
        }
        else {                                                          //1의 자리수가 0~4이면
            int index = search(a, input, compare);   //해당값보다 작은 값이 나오면 그 위치를 리턴, 없으면 -1 리턴
            insert(a, input, index);                            //그 위치에 값을 삽입, 더 큰 값이 없다면 -1 이므로 자동으로 맨 뒤에 추가
            printNode(a, "[%2d]");                           //노드 출력
        }
    }
}