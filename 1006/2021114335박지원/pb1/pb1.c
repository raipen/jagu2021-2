#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


char* postfix(char str[]) {
	char* poststr=(char*)malloc(sizeof(char)*100);
	int index = 0;
	stack* temp = newStack();
	for (int i = 0;i < strlen(str);i++) {
		int ord = pushOrder(str[i]);
		if (ord == 99) {
			while (top(temp).operator!='(') {
				poststr[index]= pop(temp).operator;
				index++;
			}
			pop(temp);
		}
		else if (ord) {
			while (!isEmpty(temp) && top(temp).order >= ord) {
				poststr[index] = pop(temp).operator;
				index++;
			}
			contents con = { str[i],popOrder(str[i]),0 };
			push(temp, con);
		}
		else {
			poststr[index] = str[i];
			index++;
		}
	}
	while (!isEmpty(temp)) {
		poststr[index] = pop(temp).operator;
		index++;
	}
	poststr[index] = '\0';
	return poststr;
}

int calculate(char str[]) {
	stack* temp = newStack();
	contents con = { 0,0 };
	for (int i = 0;i < strlen(str);i++) {
		if (!commonOrder(str[i])) {
			con.value =str[i]-'0';
			//printf("\n숫자%d", con.value);
			push(temp, con);
		}
		else {
			int a = pop(temp).value;
			int b = pop(temp).value;
			switch (str[i]) {
			case '+': con.value = b + a; break;
			case '-': con.value = b - a;break;
			case '*': con.value = b * a;break;
			case '/': con.value = b / a;break;
			case '%': con.value = b % a;break;
			}
			//printf("\n계산%d%c%d=%d", a,str[i],b,con.value);
			push(temp, con);
		}
	}
	return pop(temp).value;
}

void main() {
	char str[100];
	FILE* fp = fopen("infix.txt", "r");
	while (!feof(fp)) {
		printf("Infix:");
		fscanf(fp, "%s", str);
		printf("%s", str);
		char* poststr = postfix(str);
		printf("\nPostfix: %s", poststr);
		printf("\nEvaluation: %d\n\n", calculate(poststr));
	}
}