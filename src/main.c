#include "lib/hashtable/hashtable.h"
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

    freeHashTable(table);
}
