#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

typedef struct {
    char* key;
    char* value;
} HashTableItem;

typedef struct ListNode {
    HashTableItem* item;
    struct ListNode* next;
} ListNode;

typedef struct {
    HashTableItem** items;
    ListNode** overflowBuckets;

    int size;
    int count;
} HashTable;

int hashString(char* str);

ListNode* insertList(ListNode* head, HashTableItem* item);
HashTableItem* removeFromList(ListNode* head);
void handleCollision(HashTable* table, int index, HashTableItem* item);

HashTableItem* createItem(char* key, char* value);

HashTable* createHashTable(int size);
bool insertHashTable(HashTable* table, char* key, char* value);
char* searchHashTable(HashTable* table, char* key);
void deleteFromHashTable(HashTable* table, char* key);


void freeHashItem(HashTableItem* item);
void freeHashTable(HashTable* table);
void freeOverflowBuckets(HashTable* table);
void freeLinkedList(ListNode* head);


void printHashTable(HashTable* table);

#endif // !HASHTABLE_H
