#include "hashtable.h"
#include "../info.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash(uint64_t key) {
    return ((key * 2654435761u) >> 16) % CAPACITY;
}

ListNode* insertList(ListNode* head, HashTableItem* item) {
    if (!head) {
        ListNode* node = (ListNode*) malloc(sizeof(ListNode));

        node -> item = item;
        node -> next = NULL;

        head = node;
        return head;
    }

    ListNode* current = head;

    while (current) {
        current = current -> next;
    }

    current = (ListNode*) malloc(sizeof(ListNode));
    current -> item = item;
    current -> next = NULL;

    return head;
}

HashTableItem* removeFromList(ListNode* head) {
    if (head == NULL) {
        return NULL;
    }

    ListNode* nextNode = head -> next;
    ListNode* current = head;

    current -> next = NULL;
    head = nextNode;

    HashTableItem* item = NULL;
    memcpy(current -> item, item, sizeof(HashTableItem));

    free(current -> item -> key);
    free(current -> item -> value);
    free(current -> item);
    free(current);

    return item;
}

void handleCollision(HashTable* table, int index, HashTableItem* item) {
    ListNode* head = table -> overflowBuckets[index];

    if (head == NULL) {
        head = (ListNode*) malloc(sizeof(ListNode));

        head -> item = item;
        head -> next = NULL;

        table -> overflowBuckets[index] = head;
    } else {
        insertList(head, item);
    }
}

HashTableItem* createItem(uint64_t key, void* value, size_t valueSize) {
    HashTableItem* item = (HashTableItem*) malloc(sizeof(HashTableItem));

    item -> key = key;
    item -> value = malloc(valueSize);

    memcpy(item -> value, value, valueSize);

    return item;
}

HashTable* createHashTable(int size) {
    HashTable* table = (HashTable*) malloc(sizeof(HashTable));

    table -> count = 0;
    table -> size = size;
    table -> items = (HashTableItem**) calloc(table -> size, sizeof(HashTableItem*));
    table -> overflowBuckets = (ListNode**) calloc(table -> size, sizeof(ListNode*));

    for (int i = 0; i < size; i++) {
        table -> items[i] = NULL;
    } 

    for (int i = 0; i < size; i++) {
        table -> overflowBuckets[i] = NULL;
    } 


    return table;
}


// Return false on insert failure, upgrade to result type in the future
// I just want to get it working for now
bool insertHashTable(HashTable* table, int key, char* value) {
    if (table -> count == table -> size) {
        return false;
    }

    HashTableItem* item = createItem(key, value);
    int index = hash(key);

    HashTableItem* currentItem = table -> items[index];

    if (currentItem == NULL) {
        table -> items[index] = item;
        table -> count++;

        return true;
    } else {
        handleCollision(table, index, item);

        return true;
    }
}

char* searchHashTable(HashTable* table, char* key) {
    int index = hash(key);
    HashTableItem* item = table -> items[index];

    if (item == NULL) {
        return NULL;
    }

    if (strcmp(item -> key, key) == 0) {
        return item -> value;
    }

    ListNode* head = table -> overflowBuckets[index];

    while (head != NULL) {
        item = head -> item;
        head = head -> next;
    }

    if (strcmp(item -> key, key) == 0) {
        return item -> value;
    }


    return NULL;
}

void deleteFromHashTable(HashTable* table, char* key) {
    int index = hash(key);
    HashTableItem* item = table -> items[index];

    if (item == NULL) return;

    ListNode* head = table -> overflowBuckets[index];

    if (head == NULL) {
        table -> items[index] = NULL;

        freeHashItem(item);
        table -> count--;

        return;
    }

    freeHashItem(item);
    freeLinkedList(head);

    table -> items[index] = NULL;
    table -> overflowBuckets[index] = NULL;
    table -> count--;
}

void freeHashItem(HashTableItem* item) {
    free(item -> key);
    free(item -> value); 
    free(item);
}

void freeHashTable(HashTable* table) {
    for (int i = 0; i < table -> size; i++) {
        HashTableItem* item = table -> items[i];

        if (item != NULL) {
            freeHashItem(item);
        }
    }

    freeOverflowBuckets(table);
    free(table -> items);
    free(table);
}

void freeOverflowBuckets(HashTable *table) {
    for (int i = 0; i < table -> size; i++) {
        ListNode* list = table -> overflowBuckets[i];

        if (list != NULL) {
            freeLinkedList(list);
        }
    }

    free(table -> overflowBuckets);
}

void freeLinkedList(ListNode* head) {
    ListNode* current = head;

    while (head != NULL) {
        current = head;
        head = head -> next;

        free(current -> item -> key);
        free(current -> item -> value);
        free(current -> item);
        free(current);
    }
}

void printHashTable(HashTable* table) {
    printf("\n--------- Hash Table ---------\n");

    for (int i = 0; i < table -> size; i++) {
        if (table -> items[i] != NULL) {
            printf("\nIndex: %d\n\tKey: %s\n\tValue: %s\n", i, table -> items[i] -> key, table -> items[i] -> value);
            if (table -> overflowBuckets[i] != NULL) {
                ListNode* head = table -> overflowBuckets[i];

                while (head) {
                    printf("\nBUCKET Index: %d\n\tKey: %s\n\tValue: %s\n", i, head -> item -> key, head -> item -> value);

                    head = head -> next;
                }

            }
        }     
    }

    float percent = (float)table -> count / (float)table -> size * 100; 

    printf("\nUsed %zu of %zu slots (%.4f%%)\n", table -> count, table -> size, percent);

    printf("\n--------- Hash Table ---------\n");
}
