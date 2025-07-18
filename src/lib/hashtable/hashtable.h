#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

typedef struct {
    char* key;
    char* value;
} HashTableItem;

typedef struct {
    HashTableItem** items;

    int size;
    int count;
} HashTable;

unsigned long hashString(char* str);


HashTableItem* createItem(char* key, char* value);


HashTable* createHashTable(int size);
bool insertHashTable(HashTable* table, char* key, char* value);

void freeHashItem(HashTableItem* item);
void freeHashTable(HashTable* table);


void printHashTable(HashTable* table);

#endif // !HASHTABLE_H
