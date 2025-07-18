#include "hashtable.h"
#include "../info.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long hashString(char* str) {
    unsigned long i = 0.0;

    for (int j = 0; str[j]; j++) {
        i += str[j];
    }

    return i % CAPACITY;
}

// Items

HashTableItem* createItem(char* key, char* value) {
    HashTableItem* item = (HashTableItem*) malloc(sizeof(HashTableItem));

    item -> key = (char*) malloc(strlen(key) + 1);
    item -> value = (char*) malloc(strlen(value) + 1);

    strcpy(item -> key, key);
    strcpy(item -> value, value);

    return item;
}

// Table

HashTable* createHashTable(int size) {
    HashTable* table = (HashTable*) malloc(sizeof(HashTable));

    table -> count = 0;
    table -> size = size;
    table -> items = (HashTableItem**) calloc(table -> size, sizeof(HashTableItem*));

    for (int i = 0; i < size; i++) {
        table -> items[i] = NULL;
    } 

    return table;
}


// Return false on insert failure, upgrade to result type in the future
// I just want to get it working for now
bool insertHashTable(HashTable* table, char* key, char* value) {
    if (table -> count == table -> size) {
        return false;
    }

    HashTableItem* item = createItem(key, value);
    unsigned long index = hashString(key);

    HashTableItem* currentItem = table -> items[index];

    if (currentItem == NULL) {
        table -> items[index] = item;
        table -> count++;

        return true;
    } else if (strcmp(currentItem -> key, key) == 0) {
        strcpy(currentItem -> value, value);

        return true;
    } else {
        //handleCollision(table, item);

        return true;
    }
}


void freeHashItem(HashTableItem* item) {
    free(item -> key);
    free(item -> value); 
    free(item );
}

void freeHashTable(HashTable* table) {
    for (int i = 0; i < table -> size; i++) {
        HashTableItem* item = table -> items[i];

        if (item != NULL) {
            freeHashItem(item);
        }
    }

    free(table -> items);
    free(table);
}

void printHashTable(HashTable* table) {
    printf("\n--------- Hash Table ---------\n");

    for (int i = 0; i < table -> size; i++) {
        if (table -> items[i]) {
            printf("Index: %d\n\tKey: %s\nValue: %s\n", i, table -> items[i] -> key, table -> items[i] -> key);
        }
    }

    printf("\n--------- Hash Table ---------\n");
}
