#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 100
#define ERROR INT_MIN



typedef struct QNode {
    int val;
    struct QNode* next;
} QNode;

typedef struct {
   int size;
   QNode* front;
   QNode* rear;
} Q;

Q* init() {
    Q* q = (Q*) malloc(sizeof(Q));
    if(NULL == q) {
        printf("Fail to initialize a queue.\n");
        return NULL;
    }
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

bool isFull(Q* q){
    return MAX_SIZE == q->size;
}

bool isEmpty(Q* q){
    return 0 == q->size;
}

void push(Q* q, int val){
    if(NULL == q) {
        printf("The queue has not been initialized.\n");
        return;
    }
    if(isFull(q)) {
        printf("The queue has been full.\n");
        return;
    }
    QNode* node = (QNode*) malloc(sizeof(QNode));
    if(NULL == node) {
        printf("Fail to initialize a queue node.\n");
        return;
    }
    node->val = val;
    node->next = NULL;
    if(NULL == q->front) {
        q->front = node;
    }
    if(NULL == q->rear) {
        q->rear = node;
    } else {
        q->rear->next = node;
        q->rear = node;
    }
    q->size++;
    return;

}

void print_queue(Q* q) {
    if(NULL == q) {
        printf("The queue has not been initialized.\n");
        return;
    }
    if(isEmpty(q)){
        printf("The queue is empty.\n");
        return;
    }
    QNode* temp = q->front;
    while(temp) {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

int peek(Q* q){
    if(NULL == q) {
        printf("The queue has not been initialized.\n");
        return ERROR;
    }
    if(isEmpty(q)){
        printf("The queue is empty.\n");
        return ERROR;
    }
    return q->front->val;
}

int pop(Q* q) {
    if(NULL == q) {
        printf("The queue has not been initialized.\n");
        return ERROR;
    }
    if(isEmpty(q)){
        printf("The queue is empty.\n");
        return ERROR;
    }
    int res = q->front->val;
    if(1 == q->size) {
        free(q->front);
        q->front = NULL;
        q->rear = NULL;
    } else {
        QNode* temp = q->front->next;
        free(q->front);
        q->front = temp;
    }
    q->size--;
    return res;
}

Q* destory_queue(Q* q) {
    if(NULL == q) {
        printf("The queue has not been initialized.\n");
        return NULL;
    }
    QNode *temp = q->front;
    while(q->front) {
        q->front = q->front->next;
        free(temp);
        temp = q->front;
    }
    free(q);
    return NULL;
}


void test() {
    Q* q = init();
    push(q, 1);
    push(q, 2);
    push(q, 3);
    push(q, 4);
    print_queue(q);
    int a = peek(q);
    printf("%d\n", a);
    int b = pop(q);
    printf("%d\n", b);
    print_queue(q);
    pop(q);
    pop(q);
    pop(q);
    print_queue(q);
    q = destory_queue(q);
    print_queue(q);
}

int main() {
    test();
    return 0;
}