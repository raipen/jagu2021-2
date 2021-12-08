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
	printf("�迭�� ������ �Է��ϼ���: ");
	scanf("%d", &count);

	NODE* head = malloc(sizeof(NODE));	// head ���� �����Ͱ� ���� (0��° �ε����� ���� �ֱ� ���� �뵵)
	head->next = NULL;

	int data;
	printf("�迭�� ��Ҹ� �Է��ϼ���: ");	//������ �߰�
	while (count--)	{
		scanf(" %d", &data);
		insert(&head, data, -1);
	}
	printList(head);

	int loc;
	printf("\n������ �����Ϳ� �������� ��ġ�� �Է��ϼ���: ");	// ������ ����
	scanf("%d %d", &data, &loc);
	insert(&head, data, loc);
	printList(head);


	printf("\n������ �����͸� �Է��ϼ���: ");	// ������ ����
	scanf("%d", &data);
	delete(&head, data);
	printList(head);

	freeList(&head);
	printf("\n");
	return 0;
}