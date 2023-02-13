#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 100
#define ERROR INT_MIN

typedef struct StackNode {
    int val;
    struct StackNode* next;
} SNode;

typedef struct {
    SNode* top;
    int size;
} Stack;

Stack* init() {
    Stack* s = (Stack*) malloc(sizeof(Stack));
    if(NULL == s) {
        printf("Fail to initialize a stack.\n");
        return NULL;
    }
    s->top = NULL;
    s->size = 0;
    return s;
}

bool isFull(Stack* s){
    return MAX_SIZE == s->size;
}

bool isEmpty(Stack* s){
    return 0 == s->size;
}

void push(Stack* s, int val) {
    if(NULL == s) {
        printf("The stack has not been initialized.\n");
        return;
    }
    if(isFull(s)) {
        printf("The stack has been full.\n");
        return;
    }
    SNode* node = (SNode*) malloc(sizeof(SNode));
    if(!node) {
        printf("Fail to initialize a stack node.\n");
        return;
    }
    node->val = val;
    node->next = s->top;
    s->top = node;
    s->size++;
    return;
}

int peek(Stack* s) {
    if(NULL == s) {
        printf("The stack has not been initialized.\n");
        return ERROR;
    }
    if(isEmpty(s)){
        printf("The stack is empty.\n");
        return ERROR;
    }
    return s->top->val;
}

int pop(Stack* s) {
    if(NULL == s) {
        printf("The stack has not been initialized.\n");
        return ERROR;
    }
    if(isEmpty(s)){
        printf("The stack is empty.\n");
        return ERROR;
    }
    SNode* temp = s->top;
    int res = temp->val;
    s->top = s->top->next;
    s->size--;
    free(temp);
    return res;
}

Stack* destroy_stack(Stack* s){
    if(NULL == s) {
        printf("The stack has not been initialized.\n");
        return NULL;
    }
    SNode *temp = s->top;
    while(s->top) {
        s->top = s->top->next;
        free(temp);
        temp = s->top;
    }
    free(s);
    return NULL;
}

void print_stack(Stack* s) {
    if(NULL == s) {
        printf("The stack has not been initialized.\n");
        return;
    }
    if(isEmpty(s)){
        printf("The stack is empty.\n");
        return;
    }
    SNode* temp = s->top;
    while(temp) {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

void test() {
    Stack* s = init();
    push(s, 1);
    push(s, 2);
    push(s, 3);
    push(s, 4);
    push(s, 6);
    print_stack(s);
    int b = pop(s);
    printf("%d\n", b);
    print_stack(s);
    int a = peek(s);
    printf("%d\n", a);
    s = destroy_stack(s);
    print_stack(s);
}

int main() {
    test();
    return 0;
}