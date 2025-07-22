#include "lib/hashtable/hashtable.h"
#include "lib/parser/parser.h"
#include "lib/info.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    HashTable* table = createHashTable(CAPACITY);

    INSERT_ITEM(table, 1, "LALALA");
    INSERT_ITEM(table, 2, "C the goat");
    INSERT_ITEM(table, 3, "RUST <3333");
    INSERT_ITEM(table, 4, "C#");
    INSERT_ITEM(table, 5, "Potato");

    printHashTable(table);

    char* value = (char*) searchHashTable(table, 3);

    printf("\nSearched for Key: %d and Found: %s\n", 3, value);

    deleteFromHashTable(table, 3);

    printHashTable(table);

    freeHashTable(table);

    parseNodes();
}
