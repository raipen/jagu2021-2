typedef struct {
    char operator;
    int order;
    int value;
}contents;

int commonOrder(char ope) {
    switch (ope) {
    case '+': return 1;
    case '-': return 1;
    case '*': return 2;
    case '/': return 2;
    case '%': return 2;
    case ')': return 99;
    default: return 0;
    }
}

int pushOrder(char ope) {
    switch (ope) {
    case '(': return 100;
    default: return commonOrder(ope);
    }
}

int popOrder(char ope) {
    switch (ope) {
    case '(': return 0;
    default: return commonOrder(ope);
    }
}

typedef struct {
    contents* stack;
    int t;
    int capacity;
}stack;

int isEmpty(stack* this) {
    return (this->t == -1) ? 1 : 0;
}

int isFull(stack* this) {
    return (this->t == this->capacity - 1) ? 1 : 0;
}

void push(stack* this, contents con) {
    if (isFull(this)) {
        this->capacity *= 2;
        this->stack = (contents*)realloc(this->stack, sizeof(contents) * this->capacity);
        //printf("더블링 완료 %d\n", this->capacity);
    }
    this->stack[++(this->t)] = con;
}

contents pop(stack* this) {
    if (isEmpty(this)) {
        printf("스택이 비었음\n");
        return;
    }
    return this->stack[this->t--];
}

contents top(stack* this) {
    if (isEmpty(this)) {
        printf("스택이 비었음\n");
        return;
    }
    return this->stack[this->t];
}

stack* newStack() {
    stack* temp = (stack*)malloc(sizeof(stack));
    temp->capacity = 1;
    temp->stack = (contents*)calloc(temp->capacity, sizeof(contents));
    temp->t = -1;
    return temp;
}

void deleteStack(stack* this) {
    free(this->stack);
    free(this);
}

void printStack(stack* this) {
    for (int i = 0;i <= this->t;i++) {
        printf("%c %d\n", this->stack[i].operator, this->stack[i].order);
    }
}