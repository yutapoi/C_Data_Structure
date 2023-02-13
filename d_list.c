#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define ERROR INT_MIN

typedef struct DNode {
    struct DNode *prev;
    int val;
    struct DNode *next;
} DNode;

typedef struct {
    DNode *head;
    DNode *tail;
    int size;
} DList;



DList* init() {
    DList *dlist = (DList *) malloc(sizeof(DList));
    if(NULL == dlist) {
        printf("Fail to initialize a double linked list.\n");
        return NULL;
    }
    dlist->head = NULL;
    dlist->tail = NULL;
    dlist->size = 0;
    return dlist;
}

bool isEmpty(DList* dlist) {
    if(NULL == dlist) {
        printf("The double linked list has not been initialized.\n");
        return false;
    }
    return (0 == dlist->size);
}

void insert_at_head(DList* dlist, int val) {
    if(NULL == dlist) {
        printf("The double linked list has not been initialized.\n");
        return;
    }
    DNode *dnode = (DNode*) malloc(sizeof(DNode));
    if(NULL == dnode) {
        printf("Fail to initialize a double linked list node.\n");
        return;
    }
    dnode->val = val;
    dnode->next = NULL;
    dnode->prev = NULL;
    if(!dlist->head) {
        dlist->head = dnode;
        dlist->tail = dnode;
    } else {
        dnode->next = dlist->head;
        dlist->head->prev = dnode;
        dlist->head = dnode;
    }
    dlist->size++;
    return;
}

void insert_at_tail(DList* dlist, int val) {
    if(NULL == dlist) {
        printf("The double linked list has not been initialized.\n");
        return;
    }
    DNode *dnode = (DNode*) malloc(sizeof(DNode));
    if(NULL == dnode) {
        printf("Fail to initialize a double linked list node.\n");
        return;
    }
    dnode->val = val;
    dnode->next = NULL;
    dnode->prev = NULL;
    if(!dlist->head) {
        insert_at_head(dlist, val);
        return;
    }
    dlist->tail->next = dnode;
    dnode->prev = dlist->tail;
    dlist->tail = dnode;
    dlist->size++;
    return;
}

void insert_at_index(DList* dlist, int val, int index) {
    if(NULL == dlist) {
        printf("The double linked list has not been initialized.\n");
        return;
    }
    DNode *dnode = (DNode*) malloc(sizeof(DNode));
    if(NULL == dnode) {
        printf("Fail to initialize a double linked list node.\n");
        return;
    }
    if(index < 0) {
        printf("The index value is invalid.\n");
        return;
    }
    if(index == 0) {
        insert_at_head(dlist, val);
        return;
    }
    if(index >= dlist->size) {
        insert_at_tail(dlist, val);
        return;
    }
    dnode->val = val;
    dnode->next = NULL;
    dnode->prev = NULL;
    DNode *temp = dlist->head;
    for(int i = 0; i < index - 1; ++i) {
        temp = temp->next;
    }
    dnode->next = temp->next;
    dnode->prev = temp;
    temp->next->prev = dnode;
    temp->next = dnode;
    dlist->size++;
    return;
}

int peek_at_index(DList* dlist, int index) {
    if(NULL == dlist) {
        printf("The list has not been initialized.\n");
        return ERROR;
    }
    if(index < 0 || index >= dlist->size) {
        printf("The index value is invalid.\n");
        return ERROR;
    }
    DNode *temp = dlist->head;
    for(int i = 0; i < index; ++i) {
        temp = temp->next;
    }
    return temp->val;
}

void printList(DList* dlist) {
    if(NULL == dlist) {
        printf("The double linked list has not been initialized.\n");
        return;
    }
    if(0 == dlist->size) {
        printf("The double linked list is empty.\n");
        return;
    }
    DNode *temp = dlist->head;
    while(temp) {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
    temp = dlist->tail;
    while(temp) {
        printf("%d ", temp->val);
        temp = temp->prev;
    }
    printf("\n");
    return;
}

void delete_at_index(DList* dlist, int index) {
    if(NULL == dlist) {
        printf("The list has not been initialized.\n");
        return;
    }
    if(isEmpty(dlist)) {
        printf("The list is empty.\n");
        return;
    }
    if(index < 0 || index >= dlist->size) {
        printf("The index value is invalid.\n");
        return;
    }
    if(index == 0) {
        if(dlist->head->next) {
            DNode* temp = dlist->head->next;
            temp->prev = NULL;
            free(dlist->head);
            dlist->head = temp;
            dlist->size--;
            return;
        } else {
            free(dlist->head);
            dlist->head = NULL;
            dlist->size--;
            return;
        }
    }
    DNode *prevNode = dlist->head;
    for(int i = 0; i < index - 1; ++i) {
        prevNode = prevNode->next;
    }
    DNode *deleNode = prevNode->next;
    if(deleNode->next) {
        DNode *nextNode = deleNode->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    } else {
        prevNode->next = NULL;
    }
    free(deleNode);
    deleNode = NULL;
    dlist->size--;
    return;
}

DList* delete_list(DList* dlist) {
    if(NULL == dlist) {
        printf("The list has not been initialized.\n");
        return dlist;
    }
    DNode *temp = NULL;
    while(dlist->head) {
        temp = dlist->head->next;
        free(dlist->head);
        dlist->head = temp;
    }
    free(dlist);
    return NULL;
}

void reverse(DList* dlist) {
    if(NULL == dlist) {
        printf("The list has not been initialized.\n");
        return;
    }
    if(!dlist->head || !dlist->head->next) {
        return;
    }

    DNode *curr = dlist->head;
    while(curr) {
        DNode *temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }
    DNode *temp = dlist->head;
    dlist->head = dlist->tail;
    dlist->tail = temp;
}

void test() {
    DList *dlist = init();
    insert_at_tail(dlist, 1);
    insert_at_tail(dlist, 2);
    insert_at_index(dlist, 3, 1);
    insert_at_index(dlist, 4, 3);
    insert_at_index(dlist, 5, 3);

    printf("%d\n", dlist->size);
    printList(dlist);
    reverse(dlist);
    printf("%d\n", dlist->size);
    printList(dlist);


}



int main() {
    test();

    return 0;
}
