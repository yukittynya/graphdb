#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define INSERT_ITEM(t, k, v) insertHashTable(t, k, &(v), sizeof(v))

typedef struct {
    uint64_t key;
    void* value;
} HashTableItem;

typedef struct ListNode {
    HashTableItem* item;
    struct ListNode* next;
} ListNode;

typedef struct {
    HashTableItem** items;
    ListNode** overflowBuckets;

    size_t size;
    size_t count;
} HashTable;

int hash(uint64_t key);

ListNode* insertList(ListNode* head, HashTableItem* item);
HashTableItem* removeFromList(ListNode* head);
void handleCollision(HashTable* table, int index, HashTableItem* item);


HashTableItem* createItem(uint64_t key, void* value, size_t valueSize);
HashTable* createHashTable(int size);
bool insertHashTable(HashTable* table, uint64_t key, void* value, size_t valueSize);
void* searchHashTable(HashTable* table, uint64_t key);
void deleteFromHashTable(HashTable* table, uint64_t key);


void freeHashItem(HashTableItem* item);
void freeHashTable(HashTable* table);
void freeOverflowBuckets(HashTable* table);
void freeLinkedList(ListNode* head);


void printHashTable(HashTable* table);

#endif // !HASHTABLE_H
