#ifndef PARSER_H
#define PARSER_H

#include "../info.h"
#include "../hashtable/hashtable.h"
#include "../node/node.h"

char* getBuffer(char* path);

HashTable* parseNodes();
HashTable* parseEdges();
HashTable* parseAdjacencyLists();

#endif // !PARSER_H
