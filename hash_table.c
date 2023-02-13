#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>


#define ARR_LEN UINT_MAX

typedef struct HashNode {
    const char* key;
    int val;
    struct HashNode* next;
} HNode;

typedef struct {
    HNode* table[ARR_LEN];
    int size;
} HTable;

HTable* init() {
    HTable* ht = (HTable*) malloc(sizeof(HTable));
    if(NULL == ht) {
        printf("Fail to initialize a Hash Table.\n");
        return NULL;
    }
    ht->size = 0;
    return ht;
}

HTable* destroy(HTable* ht) {
    if(!ht) {
        return NULL;
    }
    for(unsigned int i = 0; i < ARR_LEN; ++i) {
        if(ht->table[i]) {
            HNode* head = ht->table[i];
            HNode* temp = head;
            while(head) {
                head = head->next;
                free(temp);
                temp = head;
            }
            ht->table[i] = NULL;
        }
    }
    free(ht);
    return NULL;
}

bool isEmpty(HTable* ht) {
    if(!ht) {
        printf("not initialized.\n");
        return false;
    }
    return (0 == ht->size);
}

unsigned int hashCode(const char* str) {
    unsigned int len = strlen(str);
    unsigned int seed = 131;
    unsigned int hash = 0;
    for(unsigned int i = 0; i < len; ++i) {
        hash = hash * seed + (*str++);
    }
    return hash;
}

bool isSameKey(const char* str1, const char* str2) {
    unsigned int len1 = strlen(str1);
    unsigned int len2 = strlen(str2);
    if(len1 != len2) {
        return false;
    }
    for(unsigned int i = 0; i < len1; ++i) {
        if(str1[i] != str2[i]) {
            return false;
        }
    }
    return true;
}

HNode* search(HTable* ht, const char* str) {
    if(!ht) {
        printf("not initialized.\n");
        return NULL;
    }
    unsigned int index = hashCode(str);
    if(NULL == ht->table[index]) {
        printf("No such element.1\n");
        return NULL;
    }
    HNode* temp = ht->table[index];
    while(temp) {
        const char* curr = temp->key;
        if(isSameKey(curr, str)) {
            return temp;
        }
        temp = temp->next;
    }
    printf("No such element.2\n");
    return NULL;
}

void insert(HTable* ht, const char* str, int val) {
    if(!ht) {
        printf("not initialized.\n");
        return;
    }
    unsigned int index = hashCode(str);
    HNode* temp = search(ht, str);

    if(temp) {
        printf("The key exists.\n");
        return;
    }
    temp = (HNode*) calloc(1, sizeof(HNode));
    if(!temp) {
        printf("Fail to initialize a Hash Node.\n");
    }

    temp->key = str;
    temp->val = val;
    temp->next = NULL;
    if(NULL == ht->table[index]) {
        ht->table[index] = temp;
    } else {
        temp->next = ht->table[index];
        ht->table[index] = temp;
    }
    ht->size++;

    return;
}

void remove_element(HTable* ht, const char* str) {
    if(!ht) {
        printf("not initialized.\n");
        return;
    }
    if(isEmpty(ht)) {
        printf("The table is empty.\n");
        return;
    }
    HNode* node = search(ht, str);
    if(NULL == node) {
        printf("No such element.\n");
        return;
    }
    unsigned int index = hashCode(str);
    HNode* curr = ht->table[index];
    if(curr == node) {
        HNode* temp = curr->next;
        free(curr);
        ht->table[index] = temp;
    } else {
        while(curr->next) {
            if(curr->next == node) {
                HNode* prev = curr;
                HNode* temp = curr->next;
                prev->next = temp->next;
                free(temp);
                break;
            }
            curr = curr->next;
        }
    }
    ht->size--;
    return;
}

void test() {
    HTable* ht = init();
    printf("%d\n", ht->size);
    insert(ht, "aa", 25);
    insert(ht, "bb", 30);
    insert(ht, "cc", 35);
    printf("%d\n", ht->size);
    remove_element(ht, "bb");
    HNode* temp1 = search(ht, "bb");
    insert(ht, "bb", 50);
    HNode* temp = search(ht, "bb");
    printf("%d\n", temp->val);


}

int main() {
    test();
    return 0;
}