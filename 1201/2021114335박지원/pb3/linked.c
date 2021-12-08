#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
	int data;
	struct NODE *next;
} NODE;

void insert(NODE** head,int data, int location) {
	NODE* cur = (*head);
	while(cur->next!=NULL&&location--)
	{
		cur = cur->next;
	}
	NODE * newNode = malloc(sizeof(NODE));
	newNode->next = cur->next;
	newNode->data = data;
	cur->next = newNode;
}

void printList(NODE* linkedList)
{
	NODE* currNode;
	currNode = linkedList->next;
	while (currNode != NULL)
	{
		printf("%2d", currNode->data);
		currNode = currNode->next;
	}
}

void delete(NODE** head, int data) {
	NODE* cur;
	cur = (*head);
	while (cur != NULL&&cur->next->data!=data)
	{
		cur = cur->next;
	}
	cur->next = cur->next->next;
}

void freeList(NODE** head) {
	NODE* cur;
	cur = (*head)->next;
	while (cur != NULL )
	{	
		NODE* temp = cur;
		cur = cur->next;
		free(temp);
	}
}

int main()
{
	int count;
	printf("배열의 개수를 입력하세요: ");
	scanf("%d", &count);

	NODE* head = malloc(sizeof(NODE));	// head 노드는 데이터가 없음 (0번째 인덱스에 값을 넣기 위한 용도)
	head->next = NULL;

	int data;
	printf("배열의 요소를 입력하세요: ");	//데이터 추가
	while (count--)	{
		scanf(" %d", &data);
		insert(&head, data, -1);
	}
	printList(head);

	int loc;
	printf("\n삽입할 데이터와 데이터의 위치를 입력하세요: ");	// 데이터 삽입
	scanf("%d %d", &data, &loc);
	insert(&head, data, loc);
	printList(head);


	printf("\n삭제할 데이터를 입력하세요: ");	// 데이터 삭제
	scanf("%d", &data);
	delete(&head, data);
	printList(head);

	freeList(&head);
	printf("\n");
	return 0;
}