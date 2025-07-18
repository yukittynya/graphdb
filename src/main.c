#include "lib/hashtable/hashtable.h"
#include "lib/info.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    HashTable* table = createHashTable(CAPACITY);

    insertHashTable(table, "Node 1", "Emma");
    insertHashTable(table, "Node 2", "a;ldfjhs");
    insertHashTable(table, "Node 3", "ognam");
    insertHashTable(table, "Node 3", "mango");
    insertHashTable(table, "Node 4", "Pineapple");
    insertHashTable(table, "Node 5", "Jeff");

    printHashTable(table);

    char* value = searchHashTable(table, "Node 3");
    printf("\nSearched for Node 3 got, '%s'\n", value);

    deleteFromHashTable(table, "Node 3");
    printHashTable(table);

    freeHashTable(table);
}
