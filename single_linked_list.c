#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "single_linked_list.h"

#define ERROR INT_MIN

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} List;

List* init() {
    List *list = (List*)malloc(sizeof(List));
    if(NULL == list) {
        printf("Fail to initialize a list.\n");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

bool isEmpty(List* list) {
    if(NULL == list) {
        printf("The list has not been initialized.\n");
        return false;
    }
    return (0 == list->size);
}

void insert_at_head(List* list, int val) {
    if(NULL == list) {
        printf("The list has not been initialized.\n");
        return;
    }
    Node *node = (Node*) malloc(sizeof(Node));
    if(NULL == node) {
        printf("Fail to initialize a list node.\n");
        return;
    }
    node->val = val;
    node->next = NULL;
    if(!list->head) {
        list->head = node;
    } else {
        node->next = list->head;
        list->head = node;
    }
    list->size++;
    return;
}

void insert_at_tail(List* list, int val) {
    if(NULL == list) {
        printf("The list has not been initialized.\n");
        return;
    }
    Node *node = (Node*) malloc(sizeof(Node));
    if(NULL == node) {
        printf("Fail to initialize a list node.\n");
        return;
    }
    node->val = val;
    node->next = NULL;
    if(!list->head) {
        insert_at_head(list, val);
        return;
    }
    Node* temp = list->head;
    while(temp->next) {
        temp = temp->next;
    }
    temp->next = node;
    list->size++;
    return;
}

void insert_at_index(List* list, int val, int index) {
    if(NULL == list) {
        printf("The list has not been initialized.\n");
        return;
    }
    Node *node = (Node*) malloc(sizeof(Node));
    if(NULL == node) {
        printf("Fail to initialize a list node.\n");
        return;
    }
    if(index < 0) {
        printf("The index value is invalid.\n");
        return;
    }
    node->val = val;
    node->next = NULL;
    if(index >= list->size) {
        insert_at_tail(list, val);
        return;
    }
    Node *temp = list->head;
    if(0 == index) {
        insert_at_head(list, val);
        return;
    }
    for(int i = 0; i < index - 1; ++i) {
        temp = temp->next;
    }
    node->next = temp->next;
    temp->next = node;
    list->size++;
    return;
}

int peek_at_index(List* list, int index) {
    if(NULL == list) {
        printf("The list has not been initialized.\n");
        return ERROR;
    }
    if(index < 0 || index >= list->size) {
        printf("The index value is invalid.\n");
        return ERROR;
    }
    Node *temp = list->head;
    for(int i = 0; i < index; ++i) {
        temp = temp->next;
    }
    return temp->val;
}

void printList(List* list) {
    if(NULL == list) {
        printf("The list has not been initialized.\n");
        return;
    }
    if(0 == list->size) {
        printf("The list is empty.\n");
        return;
    }
    Node *temp = list->head;
    while(temp) {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
    return;
}

void delete_at_index(List* list, int index) {
    if(NULL == list) {
        printf("The list has not been initialized.\n");
        return;
    }
    if(isEmpty(list)) {
        printf("The list is empty.\n");
        return;
    }
    if(index < 0 || index >= list->size) {
        printf("The index value is invalid.\n");
        return;
    }
    Node *prev = list->head;
    if(index == 0) {
        list->head = list->head->next;
        list->size--;
        return;
    }
    for(int i = 0; i < index - 1; ++i) {
        prev = prev->next;
    }
    Node *dele = prev->next;
    prev->next = dele->next;
    free(dele);
    dele = NULL;
    list->size--;
    return;
}

List* delete_list(List* list) {
    if(NULL == list) {
        printf("The list has not been initialized.\n");
        return NULL;
    }
    Node *temp = NULL;
    while(list->head) {
        temp = list->head->next;
        free(list->head);
        list->head = temp;
    }
    free(list);
    return NULL;
}

void reverse(List* list) {
    if(NULL == list) {
        printf("The list has not been initialized.\n");
        return;
    }
    if(list->head == NULL || list->head->next == NULL) {
        return;
    }
    Node *prev = NULL;
    Node *curr = list->head;
    while(curr) {
        Node *temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    list->head = prev;
    return;
}

void test() {
    List* list = init();
    insert_at_index(list, 0, 0);
    insert_at_head(list, 1);
    insert_at_index(list, 3, 1);
    insert_at_tail(list, 2);
    //delete_at_index(list, 1);
    //list = delete_list(list);
    int a = peek_at_index(list, 2);
    printf("%d\n", a);
    printList(list);
    printf("%d\n", list->size);
    reverse(list);
    printList(list);
}

int main() {
    test();
    return 0;
}
